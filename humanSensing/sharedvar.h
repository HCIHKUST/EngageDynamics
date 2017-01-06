#ifndef SHAREDVAR_H
#define SHAREDVAR_H
// this is the shared variable header file

#include <iostream>
#include <map>
#include <vector>
#include <ctime>

#include <alvalue/alvalue.h>

using namespace std;

/**************************************************
**       STRUCT DEFINITIONS START HERE          **
**************************************************/

struct gazeInfo{
    float    eyeOpeningDegree[2];   // left eye, right eye
    float    gazeDirection[2];      // [yaw, pitch] in radian, relative to the plane of the face
    float    headAngles[3];         // [yaw, pitch, roll] in radian
    //bool     isLookingAtRobot;
    float    lookingAtRobotScore;
};

struct humanDetectionInfo{
    // string   shirtColor; // black, gray, white, red, orange, yellow, green, blue, purple
    bool     isVisible;
    // int      presentSince;
    // float    realHeight;
    float    positionInRobotFrame[3];
    float    anglesYawPicth[2];
    // float    shirtColorHSV[3];
    float    distance;
    // int      notSeenSince;
    // float    lastSeenHeight;
    bool     isFaceDetected;
    // float    positionInWorldFrame[3];
    // float    positionInTorsoFrame[3];
};

struct personInfo{
    int    id;
    float  distanceToCamera;
    float  pitchAngleInImage;
    float  yawAngleInImage;
};

enum Engage {INIT, F_ENGAGE, Q_ENGAGE, P_DISENGAGE, DISENGAGE};
enum Strategy {IMP, EXP, UNA};


/**************************************************
**      CONSTANTS  DEFINITIONS START HERE       **
**************************************************/

extern map<int, string>     MAP_PEOPLE_ID_NAME;

extern const string         ROBOT_IP;
extern const int            ROBOT_PORT;
extern int                  CURR_HUMAN_ID;

extern gazeInfo             GAZE_INFO;
extern humanDetectionInfo   HUMAN_DETECTION_INFO;
extern personInfo           HUMAN_IN_SIGHT;
extern personInfo           HUMAN_DYNAMICS[100];
extern const int            WINDOW_SIZE;
extern int                  CURR_POS_INDEX;
extern int                  CURR_VALID_NUM;

extern bool                 LOOKING_OR_NOT;
extern bool                 FEEDBACK_OR_NOT;
extern bool                 START_FLAG;
extern Engage               CURR_STATE;
extern Strategy             CURR_STRATEGY;

extern AL::ALValue          DATA_IN_SIGHT;
extern std::clock_t         LAST_FEEDBACK_TIMEPOINT;

#endif // SHAREDVAR_H
