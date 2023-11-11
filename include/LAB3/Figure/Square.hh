
#ifndef LAB3_FIGURES_SQUARE_HH
#define LAB3_FIGURES_SQUARE_HH

#include "Rotateable.hh"
#include <SDL_render.h>
#include <cstdint>

namespace Figure {
class Square : public Figure::Rotateable {
protected:
  VR2 O_;
  int32_t a_;
  double alpha_;

public:
  Square(VR2 O, int32_t a, double alpha);
  void Rotate(double da) override;
  void MoveTo(VR2 v) override;
  void SetPosition(VR2 v);
  VR2 GetPosition();

  void SetASize(int32_t a);
  void SetAngle(double angle);

  double GetAngle() const;
  int32_t GetASize() const;

  void Show(SDL_Renderer *r) override;
  ~Square() = default;
};
} // namespace Figure
#endif
