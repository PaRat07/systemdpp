add_executable(systemdpp-tests test_config_load.cpp)

target_link_libraries(systemdpp-tests PRIVATE gtest gtest_main config-loader reflectcpp::reflectcpp)

add_test(NAME systemdpp COMMAND $<TARGET_FILE:systemdpp-tests>)

set_tests_properties(systemdpp PROPERTIES
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

