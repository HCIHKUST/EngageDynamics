#ifndef WAKEUP_H
#define WAKEUP_H

#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <alcommon/almodule.h>
#include <alcommon/albroker.h>
#include <alproxies/altouchproxy.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/alspeechrecognitionproxy.h>

using std::string;

namespace AL {
    class ALBroker;
}

class wakeUp: public AL::ALModule
{
public:
  wakeUp(boost::shared_ptr<AL::ALBroker> broker, const string name);
  virtual ~wakeUp();
  virtual void init();
  virtual void exit();
  void standUp();
  void stopStandUp();
  bool getStatus();

  void onWakeUp(const string& name, const AL::ALValue& val, const string& myName);
  void handTouched(string evName, float val, string subID);

private:
  bool status;
  string wake_up_command;
  AL::ALTouchProxy* touch;
  AL::ALMemoryProxy* mem;
  AL::ALSpeechRecognitionProxy* speech_recog;
  AL::ALTextToSpeechProxy* speak_out;

  void setStatus(bool val);
};

#endif // WAKEUP_H
