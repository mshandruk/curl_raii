#pragma once

#include <stdexcept>

namespace curl_raii
{
    template<typename GlobalPolicy>
    CurlRAII<GlobalPolicy>::CurlRAII(InitFunc init, CleanUpFunc cleanup)
        : init_{std::move(init)},
          cleanup_{std::move(cleanup)}
    {
        check_callbacks();
        GlobalPolicy::ensure_initialized();
        handle_ = init_();
        if (!handle_)
        {
            throw std::runtime_error("curl_easy_init failed");
        }
    }

    template<typename GlobalPolicy>
    CurlRAII<GlobalPolicy>::CurlRAII(CurlRAII &&other) noexcept
        : handle_{other.handle_},
          init_{std::move(other.init_)},
          cleanup_{std::move(other.cleanup_)}
    {
        other.handle_ = nullptr;
        check_callbacks();
    }

    template<typename GlobalPolicy>
    CurlRAII<GlobalPolicy> &CurlRAII<GlobalPolicy>::operator=(CurlRAII &&other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        cleanup_(handle_);
        handle_ = other.handle_;
        other.handle_ = nullptr;

        init_ = std::move(other.init_);
        cleanup_ = std::move(other.cleanup_);

        check_callbacks();
        return *this;
    }

    template<typename GlobalPolicy>
    CurlRAII<GlobalPolicy>::~CurlRAII()
    {
        if (handle_ && cleanup_)
        {
            cleanup_(handle_);
        }
        GlobalPolicy::cleanup();
    }

    template<typename GlobalPolicy>
    CURL *CurlRAII<GlobalPolicy>::get() const
    {
        return handle_;
    }

    template<typename GlobalPolicy>
    void CurlRAII<GlobalPolicy>::check_callbacks() const
    {
        if (!init_ || !cleanup_)
        {
            throw std::invalid_argument("init and cleanup and policy_ must be valid functions");
        }
    }
}
