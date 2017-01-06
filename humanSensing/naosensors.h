#ifndef NAOSENSORS_H
#define NAOSENSORS_H

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <alcommon/almodule.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/alledsproxy.h>
#include <alproxies/alchestbuttonproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/alfsrproxy.h>     // Force Sensitive Resistors(FSRs), Event List: footContactChanged()
#include <alproxies/altouchproxy.h>   // Bumper + Tactil + Hand

using namespace AL;

class naosensors
{
public:
  naosensors(boost::shared_ptr<AL::ALBroker> broker);

  void blinkEye();
  void hintEye();
  void blinkEar();
  void turnOffLeds();
  void chestLight(bool red, bool green, bool blue);

private:
  AL::ALLedsProxy* leds;
};

#endif // NAOSENSORS_H
