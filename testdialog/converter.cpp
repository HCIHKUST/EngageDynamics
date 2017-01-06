#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "converter.h"
#include "exec_shell.h"

#include <qi/os.hpp>
#include <qi/log.hpp>
#include <alcommon/almodule.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alaudiorecorderproxy.h>
#include <alproxies/alspeechrecognitionproxy.h>

#define UPLOAD_SPEECH 1
#define CONFIRM_TEXT 2
#define UPLOAD_HUM 3

const char* WAV_NAME_LOCAL = "/home/nao/mingfei/dialogAudio/test.wav";
std::string finishWords = "需要时随时吩咐我^runTag(bow)";
using namespace AL;

Converter::Converter(boost::shared_ptr<ALBroker> broker, const std::string &name)
    :AL::ALModule(broker, name)
    ,tts(new AL::ALAnimatedSpeechProxy(broker))
    ,tts_lang(new AL::ALTextToSpeechProxy(broker))
{
    flushResult();

    tts_lang->setLanguage("Chinese");

    functionName("getResult", getName(), "");
    setReturn("string", "string");
    BIND_METHOD(Converter::getResult);

    functionName("flushResult", getName(), "");
    BIND_METHOD(Converter::flushResult);

    functionName("speechDetecting", getName(), "");
    BIND_METHOD(Converter::speechDetecting);

    functionName("start", getName(), "");
    BIND_METHOD(Converter::start);

    functionName("stop", getName(), "");
    BIND_METHOD(Converter::stop);

    functionName("proxyInit", getName(), "");
    BIND_METHOD(Converter::proxyInit);

    functionName("getReady", getName(), "");
    BIND_METHOD(Converter::getReady);

    functionName("test", getName(), "");
    BIND_METHOD(Converter::test);

    functionName("getExit", getName(), "");
    BIND_METHOD(Converter::getExit);

    functionName("getCafe", getName(), "");
    BIND_METHOD(Converter::getCafe);

    functionName("sayThis", getName(), "");
    addParam("tosay", "tosay");
    BIND_METHOD(Converter::sayThis);

    ready = true;
    exit_val = false;
    cafe = false;
}

Converter::~Converter()
{
    mem_pro->unsubscribeToEvent("ALSpeechRecognition/Status", getName());
}

void Converter::init()
{
}

void Converter::proxyInit()
{
    mem_pro          = new AL::ALMemoryProxy(getParentBroker());
    mem_pro_s        = new AL::ALMemoryProxy(getParentBroker());
    motion_pro       = new AL::ALMotionProxy(getParentBroker());
    audio_rec_pro    = new AL::ALAudioRecorderProxy(getParentBroker());

}

void Converter::sayThis(string tosay)
{
    if(ready){
        tts->say(tosay);
    }
}

void Converter::speechDetecting(std::string eventName, AL::ALValue status, std::string subId)
{
    qiLogInfo("Status Info:")<<(string)status<<"  ";
    motion_pro->setAngles("HeadYaw", 0.0f, 0.3f);
    if(std::string(status) == "ListenOn" && !rec_now ){
        startRecording();
    }
    if((std::string(status) == "ListenOff") && rec_now ){
        stopRecording();
        mem_pro->unsubscribeToEvent("ALSpeechRecognition/Status", getName());
        transition(UPLOAD_SPEECH);
        speech_recog_pro->pause(true);
        witAI();
    }
}

void Converter::startRecording()
{
    AL::ALValue channels;
    channels.arrayPush(0); //left
    channels.arrayPush(0); //right
    channels.arrayPush(1); //front
    channels.arrayPush(0); //rear
    try{
        qiLogInfo("Recording Status")<<"RECORDING"<<std::endl;
        audio_rec_pro->startMicrophonesRecording(WAV_NAME_LOCAL, "wav", 16000, channels);
    }
    catch(AL::ALError& e){
        qiLogError("Recording Error")<<e.what()<<std::endl;
    }

    motion_pro->setAngles("HeadYaw", 0.0f, 0.3f);
    rec_now = true;
}

void Converter::stopRecording()
{
    qiLogInfo("Recording Status")<<"STOP RECORDING"<<std::endl;
    audio_rec_pro->stopMicrophonesRecording();
    rec_now = false;
}

void Converter::transition(int type)
{
    static int index = 0;
    std::string fileName;
    std::vector<string> trans;
    std::ifstream inContents;

    switch (type) {
        case UPLOAD_SPEECH:
            fileName = "speechTran.dat";
            break;
        case CONFIRM_TEXT:
            fileName = "confirmTran.dat";
            break;
        case UPLOAD_HUM:
            fileName = "speechHum.dat";
            break;
    }
    inContents.open(fileName.c_str(), std::ios::in);

    if(!inContents){
        std::cerr<<fileName<<"open error"<<std::endl;
        std::exit(1);
    }
    std::string temp;
    while(inContents>>temp){
        trans.push_back(temp);
    }
    tts->post.say(trans[index%trans.size()]);
    index++;
}

void Converter::flushResult()
{
    rec_result = "";
}

void Converter::start()
{
    speech_recog_pro = new AL::ALSpeechRecognitionProxy(getParentBroker());

    std::vector<std::string> wordList;
    wordList.push_back("谢谢");

    try{
        speech_recog_pro->setLanguage("Chinese");
        speech_recog_pro->setAudioExpression(true);
        speech_recog_pro->setVisualExpression(true);
        speech_recog_pro->setVocabulary(wordList, false);

        motion_pro->setAngles("HeadYaw", 0.0f, 0.1f);
        motion_pro->setStiffnesses("HeadYaw", 0.0f);
    }
    catch(AL::ALError& e){
        //std::cout<<e.what()<<std::endl;
    }

    mem_pro->subscribeToEvent("ALSpeechRecognition/Status", getName(), "speechDetecting");
    speech_recog_pro->pause(false);
    ready = false;
    exit_val = false;
}

void Converter::stop()
{
    try{
        mem_pro->unsubscribeToEvent("ALSpeechRecognition/Status", getName());
        speech_recog_pro->pause(true);
    }
    catch(AL::ALError& e){
        //std::cout<<e.what()<<std::endl;
    }
    cafe = false;
    sayThis(finishWords);
}

bool Converter::getReady()
{
    return ready;
}

bool Converter::getExit()
{
    return exit_val;
}

bool Converter::getCafe()
{
    return cafe;
}

string Converter::getResult()
{
    return rec_result;
}

void Converter::test()
{
    witAI();
}

bool Converter::witAI()
{

    char* cmd = "ssh nao@192.168.1.102 'bash -s' < upload.sh";
    // char* cmd = "sh /home/nao/mingfei/curl.sh";

    std::string result = exec_shell(cmd);

    qiLogInfo("Raw SPR Result:")<<result<<std::endl;
    std::string loc = "\"_text\"";
    int ind_e = result.find(loc);
    while(result[ind_e] != ':'){
        ind_e++;
    }
    while(result[ind_e] != '"'){
        if(result[ind_e] == ','){
            rec_result = "";
            ready = true;

            return true;
        }
        ind_e++;
    }
    int ind_s = ++ind_e;
    while(result[ind_e] != '"'){
        ind_e++;
    }
    rec_result = result.substr(ind_s, ind_e-ind_s);
    loc = "谢谢";

    if(rec_result.find(loc) != -1){
        exit_val = true;
    }

    loc = "咖啡";
    if(rec_result.find(loc) != -1){
        cafe = true;
    }

    ready = true;

    return true;
}
