#include <iostream>
#include <string>

#include <curl_raii/curl_easy_session.hpp>
#include <curl_raii/utils.hpp>

using namespace curl_raii;

int main()
{
    CurlRAIIAdapterImpl adapter;
    CurlEasySession session(adapter);
    std::string url = "https://example.com/file.txt";
    std::string response;
    session.set_url(url);
    session.set_option(CURLOPT_WRITEFUNCTION, write_to_string);
    session.set_option(CURLOPT_WRITEDATA, &response);
    session.perform();
    std::cout << response << std::endl;
    return 0;
}
