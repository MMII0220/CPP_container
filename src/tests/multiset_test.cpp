#include <gtest/gtest.h>

#include <set>

// #include "./s21_containers/list/s21_list.tpp"
#include "./../s21_containersplus/s21_containersplus.hpp"

TEST(multiset_test, def_constructor) {
  s21::multiset<int> t;
  EXPECT_EQ(t.empty(), true);
  auto ref = t.insert(15);
  EXPECT_EQ(*ref, 15);
  ref = t.insert(2);
  EXPECT_EQ(*ref, 2);
  ref = t.insert(28);
  EXPECT_EQ(*ref, 28);
  ref = t.insert(20);
  EXPECT_EQ(*ref, 20);
  ref = t.insert(30);
  EXPECT_EQ(*ref, 30);
  ref = t.insert(40);
  EXPECT_EQ(*ref, 40);
  ref = t.insert(35);
  EXPECT_EQ(*ref, 35);
  ref = t.insert(35);
  EXPECT_EQ(*ref, 35);
  const s21::multiset<int> t_const;
  size_t result = t_const.size();
  size_t answer = 0;
  EXPECT_EQ(result, answer);
  EXPECT_EQ(t_const.empty(), true);
}

TEST(multiset_test, init_constructor) {
  const s21::multiset<int> t_zero = {};
  size_t answer = 0;
  EXPECT_EQ(t_zero.size(), answer);
  EXPECT_EQ(t_zero.empty(), true);

  const s21::multiset<int> t = {15, 2, 28, 20, 30, 30, 2};
  int i = 0;
  int arr_true[]{28, 15, 2, 2, 20, 30, 30};
  int arr_orig[7]{0};
  t.import(t.GetRoot(), arr_orig, i);
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(arr_true[i], arr_orig[i]);
  }

  const s21::multiset<int> t_const = {1, 2, 2, 2, 2};
  size_t result = t_const.size();
  answer = 5;
  EXPECT_EQ(result, answer);
}

TEST(multiset_test, copy_constructor) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35};
  s21::multiset<int> res(t);
  int arr_true[7]{28, 15, 2, 20, 35, 30, 40};
  int arr_orig[7]{0};
  int i = 0;
  res.import(res.GetRoot(), arr_orig, i);
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(arr_true[i], arr_orig[i]);
  }
}

TEST(multiset_test, operator_eq_copy) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35};
  s21::multiset<int> res;
  res = t;
  int arr_true[7]{28, 15, 2, 20, 35, 30, 40};
  int arr_orig[7]{0};
  int i = 0;
  res.import(res.GetRoot(), arr_orig, i);
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(arr_true[i], arr_orig[i]);
  }
}

TEST(multiset_test, move_constructor) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35};
  s21::multiset<int> res(std::move(t));
  int arr_true[7]{28, 15, 2, 20, 35, 30, 40};
  int arr_orig[7]{0};
  int i = 0;
  res.import(res.GetRoot(), arr_orig, i);
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(arr_true[i], arr_orig[i]);
  }
  EXPECT_EQ(t.GetRoot(), nullptr);
}

TEST(multiset_test, operator_eq_move) {
  s21::multiset<int> k = {1, 3, 5, 10};
  s21::multiset<int> t = {2, 4, 6};

  int sizeT = t.size();
  EXPECT_EQ(sizeT, 3);
  int sizeK = k.size();
  EXPECT_EQ(sizeK, 4);

  t = std::move(k);

  auto itT = t.begin();
  auto itK = k.begin();

  sizeT = t.size();
  sizeK = k.size();

  int arr_keyT[4] = {1, 3, 5, 10};

  int arr_keyK[3] = {2, 4, 6};

  for (int i = 0; itT != t.end(); itT++, i++) {
    EXPECT_EQ((*itT), arr_keyT[i]);
  }

  for (int i = 0; itK != t.end(); itK++, i++) {
    EXPECT_EQ((*itK), arr_keyK[i]);
  }

  EXPECT_EQ(sizeT, 4);
  EXPECT_EQ(sizeK, 3);
}

TEST(multiset_test, size) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35};
  size_t tt = t.size();
  size_t orig = 7;
  EXPECT_EQ(tt, orig);
}

TEST(multiset_test, max_size) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35};
  s21::multiset<int> tt = {15, 2, 28, 20, 30, 40, 35};
  EXPECT_EQ(t.max_size(), tt.max_size());
}

