cmake_minimum_required(VERSION 3.10)
project(CharacterApp)
# include_directories(../tests)
# include_directories(../lib)
# set(SOURCE_FILES main.cpp)
# add_executable(CharacterApp ${SOURCE_FILES})
add_executable(CharacterApp main.cpp)
set_target_properties(CharacterApp
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
include_directories(../lib)
if(!MSVC)
  target_compile_options(CharacterApp PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
target_link_directories(CharacterApp PUBLIC ../lib/lib)
target_link_libraries(CharacterApp PUBLIC Characters_lib)