#include "Figure/Ellipse.hh"
#include "Figure/ManhattanEllipse.hh"
#include "Figure/PictogramOfTheAncientGods.hh"
#include "Figure/Rectangle.hh"
#include "Figure/Ring.hh"
#include "FigureGui/CircleGui.hh"
#include "FigureGui/EllipseGui.hh"
#include "FigureGui/ManhattanCircleGui.hh"
#include "FigureGui/PictogramOfTheAncientGodsGui.hh"
#include "FigureGui/RingGui.hh"
#include "MSDCore/exceptions.hh"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include <iostream>
#include <memory>
#include <numbers>
#include <queue>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <random>

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

  SDL_Surface *ico_ = IMG_Load("./ellipse.png");

  Figure::ICircle *c_ = new Figure::Circle({150, 150}, 50);
  FigureGui::CircleGui gc_;

  Figure::ManhattanCircle *mc_ = new Figure::ManhattanCircle({150, 150}, 50);
  FigureGui::ManhtattanCircleGui gmc_;

  Figure::Ring *r_ = new Figure::Ring({150, 200}, 50, 10);
  FigureGui::RingGui gr_;

  Figure::PictogramOfTheAncientGods *potag_ =
      new Figure::PictogramOfTheAncientGods({150, 150}, 50, 0);
  FigureGui::PictogramOfTheAncientGodsGui gpotag_;

  Figure::IEllipse *e_ =
      new Figure::ManhattanEllipse({200, 200}, 100, 300, std::numbers::pi / 6);
  FigureGui::EllipseGui ge_;

  std::queue<Figure::TFigure *> rq_;

  Figure::Rectangle *rect_ =
      new Figure::Rectangle({300, 300}, 100, 30, std::numbers::pi / 3);

public:
  App() : gc_(c_), gmc_(mc_), gr_(r_), gpotag_(potag_), ge_(e_) {
    std::cout << "App()\n";
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
    SDL_SetWindowIcon(win_, ico_);
  }
  ~App() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    delete c_;
    delete mc_;
    delete r_;
    delete potag_;
    delete e_;
    delete rect_;
    // delete ico_;
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
    for (; !rq_.empty(); rq_.pop())
      rq_.front()->Show(ren_);

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
      if (ImGui::BeginMenu("Figures")) {
        ImGui::MenuItem("Circle", nullptr, &gc_.show_gui_);
        ImGui::MenuItem("ManhattanCircle", nullptr, &gmc_.show_gui_);
        ImGui::MenuItem("Ring", nullptr, &gr_.show_gui_);
        ImGui::MenuItem("Pictogram of the ancient gods", nullptr,
                        &gpotag_.show_gui_);
        ImGui::MenuItem("Ellipse", nullptr, &ge_.show_gui_);
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
    gc_.Show();
    gmc_.Show();
    gr_.Show();
    gpotag_.Show();
    ge_.Show();
    ImGui::Render();
  }
  void update() {
    if (gc_.show_ && gc_.getFig() != nullptr)
      rq_.push(gc_.getFig());
    if (gmc_.show_ && gmc_.getFig() != nullptr)
      rq_.push(gmc_.getFig());
    if (gr_.show_ && gr_.getFig() != nullptr)
      rq_.push(gr_.getFig());
    if (gpotag_.show_ && gpotag_.getFig() != nullptr)
      rq_.push(gpotag_.getFig());
    if (ge_.show_ && ge_.getFig() != nullptr)
      rq_.push(ge_.getFig());
    rq_.push(rect_);
    rect_->Rotate(0.1);
  }
  void PollEvent() {
    SDL_Event e{};
    while (SDL_PollEvent(&e) != 0) {
      ImGui_ImplSDL2_ProcessEvent(&e);
      // if (e.type == SDL_QUIT)
      //   run_ = false;
      // if (e.type == SDL_KEYDOWN) {
      //   Figure::TFigure *f[] = {gc_.getFig(),     gmc_.getFig(),
      //   gr_.getFig(),
      //                           gpotag_.getFig(), ge_.getFig(),  rect_};
      //   for (auto &&i: f) {
      //     if (i != nullptr) {
      //       // if (e.key == SDLK_UP)
      //       SDLK_UP
      //     }
      //   }
      // }
      switch (e.type) {
      case SDL_QUIT:
        run_ = false;
        break;
      case SDL_KEYDOWN:
        Figure::TFigure *f[] = {gc_.getFig(),     gmc_.getFig(), gr_.getFig(),
                                gpotag_.getFig(), ge_.getFig(),  rect_};
        for (auto &&i : f) {
          if (i != nullptr) {
            switch (e.key.keysym.sym) {
              case SDLK_UP:
                i->MoveTo({0, -1});
                break;
              case SDLK_DOWN:
                i->MoveTo({0, 1});
                break;
              case SDLK_RIGHT:
                i->MoveTo({1, 0});
                break;
              case SDLK_LEFT:
                i->MoveTo({-1, 0});
                break;
            }
          }
        }
        break;
      }
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
