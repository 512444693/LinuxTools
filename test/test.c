#include "max.h"
#include "gtest/gtest.h"



TEST(MaxTest, ZeroInput)
{
	EXPECT_EQ(4, max(4, 0));
	EXPECT_EQ(4, max(0, 4));
	EXPECT_EQ(0, max(0, 0));
}

TEST(MaxTest, NegtiveInput)
{
	EXPECT_EQ(4, max(4, -1));
	EXPECT_EQ(4, max(-1, 4));
	EXPECT_EQ(-2, max(-2, -3));
}

/*
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
*/
