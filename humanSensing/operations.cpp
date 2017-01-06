#include "operations.h"

#include "sharedvar.h"

#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>

#include <qi/log.hpp>
#include <alproxies/almemoryproxy.h>
#include <alvalue/alvalue.h>
#include <alerror/alerror.h>

using namespace std;

operations::operations(boost::shared_ptr<AL::ALBroker> broker)
{
    mem = new AL::ALMemoryProxy(broker);
}

bool operations::copyGazeInfo(int humanID, gazeInfo* const dest)
{
    char temp[500];
    vector<string> args;

    for(int i=0; i<gaze_arguments_num; i++){
        sprintf(temp, "PeoplePerception/Person/%d/%s", humanID, gaze_arguments[i]);
        args.push_back(string(temp));
    }

    try{
        AL::ALValue dataPack = mem->getListData(args);
        int index = 0;

        AL::ALValue temp = dataPack[index++]; // eye opening degree
        if( temp.getSize() == 2){
            dest->eyeOpeningDegree[0] = (float)temp[0];
            dest->eyeOpeningDegree[1] = (float)temp[1];
            qiLogInfo("Eye opening degree")<<"ok"<<endl;
        }

        temp = dataPack[index++]; // gaze direction
        if( temp.getSize() == 2){
            dest->gazeDirection[0] = (float)temp[0];
            dest->gazeDirection[1] = (float)temp[1];
            qiLogInfo("Gaze direction")<<"ok"<<endl;
        }

        temp = dataPack[index++]; // head angles
        if( temp.getSize() == 3){
            dest->headAngles[0] = (float)temp[0];
            dest->headAngles[1] = (float)temp[1];
            dest->headAngles[2] = (float)temp[2];
            qiLogInfo("Head angle")<<"ok"<<endl;
        }

        // dest->isLookingAtRobot = (bool)dataPack[index++]; // is looking at robot
        // qiLogInfo("Is looking at robot")<<"ok"<<endl;

        dest->lookingAtRobotScore = (float)dataPack[index++]; // looking at robot score
        qiLogInfo("Looking at robot score")<<"ok"<<endl;

        return true;
    }
    catch(AL::ALError& e ){
        qiLogError("Get list data from memory error: ")<<e.what()<<endl;
        return false;
    }
}

void operations::dispGazeInfo(const gazeInfo *dest)
{
    qiLogInfo("------------------- Gaze Information -------------------")<<std::endl;
    qiLogInfo("Eye opeing degree")<<dest->eyeOpeningDegree[0]<<","<<dest->eyeOpeningDegree[1]<<std::endl;
    qiLogInfo("Gaze direction")<<dest->gazeDirection[0]<<","<<dest->gazeDirection[1]<<std::endl;
    qiLogInfo("Head angles")<<dest->headAngles[0]<<","<<dest->headAngles[1]<<","<<dest->headAngles[2]<<std::endl;
    // qiLogInfo("Is looking at robot")<<(dest->isLookingAtRobot ? "Yes" : "No")<<std::endl;
    qiLogInfo("Looking at robot score")<<dest->lookingAtRobotScore<<std::endl;
    qiLogInfo("------------------------- end --------------------------");
}

bool operations::copyHumanDetectionInfo(int humanID, humanDetectionInfo* const dest)
{
    char temp[500];
    vector<string> args;

    for(int i=0; i<people_perception_arguements_num; i++){
        sprintf(temp, "PeoplePerception/Person/%d/%s", humanID, people_perception_arguements[i]);
        args.push_back(string(temp));
    }

    const vector<string> argsConst(args);

    try{
        AL::ALValue dataPack = mem->getListData(argsConst);
        int index = 0;

        // dest->shirtColor = string(dataPack[index++]);

        dest->isVisible = (bool)dataPack[index++];

        // dest->notSeenSince = (int)dataPack[index++];

        // dest->realHeight = (float)dataPack[index++];

        AL::ALValue temp = dataPack[index++];
        if( temp.getSize() == 3){
            dest->positionInRobotFrame[0] = (float)temp[0];
            dest->positionInRobotFrame[1] = (float)temp[1];
            dest->positionInRobotFrame[2] = (float)temp[2];
        }

        temp = dataPack[index++];
        if(temp.getSize() == 2){
            dest->anglesYawPicth[0] = (float)temp[0];
            dest->anglesYawPicth[1] = (float)temp[1];
        }

        // temp = dataPack[index++];
        // if(temp.getSize() == 3){
        //     dest->positionInTorsoFrame[0] = (float)temp[0];
        //     dest->positionInTorsoFrame[1] = (float)temp[1];
        //     dest->positionInTorsoFrame[2] = (float)temp[2];
        // }

        dest->distance = (float)dataPack[index++];

        // dest->presentSince = (int)dataPack[index++];

        // dest->lastSeenHeight = (float)dataPack[index++];

        dest->isFaceDetected = (bool)dataPack[index++];

        // temp = dataPack[index++];
        // if(temp.getSize() == 3){
        //     dest->positionInWorldFrame[0] = (float)temp[0];
        //     dest->positionInWorldFrame[1] = (float)temp[1];
        //     dest->positionInWorldFrame[2] = (float)temp[2];
        // }

        // temp = dataPack[index++];
        // if(temp.getSize() == 3){
        //     dest->shirtColorHSV[0] = (float)temp[0];
        //     dest->shirtColorHSV[1] = (float)temp[1];
        //     dest->shirtColorHSV[2] = (float)temp[2];
        // }

        return true;
    }
    catch(AL::ALError& e ){
        qiLogError("Get list data from memory error: ")<<e.what()<<endl;
        return false;
    }
}

