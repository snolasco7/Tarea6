#include "Hurtbox.h"

Hurtbox::Hurtbox(int x, int y, int w, int h)
{
    this->rect.x=x;
    this->rect.y=y;
    this->rect.w=w;
    this->rect.h=h;
}

Hurtbox::~Hurtbox()
{
    //dtor
}
