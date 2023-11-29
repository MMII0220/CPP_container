#include <gtest/gtest.h>

#include <set>

#include "./../s21_containers/s21_container.hpp"

TEST(set_test, def_constructor) {
  s21::set<int> t;
  EXPECT_EQ(t.empty(), true);
  auto ref = t.insert(15);
  EXPECT_EQ(ref.second, true);
  EXPECT_EQ(ref.first.GetNode()->GetKey(), 15);
  ref = t.insert(2);
  EXPECT_EQ(ref.second, true);
  EXPECT_EQ(ref.first.GetNode()->GetKey(), 2);
  ref = t.insert(28);
  EXPECT_EQ(ref.second, true);
  EXPECT_EQ(ref.first.GetNode()->GetKey(), 28);
  ref = t.insert(20);
  EXPECT_EQ(ref.second, true);
  EXPECT_EQ(ref.first.GetNode()->GetKey(), 20);
  ref = t.insert(30);
  EXPECT_EQ(ref.second, true);
  EXPECT_EQ(ref.first.GetNode()->GetKey(), 30);
  ref = t.insert(40);
  EXPECT_EQ(ref.second, true);
  EXPECT_EQ(ref.first.GetNode()->GetKey(), 40);
  ref = t.insert(35);
  EXPECT_EQ(ref.second, true);
  EXPECT_EQ(ref.first.GetNode()->GetKey(), 35);
  ref = t.insert(35);
  EXPECT_EQ(ref.first.GetNode()->GetKey(), 35);
  EXPECT_EQ(ref.second, false);

  const s21::set<int> t_const;
  size_t result = t_const.size();
  size_t answer = 0;
  EXPECT_EQ(result, answer);
  EXPECT_EQ(t_const.empty(), true);
}

TEST(set_test, init_constructor) {
  const s21::set<int> t_zero = {};
  size_t answer = 0;
  EXPECT_EQ(t_zero.size(), answer);
  EXPECT_EQ(t_zero.empty(), true);

  const s21::set<int> t = {15, 2, 28, 20, 30, 40, 35};
  int i = 0;
  int arr_true[7]{28, 15, 2, 20, 35, 30, 40};
  int arr_orig[7]{0};
  t.import(t.GetRoot(), arr_orig, i);
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(arr_true[i], arr_orig[i]);
  }

  const s21::set<int> t_const = {1, 2, 2, 2, 2};
  size_t result = t_const.size();
  answer = 2;
  EXPECT_EQ(result, answer);
  answer = 2;
  result = t_const.GetRoot()->GetRight()->GetKey();
  EXPECT_EQ(result, answer);
}

TEST(set_test, copy_constructor) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35};
  s21::set<int> res(t);
  int arr_true[7]{28, 15, 2, 20, 35, 30, 40};
  int arr_orig[7]{0};
  int i = 0;
  res.import(res.GetRoot(), arr_orig, i);
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(arr_true[i], arr_orig[i]);
  }
}

TEST(set_test, operator_eq_copy) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35};
  s21::set<int> res;
  res = t;
  int arr_true[7]{28, 15, 2, 20, 35, 30, 40};
  int arr_orig[7]{0};
  int i = 0;
  res.import(res.GetRoot(), arr_orig, i);
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(arr_true[i], arr_orig[i]);
  }
}

TEST(set_test, move_constructor) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35};
  s21::set<int> res(std::move(t));
  int arr_true[7]{28, 15, 2, 20, 35, 30, 40};
  int arr_orig[7]{0};
  int i = 0;
  res.import(res.GetRoot(), arr_orig, i);
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(arr_true[i], arr_orig[i]);
  }
  EXPECT_EQ(t.GetRoot(), nullptr);
}

TEST(set_test, operator_eq_move) {
  s21::set<int> k = {1, 3, 5, 10};
  s21::set<int> t = {2, 4, 6};

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

TEST(set_test, size) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35};
  size_t tt = t.size();
  size_t orig = 7;
  EXPECT_EQ(tt, orig);
}

TEST(set_test, max_size) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35};
  s21::set<int> tt = {15, 2, 28, 20, 30, 40, 35};
  EXPECT_EQ(t.max_size(), tt.max_size());
}

TEST(set_test, empty_true) {
  s21::set<int> t;
  EXPECT_EQ(t.empty(), true);

  const s21::set<int> t_const;
  EXPECT_EQ(t_const.empty(), true);
}

TEST(set_test, empty_false) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35};
  EXPECT_EQ(t.empty(), false);

  const s21::set<int> t_const = {15, 2, 28, 20, 30, 40, 35};
  EXPECT_EQ(t_const.empty(), false);
}

TEST(set_test, erase) {
  s21::set<int> t_zero = {};
  size_t answer = 0;
  EXPECT_EQ(t_zero.size(), answer);
  EXPECT_EQ(t_zero.empty(), true);

  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  int i = 0;
  int arr_true[11]{15, 2, 1, 4, 5, 28, 18, 17, 20, 35, 30};
  int arr_orig[11]{0};

  auto j = t.end();
  t.erase(--j);
  t.import(t.GetRoot(), arr_orig, i);
  for (int i = 0; i < 11; i++) {
    EXPECT_EQ(arr_true[i], arr_orig[i]);
  }

  s21::set<int> tt = {2, 1};
  auto iter = tt.find(2);
  tt.erase(iter);
  EXPECT_EQ(*(tt.begin()), 1);
}

TEST(set_test, find_true) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  auto it = t.find(30);
  EXPECT_EQ(*it, 30);
}

TEST(set_test, const_find_true) {
  const s21::set<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  auto it = t.find(30);
  EXPECT_EQ(*it, 30);
}

TEST(set_test, find_false) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  auto it = t.find(32);
  EXPECT_EQ(it.GetNode(), nullptr);
}

TEST(set_test, contains_true) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  bool it = t.contains(30);
  EXPECT_EQ(it, true);
}

TEST(set_test, contains_false) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  bool it = t.contains(32);
  EXPECT_EQ(it, false);
  t.clear();
  EXPECT_EQ(it, false);
}

TEST(set_test, clear) {
  s21::set<int> t = {15, 2, 28, 20, 30, 40, 35, 17, 18, 1, 4, 5, 40};
  t.clear();
  auto it = t.GetRoot();
  EXPECT_EQ(it, nullptr);
  int i = t.size();
  EXPECT_EQ(i, 0);
}

TEST(set_test, merge) {
  s21::set<char> t = {'C', 'B', 'B', 'A'};
  s21::set<char> k = {'E', 'D', 'E', 'C'};

  t.merge(k);
  auto it = t.begin();
  char arr_true[5]{'A', 'B', 'C', 'D', 'E'};
  for (int i = 0; i < 5; i++, it++) {
    EXPECT_EQ(arr_true[i], *it);
  }
}

TEST(set_test, insert_many) {
  s21::set<int> t;
  auto result = t.insert_many(15, 2, 28, 20, 30, 30);
  int arr[6] = {15, 2, 28, 20, 30, 30};
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(result[i].first.GetNode()->GetKey(), arr[i]);
    EXPECT_EQ(result[i].second, true);
  }
  EXPECT_EQ(result[5].second, false);
}