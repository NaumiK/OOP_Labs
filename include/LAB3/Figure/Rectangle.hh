#ifndef LAB3_FIGURES_RECTANGLE_HH
#define LAB3_FIGURES_RECTANGLE_HH

#include "Square.hh"
#include <SDL_render.h>
#include <cstdint>

namespace Figure {
class Rectangle final : public Figure::Square {
  int32_t b_;

public:
  Rectangle(VR2 O, int32_t a, int32_t b, double alpha);
  void SetPosition(VR2 v);
  VR2 GetPosition();

  void SetBSize(int32_t b);

  int32_t GetBSize() const;

  void Show(SDL_Renderer *r) override;
};
} // namespace Figure
#endif
