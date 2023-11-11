#include "Figure/Square.hh"
#include <SDL_rect.h>
#include <iostream>

Figure::Square::Square(VR2 O, int32_t a, double alpha)
    : O_(O), a_(a), alpha_(alpha) {
      std::cout << "Square()\n";
    }

void Figure::Square::Rotate(double da) { alpha_ += da; }
void Figure::Square::MoveTo(VR2 v) { O_ += v; }

void Figure::Square::SetPosition(VR2 v) { O_ = v; }
void Figure::Square::SetASize(int32_t a) { a_ = a; }
void Figure::Square::SetAngle(double angle) { alpha_ = angle; }

double Figure::Square::GetAngle() const { return alpha_; }
int32_t Figure::Square::GetASize() const { return a_; }

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

void Figure::Square::Show(SDL_Renderer *r) {
  int32_t a = a_ / 2;
  SDL_Point p[] = {
      {O_.x + rotatex(alpha_, a, a), O_.y + rotatey(alpha_, a, a)},
      {O_.x + rotatex(alpha_, -a, a), O_.y + rotatey(alpha_, -a, a)},
      {O_.x + rotatex(alpha_, -a, -a), O_.y + rotatey(alpha_, -a, -a)},
      {O_.x + rotatex(alpha_, a, -a), O_.y + rotatey(alpha_, a, -a)},
      {O_.x + rotatex(alpha_, a, a), O_.y + rotatey(alpha_, a, a)},
  };
  SDL_RenderDrawLines(r, p, 5);
}
