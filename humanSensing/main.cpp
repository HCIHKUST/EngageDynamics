#include <iostream>

#include "humansense.h"
#include "newauto.h"
#include "sharedvar.h"
#include "naosensors.h"

#include "dialogModule/converter.h"
#include "dialogModule/wakeup.h"
#include "dialogModule/dialogtext.h"
#include "dialogModule/tulingmodule.h"

#include "NaoAction3/nao_action.h"
#include "NaoAction3/human_state.h"
#include "NaoAction3/motion_utils.h"
#include "NaoAction3/trim.h"

#include <boost/shared_ptr.hpp>
#include <alcommon/almodule.h>
#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>

int main(){
  boost::shared_ptr<AL::ALBroker> broker = AL::ALBroker::createBroker("broker", "", 0, ROBOT_IP, ROBOT_PORT);
  AL::ALBrokerManager::setInstance(broker->fBrokerManager.lock());
  AL::ALBrokerManager::getInstance()->addBroker(broker);

  newAuto initStart(broker);

  AL::ALModule::createModule<humanSense>(broker, "humanSense");

  humanSense* hs = new humanSense(broker, "humanSense");

  std::string scenarios[] = {"MorningReport", "MeetingArrangement", "DailySummary"};

  initStart.setPosture("Stand");

  hs->giveIntro();
  initStart.setPosture("Stand");

  qi::os::msleep(2000);
  hs->giveHint();

  while(!START_FLAG);

  initStart.setPosture("Stand");

  std::cout<<"starting..."<<std::endl;

  NaoAction* na = new NaoAction(broker, "naoact");

  na->NaoActForAScenario(scenarios[0]);

  hs->stop();
  hs->giveThanks();

  initStart.setPosture("Stand");
  return 0;
}
