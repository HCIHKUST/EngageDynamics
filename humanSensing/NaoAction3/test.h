#ifndef TEST_H
#define TEST_H

#include "motion_utils.h"

#include <alcommon/albroker.h>
#include <alcommon/almodule.h>
#include <alcommon/albrokermanager.h>
#include <alcommon/almodule.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/alfacecharacteristicsproxy.h>
#include <alproxies/alspeechrecognitionproxy.h>
#include <alproxies/alsounddetectionproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/almotionproxy.h>
#include <qi/os.hpp>
#include <almath/types/alpose2d.h>
#include <almath/tools/aldubinscurve.h>
#include <almath/tools/almathio.h>
#include <almath/tools/almath.h>
#include <almath/tools/altrigonometry.h>
#include <althread/almutex.h>
#include <althread/alcriticalsection.h>
#include <boost/shared_ptr.hpp>
#include <qi/application.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <alcommon/almodule.h>
#include <string>
#include <alproxies/altexttospeechproxy.h>
#include "alaudio/alsoundextractor.h"
#include <alproxies/albasicawarenessproxy.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

namespace AL
{
  class ALBroker;
}

class TestModule: public AL::ALModule
{
public:
  TestModule(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& name);
  virtual ~TestModule();
  virtual void init();

private:
  AL::ALTextToSpeechProxy textToSpeechProxy;
  MotionUtils motionUtilsProxy;
};

#endif
