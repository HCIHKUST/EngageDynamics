#include "nao_action.h"
#include "human_state.h"

#include "../sharedvar.h"

void NaoAction::engagementBasedAction(std::string keywords)
{
  HumanState humanState = getHumanState();
  // CURR_STRATEGY

  switch (CURR_STRATEGY)
  {
  case EXP:
     explicitExpress(keywords, humanState);
     break;
  case IMP:
     implicitExpress(keywords, humanState);
     break;
  default:
     unawareExpress(keywords, humanState);
     break;
  }
  qi::os::msleep(200u);
}

void NaoAction::ActionMorningReport()
{
  qiLogInfo("Moring Report Start")<<std::endl;

  tts.say("Good Morning!");
  qi::os::msleep(1000u);

  tts.say("You have two new emails.");
  qi::os::msleep(200u);
  tts.say("Would you like to read them now?");

  tts.say("The first email is from Julie. She says that");
  tts.say("Peter is sick, and is currently hospitalized!");
  tts.say("So instead, Julie will come to your office on Friday this week");
  qi::os::msleep(200u);

  engagementBasedAction("She will discuss with you about the hiking event on Sunday.");
  tts.say("OK.");
  qi::os::msleep(200u);
  engagementBasedAction("Please note that she will come around 11:30am.");

  tts.say("Oh. About the hiking. Julie says that she plans to go to the Clear Water Bay Country Park.");
  tts.say("It is a beautiful country park near the Clearwater Bay.");
  tts.say("And Clearwater Bay Peninsula is a typical submergent coast.");
  tts.say("It is a comfortable starting point for hikers.");
  tts.say("This popular barbecue and picnic destination almost always has a cool breeze.");
  tts.say("And Many come here just to fly kites.");


  tts.say("");
  tts.say("The second email is from Prof. Park.");
  qi::os::msleep(300u);

  tts.say("He says next week's class will be canceled.");
  qi::os::msleep(100u);

  tts.say("Because he will attend an important academic conference, and give a talk then.");
  qi::os::msleep(100u);

  tts.say("The main theme of this conference is about Deep Learning on Robotics.");
  tts.say("Many famous scholars will come.");
  tts.say("Using deep learning to make robots more intelligent is a promising direction.");
  tts.say("Prof. Park says that you can keep an eye on this area for your future research.");
  qi::os::msleep(100u);

  tts.say("The good news is that Prof. Park will arrange a group lunch when he comes back next Friday.");
  qi::os::msleep(100u);

  tts.say("However, he stresses that you should submit your paper draft on time by 7 September.");
  qi::os::msleep(100u);

  tts.say("OK.");
  engagementBasedAction("Remember to sumbmit your draft.");

  tts.say("OK. Sounds like you have a lot of work to do.");

  tts.say("Fighting! Have a fruitful day!");
}

void NaoAction::ActionMeetingArrangement()
{
  tts.say("Hello! Knock, knock, knock.");
  qi::os::msleep(500u);

  tts.say("Davis wants to see you at twelve o'clock this Tuesday!");
  engagementBasedAction("You have a meeting on this Tuesday!");

  tts.say("He wants to talk with you about some problems with our new website.");
  qi::os::msleep(200u);

  tts.say("He says Luise cannot make it, but Dr. Wang will join instead!");
  qi::os::msleep(200u);
  tts.say("And Dr. Wang will in charge of this project!");
  qi::os::msleep(200u);
  engagementBasedAction("Your boss will come.");

  tts.say("Dr. Wang is a seasoned software engineer.");
  tts.say("He got his PhD degree from Stanford Unviversity.");
  tts.say("And then he joined Microsoft Research Redmond immediately after graduation,");
  tts.say("and worked there for five years as a senior researcher.");
  tts.say("After that, he went to Goolge as a project manager, and worked there for three years.");
  tts.say("Before joining our company, he was a Vice President at Facebook.");
  tts.say("Wow. Really a knowledgable boss.");

  tts.say("OK. You should prepare for this meeting.");
  qi::os::msleep(200u);

  tts.say("Dr. Wang says many customers complain that they cannot log into their accounts on our new website.");
  qi::os::msleep(200u);

  tts.say("They are sure that they have typed in the correct passwords. Maybe there are some bugs in your code.");
  qi::os::msleep(200u);

  tts.say("He wants you to check your program beforehand");
  tts.say(", and make sure that your implementation is error-free before this meeting.");
  engagementBasedAction("Check your code.");

  tts.say("OK. That’s all for this week’s meeting arrangement!");
  tts.say("Good luck, and have a nice one");
  qi::os::msleep(1000u);
}

void NaoAction::ActionDailySummary()
{
  tts.say("What a busy day!");
  qi::os::msleep(500u);

  tts.say("You have had quite a lot of work done today!");
  qi::os::msleep(200u);

  tts.say("Almost finish your photoshop homework! But, ");
  qi::os::msleep(200u);
  engagementBasedAction("You sister has asked you to help her edit her profile photo.");

  tts.say("You konw. She just graduated from university, and needs a good profile photo to find a good job.");
  tts.say("So. Do a favor for your sister.");

  tts.say("You have also completed three assignments on Coursera.");
  tts.say("But still needs to write a short essay about your hometown for the language course.");
  tts.say("The essay should have at least one thousand words.");
  tts.say("You can write the beautiful scene about your hometown.");
  tts.say("Alternatively, you can also write the interesting people in your hometown.");
  tts.say("Oh. The teacher stressed that you can not copy any contents from the website.");

  qi::os::msleep(200u);
  engagementBasedAction("Remember to submit it before August the twelfth.");

  tts.say("Another imporant item on your to do list is that");
  tts.say("you have to prepare for your language course presentation.");
  tts.say("this presentation should have something to do with your current research.");
  tts.say("It can be paper digestion, technology digestion, or book digestion.");
  tts.say("It is up to you to choose the topic.");

  qi::os::msleep(200u);
  engagementBasedAction("It must last at least for fifteen minutes.");

  tts.say("OK. Not much left on the plate. Proud of you.");
  qi::os::msleep(200u);
  tts.say("Enjoy the rest of then evening. Bye!");
}
