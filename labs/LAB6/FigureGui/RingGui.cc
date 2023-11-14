#include "FigureGui/RingGui.hh"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

FigureGui::RingGui::RingGui(Figure::Ring *&fig) : fig_(fig), gen(std::random_device{}()) {}
Figure::TFigure *FigureGui::RingGui::getFig() { return fig_; }
void FigureGui::RingGui::Show() {
  if (!show_gui_)
    return;
  ImGui::Begin("Ring", &show_gui_);
  if (fig_ != nullptr) {
    int32_t r = fig_->GetRadius();
    VR2 xy = fig_->GetPosition();
    int32_t t = fig_->GetThickness();
    ImGui::SliderInt("Radius", &r, 0, 1000);
    ImGui::SliderInt2("Coordinates", &xy.x, -500, 500);
    ImGui::Checkbox("Show", &show_);
    ImGui::SliderInt("Thickness", &t, 0, 50);
    fig_->SetRadius(r);
    fig_->SetPosition(xy);
    fig_->SetThickness(t);
    if (ImGui::Button("Random move")) {
      fig_->MoveTo({dist(gen), dist(gen)});
    }

    if (ImGui::Button("Delete object")) {
      delete fig_;
      fig_ = nullptr;
    }
  }
  if (ImGui::Button("Create new object")) {
    auto *tmp = new Figure::Ring({150, 150}, 50, 5);
    std::swap(tmp, fig_);
    delete tmp;
  }
  ImGui::End();
}
