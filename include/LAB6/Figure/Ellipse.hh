#ifndef LAB6_FIGURES_ELLIPSE_HH
#define LAB6_FIGURES_ELLIPSE_HH
#include "Figure/IEllipse.hh"
#include "VR2.hh"

namespace Figure {
class Ellipse final : public IEllipse {
  VR2 O_;
  int32_t F_;
  double alpha_;
  int32_t r_;

public:
  Ellipse(VR2 O, int32_t focal_length, int32_t r, double alpha);

  static Ellipse CreateViaABNotation(VR2 O, int32_t a_half_axis,
                                     int32_t b_half_axis, double alpha);

  static int32_t po(VR2 a, VR2 b);

  void Show(SDL_Renderer *s) override;
  void MoveTo(VR2 v) override;
  void Rotate(double da) override;

  int32_t GetA() const override;
  int32_t GetB() const override;
  int32_t GetRadius() const override;
  VR2 GetPosition() const override;
  int32_t GetFocalLength() const override;
  double GetAngle() const override;

  void SetRadius(int32_t r) override;
  void SetPosition(VR2 v) override;
  void SetFocalLength(int32_t fl) override;
  void SetAngle(double alpha) override;
};
} // namespace Figure

#endif
