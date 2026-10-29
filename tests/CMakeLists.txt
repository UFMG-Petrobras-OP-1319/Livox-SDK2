add_executable(test_sdk_version_api sdk_version_api.cpp)
target_include_directories(test_sdk_version_api PRIVATE ../include)
target_link_libraries(test_sdk_version_api PRIVATE livox_lidar_sdk_shared)
add_test(NAME sdk_version_api COMMAND test_sdk_version_api)

add_executable(test_mid360s_config_parser mid360s_config_parser.cpp)
target_include_directories(test_mid360s_config_parser PRIVATE
  ../include
  ../sdk_core
  ../3rdparty
)
target_link_libraries(test_mid360s_config_parser PRIVATE livox_lidar_sdk_static)
add_test(NAME mid360s_config_parser COMMAND test_mid360s_config_parser
  ${CMAKE_SOURCE_DIR}/samples/livox_lidar_quick_start/mid360s_config.json 35)
add_test(NAME mid360_config_parser COMMAND test_mid360s_config_parser
  ${CMAKE_SOURCE_DIR}/samples/livox_lidar_quick_start/mid360_config.json 9)
