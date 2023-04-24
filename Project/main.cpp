// main.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "GameLib/GameLib.h"
#include "GameLib/ANSI/ANSI.h"
#include <stdbool.h>
#include <time.h>

using namespace std;

void gameMenu(struct playerData* player);
void cryoRoom(struct playerData* player);
void mechanicalRoom(struct playerData* player);
void navigationRoom(struct playerData* player);
void bridgeRoom(struct playerData* player);
void pressEnter(unsigned int row);
unsigned int nextPrime(unsigned int number);
bool isPrime(unsigned int number);

const char* textFile = "data/text.dat";
const char* nameFile = "data/name.dat";
const char* mapFile = "data/map.dat";

struct playerData {
	char name[15];
	bool key;
	bool repairedEl;
	int coordinationsA[3];
	int coordinationsB[3];
	bool visitedMech;
	bool visitedNav;
	bool visitedBridge;
};

int main()
{
	struct playerData player;

	setup("Destination Unknown", 100, 30);
	clearScreen();
	gameMenu(&player);
	
	clearScreen();
	printArtFile(mapFile, 20, 1);

	if (!player.visitedMech)cryoRoom(&player);
	if (!player.visitedNav)mechanicalRoom(&player);
	if (!player.visitedBridge)navigationRoom(&player);
	bridgeRoom(&player);

	close();
	return 0;
}

void gameMenu(struct playerData* player) {
	printArtFile(nameFile, 8, 3);
	printMenu(43, 20, 3, "Nova hra", "Nacist hru", "Konec");
	unsigned int choice;
	choice = numAnswer(1, 3);
	absoluteCursorPosition(43, 20);
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, WHITE);
	eraseViewport(CURSOR_TO_END);

	switch (choice) {
	//zalozeni nove postavy
	case 1:
		printTextFile(textFile, 1, 1, 24);
		printInputBox();
		scanf("%14s", player->name);
		while (getchar() != '\n');
		printInputBox();
		player->key = 0;
		player->repairedEl = 0;
		for (int s = 0; s < 3; s++) {
			player->coordinationsA[s] = 0;
			player->coordinationsB[s] = 0;
		}
		player->visitedMech = 0;
		player->visitedNav = 0;
		player->visitedBridge = 0;

		saveGame(player, sizeof(struct playerData));
		break;

	//nasteni postavy
	case 2:
		loadGame(player, sizeof(struct playerData));
		break;

	//ukonceni hry
	case 3:
		close();
		break;
	}

	//uvod do pribehu
	if (choice == 1) {
		clearScreen();
		printTextFile(textFile, 2, 0, 2);
		printTextFile(textFile, 3, 0, 6);
		pressEnter(10);
	}
}

void cryoRoom(struct playerData* player) {
	unsigned int choice, first, second, third;
	setColor(BRIGHT_FOREGROUND, WHITE);
	printTextFile(textFile, 5, 0, 20);
	pressEnter(25);

	start:
	printMenu(3, 20, 3, "Odejit do strojovny", "Podivat se na stul", "Podivat se na skrinku");

	choice = numAnswer(1, 3);
	switch (choice) {
	//odejti do strojovny
	case 1:
		if (player->key) return;
		else {
			setColor(BACKGROUND, BLACK);
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 6, 0, 20);
			pressEnter(23);
			goto start;
		}
		break;
	
	//stul
	case 2:
		setColor(BACKGROUND, BLACK);
		setColor(BRIGHT_FOREGROUND, WHITE);
		printTextFile(textFile, 7, 0, 20);
		pressEnter(22);
		goto start;
		break;
	
	//skrinka
	case 3:
		if (player->key) {
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 29, 0, 20);
			pressEnter(22);
			goto start;
		}
		setColor(BACKGROUND, BLACK);
		setColor(BRIGHT_FOREGROUND, WHITE);
		printTextFile(textFile, 8, 0, 20);

		//zadani kombinace
		setColor(FOREGROUND, WHITE);
		printTextFile(textFile, 9, 1, 22);
		printInputBox();
		first = numAnswer(1, 9);
		setColor(FOREGROUND, WHITE);
		printTextFile(textFile, 10, 1, 22);
		printInputBox();
		second = numAnswer(1, 9);
		setColor(FOREGROUND, WHITE);
		printTextFile(textFile, 11, 1, 22);
		printInputBox();
		third = numAnswer(1, 9);

		//kontrola kombinace
		if (first == 8 && second == 5 && third == 7) {
			player->key = 1;
			saveGame(player, sizeof(struct playerData));
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 13, 0, 20);
			pressEnter(24);
			goto start;
		}
		else {
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 12, 0, 20);
			pressEnter(22);
			goto start;
		}
		break;
	}
}

