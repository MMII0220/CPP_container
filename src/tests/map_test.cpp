#include <gtest/gtest.h>

#include <map>

#include "./../s21_containers/s21_container.hpp"

TEST(map_test, def_constructor) {
  const s21::map<int, int> t;
  int i = t.size();
  EXPECT_EQ(i, 0);
}

TEST(map_test, const_init_constructor_wout_clone) {
  const s21::map<int, int> t = {{1, 2}, {3, 4}, {5, 6}};
  auto it = t.begin();
  int siz = t.size();
  int arr_key[3] = {1, 3, 5};
  int arr_value[3] = {2, 4, 6};

  for (int i = 0; it != t.end(); ++it, i++) {
    EXPECT_EQ(it->first, arr_key[i]);
    EXPECT_EQ(it->second, arr_value[i]);
  }
  EXPECT_EQ(siz, 3);
}

TEST(map_test, init_constructor_wout_clone) {
  s21::map<int, int> t = {{1, 2}, {3, 4}, {5, 6}};
  auto it = t.begin();
  int siz = t.size();
  int arr_key[3] = {1, 3, 5};
  int arr_value[3] = {2, 4, 6};

  for (int i = 0; it != t.end(); it++, i++) {
    EXPECT_EQ(it->first, arr_key[i]);
    EXPECT_EQ(it->second, arr_value[i]);
  }
  EXPECT_EQ(siz, 3);
}

TEST(map_test, init_constructor_with_clone) {
  s21::map<int, int> t = {{1, 2}, {3, 4}, {5, 6}, {5, 10}};
  auto it = t.begin();
  int siz = t.size();
  int arr_key[3] = {1, 3, 5};
  int arr_value[3] = {2, 4, 6};

  for (int i = 0; it != t.end(); it++, i++) {
    EXPECT_EQ(it->first, arr_key[i]);
    EXPECT_EQ(it->second, arr_value[i]);
  }
  EXPECT_EQ(siz, 3);
}

TEST(map_test, copy_constructor) {
  s21::map<int, int> k = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> t(k);
  auto it = t.begin();
  int siz = t.size();
  int arr_key[3] = {1, 3, 5};
  int arr_value[3] = {2, 4, 6};

  for (int i = 0; it != t.end(); it++, i++) {
    EXPECT_EQ(it->first, arr_key[i]);
    EXPECT_EQ(it->second, arr_value[i]);
  }
  EXPECT_EQ(siz, 3);
}

TEST(map_test, move_constructor) {
  s21::map<int, int> k = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> t(std::move(k));
  auto it = t.begin();
  int siz = t.size();
  int arr_key[3] = {1, 3, 5};
  int arr_value[3] = {2, 4, 6};
  for (int i = 0; it != t.end(); it++, i++) {
    EXPECT_EQ(it->first, arr_key[i]);
    EXPECT_EQ(it->second, arr_value[i]);
  }
  EXPECT_EQ(siz, 3);
  siz = k.size();
  EXPECT_EQ(siz, 0);
}

TEST(map_test, operator_eq_move) {
  s21::map<int, char> k = {{1, 'A'}, {3, 'B'}, {5, 'C'}, {10, 'G'}};
  s21::map<int, char> t = {{2, 'd'}, {4, 'e'}, {6, 'f'}};
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
  int arr_valueT[4] = {'A', 'B', 'C', 'G'};

  int arr_keyK[3] = {2, 4, 6};
  int arr_valueK[3] = {'d', 'e', 'f'};

  for (int i = 0; itT != t.end(); itT++, i++) {
    EXPECT_EQ((*itT).first, arr_keyT[i]);
    EXPECT_EQ((*itT).second, arr_valueT[i]);
  }
  for (int i = 0; itK != t.end(); itK++, i++) {
    EXPECT_EQ((*itK).first, arr_keyK[i]);
    EXPECT_EQ((*itK).second, arr_valueK[i]);
  }

  EXPECT_EQ(sizeT, 4);
  EXPECT_EQ(sizeK, 3);
}

TEST(map_test, insert_pair) {
  s21::map<int, char> t;
  auto tmp = std::make_pair(3, 'A');
  auto res = t.insert(tmp);
  auto it = res.first;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, 'A');
  EXPECT_EQ(res.second, true);

  tmp = std::make_pair(1, 'B');
  res = t.insert(tmp);
  it = res.first;
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 'B');
  EXPECT_EQ(res.second, true);
  int SIZE = t.size();
  EXPECT_EQ(SIZE, 2);

  tmp = std::make_pair(1, 'C');
  res = t.insert(tmp);
  it = res.first;
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 'B');
  EXPECT_EQ(res.second, false);
  SIZE = t.size();
  EXPECT_EQ(SIZE, 2);

  tmp = std::make_pair(5, 'D');
  res = t.insert(tmp);
  it = res.first;
  EXPECT_EQ(it->first, 5);
  EXPECT_EQ(it->second, 'D');
  EXPECT_EQ(res.second, true);
  SIZE = t.size();
  EXPECT_EQ(SIZE, 3);
}

