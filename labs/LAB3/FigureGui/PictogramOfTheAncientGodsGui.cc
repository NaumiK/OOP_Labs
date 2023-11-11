#include "FigureGui/PictogramOfTheAncientGodsGui.hh"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <numbers>

FigureGui::PictogramOfTheAncientGodsGui::PictogramOfTheAncientGodsGui(Figure::PictogramOfTheAncientGods *&fig)
    : fig_(fig), gen(std::random_device{}()) {}
Figure::TFigure *FigureGui::PictogramOfTheAncientGodsGui::getFig() { return fig_; }
void FigureGui::PictogramOfTheAncientGodsGui::Show() {
  if (!show_gui_)
    return;
  ImGui::Begin("Pictogram of the ancient gods", &show_gui_);
  if (fig_ != nullptr) {
    int32_t r = fig_->GetRadius();
    VR2 xy = fig_->GetPosition();
    float a = fig_->GetAngle();
    ImGui::SliderInt("Radius", &r, 0, 1000);
    ImGui::SliderInt2("Coordinates", &xy.x, -500, 500);
    ImGui::Checkbox("Show", &show_);
    ImGui::SliderFloat("Angle", &a, 0, std::numbers::pi * 2);
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
    auto *tmp = new Figure::PictogramOfTheAncientGods({150, 150}, 50, 5);
    std::swap(tmp, fig_);
    delete tmp;
  }
  ImGui::End();
}
