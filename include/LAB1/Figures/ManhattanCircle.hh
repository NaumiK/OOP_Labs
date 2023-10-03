#ifndef LAB1_FIGURES_SQUARE_HH
#define LAB1_FIGURES_SQUARE_HH
#include <SDL_render.h>
#include <cstdint>
#include <random>

namespace Figure {
class ManhattanCircle final {
  int32_t x_, y_;
  int32_t r_;
  double alpha_ = 0;

public:
  ManhattanCircle(int32_t x, int32_t y, int32_t r);

  static int32_t po(int32_t ax, int32_t ay, int32_t bx, int32_t by);

  void Show(SDL_Renderer *s);

  int32_t GetRadius() const;

  int32_t GetX() const;
  int32_t GetY() const;
  double GetAngle() const;

  void SetRadius(int32_t r);

  void SetPosition(int32_t x, int32_t y);
  void SetX(int32_t x);
  void SetY(int32_t y);
  void SetAngle(double alpha);

  void MoveTo(int32_t x, int32_t y);
  void Rotate(double da);
};
} // namespace Figure
#endif
