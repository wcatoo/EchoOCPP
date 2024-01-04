add_library(
        ChargePointOCPP201
        STATIC
        OCPPManager.cpp
        OCPPRouter.cpp
)
find_package(cppzmq CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

target_include_directories(
        ChargePointOCPP201
        PUBLIC
        ../DataType
        ../Message
)
target_link_libraries(
        ChargePointOCPP201
        PUBLIC
        MessageQueueDealer
        OCPP201Utilies
)
