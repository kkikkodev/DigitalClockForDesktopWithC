#include "DigitalClockView.h"
#include "Constant.h"

// use as global variable because activate main menu key input when ring or stop alarm
DigitalClockView digitalClockView;

int main(int argc, char* argv[]){
	DigitalClockView_Init(&digitalClockView);
	do{
		if (DigitalClockView_IsRinging(digitalClockView)){
			DigitalClockView_StopAlarm(&digitalClockView);
		}
		DigitalClockView_ProcessMainMenu(&digitalClockView);
		switch (digitalClockView.selectedMainMenu){
		case NORMAL_CLOCK_MAIN_MENU:
			DigitalClockView_ShowNormalClock(&digitalClockView);
			break;
		case ALARM_CLOCK_MAIN_MENU:
			DigitalClockView_ShowAlarmClock(&digitalClockView);
			break;
		}
	} while (digitalClockView.selectedMainMenu != EXIT_MAIN_MENU);
	return 0;
}