#include "motion_utils.h"

#include <alvalue/alvalue.h>
#include <alcommon/albroker.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/almotionproxy.h>
#include <qi/os.hpp>
#include <almath/types/alpose2d.h>
#include <almath/tools/aldubinscurve.h>
#include <almath/tools/almathio.h>
#include <almath/tools/almath.h>
#include <almath/tools/altrigonometry.h>

#include <iostream>

MotionUtils::MotionUtils(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& name):
AL::ALModule(pBroker, name)
{
  setModuleDescription("Give joint parameters to make Nao move.");
}

MotionUtils::~MotionUtils() {}

void MotionUtils::NaoWaveHands(bool isInitial, bool isPost, std::string posture)
{
  std::vector<std::string> jointNames;
  jointNames.push_back("RShoulderPitch");
//  jointNames.push_back("RShoulderRoll");
  jointNames.push_back("RHand");
//  jointNames.push_back("RElbowRoll");
//  jointNames.push_back("RElbowRoll");
//  jointNames.push_back("RElbowRoll");
//  jointNames.push_back("RElbowRoll");

  std::vector<float> jointValues;
  jointValues.push_back(-0.5f);
//  jointValues.push_back(0.2f);
  jointValues.push_back(1.0f);
//  jointValues.push_back(0.5f);
//  jointValues.push_back(-0.5f);
//  jointValues.push_back(0.5f);
//  jointValues.push_back(-0.5f);

  std::vector<float> motionDurations;
  motionDurations.push_back(1.0f);
//  motionDurations.push_back(2.0f);
  motionDurations.push_back(1.0f);
//  motionDurations.push_back(1.0f);
//  motionDurations.push_back(1.0f);
//  motionDurations.push_back(1.0f);
//  motionDurations.push_back(1.0f);

  moveTemplate(jointNames, jointValues, motionDurations, isInitial, isPost, posture);
}

void MotionUtils::NaoThink()
{
  boost::shared_ptr<AL::ALMotionProxy> motionProxy = getParentBroker()->getMotionProxy();
  boost::shared_ptr<AL::ALRobotPostureProxy> postureProxy =
      getParentBroker()->getSpecialisedProxy<AL::ALRobotPostureProxy>("ALRobotPosture");

  std::string pChainName = "RArm";

  postureProxy->goToPosture("Stand", 1.0f);

  AL::ALValue robotConfig = motionProxy->getRobotConfig();
  std::string pRobotName = (std::string) robotConfig[1][0];

  bool pEnable = true;
  bool success = motionProxy->setCollisionProtectionEnabled(pChainName, pEnable);
  if (!success)
  {
    std::cerr << "Failed to ensable collision protection" << std::endl;
  }

  std::string pTargetName = "Head";
  xMoveArm(pTargetName, pRobotName, pChainName);
}

void MotionUtils::NaoPointToSomething(bool isInitial, bool isPost, std::string posture)
{
  std::vector<std::string> jointNames;
  jointNames.push_back("RShoulderPitch");
  jointNames.push_back("RHand");

  std::vector<float> jointValues;
  jointValues.push_back(0.5f);
  jointValues.push_back(1.0f);

  std::vector<float> motionDurations;
  motionDurations.push_back(1.0f);
  motionDurations.push_back(2.0f);

  moveTemplate(jointNames, jointValues, motionDurations, isInitial, isPost, posture);
}

void MotionUtils::NaoGiveMeTheGift()
{
  std::vector<std::string> jointNames;
  jointNames.push_back("RShoulderPitch");
  jointNames.push_back("RWristYaw");
  jointNames.push_back("RHand");

  std::vector<float> jointValues;
  jointValues.push_back(0.5f);
  jointValues.push_back(2.0f);
  jointValues.push_back(1.0f);

  std::vector<float> motionDurations;
  motionDurations.push_back(1.0f);
  motionDurations.push_back(1.0f);
  motionDurations.push_back(2.0f);

  moveTemplate(jointNames, jointValues, motionDurations, true, true, "Stand");
}

void MotionUtils::NaoGraspSomething(bool isInitial, bool isPost, std::string posture)
{
  std::vector<std::string> jointNames;
  jointNames.push_back("RHand");

  std::vector<float> jointValues;
  jointValues.push_back(0.0f);

  std::vector<float> motionDurations;
  motionDurations.push_back(2.0f);

  moveTemplate(jointNames, jointValues, motionDurations, isInitial, isPost, posture);
}

