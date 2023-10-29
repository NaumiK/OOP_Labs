#ifndef LAB2_FIGUREGUI_MANHATTANCIRCLE_HH
#define LAB2_FIGUREGUI_MANHATTANCIRCLE_HH
#include "FigureGui/FigureGui.hh"
#include "Figure/ManhattanCircle.hh"
#include <random>

namespace FigureGui {
class ManhtattanCircleGui final : public FigureGui {
  Figure::ManhattanCircle *&fig_;
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

public:
  ManhtattanCircleGui(Figure::ManhattanCircle *&fig);
  Figure::TFigure *getFig() override;
  void Show() override;
};
}
#endif
