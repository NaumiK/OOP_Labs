#ifndef LAB2_FIGUREGUI_PICTOGRAMOFTHEANCIENTGODSGUI_HH
#define LAB2_FIGUREGUI_PICTOGRAMOFTHEANCIENTGODSGUI_HH

#include "FigureGui/FigureGui.hh"
#include "Figure/PictogramOfTheAncientGods.hh"
#include <random>

namespace FigureGui {
class PictogramOfTheAncientGodsGui final : public FigureGui {
  Figure::PictogramOfTheAncientGods *&fig_;
  std::default_random_engine gen;
  std::uniform_int_distribution<> dist{-50, 50};

public:
  PictogramOfTheAncientGodsGui(Figure::PictogramOfTheAncientGods *&fig);
  Figure::TFigure *getFig() override;
  void Show() override;
};
}
#endif
