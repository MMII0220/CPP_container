#include <gtest/gtest.h>

#include <array>
#include <string>

// #include "./s21_containers/list/s21_list.tpp"
#include "./../s21_containersplus/s21_containersplus.hpp"

TEST(Array, test_default_contructor) {
  s21::array<std::string, 0> s21_arr;
  std::array<std::string, 0> std_arr;

  EXPECT_EQ(s21_arr.size(), std_arr.size());

  s21::array<std::string, 2> s21_arr_2;
  std::array<std::string, 2> std_arr_2;
  EXPECT_EQ(s21_arr_2[0], std_arr_2[0]);
  EXPECT_EQ(s21_arr_2[1], std_arr_2[1]);
  EXPECT_EQ(s21_arr_2[0], "");
  EXPECT_EQ(s21_arr_2[1], "");
  EXPECT_EQ(s21_arr_2.size(), std_arr_2.size());
}

TEST(Array, test_initializer_list) {
  s21::array<std::string, 3> s21_arr = {"one", "two", "three"};
  std::array<std::string, 3> std_arr = {"one", "two", "three"};

  EXPECT_EQ(s21_arr.size(), std_arr.size());
  EXPECT_EQ(s21_arr[0], std_arr[0]);
  EXPECT_EQ(s21_arr[1], std_arr[1]);
  EXPECT_EQ(s21_arr[2], std_arr[2]);

  s21::array<int, 2> s21_arr_2 = {};
  std::array<int, 2> std_arr_2 = {};

  EXPECT_EQ(s21_arr_2[0], std_arr_2[0]);
  EXPECT_EQ(s21_arr_2[1], std_arr_2[1]);
  EXPECT_EQ(s21_arr_2[0], 0);
  EXPECT_EQ(s21_arr_2[1], 0);
  EXPECT_EQ(s21_arr_2.size(), std_arr_2.size());

  const s21::array<int, 3> s21_arr_3 = {1, 2, 3};
  const std::array<int, 3> std_arr_3 = {1, 2, 3};

  EXPECT_EQ(s21_arr_3[0], std_arr_3[0]);
  EXPECT_EQ(s21_arr_3[1], std_arr_3[1]);
  EXPECT_EQ(s21_arr_3[0], 1);
  EXPECT_EQ(s21_arr_3[1], 2);
  EXPECT_EQ(s21_arr_3.size(), std_arr_3.size());
}

TEST(Array, test_copy_contructor) {
  s21::array<std::string, 3> arr_1 = {"one", "two", "three"};
  s21::array<std::string, 3> arr_2 = arr_1;

  EXPECT_EQ(arr_2[0], arr_1[0]);
  EXPECT_EQ(arr_2[1], arr_1[1]);
  EXPECT_EQ(arr_2[2], arr_1[2]);
  EXPECT_EQ(arr_2[0], "one");
  EXPECT_EQ(arr_2[1], "two");
  EXPECT_EQ(arr_2[2], "three");
  EXPECT_EQ(arr_2.size(), arr_1.size());

  const s21::array<std::string, 3> arr_c = arr_1;

  EXPECT_EQ(arr_c[0], arr_1[0]);
  EXPECT_EQ(arr_c[1], arr_1[1]);
  EXPECT_EQ(arr_c[2], arr_1[2]);
  EXPECT_EQ(arr_c[0], "one");
  EXPECT_EQ(arr_c[1], "two");
  EXPECT_EQ(arr_c[2], "three");
  EXPECT_EQ(arr_c.size(), arr_1.size());
}

TEST(Array, test_move_contructor) {
  std::array<std::string, 3> std_arr_1 = {"1", "2", "3"};
  std::array<std::string, 3> std_arr_2(std::move(std_arr_1));

  EXPECT_EQ(std_arr_1[0], "");
  EXPECT_EQ(std_arr_1[1], "");
  EXPECT_EQ(std_arr_1[2], "");
  EXPECT_EQ(std_arr_2[0], "1");
  EXPECT_EQ(std_arr_2[1], "2");
  EXPECT_EQ(std_arr_2[2], "3");
  EXPECT_EQ(std_arr_2.size(), std_arr_1.size());

  s21::array<std::string, 3> arr_1 = {"1", "2", "3"};
  s21::array<std::string, 3> arr_2(std::move(arr_1));

  EXPECT_EQ(arr_1[0], "");
  EXPECT_EQ(arr_1[1], "");
  EXPECT_EQ(arr_1[2], "");
  EXPECT_EQ(arr_2[0], "1");
  EXPECT_EQ(arr_2[1], "2");
  EXPECT_EQ(arr_2[2], "3");
  EXPECT_EQ(arr_2.size(), arr_1.size());
}

