// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

// Thread safe logger (except for set_error_handler())
// Has name, log level, vector of std::shared sink pointers and formatter
// Upon each log write the logger:
// 1. Checks if its log level is enough to log the message and if yes:
// 2. Call the underlying sinks to do the job.
// 3. Each sink use its own private copy of a formatter to format the message
// and send to its destination.
//
// The use of private formatter per sink provides the opportunity to cache some
// formatted data, and support for different format per sink.

#include "common.h"
#include "details/log_msg.h"
#include "sinks/sink.h"

#include <vector>
#include <cassert>

#ifndef SPDLOG_NO_EXCEPTIONS
#    define SPDLOG_LOGGER_CATCH(location)                                                                                                  \
        catch (const std::exception &ex)                                                                                                   \
        {                                                                                                                                  \
            if (location.filename)                                                                                                         \
            {                                                                                                                              \
                err_handler_(fmt_lib::format(SPDLOG_FMT_STRING("{} [{}({})]"), ex.what(), location.filename, location.line));              \
            }                                                                                                                              \
            else                                                                                                                           \
            {                                                                                                                              \
                err_handler_(ex.what());                                                                                                   \
            }                                                                                                                              \
        }                                                                                                                                  \
        catch (...)                                                                                                                        \
        {                                                                                                                                  \
            err_handler_("Rethrowing unknown exception in logger");                                                                        \
            throw;                                                                                                                         \
        }
#else
#    define SPDLOG_LOGGER_CATCH(location)
#endif

namespace spdlog {

class SPDLOG_API logger
{
public:
    // Empty logger
    explicit logger(std::string name)
        : name_(std::move(name))
    {}

    // Logger with range on sinks
    template<typename It>
    logger(std::string name, It begin, It end)
        : name_(std::move(name))
        , sinks_(begin, end)
    {}

    // Logger with single sink
    logger(std::string name, sink_ptr single_sink)
        : logger(std::move(name), {std::move(single_sink)})
    {}

    // Logger with sinks init list
    logger(std::string name, sinks_init_list sinks)
        : logger(std::move(name), sinks.begin(), sinks.end())
    {}

    virtual ~logger() = default;

    logger(const logger &other);
    logger(logger &&other) noexcept;
    logger &operator=(logger other) noexcept;
    void swap(spdlog::logger &other) noexcept;

    template<typename... Args>
    void log(source_loc loc, level::level_enum lvl, format_string_t<Args...> fmt, Args &&...args)
    {
        log_with_format_(loc, lvl, details::to_string_view(fmt), std::forward<Args>(args)...);
    }

    template<typename... Args>
    void log(level::level_enum lvl, format_string_t<Args...> fmt, Args &&...args)
    {
        log(source_loc{}, lvl, fmt, std::forward<Args>(args)...);
    }

    template<typename T>
    void log(level::level_enum lvl, const T &msg)
    {
        log(source_loc{}, lvl, msg);
    }

    // T cannot be statically converted to format string (including string_view/wstring_view)
    template<class T, typename std::enable_if<!is_convertible_to_any_format_string<const T &>::value, int>::type = 0>
    void log(source_loc loc, level::level_enum lvl, const T &msg)
    {
        log(loc, lvl, "{}", msg);
    }

    void log(log_clock::time_point log_time, source_loc loc, level::level_enum lvl, string_view_t msg)
    {
        if (should_log(lvl))
        {
            sink_it_(details::log_msg(log_time, loc, name_, lvl, msg));
        }
    }

    void log(source_loc loc, level::level_enum lvl, string_view_t msg)
    {
        if (should_log(lvl))
        {
            sink_it_(details::log_msg(loc, name_, lvl, msg));
        }
    }

    void log(level::level_enum lvl, string_view_t msg)
    {
        log(source_loc{}, lvl, msg);
    }

