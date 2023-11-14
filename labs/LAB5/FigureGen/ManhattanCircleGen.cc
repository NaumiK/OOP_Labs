#include "FigureGen/ManhattanCircleGen.hh"
#include "Figure/TFigure.hh"

Figure::TFigure *FigureGen::ManhattanCircleGen::generate() {
  return new Figure::ManhattanCircle({dist(gen) + 150, dist(gen) + 150},
                                     abs(dist(gen)) * 4);
}
