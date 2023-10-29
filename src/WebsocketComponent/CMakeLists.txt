add_library(WebsocketServer WebsocketServerComponent.cpp)

find_package(nlohmann_json CONFIG REQUIRED)


# uwebsockets library vcpkg cmake installing command
find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")
target_include_directories(WebsocketServer PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})

target_include_directories(WebsocketServer PRIVATE ${CMAKE_SOURCE_DIR}/src)
