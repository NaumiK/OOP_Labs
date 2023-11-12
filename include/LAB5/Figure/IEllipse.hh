#ifndef LAB5_FIGURES_IELLIPSE_HH
#define LAB5_FIGURES_IELLIPSE_HH

#include "ICircle.hh"

namespace Figure {
class IEllipse : public Figure::ICircle {
public:
  virtual int32_t GetFocalLength() const = 0;

  virtual void SetFocalLength(int32_t fl) = 0;
  virtual void SetAngle(double da) = 0;
  virtual void Rotate(double da) = 0;

  virtual int32_t GetA() const = 0;
  virtual int32_t GetB() const = 0;
  virtual double GetAngle() const = 0;

  virtual ~IEllipse() = default;
};
}

#endif

