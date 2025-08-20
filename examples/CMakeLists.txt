cmake_minimum_required(VERSION 3.16)
project(curl_raii_example)

add_executable(http_get_example http_get.cpp)
add_executable(download_file_example download_file.cpp)

target_link_libraries(http_get_example PRIVATE curl_raii)
target_link_libraries(download_file_example PRIVATE curl_raii)
