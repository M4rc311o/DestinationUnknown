#pragma once
#include "ANSIMacros.h"
#include <stdarg.h>
#include <stdbool.h>

//console properties
int setupConsole(unsigned int columns, unsigned int rows);
int restoreConsole();
void setWindowTitle(const char* title);

//colors, styles, ...
void setColor(unsigned int FBground, unsigned int color);
void setStyle(unsigned int count, ...);

//cursor
void relativeCursorPosition(short columns, short rows);
void absoluteCursorPosition(short columns, short rows);	//if the value is set to 0 than parameter is ignored
void saveCursorPosisiton();
void restoreCursorPosition();
void blinkCursor(bool blink);
void hideCursor(bool hide);
void shapeCursor(unsigned int shape);

//viewport
void scrollUp(int rows);
void scrollDown(int rows);
void eraseViewport(unsigned int mode);
void scrollMargins(unsigned int top, unsigned int bottom);
void alternateBuffer(bool alternate);

//text
void insertCharacter(unsigned int count);
void deleteCharacter(unsigned int count);
void insertLine(unsigned int count);
void deleteLine(unsigned int count);
void eraseLine(unsigned int mode);