cmake_minimum_required(VERSION 3.15)
include(FetchContent)

project(anton_math)

# Add anton_types
FetchContent_Declare(
    anton_types
    GIT_REPOSITORY https://github.com/kociap/anton_types.git
    GIT_TAG 77cd0eb15dd4bd0e7796f4e7acac59ab7713c0a0
)
FetchContent_MakeAvailable(anton_types)

add_library(anton_math
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/math.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/mat2.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/mat3.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/mat4.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/primitives.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/quat.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/transform.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/vec2.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/vec3.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/vec4.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/mat2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/mat3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/mat4.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/math.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/quat.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/transform.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/vec2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/vec3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/vec4.cpp"
)
target_link_libraries(anton_math PUBLIC anton_types)
target_include_directories(anton_math PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/public" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/private")
set_target_properties(anton_math
    PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS TRUE
    CXX_STANDARD 17
    CXX_EXTENSIONS FALSE
)

# Detect MSVC as it requires different intrinsics.
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(ANTON_COMPILER_MSVC ON)
else()
    set(ANTON_COMPILER_MSVC OFF)
endif()

target_compile_definitions(anton_math
    PUBLIC
    ANTON_COMPILER_MSVC=$<BOOL:${ANTON_COMPILER_MSVC}>
)
