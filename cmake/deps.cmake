include(cmake/get_cpm.cmake)


CPMAddPackage("gh:marzer/tomlplusplus#v3.4.0")

set(REFLECTCPP_JSON OFF)
set(REFLECTCPP_TOML ON)
set(REFLECTCPP_USE_STD_EXPECTED ON)

CPMAddPackage("gh:getml/reflect-cpp#v0.24.0")
