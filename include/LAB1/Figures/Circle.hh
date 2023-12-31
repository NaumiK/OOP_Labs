#ifndef LAB1_FIGURES_CIRCLE_HH
#define LAB1_FIGURES_CIRCLE_HH
#include <SDL_render.h>
#include <cstdint>
#include <random>

namespace Figure {
class Circle final {
  int32_t x_, y_;
  uint32_t r_;

public:
  Circle(int32_t x, int32_t y, uint32_t r);

  static int32_t po(int32_t ax, int32_t ay, int32_t bx, int32_t by);

  void Show(SDL_Renderer *s);

  uint32_t GetRadius() const;

  int32_t GetX() const;
  int32_t GetY() const;

  void SetRadius(uint32_t r);

  void SetPosition(int32_t x, int32_t y);
  void SetX(int32_t x);
  void SetY(int32_t y);

  void MoveTo(int32_t x, int32_t y);
};
} // namespace Figure
#endif
