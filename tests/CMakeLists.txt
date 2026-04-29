add_executable(systemdpp-tests test_config_load.cpp)

target_link_libraries(systemdpp-tests PRIVATE gtest gtest_main config-loader reflectcpp::reflectcpp)
