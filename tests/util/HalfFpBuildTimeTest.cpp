#include "CppUTest/TestHarness.h"
#include "HalfFpBuildTime.h"

TEST_GROUP(HalfFpBuildTime)
{
  HalfFpBuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new HalfFpBuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(HalfFpBuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

