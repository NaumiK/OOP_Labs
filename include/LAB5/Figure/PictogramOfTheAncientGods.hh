#ifndef LAB5_FIGURES_PICTOGRAMOFTHEANCIENTGODS_HH
#define LAB5_FIGURES_PICTOGRAMOFTHEANCIENTGODS_HH

#include "Circle.hh"
#include "ManhattanCircle.hh"
#include <SDL_render.h>
#include <cstdint>

namespace Figure {
class PictogramOfTheAncientGods final : public TFigure {
  Figure::Circle egn_;
  Figure::ManhattanCircle inside_;

public:
  PictogramOfTheAncientGods(VR2 O, int32_t r, double angle);
  void Rotate(double da);
  void MoveTo(VR2 v) override;
  void SetPosition(VR2 v);
  VR2 GetPosition();

  void SetRadius(int32_t r);
  void SetAngle(double angle);

  int32_t GetRadius();

  double GetAngle();

  void Show(SDL_Renderer *r) override;
};
} // namespace Figure
#endif
