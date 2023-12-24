cmake_minimum_required(VERSION 3.20)
project(EchoOCPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(client client.cpp)
add_executable(server server.cpp)


add_subdirectory(src)
add_subdirectory(test)


#find_package(nlohmann_json CONFIG REQUIRED)



#target_link_libraries(server PRIVATE nlohmann_json nlohmann_json::nlohmann_json )
target_link_libraries(server PRIVATE MessageQueue WebsocketServer)
#target_link_libraries(client PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(client PRIVATE MessageQueue WebsocketClient)



