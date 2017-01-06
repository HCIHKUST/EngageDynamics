#include "test.h"

#include <alvalue/alvalue.h>
#include <alcommon/alproxy.h>
#include <alcommon/albroker.h>

#include <iostream>
#include <fstream>

TestModule::TestModule(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& name):
AL::ALModule(pBroker, name),
textToSpeechProxy(pBroker),
motionUtilsProxy(pBroker, "MotionUtils")
{
}

TestModule::~TestModule()
{
}

void TestModule::init()
{
  // std::cout<<"I am here\n";
  motionUtilsProxy.NaoWaveHands(false, true, "Stand");
}