void mechanicalRoom(struct playerData* player) {
	player->visitedMech = 1;
	saveGame(player, sizeof(struct playerData));
	unsigned int choice;
	bool tryAnswer;
	setColor(BRIGHT_FOREGROUND, WHITE);
	printTextFile(textFile, 14, 0, 20);
	pressEnter(23);

	start:
	printMenu(3, 20, 3, "Odejit na mustek", "Odejit do navigace", "Zkotrolovat ovladaci panel generatoru");

	choice = numAnswer(1, 3);
	switch (choice) {
	//odejit na mustek
	case 1:
		if (!player->repairedEl) {
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 15, 0, 20);
			pressEnter(22);
			goto start;
		}

		else {
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 24, 0, 20);
			pressEnter(22);
			goto start;
		}
			
		break;

	//odejit do navigace
	case 2:
		if (player->repairedEl) return;
		else {
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 15, 0, 20);
			pressEnter(22);
			goto start;
		}
		break;

	//kontrola ovaldaciho panelu
	case 3:
		if (player->repairedEl) {
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 29, 0, 20);
			pressEnter(22);
			goto start;
		}
		setColor(BRIGHT_FOREGROUND, WHITE);
		printTextFile(textFile, 16, 0, 20);
		setColor(FOREGROUND, WHITE);
		printTextFile(textFile, 17, 1, 23);
		printInputBox();
		tryAnswer = boolAnswer();

		if (tryAnswer) {
			//otazka 1
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 18, 0, 20);
			printMenu(3, 22, 3, "Muze pouzit", "Nesmi pouzit", "Musi pouzit");
			choice = numAnswer(1, 3);
			if (choice == 2) {
				setColor(BRIGHT_FOREGROUND, WHITE);
				printTextFile(textFile, 19, 0, 20);
				pressEnter(22);
			}
			else {
				setColor(BRIGHT_FOREGROUND, WHITE);
				printTextFile(textFile, 20, 0, 20);
				pressEnter(22);
				goto start;
			}

			//otazka 2
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 21, 0, 20);
			printMenu(3, 22, 3, "Cervena", "Zluta", "Cerna");
			choice = numAnswer(1, 3);
			if (choice == 1) {
				setColor(BRIGHT_FOREGROUND, WHITE);
				printTextFile(textFile, 19, 0, 20);
				pressEnter(22);
			}
			else {
				setColor(BRIGHT_FOREGROUND, WHITE);
				printTextFile(textFile, 20, 0, 20);
				pressEnter(22);
				goto start;
			}

			//otazka 3
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 22, 0, 20);
			printMenu(3, 22, 3, "Vsechny pracovni vodice", "Pouze ochranny vodic", "Pouze zemnici vodic");
			choice = numAnswer(1, 3);
			if (choice == 1) {
				setColor(BRIGHT_FOREGROUND, WHITE);
				printTextFile(textFile, 19, 0, 20);
				pressEnter(22);
			}
			else {
				setColor(BRIGHT_FOREGROUND, WHITE);
				printTextFile(textFile, 20, 0, 20);
				pressEnter(22);
				goto start;
			}

			player->repairedEl = 1;
			saveGame(player, sizeof(struct playerData));
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 23, 0, 20);
			pressEnter(22);
			goto start;
		}
		else goto start;

		break;
	}
}

void navigationRoom(struct playerData* player) {
	player->visitedNav = 1;
	saveGame(player, sizeof(struct playerData));
	unsigned int choice;

	start:
	printMenu(3, 20, 2, "Odejit na mustek", "Zjistit souradnice");

	choice = numAnswer(1, 2);
	switch (choice) {
	//odejit na mustek
	case 1:
		if ((player->coordinationsA[0] + player->coordinationsA[1] + player->coordinationsA[2]) && (player->coordinationsB[0] + player->coordinationsB[1] + player->coordinationsB[2])) return;
		else {
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 25, 0, 20);
			pressEnter(22);
			goto start;
			break;
		}

	//zjistit souradnice
	case 2:
		if (!((player->coordinationsA[0] + player->coordinationsA[1] + player->coordinationsA[2]) && (player->coordinationsB[0] + player->coordinationsB[1] + player->coordinationsB[2]))) {
			srand(time(NULL));
			int rNum;

			//aktualni souradnice
			for (int c = 0; c < 3; c++) {
				rNum = rand() % 20;
				player->coordinationsA[c] = rNum;
			}

			//souradnice cile
			for (int c = 0; c < 3; c++) {
				rNum = rand() % 20;
				player->coordinationsB[c] = rNum;
			}
			saveGame(player, sizeof(struct playerData));
		}

		//tisk souradnic
		setColor(BRIGHT_FOREGROUND, WHITE);
		printTextFile(textFile, 28, 0 ,20);
		printTextFile(textFile, 26, 0, 21);
		printf("[%d; %d; %d]", player->coordinationsA[0], player->coordinationsA[1], player->coordinationsA[2]);
		printTextFile(textFile, 27, 0, 24);
		printf("[%d; %d; %d]", player->coordinationsB[0], player->coordinationsB[1], player->coordinationsB[2]);
		pressEnter(27);
		goto start;
		break;
	}
}

