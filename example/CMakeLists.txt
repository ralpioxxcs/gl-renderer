set(BIN_NAME ${PROJECT_NAME}_launcher)
add_executable(${BIN_NAME} main.cpp)

target_link_libraries(${BIN_NAME} PUBLIC ${PROJECT_NAME})
target_include_directories(${BIN_NAME} PUBLIC ${CMAKE_PROJECT_INCLUDE})