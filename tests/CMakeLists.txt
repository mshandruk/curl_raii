cmake_minimum_required(VERSION 3.16)
project(curl_raii_tests LANGUAGES CXX)

add_executable(${PROJECT_NAME}
        unit/curl_raii_test.cpp
        unit/curl_easy_test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        gtest_main
        gmock
        curl_raii
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
