#ifndef LAB6_FIGURES_CIRCLEGEN_HH
#define LAB6_FIGURES_CIRCLEGEN_HH

#include "TFigureGen.hh"

#include <random>

namespace FigureGen {
class CircleGen : public TFigureGen {
public:
  Figure::TFigure *generate() override;
};
} // namespace FigureGen
#endif
