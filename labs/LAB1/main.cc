#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_surface.h>

#include <SDL_video.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <iostream>
#include <numbers>
#include <random>

#include "Figures/ManhattanCircle.hh"
#include "MSDCore/exceptions.hh"

#include "Figures/Circle.hh"

class App final {
  SDL_Window *win_ =
      SDL_CreateWindow("Lab 1", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  SDL_Renderer *ren_ = SDL_CreateRenderer(
      win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  bool running_ = true;
  float color_[3] = {0.f, 0.f, 0.f};
  char windowtitle_[255] = "Lab 1";
  bool show_settings_ = false;

  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

  bool show_mc_gui_ = false, show_mc_ = true;
  Figure::ManhattanCircle *mc_ = new Figure::ManhattanCircle(150, 150, 50);

  bool show_c_gui_ = false, show_c_ = true;
  Figure::Circle *c_ = new Figure::Circle(150, 150, 50);

public:
  App() : gen(std::random_device{}()) {
    if (win_ == NULL)
      throw sdl_error("SDL_CreateWindow error");
    if (ren_ == NULL)
      throw sdl_error("SDL_CreateRenderer error");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplSDL2_InitForSDLRenderer(win_, ren_);
    ImGui_ImplSDLRenderer2_Init(ren_);
  }
  App(const App &) = delete;
  App(App &&) = delete;
  App &operator=(const App &) = delete;
  App &operator=(App &&) = delete;

  ~App() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    delete mc_;
    delete c_;

    SDL_DestroyRenderer(ren_);
    SDL_DestroyWindow(win_);
  }

  void run() {
    running_ = true;
    while (running_) {
      processEvent();
      imGuiRender();
      update();
      render();
    }
  }

  float get_scale() const {
    int window_width = 0;
    int windows_height = 0;
    SDL_GetWindowSize(win_, &window_width, &windows_height);

    int render_output_width = 0;
    int render_output_height = 0;
    SDL_GetRendererOutputSize(ren_, &render_output_width,
                              &render_output_height);

    const auto scale_x = static_cast<float>(render_output_width) /
                         static_cast<float>(window_width);
    return scale_x;
  }

private:
  void processEvent() {
    SDL_Event e{};
    while (SDL_PollEvent(&e) != 0) {
      ImGui_ImplSDL2_ProcessEvent(&e);
      if (e.type == SDL_QUIT)
        running_ = false;
    }
  }

  void update() {}

  void GuiCircle(bool &show_gui, bool &show, Figure::Circle *&c) {
    if (!show_gui)
      return;
    ImGui::Begin("Circle", &show_gui);
    if (c != nullptr) {
      int32_t r = c->GetRadius();
      int32_t xy[] = {c->GetX(), c->GetY()};
      ImGui::SliderInt("Radius", &r, 0, 1000);
      ImGui::SliderInt2("Coordinates", xy, -500, 500);
      ImGui::Checkbox("Show", &show);
      c->SetRadius(r);
      c->SetPosition(xy[0], xy[1]);
      if (ImGui::Button("Random move")) {
        c->MoveTo(dist(gen), dist(gen));
      }
      if (ImGui::Button("Delete object")) {
        delete c;
        c = nullptr;
      }
    }
    if (ImGui::Button("Create new object")) {
      auto *tmp = new Figure::Circle(150, 150, 50);
      std::swap(tmp, c);
      delete tmp;
    }
    ImGui::End();
  }

  void GuiManhattanCircle(bool &show_gui, bool &show,
                          Figure::ManhattanCircle *&c) {
    if (!show_gui)
      return;
    ImGui::Begin("Manhattan Circle", &show_gui);
    if (c != nullptr) {
      int32_t r = c->GetRadius();
      int32_t xy[] = {c->GetX(), c->GetY()};
      float a = c->GetAngle();
      ImGui::SliderInt("Radius", &r, 0, 1000);
      ImGui::SliderInt2("Coordinates", xy, -500, 500);
      ImGui::Checkbox("Show", &show);
      ImGui::SliderFloat("Angle", &a, 0, 2 * std::numbers::pi);
      c->SetRadius(r);
      c->SetPosition(xy[0], xy[1]);
      c->SetAngle(a);
      if (ImGui::Button("Random move")) {
        c->MoveTo(dist(gen), dist(gen));
      }
      if (ImGui::Button("Delete object")) {
        delete c;
        c = nullptr;
      }
    }
    if (ImGui::Button("Create new object")) {
      auto *tmp = new Figure::ManhattanCircle(150, 150, 50);
      std::swap(tmp, c);
      delete tmp;
    }
    ImGui::End();
  }

  void imGuiRender() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("Window")) {
        ImGui::MenuItem("Settings", nullptr, &show_settings_);
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Figures")) {
        ImGui::MenuItem("Circle", nullptr, &show_c_gui_);
        ImGui::MenuItem("ManhattanCircle", nullptr, &show_mc_gui_);
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
    if (show_settings_) {
      ImGui::Begin("Window settings", &show_settings_);
      ImGui::ColorEdit3("Backgound color", color_);
      ImGui::InputText("Window title", windowtitle_, 255);
      if (ImGui::Button("Update window title"))
        SDL_SetWindowTitle(win_, windowtitle_);
      ImGui::End();
    }
    GuiManhattanCircle(show_mc_gui_, show_mc_, mc_);
    GuiCircle(show_c_gui_, show_c_, c_);
    ImGui::Render();
  }

  void render() {
    SDL_SetRenderDrawColor(ren_, static_cast<uint8_t>(color_[0] * 255),
                           static_cast<uint8_t>(color_[1] * 255),
                           static_cast<uint8_t>(color_[2] * 255), 0xFF);
    SDL_RenderClear(ren_);
    SDL_SetRenderDrawColor(ren_, 0xFF, 0xFF, 0xFF, 0xFF);
    if (show_mc_ && mc_ != nullptr)
      mc_->Show(ren_);
    if (show_c_ && c_ != nullptr)
      c_->Show(ren_);
    // mc_->Rotate(0.1);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

    SDL_RenderPresent(ren_);
  }
};

int main(int argc, char **argv) try {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    throw sdl_error("SDL_Init");
  {
    App app;
    app.run();
  }
  SDL_Quit();

  return 0;
} catch (sdl_error &e) {
  std::cerr << "SDL error: " << e.what() << std::endl;
  return 1;
} catch (std::runtime_error &e) {
  std::cerr << "Runtime error: " << e.what() << std::endl;
  return 1;
} catch (std::exception &e) {
  std::cerr << "Standard exception: " << e.what() << std::endl;
  return 1;
} catch (...) {
  std::cerr << "Unknown error" << std::endl;
  return 1;
}