void MotionUtils::NaoExaggerateAskSomething(bool isInitial, bool isPost, std::string posture)
{
  std::vector<std::string> jointNames;
  jointNames.push_back("RShoulderRoll");
  jointNames.push_back("RShoulderPitch");
  jointNames.push_back("RElbowRoll");
  jointNames.push_back("RElbowYaw");
  jointNames.push_back("RWristYaw");
  // jointNames.push_back("RHand");

  std::vector<float> jointValues;
  jointValues.push_back(-0.5f);
  jointValues.push_back(1.0f);
  jointValues.push_back(1.0f);
  jointValues.push_back(1.0f);
  jointValues.push_back(2.0f);
  // jointValues.push_back(1.0f);

  std::vector<float> motionDurations;
  motionDurations.push_back(1.0f);
  motionDurations.push_back(1.0f);
  motionDurations.push_back(1.0f);
  motionDurations.push_back(1.0f);
  motionDurations.push_back(1.0f);
  // motionDurations.push_back(3.0f);

  moveTemplate(jointNames, jointValues, motionDurations, isInitial, isPost, posture);
}

void MotionUtils::NaoFunctionalAskSomething(bool isInitial, bool isPost, std::string posture)
{
  std::vector<std::string> jointNames;
  jointNames.push_back("RShoulderPitch");
  jointNames.push_back("RWristYaw");
  jointNames.push_back("RHand");

  std::vector<float> jointValues;
  jointValues.push_back(0.0f);
  jointValues.push_back(1.5f);
  jointValues.push_back(1.0f);

  std::vector<float> motionDurations;
  motionDurations.push_back(1.0f);
  motionDurations.push_back(1.0f);
  motionDurations.push_back(4.0f);

  moveTemplate(jointNames, jointValues, motionDurations, isInitial, isPost, posture);
}

void MotionUtils::NaoGazePointToSomething(bool isInitial, bool isPost, std::string posture)
{
  std::vector<std::string> jointNames;
  jointNames.push_back("HeadYaw");
  jointNames.push_back("HeadPitch");

  std::vector<float> jointValues;
  jointValues.push_back(-0.4f);
  jointValues.push_back(0.2f);

  std::vector<float> motionDurations;
  motionDurations.push_back(1.0f);
  motionDurations.push_back(1.0f);

  moveTemplate(jointNames, jointValues, motionDurations, isInitial, isPost, posture);
}

void MotionUtils::NaoOpenHand(bool isInitial, bool isPost, std::string posture)
{
  std::vector<std::string> jointNames;
  jointNames.push_back("RHand");

  std::vector<float> jointValues;
  jointValues.push_back(1.0f);

  std::vector<float> motionDurations;
  motionDurations.push_back(1.0f);

  moveTemplate(jointNames, jointValues, motionDurations, isInitial, isPost, posture);
}

void MotionUtils::NaoInitialPosture()
{
  boost::shared_ptr<AL::ALRobotPostureProxy> postureProxy =
      getParentBroker()->getSpecialisedProxy<AL::ALRobotPostureProxy>("ALRobotPosture");

  postureProxy->goToPosture("Stand", 0.5f);
}

void MotionUtils::NaoCrouchPosture()
{
  boost::shared_ptr<AL::ALRobotPostureProxy> postureProxy =
      getParentBroker()->getSpecialisedProxy<AL::ALRobotPostureProxy>("ALRobotPosture");

  postureProxy->goToPosture("Crouch", 0.5f);
}

