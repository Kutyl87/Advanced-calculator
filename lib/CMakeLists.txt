cmake_minimum_required(VERSION 3.0)
project(Characters_lib)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_FILES Characters.cpp)
set(HEADER_FILES Characters.h)
add_library(Characters_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
if(!MSVC)
  target_compile_options(Characters_lib PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
target_include_directories(Characters_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})