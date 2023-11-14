#include "Figure/Rectangle.hh"
#include <SDL_rect.h>
#include <iostream>

Figure::Rectangle::Rectangle(VR2 O, int32_t a, int32_t b, double alpha)
    : Figure::Square(O, a, alpha), b_(b) {
      std::cout << "Rectangle()\n";
    }


void Figure::Rectangle::SetBSize(int32_t b) { b_ = b; }
int32_t Figure::Rectangle::GetBSize() const { return b_; }

namespace {
inline int32_t rotatex(double alpha, int32_t x, int32_t y) {
  double a_ = cos(alpha), b_ = sin(alpha);
  return x * a_ + y * b_;
}

inline int32_t rotatey(double alpha, int32_t x, int32_t y) {
  double c_ = -sin(alpha), d_ = cos(alpha);
  return x * c_ + y * d_;
}
} // namespace

void Figure::Rectangle::Show(SDL_Renderer *r) {
  int32_t a = a_ / 2, b = b_ / 2;
  SDL_Point p[] = {
      {O_.x + rotatex(alpha_, a, b), O_.y + rotatey(alpha_, a, b)},
      {O_.x + rotatex(alpha_, -a, b), O_.y + rotatey(alpha_, -a, b)},
      {O_.x + rotatex(alpha_, -a, -b), O_.y + rotatey(alpha_, -a, -b)},
      {O_.x + rotatex(alpha_, a, -b), O_.y + rotatey(alpha_, a, -b)},
      {O_.x + rotatex(alpha_, a, b), O_.y + rotatey(alpha_, a, b)},
  };
  SDL_RenderDrawLines(r, p, 5);
}
