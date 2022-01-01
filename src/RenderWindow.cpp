#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include"Entity.hpp"
#include"RenderWindow.hpp"
// #include "Dot.hpp"
using namespace std;

RenderWindow::RenderWindow(const char* p_title, int p_width, int p_height)
:window(NULL), renderer(NULL)
{
    windowHeight = p_height;
    windowWidth = p_width;
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_width, p_height, SDL_WINDOW_SHOWN);
    if(window == NULL) cout<<"Window failed to init"<<SDL_GetError()<<endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filepath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filepath);
    if(texture == NULL) cout<<"Falied in LoadTexture"<<SDL_GetError()<<endl;
    return texture;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity &p_entity){
    SDL_Rect src, dst;
    src.x=p_entity.getCurrentFrame().x;
    src.y=p_entity.getCurrentFrame().y;
    src.w=p_entity.getCurrentFrame().w;
    src.h=p_entity.getCurrentFrame().h;
    dst.x=p_entity.getX();
    dst.y=p_entity.getY();
    dst.w=p_entity.getCurrentFrame().w;
    dst.h=p_entity.getCurrentFrame().h;
    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::DrawRectangle(SDL_Texture* tex, int x_pos, int y_pos, int w, int h) {
	SDL_Rect* box = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	box->x = x_pos;
	box->y = y_pos;
	box->w = w;
	box->h = h;
	SDL_RenderCopy(renderer, tex, NULL, box);
}

void RenderWindow::Background(SDL_Texture* bg){
    SDL_RenderCopy(renderer, bg, NULL, NULL);
}

void RenderWindow::rndr(SDL_Rect &wall){
    SDL_RenderDrawRect(renderer, &wall);
}

void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}

int RenderWindow::h(){
    return windowHeight;
}

int RenderWindow::w(){
    return windowWidth;
}