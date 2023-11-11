#ifndef LAB4_FIGURES_ICIRCLE_HH
#define LAB4_FIGURES_ICIRCLE_HH
#include <SDL_render.h>
#include <cstdint>
#include "TFigure.hh"

namespace Figure {
class ICircle : public TFigure {
public:
  virtual int32_t GetRadius() const = 0;
  virtual VR2 GetPosition() const = 0;

  virtual void SetRadius(int32_t r) = 0;
  virtual void SetPosition(VR2 v) = 0;

  virtual ~ICircle() = default;
};
} // namespace Figure
#endif
