#ifndef MSDCORE_LIST_HH
#define MSDCORE_LIST_HH

#include <initializer_list>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <list>
#include <vcruntime.h>

namespace msd {
template <typename T> class list {
  struct Node {
    T *data_;
    Node *prev_ = nullptr, *next_ = nullptr;
    Node(T *data = nullptr, Node *prev = nullptr, Node *next = nullptr)
        : data_(data), prev_(prev), next_(next) {}
    Node(const T &data, Node *prev = nullptr, Node *next = nullptr)
        : data_(new T(data)), prev_(prev), next_(next) {}
    Node(T &&data, Node *prev = nullptr, Node *next = nullptr)
        : data_(new T(std::move(data))), prev_(prev), next_(next) {}
    Node(Node &&rhs) : data_(rhs.data_), prev_(rhs.prev_), next_(rhs.next_) {}
    Node &operator=(Node &&rhs) {
      std::swap(data_, rhs.data_);
      std::swap(next_, rhs.next_);
      std::swap(prev_, rhs.prev_);
    }
    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;
    ~Node() { delete data_; }
  };
  Node *fst_, *lst_;
  size_t size_ = 0;

public:
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;

public:
  list() : lst_(new Node) { fst_ = lst_; }
  list(const list &rhs) {
    list tmp;
    for (auto &&i : rhs)
      tmp.push_back(i);
    std::swap(*this, tmp);
  }
  template <typename Iter,
            typename = std::enable_if_t<std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<Iter>::iterator_category>>>
  list(Iter fst, Iter lst) {
    list tmp;
    for (; fst != lst; ++fst)
      tmp.push_back(*fst);
    std::swap(*this, tmp);
  }
  list(const std::initializer_list<T> &il) {
    list tmp;
    for (auto &&i : il)
      tmp.push_back(i);
    std::swap(*this, il);
  }
  ////// ????
  list(list &&rhs) = default;
  list &operator=(list &&rhs) = default;
  ////// ????
  ~list() {
    while (!empty()) {
      pop_front();
    }
    delete lst_;
  }

public:
  void push_back(T &&t) {
    Node *tmp = new Node(t, lst_->prev_, lst_);
    /////////////////////
    (lst_->prev_ ? lst_->prev_->next_ : fst_) = tmp;
    ++size_;
  }
  void push_back(const T &t) {
    T tmp(t);
    push_back(std::move(tmp));
  }
  void push_front(T &&t) {
    Node *tmp = new Node(t, nullptr, fst_);
    /////////////////////
    fst_ = tmp;
    ++size_;
  }
  void push_front(const T &t) {
    T tmp(t);
    push_front(std::move(tmp));
  }

public:
  void pop_back() {
    if (empty())
      throw std::runtime_error("List is empty");
    Node *tmp = lst_->prev_;
    tmp->prev_->next_ = lst_;
    lst_->prev_ = tmp->prev_;
    --size_;
    delete tmp;
  }
  void pop_front() {
    if (empty())
      throw std::runtime_error("List is empty");
    Node *tmp = fst_;
    fst_ = fst_->next_;
    --size_;
    delete tmp;
  }

public:
  reference front() {
    if (empty())
      throw std::runtime_error("List is empty");
    return *(fst_->data_);
  }
  const_reference front() const {
    if (empty())
      throw std::runtime_error("List is empty");
    return *(fst_->data_);
  }
  reference back() {
    if (empty())
      throw std::runtime_error("List is empty");
    return *(lst_->prev_->data_);
  }
  const_reference back() const {
    if (empty())
      throw std::runtime_error("List is empty");
    return *(lst_->prev_->data_);
  }

public:
  struct list_iterator__ {
    friend list;
    using iterator = list_iterator__;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using difference_type = ptrdiff_t;
    using size_type = size_t;

  private:
    Node *nde_;

  public:
    list_iterator__() = default;
    list_iterator__(Node *nde) : nde_(nde) {}
    list_iterator__(const iterator &) = default;
    list_iterator__ &operator=(const iterator &) = default;
    ~list_iterator__() = default;

  public:
    iterator &operator++() noexcept {
      nde_ = nde_->next_;
      return *this;
    }
    iterator &operator++(int) noexcept {
      auto old = *this;
      ++(*this);
      return old;
    }
    iterator &operator--() noexcept {
      nde_ = nde_->prev_;
      return *this;
    }
    iterator &operator--(int) noexcept {
      auto old = *this;
      --(*this);
      return old;
    }
    bool operator==(const iterator &rhs) const noexcept {
      return nde_->next_ == rhs.nde_->next_ && nde_->prev_ == rhs.nde_->prev_;
    }
    bool operator!=(const iterator &rhs) const noexcept {
      return !(*this == rhs);
    }

  public:
    pointer operator->() { return nde_->data_; }
    const pointer operator->() const { return nde_->data_; }

    reference operator*() { return *(nde_->data_); }
    reference operator*() const { return *(nde_->data_); }
  };
  class const_list_iterator__ final {
    list_iterator__ it_;

  public:
    using iterator = const_list_iterator__;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using difference_type = ptrdiff_t;
    using size_type = size_t;
  public:
    const_list_iterator__(const list_iterator__ &it) : it_(it) {}
    const_list_iterator__(const iterator &it) = default;
    const_list_iterator__ &operator=(const iterator&) = default;
    
    const T &operator*() const noexcept { return *it_; }

    iterator &operator++() {
      ++it_;
      return *this;
    }
    iterator& operator++(int) { return it_++; }

    iterator &operator--() {
      --it_;
      return *this;
    }
    iterator& operator--(int) { return it_--; }

    bool operator==(const iterator &) const noexcept = default;
    bool operator!=(const iterator &) const noexcept = default;
  };

public:
  using iterator = list_iterator__;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_iterator = const_list_iterator__;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
  iterator begin() { return iterator(fst_); }
  iterator end() { return iterator(lst_); }
  const_iterator begin() const {return const_iterator(iterator(fst_));}
  const_iterator end() const {return const_iterator(iterator(lst_));}

  const_iterator cbegin() const {return const_iterator(begin());}
  const_iterator cend() const {return const_iterator(end());}

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end());}
  const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

  const_reverse_iterator crbegin() const {return const_reverse_iterator(end());}
  const_reverse_iterator crend() const {return const_reverse_iterator(begin());}

public:
  bool empty() { return begin() == end(); }
  size_t size() const { return size_; }
  size_t max_size() const { return std::numeric_limits<size_t>::max(); }
};
/////////// нужно подумать, как сделать const_iterator
/////////// ещё тесты написать
/////////// баги если что половить
template <typename Iter>
list(Iter fst, Iter lst)
    -> list<typename std::iterator_traits<Iter>::value_type>;
} // namespace msd
template <typename T>
bool operator==(const msd::list<T> &lhs, const msd::list<T> &rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <typename T>
bool operator!=(const msd::list<T> &lhs, const msd::list<T> &rhs) {
  return !(lhs == rhs);
}

#endif
