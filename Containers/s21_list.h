#ifndef S21_CONTAINERS_S21_LIST_H_
#define S21_CONTAINERS_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <iterator>

namespace s21 {
template <class T>
struct NodeList {
  T data;
  NodeList<T> *next = nullptr;
  NodeList<T> *prev = nullptr;
};

template <class T>
class list {
 public:
  class ListIterator : public std::iterator<std::input_iterator_tag, int> {
   public:
    ListIterator(NodeList<T> *x) : elem_(x){};
    ListIterator(const ListIterator &li) : elem_(li.elem_){};
    ListIterator &operator++() {
      elem_ = elem_->next;
      return *this;
    };
    ListIterator &operator--() {
      elem_ = elem_->prev;
      return *this;
    };
    bool operator==(const ListIterator &l) const { return elem_ == l.elem_; };
    bool operator!=(const ListIterator &l) const { return elem_ != l.elem_; };
    T &operator*() { return elem_->data; };

   public:
    NodeList<T> *elem_;
  };

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = const ListIterator;
  using size_type = size_t;
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(const list &l);
  list operator=(list &&l);

  const_reference front() const { return head_->data; };
  const_reference back() const { return tail_->data; };

  iterator begin() {
    return size() == 0 ? iterator(after_end_) : iterator(head_);
  };
  iterator end() { return iterator(after_end_); };

  bool empty() const;
  size_type size() const;
  size_type max_size() const { return SIZE_MAX / sizeof(NodeList<T>) / 2; };

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &l);
  void merge(list &l);
  void splice(const_iterator pos, list &l);
  void reverse();
  void unique();
  void sort();

 private:
  NodeList<value_type> *head_;
  NodeList<value_type> *tail_;
  NodeList<value_type> *after_end_;
  size_type l_size_ = -1;
  // my functions
  void Copy(const list &l);
};

}  // namespace s21

template <class T>
s21::list<T>::list() : head_(nullptr), tail_(nullptr), after_end_(nullptr) {
  after_end_ = new NodeList<T>;
  after_end_->prev = tail_;
  l_size_ = 0;
}

template <class T>
s21::list<T>::list(size_type n)
    : head_(nullptr), tail_(nullptr), after_end_(nullptr) {
  after_end_ = new NodeList<T>;
  after_end_->prev = tail_;
  l_size_ = 0;
  while (n > 0) {
    push_front(0);
    n--;
  }
}

template <class T>
s21::list<T>::list(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), after_end_(nullptr) {
  after_end_ = new NodeList<T>;
  after_end_->prev = tail_;
  l_size_ = 0;
  for (auto it = items.begin(); it != items.end(); ++it) {
    push_back(*it);
  }
}

template <class T>
s21::list<T>::list(const s21::list<T> &l)
    : head_(nullptr), tail_(nullptr), after_end_(nullptr) {
  after_end_ = new NodeList<T>;
  after_end_->prev = tail_;
  l_size_ = 0;
  Copy(l);
}

template <class T>
s21::list<T>::list(list<T> &&l) {
  after_end_ = new NodeList<T>;
  *this = std::move(l);
}

template <class T>
s21::list<T>::~list() {
  while (head_ && head_ != after_end_) {
    NodeList<T> *buf = head_;
    head_ = head_->next;
    delete buf;
  }
  NodeList<T> *buf = after_end_;
  delete buf;
}

template <class T>
s21::list<T> &s21::list<T>::operator=(const list &l) {
  Copy(l);
  return *this;
}

template <class T>
s21::list<T> s21::list<T>::operator=(list &&l) {
  head_ = l.head_;
  tail_ = l.tail_;
  after_end_->prev = tail_;
  if (tail_ != nullptr) tail_->next = after_end_;
  l_size_ = l.l_size_;
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.l_size_ = 0;
  return *this;
}

template <class T>
bool s21::list<T>::empty() const {
  bool check = false;
  if (head_ == nullptr && tail_ == nullptr) {
    check = true;
  }
  return check;
}

template <class T>
size_t s21::list<T>::size() const {
  return l_size_;
}

