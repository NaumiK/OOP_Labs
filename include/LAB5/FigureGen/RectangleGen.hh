#ifndef LAB5_FIGURES_RECTANGLEGEN_HH
#define LAB5_FIGURES_RECTANGLEGEN_HH

#include "Figure/Rectangle.hh"
#include "TFigureGen.hh"

#include <numbers>
#include <random>

namespace FigureGen {
class RectangleGen : public TFigureGen {
public:
  Figure::TFigure *generate() override;
};
} // namespace FigureGen
#endif
