set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")
set(DEP_INCLUDE_DIRS ${EXTERNAL_DIR})
set(DEP_LIBRARIES "")
set(DEP_LISTS "")

if(!APPLE)
  find_package(OpenGL REQUIRED)
  list(APPEND DEP_LIBRARIES OpenGL)
endif()

# glfw3
find_package(glfw3 3.3 REQUIRED)
if(APPLE)
  list(APPEND DEP_INCLUDE_DIRS "/opt/homebrew/Cellar/glfw/3.3.6/include")
endif()
  list(APPEND DEP_LIBRARIES glfw)

# glad
add_library(glad STATIC "${EXTERNAL_DIR}/glad/src/glad.c")
target_include_directories(glad PRIVATE "${EXTERNAL_DIR}/glad/include")
list(APPEND DEP_INCLUDE_DIRS "${EXTERNAL_DIR}/glad/include")
list(APPEND DEP_LIBRARIES glad)
list(APPEND DEP_LISTS glad)

# imgui
add_library(imgui "")
file(GLOB imgui_sources "${EXTERNAL_DIR}/imgui/*.cpp")
target_sources(imgui PRIVATE ${imgui_sources})
target_include_directories(imgui PRIVATE ${IMGUI_DIR})
list(APPEND DEP_INCLUDE_DIRS "${EXTERNAL_DIR}/imgui/include")
list(APPEND DEP_LIBRARIES imgui)
list(APPEND DEP_LISTS imgui)

# stb
list(APPEND DEP_INCLUDE_DIRS "${EXTERNAL_DIR}/stb")

# glm
list(APPEND DEP_INCLUDE_DIRS "${EXTERNAL_DIR}/glm")

message(DEBUG "dependecies list : ${DEP_LISTS}")
message(DEBUG "dependecies include dirs : ${DEP_INCLUDE_DIRS}")
message(DEBUG "dependecies libraries : ${DEP_LIBRARIES}")
