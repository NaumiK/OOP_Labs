#ifndef LAB5_FIGUREGUI_CIRCLEGUI_HH
#define LAB5_FIGUREGUI_CIRCLEGUI_HH
#include "Figure/ICircle.hh"
#include "FigureGui/TFigureGui.hh"
#include <random>
namespace FigureGui {
class CircleGui final : public TFigureGui {
  Figure::ICircle *&fig_;
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

public:
  CircleGui(Figure::ICircle *&fig);
  Figure::TFigure *getFig() override;
  void Show() override;
};
} // namespace FigureGui
#endif
