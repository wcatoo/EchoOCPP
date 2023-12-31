add_library(MessageQueueRouter MQRouter.cpp protobufMessage.pb.cc)
add_library(MessageQueueDealer MQDealer.cpp protobufMessage.pb.cc)

find_package(cppzmq CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

target_link_libraries(MessageQueueRouter PRIVATE cppzmq-static protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
target_link_libraries(MessageQueueDealer PRIVATE cppzmq-static protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
