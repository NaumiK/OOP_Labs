#ifndef LAB3_FIGURES_IELLIPSE_HH
#define LAB3_FIGURES_IELLIPSE_HH

#include "Figure/Rotateable.hh"
#include "VR2.hh"

namespace Figure {
class IEllipse : public Rotateable {
public:
  virtual int32_t GetRadius() const = 0;
  virtual int32_t GetFocalLength() const = 0;
  virtual VR2 GetPosition() const = 0;

  virtual void SetRadius(int32_t r) = 0;
  virtual void SetFocalLength(int32_t fl) = 0;
  virtual void SetPosition(VR2 v) = 0;
  virtual void SetAngle(double da) = 0;

  virtual int32_t GetA() const = 0;
  virtual int32_t GetB() const = 0;
  virtual double GetAngle() const = 0;
};
}

#endif

