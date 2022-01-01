#pragma once
#include<SDL.h>
#include<SDL_image.h>
class Entity{
private:
    SDL_Rect currentFrame;
    SDL_Texture* tex; 
    float x, y,angle;

public:
    Entity(float p_x, float p_y, SDL_Texture* p_tex);
    float getX();
    float getY();
    void setX(float);
    void setY(float);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
    void setCurrFrame(SDL_Rect &r);
    void setAngle(float angle);
};