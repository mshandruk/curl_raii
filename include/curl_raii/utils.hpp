#pragma once

namespace curl_raii
{
    size_t write_to_string(const void *contents, size_t size, size_t nmemb, void *userp);

    size_t write_to_file(const void *contents, size_t size, size_t nmemb, void *userp);
}

#include "utils.inl"
