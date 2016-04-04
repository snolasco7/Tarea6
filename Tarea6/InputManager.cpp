#include "InputManager.h"

InputManager::InputManager(string file_path)
{
    possible_buttons.push_back('8');
    possible_buttons.push_back('2');
    possible_buttons.push_back('4');
    possible_buttons.push_back('6');
    possible_buttons.push_back('a');
    possible_buttons.push_back('b');
    possible_buttons.push_back('c');

    ifstream in(file_path.c_str());
    char input;
    string device;
    while(in>>input)
    {
        in>>device;
        input_map[input]=new DeviceButton(sdlKeboardMap(device));
    }

    for(int i=0;i<20;i++)
    {
        buffer.push_back(new Button('5'));
    }
}

InputManager::~InputManager()
{
    //dtor
}

bool InputManager::isPressed(Button button)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    DeviceButton* device_button = input_map[button.value];
    if(device_button!=NULL)
    {
        if(currentKeyStates[device_button->sdl_scancode_key])
            return true;
        else
            return false;
    }
}

void InputManager::update()
{
//    for(list<Button*>::iterator i=buffer.begin();
//        i!=buffer.end();
//        i++)
//        cout<<(*i)->value;
//    cout<<endl;
//    cout.flush();

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    bool is_button_pressed = false;
    for(int i=0;i<possible_buttons.size();i++)
    {
        if(isPressed(possible_buttons[i]))
        {
            buffer.push_back(new Button(possible_buttons[i]));
            buffer.pop_front();
            is_button_pressed=true;
            break;
        }
    }
    if(!is_button_pressed)
    {
        buffer.push_back(new Button('5'));
        buffer.pop_front();
    }
}

bool InputManager::isInBuffer(Move move)
{
    move.buttons;
    buffer;
    list<Button*>::iterator buffer_iterator=buffer.end();
    buffer_iterator--;

    for(int i=move.buttons.size()-1;i>=0;i--)
    {
        if((*buffer_iterator)->value!=move.buttons[i]->value)
        {
            return false;
        }
        buffer_iterator--;
    }
    return true;
}

int InputManager::sdlKeboardMap(string scancode_name)
{
    map<string,int>sdl_key_constants;
    sdl_key_constants["SDL_SCANCODE_Q"]=SDL_SCANCODE_Q;
    sdl_key_constants["SDL_SCANCODE_W"]=SDL_SCANCODE_W;
    sdl_key_constants["SDL_SCANCODE_E"]=SDL_SCANCODE_E;
    sdl_key_constants["SDL_SCANCODE_R"]=SDL_SCANCODE_R;
    sdl_key_constants["SDL_SCANCODE_T"]=SDL_SCANCODE_T;
    sdl_key_constants["SDL_SCANCODE_Y"]=SDL_SCANCODE_Y;
    sdl_key_constants["SDL_SCANCODE_U"]=SDL_SCANCODE_U;
    sdl_key_constants["SDL_SCANCODE_I"]=SDL_SCANCODE_I;
    sdl_key_constants["SDL_SCANCODE_O"]=SDL_SCANCODE_O;
    sdl_key_constants["SDL_SCANCODE_P"]=SDL_SCANCODE_P;

    sdl_key_constants["SDL_SCANCODE_A"]=SDL_SCANCODE_A;
    sdl_key_constants["SDL_SCANCODE_S"]=SDL_SCANCODE_S;
    sdl_key_constants["SDL_SCANCODE_D"]=SDL_SCANCODE_D;
    sdl_key_constants["SDL_SCANCODE_F"]=SDL_SCANCODE_F;
    sdl_key_constants["SDL_SCANCODE_G"]=SDL_SCANCODE_G;
    sdl_key_constants["SDL_SCANCODE_H"]=SDL_SCANCODE_H;
    sdl_key_constants["SDL_SCANCODE_J"]=SDL_SCANCODE_J;
    sdl_key_constants["SDL_SCANCODE_K"]=SDL_SCANCODE_K;
    sdl_key_constants["SDL_SCANCODE_L"]=SDL_SCANCODE_L;

    sdl_key_constants["SDL_SCANCODE_Z"]=SDL_SCANCODE_Z;
    sdl_key_constants["SDL_SCANCODE_X"]=SDL_SCANCODE_X;
    sdl_key_constants["SDL_SCANCODE_C"]=SDL_SCANCODE_C;
    sdl_key_constants["SDL_SCANCODE_V"]=SDL_SCANCODE_V;
    sdl_key_constants["SDL_SCANCODE_B"]=SDL_SCANCODE_B;
    sdl_key_constants["SDL_SCANCODE_N"]=SDL_SCANCODE_N;
    sdl_key_constants["SDL_SCANCODE_M"]=SDL_SCANCODE_M;

    return sdl_key_constants[scancode_name];
}
