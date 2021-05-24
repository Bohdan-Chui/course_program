#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <cctype>

using namespace std;
#define numberOfWordsInFile 4
#define Letters 26 //alphabet letters
#define MaxLettersInWord 15


class PoleChudes
{
	string userWord, guessWordByUser;
	char enteredLetters[Letters];
	int wordLenght, numberOfGuessedLetters, numberOfEnteredLetters, minAttemptions;
	COORD CursorPosition;
public:
	void gotoXY(int x, int y);

	void play(bool computerOrPlayer);
		string randomWord();
		string enteringWord();

		void someCalculating();
			int minSteps();

		void letsPlay();
			void showEnteredLetters();
			void fillWord(char letter);
				char enterLetter();
					char getLetterFromUser();	
	
		void final();
};

class Menu :public PoleChudes
{
	int menu_item, run, x;
	bool running = true;
public:
	void menu();
		void howToPlay();
	
};