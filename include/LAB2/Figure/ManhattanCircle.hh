#ifndef LAB2_FIGURES_SQUARE_HH
#define LAB2_FIGURES_SQUARE_HH
#include "Rotateable.hh"
#include <SDL_render.h>

namespace Figure {
class ManhattanCircle final : public Rotateable {
  VR2 O_;
  int32_t r_;
  double alpha_ = 0;

public:
  ManhattanCircle(VR2 O, int32_t r);

  static int32_t po(VR2 a, VR2 b);

  void Show(SDL_Renderer *s) override;
  void MoveTo(VR2 v) override;
  void Rotate(double da) override;

  int32_t GetRadius() const;
  VR2 GetPosition() const;
  double GetAngle() const;

  void SetRadius(int32_t r);
  void SetPosition(VR2 v);
  void SetAngle(double alpha);
};
} // namespace Figure
#endif
