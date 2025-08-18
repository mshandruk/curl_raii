#pragma once

#include <stdexcept>
#include <memory>

#include "curl_raii_adapter_impl.hpp"

namespace curl_raii
{
    inline CurlEasySession::CurlEasySession()
        : owned_adapter_{std::make_unique<CurlRAIIAdapterImpl>()}, curl_raii_adapter_{*owned_adapter_}
    {
        handle_ = curl_raii_adapter_.get();
    }

    inline CurlEasySession::CurlEasySession(CurlRAIIAdapter &curl_raii_adapter)
        : curl_raii_adapter_{curl_raii_adapter}
    {
        handle_ = curl_raii_adapter.get();
    }

    inline void CurlEasySession::perform() const
    {
        CURLcode code = curl_easy_perform(handle_);
        if (code != CURLE_OK)
        {
            throw std::runtime_error(
                "curl_easy_perform failed: " +
                std::string(curl_easy_strerror(code))
            );
        }
    }

    template<typename Value>
    void CurlEasySession::set_option(const CURLoption &option, Value value)
    {
        set_option_impl(option, value);
    }

    inline void CurlEasySession::set_url(const std::string &url)
    {
        set_option_impl(CURLOPT_URL, url.c_str());
    }

    template<typename Value>
    void CurlEasySession::set_option_impl(const CURLoption &option, Value value)
    {
        CURLcode code = curl_easy_setopt(handle_, option, value);

        if (code != CURLE_OK)
        {
            throw std::invalid_argument(
                "curl_easy_setopt failed: " +
                std::string(curl_easy_strerror(code))
            );
        }
    }
}
