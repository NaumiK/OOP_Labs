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
TEST(ListTests, PushFrontRbeginTest) {
  std::list l = {1, 2, 3};
  msd::list<int> ml;
  for (auto &&i: l)
    ml.push_front(i);
  bool actual = std::equal(l.begin(), l.end(), ml.rbegin(), ml.rend());
  EXPECT_EQ(actual, true);
}
TEST(ListTests, IteratorConstructTest) {
  auto v = std::vector<int>{1, 2, 3, 4};
  auto w = msd::list(v.begin(), v.end());
  bool actual = std::is_same_v<decltype(w), typename msd::list<int>> &&
                w.size() == v.size();
  actual = actual && std::equal(v.begin(), v.end(), w.begin(), w.end());
  EXPECT_EQ(actual, true);
}
TEST(ListTests, IteratorConstructTest2) {
  auto v = msd::list<int>{1, 2, 3, 4};
  auto w = msd::list(v.begin(), v.end());
  auto &&t = const_cast<const decltype(w) &>(w).begin();
  bool actual = v == w && *(++t) == 2;
  EXPECT_EQ(actual, true);
}
TEST(ListTests, IteratorConstructTest3) {
  auto v = std::list<int>{1, 2, 3, 4};
  auto w = msd::list(v.rbegin(), v.rend());
  bool actual = std::is_same_v<decltype(w), typename msd::list<int>> &&
                w.size() == v.size();
  actual = actual && std::equal(v.begin(), v.end(), w.crbegin(), w.crend());
  actual = actual && std::equal(v.rbegin(), v.rend(), w.cbegin(), w.cend());
  EXPECT_EQ(actual, true);
}

TEST(ListTests, IteratorConstructTest4) {
  int v[4] = {1, 2, 3, 4};
  auto w = msd::list(v, v + 4);
  auto x = msd::list{1, 2, 3, 4};
  bool actual = std::is_same_v<decltype(w), typename msd::list<int>>;
  actual = actual && std::equal(v, v + 4, w.begin(), w.end());
  actual = actual && std::equal(x.begin(), x.end(), w.begin(), w.end());
  EXPECT_EQ(actual, true);
}
TEST(ListTests, EmplaceTest) {
  struct CopyTest {
    bool copied = false;
    bool moved = false;
    CopyTest(const CopyTest &ct) { copied = true; }
    CopyTest(CopyTest &&ct) { moved = true; }
    int a_;
    double b_;
    int64_t c_;
    CopyTest(int a, double b, int64_t c) : a_(a), b_(b), c_(c) {}
  };
  msd::list<CopyTest> v;
  v.emplace_back(1, 2.0, 3);
  bool actual = !(v.front().moved || v.front().copied);
  EXPECT_EQ(actual, true);
  EXPECT_EQ(v.front().a_, 1);
  EXPECT_EQ(v.front().b_, 2.0);
  EXPECT_EQ(v.front().c_, 3);
}
TEST(ListTests, SwapTest) {
  msd::list v1 = {1, 2, 3};
  msd::list v2 = {2, 3, 4};
  msd::list w1 = {1, 2, 3};
  msd::list w2 = {2, 3, 4};
  std::swap(w1, w2);
  v1.swap(v2);
  EXPECT_EQ(v1 == w1, true);
  EXPECT_EQ(v2 == w2, true);
}
