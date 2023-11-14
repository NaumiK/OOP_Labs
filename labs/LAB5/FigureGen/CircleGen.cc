#include "FigureGen/CircleGen.hh"
#include "Figure/Circle.hh"

Figure::TFigure *FigureGen::CircleGen::generate() {
  return new Figure::Circle({dist(gen) + 150, dist(gen) + 150},
                            abs(dist(gen)) * 4);
}
