#ifndef LAB5_FIGUREGUI_RINGGUI_HH
#define LAB5_FIGUREGUI_RINGGUI_HH
#include "FigureGui/TFigureGui.hh"
#include "Figure/Ring.hh"
#include <random>

namespace FigureGui {
class RingGui final : public TFigureGui {
  Figure::Ring *&fig_;
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

public:
  RingGui(Figure::Ring *&fig);
  Figure::TFigure *getFig() override;
  void Show() override;
};
}
#endif