template <class T>
void s21::list<T>::clear() {
  while (head_) {
    if (l_size_ > 1)
      tail_ = head_->next;
    else
      tail_ = nullptr;
    delete head_;
    head_ = tail_;
    --l_size_;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <class T>
typename s21::list<T>::iterator s21::list<T>::insert(iterator pos,
                                                     const_reference value) {
  NodeList<T> *buf = new NodeList<T>;
  buf->data = value;
  buf->prev = pos.elem_->prev;
  if (pos.elem_ != head_ && l_size_ > 0) pos.elem_->prev->next = buf;
  pos.elem_->prev = buf;
  buf->next = pos.elem_;
  if (pos.elem_ == head_) head_ = buf;
  if (pos.elem_ == after_end_) {
    after_end_->prev = buf;
    if (l_size_ == 0) head_ = buf;
    tail_ = buf;
  }
  ++l_size_;
  return buf;
}

template <class T>
void s21::list<T>::erase(iterator pos) {
  if (l_size_ != 0) {
    NodeList<T> *prev = pos.elem_->prev;
    NodeList<T> *next = pos.elem_->next;
    if (l_size_ > 1 && prev) prev->next = next;
    if (l_size_ > 1 && next) next->prev = prev;
    if (pos == begin()) {
      if (l_size_ == 1)
        head_ = nullptr;
      else
        head_ = next;
    }
    ListIterator buf = end();
    if (pos == (--buf)) tail_ = prev;
    delete pos.elem_;
    --l_size_;
  }
}

template <class T>
void s21::list<T>::push_back(const_reference value) {
  NodeList<T> *buf = new NodeList<T>;
  buf->data = value;
  if (!head_) {
    buf->next = tail_;
    head_ = buf;
    buf->prev = nullptr;
  } else {
    buf->next = tail_->next;
    buf->prev = tail_;
    tail_->next = buf;
  }
  tail_ = buf;
  tail_->next = after_end_;
  after_end_->prev = tail_;
  ++l_size_;
}

template <class T>
void s21::list<T>::pop_back() {
  if (!tail_) return;
  NodeList<T> *buf = tail_;
  tail_ = tail_->prev;
  if (l_size_ > 1) {
    tail_->next = after_end_;
  } else {
    head_ = nullptr;
  }
  after_end_->prev = tail_;
  delete buf;
  --l_size_;
}

template <class T>
void s21::list<T>::push_front(const_reference value) {
  NodeList<T> *buf = new NodeList<T>;
  buf->data = value;
  if (!head_) {
    buf->next = tail_;
    tail_ = buf;
    tail_->next = after_end_;
  } else {
    buf->next = head_;
    head_->prev = buf;
  }
  head_ = buf;
  head_->prev = nullptr;
  ++l_size_;
}

template <class T>
void s21::list<T>::pop_front() {
  if (!head_) return;
  NodeList<T> *buf = head_;
  if (l_size_ > 1) {
    head_ = head_->next;
    head_->prev = nullptr;
  } else {
    head_ = nullptr;
    tail_ = nullptr;
    after_end_->prev = nullptr;
  }
  delete buf;
  --l_size_;
}

template <class T>
void s21::list<T>::swap(list &l) {
  std::swap(*this, l);
}

template <class T>
void s21::list<T>::merge(list &l) {
  list<T> buf;
  buf = l;
  NodeList<T> *t = buf.head_;
  while (t && t != buf.after_end_) {
    push_back(t->data);
    t = t->next;
  }
  l.clear();
  sort();
}

template <class T>
void s21::list<T>::splice(const_iterator pos, list &l) {
  l.head_->prev = pos.elem_->prev;
  if (pos.elem_ != head_ && l_size_ > 0) pos.elem_->prev->next = l.head_;
  pos.elem_->prev = l.tail_;
  l.tail_->next = pos.elem_;
  if (pos.elem_ == head_) head_ = l.head_;
  if (pos.elem_ == after_end_) {
    after_end_->prev = l.tail_;
    if (l_size_ == 0) head_ = l.head_;
    tail_ = l.tail_;
  }
  l_size_ += l.size();
  l.after_end_->prev = nullptr;
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.l_size_ = 0;
}

template <class T>
void s21::list<T>::reverse() {
  list<T> reverse_list;
  NodeList<T> *t = head_;
  while (t != after_end_) {
    reverse_list.push_front(t->data);
    t = t->next;
  }
  *this = reverse_list;
}

template <class T>
void s21::list<T>::unique() {
  list<T> new_list;
  auto it = begin();
  new_list.push_back(it.elem_->data);
  if (l_size_ > 1) {
    auto prev_data = it.elem_->data;
    ++it;
    while (it != end()) {
      if (it.elem_->data != prev_data) new_list.push_back(it.elem_->data);
      prev_data = it.elem_->data;
      ++it;
    }
  }
  *this = new_list;
}

template <class T>
void s21::list<T>::sort() {
  if (l_size_ > 1) {
    NodeList<T> *buf = head_;
    for (size_t i = 0; i < l_size_ - 1; ++i) {
      NodeList<T> *buf2 = buf->next;
      for (size_t j = 0; j < l_size_ - 1 - i; ++j) {
        if (buf->data > buf2->data) {
          std::swap(buf->data, buf2->data);
        }
        buf2 = buf2->next;
      }
      buf = buf->next;
    }
  }
}

template <class T>
void s21::list<T>::Copy(const list<T> &l) {
  if (!empty()) clear();
  NodeList<T> *t = l.head_;
  while (t && t != l.after_end_) {
    push_back(t->data);
    t = t->next;
  }
}

#endif  // S21_CONTAINERS_S21_LIST_H_
