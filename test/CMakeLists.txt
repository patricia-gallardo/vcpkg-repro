find_package(Catch2 REQUIRED)

file(GLOB unit_tests_sources CONFIGURE_DEPENDS "unit_tests/*.cpp")
add_executable(ms_pacman_unit_tests ${unit_tests_sources})
target_link_libraries(ms_pacman_unit_tests Catch2::Catch2WithMain  lib_ms_pacman)

include(Catch)
catch_discover_tests(ms_pacman_unit_tests)
