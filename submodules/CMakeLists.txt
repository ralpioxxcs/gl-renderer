set(_DEP_INCLUDE_DIRS "")
set(_DEP_LIBRARIES "")
set(_DEP_LISTS "" PARENT_SCOPE)

# if(!APPLE)
#   find_package(OpenGL REQUIRED)
#   list(APPEND _DEP_LIBRARIES OpenGL)
# endif()

# glfw3
# find_package(glfw3 3.3 REQUIRED)
# if(APPLE)
#   list(APPEND _DEP_INCLUDE_DIRS "/opt/homebrew/Cellar/glfw/3.3.6/include")
# endif()
#   list(APPEND _DEP_LIBRARIES glfw)

add_subdirectory(glfw)
list(APPEND _DEP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/glfw/include")
list(APPEND _DEP_LIBRARIES glfw)
list(APPEND _DEP_LISTS glfw)

# glad
add_subdirectory(glad)
list(APPEND _DEP_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/submodules/glad/include")
list(APPEND _DEP_LIBRARIES glad)
list(APPEND _DEP_LISTS glad)

# imgui
file(COPY 
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp 
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
file(COPY 
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp 
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

add_library(imgui 
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_impl_glfw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories(imgui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
target_include_directories(imgui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)
list(APPEND _DEP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
list(APPEND _DEP_LIBRARIES imgui)
list(APPEND _DEP_LISTS imgui)

# stb
list(APPEND _DEP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/stb")

# glm
list(APPEND _DEP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/glm")

# summary
message(DEBUG "dependecies list : ${_DEP_LISTS}")
message(DEBUG "dependecies include dirs : ${_DEP_INCLUDE_DIRS}")
message(DEBUG "dependecies libraries : ${_DEP_LIBRARIES}")

set(DEP_INCLUDE_DIRS ${_DEP_INCLUDE_DIRS} PARENT_SCOPE)
set(DEP_LIBRARIES ${_DEP_LIBRARIES} PARENT_SCOPE)
set(DEP_LISTS ${_DEP_LISTS} PARENT_SCOPE)