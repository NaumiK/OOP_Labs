#include "FigureGui/CircleGui.hh"
#include "Figure/Circle.hh"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

FigureGui::CircleGui::CircleGui(Figure::ICircle *&fig)
    : fig_(fig), gen(std::random_device{}()) {}
Figure::TFigure *FigureGui::CircleGui::getFig() { return fig_; }
void FigureGui::CircleGui::Show() {
  if (!show_gui_)
    return;
  ImGui::Begin("Circle", &show_gui_);
  if (fig_ != nullptr) {
    int32_t r = fig_->GetRadius();
    VR2 xy = fig_->GetPosition();
    ImGui::SliderInt("Radius", &r, 0, 1000);
    ImGui::SliderInt2("Coordinates", &xy.x, -500, 500);
    ImGui::Checkbox("Show", &show_);
    fig_->SetRadius(r);
    fig_->SetPosition(xy);
    if (ImGui::Button("Random move")) {
      fig_->MoveTo({dist(gen), dist(gen)});
    }
    if (ImGui::Button("Delete object")) {
      delete fig_;
      fig_ = nullptr;
    }
  }
  if (ImGui::Button("Create new object")) {
    Figure::ICircle *tmp = new Figure::Circle({150, 150}, 50);
    std::swap(tmp, fig_);
    delete tmp;
  }
  ImGui::End();
}
