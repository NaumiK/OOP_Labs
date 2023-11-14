#ifndef LAB5_FIGURES_ELLIPSEGEN_HH
#define LAB5_FIGURES_ELLIPSEGEN_HH

#include "TFigureGen.hh"

#include <numbers>
#include <random>

namespace FigureGen {
class EllipseGen : public TFigureGen {
public:
  Figure::TFigure *generate() override;
};
} // namespace FigureGen
#endif
