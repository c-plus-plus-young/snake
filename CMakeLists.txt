cmake_minimum_required(VERSION 3.20)

project(SDL2Example VERSION 1.0 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 installed by vcpkg
find_package(SDL2 CONFIG REQUIRED)

# Create executable
add_executable(SDL2Example
    main.cpp
    print.cpp
)

# Link SDL2
target_link_libraries(SDL2Example PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
)

# Copy SDL2.dll to the output directory after building (Windows)
if(WIN32)
    add_custom_command(TARGET SDL2Example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SDL2::SDL2>"
        "$<TARGET_FILE_DIR:SDL2Example>"
    )
endif()