#ifndef _NORMAL_CLOCK_MANAGER_H
#define _NORMAL_CLOCK_MANAGER_H

#include "Date.h"
#include "Time.h"

typedef struct _normalClockManager{
	Date currentDate;
	Time currentTime;
}NormalClockManager;

void NormalClockManager_Print(NormalClockManager* normalClockManager);

#endif