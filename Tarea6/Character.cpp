#include "Character.h"

std::string toString(int number)
{
    if (number == 0)
        return "0";

    if(number < 0)
        return "-"+toString(-number);

    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

int Character::posicion(){
    return this->x;
}

void Character::irPos(int x2){
x=x2;
}

void Character::retroseso(){
    if(!this->flipped){
        this->x-=20;
    }else{
        this->x+=20;
    }
}

Character::Character(SDL_Renderer* renderer, int x, int y, bool flipped, string input_manager_file)
{
    this->x=x;
    this->y=y;
    this->flipped=flipped;

    moves["idle"]=getMove(renderer,"idle",4);
    moves["kick"]=getMove(renderer,"kick",6);
    moves["punch"]=getMove(renderer,"punch",3);
    moves["walk_forward"]=getMove(renderer,"walk_forward",5);
    moves["walk_backward"]=getMove(renderer,"walk_backward",5);

    this->current_move = "idle";
    this->current_sprite = 0;
    this->current_sprite_frame = 0;
    this->input_manager=new InputManager(input_manager_file);
}

Move* Character::getMove(SDL_Renderer *renderer, string name, int sprite_amount)
{
    //Sprites load
    vector<Sprite*>sprites;
    string align_file_path = "assets/" + name + "/align.txt";
    ifstream align_file(align_file_path.c_str());
    for(int i=1;i<=sprite_amount;i++)
    {
        string path="assets/" + name + "/" + toString(i) + ".png";
        int align_x;
        int align_y;
        align_file>>align_x;
        align_file>>align_y;

        vector<Hitbox*>hitboxes;

        string hitbox_file_path = "assets/" + name + "/hitboxes/"+toString(i)+".txt";
        ifstream hitbox_file(hitbox_file_path.c_str());

        int x,y,w,h;
        while(hitbox_file>>x)
        {
            hitbox_file>>y;
            hitbox_file>>w;
            hitbox_file>>h;
            hitboxes.push_back(new Hitbox(x,y,w,h));
        }

        sprites.push_back(new Sprite(renderer,path,10,align_x,align_y,hitboxes));
    }

    //Cancel load
    string cancels_file_path = "assets/" + name + "/cancel.txt";
    ifstream cancels_file(cancels_file_path.c_str());
    vector<string>cancels;
    string cancel_temp;
    while(cancels_file>>cancel_temp)
    {
        cancels.push_back(cancel_temp);
    }

    string buttons_file_path = "assets/" + name + "/buttons.txt";
    ifstream buttons_file(buttons_file_path.c_str());
    vector<Button*>buttons;
    char button_temp;
    while(buttons_file>>button_temp)
    {
        buttons.push_back(new Button(button_temp));
    }

    return new Move(renderer,sprites,cancels,buttons);
}

Character::~Character()
{
    //dtor
}

void Character::logic()
{
    input_manager->update();

    if( input_manager->isInBuffer(*moves["kick"]) )
    {
        if(moves["kick"]->canCancel(this->current_move))
        {
            this->current_move = "kick";
            this->current_sprite = 0;
        }
    }
    else if( input_manager->isInBuffer(*moves["punch"]) )
    {
        if(moves["punch"]->canCancel(this->current_move))
        {
            this->current_move = "punch";
            this->current_sprite = 0;
        }
    }
    else if( input_manager->isInBuffer(*moves["walk_forward"]) )
    {
        if(moves["walk_forward"]->canCancel(this->current_move))
        {
            if(this->current_move!="walk_forward")
            {
                this->current_sprite = 0;
            }
            this->current_move = "walk_forward";
        }
    }
    else if( input_manager->isInBuffer(*moves["walk_backward"]) )
    {
        if(moves["walk_backward"]->canCancel(this->current_move))
        {
            if(this->current_move!="walk_backward")
            {
                this->current_sprite = 0;
            }
            this->current_move = "walk_backward";
        }
    }else
    {
        if(this->current_move=="walk_forward" || this->current_move=="walk_backward")
        {
            this->current_move = "idle";
            this->current_sprite = 0;
        }
    }

    current_sprite_frame++;
    if(current_sprite_frame>=moves[current_move]->sprites[current_sprite]->frames)
    {
        current_sprite++;
        if(current_sprite>=moves[current_move]->sprites.size())
        {
            current_move= "idle";
            current_sprite=0;
        }
        current_sprite_frame=0;
    }

    if(current_move=="walk_forward")
    {
        this->x+=5;
    }
    if(current_move=="walk_backward")
    {
        this->x-=5;
    }
}

void Character::draw()
{
    moves[current_move]->draw(current_sprite,x,y,flipped);
}

vector<Hitbox*> Character::getHitboxes()
{
    return moves[current_move]->sprites[current_sprite]->hitboxes;
}
