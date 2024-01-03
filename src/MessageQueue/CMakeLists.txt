add_library(MessageQueueRouter STATIC MQRouter.cpp protobufMessage.pb.cc)
add_library(MessageQueueDealer STATIC MQDealer.cpp protobufMessage.pb.cc)

find_package(cppzmq CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

target_link_libraries(MessageQueueRouter PUBLIC cppzmq-static protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
target_link_libraries(MessageQueueDealer PUBLIC cppzmq-static protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
