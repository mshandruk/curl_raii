#pragma once

#include <fstream>
#include <string>

namespace curl_raii
{
    inline size_t write_to_string(const void *contents, size_t size, size_t nmemb, void *userp)
    {
        static_cast<std::string *>(userp)->append(static_cast<const char *>(contents), size * nmemb);
        return size * nmemb;
    }

    inline size_t write_to_file(const void *contents, size_t size, size_t nmemb, void *userp)
    {
        auto *ofs = static_cast<std::ofstream *>(userp);
        ofs->write(static_cast<const char *>(contents), static_cast<std::streamsize>(size * nmemb));
        return size * nmemb;
    }
}
