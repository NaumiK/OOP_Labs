#ifndef LAB2_FIGURES_CIRCLE_HH
#define LAB2_FIGURES_CIRCLE_HH
#include <SDL_render.h>
#include <cstdint>
#include <random>
#include "TFigure.hh"

namespace Figure {
class Circle final : public TFigure {
  VR2 O_;
  int32_t r_;

public:
  Circle(VR2 O, int32_t r);

  static int32_t po(VR2 a, VR2 b);

  void Show(SDL_Renderer *s) override;
  void MoveTo(VR2 v) override;

  int32_t GetRadius() const;
  VR2 GetPosition() const;

  void SetRadius(int32_t r);
  void SetPosition(VR2 v);
};
} // namespace Figure
#endif
