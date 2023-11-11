#ifndef LAB3_FIGURES_RING_HH
#define LAB3_FIGURES_RING_HH
#include "Circle.hh"
#include <SDL_render.h>

namespace Figure {
class Ring final : public Figure::TFigure {
  Figure::Circle in, out;

public:
  Ring(VR2 O, int32_t r, int32_t t);
  void MoveTo(VR2 v) override;
  void Show(SDL_Renderer *r) override;

  void SetPosition(VR2 O);
  void SetRadius(int32_t r);
  void SetThickness(int32_t t);
  VR2 GetPosition();
  int32_t GetThickness();
  int32_t GetRadius();
};
} // namespace Figure
#endif
