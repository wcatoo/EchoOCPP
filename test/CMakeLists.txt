enable_testing()
find_package(GTest CONFIG REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


#add_executable(LogComponentTest LogComponentTest.cpp)
#add_executable(DatatypesTest DatatypesTest.cpp)


#find_package(nlohmann_json CONFIG REQUIRED)
#find_package(magic_enum CONFIG REQUIRED)

#target_include_directories(LogComponentTest PRIVATE ${CMAKE_SOURCE_DIR}/src)
#target_link_libraries(
#        LogComponentTest
#        GTest::gtest_main
#        LogComponent
#)
#
#
#
#
#target_include_directories(DatatypesTest PRIVATE ${CMAKE_SOURCE_DIR}/src)
#target_link_libraries(
#        DatatypesTest
#        GTest::gtest_main
#        nlohmann_json::nlohmann_json
#        magic_enum::magic_enum
#)


add_executable(OCPP201ChargePointTest OCPP201ChargePointTest.cpp
        ../src/OCPP201/Message/MessageRespone.hpp)
target_link_libraries(
        OCPP201ChargePointTest
        PRIVATE
        GTest::gtest_main
        ChargePointOCPP201
        OCPP201Utilies


)
