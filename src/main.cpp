// Correct the positioning of collision
// Score system
// Displaying something on screen, like strike: 1, strike: 2, strike: 3
// maintain a list f top 5 games played till now with their high score and player name
// Sound effect

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"

using namespace std;

static float speed = 0;
static float xdir = 1, ydir = 1;
static int count = 0;
static bool moving = true;
vector <pair<bool, bool>> flags;

void rebound(float xcoor, float ycoor){
    if (ycoor < 0 || ycoor > 720){
        ydir = -1*ydir;
    }

    else if (xcoor < 0 || xcoor > 1280){
        xdir = -1*xdir;
    }

    speed -= 0.5;
}

void droppingBall(Entity &e){
    // Stop the ball
    xdir = 0;
    ydir = 0;
    
    // Decrease the size of ball
    SDL_Rect a;
    a = e.getCurrentFrame();

    if (a.h < 0){
        cout << "You WIN\n";
        exit(0);
        // Ball disappeared
        // Game won
        // Do something
    }

    a.h -= 0.5;
    a.w -= 0.5;
    e.setCurrFrame(a);
}



pair<bool, bool> Collision(float xcoor, float ycoor, Entity &b, bool flagX, bool flagY){
    
    // cout << ycoor <<" " << b.getY() + b.getCurrentFrame().h << "\n";
    if (!flagX && ycoor >= b.getY() && ycoor <= b.getY() + b.getCurrentFrame().h){
        flagY = 1;
        // Collision from left and right
        if (xcoor >= b.getX() && xcoor <= b.getX() + b.getCurrentFrame().w){
            cout << "Left Right" << "\n";
            xdir *= -1;
            speed -= 0.5;
        }
    }
    
    else if (!flagY && xcoor >= b.getX() && xcoor <= b.getX() + b.getCurrentFrame().w){
        flagX = 1;
        // Collision from below and above
        if (ycoor >= b.getY() && ycoor <= b.getY() + b.getCurrentFrame().h){
            cout << "Above Below\n";
            ydir *= -1;
            speed -= 0.5;
        }
    }

    
    else{
        speed -= 0.01;
        flagX = 0;
        flagY = 0;
    }

    return {flagX, flagY};
}

// Collision(xcoor, ycoor, entities, flags, i);


void moveBall(Entity &e, Entity &f, vector<Entity> &b, RenderWindow &window){
    if (!speed)
        window.render(e);
    
    else{
        float xcoor = e.getX();
        float ycoor = e.getY();
        
        if (xcoor > f.getX()-10 && xcoor < f.getX()+10 && ycoor > f.getY()-10 && ycoor < f.getY()+10){
            e.setX(f.getX());
            e.setY(f.getY());
            // window.render(e);
            droppingBall(e);
        }

        // rebound condition
        // int collisionVal = isColliding(e, b);
        // cout << "COllision Value: " << collisionVal << "\n";

        // cout << SDL_HasIntersection(&firstObj, &secondObj) << "\n"; 
        if ((xcoor > 1280 || xcoor < 0) || (ycoor > 720 || ycoor < 0)){
            rebound(xcoor, ycoor);
        }
        
        SDL_Rect firstObj = e.getCurrentFrame();
        
        int i = 0;
        for (Entity entities: b){
            SDL_Rect secondObj = entities.getCurrentFrame();

            if (SDL_HasIntersection(&firstObj, &secondObj)){
                cout << flags[i].first << " " << flags[i].second <<"\n";
                flags[i] = Collision(xcoor, ycoor, entities, flags[i].first, flags[i].second);
                i++;
                // cout << "Intersection: " << xcoor << "\t" << ycoor << "\n";
            }
            
            // can also decrease the speed here

            if (speed < 0){
                moving = true;
            }
            else{
                e.setX(xcoor + (xdir*speed)/100);
                e.setY(ycoor + (ydir*speed)/100);
            }
            window.render(e);
        }
        // collision condition
        // cout << xcoor << "\t" << ycoor << "\n"; 

    }
}


