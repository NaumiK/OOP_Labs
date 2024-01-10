#ifndef MSDCORE_VECTOR_ITERATOR_HH
#define MSDCORE_VECTOR_ITERATOR_HH

#include <iterator>

namespace msd {
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
  iterator operator-(difference_type n) const {
    auto tmp = *this;
    tmp -= n;
    return tmp;
  }
  iterator operator+(difference_type n) const {
    auto tmp = *this;
    tmp += n;
    return tmp;
  }
  bool operator==(const iterator &rhs) const { return t_ == rhs.t_; }
  bool operator!=(const iterator &rhs) const { return !(*this == rhs); }
  difference_type operator-(const iterator &rhs) const { return t_ - rhs.t_; }
  bool operator<(const iterator &rhs) const { return t_ < rhs.t_; }
  bool operator>(const iterator &rhs) const { return t_ > rhs.t_; }
  bool operator<=(const iterator &rhs) const { return !(*this > rhs); }
  bool operator>=(const iterator &rhs) const { return !(*this < rhs); }
};

template <typename T> class const_vector_iterator___ {
public:
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<T>;
  using pointer = T *;
  using reference = T &;
  using iterator = const_vector_iterator___;
  using iterator_category = std::random_access_iterator_tag;
  using iterator_concept = std::contiguous_iterator_tag;

protected:
  T *t_;

public:
  const_vector_iterator___() = default;
  const_vector_iterator___(T *t) : t_(t) {}
  const_vector_iterator___(const const_vector_iterator___ &) = default;
  const_vector_iterator___ &
  operator=(const const_vector_iterator___ &) = default;
  ~const_vector_iterator___() = default;
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
  iterator operator-(difference_type n) const {
    auto tmp = *this;
    tmp -= n;
    return tmp;
  }
  iterator operator+(difference_type n) const {
    auto tmp = *this;
    tmp += n;
    return tmp;
  }
  bool operator==(const iterator &rhs) const { return t_ == rhs.t_; }
  bool operator!=(const iterator &rhs) const { return !(*this == rhs); }
  difference_type operator-(const iterator &rhs) const { return t_ - rhs.t_; }
  bool operator<(const iterator &rhs) const { return t_ < rhs.t_; }
  bool operator>(const iterator &rhs) const { return t_ > rhs.t_; }
  bool operator<=(const iterator &rhs) const { return !(*this > rhs); }
  bool operator>=(const iterator &rhs) const { return !(*this < rhs); }
};
} // namespace msd

template <typename T>
void swap(msd::vector_iterator___<T> &a, msd::vector_iterator___<T> &b) {
  std::swap(a.t_, b.t_);
}
template <typename T>
void swap(msd::const_vector_iterator___<T> &a,
          msd::const_vector_iterator___<T> &b) {
  std::swap(a.t_, b.t_);
}

#endif