TEST(map_test, insert_splice) {
  s21::map<int, char> t;
  auto res = t.insert(3, 'A');
  auto it = res.first;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, 'A');
  EXPECT_EQ(res.second, true);

  res = t.insert(1, 'B');
  it = res.first;
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 'B');
  EXPECT_EQ(res.second, true);
  int SIZE = t.size();
  EXPECT_EQ(SIZE, 2);

  res = t.insert(1, 'C');
  it = res.first;
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 'B');
  EXPECT_EQ(res.second, false);
  SIZE = t.size();
  EXPECT_EQ(SIZE, 2);

  res = t.insert(5, 'D');
  it = res.first;
  EXPECT_EQ(it->first, 5);
  EXPECT_EQ(it->second, 'D');
  EXPECT_EQ(res.second, true);
  SIZE = t.size();
  EXPECT_EQ(SIZE, 3);
}

TEST(map_test, insert_or_assign) {
  s21::map<int, char> t;
  auto res = t.insert_or_assign(3, 'A');
  auto it = res.first;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, 'A');
  EXPECT_EQ(res.second, true);

  res = t.insert_or_assign(1, 'B');
  it = res.first;
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 'B');
  EXPECT_EQ(res.second, true);
  int SIZE = t.size();
  EXPECT_EQ(SIZE, 2);

  res = t.insert_or_assign(1, 'C');
  it = res.first;
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 'C');
  EXPECT_EQ(res.second, false);
  SIZE = t.size();
  EXPECT_EQ(SIZE, 2);
}

TEST(map_test, erase) {
  s21::map<int, char> t = {
      {15, 'A'}, {2, 'B'},  {28, 'C'}, {20, 'D'}, {30, 'E'},
      {40, 'F'}, {35, 'G'}, {17, 'H'}, {18, 'I'}, {1, 'J'},
      {4, 'K'},  {5, 'L'},  {40, 'M'},
  };
  auto j = t.begin();
  for (int i = 0; i < 11; i++) {
    j++;
  }
  int size_before = t.size();
  t.erase(j);
  int size_after = t.size();
  EXPECT_EQ(size_after, size_before - 1);
}

TEST(map_test, clear) {
  s21::map<int, int> t = {{1, 2}, {3, 4}, {5, 6}};
  t.clear();
  auto it = t.GetRoot();
  EXPECT_EQ(it, nullptr);
  int i = t.size();
  EXPECT_EQ(i, 0);
}

TEST(map_test, empty_true) {
  s21::map<int, char> t;
  EXPECT_EQ(t.empty(), true);

  const s21::map<int, char> t_const;
  EXPECT_EQ(t_const.empty(), true);
}

TEST(map_test, empty_false) {
  s21::map<int, char> t = {{1, 'A'}, {3, 'B'}, {5, 'C'}};
  EXPECT_EQ(t.empty(), false);

  const s21::map<int, char> t_const = {{1, 'A'}, {3, 'B'}, {5, 'C'}};
  EXPECT_EQ(t_const.empty(), false);
}

TEST(map_test, size) {
  s21::map<int, char> t = {{1, 'A'}, {3, 'B'}, {5, 'C'}};
  size_t tt = t.size();
  size_t orig = 3;
  EXPECT_EQ(tt, orig);
}

TEST(map_test, max_size) {
  s21::map<int, char> t = {{1, 'A'}, {3, 'B'}, {5, 'C'}};
  s21::map<int, char> tt = {{1, 'A'}, {3, 'B'}, {5, 'C'}};
  EXPECT_EQ(t.max_size(), tt.max_size());
}

TEST(map_test, at) {
  s21::map<int, char> t = {{1, 'A'}, {3, 'B'}, {5, 'C'}};
  EXPECT_EQ(t.at(1), 'A');
  EXPECT_ANY_THROW(t.at(15));
}

TEST(map_test, operator_square) {
  s21::map<int, char> t = {{1, 'A'}, {3, 'B'}, {5, 'C'}};
  EXPECT_EQ(t[1], 'A');
  EXPECT_EQ(t[15], 0);
}

TEST(map_test, insert_many) {
  s21::map<int, char> t;
  auto result = t.insert_many(std::make_pair(2, 'A'), std::make_pair(3, 'B'),
                              std::make_pair(1, 'C'), std::make_pair(2, 'C'));
  int arr[4] = {2, 3, 1, 2};
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(result[i].first.GetNode()->GetKey().first, arr[i]);
    EXPECT_EQ(result[i].second, true);
  }
  EXPECT_EQ(result[3].second, false);
}