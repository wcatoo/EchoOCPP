add_library(
        OCPP201Utilies
        STATIC
        Helper.cpp
)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(nlohmann_json_schema_validator REQUIRED)


target_link_libraries(OCPP201Utilies
        PRIVATE
        nlohmann_json::nlohmann_json
        magic_enum::magic_enum
        nlohmann_json_schema_validator
)
#target_link_libraries(
#        OCPP201Utilies
#)

#target_link_libraries(
#        ChargePointOCPP201
#        PRIVATE
#        cppzmq-static
#        protobuf::libprotoc
#        protobuf::libprotobuf
#        protobuf::libprotobuf-lite
#)
