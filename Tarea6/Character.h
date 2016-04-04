#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <map>
#include <fstream>
#include "Move.h"
#include "InputManager.h"
using namespace std;

class Character
{
    public:
        InputManager *input_manager;
        map<string,Move*>moves;
        string current_move;
        int current_sprite;
        int current_sprite_frame;
        int x;
        int y;
        bool flipped;
        Character(SDL_Renderer* renderer, int x, int y, bool flipped, string input_manager_file);
        virtual ~Character();
        void logic();
        void draw();
        int posicion();
        void irPos(int x1);
        void retroseso();
        Move* getMove(SDL_Renderer *renderer, string name, int sprite_amount);
        vector<Hitbox*> getHitboxes();
    protected:
    private:
};

#endif // CHARACTER_H
