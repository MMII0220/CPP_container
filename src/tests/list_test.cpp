#include <gtest/gtest.h>

#include <list>

// #include "./s21_containers/list/s21_list.tpp"
#include "./../s21_containers/s21_container.hpp"

template <typename T>
bool compare_lists(s21::list<T> my_list, std::list<T> std_list) {
  bool result = true;
  if (my_list.size() == std_list.size()) {
    auto my_it = my_list.begin();
    auto std_it = std_list.begin();
    for (size_t i = 0; i != my_list.size(); ++i) {
      if (*my_it != *std_it) {
        result = false;
        break;
      }
      my_it++;
      std_it++;
    }
  } else {
    result = false;
  }
  return result;
}

// Constructors
TEST(ListAllTests, initialize_list_test) {
  s21::list<int> s21_v;
  size_t sz = s21_v.getSize();
  EXPECT_EQ(sz, 0);
}
TEST(ListAllTests, initialize_with_size_list) {
  s21::list<int> s21_v(2);
  EXPECT_EQ(s21_v.size(), 2);
}
TEST(ListAllTests, initialize_with_values_list) {
  s21::list<int> s21_v = {1, 2, 3, 4};
  EXPECT_EQ(s21_v.size(), 4);
}
TEST(ListAllTests, copy_list) {
  s21::list<int> s21_v1 = {1, 2, 3};
  s21::list<int> s21_v2(s21_v1);
  EXPECT_EQ(s21_v1.getSize(), 3);
  EXPECT_EQ(s21_v2.getSize(), 3);
}
TEST(ListAllTests, copy_list_operator) {
  s21::list<int> s21_v1 = {1, 2, 3};
  s21::list<int> s21_v2 = s21_v1;
  EXPECT_EQ(s21_v1.getSize(), 3);
  EXPECT_EQ(s21_v2.getSize(), 3);
}
TEST(ListAllTests, move_list) {
  s21::list<int> s21_v1 = {1, 2, 3};
  s21::list<int> s21_v2(std::move(s21_v1));
  EXPECT_EQ(s21_v1.size(), 0);
  EXPECT_EQ(s21_v2.size(), 3);
}

// Element Access
TEST(ListAllTests, element_access_list) {
  s21::list<int> s21_l = {1, 2, 3, 4};
  std::list<int> std_l = {1, 2, 3, 4};
  EXPECT_EQ(s21_l.front(), 1);
  EXPECT_EQ(s21_l.back(), 4);

  EXPECT_EQ(std_l.front(), 1);
  EXPECT_EQ(std_l.back(), 4);
}

// List Capacity
TEST(ListAllTests, empty_list_false) {
  s21::list<int> s21_l = {1, 2, 3, 4};
  std::list<int> std_l = {1, 2, 3, 4};
  EXPECT_FALSE(s21_l.empty());
  EXPECT_FALSE(std_l.empty());
}
TEST(ListAllTests, empty_list_true) {
  s21::list<int> s21_l;
  std::list<int> std_l;
  EXPECT_TRUE(s21_l.empty());
  EXPECT_TRUE(std_l.empty());
}
TEST(ListAllTests, size_list_test) {
  s21::list<int> s21_l = {1, 2, 3, 4};
  std::list<int> std_l = {1, 2, 3, 4};
  EXPECT_EQ(s21_l.size(), 4);
  EXPECT_EQ(std_l.size(), 4);
}

// List Modifiers
TEST(ListAllTests, clear_list) {
  s21::list<int> s21_l = {1, 2, 3, 4};
  std::list<int> std_l = {1, 2, 3, 4};
  s21_l.clear();
  std_l.clear();
  EXPECT_EQ(s21_l.size(), 0);
  EXPECT_EQ(std_l.size(), 0);
}
TEST(ListAllTests, push_list) {
  s21::list<int> s21_l = {1, 2};
  std::list<int> std_l = {1, 2};
  s21_l.push_back(3);
  s21_l.push_front(0);
  std_l.push_back(3);
  std_l.push_front(0);
  EXPECT_EQ(s21_l.size(), 4);
  EXPECT_EQ(std_l.size(), 4);
  EXPECT_TRUE(compare_lists(s21_l, std_l));
}
TEST(ListAllTests, pop_list) {
  s21::list<int> s21_l = {1, 2};
  std::list<int> std_l = {1, 2};
  s21_l.pop_back();
  s21_l.pop_front();
  std_l.pop_back();
  std_l.pop_front();
  EXPECT_EQ(s21_l.size(), 0);
  EXPECT_EQ(std_l.size(), 0);
  EXPECT_TRUE(compare_lists(s21_l, std_l));
}
TEST(ListAllTests, swap_list) {
  s21::list<int> s21_l1 = {1, 2};
  s21::list<int> s21_l2 = {3, 4, 5};
  std::list<int> std_l = {3, 4, 5};
  s21_l1.swap(s21_l2);
  EXPECT_EQ(s21_l1.size(), 3);
  EXPECT_EQ(s21_l2.size(), 2);
  EXPECT_TRUE(compare_lists(s21_l1, std_l));
}
TEST(ListAllTests, merge_list) {
  s21::list<int> s21_l1 = {1, 2};
  s21::list<int> s21_l2 = {3, 4, 5};
  std::list<int> std_l = {1, 2, 3, 4, 5};
  s21_l1.merge(s21_l2);
  EXPECT_EQ(s21_l1.size(), 5);
  EXPECT_EQ(s21_l2.size(), 0);
  EXPECT_TRUE(compare_lists(s21_l1, std_l));
}
TEST(ListAllTests, reverse_list) {
  s21::list<int> s21_l1 = {1, 2};
  std::list<int> s21_l2 = {2, 1};
  s21_l1.reverse();
  EXPECT_TRUE(compare_lists(s21_l1, s21_l2));
}
TEST(ListAllTests, sort_list) {
  s21::list<int> s21_l1 = {5, 4, 3, 2, 1};
  std::list<int> s21_l2 = {1, 2, 3, 4, 5};
  s21_l1.sort();
  EXPECT_TRUE(compare_lists(s21_l1, s21_l2));
}
TEST(ListAllTests, unique_list) {
  s21::list<int> s21_l1 = {1, 2, 2, 2, 2, 3};
  std::list<int> s21_l2 = {1, 2, 3};
  s21_l1.unique();
  EXPECT_EQ(s21_l1.size(), 3);
  EXPECT_TRUE(compare_lists(s21_l1, s21_l2));
}
TEST(ListAllTests, insert_list) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}
TEST(ListAllTests, erase_list) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.erase(my_list1.begin());

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.erase(std_list1.begin());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}
TEST(ListAllTests, splice_list) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

// throws
TEST(ListAllTests, throw_constructor) {
  try {
    s21::list<int> s21_l(-1);
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Limit of the container is exceeded"));
  }
}
TEST(ListAllTests, throw_pop) {
  try {
    s21::list<int> s21_l;
    s21_l.pop_back();
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("zsh: abort: list is empty"));
  }
}
TEST(ListAllTests, throw_pop_front) {
  try {
    s21::list<int> s21_l;
    s21_l.pop_front();
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("list is empty"));
  }
}