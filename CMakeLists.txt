cmake_minimum_required(VERSION 3.12)

project(SimpleLevelEditor)

set(CMAKE_CXX_STANDARD 11)


set(SOURCES
src/main.cpp
src/scene.cpp
src/sceneManager.cpp
)

set(HEADERS
include/raylib.h
include/raymath.h
include/rlgl.h
include/rlights.h
include/scene.hpp
include/sceneManager.hpp
include/raygui.h
# include/transform.hpp
include/gameObject.hpp
)
add_compile_options(-Wno-deprecated-declarations)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(SimpleLevelEditor ${SOURCES} ${HEADERS})

target_include_directories(SimpleLevelEditor PRIVATE include)

target_link_libraries(SimpleLevelEditor ${PROJECT_SOURCE_DIR}/lib/libraylib.a -lm -lpthread -ldl -lrt )
