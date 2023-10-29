#ifndef LAB2_FIGUREGUI_CIRCLEGUI_HH
#define LAB2_FIGUREGUI_CIRCLEGUI_HH
#include "Figure/Circle.hh"
#include "FigureGui/FigureGui.hh"
namespace FigureGui {
class CircleGui final : public FigureGui {
  Figure::Circle *&fig_;
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

public:
  CircleGui(Figure::Circle *&fig);
  Figure::TFigure *getFig() override;
  void Show() override;
};
} // namespace FigureGui
#endif
