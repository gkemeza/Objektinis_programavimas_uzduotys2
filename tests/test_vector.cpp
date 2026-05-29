#include "Vector.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

/**
 * @file test_vector.cpp
 * @brief Šiame faile yra įgyvendinti vienetų testai, skirti patikrinti Vector
 * klasės funkcionalumą. Testai apima konstruktorius, elementų prieigą,
 * talpą, rezervavimą, modifikatorius ir kt.
 *
 * Šie testai yra svarbūs siekiant užtikrinti, kad Vector klasė veiktų
 * tinkamai ir atitiktų lūkesčius įvairiose situacijose. Naudojant Google Test
 * framework'ą, testai yra lengvai skaitomi ir palaikomi.
 *
 */
// --- Constructor Tests ---

TEST(VectorTest, DefaultConstructor) {
  Vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.data_ptr(), nullptr);
}

TEST(VectorTest, SizeConstructor) {
  Vector<int> v(5);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], 0); // Verify default-initialized elements
  }
}

TEST(VectorTest, SizeAndValueConstructor) {
  Vector<std::string> v(3, "test");
  EXPECT_EQ(v.size(), 3);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], "test");
  }
}

TEST(VectorTest, IteratorConstructor) {
  std::vector<int> src = {10, 20, 30, 40};
  Vector<int> v(src.begin(), src.end());
  ASSERT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[3], 40);
}

TEST(VectorTest, CopyConstructorAndAssignment) {
  Vector<int> original = {1, 2, 3};
  Vector<int> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy[1], original[1]);

  Vector<int> assigned;
  assigned = original;
  EXPECT_EQ(assigned.size(), original.size());
  EXPECT_EQ(assigned[2], 3);
}

TEST(VectorTest, MoveConstructorAndAssignment) {
  Vector<int> original = {100, 200, 300};
  Vector<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved[0], 100);
  // The original vector should be in a valid, empty state
  EXPECT_EQ(original.size(), 0);
  EXPECT_EQ(original.data_ptr(), nullptr);

  Vector<int> assigned;
  assigned = std::move(moved);
  EXPECT_EQ(assigned.size(), 3);
  EXPECT_EQ(moved.size(), 0);
}

// --- Element Access Tests ---

TEST(VectorTest, ElementAccessAt) {
  Vector<int> v = {10, 20, 30};
  EXPECT_EQ(v.at(0), 10);
  EXPECT_EQ(v.at(2), 30);
  EXPECT_THROW(v.at(3), std::out_of_range);
}

TEST(VectorTest, FrontAndBackAccess) {
  Vector<int> v = {5, 6, 7};
  EXPECT_EQ(v.front(), 5);
  EXPECT_EQ(v.back(), 7);

  Vector<int> empty_v;
  EXPECT_THROW(empty_v.front(), std::out_of_range);
  EXPECT_THROW(empty_v.back(), std::out_of_range);
}

// --- Capacity and Reserve Tests ---

TEST(VectorTest, ReserveAndShrink) {
  Vector<int> v;
  v.reserve(50);
  EXPECT_EQ(v.capacity(), 50);
  EXPECT_EQ(v.size(), 0);

  v.push_back(1);
  v.push_back(2);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 2);
  EXPECT_EQ(v.size(), 2);
}

// --- Modifiers Tests ---

TEST(VectorTest, PushAndPopBack) {
  Vector<std::string> v;
  v.push_back("first");
  std::string second = "second";
  v.push_back(std::move(second));

  ASSERT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], "first");
  EXPECT_EQ(v[1], "second");

  v.pop_back();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.back(), "first");
}

TEST(VectorTest, ClearElements) {
  Vector<int> v = {1, 2, 3};
  v.clear();
  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, InsertOperations) {
  Vector<int> v = {1, 4};

  // Insert single element
  auto it = v.insert(v.begin() + 1, 2);
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[1], 2);

  // Insert multiple elements
  v.insert(v.begin() + 2, 2, 99); // Insert two 99s before element 4
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[2], 99);
  EXPECT_EQ(v[3], 99);
  EXPECT_EQ(v[4], 4);
}

TEST(VectorTest, EraseOperations) {
  Vector<int> v = {10, 20, 30, 40, 50};

  // Erase single element
  auto it = v.erase(v.begin() + 1); // Remove 20
  EXPECT_EQ(*it, 30);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[1], 30);

  // Erase range
  v.erase(v.begin() + 1, v.begin() + 3); // Remove 30 and 40
  ASSERT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 50);
}

TEST(VectorTest, EmplaceAndEmplaceBack) {
  struct TestStruct {
    int x;
    std::string y;
    TestStruct(int x_val, std::string y_val) : x(x_val), y(std::move(y_val)) {}
  };

  Vector<TestStruct> v;
  v.emplace_back(10, "ten");
  v.emplace(v.begin(), 20, "twenty");

  ASSERT_EQ(v.size(), 2);
  EXPECT_EQ(v[0].x, 20);
  EXPECT_EQ(v[0].y, "twenty");
  EXPECT_EQ(v[1].x, 10);
  EXPECT_EQ(v[1].y, "ten");
}

TEST(VectorTest, ResizeOperations) {
  Vector<int> v = {1, 2};
  v.resize(4, 100);
  ASSERT_EQ(v.size(), 4);
  EXPECT_EQ(v[2], 100);
  EXPECT_EQ(v[3], 100);

  v.resize(1);
  EXPECT_EQ(v.size(), 1);
}

// --- Comparison and Ranges Tests ---

TEST(VectorTest, Comparisons) {
  Vector<int> v1 = {1, 2, 3};
  Vector<int> v2 = {1, 2, 3};
  Vector<int> v3 = {1, 2, 4};

  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 != v2);
  EXPECT_TRUE(v1 < v3);
  EXPECT_TRUE(v3 >= v1);
}

TEST(VectorTest, RangeModifiers) {
  Vector<int> v = {1, 2};
  std::vector<int> src = {3, 4, 5};
  v.append_range(src);

  ASSERT_EQ(v.size(), 5);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}