#ifndef HUMAN_STATE_H
#define HUMAN_STATE_H

#include "interface.h"

#include <unistd.h>

enum HumanState {ENGAGED, QUSI_ENGAGED, PSEUDO_DIS_ENGAGED, DIS_ENGAGED};

HumanState getHumanState();

#endif
