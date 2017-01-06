// basic demo to show the functions of Nao people perception module
// by zzj
// 08 July, 2016

#include "human_sense.h"
#include "motion_utils.h"
#include "test.h"

#include <alproxies/altexttospeechproxy.h>
#include <alproxies/albasicawarenessproxy.h>
#include <alproxies/almotionproxy.h>
#include <alcommon/albroker.h>
#include <alcommon/almodule.h>
#include <alcommon/albrokermanager.h>
#include <boost/shared_ptr.hpp>

#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <string>

// std::string NaoIP = "192.168.1.111";
std::string NaoIP = "192.168.1.102";
// std::string NaoIP = "169.254.80.144";
//
int NaoPort = 9559;
AL::ALBasicAwarenessProxy *pBasicAwarenessProxy;
AL::ALMotionProxy *pMotionProxy;

void my_handler(int s);

int main()
{
  // ctr+c shut down
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = my_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  boost::shared_ptr<AL::ALBroker> pBroker = AL::ALBroker::createBroker("HumanSenseTest", "", 0, NaoIP, NaoPort);
  AL::ALBrokerManager::setInstance(pBroker->fBrokerManager.lock());
  AL::ALBrokerManager::getInstance()->addBroker(pBroker);

  // restart
  pBasicAwarenessProxy = new AL::ALBasicAwarenessProxy(pBroker);
  pMotionProxy = new AL::ALMotionProxy(pBroker);
  pMotionProxy->rest();
  pMotionProxy->wakeUp();

  pBasicAwarenessProxy->setEngagementMode("FullyEngaged");
  pBasicAwarenessProxy->setStimulusDetectionEnabled("Touch", false);
  pBasicAwarenessProxy->setStimulusDetectionEnabled("Sound", false);
  pBasicAwarenessProxy->setStimulusDetectionEnabled("Movement", false);
  pBasicAwarenessProxy->setStimulusDetectionEnabled("People", true);
  pBasicAwarenessProxy->startAwareness();

  //Test Module
  // AL::ALModule::createModule<TestModule>(pBroker, "TestModule");

  AL::ALModule::createModule<HumanSense>(pBroker, "HumanSense");

  while(true) sleep(1);

  return 0;
}

void my_handler(int s){
  std::cout<<"Interrupted by user, shutting down\n";
  pBasicAwarenessProxy->stopAwareness();

  delete pBasicAwarenessProxy;
  delete pMotionProxy;

  exit(1);
}
