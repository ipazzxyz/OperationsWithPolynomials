#ifndef OWP_LIB_LIST_H_
#define OWP_LIB_LIST_H_

#include <iostream>

#include "node.h"

template <typename T>
class List {
 public:
  List();
  ~List();

  // T operator[](int);

  void push_front(const T &);
  void pop_front();

  void push_back(const T &);
  void pop_back();

  bool empty() const;
  void clear();

  void erase(Node<T> *&);

  Node<T> *&first();
  Node<T> *&last();

 private:
  Node<T> *first_ = nullptr;
  Node<T> *last_ = nullptr;
};

template <typename T>
List<T>::List() {
  return;
}
template <typename T>
List<T>::~List() {
  clear();
  return;
}

// template <typename T>
// T List<T>::operator[](int index) {
//   Node<T> *it = first();
//   for (int i = 0; it && i < index; ++i) {
//     it = it->next();
//   }
//   return it->data();
// }

template <typename T>
void List<T>::push_front(const T &data) {
  if (empty()) {
    first_ = last_ = new Node<T>(data);
    return;
  }
  first_->prev() = new Node<T>(data);
  first_->prev()->next() = first_;
  first_ = first_->prev();
  return;
}
template <typename T>
void List<T>::pop_front() {
  if (empty()) {
    return;
  }
  if (first_ == last_) {
    delete first_;
    first_ = last_ = nullptr;
    return;
  }
  first_ = first_->next();
  delete first_->prev();
  first_->prev() = nullptr;
  return;
}

template <typename T>
void List<T>::push_back(const T &data) {
  if (empty()) {
    first_ = last_ = new Node<T>(data);
    return;
  }
  last_->next() = new Node<T>(data);
  last_->next()->prev() = last_;
  last_ = last_->next();
  return;
}
template <typename T>
void List<T>::pop_back() {
  if (empty()) {
    return;
  }
  if (first_ == last_) {
    delete first_;
    first_ = last_ = nullptr;
    return;
  }
  last_ = last_->prev();
  delete last_->next();
  last_->next() = nullptr;
  return;
}

template <typename T>
void List<T>::clear() {
  while (!empty()) {
    pop_front();
  }
  return;
}
template <typename T>
bool List<T>::empty() const {
  return !first_;
}

template <typename T>
void List<T>::erase(Node<T> *&node) {
  if (empty()) {
    return;
  }
  if (node == first_) {
    pop_front();
    return;
  }
  if (node == last_) {
    pop_back();
    return;
  }
  if (node->prev()) {
    node->prev()->next() = node->next();
  }
  if (node->next()) {
    node->next()->prev() = node->prev();
  }
  delete node;
  node = nullptr;
  return;
}

template <typename T>
Node<T> *&List<T>::first() {
  return first_;
}
template <typename T>
Node<T> *&List<T>::last() {
  return last_;
}

template <typename T>
void qsort(Node<T> *&first, Node<T> *&last) {
  if (first == last) {
    return;
  }
  T *pivot = &first->data();

  Node<T> *it = first, *lessBegin = nullptr, *lessEnd = nullptr,
          *equalBegin = nullptr, *equalEnd = nullptr, *greatBegin = nullptr,
          *greatEnd = nullptr;

  while (true) {
    Node<T> *next_element = it->next();
    if (it->data() < *pivot) {
      it->next() = lessBegin;
      it->prev() = nullptr;
      lessBegin = it;
      if (!lessEnd) {
        lessEnd = lessBegin;
      } else {
        lessBegin->next()->prev() = lessBegin;
      }
    } else if (it->data() == *pivot) {
      it->next() = equalBegin;
      it->prev() = nullptr;
      equalBegin = it;
      if (!equalEnd) {
        equalEnd = equalBegin;
      } else {
        equalBegin->next()->prev() = equalBegin;
      }
    } else {
      it->next() = greatBegin;
      it->prev() = nullptr;
      greatBegin = it;
      if (!greatEnd) {
        greatEnd = greatBegin;
      } else {
        greatBegin->next()->prev() = greatBegin;
      }
    }
    if (it == last) {
      break;
    }
    it = next_element;
  }
  first = equalBegin, last = equalEnd;
  if (lessBegin) {
    qsort(lessBegin, lessEnd);
    equalEnd->next() = lessBegin;
    lessBegin->prev() = equalEnd;
    last = lessEnd;
  }
  if (greatBegin) {
    qsort(greatBegin, greatEnd);
    greatEnd->next() = equalBegin;
    equalBegin->prev() = greatEnd;
    first = greatBegin;
  }
  first->prev() = last->next() = nullptr;
  return;
}

#endif  // OWP_LIB_LIST_H_