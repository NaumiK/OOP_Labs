#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_surface.h>

#include <SDL_video.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <iostream>
#include <iterator>
#include <queue>
#include <random>
#include <sstream>
#include <stdint.h>
#include <string>

struct sdl_error : public std::runtime_error {
  sdl_error(const char *s) : std::runtime_error(s) {}
};

struct VR2 {
  int32_t x, y;
};

VR2 operator+(const VR2 &a, const VR2 &b) { return {a.x + b.x, a.y + b.y}; }

VR2 operator*(int32_t a, const VR2 &b) { return {a * b.x, a * b.y}; }

int32_t abs(VR2 v) { return v.x * v.x + v.y * v.y; }

class Circle {
  VR2 xy_;
  int32_t r_;
  bool show_gui = false, show_ = true;
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

public:
  Circle(VR2 xy, uint32_t r) : xy_(xy), r_(r), gen(std::random_device{}()) {}

  static int32_t po(const VR2 &x, const VR2 &y) {
    auto dx = y.x - x.x, dy = y.y - x.y;
    return dx * dx + dy * dy;
    // return dx * dx + 4 * dy * dy;
    // return (std::abs(dx) + std::abs(dy)) * (std::abs(dx) + std::abs(dy));
    // return std::abs(dx*dy);
    // return (std::abs(dx) + std::abs(4 * dy)) *
    //        (std::abs(dx) + std::abs(4 * dy));
  }

  void Show(SDL_Renderer *s) {
    if (!show_)
      return;
    auto sqrr = r_ * r_;
    SDL_RenderDrawPoint(s, xy_.x, xy_.y); // <-- Center
    VR2 cur = VR2{r_, 0};                 // delta
    VR2 O = {0, 0};
    while (cur.x > 0) {
      auto sx = cur + VR2{-1, 0}, sy = cur + VR2{0, 1};
      // std::cout << std::abs(po(sx, O) - sqrr) << " "
      //           << std::abs(po(sy, O) - sqrr) << "\n";

      SDL_RenderDrawPoint(s, xy_.x + cur.x, xy_.y + cur.y);
      SDL_RenderDrawPoint(s, xy_.x - cur.x, xy_.y + cur.y);
      SDL_RenderDrawPoint(s, xy_.x + cur.x, xy_.y - cur.y);
      SDL_RenderDrawPoint(s, xy_.x - cur.x, xy_.y - cur.y);
      //
      // SDL_RenderDrawPoint(s, xy_.x + cur.y, xy_.y + cur.x);
      // SDL_RenderDrawPoint(s, xy_.x - cur.y, xy_.y + cur.x);
      // SDL_RenderDrawPoint(s, xy_.x + cur.y, xy_.y - cur.x);
      // SDL_RenderDrawPoint(s, xy_.x - cur.y, xy_.y - cur.x);

      if (std::abs(po(sx, O) - sqrr) < std::abs(po(sy, O) - sqrr))
        cur = sx;
      else
        cur = sy;
    }
  }

  void GUI_Show() {
    if (!show_gui)
      return;
    ImGui::Begin("Circle", &show_gui);
    ImGui::SliderInt("Radius", &r_, 0, 1000);
    ImGui::SliderInt2("Coordinates", &xy_.x, -500, 500);
    ImGui::Checkbox("Show", &show_);
    if (ImGui::Button("Random move")) {
      MoveTo({dist(gen), dist(gen)});
    }
    ImGui::End();
  }

  bool &GetGuiTrigger() { return show_gui; }

  uint32_t GetRadius() const { return r_; }

  VR2 GetPostion() const { return xy_; }

  void SetRadius(uint32_t r) { r_ = r; }

  void SetPosition(const VR2 &pos) { xy_ = pos; }

  void MoveTo(const VR2 &dlta) { xy_ = xy_ + dlta; }
};

class App {
  SDL_Window *win_ =
      SDL_CreateWindow("Lab 1", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  SDL_Renderer *ren_ = SDL_CreateRenderer(
      win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  bool running_ = true;
  float color_[3] = {0.f, 0.f, 0.f};
  char windowtitle_[255] = "Lab 1";
  bool show_settings_ = false;
  Circle *c_ = new Circle({150, 150}, 50);

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
        ImGui::MenuItem("Circle", nullptr, &(c_->GetGuiTrigger()));
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
    c_->GUI_Show();
    ImGui::Render();
  }

  void render() {
    SDL_SetRenderDrawColor(ren_, static_cast<uint8_t>(color_[0] * 255),
                           static_cast<uint8_t>(color_[1] * 255),
                           static_cast<uint8_t>(color_[2] * 255), 0xFF);
    SDL_RenderClear(ren_);
    SDL_SetRenderDrawColor(ren_, 0xFF, 0xFF, 0xFF, 0xFF);
    c_->Show(ren_);

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
