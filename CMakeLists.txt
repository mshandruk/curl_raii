cmake_minimum_required(VERSION 3.16)
project(curl_raii)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME} INTERFACE
        curl
)

option(BUILD_TESTS "Build tests" OFF)
if (BUILD_TESTS)
    message(STATUS "Building tests")
    enable_testing()

    add_subdirectory(third_party/googletest)
    add_subdirectory(tests)
endif ()

option(BUILD_EXAMPLES "Build examples" OFF)
if (BUILD_EXAMPLES)
    message(STATUS "Building examples")
    add_subdirectory(example)
endif ()