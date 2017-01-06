#ifndef MOTION_UTILS_H
#define MOTION_UTILS_H

#include <alcommon/almodule.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace AL
{
  class ALBroker;
}

class MotionUtils: public AL::ALModule
{
public:
  MotionUtils(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& name);
  virtual ~MotionUtils();

  void NaoThink();
  void NaoPointToSomething(bool isInitial, bool isPost, std::string posture);
  void NaoGiveMeTheGift();
  void NaoGraspSomething(bool isInitial, bool isPost, std::string posture);
  void NaoOpenHand(bool isInitial, bool isPost, std::string posture);
  void NaoExaggerateAskSomething(bool isInitial, bool isPost, std::string posture);
  void NaoFunctionalAskSomething(bool isInitial, bool isPost, std::string posture);
  void NaoGazePointToSomething(bool isInitial, bool isPost, std::string posture);

  void NaoInitialPosture();
  void NaoCrouchPosture();

  void NaoWaveHands(bool isInitial, bool isPost, std::string posture);
private:
  // only use RArm collision protection
  void moveTemplate(
    std::vector<std::string> jointNames,
    std::vector<float> jointValues,
    std::vector<float> motionDurations,
    bool gotoInitial,
    bool isPost,
    std::string posture);

  void xMoveArm(
    const std::string& pTargetName,
    const std::string& pRobotName,
    const std::string& pChainName);
};

#endif
