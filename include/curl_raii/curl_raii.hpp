#pragma once

#include <functional>

#include <curl/curl.h>

namespace curl_raii
{
    class CurlRAII
    {
    public:
        using InitFunc = std::function<CURL*()>;
        using CleanUpFunc = std::function<void(CURL *)>;

        explicit CurlRAII(InitFunc init = curl_easy_init, CleanUpFunc cleanup = curl_easy_cleanup);

        ~CurlRAII();

        CurlRAII(const CurlRAII &) = delete;

        CurlRAII &operator=(const CurlRAII &) = delete;

        CurlRAII(CurlRAII &&other) noexcept;

        CurlRAII &operator=(CurlRAII &&other) noexcept;

        [[nodiscard]]
        CURL *get() const;

        CURL *operator->() const;

    private:
        CURL *curl = nullptr;
        InitFunc init_;
        CleanUpFunc cleanup_;
    };
} //namespace curl_raii
