#ifndef SFG_SHOWABLE_H
#define SFG_SHOWABLE_H
#include <stdexcept>

template <typename Screen> class Showable {
  struct IShowable {
    virtual void Show_(Screen s) = 0;
    virtual IShowable *clone() = 0;
    virtual ~IShowable() = default;
  };

  template <typename T> class ShowableT : public IShowable {
    T data_;

  public:
    ShowableT(T data) : data_(std::move(data)) {}
    void Show_(Screen s) override { Show(s, data_); }
    virtual IShowable *clone() override { return new ShowableT(this->data_); }
  };

  IShowable *data_;

public:
  template <typename T> Showable(T data) : data_(new ShowableT<T>(data)) {}

  Showable(const Showable &rhs) : data_(nullptr) {
    IShowable *tmp = rhs.data_->clone();
    //////////////////////
    std::swap(data_, tmp);
  }

  Showable(Showable &&rhs) : data_(rhs.data_) { rhs.data_ = nullptr; }

  Showable &operator=(const Showable &rhs) {
    Showable tmp(rhs);
    //////////////////////
    std::swap(*this, tmp);
    return *this;
  }

  Showable &operator=(Showable &&rhs) {
    //////////////////////
    if (this != &rhs) {
      std::swap(data_, rhs.data_);
    }
    return *this;
  }

  ~Showable() { delete data_; }
  friend void Show(Screen s, Showable<Screen> &d) {
    if (d.data_ == nullptr)
      throw std::runtime_error("Showable data is empty");
    d.data_->Show_(s);
  }
};
#endif
