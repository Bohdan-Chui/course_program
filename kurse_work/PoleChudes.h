#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <time.h>

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
	void gotoXY(int, int);

	void play(bool playerOrComputer);
		string enteringWord();
		string randomWord();

		void someCalculating();
			int minSteps(string word);

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