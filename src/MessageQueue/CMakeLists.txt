add_library(MessageQueue MQRouter.cpp)

find_package(cppzmq CONFIG REQUIRED)

target_link_libraries(MessageQueue cppzmq-static)
