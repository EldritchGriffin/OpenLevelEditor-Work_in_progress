cmake_minimum_required(VERSION 3.12)

project(OpenLevelEditor)

set(CMAKE_CXX_STANDARD 11)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources
set(SOURCES
    src/main.cpp
    src/scene.cpp
    src/sceneManager.cpp
)

# Headers
set(HEADERS
    include/raylib.h
    include/raymath.h
    include/rlgl.h
    include/rlights.h
    include/scene.hpp
    include/sceneManager.hpp
    include/raygui.h
    include/gameObject.hpp
    include/raygizmo.h
)

# Add compile options
add_compile_options(-Wno-deprecated-declarations -Wno-enum-compare)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Create executable
add_executable(OpenLevelEditor ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(OpenLevelEditor PRIVATE include)

# Find and link raylib
find_package(raylib QUIET)
if(raylib_FOUND)
    target_link_libraries(OpenLevelEditor raylib)
else()
    # Fallback: try to find raylib manually
    find_library(RAYLIB_LIBRARY
        NAMES raylib
        PATHS
        /usr/lib
        /usr/local/lib
        /opt/homebrew/lib
        /usr/lib/x86_64-linux-gnu
    )
    
    if(RAYLIB_LIBRARY)
        target_link_libraries(OpenLevelEditor ${RAYLIB_LIBRARY})
    else()
        # Check for local raylib.a in lib directory
        if(EXISTS ${PROJECT_SOURCE_DIR}/lib/libraylib.a)
            target_link_libraries(OpenLevelEditor ${PROJECT_SOURCE_DIR}/lib/libraylib.a)
        else()
            message(FATAL_ERROR "raylib library not found. Please install raylib or place libraylib.a in the lib/ directory.")
        endif()
    endif()
endif()

# Platform-specific libraries
if(UNIX AND NOT APPLE)
    # Linux-specific libraries
    target_link_libraries(OpenLevelEditor m pthread dl rt)
elseif(APPLE)
    # macOS-specific libraries
    target_link_libraries(OpenLevelEditor "-framework CoreVideo" "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(WIN32)
    # Windows-specific libraries
    target_link_libraries(OpenLevelEditor opengl32 gdi32 winmm)
endif()