void operations::dispHumanDetectionInfo(const humanDetectionInfo *dest)
{
    qiLogInfo("------------------- Human Detection Information -------------------")<<std::endl;
    // qiLogInfo("Shirt color")<<dest->shirtColor<<std::endl;
    qiLogInfo("Is visible")<<(dest->isVisible ? "Yes" : "No")<<std::endl;
    // qiLogInfo("Presense since")<<dest->presentSince<<std::endl;
    // qiLogInfo("Real height")<<dest->realHeight<<std::endl;
    qiLogInfo("Position in robot frame")<<dest->positionInRobotFrame[0]<<","<<dest->positionInRobotFrame[1]<<","<<dest->positionInRobotFrame[2]<<std::endl;
    qiLogInfo("Angles yaw pitch")<<dest->anglesYawPicth[0]<<","<<dest->anglesYawPicth[1]<<std::endl;
    // qiLogInfo("Shirt color HSV")<<dest->shirtColorHSV[0]<<","<<dest->shirtColorHSV[1]<<","<<dest->shirtColorHSV[2]<<std::endl;
    qiLogInfo("Distance")<<dest->distance<<std::endl;
    // qiLogInfo("Not seen since")<<dest->notSeenSince<<std::endl;
    // qiLogInfo("Last seen height")<<dest->lastSeenHeight<<std::endl;
    qiLogInfo("Is face detected")<<(dest->isFaceDetected ? "Yes" : "No")<<std::endl;
    // qiLogInfo("Position in world frame")<<dest->positionInWorldFrame[0]<<","<<dest->positionInWorldFrame[1]<<","<<dest->positionInWorldFrame[2]<<std::endl;
    // qiLogInfo("Position in torso frame")<<dest->positionInTorsoFrame[0]<<","<<dest->positionInTorsoFrame[1]<<","<<dest->positionInTorsoFrame[2]<<std::endl;
    qiLogInfo("----------------------------- end ----------------------------------")<<std::endl;
}

bool operations::copyPersonInfo(AL::ALValue data, personInfo * const dest)
{
    int index = 0;
    if(data.getSize() == 4){
        dest->id = data[index++];
        dest->distanceToCamera = data[index++];
        dest->pitchAngleInImage = data[index++];
        dest->yawAngleInImage = data[index++];

        CURR_POS_INDEX = (CURR_POS_INDEX+1) % 100;
        CURR_VALID_NUM = (++CURR_VALID_NUM) > WINDOW_SIZE ? WINDOW_SIZE : CURR_VALID_NUM;

        return true;
    }

    return false;
}

void operations::dispPersonInfo(const personInfo *dest)
{
    qiLogInfo("----------------------- Person Data Info -----------------------------")<<std::endl;
    qiLogInfo("ID")<<dest->id<<std::endl;
    qiLogInfo("Distance to camera")<<dest->distanceToCamera<<std::endl;
    qiLogInfo("Pitch angle in image")<<dest->pitchAngleInImage<<std::endl;
    qiLogInfo("Yaw angle in image")<<dest->yawAngleInImage<<std::endl;
    qiLogInfo("----------------------------  END     --------------------------------")<<std::endl;
}

bool operations::detecHeadPitch()
{
    int pos = CURR_POS_INDEX;
    float sum = 0;

    for(int i=0; i<WINDOW_SIZE; i++){
        sum += HUMAN_DYNAMICS[pos--].pitchAngleInImage;
        pos = (pos+100) % 100;
    }

    float avg = sum/WINDOW_SIZE;
    float varr = 0;

    pos = CURR_POS_INDEX;
    for(int i=0; i<WINDOW_SIZE; i++){
        varr += abs( HUMAN_DYNAMICS[pos--].pitchAngleInImage - avg + 0.0f );
        pos = (pos+100) % 100;
    }
    qiLogInfo("varr")<<varr<<std::endl;

    if(varr >= 0.2){
        return true;
    }
    else{
        return false;
    }
}

bool operations::detecHeadYaw()
{
    int ind = WINDOW_SIZE;
    int pos = CURR_POS_INDEX;
    float sum = 0;

    while(ind){
        sum += HUMAN_DYNAMICS[pos--].yawAngleInImage;
        pos = (pos+100) % 100;
        ind--;
    }

    float avg = sum/WINDOW_SIZE;
    float varr = 0;

    while(ind < WINDOW_SIZE){
        varr += abs( HUMAN_DYNAMICS[pos++].yawAngleInImage - avg + 0.0f );
        pos = (pos+100) % 100;
        ind++;
    }
    // qiLogInfo("Varr of head yaw")<<varr<<std::endl;

    if(varr >= 0.07){
        return true;
    }
    else{
        return false;
    }
}

bool operations::detecDistanceChange()
{
    int ind = WINDOW_SIZE;
    int pos = CURR_POS_INDEX;
    float sum = 0;

    while(ind){
        sum += HUMAN_DYNAMICS[pos--].distanceToCamera;
        pos = (pos+100) % 100;
        ind--;
    }

    float avg = sum/WINDOW_SIZE;
    float varr = 0;

    while(ind < WINDOW_SIZE){
        varr += abs( HUMAN_DYNAMICS[pos++].distanceToCamera - avg + 0.0f );
        pos = (pos+100) % 100;
        ind++;
    }
    qiLogInfo("Varr of distance change")<<varr<<std::endl;

    if(varr >= 0.1){
        return true;
    }
    else{
        return false;
    }
}
