#include "wakeup.h"
#include <iostream>

#include <qi/log.hpp>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <alcommon/almodule.h>
#include <alcommon/albroker.h>
#include <alproxies/altexttospeechproxy.h>

#define COMMAND "Hey, Mo Jing"

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
}

wakeUp::~wakeUp()
{
}

void wakeUp::init()
{
    mem = getParentBroker()->getMemoryProxy();
    speech_recog = getParentBroker()->getProxy("ALSpeechRecognition");
    speak_out = getParentBroker()->getProxy("ALTextToSpeech");

}

void wakeUp::exit()
{

}

void wakeUp::standUp()
{
    try{
        speech_recog->callVoid("setLanguage", string("English"));

        speak_out->callVoid("setLanguage", string("Chinese"));

        vector<string> command_list;
        command_list.push_back(wake_up_command);
        speech_recog->callVoid("setVocabulary", command_list, false);

    }
    catch(const AL::ALError& e ){
        speech_recog->callVoid("pause", true);
        speech_recog->callVoid("setLanguage", string("English"));

        vector<string> command_list;
        command_list.push_back(wake_up_command);
        speech_recog->callVoid("setVocabulary", command_list, false);
        speech_recog->callVoid("pause", false);
    }

    speech_recog->callVoid("pause", false);
    mem->subscribeToEvent("WordRecognized", getName(), "onWakeUp");
}

void wakeUp::stopStandUp()
{
    try{
        mem->unsubscribeToEvent("WordRecognized", getName());
    }
    catch(const AL::ALError& e){
    }
    setStatus(false);
    speech_recog->callVoid("pause", true);
}

void wakeUp::onWakeUp(const string &name, const AL::ALValue &val, const string &myName)
{
    qiLogInfo("Wake Up Callback:")<<">";
    if((string)val[0] == wake_up_command && (float)val[1] >= 0.37){
        setStatus(true);
        speak_out->callVoid("say", "嘿，你好！");
    }
    else{
        setStatus(false);
    }
}

bool wakeUp::getStatus()
{
    return status;
}

void wakeUp::setStatus(bool val)
{
    status = val;
}
