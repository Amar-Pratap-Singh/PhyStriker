#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
class Entity{
private:
    SDL_Rect currentFrame;
    SDL_Texture* tex; 
    float x, y;

public:
    Entity(float p_x, float p_y, SDL_Texture* p_tex);
    float getX();
    float getY();
    void setX(float);
    void setY(float);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
    void setCurrFrame(SDL_Rect &r);
};