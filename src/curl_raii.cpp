#include <utility>

#include "curl_raii/curl_raii.hpp"


namespace curl_raii
{
    CurlRAII::CurlRAII(InitFunc init, CleanUpFunc cleanup)
        : init_{std::move(init)}, cleanup_{std::move(cleanup)}
    {
    }

    CurlRAII::CurlRAII(CurlRAII &&other) noexcept
    {
        curl = other.curl;
        other.curl = nullptr;
        init_ = std::move(other.init_);
        cleanup_ = std::move(other.cleanup_);
    }

    CurlRAII &CurlRAII::operator=(CurlRAII &&other) noexcept
    {
        if (this == &other) return *this;
        if (curl && cleanup_)
        {
            cleanup_(curl);
        }
        curl = other.curl;
        other.curl = nullptr;
        init_ = std::move(other.init_);
        cleanup_ = std::move(other.cleanup_);

        return *this;
    }

    CurlRAII::~CurlRAII()
    {
        if (curl && cleanup_)
        {
            cleanup_(curl);
        }
    }

    CURL *CurlRAII::get() const
    {
        return curl;
    }

    CURL *CurlRAII::operator->() const
    {
        return curl;
    }
}
