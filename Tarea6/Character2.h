#ifndef CHARACTER2_H
#define CHARACTER2_H

#include <iostream>
#include <map>
#include <fstream>
#include "Move.h"
using namespace std;

class Character
{
    public:
        map<string,Move*>moves;
        string current_move;
        int current_sprite;
        int current_sprite_frame;
        int x;
        int y;
        Character(SDL_Renderer* renderer, int x, int y);
        virtual ~Character();
        void logic();
        void draw();
        Move* getMove(SDL_Renderer *renderer, string name, int sprite_amount);
    protected:
    private:
};

#endif // CHARACTER_H
