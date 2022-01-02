// Correct the positioning of collision
// Score system
// Displaying something on screen, like strike: 1, strike: 2, strike: 3
// maintain a list f top 5 games played till now with their high score and player name
// Sound effect

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <queue>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Ball.hpp"
#include "Loader.hpp"
#include "Menu.hpp"
// #include "SDL2/SDL_mixer.h"

using namespace std;

static int level = 1;
static bool isClicked = true;
static priority_queue<pair<int, string>> scores;
static vector<Entity> blocks;
static vector<Entity> pointerAndMeters;

pair<Entity, Entity> levelLoader(vector<SDL_Texture *> textures, Ball *ball)
{
    isClicked = true;
    Loader *loader = new Loader(textures);
    // 0 : tile32 light
    // 1 : tile32 dark
    // 2 : tile64 light
    // 3 : tile64 dark
    // 4 : ball
    // 5 : hole
    // 6 : shadow

    blocks = loader->load_tiles(level);
    Entity e = blocks[blocks.size() - 1]; // ball
    // cout << e.getX() <<" " << e.getY() <<"\n";
    Entity f = blocks[blocks.size() - 2]; // hole
    // cout << f.getX() <<" " << f.getY() <<"\n\n";

    blocks.erase(blocks.end() - 1);
    blocks.erase(blocks.end() - 1);

    for (int i = 0; i < blocks.size(); i++)
        ball->AddtoFlag({0, 0});

    return {e, f};
}

void PhyStriker(vector<SDL_Texture *> textures, Ball *ball1, RenderWindow window, SDL_Texture *bg, Button *restart)
{
    // int state = 1;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    pair<Entity, Entity> BallHole = levelLoader(textures, ball1);

    Entity e = BallHole.first;
    Entity f = BallHole.second;

    SDL_Texture *pointTexture = window.loadTexture("images/point.png");
    SDL_Texture *powerMeterTexture_GG1 = window.loadTexture("images/powermeter_gg1.png");
    SDL_Texture *powerMeterTexture_GG2 = window.loadTexture("images/powermeter_gg2.png");
    SDL_Texture *powerMeterTexture_GG3 = window.loadTexture("images/powermeter_gg3.png");
    SDL_Texture *powerMeterTexture_GG4 = window.loadTexture("images/powermeter_gg4.png");
    SDL_Texture *powerMeterTexture_GG5 = window.loadTexture("images/powermeter_gg5.png");
    SDL_Texture *powerMeterTexture_GG = window.loadTexture("images/powermeter_gg.png");
    SDL_Texture *powerMeterTexture_overlay = window.loadTexture("images/powermeter_overlay.png");
    
    Entity p(e.getX(), e.getY(), pointTexture);
    Entity pm1(50, 8, powerMeterTexture_GG1);
    Entity pm2(50, 8, powerMeterTexture_GG2);
    Entity pm3(50, 8, powerMeterTexture_GG3);
    Entity pm4(50, 8, powerMeterTexture_GG4);
    Entity pm5(50, 8, powerMeterTexture_GG5);
    Entity pm6(50, 8, powerMeterTexture_GG);
    Entity pm(50, 8, powerMeterTexture_overlay);
    SDL_Rect resize;
    resize.x = 0;
    resize.y = 0;
    resize.w = 16;
    resize.h = 32;

    pointerAndMeters = {p, pm1, pm2, pm3, pm4, pm5, pm6, pm};

    for (int z = 1; z < pointerAndMeters.size() ; z++){
        pointerAndMeters[z].setCurrFrame(resize);
    }

    bool game = true;
    int holding = 0;

    SDL_Event event;
    MouseInput *mouse = new MouseInput();

    while (game)
    {
        frameStart = SDL_GetTicks();

        window.clear();
        window.Background(bg);
        restart->DrawButton(&window);
        for (Entity x : blocks)
        {
            window.render(x);
        }
        window.render(f);

        bool LevelRunning = ball1->moveBall(e, f, blocks, window, level, pointerAndMeters);

        // Restart condition
        if (restart->isButtonClicked(mouse))
        {
            ball1->setSpeed(0);
            ball1->setMovingState(true);
            ball1->setDroppingState(false);
            level--;
            LevelRunning = false;
        }

        if (!LevelRunning)
        {
            level++;
            BallHole = levelLoader(textures, ball1);
            e = BallHole.first;
            f = BallHole.second;
            continue;
        }
        // SDL_Event event;
        int x, y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x, &y);

        if (holding){
            float temp = sqrt(pow(x-e.getX()-e.getCurrentFrame().w/2, 2) + pow(y-e.getY()-e.getCurrentFrame().h/2, 2));  
            int index = 0;

            if (temp <= 10)
                index = 1;

            else if (temp < 20)
                index = 2;

            else if (temp < 40)
                index = 3;

            else if (temp < 60)
                index = 4;

            else if (temp < 85)
                index = 5;

            else if (temp > 85) 
                index = 6;
            
            // window.render(pointerAndMeters[0]);
            window.render(pointerAndMeters[index]);
            window.render(pointerAndMeters[pointerAndMeters.size()-1]);
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
                    // window.render(p);

                    if (!isClicked)
                    {
                        isClicked = true;

                        float xcoor = e.getX() + e.getCurrentFrame().w / 2;
                        float ycoor = e.getY() + e.getCurrentFrame().h / 2;
                        buttons = SDL_GetMouseState(&x, &y);

                        // mouse should not be released at the same point as ball
                        float xDir = abs(xcoor - x);
                        float yDir = abs(ycoor - y);

                        // float slope = atan(yDir/xDir);

                        ball1->setXdir(xDir);
                        ball1->setYdir(yDir);

                        // xdir = ydir/xdir;

                        if (x > xcoor)
                        {
                            xDir = -1 * xDir;
                            ball1->setXdir(xDir);
                        }
                        if (y > ycoor)
                        {
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
                        // Mix_PlayChannel(-1, swing, 0);
                        // if (ball1->getSpeed() < 5)
                        holding = 0;
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
                        holding = 1;
                        isClicked = false;
                        // cout << x << "\t" << y <<"\n";
                    }
                }
            }
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }

        window.display();
    }
}

