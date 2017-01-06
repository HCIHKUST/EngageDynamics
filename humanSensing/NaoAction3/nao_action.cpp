#include "nao_action.h"

#include "../sharedvar.h"

#include <qi/os.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>

#include <ctime>

using namespace std;

NaoAction::NaoAction(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& name):
AL::ALModule(pBroker, name),
memoryProxy(pBroker),
tts(pBroker),
motionProxy(pBroker),
postureProxy(pBroker),
animatedSpeechProxy(pBroker),
motionUtilsProxy(pBroker, "MotionUtils")
{
  setModuleDescription("NaoAction.");

  functionName("NaoActForAScenario", getName(), "");
//  addParam("scenario", "scenario");
  BIND_METHOD(NaoAction::NaoActForAScenario);

  volume = 1.0;
  pitchShift = 1.2; //tts.getParameter("pitchShift");
  doubleVoice = 0; //tts.getParameter("doubleVoice");
  doubleVoiceLevel = 0; // = tts.getParameter("doubleVoiceLevel");
  doubleVoiceTimeShift = 0; //tts.getParameter("doubleVoiceTimeShift");

//  qiLogInfo("init\n");
//  qiLogInfo("doubleVoice")<<doubleVoice<<std::endl;
//  qiLogInfo("doubleVoiceLevel")<<doubleVoiceLevel<<std::endl;
//  qiLogInfo("doubleVoiceTimeShift")<<doubleVoiceTimeShift<<std::endl;

  srand(time(NULL));
}

NaoAction::~NaoAction()
{
}

void NaoAction::init()
{
//  tts.setVolume(0.7);
}

void NaoAction::NaoActForAScenario(std::string scenario)
{
  // thread safe

  try
  {
    speaking(scenario);
    // if(scenario=="MorningReport")
    //     ActionMorningReport();
    // else if(scenario=="MeetingArrangement")
    //     ActionMeetingArrangement();
    // else if(scenario=="DailySummary")
    //     ActionDailySummary();
    // else
    //     std::cerr<<"Input Scenario Error\n";
  }
  catch (const AL::ALError& e)
  {
    qiLogError("NaoAction: ") << e.what() << std::endl;
  }
  return;
}

void NaoAction::speaking(std::string arg)
{
  string fileName;

  if( arg == "MorningReport" )
    fileName = "../humanSensing/NaoAction3/scenario1.dat";
  else if(arg == "MeetingArrangement" )
    fileName = "../humanSensing/NaoAction3/scenario2.dat";
  else if(arg == "DailySummary" )
    fileName = "../humanSensing/NaoAction3/scenario3.dat";
  else{
    cerr<<"Input Argument Error"<<endl;
    return;
  }

  ifstream scriptFile;
  queue<string> scripts;

  scriptFile.open(fileName.c_str());

  if(scriptFile.is_open()){
      string temp;
      while(getline(scriptFile, temp)){
          scripts.push(temp);
      }
  }
  else{
      cerr<<"open script file error: "<<fileName<<endl;
  }

  string just_saying;

  static int count_disengage    = 0;
  static int count_q_engage     = 0;
  static int count_p_disengage  = 0;
  static int count_not_in_sight = 0;

  const char* transition_words[] = {"Well", "OK?", "Alright", "What else?", "Yes?"};

  const char* exp_p_disengage[] = {"Are you still with me?",\
                                   "Are you listening?",\
                                   "Can you turn your head?"};

  const char* exp_disengage[] = {"Hey, listen to me, it's important!",\
                                 "Hey, you don't want to miss this information!",\
                                "Oh, well! I can repeat what I just said!"};

  const char* imp_p_disengage[] = {"Mmm", "uh", "Mmm, Mmm", "uhm"};

  const char* imp_disengage[] = {"OK, you are doing other tasks. I will let you finish your task.",\
                                 "No problem, I will wait for you. Just do your tasks",\
                                 "OK, I will pause for a moment. Just do your tasks",\
                                 "OK, just do your tasks. Let me know when you are done."};

  bool flag_switch_from_disengage = false;

  static unsigned int index = 0;

  while( !scripts.empty()){
      qi::os::msleep(1000);
      index++;

      if(flag_switch_from_disengage){
          tts.say(just_saying);
          qi::os::msleep(1000);
          flag_switch_from_disengage = !flag_switch_from_disengage;
      }

      if( CURR_STATE == INIT ){
          if( count_not_in_sight > 5){
              tts.say("OK, maybe we should start the experimnet later.");
              count_not_in_sight = 0;
              break;
          }
          tts.say("Oops! ");
          tts.say("I can not find you in my eyesight");
          count_not_in_sight++;
          continue;
      }

      if( CURR_STRATEGY == UNA || CURR_STATE == F_ENGAGE ){

          just_saying = scripts.front();
          tts.say(just_saying);
          scripts.pop();

          count_disengage    = 0;
          count_q_engage     = 0;
          count_p_disengage  = 0;
          continue;
      }

      if( CURR_STRATEGY == EXP ){
//          motionUtilsProxy.NaoWaveHands(false, true, "Stand");
          if( CURR_STATE == Q_ENGAGE){

              just_saying = scripts.front();
              tts.say(just_saying);
              scripts.pop();
              qi::os::msleep(400);

              tts.say(string(transition_words[index%3]));

              count_q_engage++;
          }
          else if( CURR_STATE == P_DISENGAGE){
              tts.say(string(exp_p_disengage[index%2]));
              count_p_disengage++;
              qi::os::msleep(1000);
              if(count_p_disengage > 2){
                motionUtilsProxy.NaoWaveHands(false, true, "Stand");
                tts.say(string(exp_disengage[index%2]));
                flag_switch_from_disengage = !flag_switch_from_disengage;
                count_p_disengage  = 0;
                qi::os::msleep(2000);
                motionUtilsProxy.NaoInitialPosture();
              }
          }
          else if( CURR_STATE == DISENGAGE || count_p_disengage>3){
              tts.say(string(exp_disengage[index%2]));
              flag_switch_from_disengage = !flag_switch_from_disengage;
              qi::os::msleep(1000);
          }
          continue;
      }

      if( CURR_STRATEGY == IMP ){
          if( CURR_STATE == Q_ENGAGE){
              just_saying = scripts.front();
              tts.say(just_saying);
              scripts.pop();

              count_q_engage++;
          }
          else if( CURR_STATE == P_DISENGAGE){
              tts.say(string(imp_p_disengage[index%3]));
              count_p_disengage++;
              qi::os::msleep(1000);
              if(count_p_disengage > 2){
                tts.say(string(imp_disengage[index%4]));
                count_p_disengage  = 0;
                qi::os::msleep(2000);
              }
          }
          else if( CURR_STATE == DISENGAGE || count_p_disengage>2){
              tts.say(string(imp_disengage[index%4]));
              qi::os::msleep(2000);
          }
          continue;
      }
  }

}
