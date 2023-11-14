#ifndef LAB5_FIGURES_TFIGUREGEN_HH
#define LAB5_FIGURES_TFIGUREGEN_HH

#include <random>
#include "Figure/TFigure.hh"

namespace FigureGen {
class TFigureGen {
protected:
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-100, 100};

public:
  TFigureGen() : gen(std::random_device{}()) {}
  virtual Figure::TFigure *generate() = 0;
  virtual ~TFigureGen() = default;
};
}

#endif
