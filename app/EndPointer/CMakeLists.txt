add_library(AppClient STATIC ${CMAKE_CURRENT_SOURCE_DIR}/CoreSystem.cpp)

target_include_directories(AppClient PRIVATE
        ${CMAKE_SOURCE_DIR}/src/MessageQueue
)
target_link_libraries(AppClient WebsocketClient MessageQueueDealer MessageQueueRouter)
