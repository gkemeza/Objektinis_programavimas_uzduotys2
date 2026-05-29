cmake_minimum_required(VERSION 3.14)  # 3.14 required for FetchContent_MakeAvailable
project(Darbas_su_studentais)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default to Release only if not set externally (e.g. cmake -DCMAKE_BUILD_TYPE=Debug)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# ── Shared library: all src/*.cpp EXCEPT main.cpp ─────────────────────────────
file(GLOB LIB_SOURCES "src/*.cpp")
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

add_library(student_lib ${LIB_SOURCES})
target_include_directories(student_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# ── Main executable ───────────────────────────────────────────────────────────
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE student_lib)

# ── Google Test via FetchContent ──────────────────────────────────────────────
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # required on Windows, harmless elsewhere
FetchContent_MakeAvailable(googletest)

# ── Test executable ───────────────────────────────────────────────────────────
enable_testing()

file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(StudentTests ${TEST_SOURCES})
target_link_libraries(StudentTests PRIVATE student_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(StudentTests)