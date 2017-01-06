#ifndef GRABCAFE_H
#define GRABCAFE_H
#include <iostream>
#include <string>
#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>


class grabCafe
{
private:
  static int current_x;
  static int current_y;
  static double current_theta;

  AL::ALMotionProxy* motion;
  AL::ALRobotPostureProxy* posture;

  void aboutFace();
  void walkForward();
  void walkBack();
  void grabIt();
  void handIn();

public:
  grabCafe(std::string robotIP);
  void test();
  void action();

};

#endif // GRABCAFE_H
