cmake_minimum_required(VERSION 3.20)
project(sytemdpp)

set(CMAKE_CXX_STANDARD 23)

include(cmake/deps.cmake)

option(SYSTEMDPP_USE_LOCAL_PKGS OFF)
option(SYSTEMDPP_ENABLE_TESTING "enables testing" OFF)

if (SYSTEMDPP_ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

add_library(config-loader src/config_loader.cpp)
target_link_libraries(config-loader PRIVATE reflectcpp::reflectcpp)
target_include_directories(config-loader PUBLIC include)

add_executable(systemdpp src/main.cpp src/commands.cpp)
target_link_libraries(systemdpp PRIVATE config-loader)
target_include_directories(systemdpp PRIVATE include)
