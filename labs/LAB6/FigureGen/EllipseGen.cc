#include "FigureGen/EllipseGen.hh"
#include "Figure/Ellipse.hh"

Figure::TFigure *FigureGen::EllipseGen::generate() {
  return new Figure::Ellipse({dist(gen) + 150, dist(gen) + 150}, dist(gen),
                             dist(gen) * 3, std::numbers::pi / 12 * dist(gen));
}
