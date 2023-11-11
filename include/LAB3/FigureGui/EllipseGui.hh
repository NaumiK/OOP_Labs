#ifndef LAB3_FIGUREGUI_ELLIPSEGUI_HH
#define LAB3_FIGUREGUI_ELLIPSEGUI_HH
#include "Figure/Ellipse.hh"
#include "FigureGui.hh"
#include <random>
namespace FigureGui {
class EllipseGui : public FigureGui {
  Figure::IEllipse *&fig_;
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

public:
  EllipseGui(Figure::IEllipse *&e);
  Figure::TFigure *getFig() override;
  void Show() override;
};
} // namespace FigureGui
#endif
