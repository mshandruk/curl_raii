#include <stdexcept>
#include <utility>

#include "curl_raii/curl_raii.hpp"


namespace curl_raii
{
    CurlRAII::CurlRAII(InitFunc init, CleanUpFunc cleanup)
        : init_{std::move(init)}, cleanup_{std::move(cleanup)}
    {
        curl = init_();
        if (!curl)
        {
            throw std::runtime_error("failed curl_initialize");
        }
    }

    CurlRAII::CurlRAII(CurlRAII &&other) noexcept
        : init_{std::move(other.init_)}, cleanup_{std::move(other.cleanup_)}
    {
        curl = other.curl;
        other.curl = nullptr;
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
