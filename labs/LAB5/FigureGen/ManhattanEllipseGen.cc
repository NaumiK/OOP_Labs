#include "FigureGen/ManhattanEllipseGen.hh"
#include "Figure/TFigure.hh"

Figure::TFigure *FigureGen::ManhattanEllipseGen::generate() {
  return new Figure::ManhattanEllipse({dist(gen) + 150, dist(gen) + 150},
                                      dist(gen), dist(gen) * 3,
                                      std::numbers::pi / 12 * dist(gen));
}
