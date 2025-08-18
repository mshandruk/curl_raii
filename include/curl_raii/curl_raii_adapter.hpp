#pragma once

#include <curl/curl.h>

namespace curl_raii
{
    class CurlRAIIAdapter
    {
    public:
        virtual ~CurlRAIIAdapter() = default;

        [[nodiscard]] virtual CURL *get() const = 0;
    };
}
