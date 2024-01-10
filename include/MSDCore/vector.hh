#ifndef MSDCORE_VECTOR_HH
#define MSDCORE_VECTOR_HH
#include <initializer_list>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "vector_iterator.hh"

namespace msd {
template <typename T> struct vector_buf {
protected:
  T *arr_;
  size_t capacity_, size_ = 0;

protected:
  vector_buf(const vector_buf &) = delete;
  vector_buf &operator=(const vector_buf &) = delete;
  vector_buf(vector_buf &&rhs) noexcept
      : arr_(rhs.arr_), size_(rhs.size_), capacity_(rhs.capacity_) {
    rhs.arr_ = nullptr;
    rhs.size_ = 0;
    rhs.capacity_ = 0;
  }
  vector_buf &operator=(vector_buf &&rhs) noexcept {
    std::swap(arr_, rhs.arr_);
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
    return *this;
  }
  vector_buf(size_t capacity = 0)
      : arr_((capacity == 0)
                 ? nullptr
                 : static_cast<T *>(::operator new(sizeof(T) * capacity))),
        capacity_(capacity) {}

  ~vector_buf() {
    for (auto i = arr_, ei = arr_ + capacity_; i != ei; ++i)
      i->~T();
    ::operator delete(arr_);
  }
};

template <typename T> struct vector final : private vector_buf<T> {
  using vector_buf<T>::arr_;
  using vector_buf<T>::capacity_;
  using vector_buf<T>::size_;
  using iterator = vector_iterator___<T>;
  using const_iterator = const_vector_iterator___<T>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using difference_type = iterator::difference_type;
  using reference = iterator::reference;

  explicit vector(size_t sz = 0) : vector_buf<T>(sz) {}

  vector(const std::initializer_list<T> &il) : vector_buf<T>(il.size()) {
    for (auto i = il.begin(), ei = il.end(); i != ei; ++size_, ++i)
      new (arr_ + size_) T(std::move(*i));
  }
  vector(const vector &rhs) : vector_buf<T>(rhs.size_) {
    for (; size_ < rhs.size_; ++size_) {
      new (arr_ + size_) T(rhs.arr_[size_]);
    }
  }
  vector &operator=(const vector &rhs) {
    vector tmp(rhs);
    //--------------
    std::swap(*this, tmp);
    return *this;
  }
  vector(vector &&rhs) = default;
  vector &operator=(vector &&rhs) = default;
  void pop_back() {
    if (size_ < 1)
      throw std::runtime_error("Empty vector");
    (arr_ + --size_)->~T();
  }
  static vector create_filled_vector(size_t sz = 0, const T &value = T()) {
    vector<T> res(sz);
    for (; res.size_ < sz;)
      res.push_back(value);
    return res;
  }
  template <typename Iter,
            typename = std::enable_if_t<std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<Iter>::iterator_category>>>
  vector(Iter fst, Iter lst) : vector(std::distance(fst, lst)) {
    for (; fst != lst; ++fst, ++size_)
      new (arr_ + size_) T(*fst);
  }
  reference operator[](difference_type n) const noexcept { return *(arr_ + n); }
  T back() const {
    if (size_ == 0)
      throw std::runtime_error("Empty vector");
    return arr_[size_ - 1];
  }
  T front() const {
    if (size_ == 0)
      throw std::runtime_error("Empty vector");
    return arr_[0];
  }
  void push_back(T &&t) {
    if (size_ == capacity_) {
      vector<T> tmp(capacity_ * 2 + 1);
      for (; tmp.size_ < size_;)
        tmp.push_back(std::move(arr_[tmp.size_]));
      tmp.push_back(std::move(t));
      //-------------------
      std::swap(*this, tmp);
    } else {
      new (arr_ + size_) T(std::move(t));
      size_ += 1;
    }
  }
  template <typename... Args> void emplace_back(Args &&...args) {
    if (size_ == capacity_) {
      vector<T> tmp(capacity_ * 2 + 1);
      for (; tmp.size_ < size_;)
        tmp.push_back(std::move(arr_[tmp.size_]));
      tmp.emplace_back(std::forward<Args>(args)...);
      std::swap(*this, tmp);
    } else {
      new (arr_ + size_) T(std::forward<Args>(args)...);
      size_ += 1;
    }
  }
  iterator begin() { return iterator(arr_); }
  iterator end() { return iterator(arr_ + size_); }
  const_iterator begin() const { return const_iterator(arr_); }
  const_iterator end() const { return const_iterator(arr_ + size_); }

  const_iterator cbegin() const { return const_iterator(arr_); }
  const_iterator cend() const { return const_iterator(arr_ + size_); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(begin());
  }

  void push_back(const T &t) {
    T t2(t);
    push_back(std::move(t2));
  }
  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  bool empty() const { return begin() == end(); }
  void swap(vector &rhs) noexcept { std::swap(*this, rhs); }
  size_t max_size() const noexcept {
    return std::numeric_limits<difference_type>::max();
  }
};

template <typename Iter>
vector(Iter fst, Iter lst)
    -> vector<typename std::iterator_traits<Iter>::value_type>;
} // namespace msd

template <typename T>
bool operator==(const msd::vector<T> &a, const msd::vector<T> &b) {
  return std::equal(a.begin(), a.end(), b.begin(), b.end());
}

template <typename T>
bool operator!=(const msd::vector<T> &a, const msd::vector<T> &b) {
  return !(a == b);
}

#endif
