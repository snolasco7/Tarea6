#include "Evaluar.h"

int Evaluar::paso(Character ch1,Character ch2){
    int xp=0;
    if(ch1.x>=1000 || ch1.x<=100){
        xp=1;
    }
    if(ch2.x>=1000 || ch2.x<=100){
        xp=2;
    }
    return xp;
}

Evaluar::Evaluar()
{
    //ctor
}

Evaluar::~Evaluar()
{
    //dtor
}
