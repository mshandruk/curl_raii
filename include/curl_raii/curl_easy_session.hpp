#pragma once

#include "curl/curl.h"

#include "curl_raii/curl_raii.hpp"

namespace curl_raii
{
    template<typename GlobalPolicy = CurlGlobalInitPolicy>
    class CurlEasySession
    {
    public:
        explicit CurlEasySession(CurlRAII<> curl_raii = CurlRAII<>{});

        void perform() const;

        template<typename Value>
        void set_option(const CURLoption &option, Value value);

        void set_url(const std::string &url);

    private:
        template<typename Value>
        void set_option_impl(const CURLoption &option, Value value);

        CurlRAII<> curl_raii_;
        CURL *handle_{};
    };
}


#include "curl_easy_session.inl"
