cmake_minimum_required(VERSION 3.20)
project(EchoOCPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(client client.cpp)
add_executable(server server.cpp)


add_subdirectory(src)
add_subdirectory(test)


find_package(nlohmann_json CONFIG REQUIRED)
find_package(cppzmq CONFIG REQUIRED)



#link_directories(${CMAKE_SOURCE_DIR}/lib)
#target_link_libraries(Echo PUBLIC ${CMAKE_SOURCE_DIR}/lib/libuSockets)
#find_package(protobuf CONFIG REQUIRED)
#target_link_libraries(Echo PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
#target_link_libraries(Echo PRIVATE LogComponent)

#target_include_directories(Echo PRIVATE ${nlohmann_json_INCLUDE_DIRS})
target_link_libraries(server PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(server PRIVATE MessageQueue)

target_link_libraries(client PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(client PRIVATE cppzmq cppzmq-static)



