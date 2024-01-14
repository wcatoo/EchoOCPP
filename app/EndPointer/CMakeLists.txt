add_library(AppChargePoint STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/CoreSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ChargePoint.cpp
)

target_include_directories(AppChargePoint PRIVATE
        ${CMAKE_SOURCE_DIR}/src/MessageQueue
)
target_link_libraries(AppChargePoint WebsocketClient MessageQueueDealer MessageQueueRouter ChargePointOCPP201)