void MotionUtils::moveTemplate(
  std::vector<std::string> jointNames,
  std::vector<float> jointValues,
  std::vector<float> motionDurations,
  bool gotoInitial,
  bool isPost,
  std::string posture)
{
  // std::cerr<<"Run into\n";
  boost::shared_ptr<AL::ALMotionProxy> motionProxy = getParentBroker()->getMotionProxy();
  boost::shared_ptr<AL::ALRobotPostureProxy> postureProxy =
      getParentBroker()->getSpecialisedProxy<AL::ALRobotPostureProxy>("ALRobotPosture");

  // go to initial posture
  if(gotoInitial==true)
    postureProxy->goToPosture(posture.c_str(), 0.5f);

  // set collision protection
  std::string pChainName = "RArm";
  std::string pTargetName = "Torso";

  AL::ALValue robotConfig = motionProxy->getRobotConfig();
  std::string pRobotName = (std::string) robotConfig[1][0];
  bool pEnable = true;
  bool success = motionProxy->setCollisionProtectionEnabled(pChainName, pEnable);
  if (!success)
  {
    std::cerr << "Failed to ensable collision protection" << std::endl;
  }

  // set joint values
  int N = jointNames.size();
  std::cout<<N<<std::endl;

  AL::ALValue names;
  names.clear();
  names.arraySetSize(N);

  AL::ALValue angleLists;
  angleLists.clear();
  angleLists.arraySetSize(N);

  AL::ALValue timeLists;
  timeLists.clear();
  timeLists.arraySetSize(N);

  for(int i=0; i<N; ++i)
  {
    names[i] = jointNames[i];
    angleLists[i] = jointValues[i];
    timeLists[i] = motionDurations[i];
  }

  // run
  bool isAbsolute = true;
  if(isPost==true)
    motionProxy->post.angleInterpolation(names, angleLists, timeLists, isAbsolute);
  else
    motionProxy->angleInterpolation(names, angleLists, timeLists, isAbsolute);
}

void MotionUtils::xMoveArm(
    const std::string& pTargetName,
    const std::string& pRobotName,
    const std::string& pChainName)
{
  boost::shared_ptr<AL::ALMotionProxy> motionProxy = getParentBroker()->getMotionProxy();

  // Function to make NAO bump on his torso with his arm '''

  // Set the fraction of max speed for the arm movement.
  float pMaxSpeedFraction = 0.5f;

  // Define the final position.
  float shoulderPitchAngle = 0.0f;
  if (pTargetName == "Torso")
  {
    shoulderPitchAngle = 50.0f * AL::Math::TO_RAD;
  }
  else if (pTargetName == "Head")
  {
    shoulderPitchAngle = -50.0f * AL::Math::TO_RAD;
  }
  else
  {
    std::cerr << "ERROR: target is unknown" << std::endl;
    std::cerr << "Must be Torso or Head" << std::endl;
    std::cerr << "---------------------" << std::endl;
    return;
  }

  float ShoulderRollAngle  =    6.0f * AL::Math::TO_RAD;
  float ElbowYawAngle      =    0.0f * AL::Math::TO_RAD;
  float ElbowRollAngle     = -150.0f * AL::Math::TO_RAD;

  AL::ALValue pTargetAngles;

  if (pChainName == "LArm")
  {
    pTargetAngles.arrayPush(shoulderPitchAngle);
    pTargetAngles.arrayPush(+ShoulderRollAngle);
    pTargetAngles.arrayPush(+ElbowYawAngle);
    pTargetAngles.arrayPush(+ElbowRollAngle);
  }
  else if (pChainName == "RArm")
  {
    pTargetAngles.arrayPush(shoulderPitchAngle);
    pTargetAngles.arrayPush(-ShoulderRollAngle);
    pTargetAngles.arrayPush(-ElbowYawAngle);
    pTargetAngles.arrayPush(-ElbowRollAngle);
  }
  else
  {
    std::cerr << "ERROR: chainName is unknown" << std::endl;
    std::cerr << "Must be LArm or RArm" << std::endl;
    std::cerr << "---------------------" << std::endl;
    return;
  }

  // Set the target angles according to the robot version.
  if (pRobotName == "naoH25" ||
      pRobotName == "naoAcademics" ||
      pRobotName == "naoT14")
  {
    pTargetAngles.arrayPush(0.0f);
    pTargetAngles.arrayPush(0.0f);
  }
  else if (pRobotName == "naoH21" ||
           pRobotName == "naoRobocup")
  {
    // Do nothing
  }
  else if (pRobotName == "naoT2")
  {
    return;
  }
  else
  {
    std::cerr << "ERROR: Your robot is unknown" << std::endl;
    std::cerr << "This test is not available for your Robot" << std::endl;
    std::cerr << "---------------------" << std::endl;
    return;
  }

  // Move the arm to the final position.
  motionProxy->angleInterpolationWithSpeed(
        pChainName, pTargetAngles, pMaxSpeedFraction);
}
