#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<stdio.h>
#include<string>
#include<iostream>
#include<list>
#include "Character.h"
#include "Button.h"
#include "DeviceButton.h"
#include "InputManager.h"

using namespace std;
int resu=0;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background;
SDL_Texture *pw1;
SDL_Texture *pw2;
SDL_Texture *punta1;
SDL_Texture *punta2;
SDL_Rect rect_background,rect_character,rec_punta1,rec_punta2,pw1_rect,pw2_rect;
int score1=0;
int score2=0;
Mix_Music *gMusic=NULL;
Mix_Chunk *gChunk=NULL;
bool gano=true;

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1100/*WIDTH*/, 800/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    gano = false;
    }

    gMusic = Mix_LoadMUS( "assets/sound/Game Music.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        gano = false;
    }

    gChunk = Mix_LoadWAV( "assets/sound/Punch Sound Effect.wav" );
    if( gChunk == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        gano = false;
    }

    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    background = IMG_LoadTexture(renderer,"assets/bg.jpg");
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = 1100;
    rect_background.h = 800;

    rec_punta1.x=300;
    rec_punta1.y=0;
    rec_punta1.w=101;
    rec_punta1.h=73;

    rec_punta2.x=700;
    rec_punta2.y=0;
    rec_punta2.w=101;
    rec_punta2.h=73;

    Character* character = new Character(renderer,350,750,false,"assets/inputs_player1.txt");
    Character* character2 = new Character(renderer,750,750,true,"assets/inputs_player2.txt");
    Character* pw1 = new Character(renderer,500,500,false,"p1w.png");
    Character* pw2 = new Character(renderer,500,500,false,"p2w.png");



    map<DeviceButton*,Button*>input_map;

    int frame=0;

    double last_fame_ticks=SDL_GetTicks();
    Mix_PlayMusic(gMusic,-1);
    //Main Loop
    while(true)
    {
        frame++;
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_d)
                    rect_character.x++;
                if(Event.key.keysym.sym == SDLK_a)
                    rect_character.x--;
            }
        }
        //jugador 1
        if(score1==0){
            punta1 = IMG_LoadTexture(renderer,"0.png");
        }else if(score1==1){
            punta1 = IMG_LoadTexture(renderer,"1.png");
        }else if(score1==2){
            punta1 = IMG_LoadTexture(renderer,"2.png");
        }else if(score1==3){
            punta1 = IMG_LoadTexture(renderer,"3.png");
        }
        //jugador 2
        if(score2==0){
            punta2 = IMG_LoadTexture(renderer,"0.png");
        }else if(score2==1){
            punta2 = IMG_LoadTexture(renderer,"1.png");
        }else if(score2==2){
            punta2 = IMG_LoadTexture(renderer,"2.png");
        }else if(score2==3){
            punta2 = IMG_LoadTexture(renderer,"3.png");
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);


        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, punta1, NULL, &rec_punta1);
        SDL_RenderCopy(renderer, punta2, NULL, &rec_punta2);

        character->logic();
        character->draw();

        character2->logic();
        character2->draw();

        vector<Hitbox*>char1_hitboxes=character->getHitboxes();
        vector<Hitbox*>char2_hitboxes=character2->getHitboxes();

        for(int i=0;i<char1_hitboxes.size();i++)
        {
            for(int j=0;j<char2_hitboxes.size();j++)
            {
                SDL_Rect rect1 = char1_hitboxes[i]->rect;
                SDL_Rect rect2 = char2_hitboxes[j]->rect;

                if(!character->flipped)
                {
                    rect1.x+=character->x;
                }else
                {
                    rect1.x=-rect1.x-rect1.w+character->x;
                }
                rect1.y=-rect1.y+character->y;

                if(!character2->flipped)
                {
                    rect2.x+=character2->x;
                }else
                {
                    rect2.x=-rect2.x-rect2.w+character2->x;
                }
                rect2.y=-rect2.y+character2->y;
                if(collides(rect1,rect2))
                {
                    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
                    if(currentKeyStates[ SDL_SCANCODE_X ] || currentKeyStates[ SDL_SCANCODE_Z ])
                    {
                        if(damage(rect1,rect2)){
                            Mix_PlayChannel( -1, gChunk, 0 );
                            character2->retroseso();
                            drawRect(renderer,rect2.x,rect2.y,rect2.w,rect2.h,0,0,255,0);
                            cout<<"Ahhhh!"<<endl;
                        }
                    }
                    if(currentKeyStates[ SDL_SCANCODE_N ] ||currentKeyStates[ SDL_SCANCODE_B ])
                    {
                        if(damage(rect1,rect2)){
                            Mix_PlayChannel( -1, gChunk, 0 );
                            character->retroseso();
                            drawRect(renderer,rect1.x,rect1.y,rect1.w,rect1.h,0,0,255,0);
                            cout<<"Ahhhh!"<<endl;
                        }
                    }
                    cout<<"Colision!"<<endl;
                    Mix_PlayChannel( -1, gChunk, 0 );
                }else
                {
                   //Hola pito
                }
            }
        }

        if(character->x>character2->x)
        {
            character->flipped=true;
            character2->flipped=false;
        }else
        {
            character->flipped=false;
            character2->flipped=true;
        }

        double last_frame_length=SDL_GetTicks()-last_fame_ticks;
        double sleep_time=17-last_frame_length;
        //cout<<"Length: "<<last_frame_length<<", Sleep time: "<<sleep_time<<endl;
        if(sleep_time>0)
            SDL_Delay(sleep_time);
        last_fame_ticks=SDL_GetTicks();

        if(character->x>=950 || character->x<=100){
        score2=score2+1;

        character->irPos(350);
        character2->irPos(750);
        }

        cout<<score2<<endl;
        if(character2->x>=950 || character2->x<=100){
        score1=score1+1;
        character->irPos(350);
        character2->irPos(750);
        }
        cout<<score1<<endl;
        SDL_Texture *pw;
        if(score1==3){
            cout<<"Jugador 1 ganoooo"<<endl;
            pw2->logic();
            pw1->draw();
            //SDL_RenderCopy(renderer, pw1, NULL, &pw1_rect);
        }else if(score2==3){
            cout<<"Jugador 2 ganoooo"<<endl;
            pw2->logic();
            pw2->draw();
            //SDL_RenderCopy(renderer, pw2, NULL, &pw2_rect);
        }

//        drawRect(renderer,10,30,50,100,
//                 0,255,255,0);
        SDL_RenderPresent(renderer);
    }

	return 0;
}
