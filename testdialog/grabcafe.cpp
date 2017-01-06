#include "grabcafe.h"
#include <iostream>
#include <string>

#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>

double grabCafe::current_theta = 0;
int grabCafe::current_x = 0;
int grabCafe::current_y = 0;

grabCafe::grabCafe(std::string robotIP)
{
    motion = new AL::ALMotionProxy(robotIP);
    posture = new AL::ALRobotPostureProxy(robotIP);
}

void grabCafe::test()
{
    aboutFace();
    walkForward();
    grabIt();
    walkBack();
    handIn();
}

void grabCafe::action()
{
    aboutFace();
    walkForward();
    grabIt();
    walkBack();
}

void grabCafe::aboutFace()
{
    motion->moveInit();
    motion->moveTo(0, 0, -3.10); // x, y, theta
    current_theta += -3.10;
}

void grabCafe::walkForward()
{
    motion->moveInit();
    motion->moveTo(0.1, 0, 0); // x, y, theta
    current_x += 0.1;
}

void grabCafe::walkBack()
{
    aboutFace();
    motion->moveInit();
    motion->moveTo(current_x, current_y, current_theta); // x, y, theta
    current_x = 0;
    current_y = 0;
    motion->moveTo(0, 0, -current_theta); // x, y, theta
    current_theta = 0;
}

void grabCafe::grabIt()
{

}

void grabCafe::handIn()
{

}
