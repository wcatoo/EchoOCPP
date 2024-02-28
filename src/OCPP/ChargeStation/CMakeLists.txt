add_library(
        ChargePointOCPP201
        STATIC
        OCPPManager.cpp
        ../201/Message/MessageManager.cpp
)
find_package(cppzmq CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

target_include_directories(
        ChargePointOCPP201
        PUBLIC
        ../
#        ../201/DataType
#        ../201/Message
)
target_link_libraries(
        ChargePointOCPP201
        PUBLIC
        MessageQueueDealer
        OCPP201Utilies
)
