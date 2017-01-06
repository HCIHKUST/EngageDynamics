#include "sharedvar.h"

#include <iostream>
#include <map>

using namespace std;

std::map<int, std::string> MAP_PEOPLE_ID_NAME;

const string   ROBOT_IP         =   "192.168.1.111";
const int      ROBOT_PORT       =   9559;
int            CURR_HUMAN_ID    =   -1;
bool           LOOKING_OR_NOT   =   false;
bool           FEEDBACK_OR_NOT  =   false;
bool           START_FLAG      =   false;
int            CURR_POS_INDEX   =   0;
int            CURR_VALID_NUM   =   0;
Strategy       CURR_STRATEGY    =   UNA;
Engage         CURR_STATE       =   INIT;

gazeInfo             GAZE_INFO;
humanDetectionInfo   HUMAN_DETECTION_INFO;
personInfo           HUMAN_IN_SIGHT;
personInfo           HUMAN_DYNAMICS[100];
const int            WINDOW_SIZE = 5;
clock_t              LAST_FEEDBACK_TIMEPOINT = clock();

AL::ALValue          DATA_IN_SIGHT;
