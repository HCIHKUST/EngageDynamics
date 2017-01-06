#include "nao_action.h"
#include "human_state.h"

#include "../sharedvar.h"

std::string strDisEngagedImp[5] = {"Hi ...", "Hello ...", "Hello ...", "Hi ...", "There ..."};

void NaoAction::setbackVoice()
{
//    qiLogInfo("volume")<<volume<<std::endl;
//    qiLogInfo("doubleVoice")<<doubleVoice<<std::endl;
//    qiLogInfo("doubleVoiceLevel")<<doubleVoiceLevel<<std::endl;
//    qiLogInfo("doubleVoiceTimeShift")<<doubleVoiceTimeShift<<std::endl;

    tts.setVolume(volume);
    tts.setParameter("pitchShift", pitchShift);
    tts.setParameter("doubleVoice", doubleVoice);
    tts.setParameter("doubleVoiceLevel", doubleVoiceLevel);
    tts.setParameter("doubleVoiceTimeShift", doubleVoiceTimeShift);
}

void NaoAction::response(HumanState hState, std::string keywords)
{
    switch(hState)
    {
    case PSEUDO_DIS_ENGAGED:
        tts.setVolume(1.6);
        tts.setParameter("pitchShift", 1.3);
        tts.say("Are you listening to me?");
        tts.say("I said:");
        tts.say(keywords);
        break;
    case DIS_ENGAGED:
        motionUtilsProxy.NaoWaveHands(false, true, "Stand");
        tts.setVolume(1.6);
        tts.setParameter("pitchShift", 1.3);
        tts.say("Hi! Please listen to me!");
        tts.say("I said:");
        tts.say(keywords);
        motionUtilsProxy.NaoInitialPosture();
    }
}

void NaoAction::responseImplicit(HumanState hState, std::string keywords)
{
    switch(hState)
    {
    case PSEUDO_DIS_ENGAGED:
        tts.setVolume(1.5);
        tts.setParameter("pitchShift", 1.3);
        tts.say("OK. Listen to me.");
        tts.say(keywords);
        break;
    case DIS_ENGAGED:
        int r = rand() % 5;
        tts.setVolume(1.5);
        tts.setParameter("pitchShift", 1.3);
        tts.say(strDisEngagedImp[r].c_str());
        tts.say(keywords);
        tts.say("OK.");
        break;
    }
}

void NaoAction::explicitExpress(std::string keywords, HumanState humanState)
{
    switch (humanState)
    {
    case ENGAGED:
        tts.say(keywords);
        break;
    case QUSI_ENGAGED:
        tts.say("OK. Listen to me.");
        tts.say(keywords);
        break;
    case PSEUDO_DIS_ENGAGED:
        response(PSEUDO_DIS_ENGAGED, keywords);
        setbackVoice();
        break;
    case DIS_ENGAGED:
        response(DIS_ENGAGED, keywords);
        setbackVoice();
        break;
    }
}

void NaoAction::implicitExpress(std::string keywords, HumanState humanState)
{
    switch (humanState)
    {
    case ENGAGED:
        tts.say(keywords);
        break;
    case QUSI_ENGAGED:
        tts.say("OK. Listen to me!");
        tts.say(keywords);
        break;
    case PSEUDO_DIS_ENGAGED:
        responseImplicit(PSEUDO_DIS_ENGAGED, keywords);
        setbackVoice();
        break;
    case DIS_ENGAGED:
        responseImplicit(DIS_ENGAGED, keywords);
        setbackVoice();
        break;
    }
}

void NaoAction::unawareExpress(std::string keywords, HumanState humanState)
{
    switch (humanState)
    {
    case ENGAGED:
        tts.say(keywords);
        break;
    case QUSI_ENGAGED:
        tts.say(keywords);
        break;
    case PSEUDO_DIS_ENGAGED:
        tts.say(keywords);
        break;
    case DIS_ENGAGED:
        tts.say(keywords);
        break;
    }
}