TEST(Array, test_operator_equal_move) {
  std::array<int, 3> std_arr_1 = {1, 2, 3};
  std::array<int, 3> std_arr_2 = std::move(std_arr_1);

  EXPECT_EQ(std_arr_1[0], 1);
  EXPECT_EQ(std_arr_1[1], 2);
  EXPECT_EQ(std_arr_1[2], 3);
  EXPECT_EQ(std_arr_2[0], 1);
  EXPECT_EQ(std_arr_2[1], 2);
  EXPECT_EQ(std_arr_2[2], 3);
  EXPECT_EQ(std_arr_2.size(), std_arr_1.size());

  s21::array<int, 3> arr_1 = {1, 2, 3};
  s21::array<int, 3> arr_2 = std::move(arr_1);

  EXPECT_EQ(arr_1[0], 0);
  EXPECT_EQ(arr_1[1], 0);
  EXPECT_EQ(arr_1[2], 0);
  EXPECT_EQ(arr_2[0], 1);
  EXPECT_EQ(arr_2[1], 2);
  EXPECT_EQ(arr_2[2], 3);
  EXPECT_EQ(arr_2.size(), arr_1.size());
}

TEST(Array, test_operator_equal_copy) {
  std::array<int, 3> std_arr_1 = {1, 2, 3};
  std::array<int, 3> std_arr_2 = std_arr_1;

  EXPECT_EQ(std_arr_1[0], 1);
  EXPECT_EQ(std_arr_1[1], 2);
  EXPECT_EQ(std_arr_1[2], 3);
  EXPECT_EQ(std_arr_2[0], 1);
  EXPECT_EQ(std_arr_2[1], 2);
  EXPECT_EQ(std_arr_2[2], 3);
  EXPECT_EQ(std_arr_2.size(), std_arr_1.size());

  s21::array<int, 3> arr_1 = {1, 2, 3};
  s21::array<int, 3> arr_2 = arr_1;

  EXPECT_EQ(arr_1[0], 1);
  EXPECT_EQ(arr_1[1], 2);
  EXPECT_EQ(arr_1[2], 3);
  EXPECT_EQ(arr_2[0], 1);
  EXPECT_EQ(arr_2[1], 2);
  EXPECT_EQ(arr_2[2], 3);
  EXPECT_EQ(arr_2.size(), arr_1.size());
}

TEST(Array, test_at) {
  std::array<int, 3> std_arr = {1, 2, 3};
  s21::array<int, 3> s21_arr = {1, 2, 3};

  EXPECT_EQ(s21_arr[0], 1);
  EXPECT_EQ(s21_arr[1], 2);
  EXPECT_EQ(s21_arr[2], 3);

  EXPECT_EQ(s21_arr.at(0), std_arr[0]);
  EXPECT_EQ(s21_arr.at(1), std_arr[1]);
  EXPECT_EQ(s21_arr.at(2), std_arr[2]);
  EXPECT_EQ(s21_arr.size(), std_arr.size());

  EXPECT_THROW(std_arr.at(5), std::out_of_range);
  EXPECT_THROW(s21_arr.at(5), std::out_of_range);

  const std::array<int, 3> std_arr_c = {1, 2, 3};
  const s21::array<int, 3> s21_arr_c = {1, 2, 3};

  EXPECT_EQ(s21_arr_c[0], 1);
  EXPECT_EQ(s21_arr_c[1], 2);
  EXPECT_EQ(s21_arr_c[2], 3);

  EXPECT_EQ(s21_arr_c.at(0), std_arr_c[0]);
  EXPECT_EQ(s21_arr_c.at(1), std_arr_c[1]);
  EXPECT_EQ(s21_arr_c.at(2), std_arr_c[2]);
  EXPECT_EQ(s21_arr_c.size(), std_arr_c.size());

  EXPECT_THROW(std_arr_c.at(5), std::out_of_range);
  EXPECT_THROW(s21_arr_c.at(5), std::out_of_range);
}

TEST(Array, test_front) {
  s21::array<int, 3> s21_arr = {1, 2, 3};

  EXPECT_EQ(s21_arr.front(), 1);

  const s21::array<int, 1> s21_arr_c = {5};
  EXPECT_EQ(s21_arr_c.front(), 5);
}

TEST(Array, test_back) {
  s21::array<int, 3> s21_arr = {1, 2, 3};

  EXPECT_EQ(s21_arr.back(), 3);

  const s21::array<int, 1> s21_arr_c = {5};
  EXPECT_EQ(s21_arr_c.back(), 5);
}

