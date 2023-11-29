#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class VectorIterator;

template <typename T>
class VectorConstIterator;

template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  using size_type = std::size_t;
  using pointer = T*;

  // getters
  T getSize() { return this->size_; };
  T getCapacity() { return this->capacity_; };
  T* getContainer() { return this->container_; };

  // Constructors
  Vector();
  Vector(std::size_t n);
  Vector(std::initializer_list<T> const& items);
  Vector(const Vector& v);
  Vector(Vector&& v);
  ~Vector();
  Vector<T>& operator=(Vector<T>&& v);

  void my_copy(const Vector& v);

  // Vector Element Access
  T& front() noexcept;
  T& back() noexcept;
  T* data() noexcept;
  T& at(std::size_t num);
  T& operator[](std::size_t num);

  // Vector Sizes
  std::size_t max_size() const noexcept;
  bool empty() const noexcept;
  std::size_t size() const noexcept;
  std::size_t capacity() const noexcept;
  void reserve(std::size_t size);
  void shrink_to_fit() noexcept;

  // Vector Mofifier
  void push_back(const T& value);
  void pop_back();
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(VectorIterator<T> pos);
  void swap(Vector& other) noexcept;

  // BONUS FUNCS
  template <typename... Args>
  iterator emplace(iterator pos, Args&&... args);
  template <typename... Args>
  void emplace_back(Args&&... args);

  // Vector Iterators
  VectorIterator<T> begin() noexcept;
  VectorIterator<T> end() noexcept;
  VectorConstIterator<T> begin() const noexcept;
  VectorConstIterator<T> end() const noexcept;

 private:
  std::size_t size_;      // size of our array
  std::size_t capacity_;  // // capacity of our array
  T* container_;          // our array with values

  void turn_to_zero();
  void remove_vector();
  void add_memory(std::size_t size, bool flag);
  std::size_t increase_capacity_check(std::size_t size, bool flag);
};

template <typename T>
class VectorIterator {
 public:
  VectorIterator() { this->ptr_ = nullptr; };
  VectorIterator(T* ptr) { this->ptr_ = ptr; };

  // preincrement
  VectorIterator<T>& operator++();
  // posincrement
  VectorIterator<T> operator++(int);

  // predecrement
  VectorIterator<T>& operator--();
  // posposincrement
  VectorIterator<T> operator--(int);

  // dereference
  T& operator*() const;

  // equality
  bool operator!=(const VectorIterator<T>& other) const;
  bool operator==(const VectorIterator<T>& other) const;

  VectorIterator<T> operator+(const std::size_t value);
  VectorIterator<T> operator-(const std::size_t value);

  operator VectorConstIterator<T>() const {
    return VectorConstIterator<T>(ptr_);
  }

 private:
  T* ptr_;
};

template <typename T>
class VectorConstIterator {
 public:
  VectorConstIterator() { this->ptr_ = nullptr; }
  VectorConstIterator(T* ptr) { this->ptr_ = ptr; }

  // preincrement
  VectorConstIterator<T> operator++() const;
  // posincrement
  VectorConstIterator<T> operator++(int) const;

  // predecrement
  VectorConstIterator<T> operator--() const;
  // posposincrement
  VectorConstIterator<T> operator--(int) const;

  // dereference
  T operator*() const;

  // equality
  bool operator!=(const VectorConstIterator<T>& other) const;
  bool operator==(const VectorConstIterator<T>& other) const;

  VectorConstIterator<T> operator+(const std::size_t value) const;
  VectorConstIterator<T> operator-(const std::size_t value) const;

  operator VectorIterator<T>() const { return VectorIterator<T>(ptr_); }

 private:
  T* ptr_;
};
}  // namespace s21

#endif  // VECTOR_H