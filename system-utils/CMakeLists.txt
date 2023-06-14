find_package(SFML COMPONENTS window graphics CONFIG REQUIRED)

add_library(system-utils)

target_include_directories(system-utils PUBLIC .)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    target_sources(system-utils PRIVATE User.hpp Scaling.hpp Scaling.mm UserPosix.cpp)
    target_link_libraries(system-utils PUBLIC sfml-graphics)
elseif (WIN32)
    target_sources(system-utils PRIVATE User.hpp Scaling.hpp Scaling.cpp UserWin32.cpp)
    target_link_libraries(system-utils PUBLIC advapi32 sfml-graphics)
else ()
    target_sources(system-utils PRIVATE User.hpp Scaling.hpp Scaling.cpp UserPosix.cpp)
    target_link_libraries(system-utils PUBLIC sfml-graphics)
endif ()
