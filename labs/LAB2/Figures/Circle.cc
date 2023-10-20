#include "Figures/Circle.hh"
#include "VR2.hh"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

Figure::Circle::Circle(VR2 O, int32_t r) : O_(O), r_(r) {}

int32_t Figure::Circle::po(VR2 a, VR2 b) {
  auto d = b - a;
  return d.x * d.x + d.y * d.y;
}

void Figure::Circle::Show(SDL_Renderer *s) {
  int32_t sqrr = r_ * r_;
  SDL_RenderDrawPoint(s, O_.x, O_.y); // <-- Center
  VR2 cur = {r_, 0}, O = {0, 0};
  while (cur.x > cur.y) {
    VR2 sx = {cur.x - 1, cur.y}, sy = {cur.x, cur.y - 1};

    SDL_RenderDrawPoint(s, O_.x + cur.x, O_.y + cur.y);
    SDL_RenderDrawPoint(s, O_.x - cur.x, O_.y + cur.y);
    SDL_RenderDrawPoint(s, O_.x + cur.x, O_.y - cur.y);
    SDL_RenderDrawPoint(s, O_.x - cur.x, O_.y - cur.y);
    //                               .             .
    SDL_RenderDrawPoint(s, O_.x + cur.y, O_.y + cur.x);
    SDL_RenderDrawPoint(s, O_.x - cur.y, O_.y + cur.x);
    SDL_RenderDrawPoint(s, O_.x + cur.y, O_.y - cur.x);
    SDL_RenderDrawPoint(s, O_.x - cur.y, O_.y - cur.x);

    if (std::abs(po(sx, O) - sqrr) < std::abs(po(sy, O) - sqrr))
      cur = sx;
    else
      cur = sy;
  }
}

int32_t Figure::Circle::GetRadius() const { return r_; }
VR2 Figure::Circle::GetPosition() const { return O_; }

void Figure::Circle::SetRadius(int32_t r) { r_ = r; }

void Figure::Circle::SetPosition(VR2 O) { O_ = O; }

void Figure::Circle::MoveTo(VR2 v) { O_ += v; }
