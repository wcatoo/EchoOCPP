add_library(AppClient STATIC ${CMAKE_CURRENT_SOURCE_DIR}/CoreSystem.cpp)
target_link_libraries(AppClient WebsocketClient MessageQueueDealer)
