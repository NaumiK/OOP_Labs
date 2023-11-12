#ifndef LAB5_FIGURES_CIRCLE_HH
#define LAB5_FIGURES_CIRCLE_HH
#include <SDL_render.h>
#include <cstdint>
#include <random>
#include "ICircle.hh"

namespace Figure {
class Circle : public ICircle {
  VR2 O_;
  int32_t r_;

public:
  Circle(VR2 O, int32_t r);

  static int32_t po(VR2 a, VR2 b);

  void Show(SDL_Renderer *s) override;
  void MoveTo(VR2 v) override;

  int32_t GetRadius() const override;
  VR2 GetPosition() const override;

  void SetRadius(int32_t r) override;
  void SetPosition(VR2 v) override;
};
} // namespace Figure
#endif
