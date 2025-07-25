cmake_minimum_required(VERSION 3.16)
project(curl_raii_tests LANGUAGES CXX)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        curl_raii
        gtest_main
        gmock
)

target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
