#include "human_state.h"

HumanState getHumanState()
{
  bool bGaze = isLookingatMe();
  bool bFeedback = hasFeedback();

  if(bGaze==true/* && bFeedback==true*/)
    return ENGAGED;

  if(bGaze==false && bFeedback==true)
    return QUSI_ENGAGED;

  for(int k=0; k<60; ++k)
  {
    usleep(100);
    bFeedback = hasFeedback();
    if(bFeedback==true)
      return PSEUDO_DIS_ENGAGED;
  }
  return DIS_ENGAGED;
}
