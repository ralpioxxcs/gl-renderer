#----------------------------------------------------------------------
# DEP_INSTALL_DIR : build output directory (include, lib ...)
# DEP_INCLUDE_DIR : header files of dependencies
# DEP_LIB_DIR     : library directory of dependencies (*.so, *.a)
# DEP_LIST        : names of dependencies (for cmake build order)
#----------------------------------------------------------------------

# glfw, glad, glm, stb, imgui

include(ExternalProject)

set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)
set(DEP_LIST "")

# glfw
ExternalProject_Add(
    dep_glfw
    PREFIX ${PROJECT_BINARY_DIR}
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
    PREFIX ${PROJECT_BINARY_DIR}
    GIT_REPOSITORY "https://github.com/Dav1dde/glad"
    GIT_TAG "v0.1.34"
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLAD_INSTALL=ON
)
set(DEP_LIST ${DEP_LIST} dep_glad)
set(DEP_LIBS ${DEP_LIBS} glad)

# glm
ExternalProject_Add(
    dep_glm
    PREFIX ${PROJECT_BINARY_DIR}
    GIT_REPOSITORY "https://github.com/g-truc/glm"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_BINARY_DIR}/src/dep_glm/glm
        ${DEP_INSTALL_DIR}/include/glm
)
set(DEP_LIST ${DEP_LIST} dep_glm)

# stb
ExternalProject_Add(
    dep_stb
    PREFIX ${PROJECT_BINARY_DIR}
    GIT_REPOSITORY "https://github.com/nothings/stb"
    GIT_TAG "master"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ""
    TEST_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/src/dep_stb/stb_image.h
        ${DEP_INSTALL_DIR}/include/stb/stb_image.h
    )
set(DEP_LIST ${DEP_LIST} dep_stb)
    
# imgui
ExternalProject_Add(
    dep_imgui
    PREFIX ${PROJECT_BINARY_DIR}
    URL "https://github.com/ocornut/imgui/archive/refs/tags/v1.84.2.zip"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/src/dep_imgui/backends/imgui_impl_glfw.cpp
        ${PROJECT_BINARY_DIR}/src/dep_imgui
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/src/dep_imgui/backends/imgui_impl_glfw.h
        ${PROJECT_BINARY_DIR}/src/dep_imgui
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/src/dep_imgui/backends/imgui_impl_opengl3.cpp
        ${PROJECT_BINARY_DIR}/src/dep_imgui
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/src/dep_imgui/backends/imgui_impl_opengl3.h
        ${PROJECT_BINARY_DIR}/src/dep_imgui
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/src/dep_imgui/backends/imgui_impl_opengl3_loader.h
        ${PROJECT_BINARY_DIR}/src/dep_imgui
)
add_library(imgui
    ${PROJECT_BINARY_DIR}/src/dep_imgui/imgui_draw.cpp
    ${PROJECT_BINARY_DIR}/src/dep_imgui/imgui_tables.cpp
    ${PROJECT_BINARY_DIR}/src/dep_imgui/imgui_widgets.cpp
    ${PROJECT_BINARY_DIR}/src/dep_imgui/imgui.cpp
    ${PROJECT_BINARY_DIR}/src/dep_imgui/imgui_impl_glfw.cpp
    ${PROJECT_BINARY_DIR}/src/dep_imgui/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PRIVATE ${PROJECT_BINARY_DIR}/src/dep_imgui)
target_include_directories(imgui PRIVATE ${DEP_INCLUDE_DIR})
add_dependencies(imgui ${DEP_LIST})
set(DEP_INCLUDE_DIR ${DEP_INCLUDE_DIR} ${PROJECT_BINARY_DIR}/src/dep_imgui)
set(DEP_LIST ${DEP_LIST} imgui)
set(DEP_LIBS ${DEP_LIBS} imgui)