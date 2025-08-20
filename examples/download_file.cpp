#include <fstream>

#include <curl_raii/curl_easy_session.hpp>
#include <curl_raii/utils.hpp>

using namespace curl_raii;

int main()
{
    CurlRAIIAdapterImpl adapter;
    CurlEasySession session(adapter);
    std::string url = "https://example.com/file.txt";

    std::ofstream out("downloaded_file.txt", std::ios::binary);
    session.set_url(url);
    session.set_option(CURLOPT_WRITEFUNCTION, write_to_file);
    session.set_option(CURLOPT_WRITEDATA, &out);
    session.perform();
    out.close();

    return 0;
}
