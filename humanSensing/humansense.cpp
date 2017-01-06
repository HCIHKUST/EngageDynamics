#include "humansense.h"

#include "operations.h"
#include "sharedvar.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <qi/log.hpp>
#include <alcommon/almodule.h>
#include <boost/shared_ptr.hpp>
#include <alproxies/albasicawarenessproxy.h>

#include <althread/alcriticalsection.h>


using namespace AL;

humanSense::humanSense(boost::shared_ptr<ALBroker> broker, const string &name)
  :ALModule(broker, name)
  ,fCallbackMutex(AL::ALMutex::createALMutex())
{
  this->broker = broker;
  manualFlag = false;

  this->setModuleDescription("");

  this->functionName("stop", this->getName(), "");
  BIND_METHOD(humanSense::stop);

  this->functionName("showEngage", this->getName(), "");
  setReturn("boolean", "boolean");
  BIND_METHOD(humanSense::showEngage);

  this->functionName("startsLookingAtRobotFromGaze", this->getName(), "");
  BIND_METHOD(humanSense::startsLookingAtRobotFromGaze);

  this->functionName("stopsLookingAtRobotFromGaze", this->getName(), "");
  BIND_METHOD(humanSense::stopsLookingAtRobotFromGaze);

  this->functionName("peopleInSight", this->getName(), "");
  BIND_METHOD(humanSense::peopleInSight);

  this->functionName("peopleOutOfSight", this->getName(), "");
  BIND_METHOD(humanSense::peopleOutOfSight);

  this->functionName("soundDetectedFromAware", this->getName(), "");
  BIND_METHOD(humanSense::soundDetectedFromAware);

  this->functionName("touchSwitch", this->getName(), "");
  BIND_METHOD(humanSense::touchSwitch);

  this->functionName("setupInit", this->getName(), "");
  BIND_METHOD(humanSense::setupInit);

  this->functionName("getManualFlag", this->getName(), "");
  setReturn("boolean", "boolean");
  BIND_METHOD(humanSense::getManualFlag);

}

void humanSense::init(){
  oprPtr  = new operations(this->broker);
  tts     = new ALTextToSpeechProxy(this->broker);
  sensors = new naosensors(this->broker);
  touch   = new ALTouchProxy(broker);

  startAware();
  startGazeAnalysis();
  // sensors->startTouch();
  // startFaceTracker();

  subscribeAll();
}

humanSense::~humanSense()
{
  memory->unsubscribeToEvent("GazeAnalysis/PersonStartsLookingAtRobot", getName());
  memory->unsubscribeToEvent("GazeAnalysis/PersonStopsLookingAtRobot",  getName());
  memory->unsubscribeToEvent("PeoplePerception/PeopleDetected", getName());
  memory->unsubscribeToEvent("FrontTactilTouched", getName());
  memory->unsubscribeToEvent("MiddleTactilTouched", getName());
  memory->unsubscribeToEvent("RearTactilTouched", getName());
  memory->unsubscribeToEvent("HandRightBackTouched", getName());
  memory->unsubscribeToEvent("HandLeftBackTouched", getName());
  // memory->unsubscribeToEvent("ChestButtonPressed", getName());
}

void humanSense::showEngage()
{
  sensors->blinkEar();
}

void humanSense::giveIntro()
{
  ani_tts = new ALAnimatedSpeechProxy(this->broker);
  ani_tts->say("Hello, I am HCI Nao robot.");
  ani_tts->say("Thanks for taking this experiment.");
  ani_tts->say("I will be your personal assistant in this experiment.");
  ani_tts->say("Talk and help you!");
  ani_tts->say("OK! Relax, and let's begin");
//  ani_tts->say("Hello, Welcome to join our experiment.");
//  ani_tts->say("In this experiment, I will speak to you all the time.");
//  ani_tts->say("During the talking, you are supposed to finish a questionair online.");
//  ani_tts->say("The questionair will pop up in the laptop at some time.");
//  ani_tts->say("When you are doing the questionair, I will continue talking with you.");
//  ani_tts->say("You can look at me or nod your head to show you are listening to me.");
//  ani_tts->say("You can also focus on doing the questionair with giving me any feedbacks.");
//  ani_tts->say("I will speak to you all the time.");
//  ani_tts->say("Please touch the blue part in my hands to start the experiment.");
}

