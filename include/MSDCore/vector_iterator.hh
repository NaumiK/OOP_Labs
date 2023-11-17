#ifndef MSDCORE_VECTOR_ITERATOR_HH
#define MSDCORE_VECTOR_ITERATOR_HH

#include <iterator>

template <typename T> class vector_iterator___;

template <typename T>
bool operator==(const vector_iterator___<T> &lhs,
                const vector_iterator___<T> &rhs) {
  return lhs.t_ == rhs.t_;
}

template <typename T>
bool operator!=(const vector_iterator___<T> &lhs,
                const vector_iterator___<T> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
bool operator<(const vector_iterator___<T> &lhs,
               const vector_iterator___<T> &rhs) {
  return lhs.t_ < rhs.t_;
}

template <typename T>
bool operator>(const vector_iterator___<T> &lhs,
               const vector_iterator___<T> &rhs) {
  return rhs < lhs;
}

template <typename T>
bool operator<=(const vector_iterator___<T> &lhs,
                const vector_iterator___<T> &rhs) {
  return !(lhs > rhs);
}

template <typename T>
bool operator>=(const vector_iterator___<T> &lhs,
                const vector_iterator___<T> &rhs) {
  return !(lhs < rhs);
}

template <typename T>
vector_iterator___<T>
operator+(vector_iterator___<T> it,
          typename vector_iterator___<T>::difference_type n) {
  it += n;
  return it;
}

template <typename T>
vector_iterator___<T>
operator+(typename vector_iterator___<T>::difference_type n,
          vector_iterator___<T> it) {
  it += n;
  return it;
}

template <typename T>
vector_iterator___<T>
operator-(vector_iterator___<T> it,
          typename vector_iterator___<T>::difference_type n) {
  it -= n;
  return it;
}

template <typename T>
int64_t operator-(const vector_iterator___<T> &lhs,
                  const vector_iterator___<T> &rhs) {
  return lhs.t_ - rhs.t_;
}

template <typename T> class vector_iterator___ {
public:
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<T>;
  using pointer = T *;
  using reference = T &;
  using iterator = vector_iterator___;
  using iterator_category = std::random_access_iterator_tag;
  using iterator_concept = std::contiguous_iterator_tag;

protected:
  T *t_;

public:
  vector_iterator___() = default;
  vector_iterator___(T *t) : t_(t) {}
  vector_iterator___(const vector_iterator___ &) = default;
  vector_iterator___ &operator=(const vector_iterator___ &) = default;
  ~vector_iterator___() = default;
  reference operator*() { return *t_; }
  reference operator*() const { return *t_; }
  iterator &operator++() {
    ++t_;
    return *this;
  }
  iterator operator++(int) {
    auto old = *this;
    ++(*this);
    return old;
  }

  pointer operator->() { return t_; }
  const pointer operator->() const { return t_; }

  iterator &operator--() {
    --t_;
    return *this;
  }

  iterator operator--(int) {
    auto old = *this;
    --(*this);
    return old;
  }

  reference operator[](difference_type n) const {
    auto tmp = *this;
    tmp += n;
    return *tmp;
  }

  iterator &operator+=(difference_type n) {
    t_ += n;
    return *this;
  }

  iterator &operator-=(difference_type n) {
    t_ -= n;
    return *this;
  }

  template <typename T1>
  friend bool operator==(const vector_iterator___<T1> &lhs,
                         const vector_iterator___<T1> &rhs);

  template <typename T1>
  friend int64_t operator-(const vector_iterator___<T1> &lhs,
                           const vector_iterator___<T1> &rhs);

  template <typename T1>
  friend bool operator<(const vector_iterator___<T1> &lhs,
                        const vector_iterator___<T1> &rhs);
};

template <typename T>
void swap(vector_iterator___<T> &a, vector_iterator___<T> &b) {
  std::swap(a.t_, b.t_);
}
#endif
