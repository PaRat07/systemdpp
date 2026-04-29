cmake_minimum_required(VERSION 3.20)
project(sytemdpp)

include(cmake/deps.cmake)

option(SYSTEMDPP_ENABLE_TESTING "enables testing" OFF)
option(SYSTEMDPP_ENABLE_ASAN "build ASAN" OFF)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")


if (SYSTEMDPP_ENABLE_TESTING)
    include(CTest)
    add_subdirectory(test)
endif()

add_executable(systemdpp ${SRC})

if (SYSTEMDPP_ENABLE_ASAN)
    target_compile_options(systemdpp PRIVATE
        -fsanitize=address
    )

    target_link_options(systemdpp PRIVATE
        -fsanitize=address
    )
endif()

set_target_properties(systemdpp PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 20
	CMAKE_CXX_STANDARD_REQUIRED ON
)

