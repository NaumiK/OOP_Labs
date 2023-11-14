#include "FigureGui/ManhattanCircleGui.hh"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <numbers>

FigureGui::ManhtattanCircleGui::ManhtattanCircleGui(Figure::ManhattanCircle *&fig)
    : fig_(fig), gen(std::random_device{}()) {}
Figure::TFigure *FigureGui::ManhtattanCircleGui::getFig() { return fig_; }
void FigureGui::ManhtattanCircleGui::Show() {
  if (!show_gui_)
    return;
  ImGui::Begin("Manhattan Circle", &show_gui_);
  if (fig_ != nullptr) {
    int32_t r = fig_->GetRadius();
    VR2 xy = fig_->GetPosition();
    float a = fig_->GetAngle();
    ImGui::SliderInt("Radius", &r, 0, 1000);
    ImGui::SliderInt2("Coordinates", &xy.x, -500, 500);
    ImGui::Checkbox("Show", &show_);
    ImGui::SliderFloat("Angle", &a, 0, 2 * std::numbers::pi);
    fig_->SetRadius(r);
    fig_->SetPosition(xy);
    fig_->SetAngle(a);
    if (ImGui::Button("Random move")) {
      fig_->MoveTo({dist(gen), dist(gen)});
    }
    if (ImGui::Button("Delete object")) {
      delete fig_;
      fig_ = nullptr;
    }
  }
  if (ImGui::Button("Create new object")) {
    auto *tmp = new Figure::ManhattanCircle({150, 150}, 50);
    std::swap(tmp, fig_);
    delete tmp;
  }
  ImGui::End();
}
