#ifndef ECHOOCPP_ILOGCOMPONENT_HPP
#define ECHOOCPP_ILOGCOMPONENT_HPP

#include <string>
namespace Components {
    class ILogComponent {
    public:
        virtual void init(const std::string &tPath) = 0;
        virtual void info(const std::string &tMessage, const std::string &tLogName) = 0;
        virtual void error(const std::string &tMessage, const std::string &tLogName) = 0;
        virtual bool createLogName(const std::string &tLogname) = 0;
//        virtual bool removeLogName(const std::string &tLogname) = 0;
    };
}

#endif//ECHOOCPP_ILOGCOMPONENT_HPP
