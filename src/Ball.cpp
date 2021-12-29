#include "Ball.hpp"

float Ball::xdir = 1;
float Ball::ydir = 1;
float Ball::speed = 0;
bool Ball::moving = true;
bool Ball::dropping = false;
vector<pair<bool, bool>>  Ball::flags;

Ball::Ball()
{}

//************************* Getters and Setters **********************************
void Ball::AddtoFlag(pair<bool, bool> val)
{
    flags.push_back(val);
}

bool Ball::getMovingState()
{
    return moving;
}

bool Ball::getDroppingState()
{
    return dropping;
}

void Ball::setMovingState(bool state)
{
    moving = state;
}

void Ball::setDroppingState(bool state)
{
    dropping = state;
}

pair<float, float> Ball::getBallDir()
{
    return {xdir, ydir};
}

void Ball::setXdir(float newDir)
{
    xdir = newDir;
}

void Ball::setYdir(float newDir)
{
    ydir = newDir;
}

float Ball::getSpeed()
{
    return speed;
}

void Ball::setSpeed(float s)
{
    speed = s;
}

// ************************************************************************************

void Ball::rebound(Entity &e, int w, int h)
{
    float xcoor = e.getX();
    float ycoor = e.getY();

    if (ycoor < 0 || ycoor + e.getCurrentFrame().h > h)
    {
        ydir = -1 * ydir;
    }

    else if (xcoor < 0 || xcoor + e.getCurrentFrame().w > w/2)
    {
        xdir = -1 * xdir;
    }
    // speed -= 0.5;
}

bool Ball::droppingBall(Entity &e, Entity &f, RenderWindow &window, int level)
{
    e.setX(f.getX() + e.getCurrentFrame().w);
    e.setY(f.getY() + e.getCurrentFrame().h);

    // Stop the ball
    xdir = 0;
    ydir = 0;

    // Decrease the size of ball
    SDL_Rect a;
    a = e.getCurrentFrame();

    // while (a.h || a.w){
    a.h -= 0.1;
    a.w -= 0.2;

    if (a.h <= 0.0001 && a.w <= 0.0001)
    {
        flags.clear();
        return false;
        // print Ball In The Hole 
        // Display score
        // Next level
        
    }

    e.setCurrFrame(a);
    return true;
}

pair<bool, bool> Ball::Collision(Entity &e, Entity &b, bool flagX, bool flagY)
{

    float xcoor = e.getX();
    float ycoor = e.getY();

    if (!flagX && ycoor + e.getCurrentFrame().h >= b.getY() && ycoor - e.getCurrentFrame().h <= b.getY() + b.getCurrentFrame().h)
    {
        flagY = 1;
        // Collision from left and right
        if (xcoor + e.getCurrentFrame().w >= b.getX() && xcoor <= b.getX() + b.getCurrentFrame().w)
        {
            xdir *= -1;
            // speed -= 0.5;
        }
    }

    else if (!flagY && xcoor + e.getCurrentFrame().w >= b.getX() && xcoor - e.getCurrentFrame().w <= b.getX() + b.getCurrentFrame().w)
    {
        flagX = 1;
        // Collision from below and above
        if (ycoor + e.getCurrentFrame().h >= b.getY() && ycoor <= b.getY() + b.getCurrentFrame().h)
        {
            ydir *= -1;
            // speed -= 0.5;
        }
    }

    else
    {
        // speed -= 0.01;
        flagX = 0;
        flagY = 0;
    }

    return {flagX, flagY};
}

bool Ball::moveBall(Entity &e, Entity &f, vector<Entity> &b, RenderWindow &window, int level)
{
    if (!speed)
        window.render(e);

    else
    {
        float xcoor = e.getX();
        float ycoor = e.getY();

        float x = xcoor + e.getCurrentFrame().w / 2;
        float y = ycoor + e.getCurrentFrame().h / 2;

        if (dropping)
        {
            bool running = droppingBall(e, f, window, level);
            window.render(e);
            return running;
        }

        if (x >= f.getX() + f.getCurrentFrame().w / 4 && x <= f.getX() + 3 * f.getCurrentFrame().w / 4 && y >= f.getY() + f.getCurrentFrame().h / 4 && y <= f.getY() + 3 * f.getCurrentFrame().h / 4)
        {
            // window.render(e);
            dropping = true;
            SDL_Rect k;
            k = e.getCurrentFrame();
            k.h /= 2;
            k.w /= 2;
            bool running = droppingBall(e, f, window, level);
            window.render(e);
            return running;
        }

        // rebound condition
        if ((xcoor + e.getCurrentFrame().w > window.w()/2 || xcoor < 0) || (ycoor + e.getCurrentFrame().h > window.h() || ycoor < 0))
        {
            rebound(e, window.w(), window.h());
        }

        SDL_Rect firstObj = e.getCurrentFrame();

        int i = 0;
        for (Entity entities : b)
        {
            SDL_Rect secondObj = entities.getCurrentFrame();

            if (SDL_HasIntersection(&firstObj, &secondObj))
            {
                // cout << flags[i].first << " " << flags[i].second << "\n";
                flags[i] = Collision(e, entities, flags[i].first, flags[i].second);
                i++;
            }

            // can also decrease the speed here
            if (speed < 0)
            {
                moving = true;
            }
            else
            {
                e.setX(xcoor + (xdir * speed) / 100);
                e.setY(ycoor + (ydir * speed) / 100);
            }

            // if (xdir && ydir)
            window.render(e);
            speed -= 0.01;
        }

        // collision condition
        // cout << xcoor << "\t" << ycoor << "\n";
    }

    return true;
}
