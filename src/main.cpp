// Correct the positioning of collision
// Score system
// Displaying something on screen, like strike: 1, strike: 2, strike: 3
// maintain a list f top 5 games played till now with their high score and player name
// Sound effect
// Making a ball class

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Ball.hpp"

using namespace std;

// static float xdir = 1, ydir = 1;
static int count = 0;
// vector<pair<bool, bool>> flags;

int main(int argc, char *argv[])
{
    int state = 1;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "SDL_Init failure." << SDL_GetError() << endl;
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        cout << "IMG_Init failure." << SDL_GetError() << endl;
    }

    RenderWindow window("GAME v1.0", 1200, 800);

    SDL_Texture *ballTexture = window.loadTexture("images/ball.png");
    SDL_Texture *holeTexture = window.loadTexture("images/hole.png");
    SDL_Texture *bg2Texture = window.loadTexture("images/123.png");
    SDL_Texture *blockTexture = window.loadTexture("images/block.png");
    SDL_Texture *bgTexture = window.loadTexture("images/bg.png");
    SDL_Texture *logoTexture = window.loadTexture("images/logo.png");
    SDL_Texture *menuTexture = window.loadTexture("images/menu.png");
    // SDL_Texture* pointTexture = window.loadTexture("images/point.png");
    // SDL_Texture* tileDarkTexture32 = window.loadTexture("images/tile32_dark.png");
    // SDL_Texture* tileDarkTexture64 = window.loadTexture("images/tile64_dark.png");
    // SDL_Texture* tileLightTexture32 = window.loadTexture("images/tile32_light.png");
    // SDL_Texture* tileLightTexture64 = window.loadTexture("images/tile64_light.png");
    // SDL_Texture* ballShadowTexture = window.loadTexture("images/ball_shadow.png");
    // SDL_Texture* uiBgTexture = window.loadTexture("images/UI_bg.png");
    // SDL_Texture* levelTextBgTexture = window.loadTexture("images/levelText_bg.png");
    // SDL_Texture* powerMeterTexture_FG = window.loadTexture("images/powermeter_fg.png");
    // SDL_Texture* powerMeterTexture_BG = window.loadTexture("images/powermeter_bg.png");
    // SDL_Texture* powerMeterTexture_overlay = window.loadTexture("images/powermeter_overlay.png");
    // SDL_Texture* click2start = window.loadTexture("images/click2start.png");
    // SDL_Texture* endscreenOverlayTexture = window.loadTexture("images/end.png");
    // SDL_Texture* splashBgTexture = window.loadTexture("images/splashbg.png");

    Ball *ball1 = new Ball();

    Entity intro(50, 70, logoTexture);

    Entity e(100, 400, ballTexture);
    Entity f(308, 106, holeTexture);

    Entity Block1(200, 300, blockTexture);
    Entity Block2(500, 100, blockTexture);

    SDL_Rect block1 = Block1.getCurrentFrame();
    SDL_Rect block2 = Block2.getCurrentFrame();
    block1.w *= 8;
    block2.w *= 8;
    block1.h *= 4;
    block2.h *= 4;
    Block1.setCurrFrame(block1);
    Block2.setCurrFrame(block2);

    vector<Entity> blocks;
    blocks.push_back(Block1);
    blocks.push_back(Block2);

    for (int i = 0; i < blocks.size(); i++)
        ball1->AddtoFlag({0, 0});


    bool game = true;
    bool isClicked = true;

    SDL_Event event;

    while (game)
    {
        frameStart = SDL_GetTicks();

        if (state == 0)
        {
            window.clear();
            window.Background(menuTexture);
        }

        else
        {
            window.clear();
            window.Background(bg2Texture);
            window.render(Block1);
            window.render(Block2);
            window.render(f);
            ball1->moveBall(e, f, blocks, window);
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                game = false;
                continue;
            }

            if (ball1->getMovingState())
            {
                if (event.type == SDL_MOUSEBUTTONUP)
                {

                    if (!isClicked)
                    {

                        cout << "Over Here\n";

                        isClicked = true;
                        cout << "Released\n";

                        float xcoor = e.getX();
                        float ycoor = e.getY();
                        int x, y;
                        Uint32 buttons;
                        buttons = SDL_GetMouseState(&x, &y);

                        // mouse should not be released at the same point as ball
                        float xDir = abs(xcoor - x);
                        float yDir = abs(ycoor - y); 
                        ball1->setXdir(xDir);
                        ball1->setYdir(yDir);

                        // xdir = ydir/xdir;

                        if (x > xcoor){
                            xDir = -1 * xDir;
                            ball1->setXdir(xDir);
                        }
                        if (y > ycoor){
                            yDir = -1 * yDir;
                            ball1->setYdir(yDir);
                        }
                        // deciding speed
                        float maxV = 10;
                        float xdis = abs(xcoor - x);
                        float ydis = abs(ycoor - y);

                        float radialDis = sqrt(pow(xdis, 2) + pow(ydis, 2));

                        ball1->setSpeed(min(maxV, radialDis));
                        ball1->setMovingState(false);
                    }
                }

                if (event.type == SDL_MOUSEBUTTONDOWN)
                {

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
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }

        window.display();
    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}