void bridgeRoom(struct playerData* player) {
	player->visitedBridge = 1;
	saveGame(player, sizeof(struct playerData));
	unsigned int choice, firstC, secondC, thirdC, firstCC, secondCC, thirdCC, firstP, secondP, thirdP;

	start:
	printMenu(3, 20, 2, "Zadat souradnice", "Jit se znovu podivat na souradnice");

	choice = numAnswer(1, 2);
	switch (choice) {
	//zadani souradnic
	case 1:
		//prvni souradnice
		setColor(FOREGROUND, WHITE);
		printTextFile(textFile, 30, 1, 20);
		printInputBox();
		firstC = numAnswer(-20, 20);

		//druha souradnice
		setColor(FOREGROUND, WHITE);
		printTextFile(textFile, 31, 1, 20);
		printInputBox();
		secondC = numAnswer(-20, 20);

		//treti souradnice
		setColor(FOREGROUND, WHITE);
		printTextFile(textFile, 32, 1, 20);
		printInputBox();
		thirdC = numAnswer(-20, 20);

		firstCC = player->coordinationsB[0] - player->coordinationsA[0];
		secondCC = player->coordinationsB[1] - player->coordinationsA[1];
		thirdCC = player->coordinationsB[2] - player->coordinationsA[2];

		//konec hry
		if (firstC == firstCC && secondC == secondCC && thirdC == thirdCC) {
			srand(time(NULL));
			int rNum = rand() % 50;
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 34, 0, 20);
			printf("%u", rNum);

			//zadani prvocisel
			setColor(FOREGROUND, WHITE);
			printTextFile(textFile, 36, 1, 23);
			printInputBox();
			firstP = numAnswer(0, 100);
			setColor(FOREGROUND, WHITE);
			printTextFile(textFile, 37, 1, 23);
			printInputBox();
			secondP = numAnswer(0, 100);
			setColor(FOREGROUND, WHITE);
			printTextFile(textFile, 38, 1, 23);
			printInputBox();
			thirdP = numAnswer(0, 100);

			//kontrola prvocisel
			if (firstP != nextPrime(rNum) || secondP != nextPrime(firstP) || thirdP != nextPrime(secondP)) {
				setColor(BRIGHT_FOREGROUND, WHITE);
				printTextFile(textFile, 39, 0, 20);
				pressEnter(22);
				goto start;
			}

			//uspesne ukonceno
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 35, 0, 20);
			pressEnter(23);
			for (int t = 20; t > 0; t--) {
				printArtFile(mapFile, t, 1);
				uSleep(10);
			}
			clearScreen();
			printArtFile(nameFile, 8, 3);
			printTextFile(textFile, 40, 1, 17);
			pressEnter(20);
			close();
		}
		else {
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 33, 0, 20);
			pressEnter(22);
			goto start;
		}
		break;

	//opetovne zobrazeni souradnic
	case 2:
		setColor(BRIGHT_FOREGROUND, WHITE);
		printTextFile(textFile, 26, 0, 20);
		printf("[%d; %d; %d]", player->coordinationsA[0], player->coordinationsA[1], player->coordinationsA[2]);
		printTextFile(textFile, 27, 0, 23);
		printf("[%d; %d; %d]", player->coordinationsB[0], player->coordinationsB[1], player->coordinationsB[2]);
		pressEnter(26);
		
		goto start;
		break;
	}
}

void pressEnter(unsigned int row) {
	hideCursor(1);
	setColor(FOREGROUND, WHITE);
	printTextFile(textFile, 4, 1, row);
	while (getchar() != '\n');
	hideCursor(0);
}

unsigned int nextPrime(unsigned int number) {
	if (number < 2) return 2;
	for (unsigned int p = number + 1;; p++) {
		if(isPrime(p)) return p;
	}
}

bool isPrime(unsigned int number) {
	if (number < 2) return 0;
	if (number == 2 || number == 3) return 1;

	if (!(number % 2) || !(number % 3)) return 0;

	for (unsigned int n = 5; (n * n) <= number; n += 6) {
		if (!(number % n) || !(number % (n + 2))) return 0;
	}

	return 1;
}