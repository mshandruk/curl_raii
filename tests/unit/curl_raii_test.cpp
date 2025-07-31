#include <gtest/gtest.h>
#include <curl_raii/curl_raii.hpp>

using namespace curl_raii;

TEST(CurlRAIITest, CallsCleanup_WhenDestroyed)
{
    bool cleanup_called = false;
    auto fake_init_func = []() {
        static CURL *dummy;
        return &dummy;
    };

    auto fake_cleanup_func = [&](CURL *) {
        cleanup_called = true;
    }; {
        CurlRAII curl_raii{fake_init_func, fake_cleanup_func};
    }

    ASSERT_TRUE(cleanup_called);
}

TEST(CurlRAIITest, Throws_WhenInitFails_AndDoesNotCallCleanup)
{
    bool cleanup_called = false;
    auto fake_init_func = []() {
        return nullptr;
    };
    auto fake_cleanup_func = [&](CURL *) {
        cleanup_called = false;
    };
    ASSERT_THROW(
        CurlRAII(fake_init_func, fake_cleanup_func),
        std::runtime_error
    );
    EXPECT_FALSE(cleanup_called);
}

TEST(CurlRAIITest, Succeeds_WhenConstructedWithDefaults)
{
    CurlRAII curl_raii;
    EXPECT_TRUE(curl_raii.get());
}

TEST(CurlRAIITest, Throws_WhenInitAndCleanupAreNullptr)
{
    EXPECT_THROW(CurlRAII(nullptr, nullptr), std::invalid_argument);
}

TEST(CurlRAIITest, Throws_WhenInitIsNullptr)
{
    auto fake_cleanup = [](CURL *) {
    };
    EXPECT_THROW(CurlRAII(nullptr,fake_cleanup), std::invalid_argument);
}

TEST(CurlRAIITest, Throws_WhenCleanupIsNullptr)
{
    auto fake_init = []() {
        static CURL *handle;
        return &handle;
    };

    EXPECT_THROW(CurlRAII(fake_init, nullptr), std::invalid_argument);
}

TEST(CurlRAIITest, DoesNotThrow_WhenInitAndCleanupAreValid)
{
    auto fake_init = []() {
        static CURL *handle;
        return &handle;
    };

    auto fake_cleanup = [](CURL *) {
    };

    EXPECT_NO_THROW(CurlRAII(fake_init, fake_cleanup));
}
