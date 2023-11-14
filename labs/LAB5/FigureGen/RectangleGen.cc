#include "FigureGen/RectangleGen.hh"

Figure::TFigure *FigureGen::RectangleGen::generate() {
  return new Figure::Rectangle({dist(gen) + 150, dist(gen) + 150},
                               abs(dist(gen)), abs(dist(gen)),
                               std::numbers::pi / 12 * dist(gen));
}
