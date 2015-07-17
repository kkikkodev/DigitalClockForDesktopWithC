#include <windows.h>
#include <stdio.h>
#include "Util.h"

#define CURSOR_SIZE 30
#define COMMAND_SIZE 256

#define DIGITAL_PATTERNS_TO_PRINT_LENGTH 11
#define DIGITAL_PATTERNS_TO_PRINT_ROW 5
#define DIGITAL_PATTERNS_TO_PRINT_COL 3

const static char digitalPatternsToPrint[DIGITAL_PATTERNS_TO_PRINT_LENGTH][DIGITAL_PATTERNS_TO_PRINT_ROW][DIGITAL_PATTERNS_TO_PRINT_COL] = {
	{ // 0
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }
	},
	{ // 1
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 }
	},
	{ // 2
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 },
		{ 1, 0, 0 },
		{ 1, 1, 1 }
	},
	{ // 3
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 }
	},
	{ // 4
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	},
	{ // 5
		{ 1, 1, 1 },
		{ 1, 0, 0 },
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 }
	},
	{ // 6
		{ 1, 0, 0 },
		{ 1, 0, 0 },
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }
	},
	{ // 7
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	},
	{ // 8
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }
	},
	{ // 9
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	},
	{ // :
		{ 0, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 0 }
	}
};

void CursorUtil_GotoXY(int x, int y){
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorUtil_Show(){
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = TRUE;
	cursorInfo.dwSize = CURSOR_SIZE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void CursorUtil_Hide(){
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void WindowUtil_ChangeWindowSize(int lines, int cols){
	char command[COMMAND_SIZE] = { '\0', };
	sprintf(command, "mode con: lines=%d cols=%d", lines, cols);
	system(command);
}

void FontUtil_ChangeFontColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ScreenUtil_ClearRectangle(int leftTopX, int leftTopY, int width, int height){
	int i;
	int j;
	CursorUtil_GotoXY(leftTopX, leftTopY++);
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			printf(" ");
		}
		CursorUtil_GotoXY(leftTopX, leftTopY++);
	}
}

void DigitalPattern_Print(int x, int y, int digitalPattern, int digitalPatternType){
	int i = 0;
	int j = 0;
	for (i = 0; i < digitalPatternType; i++){
		x += 8;
	}
	if (!(digitalPattern >= 0 && digitalPattern <= 9)){
		digitalPattern = DIGITAL_PATTERNS_TO_PRINT_LENGTH - 1;
	}
	CursorUtil_GotoXY(x, y++);
	for (i = 0; i < DIGITAL_PATTERNS_TO_PRINT_ROW; i++){
		for (j = 0; j < DIGITAL_PATTERNS_TO_PRINT_COL; j++){
			if (digitalPatternsToPrint[digitalPattern][i][j]){
				printf("бс");
			}
			else{
				printf("  ");
			}
		}
		CursorUtil_GotoXY(x, y++);
	}
}