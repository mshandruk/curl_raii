#pragma once

namespace curl_raii
{
    template<typename GlobalPolicy>
    CurlEasySession<GlobalPolicy>::CurlEasySession(CurlRAII<> curl_raii)
        : curl_raii_{std::move(curl_raii)}
    {
        handle_ = curl_raii_.get();
    }

    template<typename GlobalPolicy>
    void CurlEasySession<GlobalPolicy>::perform() const
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

    template<typename GlobalPolicy>
    template<typename Value>
    void CurlEasySession<GlobalPolicy>::set_option(const CURLoption &option, Value value)
    {
        set_option_impl(option, value);
    }

    template<typename GlobalPolicy>
    void CurlEasySession<GlobalPolicy>::set_url(const std::string &url)
    {
        set_option_impl(CURLOPT_URL, url.c_str());
    }

    template<typename GlobalPolicy>
    template<typename Value>
    void CurlEasySession<GlobalPolicy>::set_option_impl(const CURLoption &option, Value value)
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
