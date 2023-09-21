#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_surface.h>

#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <imgui.h>

#include <iostream>
#include <vector>


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

#include "SFG/Showable.hh"

class App {
  SDL_Window *win_ =
      SDL_CreateWindow("hello, circle", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  SDL_Renderer *ren_ = SDL_CreateRenderer(
      win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  bool running_ = true;

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

  void frame() {
    SDL_SetRenderDrawColor(ren_, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(ren_);

    SDL_SetRenderDrawColor(ren_, 0xFF, 0xFF, 0xFF, 0xFF);
    Showable<SDL_Renderer *> sh(
        ColoredCircle{{{150, 150}, 150}, 0xFF, 0x00, 0xFF, 0xFF});
    std::vector<Showable<SDL_Renderer *>> shl = {Circle{{150, 150}, 150}};
    shl.push_back(ColoredCircle{{{150, 250}, 150}, 0xFF, 0x00, 0xFF, 0xFF});

    for (auto &shi : shl)
      Show(ren_, shi);

    ImGui_ImplSDLRenderer2_RenderDrawData(
      ImGui::GetDrawData()
    );

    SDL_RenderPresent(ren_);
    // SDL_Delay(2000);
  }

  void run() {
    running_ = true;
    bool show_panel{true};
    while (running_) {
    SDL_Event e{};
      while (SDL_PollEvent(&e) != 0) {
        ImGui_ImplSDL2_ProcessEvent(&e);
        if (e.type == SDL_QUIT)
          stop();
      }

      ImGui_ImplSDLRenderer2_NewFrame();
      ImGui_ImplSDL2_NewFrame();
      ImGui::NewFrame();

      if (show_panel) {
        ImGui::Begin("Some panel", &show_panel);
        ImGui::Text("Hello, world");
        ImGui::End();
      }
      ImGui::Render();
      frame();
    }
  }

  void stop() {
    running_ = false;
  }

  ~App() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(ren_);
    SDL_DestroyWindow(win_);
  }
};

int main(int argc, char **argv) try {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    throw sdl_error("SDL_Init");
  {
    App app;
    // app.frame();
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
