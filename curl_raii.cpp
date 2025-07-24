#include <stdexcept>
#include <functional>

#include <curl/curl.h>

class CurlRAII
{
public:
    using InitFunc = std::function<CURL*()>;
    using CleanUpFunc = std::function<void(CURL*)>;

    CurlRAII(
            InitFunc init = curl_easy_init, 
            CleanUpFunc cleanup = curl_easy_cleanup
    ):
        init_{init}, cleanup_{cleanup}
    {
        curl = init();
        if (!curl)
        {
            throw std::runtime_error("curl_easy_init failed");
        }
    }

    CurlRAII(const CurlRAII&)= delete;
    CurlRAII& operator=(const CurlRAII&) = delete;

    CurlRAII(CurlRAII &&other) noexcept
        : init_{other.init_}, cleanup_{other.cleanup_}
    {
        curl = other.curl;
        other.curl = nullptr;
    }

    CurlRAII& operator=(CurlRAII&& other)
    {
        if (this == &other) return *this;
        if (curl && cleanup_)
        {
            cleanup_(curl);
        }

        curl = other.curl;
        init_ = std::move(other.init_);
        cleanup_ = std::move(other.cleanup_);
        other.curl = nullptr;
        return *this;
    }

    ~CurlRAII()
    {
        if (curl && cleanup_)
        {
            cleanup_(curl);
        }
    }

    CURL* get() const
    {
        return curl;
    }

    CURL* operator->() const
    {
        return curl;
    }
private:
    CURL* curl = nullptr;
    InitFunc init_;
    CleanUpFunc cleanup_;
};

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

TEST(CurlRAIITest, CallCleanUpOnDestuction)
{
    bool cleanup_called = false;

    auto fake_init = [](){
        static CURL* curl;
        return &curl;
    };

    auto fake_cleanup = [&](CURL *curl){
        cleanup_called = true;
    };

    {
        CurlRAII curl(fake_init, fake_cleanup);
    }

    ASSERT_TRUE(cleanup_called);
}

TEST(CurlRAIITest, ThrowsIfInitFailsAndNoClean)
{
    bool cleanup_called = false;

    auto fake_init = []() {
        return nullptr;
    };

    auto fake_cleanup = [&](CURL *curl) {
        cleanup_called = true;
    };

    ASSERT_THROW(
            CurlRAII(fake_init, fake_cleanup), 
            std::runtime_error
    );

    EXPECT_FALSE(cleanup_called);
}
