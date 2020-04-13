cmake_minimum_required(VERSION 3.13)

project(anton_math)

add_library(anton_math
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/math.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/matrix2.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/matrix3.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/matrix4.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/quaternion.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/transform.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/vector2.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/vector3.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/math/vector4.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/vector.cpp"
)

target_include_directories(anton_math PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/public")

set_target_properties(anton_math 
    PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS TRUE
    CXX_STANDARD 17
    CXX_EXTENSIONS FALSE
)
