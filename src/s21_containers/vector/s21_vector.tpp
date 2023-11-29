#include "s21_vector.hpp"

namespace s21 {
// publics
template <typename T>
Vector<T>::Vector() {
  this->turn_to_zero();
}

template <class T>
Vector<T>::Vector(std::size_t n) {
  if (this->max_size() < n) {
    throw std::out_of_range("cannot create std::vector larger than max_size()");
  }
  this->size_ = n;
  this->capacity_ = n;
  this->container_ = new T[n];
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> const& items) {
  this->size_ = this->capacity_ = items.size();
  this->container_ = new T[this->size_];
  std::copy(items.begin(), items.end(), this->container_);
}

template <typename T>
Vector<T>::Vector(const Vector& v) {
  this->my_copy(v);
}

template <class T>
Vector<T>::Vector(Vector&& v) {
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  this->container_ = v.container_;
  v.turn_to_zero();
}

template <typename T>
Vector<T>::~Vector() {
  this->remove_vector();
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) {
  if (this != &v) {
    this->remove_vector();
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->container_ = v.container_;
    v.turn_to_zero();
  }
  return *this;
}

template <typename T>
void Vector<T>::my_copy(const Vector& v) {
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  this->container_ = new T[v.size_];
  for (long unsigned int i = 0; i < v.size_; i++) {
    this->container_[i] = v.container_[i];
  }
}

template <typename T>
T& Vector<T>::front() noexcept {
  return this->container_[0];
}

template <typename T>
T& Vector<T>::back() noexcept {
  return this->container_[size_ - 1];
}

template <typename T>
T* Vector<T>::data() noexcept {
  return this->container_;
}

template <typename T>
T& Vector<T>::at(std::size_t num) {
  if (num >= this->size_) {
    throw std::out_of_range("vector::_M_range_check: __n");
  }
  return this->container_[num];
}

template <typename T>
T& Vector<T>::operator[](std::size_t num) {
  if (this->size() < num || num < 0) {
    throw std::out_of_range("index out of range");
  }
  return this->container_[num];
}

template <typename T>
std::size_t Vector<T>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template <typename T>
bool Vector<T>::empty() const noexcept {
  return this->size_ == 0 ? true : false;
}

template <typename T>
std::size_t Vector<T>::size() const noexcept {
  return this->size_;
}

template <typename T>
std::size_t Vector<T>::capacity() const noexcept {
  return this->capacity_;
}

template <typename T>
void Vector<T>::reserve(std::size_t size) {
  if (size > this->capacity_) {
    // this->add_memory(size, true);
    this->capacity_ = size;
  } else if ((T)size < 0) {
    throw std::length_error(
        "terminate called after throwing an instance of 'std::length_error'");
  } else if (size > this->max_size()) {
    throw std::length_error(
        "terminate called after throwing an instance of bad alloc");
  }
}

template <typename T>
void Vector<T>::shrink_to_fit() noexcept {
  this->capacity_ = this->size_;
}

template <typename T>
void Vector<T>::push_back(const T& value) {
  if (this->size_ >= this->capacity_) {
    add_memory(0, false);
  }
  this->container_[this->size_++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
  if (this->size_ > 0) {
    this->size_--;
  } else {
    throw std::out_of_range("0 zsh: segmentation fault");
  }
}

template <typename T>
void Vector<T>::clear() noexcept {
  this->size_ = 0;
}

template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_type index = pos - begin();

  if (index > size_)
    throw std::out_of_range(
        "s21::vector::insert Unable to insert into a position out of "
        "range of begin() to end()");

  if (size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }

  iterator new_pos = begin() + index;

  for (iterator it = end(); it != new_pos; --it) {
    *it = *(it - 1);
  }

  *new_pos = value;
  ++size_;
  return new_pos;
}

// 2, 5, 7, 8, 1
// s21_v.erase(s21_v.begin() + 2); - это элемент 7
// pos = 2
template <typename T>
void Vector<T>::erase(VectorIterator<T> pos) {
  std::size_t position = &(*pos) - this->container_;
  for (std::size_t i = position + 1; i < this->size_; ++i) {
    this->container_[i - 1] = this->container_[i];
  }
  this->size_--;
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept {
  std::swap(this->size_, other.size_);
  std::swap(this->capacity_, other.capacity_);
  std::swap(this->container_, other.container_);
}

template <typename value_type>
template <typename... Args>
typename Vector<value_type>::iterator Vector<value_type>::emplace(
    iterator pos, Args&&... args) {
  auto args_v = std::initializer_list<value_type>{std::forward<Args>(args)...};

  for (auto& i : args_v) {
    insert(pos, i);
  }

  return pos;
}

template <typename value_type>
template <typename... Args>
void Vector<value_type>::emplace_back(Args&&... args) {
  emplace(end(), args...);
}

template <typename T>
VectorIterator<T> Vector<T>::begin() noexcept {
  return VectorIterator<T>(this->container_);
}

template <typename T>
VectorIterator<T> Vector<T>::end() noexcept {
  return VectorIterator<T>(this->container_ + this->size_);
}

template <typename T>
VectorConstIterator<T> Vector<T>::begin() const noexcept {
  return VectorConstIterator<T>(this->container_);
}

template <typename T>
VectorConstIterator<T> Vector<T>::end() const noexcept {
  return VectorConstIterator<T>(this->container_ + this->size_);
}

template <typename T>
void Vector<T>::turn_to_zero() {
  this->capacity_ = 0;
  this->size_ = 0;
  this->container_ = nullptr;
}

template <typename T>
void Vector<T>::remove_vector() {
  if (this->container_ != nullptr) {
    delete[] this->container_;
  }
  this->turn_to_zero();
}

template <typename T>
void Vector<T>::add_memory(std::size_t size, bool flag) {
  this->capacity_ = increase_capacity_check(size, flag);
  T* tmp = this->container_;
  this->container_ = new T[this->capacity_];
  for (size_t i = 0; i < this->size_; i++) {
    this->container_[i] = tmp[i];
  }
  delete[] tmp;
}

template <typename T>
std::size_t Vector<T>::increase_capacity_check(std::size_t size, bool flag) {
  std::size_t n = 2;
  return flag ? size : n * (this->capacity_ > 0 ? this->capacity_ : n);
}

/* VectorIterators
*********************************************
*********************************************
**********************************************/

// increment
template <typename T>
VectorIterator<T>& VectorIterator<T>::operator++() {
  ++ptr_;
  return *this;
}

// posincrement
template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int) {
  VectorIterator tmp = *this;
  ++(*this);
  return tmp;
}

// decrement
template <typename T>
VectorIterator<T>& VectorIterator<T>::operator--() {
  --this->ptr_;
  return *this;
}

// deference
template <typename T>
T& VectorIterator<T>::operator*() const {
  return *ptr_;
}

// inequality iterators
template <typename T>
bool VectorIterator<T>::operator!=(const VectorIterator<T>& other) const {
  return this->ptr_ != other.ptr_;
}

template <typename T>
bool VectorIterator<T>::operator==(const VectorIterator<T>& other) const {
  return this->ptr_ == other.ptr_;
}

// adding num to iterator
template <typename T>
VectorIterator<T> VectorIterator<T>::operator+(const std::size_t value) {
  VectorIterator tmp(this->ptr_ + value);
  return tmp;
}

// substraction num to iterator
template <typename T>
VectorIterator<T> VectorIterator<T>::operator-(const std::size_t value) {
  VectorIterator tmp(this->ptr_ - value);
  return tmp;
}

/* VectorConstIterator
*********************************************
*********************************************
**********************************************/

// increment
template <typename T>
VectorConstIterator<T> VectorConstIterator<T>::operator++() const {
  VectorConstIterator(this->ptr_ + 1);
  // ++ptr_;
  // return *this;
}

// posincrement
template <typename T>
VectorConstIterator<T> VectorConstIterator<T>::operator++(int) const {
  VectorConstIterator tmp = *this;
  ++(*this);
  return tmp;
}

// decrement
template <typename T>
VectorConstIterator<T> VectorConstIterator<T>::operator--() const {
  VectorConstIterator(this->ptr_ - 1);
  // --this->ptr_;
  // return *this;
}

// deference
template <typename T>
T VectorConstIterator<T>::operator*() const {
  return *ptr_;
}

// inequality iterators
template <typename T>
bool VectorConstIterator<T>::operator!=(
    const VectorConstIterator<T>& other) const {
  return this->ptr_ != other.ptr_;
}

template <typename T>
bool VectorConstIterator<T>::operator==(
    const VectorConstIterator<T>& other) const {
  return this->ptr_ == other.ptr_;
}

// adding num to iterator
template <typename T>
VectorConstIterator<T> VectorConstIterator<T>::operator+(
    const std::size_t value) const {
  VectorConstIterator tmp(this->ptr_ + value);
  return tmp;
}

// substraction num to iterator
template <typename T>
VectorConstIterator<T> VectorConstIterator<T>::operator-(
    const std::size_t value) const {
  VectorConstIterator tmp(this->ptr_ - value);
  return tmp;
}
}  // namespace s21