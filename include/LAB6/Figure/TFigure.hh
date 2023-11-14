#ifndef LAB6_FIGURES_TFIGURE_HH
#define LAB6_FIGURES_TFIGURE_HH

#include "MSDCore/VR2.hh"
#include <SDL_render.h>
namespace Figure {
struct TFigure {
  virtual void Show(SDL_Renderer *) = 0;
  virtual void MoveTo(VR2) = 0;
  virtual ~TFigure() = default;
};
} // namespace Figure
#endif
