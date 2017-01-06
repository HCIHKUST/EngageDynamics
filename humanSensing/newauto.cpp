#include "sharedvar.h"
#include "newauto.h"
#include <iostream>

#include <alproxies/alautonomouslifeproxy.h>
#include <alproxies/alrobotpostureproxy.h>

newAuto::newAuto(boost::shared_ptr<AL::ALBroker> broker)
{
    autono = new AL::ALAutonomousLifeProxy(broker);
    posture = new AL::ALRobotPostureProxy(broker);

    if(autono->getState() != "disabled"){
        autono->setState("disabled");
    }

    // if(posture->getPosture() != "Stand"){
    //     setPosture("Stand", 1.0);
    // }
    setPosture("Stand");

}

void newAuto::setPosture(const std::string name)
{
    posture->goToPosture(name, 0.2);
}
