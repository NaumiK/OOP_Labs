#include "Figures/ManhattanCircle.hh"
#include <imgui.h>
#include <numbers>

Figure::ManhattanCircle::ManhattanCircle(int32_t x, int32_t y, int32_t r)
    : x_(x), y_(y), r_(r) {}

int32_t Figure::ManhattanCircle::po(int32_t ax, int32_t ay, int32_t bx,
                                    int32_t by) {
  auto dx = bx - ax, dy = by - ay;
  return abs(dx) + abs(dy);
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
  SDL_RenderDrawPoint(s, x_, y_); // <-- Center
  int32_t curx = r_, cury = 0;
  using std::numbers::pi;

  while (curx > 0) {
    SDL_RenderDrawPoint(s, x_ + rotatex(alpha_, curx, cury),
                        y_ + rotatey(alpha_, curx, cury));
    SDL_RenderDrawPoint(s, x_ + rotatex(alpha_ + pi / 2, curx, cury),
                        y_ + rotatey(alpha_ + pi / 2, curx, cury));
    SDL_RenderDrawPoint(s, x_ + rotatex(alpha_ + pi, curx, cury),
                        y_ + rotatey(alpha_ + pi, curx, cury));
    SDL_RenderDrawPoint(s, x_ + rotatex(alpha_ - pi / 2, curx, cury),
                        y_ + rotatey(alpha_ - pi / 2, curx, cury));

    auto sxx = curx - 1, sxy = cury, syx = curx, syy = cury + 1;
    if (std::abs(po(sxx, sxy, 0, 0) - r_) < std::abs(po(syx, syy, 0, 0) - r_))
      curx = sxx, cury = sxy;
    else
      curx = syx, cury = syy;
  }
}

int32_t Figure::ManhattanCircle::GetRadius() const { return r_; }
int32_t Figure::ManhattanCircle::GetX() const { return x_; }
int32_t Figure::ManhattanCircle::GetY() const { return y_; }
double Figure::ManhattanCircle::GetAngle() const { return alpha_; }

void Figure::ManhattanCircle::SetRadius(int32_t r) { r_ = r; }
void Figure::ManhattanCircle::SetPosition(int32_t x, int32_t y) {
  x_ = x, y_ = y;
}
void Figure::ManhattanCircle::SetAngle(double alpha) { alpha_ = alpha; }

void Figure::ManhattanCircle::MoveTo(int32_t dx, int32_t dy) {
  x_ += dx, y_ += dy;
}

void Figure::ManhattanCircle::Rotate(double da) { SetAngle(alpha_ + da); }
