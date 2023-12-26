add_library(WebsocketServer Server/WebsocketServer.cpp)
add_library(WebsocketClient Client/WebsocketClient.cpp)

find_package(websocketpp CONFIG REQUIRED)

target_include_directories(WebsocketServer PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(WebsocketServer PUBLIC websocketpp::websocketpp)

target_include_directories(WebsocketClient PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(WebsocketClient PUBLIC websocketpp::websocketpp)

