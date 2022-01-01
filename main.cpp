// Displaying something on screen, like strike: 1, strike: 2, strike: 3
// Correct the positioning of collision
// Score system
// maintain a list f top 5 games played till now with their high score and player name
// Sound effect
// Making a ball class DONE

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <queue>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Ball.hpp"
#include "Loader.hpp"

using namespace std;

static int level = 1;
static bool isClicked = true;
static priority_queue<pair<int, string>> scores;
static vector<Entity> blocks;

pair<Entity, Entity> levelLoader(vector<SDL_Texture*> textures, Ball* ball)
{
    isClicked = true;
    Loader* loader = new Loader(textures);
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

    Entity arr = blocks[blocks.size() - 3]; // arrow

    blocks.erase(blocks.end() - 1);
    blocks.erase(blocks.end() - 1);

    for (int i = 0; i < blocks.size(); i++)
        ball->AddtoFlag({ 0, 0 });

    return { e, f};
}

void PhyStriker(vector<SDL_Texture*> textures, Ball* ball1, RenderWindow window, SDL_Texture* bg)
{
    // int state = 1;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    pair<Entity, Entity> BallHole = levelLoader(textures, ball1);

    Entity e = BallHole.first;
    Entity f = BallHole.second;

    bool game = true;

    while (game)
    {
        frameStart = SDL_GetTicks();

        window.clear();
        window.Background(bg);
        for (Entity x : blocks)
        {
            window.render(x);
        }
        window.render(f);

        bool LevelRunning = ball1->moveBall(e, f, blocks, window, level);

        if (!LevelRunning)
        {
            level++;
            BallHole = levelLoader(textures, ball1);
            e = BallHole.first;
            f = BallHole.second;
            continue;
        }
        SDL_Event event;
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
                        isClicked = true;

                        float xcoor = e.getX() + e.getCurrentFrame().w / 2;
                        float ycoor = e.getY() + e.getCurrentFrame().h / 2;

                        //float xcoor = arr.getX() + arr.getCurrentFrame().w / 2;
                        //float ycoor = arr.getY() + arr.getCurrentFrame().h / 2;
                        int x, y;
                        Uint32 buttons;
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
                    }
                }

                if (event.type == SDL_MOUSEBUTTONDOWN)
                {

                    int x, y;
                    Uint32 buttons;
                    buttons = SDL_GetMouseState(&x, &y);

                    float xcoor = e.getX();
                    //float xcoor = arr.getX();
                    float ycoor = e.getY();

                    SDL_Rect currFrame = e.getCurrentFrame();

                    // Do it for left click only
                    if (xcoor - currFrame.w <= x && xcoor + currFrame.w >= x && ycoor - currFrame.h <= y && ycoor + currFrame.h >= y)
                    {
                        isClicked = false;
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
    // window.cleanUp();
}


void HighScores() {
    vector <pair<int, string>> displayScores;
    int index = 1;

    if (scores.size() < 5) {
        while (!scores.empty()) {
            displayScores.push_back(scores.top());
            scores.pop();
        }
    }
    else {
        while (displayScores.size() != 5) {
            displayScores.push_back(scores.top());
            scores.pop();
        }
    }

    for (auto x : displayScores) {
        // Render this text message onto screen
        cout << index++ << "\t" << x.second << "  " << x.first << "\n";
        scores.push(x);
    }
}


int main(int argc, char* argv[])
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

    SDL_Texture* ballTexture = window.loadTexture("images/ball.png");
    SDL_Texture* holeTexture = window.loadTexture("images/hole.png");
    SDL_Texture* bg2Texture = window.loadTexture("images/1232.png");
    SDL_Texture* blockTexture = window.loadTexture("images/block.png");
    SDL_Texture* bgTexture = window.loadTexture("images/bg.png");
    SDL_Texture* logoTexture = window.loadTexture("images/logo.png");
    SDL_Texture* menuTexture = window.loadTexture("images/menu.png");
    SDL_Texture* pointTexture = window.loadTexture("images/point.png");
    SDL_Texture* tileDarkTexture32 = window.loadTexture("images/tile32_dark.png");
    SDL_Texture* tileDarkTexture64 = window.loadTexture("images/tile64_dark.png");
    SDL_Texture* tileLightTexture32 = window.loadTexture("images/tile32_light.png");
    SDL_Texture* tileLightTexture64 = window.loadTexture("images/tile64_light.png");
    SDL_Texture* ballShadowTexture = window.loadTexture("images/ball_shadow.png");
    SDL_Texture* uiBgTexture = window.loadTexture("images/UI_bg.png");
    SDL_Texture* levelTextBgTexture = window.loadTexture("images/levelText_bg.png");
    SDL_Texture* powerMeterTexture_FG = window.loadTexture("images/powermeter_fg.png");
    SDL_Texture* powerMeterTexture_BG = window.loadTexture("images/powermeter_bg.png");
    SDL_Texture* powerMeterTexture_overlay = window.loadTexture("images/powermeter_overlay.png");
    SDL_Texture* click2start = window.loadTexture("images/click2start.png");
    SDL_Texture* endscreenOverlayTexture = window.loadTexture("images/end.png");
    SDL_Texture* playButton = window.loadTexture("images/Play.png");
    SDL_Texture* RestartButton = window.loadTexture("images/Restart.jpg");
    SDL_Texture* high_Scores = window.loadTexture("images/HighScore.png");

    // SDL_Texture* splashBgTexture = window.loadTexture("images/splashbg.png");

    Entity intro(50, 70, logoTexture);
    Entity startButton(100, 200, playButton);
    Entity highScores(400, 200, high_Scores);

    bool StartTheGame = true;
    bool ViewHighScores = false;
    //SDL_Event event;

    // while (SDL_PollEvent(&event)){
    //     window.clear();
    //     window.Background(menuTexture);
    //     window.render(intro);
    //     window.render(startButton);
    //     window.render(highScores);

    //     if (event.type == SDL_QUIT){
    //         StartTheGame = true;
    //     }
    //         // break;

    //     // if (mouse over playButton){
    //     //     StartTheGame = true;
    //     //     break;
    //     // }

    //     // if (!ViewHighScores && mouse over highScores button){
    //     //     ViewHighScores = true;
    //     //     HighScores();
    //     // }
    // }

    // if (StartTheGame){
    vector<SDL_Texture*> textures = { tileLightTexture32, tileDarkTexture32, tileLightTexture64, tileDarkTexture64, ballTexture, holeTexture, ballShadowTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG };

    Ball* ball = new Ball(pointTexture, powerMeterTexture_FG, powerMeterTexture_BG);
    PhyStriker(textures, ball, window, bg2Texture);
    cout << "Level Finished\n";
    // }

    window.cleanUp();
    SDL_Quit();
    return 0;
}