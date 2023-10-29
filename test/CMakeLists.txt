find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(LogComponentTest LogComponentTest.cpp)

#add_subdirectory(src)

target_include_directories(LogComponentTest PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(
        LogComponentTest
        GTest::gtest_main
        LogComponent
)
