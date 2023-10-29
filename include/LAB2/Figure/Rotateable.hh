#ifndef LAB2_FIGURES_ROTATEABLE_HH
#define LAB2_FIGURES_ROTATEABLE_HH

#include "TFigure.hh"
namespace Figure {
struct Rotateable : public TFigure {
  virtual void Rotate(double da) = 0;
};
} // namespace Figure
#endif
