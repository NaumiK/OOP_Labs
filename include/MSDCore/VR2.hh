#ifndef MSDCORE_VR2_HH
#define MSDCORE_VR2_HH

#include <cstdint>

struct VR2 {
  int32_t x, y;
};

VR2 operator+(const VR2 &a, const VR2 &b);

VR2 operator*(int32_t a, const VR2 &b);

int32_t abs(VR2 v);

#endif