void humanSense::giveThanks()
{
  ani_tts = new ALAnimatedSpeechProxy(this->broker);

  ani_tts->say("The experiment is over!");
  ani_tts->say("Thank you!");
  ani_tts->say("Have a nice day!");
}

void humanSense::giveHint()
{
  tts = new ALTextToSpeechProxy(this->broker);
  tts->say("Please touch the blue part in my hands to start the experiment.");
}


bool humanSense::getManualFlag()
{
  return manualFlag;
}

void humanSense::stop()
{
  aware = new ALBasicAwarenessProxy(this->broker);
  aware->stopAwareness();
}

void humanSense::startAware()
{
  aware = new ALBasicAwarenessProxy(this->broker);
  peoplePercept = new ALPeoplePerceptionProxy(this->broker);

  peoplePercept->resetPopulation();
  peoplePercept->setMaximumDetectionRange(2.0);
  peoplePercept->setFaceDetectionEnabled(true);
  peoplePercept->setFastModeEnabled(true);
  peoplePercept->setGraphicalDisplayEnabled(false);
  peoplePercept->setTimeBeforePersonDisappears(4);
  peoplePercept->setTimeBeforeVisiblePersonDisappears(2);

  aware->setEngagementMode("FullyEngaged");
  aware->setTrackingMode("WholeBody");

  aware->setStimulusDetectionEnabled("People", true);
  aware->setStimulusDetectionEnabled("Sound", false);
  aware->setStimulusDetectionEnabled("Movement", false);
  aware->setStimulusDetectionEnabled("Touch", false);

  aware->setParameter("LookStimulusSpeed", 0.1f);

  aware->startAwareness();

  sensors->turnOffLeds();
}

void humanSense::startGazeAnalysis()
{
  gaze = new ALGazeAnalysisProxy(this->broker);
  gaze->setFaceAnalysisEnabled(true);
  gaze->setTolerance(0.4);
}

void humanSense::startFaceTracker()
{
  faceTracker = new ALTrackerProxy(this->broker);

  faceTracker->setMode("Head");

  std::string target = "Face";
  faceTracker->registerTarget(target, 0.1); // width of face (meter)
  faceTracker->track(target);
}

void humanSense::subscribeAll()
{
  memory  = new ALMemoryProxy(this->broker);

  memory->subscribeToEvent("FrontTactilTouched", getName(), "touchSwitch");
  memory->subscribeToEvent("MiddleTactilTouched", getName(), "touchSwitch");
  memory->subscribeToEvent("RearTactilTouched", getName(), "touchSwitch");
  memory->subscribeToEvent("HandRightBackTouched", getName(), "setupInit");
  memory->subscribeToEvent("HandLeftBackTouched", getName(), "setupInit");
  memory->subscribeToEvent("GazeAnalysis/PersonStartsLookingAtRobot", getName(), "startsLookingAtRobotFromGaze");
  memory->subscribeToEvent("GazeAnalysis/PersonStopsLookingAtRobot",  getName(), "stopsLookingAtRobotFromGaze");
  memory->subscribeToEvent("PeoplePerception/PeopleDetected", getName(), "peopleInSight");
  memory->subscribeToEvent("PeoplePerception/JustLeft", getName(), "peopleOutOfSight");
  memory->subscribeToEvent("ALBasicAwareness/StimulusDetected", getName(), "soundDetectedFromAware");

  // memory->subscribeToEvent("ChestButtonPressed", getName(), "setupInit");
}

void humanSense::updateEngage()
{
  if(LOOKING_OR_NOT){
    CURR_STATE = F_ENGAGE;
  }
  else{
      if(FEEDBACK_OR_NOT){
        CURR_STATE = Q_ENGAGE;
      }
      else{
        std::clock_t  temp = clock();
        if( (temp - LAST_FEEDBACK_TIMEPOINT)/(1.0*CLOCKS_PER_SEC) > 0.1){
            CURR_STATE = DISENGAGE;
        }
        else{
            CURR_STATE = P_DISENGAGE;
            LAST_FEEDBACK_TIMEPOINT = temp;
        }
      }
  }
}

