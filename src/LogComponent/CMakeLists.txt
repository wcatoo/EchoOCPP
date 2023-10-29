add_library(LogComponent LogComponent.cpp)

#find_package(spdlog REQUIRED)
target_include_directories(LogComponent PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(LogComponent PUBLIC ${CMAKE_SOURCE_DIR}/third_library)


