#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <curl_raii/curl_easy_session.hpp>
#include <curl_raii/curl_raii_adapter.hpp>

using namespace curl_raii;

class MockCurlRaii final : public CurlRAIIAdapter
{
public:
    MOCK_METHOD(CURL*, get, (), (const, override));
};

using namespace curl_raii;
using ::testing::AtLeast;

TEST(CurlEasySessionTest, ShouldCallGet_WhenInitialize)
{
    MockCurlRaii mock;
    EXPECT_CALL(mock, get()).Times(AtLeast(1));

    CurlEasySession session(mock);
}

TEST(CurlEasySessionTest, Should_Throw_WhenPeform)
{
    MockCurlRaii mock;
    EXPECT_CALL(mock, get()).Times(AtLeast(1));
    CurlEasySession session(mock);

    EXPECT_THROW(session.perform(), std::runtime_error);
}
