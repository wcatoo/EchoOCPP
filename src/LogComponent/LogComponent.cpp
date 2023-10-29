#ifndef ECHOOCPP_LOGCOMPONENT_CPP
#define ECHOOCPP_LOGCOMPONENT_CPP


#include "LogComponent.hpp"
#include <spdlog/async.h>

namespace Components {
/**
 * log component initializaion function
 * @param tDirPath the directory of saving logs
 */
void Components::LogComponent::init(const std::string &tDirPath) {
    spdlog::init_thread_pool(8192, 1);
    this->mFileSink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(tDirPath+ "/" + "ocpp.txt", 23, 59);
    this->mConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    this->createLogName("Core");
}
/**
 * create a name of special log e.g. [log test] this is a name of log test
 * @param tLogName
 * @return
 */
bool LogComponent::createLogName(const std::string &tLogName) {
    if (this->mFileSink == nullptr || this->mConsoleSink == nullptr) {
        return false;
    }

    if (this->mLogPool.find(tLogName) == mLogPool.end()) {
        std::vector<spdlog::sink_ptr> sinks {this->mFileSink, this->mConsoleSink};
        this->mLogPool[tLogName] = std::make_shared<spdlog::async_logger>(tLogName, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        this->mLogPool[tLogName]->set_level(spdlog::level::info);
        spdlog::register_logger(this->mLogPool[tLogName]);
        return true;
    }
    return false;
}

void LogComponent::info(const std::string &tMessage, const std::string &tLogName){
    this->log(spdlog::level::info, tLogName, tMessage);
}
void LogComponent::error(const std::string &tMessage, const std::string &tLogName) {
    this->log(spdlog::level::err, tLogName, tMessage);
}

void LogComponent::log(spdlog::level::level_enum tLevel, const std::string &tLogName, std::string_view tMessage) {
    switch (tLevel) {
        case spdlog::level::info:
            this->mLogPool[tLogName]->info(tMessage);
            break;
        case spdlog::level::err:
            this->mLogPool[tLogName]->error(tMessage);
            break;
        case spdlog::level::debug:
            this->mLogPool[tLogName]->set_level(spdlog::level::debug);
            this->mLogPool[tLogName]->debug(tMessage);
            break;
        case spdlog::level::warn:
            this->mLogPool[tLogName]->warn(tMessage);
            break;
        case spdlog::level::trace:
            this->mLogPool[tLogName]->set_level(spdlog::level::trace);
            this->mLogPool[tLogName]->trace(tMessage);
            break;
        case spdlog::level::critical:
            this->mLogPool[tLogName]->critical(tMessage);
            break;
        default:
            break;
    }
    this->mLogPool[tLogName]->flush_on(tLevel);

}

}


#endif//ECHOOCPP_LOGCOMPONENT_CPP

