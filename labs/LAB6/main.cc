#include "Figure/Figure.hh"
#include "FigureGen/FigureGen.hh"
#include "FigureGui/FigureGui.hh"
#include "MSDCore/exceptions.hh"
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include <array>
#include <iostream>
#include <iterator>
#include <memory>
#include <numbers>
#include <queue>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <random>
#include <stdexcept>

template <typename T> struct MyVectorBuf {
protected:
  T *arr_;
  size_t capacity_, size_ = 0;

protected:
  MyVectorBuf(const MyVectorBuf &) = delete;
  MyVectorBuf &operator=(const MyVectorBuf &) = delete;
  MyVectorBuf(MyVectorBuf &&rhs) noexcept
      : arr_(rhs.arr_), size_(rhs.size_), capacity_(rhs.capacity_) {
    rhs.arr_ = nullptr;
    rhs.size_ = 0;
    rhs.capacity_ = 0;
  }
  MyVectorBuf &operator=(MyVectorBuf &&rhs) noexcept {
    std::swap(arr_, rhs.arr_);
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
    return *this;
  }
  MyVectorBuf(size_t capacity = 0)
      : arr_((capacity == 0)
                 ? nullptr
                 : static_cast<T *>(::operator new(sizeof(T) * capacity))),
        capacity_(capacity) {}

  ~MyVectorBuf() {
    for (auto i = arr_, ei = arr_ + capacity_; i != ei; ++i)
      i->~T();
    ::operator delete(arr_);
  }
};

template <typename T> class MyVectorIterator;

template <typename T>
bool operator==(const MyVectorIterator<T> &lhs,
                const MyVectorIterator<T> &rhs) {
  return lhs.t_ == rhs.t_;
}

