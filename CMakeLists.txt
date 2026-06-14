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

add_library(commands src/commands.cpp)
target_link_libraries(commands PRIVATE reflectcpp config-loader)
target_include_directories(commands PUBLIC include)

add_executable(_systemdpp-daemon src/daemon.cpp src/daemon_endpoints.cpp)
target_link_libraries(_systemdpp-daemon PRIVATE commands httplib reflectcpp)


add_executable(systemdpp-ctl src/ctl.cpp)
target_include_directories(systemdpp-ctl PRIVATE include)
target_link_libraries(systemdpp-ctl PRIVATE httplib reflectcpp)

add_executable(journaldpp-daemon src/journald.cpp)
target_include_directories(journaldpp-daemon PRIVATE include)

add_executable(_systemdpp-run src/run_systemdpp.cpp)

include(GNUInstallDirs)

install(TARGETS systemdpp-ctl _systemdpp-daemon journaldpp-daemon _systemdpp-run
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES data/autocomplete/_systemdpp-ctl
        DESTINATION "${CMAKE_INSTALL_DATADIR}/zsh/site-functions"
)

find_program(ASCIIDOC asciidoctor)
if (ASCIIDOC)
    message(STATUS "ASCIIDOC FOUND: ${ASCIIDOC}")
    set(MANPAGE_DIR "${CMAKE_BINARY_DIR}/man")
    set(MANPAGE "${MANPAGE_DIR}/systemdpp-ctl.1")
    set(ASCIIDOC_MANPAGE "${CMAKE_SOURCE_DIR}/data/man/systemdpp-ctl.adoc")

    add_custom_command(
            OUTPUT "${MANPAGE}"
            COMMAND "${ASCIIDOC}" --backend=manpage --destination-dir=${MANPAGE_DIR} "${ASCIIDOC_MANPAGE}"
            DEPENDS "${ASCIIDOC_MANPAGE}"
            VERBATIM
    )

    add_custom_target(manpage ALL
            DEPENDS ${MANPAGE}
    )

    install(FILES "${MANPAGE}"
        DESTINATION "${CMAKE_INSTALL_MANDIR}/man1"
    )
else()
    message(STATUS "ASCIIDOC NOT FOUND, manpage wont be built and installed")
endif()


