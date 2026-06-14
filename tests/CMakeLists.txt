add_executable(systemdpp-tests test_config_load.cpp
        test_commands.cpp)

target_link_libraries(systemdpp-tests PRIVATE gtest gtest_main config-loader commands reflectcpp::reflectcpp)

add_test(NAME systemdpp COMMAND $<TARGET_FILE:systemdpp-tests>)

set_tests_properties(systemdpp PROPERTIES
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

