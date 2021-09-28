cmake_minimum_required(VERSION 3.1)
project(opengl_cpp_template LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# configure build directory
set(PROJECT_OUTPUT_BASE_DIR ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR})
set(PROJECT_INCLUDE_DIR ${PROJECT_OUTPUT_BASE_DIR}/include)
set(PROJECT_RUNTIME_OUTPUT_DIR ${PROJECT_OUTPUT_BASE_DIR}/bin)
set(PROJECT_LIBRARY_OUTPUT_DIR ${PROJECT_OUTPUT_BASE_DIR}/lib)
set(PROJECT_THIRED_PARTY_DIR ${PROJECT_OUTPUT_BASE_DIR}/third-party)
file(MAKE_DIRECTORY ${PROJECT_INCLUDE_DIR} ${PROJECT_THIRED_PARTY_DIR})

# add_library(${PROJECT_NAME} "")
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# find & linking openGL libraries
include(Dependency.cmake)
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} ${DEP_LIBS} ${CMAKE_DL_LIBS})
add_dependencies(${PROJECT_NAME} ${DEP_LIST})

# sources
file(GLOB sources src/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${sources})