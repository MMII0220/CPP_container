#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  // List Members
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  // Getter
  T getSize() { return this->size_; }

 private:
  struct Node {
    T value_;
    Node* prev_;
    Node* next_;
    Node(const T& value) : value_(value), prev_(nullptr), next_(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  Node* end_;
  std::size_t size_;

 public:
  // Constrcutors
  list();
  list(std::size_t n);
  list(std::initializer_list<T> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  list<T>& operator=(list&& l);

  // List Element Access
  const T& front() noexcept;
  const T& back() noexcept;

  // List Capacity
  bool empty() const noexcept;
  std::size_t size() const noexcept;
  // iterator insert(iterator pos, const_reference value);
  std::size_t max_size() const noexcept;

  // List Modifiers
  void clear() noexcept;
  void push_back(const T& value);
  void push_front(const T& value);
  void pop_back();
  void pop_front();
  void swap(list& other) noexcept;
  void merge(list& other);
  void reverse() noexcept;
  void unique();
  void sort();

  template <typename value_type>
  class ListIterator {
   public:
    ListIterator() { this->ptr_ = nullptr; }
    ListIterator(Node* ptr) : ptr_(ptr){};

    value_type& operator*() {
      if (!this->ptr_) {
        throw std::invalid_argument("Value is nullptr");
      }
      return this->ptr_->value_;
    }

    ListIterator operator++(int) {
      this->ptr_ = this->ptr_->next_;
      return *this;
    }

    ListIterator operator--(int) {
      this->ptr_ = this->ptr_->prev_;
      return *this;
    }

    ListIterator& operator++() {
      this->ptr_ = this->ptr_->next_;
      return *this;
    }

    ListIterator& operator--() {
      this->ptr_ = this->ptr_->prev_;
      return *this;
    }

    ListIterator operator+(const std::size_t value) {
      Node* tmp = this->ptr_;
      for (std::size_t i = 0; i < value; i++) {
        tmp = tmp->next_;
      }

      ListIterator res(tmp);
      return res;
    }

    ListIterator operator-(const std::size_t value) {
      Node* tmp = this->ptr_;
      for (std::size_t i = 0; i < value; i++) {
        tmp = tmp->prev_;
      }
      ListIterator res(tmp);
      return res;
    }

    bool operator==(ListIterator other) { return this->ptr_ == other.ptr_; }
    bool operator!=(ListIterator other) { return this->ptr_ != other.ptr_; }

   private:
    Node* ptr_ = nullptr;
    friend class list<value_type>;
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<value_type> {
   public:
    ListConstIterator(ListIterator<value_type> other)
        : ListIterator<value_type>(other) {}
    const T& operator*() { return ListIterator<value_type>::operator*(); }
  };

  // List Iterator
  ListIterator<T> begin() noexcept;
  ListIterator<T> end() noexcept;
  ListConstIterator<T> begin() const;
  ListConstIterator<T> end() const;

  //  List Member type
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  // List Modifiers
  iterator insert(iterator pos, const value_type& value);
  void erase(iterator pos);
  void splice(const_iterator pos, list& other);

 private:
  // support
  void change_end();
  void quick_sort(ListIterator<T> left, ListIterator<T> right);
  iterator partition(iterator first, iterator last);
  void copy(const list& l);
  void print_list();
};
}  // end of namespace s21

#endif  // LIST_H