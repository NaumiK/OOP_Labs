#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_surface.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <iostream>
#include <queue>
#include <sstream>
#include <stdint.h>

struct sdl_error : public std::runtime_error {
  sdl_error(const char *s) : std::runtime_error(s) {}
};

struct VR2 {
  int32_t x, y;
};

struct Circle {
  VR2 xy;
  uint32_t r;
};

struct ColoredCircle {
  Circle cr;
  uint8_t r, g, b, a;
};

class ImGuiPanel {
  std::string name_;

public:
  ImGuiPanel(const std::string &name) : name_(name) {}
  virtual void func() = 0;
  virtual void show() {
    ImGui::Begin(name_.c_str());
    func();
    ImGui::End();
  }
  virtual ~ImGuiPanel() = default;
};

struct ImGuiOCPanel : ImGuiPanel {
  bool show_;
  ImGuiOCPanel(std::string name, bool show) : ImGuiPanel(name), show_(show) {}
  void func() override = 0;
  void show() override {
    if (show_) {
      ImGuiPanel::show();
    }
  }
  virtual ~ImGuiOCPanel() = default;
};

void Show(SDL_Renderer *s, const Circle &c) {
  const int32_t diameter = (c.r * 2);

  int32_t x = (c.r - 1);
  int32_t y = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);

  while (x >= y) {
    //  Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(s, c.xy.x + x, c.xy.y - y);
    SDL_RenderDrawPoint(s, c.xy.x + x, c.xy.y + y);
    SDL_RenderDrawPoint(s, c.xy.x - x, c.xy.y - y);
    SDL_RenderDrawPoint(s, c.xy.x - x, c.xy.y + y);
    SDL_RenderDrawPoint(s, c.xy.x + y, c.xy.y - x);
    SDL_RenderDrawPoint(s, c.xy.x + y, c.xy.y + x);
    SDL_RenderDrawPoint(s, c.xy.x - y, c.xy.y - x);
    SDL_RenderDrawPoint(s, c.xy.x - y, c.xy.y + x);

    if (error <= 0) {
      ++y;
      error += ty;
      ty += 2;
    }

    if (error > 0) {
      --x;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

void Show(SDL_Renderer *s, const ColoredCircle &c) {
  SDL_SetRenderDrawColor(s, c.r, c.g, c.b, c.a);
  Show(s, c.cr);
}

class ImGuiRenderer;

void Show(const ImGuiRenderer &s, const Circle &c) {
  std::stringstream ss;
  ss << "Coordinates: (" << c.xy.x << ", " << c.xy.y << ")\n"
     << "Radius: "
     << "c.r";
  std::string ans;
  ss >> ans;
  ImGui::Begin("Circle");
  ImGui::Text("%s", ans.c_str());
  ImGui::End();
}

#include "SFG/Showable.hh"
using SDL_Showable = Showable<SDL_Renderer *>;
using GUI_Showable = Showable<const ImGuiRenderer &>;

class App {
  SDL_Window *win_ =
      SDL_CreateWindow("hello, circle", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  SDL_Renderer *ren_ = SDL_CreateRenderer(
      win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  bool running_ = true;
  float color_[3] = {0.f, 0.f, 0.f};
  char windowtitle_[255] = "hello, circle";
  std::queue<SDL_Showable> draw_queue_;
  bool show_settings_ = false;

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
  }
  App(const App &) = delete;
  App(App &&) = delete;
  App &operator=(const App &) = delete;
  App &operator=(App &&) = delete;

  ~App() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

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

  void imGuiRender() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("Window")) {
        ImGui::MenuItem("Settings", nullptr, &show_settings_);
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
    if (show_settings_) {
      ImGui::Begin("Some panel", &show_settings_);
      ImGui::Text("Hello, world");
      ImGui::ColorEdit3("Backgound color", color_);
      ImGui::InputText("Window title", windowtitle_, 255);
      if (ImGui::Button("Update window title"))
        SDL_SetWindowTitle(win_, windowtitle_);
      ImGui::End();
    }
    ImGui::Render();
  }

  void render() {
    SDL_SetRenderDrawColor(ren_, static_cast<uint8_t>(color_[0] * 255),
                           static_cast<uint8_t>(color_[1] * 255),
                           static_cast<uint8_t>(color_[2] * 255), 0xFF);
    SDL_RenderClear(ren_);

    while (!draw_queue_.empty()) {
      Show(ren_, draw_queue_.front());
      draw_queue_.pop();
    }

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
