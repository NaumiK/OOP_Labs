#include "FigureGui/EllipseGui.hh"
#include "Figure/Ellipse.hh"
#include "Figure/IEllipse.hh"
#include "Figure/ManhattanEllipse.hh"
#include <random>

#include <numbers>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

FigureGui::EllipseGui::EllipseGui(Figure::IEllipse *&e)
    : fig_(e), gen(std::random_device{}()) {}


Figure::TFigure *FigureGui::EllipseGui::getFig() {
  return fig_;
}

void FigureGui::EllipseGui::Show() {
  if (!show_gui_)
    return;
  ImGui::Begin("Ellipse", &show_gui_);
  if (fig_ != nullptr) {
    int32_t r = fig_->GetRadius();
    int32_t fl = fig_->GetFocalLength();
    VR2 xy = fig_->GetPosition();
    float a = fig_->GetAngle();
    ImGui::SliderInt("Radius", &r, 0, 1000);
    ImGui::SliderInt("Focal length", &fl, 0, 500);
    ImGui::SliderInt2("Coordinates", &xy.x, -500, 500);
    ImGui::SliderFloat("Angle", &a, 0, 2 * std::numbers::pi);
    ImGui::Checkbox("Show", &show_);
    fig_->SetRadius(r);
    fig_->SetFocalLength(fl);
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
    Figure::IEllipse *tmp = new Figure::Ellipse({200, 200}, 100, 300, std::numbers::pi / 6);
    std::swap(tmp, fig_);
    delete tmp;
  }
  ImGui::End();
}
