#include "MSDCore/list.hh"
#include <list>
#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>

TEST(ListTests, BegEndTest) {
  std::list l = {1, 2, 3};
  msd::list<int> ml;
  for (auto &&i: l)
    ml.push_back(i);
  bool actual = std::equal(l.begin(), l.end(), ml.begin(), ml.end());
  EXPECT_EQ(actual, true);
}

