cmake_minimum_required(VERSION 3.19)

project("TerrariaClone")
set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "includes/*.hpp")
add_executable(TerrariaClone ${SOURCES})
include_directories(TerrariaClone PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes/" "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/")
target_link_libraries(TerrariaClone PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libs/libSDL3.so.0.5.0" "${CMAKE_CURRENT_SOURCE_DIR}/libs/libSDL3_image.so.0.5.0")
