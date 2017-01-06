#ifndef HUMAN_SENSE_H
#define HUMAN_SENSE_H

#include "motion_utils.h"
#include "human_state.h"

#include <alcommon/albroker.h>
#include <alvalue/alvalue.h>
#include <qi/log.hpp>
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

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <time.h>
#include <stdlib.h>

namespace AL
{
  class ALBroker;
}

class NaoAction: public AL::ALModule
{
public:
  NaoAction(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& name);
  virtual ~NaoAction();
  virtual void init();

  void NaoActForAScenario(std::string scenario);

private:
  void speaking(std::string arg);

  void ActionMorningReport();
  void ActionMeetingArrangement();
  void ActionDailySummary();

  void engagementBasedAction(std::string keywords);
  void response(HumanState hState, std::string keywords);
  void responseImplicit(HumanState hState, std::string keywords);
  void setbackVoice();

  float volume;
  float pitchShift;
  float doubleVoice;
  float doubleVoiceLevel;
  float doubleVoiceTimeShift;

  void explicitExpress(std::string keywords, HumanState humanState);
  void implicitExpress(std::string keywords, HumanState humanState);
  void unawareExpress(std::string keywords, HumanState humanState);

  AL::ALMemoryProxy memoryProxy;

  AL::ALMotionProxy motionProxy;
  AL::ALRobotPostureProxy postureProxy;
  MotionUtils motionUtilsProxy;

  AL::ALTextToSpeechProxy tts;
  AL::ALAnimatedSpeechProxy animatedSpeechProxy;
};
#endif
