#include "s21_list.hpp"

namespace s21 {
// Constructors
template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  end_ = new Node(size_);
  change_end();
}
template <typename T>
list<T>::list(std::size_t n)
    : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  if (n >= max_size()) {
    throw std::out_of_range("Limit of the container is exceeded");
  }
  end_ = new Node(size_);
  for (std::size_t i = 0; i < n; ++i) {
    push_back(T());
  }
  change_end();
}
template <typename T>
list<T>::list(std::initializer_list<T> const& items)
    : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  end_ = new Node(size_);
  for (const auto& item : items) {
    push_back(item);
    change_end();
  }
}
template <typename T>
list<T>::list(const list& l)
    : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  end_ = new Node(size_);
  this->copy(l);
}
template <typename T>
list<T>::list(list&& l)
    : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  swap(l);
}
template <typename T>
list<T>::~list() {
  clear();
  if (this->end_) {
    delete end_;
  }
}
template <typename T>
list<T>& list<T>::operator=(list&& l) {
  if (this != &l) {
    clear();
    swap(l);
  }
  return *this;
}

// List Element Access
template <typename T>
const T& list<T>::front() noexcept {
  return !head_ ? end_->value_ : head_->value_;
}

template <typename T>
const T& list<T>::back() noexcept {
  return !tail_ ? end_->value_ : tail_->value_;
}

// List Capacity
template <typename T>
bool list<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
std::size_t list<T>::size() const noexcept {
  return this->size_;
}

template <typename T>
std::size_t list<T>::max_size() const noexcept {
  return (std::numeric_limits<std::size_t>::max() / sizeof(Node) / 2);
}

// List Modifiers
template <typename T>
void list<T>::clear() noexcept {
  while (!empty()) {
    pop_back();
  }
}

template <typename T>
void list<T>::push_back(const T& value) {
  Node* new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->prev_ = tail_;
    tail_->next_ = new_node;
    tail_ = new_node;
  }
  size_++;
  change_end();
}

template <typename T>
void list<T>::push_front(const T& value) {
  Node* new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->next_ = head_;
    head_->prev_ = new_node;
    head_ = new_node;
  }
  size_++;
  change_end();
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("zsh: abort: list is empty");
  }
  Node* last_node = tail_;
  if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    tail_ = last_node->prev_;
    tail_->next_ = nullptr;
  }
  delete last_node;
  size_--;
  change_end();
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }
  Node* first_node = head_;
  if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    head_ = first_node->next_;
    head_->prev_ = nullptr;
  }
  delete first_node;
  size_--;
  change_end();
}

template <typename T>
void list<T>::swap(list& other) noexcept {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->size_, other.size_);
  std::swap(this->end_, other.end_);
}

template <typename T>
void list<T>::merge(list& other) {
  if (!this->empty() && !other.empty()) {
    ListIterator<T> iter_this = this->begin();
    ListIterator<T> iter_other = other.begin();
    while (iter_this != this->end()) {
      if (iter_other != other.end()) {
        if (iter_this.ptr_->value_ >= iter_other.ptr_->value_) {
          this->insert(iter_this, iter_other.ptr_->value_);
          iter_other++;
        } else {
          iter_this++;
        }
      } else {
        break;
      }
    }
    while (iter_other != other.end()) {
      this->insert(iter_this, iter_other.ptr_->value_);
      iter_other++;
    }
  } else if (this->empty() && !other.empty()) {
    this->copy(other);
  }
  other.clear();
}

template <typename T>
void list<T>::reverse() noexcept {
  if (!this->empty()) {
    std::size_t step = 0;
    for (iterator it = this->begin(); step <= this->size(); ++it) {
      step++;
      std::swap(it.ptr_->prev_, it.ptr_->next_);
    }
    std::swap(head_, tail_);
  }
}

