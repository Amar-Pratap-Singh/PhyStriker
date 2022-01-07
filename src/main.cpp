// Music getting stopped after completing
// After restart, make that levelStrike count as 0

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
#include <iterator>
#include <unistd.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Ball.hpp"
#include "Loader.hpp"
#include "Menu.hpp"

using namespace std;

static int level = 1;
static bool isClicked = true, restarted = false, levelLoaded = true;
static vector<Entity> blocks;
static vector<Entity> pointerAndMeters;
static int TotalStrikes = 0;
static int levelsCleared = 0;
static int TotalScore;
static map<string, int> hashmap; // Add elements at the start of game by asking user Input
string PlayerName;

void NoteDownScores()
{
    ifstream fin;
    fin.open("Scores/HighScore.txt");
    string HighScore_scoreLine;

    getline(fin, HighScore_scoreLine);
    string score = HighScore_scoreLine.substr(HighScore_scoreLine.length() - 3, 3);
    string Score_scoreLine = PlayerName + " " + to_string(TotalScore);
    fin.close();

    if (score < to_string(TotalScore))
    {
        ofstream fout("Scores/HighScore.txt");
        fout << Score_scoreLine;

        fout.close();
    }

    // add it to the Scores
    ofstream fout;
    fout.open("Scores/Scores.txt", ios::app);
    fout << PlayerName + " " + to_string(TotalScore) << "\n";
    fout.close();
}

pair<Entity, Entity> levelLoader(vector<SDL_Texture *> textures, Ball *ball, SDL_Texture *bg, RenderWindow window, TTF_Font *font)
{
    isClicked = true;
    Loader *loader = new Loader(textures);

    blocks = loader->load_tiles(level);
    if (blocks.size() == 0)
    {
        font = TTF_OpenFont("fonts/HandyRegular.ttf", 18);
        window.clear();
        window.Background(bg);
        TotalScore = 100 * levelsCleared - TotalStrikes;
        string s = "Score: " + to_string(TotalScore);
        const char *c = s.c_str();
        SDL_Surface *GameCompleted = TTF_RenderText_Solid(font, "Bravo!!", {255, 255, 0});
        SDL_Surface *YourScore = TTF_RenderText_Solid(font, c, {255, 0, 0});
        SDL_Rect rect = {220, 0, 180, 80};
        SDL_Rect rect2 = {220, 300, 180, 80};
        window.RenderText(GameCompleted, rect);
        window.RenderText(YourScore, rect2);
        window.display();

        hashmap[PlayerName] = TotalScore;
        sleep(2);

        NoteDownScores();

        Entity e(0, 0, NULL);
        Entity f(0, 0, NULL);
        return {e, f};
    }

    Entity e = blocks[blocks.size() - 1]; // ball
    // cout << e.getX() <<" " << e.getY() <<"\n";
    Entity f = blocks[blocks.size() - 2]; // hole
    // cout << f.getX() <<" " << f.getY() <<"\n\n";

    blocks.erase(blocks.end() - 1);
    blocks.erase(blocks.end() - 1);

    for (long unsigned int i = 0; i < blocks.size(); i++)
        ball->AddtoFlag({0, 0});

    return {e, f};
}

