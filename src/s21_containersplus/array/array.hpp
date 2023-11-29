#ifndef ARRAY_H
#define ARRAY_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  // Array Members
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

 public:
  // Constructors
  array() = default;
  array(std::initializer_list<value_type> const &items) {
    auto iter = items.begin();
    for (size_type i = 0; i < N && iter != items.end(); ++iter, ++i) {
      arr_[i] = *iter;
    }
  }
  array(const array &other) {
    for (size_type i = 0; i < N; ++i) {
      arr_[i] = other.arr_[i];
    }
  }
  array(array &&other) { std::swap_ranges(begin(), end(), other.begin()); }
  ~array() = default;
  array &operator=(array &other) {
    for (auto i = 0; i < N; ++i) {
      arr_[i] = other.arr_[i];
    }
    return *this;
  }
  array &operator=(array &&other) {
    std::swap_ranges(begin(), end(), other.begin());
    return *this;
  }

  value_type *data() noexcept { return arr_; }

  reference operator[](size_type pos) noexcept { return arr_[pos]; }

  const_reference operator[](size_type pos) const noexcept { return arr_[pos]; }

  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("method array::at() out of range!");
    }
    return arr_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= N) {
      throw std::out_of_range("method array::at() out of range!");
    }
    return arr_[pos];
  }

  reference front() noexcept { return arr_[0]; }

  const_reference front() const noexcept { return arr_[0]; }

  reference back() noexcept {
    size_type index = N - 1;
    if (index == 1) {
      return arr_[0];
    } else {
      return arr_[index];
    }
  }

  const_reference back() const noexcept {
    size_type index = N - 1;
    if (index == 1) {
      return arr_[0];
    } else {
      return arr_[index];
    }
  }

  size_type size() const noexcept { return N; }

  size_type max_size() const noexcept { return N; }

  bool empty() const noexcept { return N == 0; }

  iterator begin() noexcept { return iterator(data()); }

  const_iterator begin() const noexcept { return const_iterator(data()); }

  iterator end() noexcept { return iterator(data() + N); }

  const_iterator end() const noexcept { return const_iterator(data() + N); }

  void swap(array &other) noexcept {
    std::swap_ranges(begin(), end(), other.begin());
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < N; ++i) {
      arr_[i] = value;
    }
  }

 private:
  value_type arr_[N]{};
};
}  // namespace s21

#endif  // ARRAY_H