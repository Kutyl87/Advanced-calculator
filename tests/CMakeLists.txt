cmake_minimum_required(VERSION 3.0)
project(Characters_tests)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_FILES CharactersTests.cpp)
Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.0.1)
# w nowszych cmake (> 3.15) starczyłoby tylko:  FetchContent_MakeAvailable(Catch2)
FetchContent_GetProperties(Catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory("${catch2_SOURCE_DIR}"
                     "${catch2_BINARY_DIR}")
endif()
add_executable(exec ${SOURCE_FILES})
target_include_directories(exec PUBLIC ../lib)
target_link_directories(exec PUBLIC ../lib/lib)
target_link_libraries(exec Characters_lib)
target_link_libraries(exec Catch2::Catch2WithMain)
