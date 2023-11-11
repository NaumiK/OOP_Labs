#include "Figure/PictogramOfTheAncientGods.hh"
#include <iostream>

Figure::PictogramOfTheAncientGods::PictogramOfTheAncientGods(VR2 O, int32_t r, double angle)
    : egn_(O, r), inside_(O, r) {
  std::cout << "PictogramOfTheAncientGods()\n";
  inside_.SetAngle(angle);
}
void Figure::PictogramOfTheAncientGods::Rotate(double da) { inside_.Rotate(da); }

void Figure::PictogramOfTheAncientGods::MoveTo(VR2 v) {
  inside_.MoveTo(v);
  egn_.MoveTo(v);
}

void Figure::PictogramOfTheAncientGods::SetPosition(VR2 v) {
  inside_.SetPosition(v);
  egn_.SetPosition(v);
}

VR2 Figure::PictogramOfTheAncientGods::GetPosition() { return inside_.GetPosition(); }

void Figure::PictogramOfTheAncientGods::SetRadius(int32_t r) {
  inside_.SetRadius(r);
  egn_.SetRadius(r);
}

void Figure::PictogramOfTheAncientGods::SetAngle(double angle) { inside_.SetAngle(angle); }

int32_t Figure::PictogramOfTheAncientGods::GetRadius() { return egn_.GetRadius(); }

double Figure::PictogramOfTheAncientGods::GetAngle() { return inside_.GetAngle(); }

void Figure::PictogramOfTheAncientGods::Show(SDL_Renderer *r) {
  inside_.Show(r);
  egn_.Show(r);
}
