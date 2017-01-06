#ifndef HUMANSENSE_H
#define HUMANSENSE_H

#include "operations.h"
#include "naosensors.h"

#include <boost/shared_ptr.hpp>
#include <alcommon/almodule.h>
#include <alproxies/altouchproxy.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alchestbuttonproxy.h>
#include <alproxies/altrackerproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/algazeanalysisproxy.h>
#include <alproxies/alfacedetectionproxy.h>
#include <alproxies/albasicawarenessproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alpeopleperceptionproxy.h>
#include <alproxies/alsittingpeopledetectionproxy.h>

#include <althread/almutex.h>
#include <ctime>

using namespace AL;

class humanSense: public ALModule
{
public:
  humanSense(boost::shared_ptr<ALBroker> broker, const std::string& name);

  virtual ~humanSense();
  virtual void init();

  void stop();
  void showEngage();
  void giveIntro();
  void giveThanks();
  void giveHint();
  bool getManualFlag();

private:
  bool manualFlag;

  ALMemoryProxy*                 memory;
  ALBasicAwarenessProxy*         aware;
  ALGazeAnalysisProxy*           gaze;
  ALPeoplePerceptionProxy*       peoplePercept;
  ALTrackerProxy*                faceTracker;
  ALFaceDetectionProxy*          faceDetect;
  ALTextToSpeechProxy*           tts;
  ALAnimatedSpeechProxy*         ani_tts;
  ALTouchProxy*                  touch;

  boost::shared_ptr<AL::ALBroker> broker;
  boost::shared_ptr<AL::ALMutex> fCallbackMutex;
  naosensors* sensors;
  operations* oprPtr;

  void startAware();
  void startGazeAnalysis();
  void startFaceTracker();
  void subscribeAll();
  void updateEngage();

  void startsLookingAtRobotFromGaze(std::string ev, int nameID, std::string id);
  void stopsLookingAtRobotFromGaze(std::string ev, int nameID, std::string id);
  void soundDetectedFromAware(std::string ev, std::string name, std::string id);
  void peopleInSight(std::string evName, ALValue data, std::string subID);
  void peopleOutOfSight(string evName, int nameID, string subID);
  void touchSwitch(string name, float val, string id);
  void setupInit(std::string name, float val, std::string id);
};

#endif // HUMANSENSE_H
