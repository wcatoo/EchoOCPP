add_library(CenterSystem App/CenterSystem/CenterSystem.cpp)
message(${CMAKE_SOURCE_DIR}/src/WebsocketComponent)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/WebsocketComponent)


target_link_libraries(CenterSystem PRIVATE WebsocketServer)