TEST(multiset_test, empty_true) {
  s21::multiset<int> t;
  EXPECT_EQ(t.empty(), true);

  const s21::multiset<int> t_const;
  EXPECT_EQ(t_const.empty(), true);
}

TEST(multiset_test, empty_false) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35};
  EXPECT_EQ(t.empty(), false);

  const s21::multiset<int> t_const = {15, 2, 28, 20, 30, 40, 35};
  EXPECT_EQ(t_const.empty(), false);
}

TEST(multiset_test, erase) {
  s21::multiset<int> t_zero = {};
  size_t answer = 0;
  EXPECT_EQ(t_zero.size(), answer);
  EXPECT_EQ(t_zero.empty(), true);

  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5};
  int i = 0;
  int arr_true[]{15, 2, 1, 4, 5, 28, 18, 17, 20, 35, 30};
  int arr_orig[11]{0};
  auto j = t.end();
  t.erase(--j);
  t.import(t.GetRoot(), arr_orig, i);
  for (int i = 0; i < 11; i++) {
    EXPECT_EQ(arr_true[i], arr_orig[i]);
  }
}

TEST(multiset_test, find_true) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  auto it = t.find(30);
  EXPECT_EQ(*it, 30);
}

TEST(multiset_test, const_find_true) {
  const s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  auto it = t.find(30);
  EXPECT_EQ(*it, 30);
}

TEST(multiset_test, find_false) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  auto it = t.find(32);
  EXPECT_EQ(it.GetNode(), nullptr);
}

TEST(multiset_test, contains_true) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  bool it = t.contains(30);
  EXPECT_EQ(it, true);
}

TEST(multiset_test, contains_false) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  bool it = t.contains(32);
  EXPECT_EQ(it, false);
  t.clear();
  EXPECT_EQ(it, false);
}

TEST(multiset_test, clear) {
  s21::multiset<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  t.clear();
  auto it = t.GetRoot();
  EXPECT_EQ(it, nullptr);
  int i = t.size();
  EXPECT_EQ(i, 0);
}

TEST(multiset_test, merge) {
  s21::multiset<char> t = {'C', 'B', 'B', 'A'};
  s21::multiset<char> k = {'E', 'D', 'E', 'C'};

  t.merge(k);
  auto it = t.begin();
  char arr_true[]{'A', 'B', 'B', 'C', 'C', 'D', 'E', 'E'};
  for (int i = 0; i < 7; i++, it++) {
    EXPECT_EQ(arr_true[i], *it);
  }
}

TEST(multiset_test, insert_many) {
  s21::multiset<int> t;
  auto result = t.insert_many(15, 2, 28, 20, 30, 30);
  int arr[6] = {15, 2, 28, 20, 30, 30};
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(result[i].first.GetNode()->GetKey(), arr[i]);
    EXPECT_EQ(result[i].second, true);
  }
  EXPECT_EQ(result[5].second, false);
}

TEST(multiset_test, count) {
  s21::multiset<int> t = {15, 2, 40, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40, 40};
  int res = t.count(40);
  EXPECT_EQ(res, 4);
}

TEST(multiset_test, lower_bound) {
  s21::multiset<int> t = {15, 2, 20, 30, 35, 17, 18, 1, 4, 5, 40, 40};
  auto it = t.begin();
  it = it + 4;
  auto res = t.lower_bound(6);
  EXPECT_EQ(it == res, 1);
}

TEST(multiset_test, lower_bound_const) {
  const s21::multiset<int> t = {15, 2, 20, 30, 35, 17, 18, 1, 4, 5, 40, 40};
  auto it = t.begin();
  it = it + 4;
  auto res = t.lower_bound(6);
  EXPECT_EQ(it == res, 1);
}

TEST(multiset_test, upper_bound) {
  s21::multiset<int> t = {15, 2, 20, 30, 35, 17, 18, 1, 4, 5, 5, 5, 40, 40};
  auto it = t.begin();
  it = it + 6;
  auto res = t.upper_bound(5);
  EXPECT_EQ(it == res, 1);
}

TEST(multiset_test, equal_bound) {
  s21::multiset<int> t = {15, 2, 20, 30, 35, 17, 18, 1, 4, 5, 5, 5, 40, 40};
  auto it = t.begin();
  auto it_first = it + 3;
  auto it_second = it + 6;
  auto res = t.equal_range(5);
  EXPECT_EQ(res.first, it_first);
  EXPECT_EQ(res.second, it_second);
}