bool HighScores(RenderWindow window, SDL_Texture* bg)
{
    vector<pair<int, string>> displayScores;
    int index = 1;

    if (scores.size() < 5)
    {
        while (!scores.empty())
        {
            displayScores.push_back(scores.top());
            scores.pop();
        }
    }
    else
    {
        while (displayScores.size() != 5)
        {
            displayScores.push_back(scores.top());
            scores.pop();
        }
    }
    
    bool viewHighScore = true;
    Button *back = new Button(0, 0, 50, 50, "images/back.png");

    MouseInput *mouse = new MouseInput();

    SDL_Event event;

    while (viewHighScore)
    {
        if (back->isButtonClicked(mouse)){
            viewHighScore = false;
            return true;
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return false;
            }
        }

        window.clear();
        // text rendering onto screen
        window.Background(bg);
        back->DrawButton(&window);
        window.display();
    }
    
    return true;
    // for (auto x : displayScores)
    // {
    //     // Render this text message onto screen
    //     cout << index++ << "\t" << x.second << "  " << x.first << "\n";
    //     scores.push(x);
    // }

    // return true;
}

void MainMenu(RenderWindow window, vector<SDL_Texture *> textures, SDL_Texture *bg)
{

    Menu *menu = new Menu(&window);

    menu->MenuLoop();
    if (menu->getWindowType() == "Exit" || menu->getWindowType() == "Main_Menu")
    {
        return;
    }

    else if (menu->getWindowType() == "Scores")
    {
        bool next = HighScores(window, bg);
        if (!next)
        {
            return;
        }

        else{
            MainMenu(window, textures, bg);
        }
    }

    else if (menu->getWindowType() == "Game")
    {
        Button *restart = new Button(0, 0, 50, 50, "images/Restart2.png");

        Ball *ball = new Ball();
        PhyStriker(textures, ball, window, bg, restart);
    }
}

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "SDL_Init failure." << SDL_GetError() << endl;
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        cout << "IMG_Init failure." << SDL_GetError() << endl;
    }

    RenderWindow window("PhyStriker", 640, 720);

    SDL_Texture *ballTexture = window.loadTexture("images/ball.png");
    SDL_Texture *holeTexture = window.loadTexture("images/hole.png");
    SDL_Texture *bg2Texture = window.loadTexture("images/1232.png");
    SDL_Texture *blockTexture = window.loadTexture("images/block.png");
    SDL_Texture *bgTexture = window.loadTexture("images/bg.png");
    SDL_Texture *logoTexture = window.loadTexture("images/logo.png");
    SDL_Texture *menuTexture = window.loadTexture("images/menu.png");
    SDL_Texture *tileDarkTexture32 = window.loadTexture("images/tile32_dark.png");
    SDL_Texture *tileDarkTexture64 = window.loadTexture("images/tile64_dark.png");
    SDL_Texture *tileLightTexture32 = window.loadTexture("images/tile32_light.png");
    SDL_Texture *tileLightTexture64 = window.loadTexture("images/tile64_light.png");
    SDL_Texture *ballShadowTexture = window.loadTexture("images/ball_shadow.png");
    SDL_Texture *uiBgTexture = window.loadTexture("images/UI_bg.png");
    SDL_Texture *levelTextBgTexture = window.loadTexture("images/levelText_bg.png");
    SDL_Texture *click2start = window.loadTexture("images/click2start.png");
    SDL_Texture *endscreenOverlayTexture = window.loadTexture("images/end.png");
    SDL_Texture *playButton = window.loadTexture("images/Play.png");
    SDL_Texture *RestartButton = window.loadTexture("images/Restart.jpg");
    SDL_Texture *high_Scores = window.loadTexture("images/HighScore.png");

    // Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    // // SDL_Texture* splashBgTexture = window.loadTexture("images/splashbg.png");
    // Mix_Chunk* charge = Mix_LoadWAV("sfx/charge.mp3");
    // Mix_Chunk* swing = Mix_LoadWAV("sfx/swing.mp3");
    // Mix_Chunk* hole = Mix_LoadWAV("sfx/hole.mp3");

    // Entity intro(50, 70, logoTexture);
    // Entity startButton(100, 200, playButton);
    // Entity highScores(400, 200, high_Scores);
    vector<SDL_Texture *> textures = {tileLightTexture32, tileDarkTexture32, tileLightTexture64, tileDarkTexture64, ballTexture, holeTexture, ballShadowTexture};

    MainMenu(window, textures, bg2Texture);

    window.cleanUp();
    SDL_Quit();
    return 0;
}
