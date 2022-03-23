cmake_minimum_required(VERSION 3.1)
project(gl-renderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# configure build directory
set(PROJECT_OUTPUT_BASE_DIR ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR})
set(PROJECT_INCLUDE_DIR ${PROJECT_OUTPUT_BASE_DIR}/include)
set(PROJECT_RUNTIME_OUTPUT_DIR ${PROJECT_OUTPUT_BASE_DIR}/bin)
set(PROJECT_LIBRARY_OUTPUT_DIR ${PROJECT_OUTPUT_BASE_DIR}/lib)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(${PROJECT_NAME} SHARED "")

# find & linking openGL libraries
include(dependencies.cmake)
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})
add_dependencies(${PROJECT_NAME} ${DEP_LIST})

file(GLOB sources "src/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${sources})

# add_subdirectory(example)