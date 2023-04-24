#include "GameLib.h"
#include "ANSI/ANSI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

static unsigned int COLUMNS;
static unsigned int ROWS;

const char* playerFile = "data/player.dat";

void uSleep(unsigned int ms) {
	#ifdef _WIN32
	Sleep(ms);
	#else
	usleep(ms*1000);
	#endif
}

void errorMessage(const char* message) {
	clearScreen();
	scrollMargins(1, ROWS);
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, RED);
	printf("\nERROR: ");
	setColor(FOREGROUND, WHITE);
	printf("%.255s", message);
	exit(-1);
}

void quickMessage(const char* message) {
	setColor(BRIGHT_BACKGROUND, WHITE);
	setColor(BRIGHT_FOREGROUND, RED);
	printf("%.255s", message);
	setColor(FOREGROUND, BLACK);
	getchar();
	printInputBox();
}

void setup(const char* name, unsigned int columns, unsigned int rows) {
	COLUMNS = columns;
	ROWS = rows;
	if (setupConsole(columns, rows)) {
		errorMessage("chyba pri nastavovani konzole");
	}
	alternateBuffer(1);
	setWindowTitle(name);
	shapeCursor(BLOCK);
	scrollMargins(ROWS - 1, ROWS);
}

void close() {
	clearScreen();
	if (restoreConsole()) {
		errorMessage("chyba pri zavirani konzole");
	}
	scrollMargins(1, ROWS);
	exit(0);
}

void printMenu(unsigned int column, unsigned int row, unsigned int count, ...) {
	absoluteCursorPosition(1, row);
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, WHITE);
	eraseViewport(CURSOR_TO_END);
	va_list choices;
	va_start(choices, count);
	const char* choice;
	for (unsigned int n = 0; n < count; n++) {
		absoluteCursorPosition(column, row + n);
		choice = va_arg(choices, const char*);
		printf("%u: ", n+1);
		printf("%s", choice);
	}
	va_end(choices);
	printInputBox();
}

void printInputBox() {
	absoluteCursorPosition(1, ROWS - 1);
	setColor(BRIGHT_BACKGROUND, WHITE);
	insertLine(1);
	setColor(BACKGROUND, BLACK);
	insertLine(1);
	setColor(BRIGHT_BACKGROUND, WHITE);
	setColor(FOREGROUND, BLACK);
	absoluteCursorPosition(2, ROWS);
	blinkCursor(1);
}

bool boolAnswer() {
	input:
	char answer;
	scanf("%c", &answer);
	while (getchar() != '\n');
	if (answer == 'a' || answer == 'A') {
		printInputBox();
		return 1;
	}

	else if (answer == 'n' || answer == 'N') {
		printInputBox();
		return 0;
	}

	else {
		printInputBox();
		quickMessage("Zadejte platny vstup");
		goto input;
	}
}

int numAnswer(int from, int to) {
	input:
	int answer;
	scanf("%d", &answer);
	while (getchar() != '\n');
	if (answer >= from && answer <= to) {
		printInputBox();
		return answer;
	}

	else {
		printInputBox();
		quickMessage("Zadejte platny vstup");
		goto input;
	}
}

void clearScreen() {
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, WHITE);
	eraseViewport(ALL);
}

void printArtFile(const char* file, unsigned int column, unsigned int row) {
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, WHITE);
	absoluteCursorPosition(column, row);

	char* line;
	line = (char*)malloc(255 * sizeof(char));
	FILE* fG = fopen(file, "r");

	if (!fG) errorMessage("soubor s grafickym obsahem se nepodarilo otevrit");
	while (!feof(fG)) {
		fscanf(fG, "$%254[^\n]\n", line);
		printf("%.255s\n", line);
		absoluteCursorPosition(column, 0);
	}
	fclose(fG);
	free(line);
}

void printTextFile(const char* file, unsigned int part, bool instant, unsigned int row) {
	absoluteCursorPosition(1, row);
	setColor(BACKGROUND, BLACK);
	eraseViewport(CURSOR_TO_END);

	unsigned int textPart = 0;
	char* text;
	text = (char*)malloc(255 * sizeof(char));
	FILE* fT = fopen(file, "r");

	if (!fT) errorMessage("soubor s textovym obsahem se nepodarilo otevrit");
	while (textPart < part && !feof(fT)) fscanf(fT, "%u$%254[^$]$\n", &textPart, text);
	if(instant) printf("%.255s\n", text);

	else {
		for (unsigned t = 0; text[t] != '\0'; t++) {
			printf("%c", text[t]);
			uSleep(10);
		}
		printf("\n");
	}

	fclose(fT);
	free(text);
}

void saveGame(void* playerData, unsigned int size) {
	FILE* fplayer = fopen(playerFile, "wb");

	if (!fplayer) errorMessage("soubor player.dat se nepodarilo otevrit");
	fwrite(playerData, size, 1, fplayer);
	fclose(fplayer);
}

void loadGame(void* playerData, unsigned int size) {
	FILE* fplayer = fopen(playerFile, "rb");

	if (!fplayer) errorMessage("soubor player.dat se nepodarilo otevrit");
	fread(playerData, size, 1, fplayer);
	fclose(fplayer);
}