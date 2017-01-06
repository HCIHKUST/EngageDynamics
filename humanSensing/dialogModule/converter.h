#ifndef CONVERTER_H
#define CONVERTER_H
#include <iostream>
#include <string>

#include <qi/os.hpp>
#include <alcommon/albroker.h>
#include <alcommon/almodule.h>
#include <boost/shared_ptr.hpp>
#include <alproxies/almotionproxy.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/alanimatedspeechproxy.h>
#include <alproxies/alaudiorecorderproxy.h>
#include <alproxies/alspeechrecognitionproxy.h>

using std::string;

namespace AL {
   class ALBroker;
}

class Converter : public AL::ALModule
{
public:
  Converter(boost::shared_ptr<AL::ALBroker> broker, const std::string &name);
  virtual ~Converter();
  virtual void init();
  void sayThis(string tosay);
  void flushResult();
  void proxyInit();
  void start();
  void stop();
  void hintSayAgain();
  bool getReady();
  bool getExit();
  bool getCafe();
  string getResult();
  void test();

private:
  int ret;
  bool ready;
  bool cafe;
  bool rec_now;
  bool exit_val;
  string rec_result;
  AL::ALMemoryProxy* mem_pro;
  AL::ALMemoryProxy* mem_pro_s;
  AL::ALTextToSpeechProxy* tts_lang;
  AL::ALAnimatedSpeechProxy* tts;
  AL::ALAudioRecorderProxy* audio_rec_pro;
  AL::ALSpeechRecognitionProxy* speech_recog_pro;

  bool witAI();
  void startRecording();
  void stopRecording();
  void transition(int type);
  void speechDetecting(std::string eventName, AL::ALValue status, std::string subId);
};

#endif
