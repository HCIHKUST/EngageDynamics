#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "sharedvar.h"

#include <boost/shared_ptr.hpp>
#include <alcommon/albroker.h>
#include <alproxies/almemoryproxy.h>

#include <iostream>


using namespace std;

class operations
{
public:
  operations(boost::shared_ptr<AL::ALBroker> broker);

  bool copyGazeInfo(int humanID, gazeInfo* const dest);
  void dispGazeInfo(const gazeInfo* dest);

  bool copyHumanDetectionInfo(int humanID, humanDetectionInfo* const dest);
  void dispHumanDetectionInfo(const humanDetectionInfo* dest);

  bool copyPersonInfo(AL::ALValue data, personInfo* const dest);
  void dispPersonInfo(const personInfo* dest);

  bool detecHeadPitch();
  bool detecHeadYaw();
  bool detecDistanceChange();

private:
  AL::ALMemoryProxy* mem;

 // const char* gaze_arguments[5] = {"EyeOpeningDegree",\
                                   "GazeDirection",\
                                   "HeadAngles",\
                                   "IsLookingAtRobot",\
                                   "LookingAtRobotScore"};

  const char* gaze_arguments[4] = { "EyeOpeningDegree",\
                                    "GazeDirection",\
                                    "HeadAngles",\
                                    "LookingAtRobotScore"};

  const unsigned int gaze_arguments_num = 4;

 // const char* people_perception_arguements[13] ={"ShirtColor",\
                                                 "IsVisible",\
                                                 "PresentSince",\
                                                 "RealHeight", \
                                                 "PositionInRobotFrame",\
                                                 "AnglesYawPitch",\
                                                 "ShirtColorHsv",\
                                                 "Distance",\
                                                 "NotSeenSince",\
                                                 "LastSeenHeight",\
                                                 "IsFaceDetected",\
                                                 "PositionInWorldFrame",\
                                                 "PositionInTorsoFrame"};

  const char* people_perception_arguements[5] ={ "IsVisible",\
                                                 "PositionInRobotFrame",\
                                                 "AnglesYawPitch",\
                                                 "Distance",\
                                                 "IsFaceDetected"};

  const unsigned int people_perception_arguements_num = 5;

};

#endif // OPERATIONS_H
