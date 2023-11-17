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
  for (auto &i : v) {
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
  for (auto &i : v) {
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
#if 0
TEST(VectorTests, FilledTest) {
  auto v = msd::vector<int>::create_filled_vector(8, 8);
  bool expected = true, actual = (v.size() == 8 && v.capacity() == 8);
  for (auto &i : v)
    actual = actual && i == 8;
  EXPECT_EQ(actual, expected);
}
#endif

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
