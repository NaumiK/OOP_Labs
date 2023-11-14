#ifndef LAB6_FIGURES_MANHATTANELLIPSEGEN_HH
#define LAB6_FIGURES_MANHATTANELLIPSEGEN_HH

#include "Figure/ManhattanEllipse.hh"
#include "TFigureGen.hh"

#include <numbers>
#include <random>

namespace FigureGen {
class ManhattanEllipseGen : public TFigureGen {
public:
  Figure::TFigure *generate() override;
};
} // namespace FigureGen
#endif
