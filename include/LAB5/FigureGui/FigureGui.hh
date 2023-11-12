#ifndef LAB5_FIGUREGUI_FIGUREGUI_HH
#define LAB5_FIGUREGUI_FIGUREGUI_HH
#include "Figure/TFigure.hh"
namespace FigureGui {
class FigureGui {
public:
  bool show_ = true, show_gui_ = false;

public:
  virtual Figure::TFigure *getFig() = 0;

  virtual void Show() = 0;
  virtual ~FigureGui() = default;
};
}
#endif