template <typename T>
bool operator!=(const MyVectorIterator<T> &lhs,
                const MyVectorIterator<T> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
bool operator<(const MyVectorIterator<T> &lhs, const MyVectorIterator<T> &rhs) {
  return lhs.t_ < rhs.t_;
}

template <typename T>
bool operator>(const MyVectorIterator<T> &lhs, const MyVectorIterator<T> &rhs) {
  return rhs < lhs;
}

template <typename T>
bool operator<=(const MyVectorIterator<T> &lhs,
                const MyVectorIterator<T> &rhs) {
  return !(lhs > rhs);
}

template <typename T>
bool operator>=(const MyVectorIterator<T> &lhs,
                const MyVectorIterator<T> &rhs) {
  return !(lhs < rhs);
}

template <typename T>
MyVectorIterator<T> operator+(MyVectorIterator<T> it,
                              typename MyVectorIterator<T>::difference_type n) {
  it += n;
  return it;
}

template <typename T>
MyVectorIterator<T> operator+(typename MyVectorIterator<T>::difference_type n,
                              MyVectorIterator<T> it) {
  it += n;
  return it;
}

template <typename T>
MyVectorIterator<T> operator-(MyVectorIterator<T> it,
                              typename MyVectorIterator<T>::difference_type n) {
  it -= n;
  return it;
}

template <typename T>
int64_t operator-(const MyVectorIterator<T> &lhs,
                  const MyVectorIterator<T> &rhs) {
  return lhs.t_ - rhs.t_;
}

template <typename T> class MyVectorIterator {
public:
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<T>;
  using pointer = T *;
  using reference = T &;
  using iterator = MyVectorIterator;
  using iterator_category = std::random_access_iterator_tag;
  using iterator_concept = std::contiguous_iterator_tag;

protected:
  T *t_;

public:
  MyVectorIterator() = default;
  MyVectorIterator(T *t) : t_(t) {}
  MyVectorIterator(const MyVectorIterator &) = default;
  MyVectorIterator &operator=(const MyVectorIterator &) = default;
  ~MyVectorIterator() = default;
  reference operator*() { return *t_; }
  reference operator*() const { return *t_; }
  iterator &operator++() {
    ++t_;
    return *this;
  }
  iterator operator++(int) {
    auto old = *this;
    ++(*this);
    return old;
  }

  pointer operator->() { return t_; }
  const pointer operator->() const { return t_; }

  iterator &operator--() {
    --t_;
    return *this;
  }

  iterator operator--(int) {
    auto old = *this;
    --(*this);
    return old;
  }

  reference operator[](difference_type n) const {
    auto tmp = *this;
    tmp += n;
    return *tmp;
  }

  iterator &operator+=(difference_type n) {
    t_ += n;
    return *this;
  }

  iterator &operator-=(difference_type n) {
    t_ -= n;
    return *this;
  }

  template <typename T1>
  friend bool operator==(const MyVectorIterator<T1> &lhs,
                         const MyVectorIterator<T1> &rhs);

  template <typename T1>
  friend int64_t operator-(const MyVectorIterator<T1> &lhs,
                           const MyVectorIterator<T1> &rhs);

  template <typename T1>
  friend bool operator<(const MyVectorIterator<T1> &lhs,
                        const MyVectorIterator<T1> &rhs);
};

template <typename T>
void swap(MyVectorIterator<T> &a, MyVectorIterator<T> &b) {
  std::swap(a.t_, b.t_);
}

template <typename T> struct MyVector final : private MyVectorBuf<T> {
  using MyVectorBuf<T>::arr_;
  using MyVectorBuf<T>::capacity_;
  using MyVectorBuf<T>::size_;
  using iterator = MyVectorIterator<T>;
  using reverse_iterator = std::reverse_iterator<iterator>;

  explicit MyVector(size_t sz = 0) : MyVectorBuf<T>(sz) {}

  MyVector(const MyVector &rhs) : MyVectorBuf<T>(rhs.size_) {
    for (; size_ < rhs.size_; ++size_) {
      new (arr_ + size_) T(std::move(rhs.arr_[size_]));
    }
  }
  MyVector &operator=(const MyVector &rhs) {
    MyVector tmp(rhs);
    //--------------
    std::swap(*this, tmp);
  }
  MyVector(MyVector &&rhs) = default;
  MyVector &operator=(MyVector &&rhs) = default;
  void pop_back() {
    if (size_ == 0)
      throw std::runtime_error("Empty vector");
    (arr_ + --size_)->~T();
  }
  T back() const {
    if (size_ == 0)
      throw std::runtime_error("Empty vector");
    return arr_[size_ - 1];
  }
  T front() const {
    if (size_ == 0)
      throw std::runtime_error("Empty vector");
    return arr_[0];
  }
  void push_back(T &&t) {
    if (size_ == capacity_) {
      MyVector<T> tmp(capacity_ * 2 + 1);
      for (; tmp.size_ < size_;)
        tmp.push_back(std::move(arr_[tmp.size_]));
      tmp.push_back(std::move(t));
      //-------------------
      std::swap(*this, tmp);
    } else {
      new (arr_ + size_++) T(std::move(t));
    }
  }
  iterator begin() { return iterator(arr_); }
  iterator end() { return iterator(arr_ + size_); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  void push_back(const T &t) {
    T t2(t);
    push_back(std::move(t2));
  }
  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
};

class ArrayMenu final {
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-100, 100};
  std::uniform_int_distribution<> choose{0, 4};
  std::array<Figure::TFigure *, 20> &v_;
  std::array<std::unique_ptr<FigureGen::TFigureGen>, 5> g_fig_ = {
      std::make_unique<FigureGen::CircleGen>(),
      std::make_unique<FigureGen::ManhattanCircleGen>(),
      std::make_unique<FigureGen::EllipseGen>(),
      std::make_unique<FigureGen::ManhattanEllipseGen>(),
      std::make_unique<FigureGen::RectangleGen>()};

public:
  bool g_menu = false, show = true;

public:
  ArrayMenu(std::array<Figure::TFigure *, 20> &v)
      : v_(v), gen(std::random_device{}()) {}

  void create_figures() {
    for (auto &i : v_) {
      delete i;
      auto tmp = choose(gen);
      i = g_fig_[tmp]->generate();
    }
  }

  void destroy_figures() {
    for (auto &i : v_) {
      delete i;
      i = nullptr;
    }
  }

  void move_figures() {
    for (auto &i : v_)
      if (i != nullptr)
        i->MoveTo({dist(gen), dist(gen)});
  }

  void Show() {
    if (!g_menu)
      return;
    ImGui::Begin("Array", &g_menu);
    if (ImGui::Button("Create"))
      create_figures();
    if (ImGui::Button("Destroy"))
      destroy_figures();
    if (ImGui::Button("Hide"))
      show = false;
    if (ImGui::Button("Show"))
      show = true;
    if (ImGui::Button("Move"))
      move_figures();
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

  std::array<Figure::TFigure *, 20> v_{nullptr};
  ArrayMenu am_;

public:
  App() : gc_(c_), gmc_(mc_), gr_(r_), gpotag_(potag_), ge_(e_), am_(v_) {
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
    am_.destroy_figures();
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
        ImGui::MenuItem("Array", nullptr, &am_.g_menu);
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
    am_.Show();
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
    if (am_.show)
      for (auto &i : v_)
        if (i != nullptr)
          rq_.push(i);
    rq_.push(rect_);
    rect_->Rotate(0.1);
  }
  void PollEvent() {
    SDL_Event e{};
    while (SDL_PollEvent(&e) != 0) {
      ImGui_ImplSDL2_ProcessEvent(&e);
      switch (e.type) {
      case SDL_QUIT:
        run_ = false;
        break;
      case SDL_KEYDOWN:
        Figure::TFigure *f[] = {gc_.getFig(),     gmc_.getFig(), gr_.getFig(),
                                gpotag_.getFig(), ge_.getFig(),  rect_};
        for (auto &i : f) {
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
#if 0
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    throw sdl_error("SDL_Init");
  {
    App app;
    app.run();
  }

  SDL_Quit();
#endif
  MyVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(8);
  v.push_back(4);
  v.push_back(3);
  std::sort(v.rbegin(), v.rend());
  for (auto &i : v)
    std::cout << i << " ";
  // for (auto i = v.begin(), ei = v.end(); i != ei; ++i)
  //   std::cout << *i << " ";
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
