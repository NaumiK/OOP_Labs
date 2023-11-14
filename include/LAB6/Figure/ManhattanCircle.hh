#ifndef LAB6_FIGURES_MANHATTANCIRCLE_HH
#define LAB6_FIGURES_MANHATTANCIRCLE_HH
#include "ICircle.hh"
#include <SDL_render.h>

namespace Figure {
class ManhattanCircle final : public Figure::ICircle {
  VR2 O_;
  int32_t r_;
  double alpha_ = 0;

public:
  ManhattanCircle(VR2 O, int32_t r);

  static int32_t po(VR2 a, VR2 b);

  void Show(SDL_Renderer *s) override;
  void MoveTo(VR2 v) override;
  void Rotate(double da);

  int32_t GetRadius() const override;
  VR2 GetPosition() const override;
  double GetAngle() const;

  void SetRadius(int32_t r) override;
  void SetPosition(VR2 v) override;
  void SetAngle(double alpha);
};
} // namespace Figure
#endif