int main (int argc, char* argv[])
{
    int state=1;
    
    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;
 
    if(SDL_Init(SDL_INIT_VIDEO) > 0) {
        cout<<"SDL_Init failure."<<SDL_GetError()<< endl;
    }
 
    if(!IMG_Init(IMG_INIT_PNG)){
        cout<<"IMG_Init failure."<<SDL_GetError()<< endl;
    }
 
    RenderWindow window("GAME v1.0", 1280, 720);
    
    SDL_Texture* ballTexture = window.loadTexture("images/ball.png");
    SDL_Texture* holeTexture = window.loadTexture("images/hole.png");
    SDL_Texture* bg2Texture = window.loadTexture("images/123.png");
    SDL_Texture* blockTexture = window.loadTexture("images/block.png");
    // SDL_Texture* pointTexture = window.loadTexture("images/point.png");
    // SDL_Texture* tileDarkTexture32 = window.loadTexture("images/tile32_dark.png");
    // SDL_Texture* tileDarkTexture64 = window.loadTexture("images/tile64_dark.png");
    // SDL_Texture* tileLightTexture32 = window.loadTexture("images/tile32_light.png");
    // SDL_Texture* tileLightTexture64 = window.loadTexture("images/tile64_light.png");
    // SDL_Texture* ballShadowTexture = window.loadTexture("images/ball_shadow.png");
    SDL_Texture* bgTexture = window.loadTexture("images/bg.png");
    // SDL_Texture* uiBgTexture = window.loadTexture("images/UI_bg.png");
    // SDL_Texture* levelTextBgTexture = window.loadTexture("images/levelText_bg.png");
    // SDL_Texture* powerMeterTexture_FG = window.loadTexture("images/powermeter_fg.png");
    // SDL_Texture* powerMeterTexture_BG = window.loadTexture("images/powermeter_bg.png");
    // SDL_Texture* powerMeterTexture_overlay = window.loadTexture("images/powermeter_overlay.png");
    SDL_Texture* logoTexture = window.loadTexture("images/logo.png");
    // SDL_Texture* click2start = window.loadTexture("images/click2start.png");
    // SDL_Texture* endscreenOverlayTexture = window.loadTexture("images/end.png");
    // SDL_Texture* splashBgTexture = window.loadTexture("images/splashbg.png");
    SDL_Texture* menuTexture = window.loadTexture("images/menu.png");
    
    Entity e(100,400,ballTexture);
    Entity f(308,106,holeTexture);

    Entity b1(200,300,blockTexture);
    Entity b2(500,100,blockTexture);

    SDL_Rect block1 = b1.getCurrentFrame();
    SDL_Rect block2 = b2.getCurrentFrame();
    block1.w *= 8;
    block2.w *= 8;
    block1.h *= 4;
    block2.h *= 4;
    b1.setCurrFrame(block1);
    b2.setCurrFrame(block2);
    
    vector <Entity> blocks;
    blocks.push_back(b1);
    blocks.push_back(b2);
    
    for (int i=0; i<blocks.size() ;i++)
        flags.push_back({0, 0});
    
    Entity intro(50,70,logoTexture);
    // Entity d(200, 400, ballTexture);
    // Dot dot;
    
    // SDL_Rect wall;
    // wall.x = 300;
    // wall.y = 40;
    // wall.w = 40;
    // wall.h = 400;

    bool game = true;
    bool isClicked = true;
    
    SDL_Event event;
    
    while(game){
        
        frameStart = SDL_GetTicks();

        if(state==0){
            window.clear();
            window.Background(menuTexture);
        }
        
        else{
            window.clear();
            window.Background(bg2Texture);
            window.render(b1);
            window.render(b2);
            window.render(f);
            moveBall(e, f, blocks, window);
        }

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                game = false;
                continue;
            }

            if (moving){
                if (event.type == SDL_MOUSEBUTTONUP){
                    
                    if (!isClicked){

                        cout << "Over Here\n";

                        isClicked = true;
                        cout << "Released\n";
                        
                        float xcoor = e.getX();
                        float ycoor = e.getY();
                        int x, y;
                        Uint32 buttons;
                        buttons = SDL_GetMouseState(&x, &y);
                        
                        // mouse should not be released at the same point as ball
                        xdir = abs(xcoor-x);
                        ydir = abs(ycoor-y);
                        
                        // xdir = ydir/xdir; 

                        if (x > xcoor)
                            xdir = -1*xdir;
                        
                        if (y > ycoor)
                            ydir = -1*ydir;

                        // deciding speed
                        float maxV = 10;
                        float xdis = abs(xcoor - x);
                        float ydis = abs(ycoor - y);
                        
                        float radialDis = sqrt(pow(xdis, 2) + pow(ydis, 2)); 
                        
                        speed = min(maxV, radialDis);
                        moving = false;
                    }
                }

                if (event.type == SDL_MOUSEBUTTONDOWN){
                    
                    int x, y;
                    Uint32 buttons;
                    buttons = SDL_GetMouseState(&x, &y);
                    
                    float xcoor = e.getX();
                    float ycoor = e.getY();
                    
                    SDL_Rect currFrame = e.getCurrentFrame();
                    
                    // Do it for left click only
                    if (xcoor - currFrame.w <= x && xcoor + currFrame.w >= x && ycoor - currFrame.h <= y && ycoor + currFrame.h >= y)
                    {
                        isClicked = false;
                        cout << "Pressed\n";
                        // cout << x << "\t" << y <<"\n";
                    }
                }
            }

            // if (SDL_BUTTON(SDL_BUTTON_LEFT)){
            //     cout << "Working\n";
            // }
            
            // if (SDL_BUTTON(SDL_BUTTON_RIGHT))
            //     cout << "Right Working\n"; 
            // if (event.type == SDL_MouseButtonEvent)
            // dot.handleEvent(event);

        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

        window.display();
    }

    window.cleanUp();
    SDL_Quit();
    return 0;
} 