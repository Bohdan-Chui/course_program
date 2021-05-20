#include "PoleChudes.h"

void PoleChudes::showEnteredLetters()
{
	cout << "your entered letters: ";
	if (numberOfEnteredLetters) {
		for (int i = 0; i < numberOfEnteredLetters; i++) {
			cout << enteredLetters[i] << ' ';
		}
	}
	else cout << "no letters\n\n";
}

void PoleChudes::enterWordAndGreeting()
{
	cout << "hello my dear player, welcome\n\n";
	cout << "please, enter word\n";
	userWord = enteringWord();
	system("cls");
	someCalculating();
}

void PoleChudes::someCalculating()
{
	wordLenght = userWord.length();
	guessWordByUser = userWord;
	for (int i = 0; i < wordLenght; i++) {
		guessWordByUser[i] = '_';
	}
	numberOfGuessedLetters = 0;
	numberOfEnteredLetters = 0;
}

void PoleChudes::letsPlay()
{
	while (numberOfGuessedLetters < wordLenght) {

		showEnteredLetters();
		cout << "\n\nthe current state of the word  : " << guessWordByUser;
		fillWord(guessWordByUser, enterLetter());
		system("cls");
	}

	cout << "you won, guessed word: " << guessWordByUser << "\n bue!";
	return;


}

char PoleChudes::enterLetter()
{
	char letter;
	bool ind;
	cout << "\n enter your letter \n";
	letter = getLetterFromUser();
	do {
		ind = false;
		for (int i = 0; i != numberOfEnteredLetters; i++) {
			if (letter == enteredLetters[i]) {
				cout << "\nletter " << letter << " is already enterred\nEnter enother one: ";
				ind = true;
				letter = getLetterFromUser();
			}
		}
	} while (ind);

	numberOfEnteredLetters++;
	enteredLetters[numberOfEnteredLetters - 1] = letter;

	return letter;
}

void PoleChudes::fillWord(string& word, char letter)
{
	for (int i = 0; i < wordLenght; i++) {
		if (letter == userWord[i]) {
			guessWordByUser[i] = letter;
			numberOfGuessedLetters++;

		}

	}

}

string PoleChudes::enteringWord()
{
	char c, a[MaxLettersInWord];
	bool ind;
	int i;
	do {
		ind = true;
		i = 0;
		while ((c = getchar()) != '\n') {
			if (!(c >= 'a' && c <= 'z') && ind) {
				ind = false;
				cout << "that`s not one correct word.\nTry again, do it correctly\n";
			}
			else {
				a[i] = c;
				i++;
			}
		}
	} while (!ind);

	a[i] = '\0';
	return string(a);

}

 char PoleChudes::getLetterFromUser()
{
	char a;
	bool ind;

	do {
		cin >> a;
		if (a >= 'a' && a <= 'z'){
			ind = false;
		}
		else {
			ind = true;
			cout << "\nthat`s exactly not a letter\nTry again: ";
		}
	} while (ind);
	return a;
}
