#include "Figures/Circle.hh"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

Figure::Circle::Circle(VR2 xy, uint32_t r)
    : xy_(xy), r_(r), gen(std::random_device{}()) {}

int32_t Figure::Circle::po(const VR2 &x, const VR2 &y) {
  auto dx = y.x - x.x, dy = y.y - x.y;
  return dx * dx + dy * dy;
  // return dx * dx + 4 * dy * dy;
  // return (std::abs(dx) + std::abs(dy)) * (std::abs(dx) + std::abs(dy));
  // return std::abs(dx*dy);
  // return (std::abs(dx) + std::abs(4 * dy)) *
  //        (std::abs(dx) + std::abs(4 * dy));
}

void Figure::Circle::Show(SDL_Renderer *s) {
  if (!show_)
    return;
  auto sqrr = r_ * r_;
  SDL_RenderDrawPoint(s, xy_.x, xy_.y); // <-- Center
  VR2 cur = VR2{r_, 0};                 // delta
  VR2 O = {0, 0};
  while (cur.x > 0) {
    auto sx = cur + VR2{-1, 0}, sy = cur + VR2{0, 1};
    // std::cout << std::abs(po(sx, O) - sqrr) << " "
    //           << std::abs(po(sy, O) - sqrr) << "\n";

    SDL_RenderDrawPoint(s, xy_.x + cur.x, xy_.y + cur.y);
    SDL_RenderDrawPoint(s, xy_.x - cur.x, xy_.y + cur.y);
    SDL_RenderDrawPoint(s, xy_.x + cur.x, xy_.y - cur.y);
    SDL_RenderDrawPoint(s, xy_.x - cur.x, xy_.y - cur.y);
    //
    // SDL_RenderDrawPoint(s, xy_.x + cur.y, xy_.y + cur.x);
    // SDL_RenderDrawPoint(s, xy_.x - cur.y, xy_.y + cur.x);
    // SDL_RenderDrawPoint(s, xy_.x + cur.y, xy_.y - cur.x);
    // SDL_RenderDrawPoint(s, xy_.x - cur.y, xy_.y - cur.x);

    if (std::abs(po(sx, O) - sqrr) < std::abs(po(sy, O) - sqrr))
      cur = sx;
    else
      cur = sy;
  }
}

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

uint32_t Figure::Circle::GetRadius() const { return r_; }

VR2 Figure::Circle::GetPostion() const { return xy_; }

void Figure::Circle::SetRadius(uint32_t r) { r_ = r; }

void Figure::Circle::SetPosition(const VR2 &pos) { xy_ = pos; }

void Figure::Circle::MoveTo(const VR2 &dlta) { xy_ = xy_ + dlta; }
