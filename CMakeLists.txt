cmake_minimum_required(VERSION 3.16)
project(path_tracer
        VERSION 1.0
        LANGUAGES CXX)


# ============================================================================
# Configure dependencies
# ============================================================================
include(cmake/Config.cmake)


# compilation options for faster result and better practive
add_compile_options(
#        -fmodules-ts # enables modules g++-11 only
        -O3
        -march=native # for SSE and AVX
        -mno-fma # fused multiply add
        -Wall # enables most compiler's warning messages
        -Wextra # enables more compiler's warning messages
#        -Werror # Make all warnings into errors. CANNOT  USE THAT WITH c++20 because Eigen 3.4.0 is not c++20 compliant
)

# ============================================================================
# Create path_tracer_lib library
# ============================================================================
#include_directories(
#        include
#)

add_library(path_tracer_lib
        src/utils.cpp
        src/camera.cpp
        src/hittable_list.cpp
        src/sphere.cpp
        src/materials/lambertian.cpp
        src/materials/dielectric.cpp
        src/materials/metal.cpp
        )

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(path_tracer_lib PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(
        path_tracer_lib
        PRIVATE stb Threads::Threads tinyobjloader tinyexr
        PUBLIC fmt::fmt nlohmann_json filesystem pcg32 cli11 linalg spdlog::spdlog
)


# Windows' math include does not define constants by default. Set this definition so it does. Also
# set NOMINMAX so the min and max functions are not overwritten with macros.
if(MSVC)
target_compile_definitions(path_tracer_lib PUBLIC -D_USE_MATH_DEFINES -DNOMINMAX -DWIN32_LEAN_AND_MEAN)
endif()


target_include_directories(path_tracer_lib
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# https://github.com/bshoshany/thread-pool/blob/master/thread_pool.hpp


# ============================================================================
# Create executables
# ============================================================================
add_executable(RT1_0_first_image src/RT1/RT1_0_first_image.cpp)
target_link_libraries(RT1_0_first_image PRIVATE path_tracer_lib)


add_executable(RT1_1_empty_backgound src/RT1/RT1_1_empty_backgound.cpp)
target_link_libraries(RT1_1_empty_backgound PRIVATE path_tracer_lib)


add_executable(RT1_2_first_sphere src/RT1/RT1_2_first_sphere.cpp)
target_link_libraries(RT1_2_first_sphere PRIVATE path_tracer_lib)


add_executable(RT1_3_sphere_with_normals src/RT1/RT1_3_sphere_with_normals.cpp)
target_link_libraries(RT1_3_sphere_with_normals PRIVATE path_tracer_lib)


add_executable(RT1_4_sphere_with_normals_with_ground src/RT1/RT1_4_sphere_with_normals_with_ground.cpp)
target_link_libraries(RT1_4_sphere_with_normals_with_ground PRIVATE path_tracer_lib)


add_executable(RT1_5_antialiasing src/RT1/RT1_5_antialiasing.cpp)
target_link_libraries(RT1_5_antialiasing PRIVATE path_tracer_lib)


add_executable(RT1_6_diffuse src/RT1/RT1_6_diffuse.cpp)
target_link_libraries(RT1_6_diffuse PRIVATE path_tracer_lib)

add_executable(RT1_7_metal src/RT1/RT1_7_metal.cpp)
target_link_libraries(RT1_7_metal PRIVATE path_tracer_lib)

add_executable(RT1_8_dielectrics src/RT1/RT1_8_dielectrics.cpp)
target_link_libraries(RT1_8_dielectrics PRIVATE path_tracer_lib)

add_executable(RT1_9_camera src/RT1/RT1_9_camera.cpp)
target_link_libraries(RT1_9_camera PRIVATE path_tracer_lib)


# ============================================================================
# Create an installable target
#
# this allows users to install and find darts_lib via `find_package()`.
# ============================================================================

string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
        NAME path_tracer_lib
        VERSION ${PROJECT_VERSION}
        NAMESPACE ${PROJECT_NAME}
        BINARY_DIR ${PROJECT_BINARY_DIR}
        INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
        INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
        VERSION_HEADER "${VERSION_HEADER_LOCATION}"
        COMPATIBILITY SameMajorVersion
        DEPENDENCIES ""
)

# add the documentation/website subproject
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/documentation ${CMAKE_BINARY_DIR}/documentation)
