#ifndef LAB2_FIGURES_SQUARE_HH
#define LAB2_FIGURES_SQUARE_HH
#include "TFigure.hh"
#include <SDL_render.h>

namespace Figure {
class ManhattanCircle : public TFigure {
  VR2 O_;
  int32_t r_;
  double alpha_ = 0;

public:
  ManhattanCircle(VR2 O, int32_t r);

  static int32_t po(VR2 a, VR2 b);

  void Show(SDL_Renderer *s) override;
  void MoveTo(VR2 v) override;
  void Rotate(double da);

  int32_t GetRadius() const;
  VR2 GetPosition() const;
  double GetAngle() const;

  void SetRadius(int32_t r);
  void SetPosition(VR2 v);
  void SetAngle(double alpha);
};
} // namespace Figure
#endif
