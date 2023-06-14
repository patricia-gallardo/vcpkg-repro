add_executable(ms_pacman main.cpp)
target_link_libraries(ms_pacman PUBLIC lib_ms_pacman)

set_target_properties(ms_pacman
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
