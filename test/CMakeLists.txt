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
add_executable(OCPP201DatatypesTest
        OCPP201DatatypesTest.cpp
        ../src/OCPP/201/DataType/Datatypes.hpp)
target_link_libraries(
        OCPP201DatatypesTest
        PRIVATE
        GTest::gtest_main
        ChargePointOCPP201
#        OCPP201Utilies
)


add_executable(OCPP201ChargePointTest OCPP201ChargePointTest.cpp
        ../src/OCPP/201/Message/MessageRespone.hpp)
target_link_libraries(
        OCPP201ChargePointTest
        PRIVATE
        GTest::gtest_main
        ChargePointOCPP201
#        OCPP201Utilies


)
