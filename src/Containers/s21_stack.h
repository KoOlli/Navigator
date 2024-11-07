#ifndef S21_CONTAINERS_S21_STACK_H_
#define S21_CONTAINERS_S21_STACK_H_

#include "s21_list.h"

namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() = default;

  stack(std::initializer_list<value_type> const &items) {
    for (auto &item : items) {
      st_.push_back(item);
    }
  };

  stack(const stack &s) { st_ = s.st_; };

  stack(stack &&s) { st_.swap(s.st_); };

  ~stack() = default;

  stack operator=(const stack &s) {
    st_ = s.st_;
    return *this;
  }

  stack operator=(stack &&s) {
    st_.swap(s.st_);
    return *this;
  }

  const_reference top() const { return st_.back(); };

  bool empty() const { return st_.empty(); };

  size_type size() const { return st_.size(); };

  void push(const_reference value) { st_.push_back(value); };

  void pop() { st_.pop_back(); };

  void swap(stack &other) { st_.swap(other.st_); };

 private:
  s21::list<value_type> st_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_STACK_H_
