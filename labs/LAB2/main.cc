#include "Figures/Circle.hh"
#include "Figures/ManhattanCircle.hh"
#include "Figures/TFigure.hh"
#include "MSDCore/exceptions.hh"
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <iostream>
#include <list>
#include <memory>
#include <numbers>
#include <queue>
#include <set>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

class FigureGui {
public:
  bool show_ = true, show_gui_ = false;

public:
  virtual Figure::TFigure *getFig() = 0;

  virtual void Show() = 0;
  virtual ~FigureGui() = default;
};

class CircleGui final : public FigureGui {
  Figure::Circle *&fig_;
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

public:
  CircleGui(Figure::Circle *&fig) : fig_(fig), gen(std::random_device{}()) {}
  Figure::TFigure *getFig() override { return fig_; }
  void Show() override {
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
    }
    if (ImGui::Button("Create new object")) {
      auto *tmp = new Figure::Circle({150, 150}, 50);
      std::swap(tmp, fig_);
      delete tmp;
    }
    ImGui::End();
  }
};

class ManhtattanCircleGui final : public FigureGui {
  Figure::ManhattanCircle *&fig_;
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

public:
  ManhtattanCircleGui(Figure::ManhattanCircle *&fig)
      : fig_(fig), gen(std::random_device{}()) {}
  Figure::TFigure *getFig() override { return fig_; }
  void Show() override {
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
};

struct FigureList {
  std::list<
      std::pair<std::shared_ptr<Figure::TFigure>, std::shared_ptr<FigureGui>>>
      fig_;
  bool show_insert_ = false;

  void insert() {
    ImGui::Begin("insert", &show_insert_);
    std::vector<std::string> items = {"GGGG", "HHHH",       "IIII", "JJJJ",
                                      "KKKK", "LLLLLLL",    "MMMM", "OOOOOOO",
                                      "PPPP", "QQQQQQQQQQ", "RRR",  "SSSS"};
    static std::string current_item = "";
    if (ImGui::BeginCombo("WTF", current_item.c_str())) {
      for (auto &i: items)
        if (ImGui::Selectable(i.c_str()))
          current_item = i;
      ImGui::EndCombo();
    }
    ImGui::Text("%s", current_item.c_str());

    ImGui::End();
  }
};

class App final {
  bool run_ = true;
  char name_[255] = "Lab 2";
  SDL_Window *win_ =
      SDL_CreateWindow(name_, 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  SDL_Renderer *ren_ = SDL_CreateRenderer(
      win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  bool show_settings_ = false;
  float color_[3] = {0.f, 0.f, 0.f};
  char windowtitle_[255] = "Lab 1";

  FigureList fl_;

  std::queue<std::shared_ptr<Figure::TFigure>> rq_;

public:
  App() {
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
    ImGui::StyleColorsClassic();
  }
  ~App() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
  }
  App(const App &) = delete;
  App(App &&) = delete;
  App &operator=(const App &) = delete;
  App &operator=(App &&) = delete;

public:
  void run() {
    run_ = true;
    while (run_) {
      PollEvent();
      GUI_Render();
      update();
      render();
    }
  }

private:
  void render() {
    SDL_SetRenderDrawColor(ren_, static_cast<uint8_t>(color_[0] * 255),
                           static_cast<uint8_t>(color_[1] * 255),
                           static_cast<uint8_t>(color_[2] * 255), 0xFF);
    SDL_RenderClear(ren_);
    SDL_SetRenderDrawColor(ren_, 0xFF, 0xFF, 0xFF, 0xFF);
    // for (; !rq_.empty(); rq_.pop())
    //   rq_.front()->Show(ren_);
    while (!rq_.empty()) {
      rq_.front()->Show(ren_);
      rq_.pop();
    }

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

    SDL_RenderPresent(ren_);
  }
  void GUI_Render() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("Window")) {
        ImGui::MenuItem("Settings", nullptr, &show_settings_);
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("List")) {
        ImGui::MenuItem("insert", nullptr, &fl_.show_insert_);
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
    if (fl_.show_insert_)
      fl_.insert();
    ImGui::Render();
  }
  void update() {
    auto c = std::make_shared<Figure::ManhattanCircle>(VR2{150, 150}, 50);
    c->Rotate(std::numbers::pi / 6);
    rq_.push(c);
  }
  void PollEvent() {
    SDL_Event e{};
    while (SDL_PollEvent(&e) != 0) {
      ImGui_ImplSDL2_ProcessEvent(&e);
      if (e.type == SDL_QUIT)
        run_ = false;
    }
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
