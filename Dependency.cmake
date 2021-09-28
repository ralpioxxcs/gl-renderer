#----------------------------------------------------------------------
# DEP_INSTALL_DIR : build output directory (include, lib ...)
# DEP_INCLUDE_DIR : header files of dependencies
# DEP_LIB_DIR     : library files of dependencies (*.so, *.a)
# DEP_LIST        : names of dependencies (for cmake build order)
#----------------------------------------------------------------------

include(ExternalProject)

set(DEP_INSTALL_DIR ${PROJECT_THIRED_PARTY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# glfw
ExternalProject_Add(
    dep_glfw
    PREFIX ${PROJECT_THIRED_PARTY_DIR}
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
)
set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3)

# glad
ExternalProject_Add(
    dep_glad
    PREFIX ${PROJECT_THIRED_PARTY_DIR}
    GIT_REPOSITORY "https://github.com/Dav1dde/glad"
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLAD_INSTALL=ON
)
set(DEP_LIST ${DEP_LIST} dep_glad)
set(DEP_LIBS ${DEP_LIBS} glad)

# glm
ExternalProject_Add(
    dep_glm
    PREFIX ${PROJECT_THIRED_PARTY_DIR}
    GIT_REPOSITORY "https://github.com/g-truc/glm"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    TEST_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_THIRED_PARTY_DIR}/src/dep_glm/glm
        ${DEP_INSTALL_DIR}/include/glm
)
set(DEP_LIST ${DEP_LIST} dep_glm)
set(DEP_LIBS ${DEP_LIBS} glm)
    
# imgui
ExternalProject_Add(
    dep_imgui
    PREFIX ${PROJECT_THIRED_PARTY_DIR}
    URL "https://github.com/ocornut/imgui/archive/refs/tags/v1.84.2.zip"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_THIRED_PARTY_DIR}/src/dep_imgui/backends/imgui_impl_glfw.cpp
        ${PROJECT_THIRED_PARTY_DIR}/src/dep_imgui
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_THIRED_PARTY_DIR}/src/dep_imgui/backends/imgui_impl_glfw.h
        ${PROJECT_THIRED_PARTY_DIR}/src/dep_imgui
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_THIRED_PARTY_DIR}/src/dep_imgui/backends/imgui_impl_opengl3.cpp
        ${PROJECT_THIRED_PARTY_DIR}/src/dep_imgui
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_THIRED_PARTY_DIR}/src/dep_imgui/backends/imgui_impl_opengl3.h
        ${PROJECT_THIRED_PARTY_DIR}/src/dep_imgui
)
# add_library(imgui "")
# file(GLOB imgui_sources ${PROJECT_THIRED_PARTY_DIR}/src/dep_imgui/*.cpp)
# target_include_directories(imgui PRIVATE ${DEP_INCLUDE_DIR})
# target_sources(imgui PRIVATE ${imgui_sources})
# add_dependencies(imgui ${DEP_LIST})

# set(DEP_INCLUDE_DIR ${DEP_INCLUDE_DIR} ${PROJECT_THIRED_PARTY_DIR}/src/dep_imgui)
# set(DEP_LIST ${DEP_LIST} imgui)
# set(DEP_LIBS ${DEP_LIBS} imgui)
