find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

find_package(fmt REQUIRED)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(OpenGL REQUIRED COMPONENTS OpenGL GLX)
endif ()

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp" "*.hpp")
add_library(lib_ms_pacman ${sources})

target_include_directories(lib_ms_pacman PUBLIC include)
target_link_libraries(lib_ms_pacman PUBLIC system-utils fmt::fmt sfml-system sfml-network sfml-graphics sfml-window)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(lib_ms_pacman PUBLIC OpenGL::OpenGL OpenGL::GLX)
endif ()
