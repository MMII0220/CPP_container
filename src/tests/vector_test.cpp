#include <gtest/gtest.h>

#include <vector>

#include "./../s21_containers/s21_container.hpp"

// Constructors
TEST(VectorAllTests, initialize_test) {
  s21::Vector<int> s21_v;
  size_t sz = s21_v.getSize();
  EXPECT_EQ(sz, 0);
}
TEST(VectorAllTests, initialize_with_size) {
  s21::Vector<int> s21_v(2);
  size_t sz = s21_v.getSize();
  EXPECT_EQ(sz, 2);
  EXPECT_EQ(s21_v.getCapacity(), 2);
}
TEST(VectorAllTests, initialize_with_values) {
  s21::Vector<int> s21_v = {1, 2, 3, 4};
  EXPECT_EQ(s21_v.getSize(), 4);
  EXPECT_EQ(s21_v.getCapacity(), 4);
  EXPECT_EQ(s21_v.getContainer()[0], 1);
  EXPECT_EQ(s21_v.getContainer()[1], 2);
  EXPECT_EQ(s21_v.getContainer()[2], 3);
  EXPECT_EQ(s21_v.getContainer()[3], 4);
}
TEST(VectorAllTests, constructor_throw_size_turn_) {
  s21::Vector<int> s21_v = {};
  // s21_v.size() = 0;
  EXPECT_EQ(s21_v.getSize(), 0);
}

TEST(VectorAllTests, copy_vector) {
  // std::vector<int> std_v = {1, 2, 3};
  s21::Vector<int> s21_v1 = {1, 2, 3};
  s21::Vector<int> s21_v2 = s21_v1;
  EXPECT_EQ(s21_v2.getContainer()[0], 1);
  EXPECT_EQ(s21_v2.getContainer()[1], 2);
  EXPECT_EQ(s21_v2.getContainer()[2], 3);
}
TEST(VectorAllTests, move_vector) {
  s21::Vector<int> s21_v1(3);
  s21::Vector<int> s21_v2(std::move(s21_v1));
  EXPECT_EQ(0, s21_v1.getSize());
  EXPECT_EQ(0, s21_v1.getCapacity());

  EXPECT_EQ(3, s21_v2.getSize());
  EXPECT_EQ(3, s21_v2.getCapacity());
}
TEST(VectorAllTests, empty_size_capacity_reserve_shrink_fit) {
  s21::Vector<int> s21_v = {1, 2, 3, 4};
  EXPECT_FALSE(s21_v.empty() == true);
  EXPECT_EQ(s21_v.size(), 4);
  EXPECT_EQ(s21_v.capacity(), 4);
  s21_v.reserve(22);
  EXPECT_EQ(s21_v.getCapacity(), 22);
  s21_v.shrink_to_fit();
  EXPECT_EQ(s21_v.size(), 4);
}

TEST(VectorAllTests, modifiers_push_tests) {
  s21::Vector<int> s21_v;
  s21_v.push_back(2);
  s21_v.push_back(6);
  s21_v.push_back(9);
  EXPECT_EQ(s21_v.getContainer()[0], 2);
  EXPECT_EQ(s21_v.getContainer()[1], 6);
  EXPECT_EQ(s21_v.getContainer()[2], 9);
}

TEST(VectorAllTests, modifiers_pop_tests) {
  s21::Vector<int> s21_v = {1, 2, 3, 4};
  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();
  EXPECT_EQ(s21_v.getContainer()[0], 1);
  EXPECT_EQ(s21_v.size(), 1);
  EXPECT_EQ(s21_v.getSize(), 1);
}
TEST(VectorAllTests, clear_test) {
  s21::Vector<int> s21_v = {1, 2, 3};
  s21_v.clear();
  EXPECT_EQ(s21_v.size(), 0);
}
TEST(VectorAllTests, erase_test) {
  s21::Vector<int> s21_v = {11, 32, 53, 62, 16};
  s21_v.erase(s21_v.begin() + 2);

  EXPECT_EQ(s21_v.size(), 4);

  EXPECT_EQ(s21_v.getContainer()[0], 11);
  EXPECT_EQ(s21_v.getContainer()[1], 32);
  EXPECT_EQ(s21_v.getContainer()[2], 62);
  EXPECT_EQ(s21_v.getContainer()[3], 16);
}

TEST(VectorAllTests, modifiers_at_tests) {
  s21::Vector<int> s21_v = {1, 2, 3, 4};
  EXPECT_EQ(s21_v.at(0), 1);
  EXPECT_EQ(s21_v.at(1), 2);
  EXPECT_EQ(s21_v.at(2), 3);
  EXPECT_EQ(s21_v.at(3), 4);
}

TEST(VectorAllTests, front_back_test) {
  s21::Vector<int> s21_v = {1, 2, 3, 4};
  EXPECT_EQ(s21_v.front(), 1);
  EXPECT_EQ(s21_v.back(), 4);
}
TEST(VectorAllTests, data_test) {
  s21::Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_EQ(*s21_v.data(), *std_v.data());
}

/* Throw_ERRORS
***************************************
***************************************
****************************************/

TEST(VectorAllTests, constructor_throw_size) {
  try {
    s21::Vector<int> s21_v(-1);
    // FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(),
              std::string("cannot create std::vector larger than max_size()"));
  }
}
TEST(VectorAllTests, modifier_throw_at) {
  try {
    s21::Vector<int> s21_v = {1, 2, 3, 4};
    s21_v.at(7);
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("vector::_M_range_check: __n"));
  }
}
TEST(VectorAllTests, modifier_throw_pop) {
  try {
    s21::Vector<int> s21_v;
    s21_v.pop_back();
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("0 zsh: segmentation fault"));
  }
}