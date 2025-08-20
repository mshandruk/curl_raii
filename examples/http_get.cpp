#include <iostream>
#include <string>

#include <curl_raii/curl_easy_session.hpp>

static size_t write_to_string(const void *contents, size_t size, size_t nmemb, void *userp)
{
    static_cast<std::string *>(userp)->append(static_cast<const char *>(contents), size * nmemb);
    return size * nmemb;
}

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
