cmake_minimum_required(VERSION 3.10)
project(client LANGUAGES C CXX)

# Set C++ standard (change to 20 if you need)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory
include_directories(include)

# Source files
set(SOURCES
    main.cpp
    glad.c
)

# Create executable
add_executable(client ${SOURCES})

# Link libraries
target_link_libraries(client
    m          # math library
    GL         # OpenGL
    glfw       # GLFW
)

