cmake_minimum_required(VERSION 3.16)
project(graphics)

set(CMAKE_CXX_STANDARD 20)

include(cmake/FetchDependencies.cmake)

add_compile_options(
        -fmodules-ts # enables modules g++-11 only
        -O3
        -march=native # for SSE and AVX
        -mno-fma # fused multiply add
        -Wall # enables most compiler's warning messages
        -Wextra # enables more compiler's warning messages
        -Werror # Make all warnings into errors. CANNOT  USE THAT WITH c++20 because Eigen 3.4.0 is not c++20 compliant
)

# for windows
SET( EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}" )
SET( CMAKE_MODULE_PATH "$ENV{EIGEN3_DIR}" )

find_package(Eigen3 REQUIRED)

include_directories(
        include
        ${EIGEN3_INCLUDE_DIR}
)

add_executable(graphics
        main.cpp
        )

add_executable(first_image
        src/utils.cpp
        first_image.cpp
        )
target_link_libraries(first_image PRIVATE fmt::fmt-header-only)


add_executable(empty_backgound
        src/utils.cpp
        empty_backgound.cpp
        )
target_link_libraries(empty_backgound PRIVATE fmt::fmt-header-only)


add_executable(first_sphere
        src/utils.cpp
        first_sphere.cpp
        )
target_link_libraries(first_sphere PRIVATE fmt::fmt-header-only)


add_executable(sphere_with_normals
        src/utils.cpp
        sphere_with_normals.cpp
        )
target_link_libraries(sphere_with_normals PRIVATE fmt::fmt-header-only)


add_executable(sphere_with_normals_with_ground
        src/utils.cpp
        src/hittable_list.cpp
        src/sphere.cpp
        sphere_with_normals_with_ground.cpp
        )
target_link_libraries(sphere_with_normals_with_ground PRIVATE fmt::fmt-header-only)


add_executable(antialiasing
        src/camera.cpp
        src/hittable_list.cpp
        src/sphere.cpp
        src/utils.cpp
        antialiasing.cpp
        )
target_link_libraries(antialiasing PRIVATE fmt::fmt-header-only)

