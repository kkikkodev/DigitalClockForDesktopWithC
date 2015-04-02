#ifndef _UTIL_H
#define _UTIL_H

#define WINDOW_LINE_SIZE 9
#define WINDOW_COL_SIZE 66

enum FontColor{
	BLACK, BLUE, GREEN, JADE, RED, PURPLE, YELLOW, WHITE, GRAY,
	LIGHT_BLUE, LIGHT_GREEN, LIGHT_JADE, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE
};

void CursorUtil_GotoXY(int x, int y);
void CursorUtil_Hide();
void WindowUtil_ChangeWindowSize(int lines, int cols);
void FontUtil_ChangeFontColor(int color);

#endif