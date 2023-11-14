#ifndef LAB6_FIGURES_MANHATTANCIRCLEGEN_HH
#define LAB6_FIGURES_MANHATTANCIRCLEGEN_HH

#include "Figure/ManhattanCircle.hh"
#include "TFigureGen.hh"

#include <random>

namespace FigureGen {
class ManhattanCircleGen : public TFigureGen {
public:
  Figure::TFigure *generate() override;
};
} // namespace FigureGen
#endif
