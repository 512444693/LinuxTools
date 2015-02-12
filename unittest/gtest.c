#include <stdio.h>
#include "gtest/gtest.h"
#include "utils.h"

TEST(UtilsTest, IPStr2Int)
{
    Utils u;
    EXPECT_EQ(16777343u, u.IPStr2Int("127.0.0.1"));
}

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from gtest.c\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
