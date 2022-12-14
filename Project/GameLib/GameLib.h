#pragma once
#include <stdarg.h>
#include <stdbool.h>

void setup(const char* name, unsigned int columns, unsigned int rows);
void close();

void errorMessage(const char* message);
void quickMessage(const char* message);

void printMenu(unsigned int column, unsigned int row, unsigned int count, ...);
void printInputBox();
void printArtFile(const char* file, unsigned int column, unsigned int row);
void printTextFile(const char* file, unsigned int part, bool instant, unsigned int row);

void uSleep(unsigned int ms);
bool boolAnswer();
int numAnswer(int from, int to);

void saveGame(void* playerData, unsigned int size);
void loadGame(void* playerData, unsigned int size);

void clearScreen();