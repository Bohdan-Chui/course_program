#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;
#define numberOfWordsInFile 4
#define Letters 26 //alfabet letters
#define MaxLettersInWord 15


class PoleChudes
{
	string userWord, guessWordByUser;
	char enteredLetters[Letters];
	int wordLenght, numberOfGuessedLetters, numberOfEnteredLetters, minAttemptions;
	COORD CursorPosition;
public:
	void showEnteredLetters();
	void playWithFriend();
	void someCalculating();
	void letsPlay();
	char enterLetter();
	void fillWord(string& word, char letter);
	string enteringWord();
	char getLetterFromUser();
	int minSteps(string word);
	string getword();
	void gotoXY(int, int);
	void playWithComputer();
	string randomWord();
	int getUsedAttemption();
	int getMinAttemption();

};

class Menu :public PoleChudes
{
	int menu_item, run, x;
	bool running = true;
public:
	void menu();
	void howToPlay();
	void final(string, int, int);
};