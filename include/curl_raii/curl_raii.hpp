#pragma once

#include <functional>

#include <curl/curl.h>

#include "policy.hpp"

namespace curl_raii
{
    template<typename GlobalPolicy = CurlGlobalPolicy>
    class CurlRAII
    {
    public:
        using InitFunc = std::function<CURL*()>;
        using CleanUpFunc = std::function<void(CURL *)>;

        explicit CurlRAII(
            InitFunc init = curl_easy_init,
            CleanUpFunc cleanup = curl_easy_cleanup
        );

        ~CurlRAII();

        CurlRAII(const CurlRAII &) = delete;

        CurlRAII &operator=(const CurlRAII &) = delete;

        CurlRAII(CurlRAII &&other) noexcept;

        CurlRAII &operator=(CurlRAII &&other) noexcept;

        [[nodiscard]] CURL *get() const;

    private:
        CURL *handle_ = nullptr;
        InitFunc init_;
        CleanUpFunc cleanup_;

        void check_callbacks() const;
    };
} //namespace curl_raii
#include "curl_raii.inl"
