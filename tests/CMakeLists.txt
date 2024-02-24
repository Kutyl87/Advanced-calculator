cmake_minimum_required(VERSION 3.16.0)
project(Characters_tests)
set(SOURCE_FILES CharactersTests.cpp)
Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0)
# w nowszych cmake (> 3.15) starczyłoby tylko:  FetchContent_MakeAvailable(Catch2)
FetchContent_GetProperties(Catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory("${catch2_SOURCE_DIR}"
                     "${catch2_BINARY_DIR}")
endif()

add_executable(exec ${SOURCE_FILES})
set_target_properties(exec
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
if(MSVC)
  # target_compile_options(exec PRIVATE -Wall /W4 -pedantic -Werror)
else()
  target_compile_options(exec PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
target_include_directories(exec PUBLIC ../lib)
target_link_directories(exec PUBLIC ../lib/lib)
target_link_libraries(exec Characters_lib)
target_link_libraries(exec Catch2::Catch2WithMain)
