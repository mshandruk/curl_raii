#include <gtest/gtest.h>
#include <curl_raii/curl_raii.hpp>

using namespace curl_raii;

TEST(CurlRAIITest, CallsClenup_WhenDestroyed)
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

TEST(CurlRAIITest, Throws_WhenInitFails_AndDoesNotCleanup)
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

TEST(CurlRAIITest, DefaultConstructor_InitializesValidHandle)
{
    CurlRAII curl_raii;
    EXPECT_TRUE(curl_raii.get());
}