void humanSense::startsLookingAtRobotFromGaze(string ev, int nameID, string id)
{
  AL::ALCriticalSection section(fCallbackMutex);
  aware->setStimulusDetectionEnabled("Sound", false);

  qiLogInfo("Looking at me")<<std::endl;
  LOOKING_OR_NOT = true;
  LAST_FEEDBACK_TIMEPOINT = clock();
  updateEngage();
  CURR_VALID_NUM = 0;
  CURR_HUMAN_ID = nameID;
  sensors->hintEye();
}

void humanSense::stopsLookingAtRobotFromGaze(string ev, int humanID, string id)
{
  AL::ALCriticalSection section(fCallbackMutex);
  aware->setStimulusDetectionEnabled("Sound", true);

  qiLogInfo("Stop looking at me")<<std::endl;
  LOOKING_OR_NOT = false;
  updateEngage();
  oprPtr->copyHumanDetectionInfo(humanID, &HUMAN_DETECTION_INFO);
}

void humanSense::soundDetectedFromAware(string ev, string name, string id)
{
  AL::ALCriticalSection section(fCallbackMutex);

  if(name == "Sound"){
      qiLogInfo("Sound detected")<<std::endl;
      FEEDBACK_OR_NOT = true;
      LAST_FEEDBACK_TIMEPOINT = clock();
  }
  else{
      FEEDBACK_OR_NOT = false;
  }
  updateEngage();
}

void humanSense::peopleInSight(string evName, ALValue data, string subID)
{
  qiLogInfo("People in sight")<<std::endl;
  qiLogInfo("Current state")<<CURR_STATE;
  sensors->blinkEye();

  DATA_IN_SIGHT = data[1][0];
  oprPtr->copyPersonInfo(DATA_IN_SIGHT, &HUMAN_DYNAMICS[CURR_POS_INDEX]);
  if(FEEDBACK_OR_NOT && (clock() - LAST_FEEDBACK_TIMEPOINT)/(1.0*CLOCKS_PER_SEC) <= 0.02){
      qiLogInfo("time lapse")<< ((clock() - LAST_FEEDBACK_TIMEPOINT)/(1.0*CLOCKS_PER_SEC))<<std::endl;
      return;
  }
  if(CURR_VALID_NUM >= WINDOW_SIZE && (oprPtr->detecHeadPitch())){
      qiLogInfo("Feedback yes")<<std::endl;
      FEEDBACK_OR_NOT = true;
      CURR_VALID_NUM = 0;
      LAST_FEEDBACK_TIMEPOINT = clock();
  }
  else{
      qiLogInfo("Feedback no")<<std::endl;
      FEEDBACK_OR_NOT = false;
  }
  updateEngage();
}

void humanSense::peopleOutOfSight(string evName, int nameID, string subID)
{
  CURR_STATE = INIT;
}

void humanSense::touchSwitch(string name, float val, string id)
{
  AL::ALCriticalSection section(fCallbackMutex);


  if(name == "FrontTactilTouched" && val == 1.0f){
      tts->post.say("implicit strategy");
      CURR_STRATEGY = IMP;
      sensors->chestLight(1, 0, 0);
      return;
  }
  if(name == "MiddleTactilTouched" && val == 1.0f){
      tts->post.say("explicit strategy");
      CURR_STRATEGY = EXP;
      sensors->chestLight(0, 1, 0);
      return;
  }
  if(name == "RearTactilTouched" && val == 1.0f){
      tts->post.say("unaware strategy");
      CURR_STRATEGY = UNA;
      sensors->chestLight(0, 0, 1);
      return;
  }

//  memory->subscribeToEvent("FrontTactilTouched", getName(), "touchSwitch");
//  memory->subscribeToEvent("MiddleTactilTouched", getName(), "touchSwitch");
//  memory->subscribeToEvent("RearTactilTouched", getName(), "touchSwitch");
}

void humanSense::setupInit(string name, float val, string id)
{
  AL::ALCriticalSection section(fCallbackMutex);

  if( (name == "HandRightBackTouched" || name == "HandLeftBackTouched") && val == 1.0f){
      qiLogInfo("Hand touched")<<std::endl;
      START_FLAG = true;
      memory->unsubscribeToEvent("HandRightBackTouched", getName());
      memory->unsubscribeToEvent("HandLeftBackTouched", getName());

      memory->unsubscribeToEvent("FrontTactilTouched", getName());
      memory->unsubscribeToEvent("MiddleTactilTouched", getName());
      memory->unsubscribeToEvent("RearTactilTouched", getName());

      return;
  }
}
