add_library(CenterSystem ${CMAKE_SOURCE_DIR}/src/App/CenterSystem/CoreSystem.cpp)
target_include_directories(CenterSystem PRIVATE ${CMAKE_SOURCE_DIR}/src)
find_package(websocketpp CONFIG REQUIRED)

target_link_libraries(CenterSystem PRIVATE websocketpp::websocketpp WebsocketServer)
