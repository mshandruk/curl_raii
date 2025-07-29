#include <stdexcept>
#include <utility>

#include "curl_raii/curl_raii.hpp"


namespace curl_raii
{
    CurlRAII::CurlRAII(InitFunc init, CleanUpFunc cleanup)
        : init_{std::move(init)}, cleanup_{std::move(cleanup)}
    {
        handle_ = init_();
        if (!handle_)
        {
            throw std::runtime_error("curl_easy_init failed");
        }
    }

    CurlRAII::CurlRAII(CurlRAII &&other) noexcept
        : handle_{other.handle_},
          init_{std::move(other.init_)},
          cleanup_{std::move(other.cleanup_)}
    {
        other.handle_ = nullptr;
    }

    CurlRAII &CurlRAII::operator=(CurlRAII &&other) noexcept
    {
        if (this == &other) return *this;

        if (handle_ && cleanup_)
        {
            cleanup_(handle_);
        }

        handle_ = other.handle_;
        other.handle_ = nullptr;
        init_ = std::move(other.init_);
        cleanup_ = std::move(other.cleanup_);

        return *this;
    }

    CurlRAII::~CurlRAII()
    {
        if (handle_ && cleanup_)
        {
            cleanup_(handle_);
        }
    }

    CURL *CurlRAII::get() const
    {
        return handle_;
    }

    CURL *CurlRAII::operator->() const
    {
        return handle_;
    }
}
