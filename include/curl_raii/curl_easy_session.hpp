#pragma once

#include <memory>
#include <string>

#include "curl/curl.h"

#include "curl_raii_adapter.hpp"

namespace curl_raii
{
    class CurlEasySession
    {
    public:
        CurlEasySession();

        explicit CurlEasySession(CurlRAIIAdapter &curl_raii_adapter);

        void perform() const;

        template<typename Value>
        void set_option(const CURLoption &option, Value value);

        void set_url(const std::string &url);

    private:
        template<typename Value>
        void set_option_impl(const CURLoption &option, Value value);

        std::unique_ptr<CurlRAIIAdapter> owned_adapter_;
        CurlRAIIAdapter &curl_raii_adapter_;
        CURL *handle_;
    };
}


#include "curl_easy_session.inl"
