#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../list/s21_list.tpp"  // TODO думаю что нужно везде инклюдить .h а .tpp

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  //   using value_type = typename Container::value_type;
  //   using reference = typename Container::reference;
  //   using const_reference = typename Container::const_reference;
  //   using size_type = typename Container::size_type;

 protected:
  Container cont;

 public:
  queue() : cont() {}
  queue(std::initializer_list<T> const &items) : cont(items) {}
  queue(const queue &s) : cont(s.cont) {}
  queue(queue &&s) : cont(std::move(s.cont)) {}
  ~queue() {}
  queue &operator=(queue &&s) {
    this->cont = std::move(s.cont);
    return *this;
  }

  const T &front() { return cont.front(); }
  const T &back() { return cont.back(); }

  bool empty() const { return cont.empty(); }
  std::size_t size() const { return cont.size(); }

  void push(const T &value) { this->cont.push_back(value); }
  void pop() { this->cont.pop_front(); }
  void swap(queue &other) noexcept { this->cont.swap(other.cont); }
};
}  //  namespace s21

#endif  // S21_QUEUE_H