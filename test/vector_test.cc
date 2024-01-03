#include "MSDCore/vector.hh"
#include <algorithm>
#include <gtest/gtest.h>
#include <stdexcept>

TEST(VectorTests, EmptyVectorBE) {
  msd::vector<int> v;
  const auto expected = true;
  const auto actual = (v.begin() == v.end());
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, EmptyVectorRBE) {
  msd::vector<int> v;
  const auto expected = true;
  const auto actual = (v.rbegin() == v.rend());
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, EmptyVectorSize) {
  msd::vector<int> v;
  const auto expected = 0;
  const auto actual = v.size();
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, MEmptyVectorBE) {
  msd::vector<int> v;
  v.push_back(0);
  v.pop_back();
  const auto expected = true;
  const auto actual = (v.begin() == v.end());
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, MEmptyVectorRBE) {
  msd::vector<int> v;
  v.push_back(0);
  v.pop_back();
  const auto expected = true;
  const auto actual = (v.rbegin() == v.rend());
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, MEmptyVectorSize) {
  msd::vector<int> v;
  v.push_back(0);
  v.pop_back();
  const auto expected = 0;
  const auto actual = v.size();
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, PushPopSize) {
  msd::vector<int> v;
  for (size_t i = 0, ei = 1024; i < ei; ++i)
    v.push_back(i);
  for (size_t i = 0, ei = 256; i < ei; ++i)
    v.pop_back();
  const auto expected = 768;
  const auto actual = v.size();
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, PopEmpty) {
  msd::vector<int> v;
  const auto expected = 1;
  auto actual = 0;
  try {
    v.pop_back();
  } catch (std::runtime_error &) {
    actual = 1;
  }
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, InitListSize) {
  msd::vector<int> v = {0, 1, 2, 3};
  const auto expected = 4;
  const auto actual = v.size();
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, InitListIteratorTest) {
  msd::vector<int> v = {0, 1, 2, 3};
  int cur = 0;
  bool actual = true, expected = true;
  for (auto &&i : v) {
    actual = actual && (i == cur);
    ++cur;
  }
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, SortAndIteratorTest) {
  msd::vector<int> v = {0, 5, 8, 3, 2, 1, 4, 7, 6};
  int cur = 0;
  bool actual = true, expected = true;
  std::sort(v.begin(), v.end());
  for (auto &&i : v) {
    actual = actual && (i == cur);
    ++cur;
  }
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, SortTest) {
  msd::vector<int> v = {0, 5, 8, 3, 2, 1, 4, 7, 6};
  bool actual = true, expected = true;
  std::sort(v.begin(), v.end());
  for (size_t i = 0, ei = v.size(); i < ei; ++i)
    actual = actual && (v[i] == i);
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, ReverseIteratorReverseSortTest) {
  msd::vector<int> v = {0, 5, 8, 3, 2, 1, 4, 7, 6};
  int cur = 0;
  bool actual = true, expected = true;
  std::sort(v.rbegin(), v.rend());
  for (auto i = v.rbegin(), ei = v.rend(); i != ei; ++i) {
    actual = actual && (*i == cur);
    ++cur;
  }
  EXPECT_EQ(expected, actual);
}

TEST(VectorTests, SizeCapacityTest) {
  msd::vector<int> v(20);
  bool expected = true, actual = (v.size() == 0 && v.capacity() == 20);
  EXPECT_EQ(actual, expected);
}
TEST(VectorTests, FilledTest) {
  auto v = msd::vector<int>::create_filled_vector(8, 8);
  bool expected = true, actual = (v.size() == 8 && v.capacity() == 8);
  for (auto &&i : v)
    actual = actual && i == 8;
  EXPECT_EQ(actual, expected);
}
TEST(VectorTests, IteratorConstructTest) {
  auto v = std::vector<int>{1, 2, 3, 4};
  auto w = msd::vector(v.begin(), v.end());
  bool actual = std::is_same_v<decltype(w), typename msd::vector<int>> &&
                w.size() == v.size();
  actual = actual && std::equal(v.begin(), v.end(), w.begin(), w.end());
  EXPECT_EQ(actual, true);
}
TEST(VectorTests, IteratorConstructTest2) {
  auto v = msd::vector<int>{1, 2, 3, 4};
  auto w = msd::vector(v.begin(), v.end());
  auto &&t = const_cast<const decltype(w) &>(w).begin();
  bool actual = v == w && *(++t) == 2;
  EXPECT_EQ(actual, true);
}
TEST(VectorTests, IteratorConstructTest3) {
  auto v = std::vector<int>{1, 2, 3, 4};
  auto w = msd::vector(v.rbegin(), v.rend());
  bool actual = std::is_same_v<decltype(w), typename msd::vector<int>> &&
                w.size() == v.size();
  actual = actual && std::equal(v.begin(), v.end(), w.crbegin(), w.crend());
  actual = actual && std::equal(v.rbegin(), v.rend(), w.cbegin(), w.cend());
  EXPECT_EQ(actual, true);
}

TEST(VectorTests, EmplaceTest) {
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
  msd::vector<CopyTest> v(8);
  v.emplace_back(1, 2.0, 3);
  bool actual = !(v[0].moved || v[0].copied);
  EXPECT_EQ(actual, true);
  EXPECT_EQ(v[0].a_, 1);
  EXPECT_EQ(v[0].b_, 2.0);
  EXPECT_EQ(v[0].c_, 3);
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
