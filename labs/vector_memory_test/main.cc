#include "MSDCore/vector.hh"
#include <iostream>
#include <new>
#include <list>
#include "MSDCore/list.hh"

struct Controllable {
  inline static int control = 5;
  int *resource_;
  Controllable() : resource_(new int(42)) {}

  Controllable(Controllable &&rhs) noexcept : resource_(rhs.resource_) {
    rhs.resource_ = nullptr;
  }
  Controllable &operator=(Controllable &&rhs) noexcept {
    std::swap(resource_, rhs.resource_);
    return *this;
  }
  Controllable(const Controllable &rhs) : resource_(new int(*rhs.resource_)) {
    if (control == 0) {
      control = 5;
      std::cout << "Control reached\n";
      throw std::bad_alloc{};
    }
    control -= 1;
  }
  Controllable &operator=(const Controllable &rhs) {
    Controllable tmp(rhs);
    std::swap(*this, tmp);
    return *this;
  }

  ~Controllable() { delete resource_; }
};

void test1() {
  Controllable c1, c2, c3;
  msd::vector<Controllable> vv1(1);
  vv1.push_back(c1);
  vv1.push_back(c2);
  vv1.push_back(c3);
  std::cout << "Invoke copy ctor\n";
  msd::vector<Controllable> vv2(vv1); // oops
  std::cout << vv2.size() << std::endl;
}

int main() try {
  std::list l = {1, 2, 3};
  msd::list<int> ml;
  for (auto &&i: l)
    ml.push_back(i);
  for (auto &&i: ml)
    std::cout << i << " ";
  std::cout << "\n";
  bool actual = std::equal(l.begin(), l.end(), ml.begin(), ml.end());
  test1();
} catch (std::bad_alloc &) {
  std::cout << "Exception catched\n";
}
