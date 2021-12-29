#pragma once

#include <iostream>
#include <vector>
#include "Entity.hpp"
#include "RenderWindow.hpp"

using namespace std;

class Ball
{
private:
    static float xdir;
    static float ydir;
    static float speed;
    static bool moving;
    static bool dropping;
    static vector<pair<bool, bool>> flags;

public:
    Ball();
    bool droppingBall(Entity &e, Entity &f, RenderWindow &window, int level);
    // Collision with walls
    void rebound(Entity &e, int w, int h);
    // Collision with obstacles
    pair<bool, bool> Collision(Entity &e, Entity &b, bool flagX, bool flagY);
    bool moveBall(Entity &e, Entity &f, vector<Entity> &b, RenderWindow &window, int level);
    void AddtoFlag(pair<bool, bool> flag);

    // Getters and Setters
    bool getMovingState();
    bool getDroppingState();
    void setMovingState(bool state);
    void setDroppingState(bool state);
    pair<float, float> getBallDir();
    void setXdir(float dir);
    void setYdir(float dir);
    float getSpeed();
    void setSpeed(float newSpeed);
};
