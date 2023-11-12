#include "Figure/ManhattanCircle.hh"
#include <imgui.h>
#include <numbers>
#include <iostream>

Figure::ManhattanCircle::ManhattanCircle(VR2 O, int32_t r) : O_(O), r_(r) {
  std::cout << "ManhattanCircle()\n";
}

int32_t Figure::ManhattanCircle::po(VR2 a, VR2 b) {
  auto d = b - a;
  return abs(d.x) + abs(d.y);
  // auto d = b - a;
  // return d.x * d.x + 4 * d.y * d.y;
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

void Figure::ManhattanCircle::Show(SDL_Renderer *s) {
  SDL_RenderDrawPoint(s, O_.x, O_.y); // <-- Center
  VR2 cur = {r_, 0}, O = {0, 0};
  using std::numbers::pi;

  while (cur.x > 0) {
    SDL_RenderDrawPoint(s, O_.x + rotatex(alpha_, cur.x, cur.y),
                        O_.y + rotatey(alpha_, cur.x, cur.y));
    SDL_RenderDrawPoint(s, O_.x + rotatex(alpha_ + pi / 2, cur.x, cur.y),
                        O_.y + rotatey(alpha_ + pi / 2, cur.x, cur.y));
    SDL_RenderDrawPoint(s, O_.x + rotatex(alpha_ + pi, cur.x, cur.y),
                        O_.y + rotatey(alpha_ + pi, cur.x, cur.y));
    SDL_RenderDrawPoint(s, O_.x + rotatex(alpha_ - pi / 2, cur.x, cur.y),
                        O_.y + rotatey(alpha_ - pi / 2, cur.x, cur.y));

    VR2 sx = {cur.x - 1, cur.y}, sy = {cur.x, cur.y - 1};
    if (std::abs( po(sx, O) - r_) < std::abs(po(sy, O) - r_))
      cur = sx;
    else
      cur = sy;
  }
}

int32_t Figure::ManhattanCircle::GetRadius() const { return r_; }
double Figure::ManhattanCircle::GetAngle() const { return alpha_; }
VR2 Figure::ManhattanCircle::GetPosition() const { return O_; }

void Figure::ManhattanCircle::SetRadius(int32_t r) { r_ = r; }
void Figure::ManhattanCircle::SetPosition(VR2 O) { O_ = O; }
void Figure::ManhattanCircle::SetAngle(double alpha) { alpha_ = alpha; }

void Figure::ManhattanCircle::MoveTo(VR2 v) { O_ += v; }

void Figure::ManhattanCircle::Rotate(double da) { SetAngle(alpha_ + da); }
