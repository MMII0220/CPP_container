#pragma once

#include "s21_AVLTree.hpp"

namespace s21 {

template <typename Key>
class ComparatorSet {
 public:
  bool operator()(const Key& a, const Key& b) const { return a > b; }

  bool equal(const Key& a, const Key& b) const { return a == b; }
};

template <typename Key, typename Comparator = ComparatorSet<Key>>
class set : public AVLTree<Key, Comparator> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename set::AVLTree::TreeIterator;
  using size_type = size_t;

 public:
  // ========================== * Constructors* ==========================
  //  Default constructor
  set() : AVLTree<Key, Comparator>() {}

  //  Initianal list constructor
  set(std::initializer_list<value_type> const& items) {
    for (auto i = items.begin(); i != items.end(); i++) {
      this->insert(*i);
    }
  }
};

}  // namespace s21