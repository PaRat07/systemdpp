cmake_minimum_required(VERSION 3.20)
project(sytemdpp)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(deps)

option(SYSTEMDPP_USE_LOCAL_PKGS OFF)
option(SYSTEMDPP_ENABLE_TESTING "enables testing" OFF)

if (SYSTEMDPP_ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

add_library(config-loader src/config_loader.cpp)
target_link_libraries(config-loader PRIVATE reflectcpp)
target_include_directories(config-loader PUBLIC include)

add_executable(systemdpp-daemon src/daemon.cpp src/commands.cpp)
target_link_libraries(systemdpp-daemon PRIVATE config-loader httplib reflectcpp)
target_include_directories(systemdpp-daemon PRIVATE include)

add_executable(systemdpp-ctl src/ctl.cpp)
target_include_directories(systemdpp-ctl PRIVATE include)
target_link_libraries(systemdpp-ctl PRIVATE httplib reflectcpp)


