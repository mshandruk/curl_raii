cmake_minimum_required(VERSION 3.16)
project(curl_raii VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME} INTERFACE curl)

option(CURL_RAII_BUILD_TESTS "Build tests" OFF)
if (CURL_RAII_BUILD_TESTS)
    message(STATUS "Building tests")
    enable_testing()

    add_subdirectory(third_party/googletest)
    add_subdirectory(tests)
endif ()

option(CURL_RAII_BUILD_EXAMPLES "Build examples" OFF)
if (CURL_RAII_BUILD_EXAMPLES)
    message(STATUS "Building examples")
    add_subdirectory(examples)
endif ()