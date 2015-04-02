#include "DigitalClock.h"
#include "Util.h"

static void _InitDigitalClockSetting();

int main(){
	_InitDigitalClockSetting();
	while (TRUE){
		DigitalClock_Print(DigitalClock_GetTime());
	}
	return 0;
}

static void _InitDigitalClockSetting(){
	WindowUtil_ChangeWindowSize(WINDOW_LINE_SIZE, WINDOW_COL_SIZE);
	FontUtil_ChangeFontColor(LIGHT_GREEN);
	CursorUtil_Hide();
}