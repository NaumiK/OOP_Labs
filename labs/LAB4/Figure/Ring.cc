#include "Figure/Ring.hh"
#include <iostream>

Figure::Ring::Ring(VR2 O, int32_t r, int32_t t)
    : in(O, r - t / 2), out(O, r + t / 2) {
  std::cout << "Ring()\n";
}

void Figure::Ring::MoveTo(VR2 v) {
  in.MoveTo(v);
  out.MoveTo(v);
}

void Figure::Ring::Show(SDL_Renderer *r) {
  in.Show(r);
  out.Show(r);
}

void Figure::Ring::SetPosition(VR2 O) {
  in.SetPosition(O);
  out.SetPosition(O);
}

void Figure::Ring::SetRadius(int32_t r) {
  auto t = GetThickness();
  in.SetRadius(r - t);
  out.SetRadius(r + t);
}

void Figure::Ring::SetThickness(int32_t t) {
  auto r = GetThickness() + in.GetRadius();
  in.SetRadius(r + t);
  out.SetRadius(r - t);
}

VR2 Figure::Ring::GetPosition() { return in.GetPosition(); }

int32_t Figure::Ring::GetThickness() {
  return (out.GetRadius() - in.GetRadius()) / 2;
}

int32_t Figure::Ring::GetRadius() { return in.GetRadius() + GetThickness(); }
