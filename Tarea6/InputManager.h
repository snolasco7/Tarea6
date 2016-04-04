#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include<SDL.h>
#include "Move.h"
#include "Button.h"
#include "DeviceButton.h"

#include <map>
#include <list>
#include <fstream>
using namespace std;

class InputManager
{
    public:
        map<char,DeviceButton*>input_map;
        list<Button*>buffer;
        vector<char>possible_buttons;
        InputManager(string file_path);
        int sdlKeboardMap(string scancode_name);
        bool isPressed(Button button);
        bool isInBuffer(Move move);
        void update();
        virtual ~InputManager();
    protected:
    private:
};

#endif // INPUTMANAGER_H
