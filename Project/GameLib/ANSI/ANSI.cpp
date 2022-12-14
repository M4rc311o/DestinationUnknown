#include "ANSI.h"
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>

static HANDLE STDOut;
static DWORD outModeOriginal;

int setupConsole(unsigned int columns, unsigned int rows) {
	STDOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (STDOut == INVALID_HANDLE_VALUE) return -1;

	DWORD outMode = 0;
	if (!GetConsoleMode(STDOut, &outModeOriginal)) return -1;

	outMode = outModeOriginal | ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(STDOut, outMode)) return -1;

	printf_s("\x1b[8;%u;%ut", rows, columns);

	return 0;
}

int restoreConsole() {
	if (!SetConsoleMode(STDOut, outModeOriginal)) return -1;
	printf_s("\x1b[0m");
	return 0;
}

#else
int setupConsole(unsigned int columns, unsigned int rows) {
	printf_s("\x1b[8;%u;%ut", rows, columns);
	return 0;
}
int restoreConsole() {
	printf_s("\x1b[0m");
	return 0;
}
#endif

void setColor(unsigned int FBground, unsigned int color){
	if (color == DEFAULT_COLOR) {
		if (FBground == BRIGHT_FOREGROUND) FBground = FOREGROUND;
		if (FBground == BRIGHT_BACKGROUND) FBground = BACKGROUND;
	}
	printf_s("\x1b[%u%um", FBground, color);
}

void setStyle(unsigned int count, ...) {
	va_list styles;
	va_start(styles, count);

	unsigned int style;
	for (unsigned int s = 0; s < count; s++) {
		style = va_arg(styles, unsigned int);
		printf_s("\x1b[%um", style);
	}

	va_end(styles);
}

void setWindowTitle(const char* title) {
	printf_s("\x1b]0;");
	for (unsigned int c = 0; title[c] != '\0'; c++) printf_s("%c", title[c]);
	printf_s("\x07");
}

void saveCursorPosisiton() {
	printf_s("\x1b");
	printf_s("7");
}

void restoreCursorPosition() {
	printf_s("\x1b");
	printf_s("8");
}

void relativeCursorPosition(short columns, short rows) {
	if (columns > 0) printf_s("\x1b[%uC", columns);
	else if (columns < 0) printf_s("\x1b[%uD", -columns);
	if (rows > 0) printf_s("\x1b[%uA", rows);
	else if (rows < 0) printf_s("\x1b[%uB", -rows);
}

void absoluteCursorPosition(short columns, short rows) {
	if (columns && rows) printf_s("\x1b[%u;%uH", rows, columns);
	else if (!columns && rows) printf_s("\x1b[%ud", rows);
	else if (columns && !rows) printf_s("\x1b[%uG", columns);
}

void blinkCursor(bool blink) {
	if (blink) printf_s("\x1b[?12h");
	else printf_s("\x1b[?12l");
}

void hideCursor(bool hide) {
	if (hide) printf_s("\x1b[?25l");
	else printf_s("\x1b[?25h");
}

void shapeCursor(unsigned int shape) {
	printf_s("\x1b[%u\x20\x71", shape);
}

void scrollUp(int rows) {
	printf_s("\x1b[%uS", rows);
}

void scrollDown(int rows) {
	printf_s("\x1b[%uT", rows);
}

void insertCharacter(unsigned int count) {
	printf_s("\x1b[%u@", count);
}

void deleteCharacter(unsigned int count) {
	printf_s("\x1b[%uP", count);
}

void insertLine(unsigned int count) {
	printf_s("\x1b[%uL", count);
}

void deleteLine(unsigned int count) {
	printf_s("\x1b[%uM", count);
}

void eraseViewport(unsigned int mode) {
	printf_s("\x1b[%uJ", mode);
}

void eraseLine(unsigned int mode) {
	printf_s("\x1b[%uK", mode);
}

void scrollMargins(unsigned int top, unsigned int bottom) {
	printf_s("\x1b[%u;%ur", top, bottom);
}

void alternateBuffer(bool alternate) {
	if (alternate) printf_s("\x1b[?1049h");
	else printf_s("\x1b[?1049l");
}