#include "Figures/Circle.hh"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

Figure::Circle::Circle(int32_t x, int32_t y, uint32_t r)
    : x_(x), y_(y), r_(r) {}

int32_t Figure::Circle::po(int32_t ax, int32_t ay, int32_t bx, int32_t by) {
  auto dx = bx - ax, dy = by - ay;
  return dx * dx + dy * dy;
  // return dx * dx + 4 * dy * dy;
  // return (std::abs(dx) + std::abs(dy)) * (std::abs(dx) + std::abs(dy));
  // return std::abs(dx*dy);
  // return (std::abs(dx) + std::abs(4 * dy)) *
  //        (std::abs(dx) + std::abs(4 * dy));
}

void Figure::Circle::Show(SDL_Renderer *s) {
  int32_t sqrr = r_ * r_;
  SDL_RenderDrawPoint(s, x_, y_); // <-- Center
  int32_t curx = r_, cury = 0;
  while (curx >= cury) {
    auto sxx = curx - 1, sxy = cury, syx = curx, syy = cury + 1;
    // std::cout << std::abs(po(sx, O) - sqrr) << " "
    //           << std::abs(po(sy, O) - sqrr) << "\n";

    SDL_RenderDrawPoint(s, x_ + curx, y_ + cury);
    SDL_RenderDrawPoint(s, x_ - curx, y_ + cury);
    SDL_RenderDrawPoint(s, x_ + curx, y_ - cury);
    SDL_RenderDrawPoint(s, x_ - curx, y_ - cury);
    //
    SDL_RenderDrawPoint(s, x_ + cury, y_ + curx);
    SDL_RenderDrawPoint(s, x_ - cury, y_ + curx);
    SDL_RenderDrawPoint(s, x_ + cury, y_ - curx);
    SDL_RenderDrawPoint(s, x_ - cury, y_ - curx);

    if (std::abs(po(sxx, sxy, 0, 0) - sqrr) <
        std::abs(po(syx, syy, 0, 0) - sqrr))
      curx = sxx, cury = sxy;
    else
      curx = syx, cury = syy;
  }
}

#if 0
void Figure::Circle::GUI_Show() {
  if (!show_gui)
    return;
  ImGui::Begin("Circle", &show_gui);
  ImGui::SliderInt("Radius", &r_, 0, 1000);
  ImGui::SliderInt2("Coordinates", &xy_.x, -500, 500);
  ImGui::Checkbox("Show", &show_);
  if (ImGui::Button("Random move")) {
    MoveTo({dist(gen), dist(gen)});
  }
  ImGui::End();
}

bool &Figure::Circle::GetGuiTrigger() { return show_gui; }
#endif

uint32_t Figure::Circle::GetRadius() const { return r_; }

int32_t Figure::Circle::GetX() const { return x_; }
int32_t Figure::Circle::GetY() const { return y_; }

#if 0
VR2 Figure::Circle::GetPostion() const { return xy_; }
#endif

void Figure::Circle::SetRadius(uint32_t r) { r_ = r; }

void Figure::Circle::SetPosition(int32_t x, int32_t y) { x_ = x, y_ = y; }

void Figure::Circle::MoveTo(int32_t dx, int32_t dy) { x_ += dx, y_ += dy; }
