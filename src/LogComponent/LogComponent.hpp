#ifndef ECHOOCPP_LOGCOMPONENT_HPP
#define ECHOOCPP_LOGCOMPONENT_HPP


#include "ILogComponent.hpp"
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Components {
    class LogComponent : public ILogComponent{
    public:
        void init(const std::string &tPath) override;
        bool createLogName(const std::string &tLogname) override;
        void info(const std::string &tMessage, const std::string &tLogName) override;

        void error(const std::string &tMessage, const std::string &tLogName)override;
    private:
        void log(spdlog::level::level_enum tLevel, const std::string &tLogName, std::string_view tMessage);
        // file sink to save logs into file
        std::shared_ptr<spdlog::sinks::daily_file_sink_mt> mFileSink{nullptr};
        // console sink to print logs into console
        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> mConsoleSink{nullptr};
        std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> mLogPool{};
    };

}


#endif//ECHOOCPP_LOGCOMPONENT_HPP
