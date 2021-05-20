#pragma once
#include <iostream>
#include <string>
using namespace std;
#define Letters 26 //alfabet letters
#define MaxLettersInWord 15


class PoleChudes
{
	string userWord, guessWordByUser;
	char enteredLetters[Letters];
	int wordLenght, numberOfGuessedLetters, numberOfEnteredLetters;
public:
	void showEnteredLetters();
	void enterWordAndGreeting();
	void someCalculating();
	void letsPlay();
	char enterLetter();
	void fillWord(string& word, char letter);
	string enteringWord();
};

