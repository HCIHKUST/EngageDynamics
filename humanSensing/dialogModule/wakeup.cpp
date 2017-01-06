#include "wakeup.h"
#include <iostream>

#include <qi/log.hpp>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <alcommon/almodule.h>
#include <alcommon/albroker.h>
#include <alproxies/altexttospeechproxy.h>

#define COMMAND "Hey, Robot"

using std::string;
using std::vector;
using std::endl;

wakeUp::wakeUp(boost::shared_ptr<AL::ALBroker> broker, const string name)
    :AL::ALModule(broker, name), wake_up_command(COMMAND), status(false)
{
    setModuleDescription("");

    functionName("standUp", getName(), "standUp");
    BIND_METHOD(wakeUp::standUp);

    functionName("stopStandUp", getName(), "stopStandUp");
    BIND_METHOD(wakeUp::stopStandUp);

    functionName("getStatus", getName(), "getStatus");
    setReturn("bool", "bool");
    BIND_METHOD(wakeUp::getStatus);

    functionName("onWakeUp", getName(), "onWakeUp");
    BIND_METHOD(wakeUp::onWakeUp);

    functionName("handTouched", getName(), "");
    BIND_METHOD(wakeUp::handTouched);
}

wakeUp::~wakeUp()
{
}

void wakeUp::init()
{
    mem = new AL::ALMemoryProxy(getParentBroker());
    speech_recog = new AL::ALSpeechRecognitionProxy(getParentBroker());
    speak_out = new AL::ALTextToSpeechProxy(getParentBroker());
    touch = new AL::ALTouchProxy(getParentBroker());
}

void wakeUp::exit()
{

}

void wakeUp::standUp()
{
    try{
        speech_recog->setLanguage("English");

        speak_out->setLanguage("English");
        speak_out->loadVoicePreference("NaoOfficialVoiceEnglish");

        vector<string> command_list;
        command_list.push_back(wake_up_command);
        speech_recog->setVocabulary(command_list, false);

    }
    catch(const AL::ALError& e ){
        speech_recog->pause(true);
        speech_recog->setLanguage("English");

        vector<string> command_list;
        command_list.push_back(wake_up_command);
        speech_recog->setVocabulary(command_list, false);
    }

    speech_recog->pause(false);
    mem->subscribeToEvent("WordRecognized", getName(), "onWakeUp");

    mem->subscribeToEvent("HandRightBackTouched", getName(), "handTouched");
    //mem->subscribeToEvent("HandRightLeftTouched", getName(), "handTouched");
    //mem->subscribeToEvent("HandRightRightTouched", getName(), "handTouched");

    mem->subscribeToEvent("HandLeftBackTouched", getName(), "handTouched");
    //mem->subscribeToEvent("HandLeftLeftTouched", getName(), "handTouched");
    //mem->subscribeToEvent("HandLeftRightTouched", getName(), "handTouched");
}

void wakeUp::stopStandUp()
{
    try{
        mem->unsubscribeToEvent("WordRecognized", getName());

        mem->unsubscribeToEvent("HandRightBackTouched", getName());
        //mem->unsubscribeToEvent("HandRightLeftTouched", getName());
        //mem->unsubscribeToEvent("HandRightRightTouched", getName());

        mem->unsubscribeToEvent("HandLeftBackTouched", getName());
        //mem->unsubscribeToEvent("HandLeftLeftTouched", getName());
        //mem->unsubscribeToEvent("HandLeftRightTouched", getName());
    }
    catch(const AL::ALError& e){
    }
    setStatus(false);
    speech_recog->pause(true);
}

void wakeUp::onWakeUp(const string &name, const AL::ALValue &val, const string &myName)
{
    qiLogInfo("Wake Up Callback:")<<">";
    if((string)val[0] == wake_up_command && (float)val[1] >= 0.37){
        setStatus(true);
        //speak_out->say("嘿，你好！");
        speak_out->post.say("Hey!");
    }
    else{
        setStatus(false);
    }
}

void wakeUp::handTouched(std::string evName, float val, std::string subID)
{
    setStatus(true);
    speak_out->say("Hey!");
}

bool wakeUp::getStatus()
{
    return status;
}

void wakeUp::setStatus(bool val)
{
    status = val;
}
