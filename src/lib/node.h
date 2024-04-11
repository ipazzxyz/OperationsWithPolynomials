#ifndef OWP_LIB_NODE_H_
#define OWP_LIB_NODE_H_

template <typename T>
struct Node {
 public:
  Node();
  Node(const T &);
  ~Node();

  T &data();
  Node *&prev();
  Node *&next();

 private:
  T *data_ = new T;
  Node *prev_ = nullptr;
  Node *next_ = nullptr;
};

template <typename T>
Node<T>::Node() {}
template <typename T>
Node<T>::Node(const T &data) {
  *data_ = data;
}
template <typename T>
Node<T>::~Node() {
  delete data_;
}
template <typename T>
T &Node<T>::data() {
  return *data_;
}
template <typename T>
Node<T> *&Node<T>::prev() {
  return prev_;
}
template <typename T>
Node<T> *&Node<T>::next() {
  return next_;
}

#endif  // OWP_LIB_NODE_H_
