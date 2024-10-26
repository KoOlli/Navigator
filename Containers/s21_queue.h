#ifndef S21_CONTAINERS_S21_QUEUE_H_
#define S21_CONTAINERS_S21_QUEUE_H_

#include "s21_list.h"

namespace s21 {
template <class T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() = default;
  queue(std::initializer_list<value_type> const &items) {
    for (auto &item : items) {
      q_.push_back(item);
    }
  };
  queue(const queue &q) { q_ = q.q_; };
  queue(queue &&q) { q_.swap(q.q_); };
  ~queue() = default;
  queue operator=(const queue &q) {
    q_ = q.q_;
    return *this;
  };
  queue operator=(queue &&q) {
    q_.swap(q.q_);
    return *this;
  };

  const_reference front() const { return q_.front(); };
  const_reference back() const { return q_.back(); };

  bool empty() const { return q_.empty(); };
  size_type size() const { return q_.size(); };
  void push(const_reference value) { q_.push_back(value); };
  void pop() { q_.pop_front(); };
  void swap(queue &other) { q_.swap(other.q_); };

 private:
  s21::list<value_type> q_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_QUEUE_H_