template <typename T>
void list<T>::unique() {
  if (!this->empty()) {
    for (ListIterator<T> it = this->begin(); it != this->end(); it++) {
      if (it.ptr_->value_ == it.ptr_->prev_->value_) {
        ListIterator<T> del_it = (it - 1);
        this->erase(del_it);
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ > 1) {
    quick_sort(begin(), --end());
  }
}

// List Iterators
template <typename T>
typename list<T>::ListIterator<T> list<T>::begin() noexcept {
  return !head_ ? ListIterator<T>(end_) : ListIterator<T>(head_);
}

template <typename T>
typename list<T>::ListIterator<T> list<T>::end() noexcept {
  return ListIterator<value_type>(end_);
}

template <typename T>
typename list<T>::ListConstIterator<T> list<T>::begin() const {
  return !head_ ? ListConstIterator<T>(end_) : ListConstIterator<T>(head_);
}

template <typename T>
typename list<T>::ListConstIterator<T> list<T>::end() const {
  return ListConstIterator<T>(end_);
}

// List Modifiers
template <typename T>
typename list<T>::iterator list<T>::insert(
    iterator pos, const typename list<T>::value_type& value) {
  Node* current = pos.ptr_;
  Node* add = new Node(value);
  if (empty()) {
    add->next_ = end_;
    add->prev_ = end_;
    head_ = add;
    tail_ = add;
  } else {
    if (current == head_) {
      head_ = add;
    } else if (current == end_) {
      tail_ = add;
    }
    add->next_ = current;
    add->prev_ = current->prev_;
    current->prev_->next_ = add;
    current->prev_ = add;
  }
  size_++;
  change_end();
  return iterator(add);
}

template <typename T>
void list<T>::erase(ListIterator<T> pos) {
  Node* current = pos.ptr_;
  if (!empty() && current != end_) {
    if (current == head_) {
      if (current->next_ && current->next_ != end_) {
        head_ = current->next_;
      } else {
        head_ = end_;
      }
    } else if (current == tail_) {
      if (current->prev_ && current->prev_ != end_) {
        tail_ = current->prev_;
      } else {
        tail_ = end_;
      }
    }
    current->prev_->next_ = current->next_;
    current->next_->prev_ = current->prev_;
    delete current;
    this->size_--;
  } else {
    throw std::invalid_argument("Invalid argument");
  }
  change_end();
}

template <typename T>
void list<T>::splice(const ListConstIterator<T> pos, list& other) {
  if (!other.empty()) {
    for (ListIterator<T> it = other.begin(); it != other.end(); ++it) {
      this->insert(pos, *it);
    }
    other.clear();
  }
}

// support
template <typename T>
void list<T>::change_end() {
  if (end_) {
    end_->next_ = head_;
    end_->prev_ = tail_;
    end_->value_ = size();
    if (head_) {
      head_->prev_ = end_;
    }
    if (tail_) {
      tail_->next_ = end_;
    }
  }
}

template <typename T>
void list<T>::quick_sort(ListIterator<T> left, ListIterator<T> right) {
  if (left == right || left == end_ || right == end_ || left == tail_) {
    return;
  }
  ListIterator<T> pivot = partition(left, right);
  quick_sort(left, --pivot);
  quick_sort(++pivot, right);
}

template <typename T>
typename list<T>::iterator list<T>::partition(iterator first, iterator last) {
  T pivot_value = last.ptr_->value_;
  ListIterator<T> i = first;

  for (ListIterator<T> j = first; j != last; ++j) {
    if (j.ptr_->value_ <= pivot_value) {
      std::swap(i.ptr_->value_, j.ptr_->value_);
      i++;
    }
  }

  std::swap(i.ptr_->value_, last.ptr_->value_);

  return i;
}

template <typename T>
void list<T>::copy(const list& l) {
  Node* current = l.head_;
  for (std::size_t i = 0; i != l.size_; i++) {
    push_back(current->value_);
    current = current->next_;
  }
}

template <typename T>
void list<T>::print_list() {
  std::cout << "[";
  for (ListIterator<T> it = begin(); it != end(); ++it) {
    std::cout << *it;
    if ((it + 1) != end()) {
      std::cout << ", ";
    }
  }
  std::cout << "]\n";
}
}  // end of namespace s21