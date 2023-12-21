add_library(WebsocketServer Server/WebsocketServer.cpp)
add_library(WebsocketClient Client/WebsocketClient.cpp)
#add_library(WebsocketClient W)

#find_package(nlohmann_json CONFIG REQUIRED)


# uwebsockets library vcpkg cmake installing command
#find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")
#target_include_directories(WebsocketServer PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})
find_package(websocketpp CONFIG REQUIRED)

target_include_directories(WebsocketServer PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(WebsocketServer PRIVATE websocketpp::websocketpp)

target_include_directories(WebsocketClient PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(WebsocketClient PRIVATE websocketpp::websocketpp)
