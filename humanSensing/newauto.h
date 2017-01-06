//**************************************************
// for disable the autonomous state
//**************************************************

#ifndef NEWAUTO_H
#define NEWAUTO_H

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <alproxies/alautonomouslifeproxy.h>
#include <alproxies/alrobotpostureproxy.h>

class newAuto
{
public:
  newAuto(boost::shared_ptr<AL::ALBroker> broker);

  void setPosture(const std::string name);

private:
  AL::ALAutonomousLifeProxy* autono;
  AL::ALRobotPostureProxy* posture;
};

#endif // NEWAUTO_H
