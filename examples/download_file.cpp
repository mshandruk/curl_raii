#include <fstream>

#include <curl_raii/curl_easy_session.hpp>


static size_t write_to_file(const void *contents, size_t size, size_t nmemb, void *userp)
{
    auto *ofs = static_cast<std::ofstream *>(userp);
    ofs->write(static_cast<const char *>(contents), static_cast<std::streamsize>(size * nmemb));
    return size * nmemb;
}

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
