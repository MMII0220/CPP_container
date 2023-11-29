#pragma once

#include "s21_AVLTree.hpp"

namespace s21 {

template <typename Key>
class ComparatorMap {
 public:
  bool operator()(const Key& a, const Key& b) const {
    return a.first > b.first;
  }
  bool equal(const Key& a, const Key& b) const { return a.first == b.first; }
};

template <typename Key, typename Value,
          typename Comparator = ComparatorMap<std::pair<Key, Value>>>
class map : public AVLTree<std::pair<const Key, Value>, Comparator> {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator =
      typename AVLTree<std::pair<const Key, Value>, Comparator>::TreeIterator;
  using size_type = size_t;

  // ========================== * Constructors* ==========================

  map() : AVLTree<std::pair<const Key, Value>, Comparator>() {}
  map(std::initializer_list<value_type> const& items) {
    for (auto i = items.begin(); i != items.end(); i++) {
      this->insert(*i);
    }
  }

  // ========================== *Accessors* ==========================

  mapped_type& at(const mapped_type& key) {
    auto current = this->GetRoot();
    while (current) {
      if (key == current->GetKey().first) {
        return current->GetKey().second;
      } else if (current->GetKey().first > key) {
        current = current->GetLeft();
      } else {
        current = current->GetRight();
      }
    }
    throw std::out_of_range("Key not found in the tree");
  }

  mapped_type& operator[](const mapped_type& key) {
    try {
      return this->at(key);
    } catch (const std::out_of_range& ex) {
      auto it = this->insert(key, Value());
      auto res = it.first;
      return (*res).second;
    }
  }

  // ========================== *Main* ==========================

  std::pair<iterator, bool> insert(const value_type& key) {
    return AVLTree<std::pair<const Key, Value>, Comparator>::insert(key);
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    return map::AVLTree::insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    if (this->empty()) {
      return map::AVLTree::insert(std::make_pair(key, obj));
    } else {
      auto i = this->begin();
      for (; i != this->end(); ++i) {
        if (i->first == key) {
          i->second = obj;
          return std::make_pair(i, false);
        }
      }
      return map::AVLTree::insert(std::make_pair(key, obj));
    }
  }

  // Allocator allocator;
};

}  // namespace s21