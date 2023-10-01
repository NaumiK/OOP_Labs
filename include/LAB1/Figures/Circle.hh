#ifndef LAB1_FIGURES_CIRCLE_HH
#define LAB1_FIGURES_CIRCLE_HH
#include "MSDCore/VR2.hh"
#include <SDL_render.h>
#include <cstdint>
#include <random>

namespace Figure {
class Circle {
  VR2 xy_;
  int32_t r_;
  bool show_gui = false, show_ = true;
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

public:
  Circle(VR2 xy, uint32_t r);

  static int32_t po(const VR2 &x, const VR2 &y);

  void Show(SDL_Renderer *s);

  void GUI_Show();

  bool &GetGuiTrigger();

  uint32_t GetRadius() const;

  VR2 GetPostion() const;

  void SetRadius(uint32_t r);

  void SetPosition(const VR2 &pos);

  void MoveTo(const VR2 &dlta);
};
} // namespace Figure
#endif
