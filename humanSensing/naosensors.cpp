#include "naosensors.h"

#include "sharedvar.h"

#include <qi/log.hpp>

naosensors::naosensors(boost::shared_ptr<AL::ALBroker> broker)
{
    leds = new AL::ALLedsProxy(broker);
}

void naosensors::blinkEye()
{
  int temp = std::rand();

  if( temp%19 == 0 ){
      leds->post.off("FaceLeds");
      qi::os::msleep(80);
      leds->post.on("FaceLeds");
    }
}

void naosensors::hintEye()
{
  leds->post.off("FaceLeds");
  qi::os::msleep(100);
  leds->post.on("FaceLeds");
}


void naosensors::blinkEar()
{
  int fre = 4 - (LOOKING_OR_NOT*2 + FEEDBACK_OR_NOT);
  leds->post.fade("EarLeds", 0.0f, fre);
  leds->post.fade("EarLeds", 1.0f, fre);
  leds->post.fade("EarLeds", 0.0f, fre);
}

void naosensors::turnOffLeds()
{
  leds->post.off("BrainLeds");
  leds->post.off("ChestLeds");
  leds->post.off("FeetLeds");
}

void naosensors::chestLight(bool red, bool green, bool blue)
{
  red    ? leds->post.on("ChestLedsRed")   : leds->post.off("ChestLedsRed");
  green  ? leds->post.on("ChestLedsGreen") : leds->post.off("ChestLedsGreen");
  blue   ? leds->post.on("ChestLedsBlue")  : leds->post.off("ChestLedsBlue");
}
