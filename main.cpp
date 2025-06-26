#include <future>

#include <gtest/gtest.h>


TEST(SampleTest, BasicAssertions) {
    // Expect equality.
    EXPECT_EQ(1, 1);
    // Expect inequality.
    EXPECT_NE(1, 2);
    // Expect true.
    EXPECT_TRUE(true);
    // Expect false.
    EXPECT_FALSE(false);
}