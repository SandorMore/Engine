cmake_minimum_required(VERSION 3.10)
project (SasoEngine)
set(PROJECT_SOURCE_FILES
  source/main.cpp
)
include_directories(source)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})
add_subdirectory(thirdparty/glfw-3.4 "${CMAKE_CURRENT_BINARY_DIR}/glfw_build")
include_directories(thirdparty/glfw-3.4/include)
set(BUILD_UTILS OFF CACHE BOOL "utilities" FORCE)
add_subdirectory(thirdparty/glew/build/cmake "${CMAKE_CURRENT_BINARY_DIR}/glew_build")
include_directories(thirdparty/glew/include)
set_property(TARGET glew_s PROPERTY FOLDER GLEW)
set_property(TARGET glew   PROPERTY FOLDER GLEW)
target_link_libraries(${PROJECT_NAME} 
    glfw 
    glew_s
)
