#pragma once

#include <stdexcept>

#include <curl/curl.h>

namespace curl_raii
{
    class CurlGlobalPolicy
    {
    public:
        static void ensure_initialized()
        {
            static const bool initialized = []() {
                if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK)
                {
                    throw std::runtime_error("curl_global_init failed");
                }
                return true;
            }();
            (void) initialized;
        }

        static void cleanup()
        {
            curl_global_cleanup();
        }
    };
};