void PhyStriker(vector<SDL_Texture *> textures, Ball *ball1, RenderWindow window, SDL_Texture *bg, Button *restart, TTF_Font *font, Mix_Chunk *swing, Mix_Chunk *hole, Mix_Chunk *chill)
{
    cout << "Player Name: ";
    cin >> PlayerName;

    Mix_PlayChannel(1, chill, 0);

    // int state = 1;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    pair<Entity, Entity> BallHole = levelLoader(textures, ball1, bg, window, font);

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
    resize.w = 25;
    resize.h = 35;

    pointerAndMeters = {pm1, pm2, pm3, pm4, pm5, pm6, pm};

    for (long unsigned int z = 1; z < pointerAndMeters.size(); z++)
    {
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
        window.render(e);

        if (levelLoaded)
        {
            levelLoaded = false;
            string s = "Level " + to_string(level);
            const char *c = s.c_str();
            SDL_Surface *NewLevel = TTF_RenderText_Solid(font, c, {255, 255, 0});
            SDL_Rect rect = {220, 0, 180, 80};
            window.RenderText(NewLevel, rect);
            window.display();
            sleep(2);
        }
        bool LevelRunning = ball1->moveBall(e, f, blocks, window, level, hole, pointerAndMeters);

        // Restart condition
        if (restart->isButtonClicked(mouse))
        {
            restarted = true;
            ball1->setSpeed(0);
            ball1->setMovingState(true);
            ball1->setDroppingState(false);
            level--;
            LevelRunning = false;
        }

        if (!LevelRunning)
        {
            levelsCleared = level;
            level++;
            levelLoaded = true;
            BallHole = levelLoader(textures, ball1, bg, window, font);
            e = BallHole.first;
            f = BallHole.second;

            if (!e.getTex() && !f.getTex())
            {
                return;
            }

            if (!restarted)
            {
                SDL_Surface *Goal = TTF_RenderText_Solid(font, "GOAL!", {0, 0, 255});
                SDL_Rect rect = {220, 280, 200, 100};
                window.RenderText(Goal, rect);
                window.display();
                sleep(2);
            }

            restarted = false;
            continue;
        }
        // SDL_Event event;
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (holding)
        {
            Entity p(e.getX() + e.getCurrentFrame().w / 2, e.getY() + e.getCurrentFrame().h / 2, pointTexture);
            SDL_Point Center{0, 0};
            int Delta_x;
            int Delta_y;
            double Result;
            SDL_GetMouseState(&x, &y);
            Delta_x = e.getX() + e.getCurrentFrame().w / 2 - x;
            Delta_y = e.getY() + e.getCurrentFrame().h / 2 - y;

            Result = (atan2(Delta_y, Delta_x) * 180.0000) / 3.14159265;
            window.renderArrow(p, e, x, y, Result - 90, &Center);

            float temp = sqrt(pow(x - e.getX() - e.getCurrentFrame().w / 2, 2) + pow(y - e.getY() - e.getCurrentFrame().h / 2, 2));
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
            window.render(pointerAndMeters[index - 1]);
            window.render(pointerAndMeters[pointerAndMeters.size() - 1]);
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
                        Mix_PlayChannel(-1, swing, 0);

                        float xcoor = e.getX() + e.getCurrentFrame().w / 2;
                        float ycoor = e.getY() + e.getCurrentFrame().h / 2;
                        SDL_GetMouseState(&x, &y);

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
                        holding = 0;
                    }
                }

                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x, y;
                    // Uint32 buttons;
                    SDL_GetMouseState(&x, &y);

                    float xcoor = e.getX();
                    float ycoor = e.getY();

                    SDL_Rect currFrame = e.getCurrentFrame();

                    // Do it for left click only
                    if (xcoor - currFrame.w <= x && xcoor + currFrame.w >= x && ycoor - currFrame.h <= y && ycoor + currFrame.h >= y)
                    {
                        TotalStrikes++;
                        holding = 1;
                        isClicked = false;
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

bool cmp(pair<string, int> &a, pair<string, int> &b)
{
    return a.second < b.second;
}

bool HighScores(RenderWindow window, SDL_Texture *bg, TTF_Font *font)
{
    bool viewHighScore = true;
    Button *back = new Button(0, 0, 50, 50, "images/back.png");
    MouseInput *mouse = new MouseInput();
    SDL_Event event;

    string k;
    ifstream fin;
    fin.open("Scores/HighScore.txt");
    if (fin.is_open())
    {
        getline(fin, k);
    }
    fin.close();

    const char *c = k.c_str();
    while (viewHighScore)
    {
        if (back->isButtonClicked(mouse))
        {
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
        window.Background(bg);

        SDL_Surface *ScoreText = TTF_RenderText_Solid(font, c, {0, 0, 255});
        SDL_Rect rect = {220, 280, 200, 100};
        window.RenderText(ScoreText, rect);
        back->DrawButton(&window);
        window.display();
    }

    return true;
}

void MainMenu(RenderWindow window, vector<SDL_Texture *> textures, SDL_Texture *bg, TTF_Font *font, Mix_Chunk *swing, Mix_Chunk *hole, Mix_Chunk *chill)
{
    Menu *menu = new Menu(&window);
    TTF_Font *font2 = TTF_OpenFont("fonts/HandyRegular.ttf", 21);
    menu->MenuLoop(font2);
    if (menu->getWindowType() == "Exit" || menu->getWindowType() == "Main_Menu")
    {
        return;
    }

    else if (menu->getWindowType() == "Scores")
    {        
        TTF_Font *font2 = TTF_OpenFont("fonts/Regular.ttf", 40);
        if (!font)
        {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
        }

        bool next = HighScores(window, bg, font2);
        if (!next)
        {
            return;
        }

        else
        {
            MainMenu(window, textures, bg, font, swing, hole, chill);
        }
    }

    else if (menu->getWindowType() == "Game")
    {
        Button *restart = new Button(0, 0, 50, 50, "images/Restart2.png");
        SDL_Texture* bg2 = window.loadTexture("images/bg.png");
        Ball *ball = new Ball();
        PhyStriker(textures, ball, window, bg2, restart, font, swing, hole, chill);
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

    if (TTF_Init() == -1)
    {
        cout << "SDL2_ttf failure." << TTF_GetError() << endl;
    }

    TTF_Font *font = TTF_OpenFont("fonts/Regular.ttf", 40);
    if (!font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    RenderWindow window("PhyStriker", 670, 700);

    SDL_Texture *ballTexture = window.loadTexture("images/ball.png");
    SDL_Texture *holeTexture = window.loadTexture("images/hole.png");
    SDL_Texture *bg2Texture = window.loadTexture("images/1232.png");
    SDL_Texture *tileDarkTexture32 = window.loadTexture("images/tile32_dark.png");
    SDL_Texture *tileDarkTexture64 = window.loadTexture("images/tile64_dark.png");
    SDL_Texture *tileLightTexture32 = window.loadTexture("images/tile32_light.png");
    SDL_Texture *tileLightTexture64 = window.loadTexture("images/tile64_light.png");
    SDL_Texture *ballShadowTexture = window.loadTexture("images/ball_shadow.png");

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Chunk *swing = Mix_LoadWAV("sfx/swing.mp3");
    Mix_Chunk *hole = Mix_LoadWAV("sfx/hole.mp3");
    Mix_Chunk *chill = Mix_LoadWAV("sfx/chill.mp3");

    vector<SDL_Texture *> textures = {tileLightTexture32, tileDarkTexture32, tileLightTexture64, tileDarkTexture64, ballTexture, holeTexture, ballShadowTexture};

    MainMenu(window, textures, bg2Texture, font, swing, hole, chill);

    window.cleanUp();
    TTF_CloseFont(font);
    SDL_Quit();
    return 0;
}
