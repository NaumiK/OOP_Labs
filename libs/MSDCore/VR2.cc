#include "VR2.hh"

VR2 operator+(const VR2 &a, const VR2 &b) { return {a.x + b.x, a.y + b.y}; }

VR2 operator*(int32_t a, const VR2 &b) { return {a * b.x, a * b.y}; }

int32_t abs(VR2 v) { return v.x * v.x + v.y * v.y; }
