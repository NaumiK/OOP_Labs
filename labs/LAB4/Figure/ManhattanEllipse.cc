#include "Figure/ManhattanEllipse.hh"
#include "VR2.hh"
#include <SDL_render.h>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numbers>

Figure::ManhattanEllipse::ManhattanEllipse(VR2 O, int32_t focal_length,
                                           int32_t r, double alpha = 0)
    : F_(focal_length), O_(O), r_(r), alpha_(alpha) {
  std::cout << "ManhattanEllipse()\n";
}

Figure::ManhattanEllipse Figure::ManhattanEllipse::CreateViaABNotation(
    VR2 O, int32_t a_half_axis, int32_t b_half_axis, double alpha) {
  return {O,
          static_cast<int32_t>(
              abs(b_half_axis * b_half_axis - a_half_axis * a_half_axis)),
          2 * a_half_axis, alpha};
}

int32_t Figure::ManhattanEllipse::po(VR2 a, VR2 b) {
  auto d = b - a;
  return abs(d.x) + abs(d.y);
}

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

void Figure::ManhattanEllipse::Show(SDL_Renderer *s) {
  VR2 F1 = {F_, 0}, F2 = {-F_, 0};
  VR2 cur = {r_ / 2, 0}, O = {0, 0};
  using std::numbers::pi;

  while (cur.x > 0) {
    SDL_RenderDrawPoint(s, O_.x + rotatex(alpha_, cur.x, cur.y),
                        O_.y + rotatey(alpha_, cur.x, cur.y));
    SDL_RenderDrawPoint(s, O_.x + rotatex(alpha_, -cur.x, cur.y),
                        O_.y + rotatey(alpha_, -cur.x, cur.y));
    SDL_RenderDrawPoint(s, O_.x + rotatex(alpha_ + pi, cur.x, cur.y),
                        O_.y + rotatey(alpha_ + pi, cur.x, cur.y));
    SDL_RenderDrawPoint(s, O_.x + rotatex(alpha_ + pi, -cur.x, cur.y),
                        O_.y + rotatey(alpha_ + pi, -cur.x, cur.y));

    VR2 sx = {cur.x - 1, cur.y}, sy = {cur.x, cur.y + 1};
    if (std::abs(po(sx, F1) + po(sx, F2) - r_) <=
        std::abs(po(sy, F1) + po(sy, F2) - r_))
      cur = sx;
    else
      cur = sy;
  }
  SDL_SetRenderDrawColor(s, 0xFF, 0x00, 0x00, 0xFF);
  SDL_Rect r = {O_.x, O_.y, 5, 5};
  SDL_RenderDrawRect(s, &r);
  SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Figure::ManhattanEllipse::MoveTo(VR2 v) { O_ += v; }

void Figure::ManhattanEllipse::Rotate(double da) { alpha_ += da; }

int32_t Figure::ManhattanEllipse::GetA() const { return 2 * r_; }

int32_t Figure::ManhattanEllipse::GetB() const {
  auto a = GetA();
  return sqrt(F_ * F_ + a * a);
}

int32_t Figure::ManhattanEllipse::GetRadius() const { return r_; }

int32_t Figure::ManhattanEllipse::GetFocalLength() const { return F_; }

VR2 Figure::ManhattanEllipse::GetPosition() const { return O_; }

double Figure::ManhattanEllipse::GetAngle() const { return alpha_; }

void Figure::ManhattanEllipse::SetRadius(int32_t r) { r_ = r; }

void Figure::ManhattanEllipse::SetFocalLength(int32_t fl) { F_ = fl; };

void Figure::ManhattanEllipse::SetPosition(VR2 v) { O_ = v; }

void Figure::ManhattanEllipse::SetAngle(double alpha) { alpha_ = alpha; }