    template<typename... Args>
    void trace(format_string_t<Args...> fmt, Args &&...args)
    {
        log(level::trace, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(format_string_t<Args...> fmt, Args &&...args)
    {
        log(level::debug, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(format_string_t<Args...> fmt, Args &&...args)
    {
        log(level::info, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(format_string_t<Args...> fmt, Args &&...args)
    {
        log(level::warn, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(format_string_t<Args...> fmt, Args &&...args)
    {
        log(level::err, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(format_string_t<Args...> fmt, Args &&...args)
    {
        log(level::critical, fmt, std::forward<Args>(args)...);
    }

    template<typename T>
    void trace(const T &msg)
    {
        log(level::trace, msg);
    }

    template<typename T>
    void debug(const T &msg)
    {
        log(level::debug, msg);
    }

    template<typename T>
    void info(const T &msg)
    {
        log(level::info, msg);
    }

    template<typename T>
    void warn(const T &msg)
    {
        log(level::warn, msg);
    }

    template<typename T>
    void error(const T &msg)
    {
        log(level::err, msg);
    }

    template<typename T>
    void critical(const T &msg)
    {
        log(level::critical, msg);
    }

    // return true logging is enabled for the given level.
    [[nodiscard]] bool should_log(level::level_enum msg_level) const
    {
        return msg_level >= level_.load(std::memory_order_relaxed);
    }

    // set the level of logging
    void set_level(level::level_enum log_level);

    // return the active log level
    [[nodiscard]] level::level_enum level() const;

    // return the name of the logger
    [[nodiscard]] const std::string &name() const;

    // set formatting for the sinks in this logger.
    // each sink will get a separate instance of the formatter object.
    void set_formatter(std::unique_ptr<formatter> f);

    // set formatting for the sinks in this logger.
    // equivalent to
    //     set_formatter(make_unique<pattern_formatter>(pattern, time_type))
    // Note: each sink will get a new instance of a formatter object, replacing the old one.
    void set_pattern(std::string pattern, pattern_time_type time_type = pattern_time_type::local);

    // flush functions
    void flush();
    void flush_on(level::level_enum log_level);
    [[nodiscard]] level::level_enum flush_level() const;

    // sinks
    [[nodiscard]] const std::vector<sink_ptr> &sinks() const;

    [[nodiscard]] std::vector<sink_ptr> &sinks();

    // error handler
    void set_error_handler(err_handler);

    // create new logger with same sinks and configuration.
    virtual std::shared_ptr<logger> clone(std::string logger_name);

protected:
    std::string name_;
    std::vector<sink_ptr> sinks_;
    spdlog::level_t level_{level::info};
    spdlog::level_t flush_level_{level::off};
    err_handler custom_err_handler_{nullptr};

    // common implementation for after templated public api has been resolved to format string and args
    template<typename... Args>
    void log_with_format_(source_loc loc, level::level_enum lvl, string_view_t fmt, Args &&...args)
    {
        if (!should_log(lvl))
        {
            return;
        }
        SPDLOG_TRY
        {
            memory_buf_t buf;
#ifdef SPDLOG_USE_STD_FORMAT
            fmt_lib::vformat_to(std::back_inserter(buf), fmt, fmt_lib::make_format_args(args...));
#else
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
#endif
            sink_it_(details::log_msg(loc, name_, lvl, string_view_t(buf.data(), buf.size())));
        }
        SPDLOG_LOGGER_CATCH(loc)
    }

    // log the given message (if the given log level is high enough)
    virtual void sink_it_(const details::log_msg &msg)
    {
        assert (should_log(msg.level));
        for (auto &sink : sinks_)
        {
            if (sink->should_log(msg.level))
            {
                SPDLOG_TRY
                {
                    sink->log(msg);
                }
                SPDLOG_LOGGER_CATCH(msg.source)
            }
        }

        if (should_flush_(msg))
        {
            flush_();
        }
    }
    virtual void flush_();
    bool should_flush_(const details::log_msg &msg);

    // handle errors during logging.
    // default handler prints the error to stderr at max rate of 1 message/sec.
    void err_handler_(const std::string &msg);
};

void swap(logger &a, logger &b);

} // namespace spdlog

#ifdef SPDLOG_HEADER_ONLY
#    include "logger-inl.h"
#endif
