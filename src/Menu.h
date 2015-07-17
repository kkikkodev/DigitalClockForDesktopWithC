#ifndef _MENU_H
#define _MENU_H

#include "Point.h"

#define MENU_ITEMS_COUNT 20
#define MENU_ITEMS_CONTENT_SIZE 128

typedef struct _menu{
	char items[MENU_ITEMS_COUNT][MENU_ITEMS_CONTENT_SIZE];
	int count;
	int selectedIndex;
	Point startPositionToPrint;
	int menuColor;
	int isActivated; // if this is true, key input of menu is processed, otherwise, not key input of menu but key input of other module is processed
}Menu;

void Menu_Create(Menu* menu, char(*items)[MENU_ITEMS_CONTENT_SIZE], int count, int startPositionXToPrint, int startPositionYToPrint, int menuColor);
void Menu_Print(Menu menu);
int Menu_ProcessKey(Menu* menu);
const char* Menu_GetSelectedContent(Menu menu);
void Menu_SetIsActivated(Menu* menu, int isActivated);
const int Menu_GetIsActivated(Menu menu);

#endif