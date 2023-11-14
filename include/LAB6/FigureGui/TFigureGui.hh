#ifndef LAB6_FIGUREGUI_TFIGUREGUI_HH
#define LAB6_FIGUREGUI_TFIGUREGUI_HH
#include "Figure/TFigure.hh"
namespace FigureGui {
class TFigureGui {
public:
  bool show_ = true, show_gui_ = false;

public:
  virtual Figure::TFigure *getFig() = 0;

  virtual void Show() = 0;
  virtual ~TFigureGui() = default;
};
}
#endif
