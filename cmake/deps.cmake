include(cmake/get_cpm.cmake)


CPMAddPackage("gh:marzer/tomlplusplus#v3.4.0")

set(REFLECTCPP_JSON ON)
set(REFLECTCPP_TOML ON)
set(REFLECTCPP_USE_STD_EXPECTED ON)

CPMAddPackage("gh:getml/reflect-cpp#v0.24.0")


if (SYSTEMDPP_ENABLE_TESTING)
    if (SYSTEMDPP_USE_LOCAL_PKGS)
        find_package(GTest CONFIG)
    endif()

    if (NOT TARGET GTest::gtest)
        message(STATUS "GoogleTest not found, fetching via CPM...")
        CPMAddPackage("gh:google/googletest#v1.15.2")
    endif()
endif()

set(HTTPLIB_COMPILE ON)
CPMAddPackage("gh:yhirose/cpp-httplib#v0.43.0")
