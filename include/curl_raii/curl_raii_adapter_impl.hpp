#pragma once

#include <curl/curl.h>

#include "curl_raii_adapter.hpp"
#include "curl_raii.hpp"

namespace curl_raii
{
    class CurlRAIIAdapterImpl final : public CurlRAIIAdapter
    {
    public:
        ~CurlRAIIAdapterImpl() override = default;

        [[nodiscard]] CURL *get() const override;

    private:
        CurlRAII<> curl_raii_;
    };
}

#include "curl_raii_adapter_impl.inl"
