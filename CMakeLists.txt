cmake_minimum_required(VERSION 3.20)
project(EchoOCPP)

#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(app)


add_executable(client client.cpp
        src/OCPP/201/Message/MessageManager.hpp)
add_executable(server server.cpp)



target_link_libraries(server PRIVATE AppServer)
target_link_libraries(client
       PUBLIC
        AppChargePoint
)


