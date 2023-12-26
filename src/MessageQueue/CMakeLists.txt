add_library(MessageQueue MQRouter.cpp protobufMessage.pb.cc)

find_package(cppzmq CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

target_link_libraries(MessageQueue PUBLIC cppzmq-static protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
