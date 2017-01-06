#ifndef WAKEUP_H
#define WAKEUP_H

#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <alcommon/almodule.h>
#include <alcommon/albroker.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/altexttospeechproxy.h>

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
  void onWakeUp(const string& name, const AL::ALValue& val, const string& myName);
  bool getStatus();

private:
  bool status;
  string wake_up_command;
  boost::shared_ptr<AL::ALMemoryProxy> mem;
  boost::shared_ptr<AL::ALProxy> speech_recog;
  boost::shared_ptr<AL::ALProxy> speak_out;

  void setStatus(bool val);
};

#endif // WAKEUP_H