// TEST(Array, test_data) {
//   s21::array<int, 3> s21_arr = {1, 2, 3};
//   EXPECT_EQ(s21_arr.data(), &s21_arr[0]);

//   const s21::array<int, 1> s21_arr_c = {5};
//   EXPECT_EQ(s21_arr_c.data(), &s21_arr_c[0]);
// }

TEST(Array, test_size) {
  s21::array<int, 3> s21_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};
  EXPECT_EQ(s21_arr.size(), std_arr.size());

  s21::array<int, 5> s21_arr_5;
  std::array<int, 5> std_arr_5;
  EXPECT_EQ(s21_arr_5.size(), std_arr_5.size());

  s21::array<int, 0> s21_arr_0;
  std::array<int, 0> std_arr_0;
  EXPECT_EQ(s21_arr_0.size(), std_arr_0.size());

  const s21::array<int, 1> s21_arr_c = {5};
  const std::array<int, 1> std_arr_c = {5};
  EXPECT_EQ(s21_arr_c.size(), std_arr_c.size());
}

TEST(Array, test_max_size) {
  s21::array<int, 3> s21_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};
  EXPECT_EQ(s21_arr.max_size(), std_arr.max_size());

  s21::array<int, 5> s21_arr_5;
  std::array<int, 5> std_arr_5;
  EXPECT_EQ(s21_arr_5.max_size(), std_arr_5.max_size());

  s21::array<int, 0> s21_arr_0;
  std::array<int, 0> std_arr_0;
  EXPECT_EQ(s21_arr_0.max_size(), std_arr_0.max_size());

  const s21::array<int, 1> s21_arr_c = {5};
  const std::array<int, 1> std_arr_c = {5};
  EXPECT_EQ(s21_arr_c.max_size(), std_arr_c.max_size());
}

TEST(Array, test_empty) {
  s21::array<int, 3> s21_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};
  EXPECT_EQ(s21_arr.empty(), std_arr.empty());

  s21::array<int, 5> s21_arr_5;
  std::array<int, 5> std_arr_5;
  EXPECT_EQ(s21_arr_5.empty(), std_arr_5.empty());

  s21::array<int, 0> s21_arr_0;
  std::array<int, 0> std_arr_0;
  EXPECT_EQ(s21_arr_0.empty(), std_arr_0.empty());

  const s21::array<int, 1> s21_arr_c = {5};
  const std::array<int, 1> std_arr_c = {5};
  EXPECT_EQ(s21_arr_c.empty(), std_arr_c.empty());
}

TEST(Array, test_swap) {
  std::array<std::string, 3> std_arr_1 = {"1", "2", "3"};
  std::array<std::string, 3> std_arr_2 = {"4", "5", "6"};

  std_arr_1.swap(std_arr_2);
  EXPECT_EQ(std_arr_1[0], "4");
  EXPECT_EQ(std_arr_1[1], "5");
  EXPECT_EQ(std_arr_1[2], "6");
  EXPECT_EQ(std_arr_2[0], "1");
  EXPECT_EQ(std_arr_2[1], "2");
  EXPECT_EQ(std_arr_2[2], "3");
  EXPECT_EQ(std_arr_2.size(), std_arr_1.size());

  s21::array<std::string, 3> arr_1 = {"1", "2", "3"};
  s21::array<std::string, 3> arr_2 = {"4", "5", "6"};

  arr_1.swap(arr_2);
  EXPECT_EQ(arr_1[0], "4");
  EXPECT_EQ(arr_1[1], "5");
  EXPECT_EQ(arr_1[2], "6");
  EXPECT_EQ(arr_2[0], "1");
  EXPECT_EQ(arr_2[1], "2");
  EXPECT_EQ(arr_2[2], "3");
  EXPECT_EQ(arr_2.size(), arr_1.size());
}

TEST(Array, test_fill) {
  std::array<std::string, 3> std_arr_1 = {"1", "2", "3"};
  std_arr_1.fill("AAA");
  EXPECT_EQ(std_arr_1[0], "AAA");
  EXPECT_EQ(std_arr_1[1], "AAA");
  EXPECT_EQ(std_arr_1[2], "AAA");

  s21::array<std::string, 3> s21_arr_1 = {"1", "2", "3"};
  s21_arr_1.fill("AAA");
  EXPECT_EQ(s21_arr_1[0], "AAA");
  EXPECT_EQ(s21_arr_1[1], "AAA");
  EXPECT_EQ(s21_arr_1[2], "AAA");
}