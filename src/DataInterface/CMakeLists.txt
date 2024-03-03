add_library(
        DataInterface
        STATIC
        DeviceDataInterface.cpp
)


target_include_directories(
        DataInterface
        PUBLIC
        ../
)

target_link_libraries(
        DataInterface
        PUBLIC
        MessageQueueDealer
)