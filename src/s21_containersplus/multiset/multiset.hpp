#pragma once

// #include "../containers/s21_AVLTree.h"
// #include "./tree/s21_AVLTree.hpp"
// #include "./../tree/s21_AVLTree.hpp"
#include "./../../s21_containers/tree/s21_AVLTree.hpp"
namespace s21 {

template <typename Key>
class ComparatorMultiSet {
 public:
  bool operator()(const Key& a, const Key& b) const { return a >= b; }

  bool equal(const Key& a, const Key& b) const { return a == b; }
};

template <typename Key, typename Comparator = ComparatorMultiSet<Key>>
class multiset : public AVLTree<Key, Comparator> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename multiset::AVLTree::TreeIterator;
  using const_iterator = typename multiset::AVLTree::ConstTreeIterator;
  using Node_ptr = typename multiset::AVLTree::Node*;
  using size_type = size_t;

 public:
  //  Default constructor
  multiset() : AVLTree<Key, Comparator>() {}

  //  Initianal list constructor
  multiset(std::initializer_list<value_type> const& items) {
    for (auto i = items.begin(); i != items.end(); i++) {
      this->insert(*i);
    }
  }

  void merge(AVLTree<Key, Comparator>& other) override {
    for (auto it = other.begin(); it != other.end(); it++) {
      insert(*it);
    }
    other.clear();
  }

  iterator insert(const value_type& value) {
    auto root = this->GetRoot();
    Node_ptr res = this->insert_tree(root, value);
    return iterator(res, root);
  }

  //   const_iterator insert(const value_type& value) const {
  //     auto root = this->GetRoot();
  //     Node_ptr res = this->insert_tree(root, value);
  //     return const_iterator(res, root);
  //   }

  size_type count(const Key& key) const {
    size_type cnt = 0;
    if (this->root_ != nullptr) {
      this->count_helper(this->root_, key, cnt);
    }
    return cnt;
  }

  iterator lower_bound(const Key& key) {
    for (iterator it = this->begin(); it != this->end(); ++it) {
      if (*it >= key) return it;
    }
    return iterator(nullptr, this->root_);
  }

  const_iterator lower_bound(const Key& key) const {
    for (const_iterator it = this->begin(); it != this->end(); ++it) {
      if (*it >= key) return it;
    }
    return const_iterator(nullptr, this->root_);
  }

  iterator upper_bound(const Key& key) {
    for (iterator it = this->begin(); it != this->end(); ++it) {
      if (*it > key) return it;
    }
    return iterator(nullptr, this->root_);
  }

  const_iterator upper_bound(const Key& key) const {
    for (const_iterator it = this->begin(); it != this->end(); ++it) {
      if (*it > key) return it;
    }
    return const_iterator(nullptr, this->root_);
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return std::make_pair(this->lower_bound(key), this->upper_bound(key));
  }

  // Support
 private:
  void count_helper(Node_ptr node, const Key& key, size_type& i) const {
    if (node != nullptr) {
      if (key == node->GetKey()) ++i;
      count_helper(node->left, key, i);
      count_helper(node->right, key, i);
    }
  }

  // insert
};

}  // namespace s21