#ifndef HURTBOX_H
#define HURTBOX_H

#include<SDL.h>

class Hurtbox
{
    public:
        SDL_Rect rect;
        Hurtbox(int x, int y, int w, int h);
        virtual ~Hurtbox();
    protected:
    private:
};

#endif // HITBOX_H
