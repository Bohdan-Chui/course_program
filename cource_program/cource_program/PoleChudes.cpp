#include "PoleChudes.h"

void PoleChudes::showEnteredLetters()
{
	cout << "Your entered letters: ";
	if (numberOfEnteredLetters) {
		for (int i = 0; i < numberOfEnteredLetters; i++) {
			cout << enteredLetters[i] << ' ';
		}
	}
	else cout << "no letters";
}

void PoleChudes::enterWordAndGreeting()
{
	cout << "Hello my dear player, welcome\n\n";
	cout << "Please, enter word\n";
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
		cout << "\n\nThe current state of the word  : " << guessWordByUser;
		fillWord(guessWordByUser, enterLetter());
		system("cls");
	}

	cout << "You won, guessed word: " << guessWordByUser << "\nBue!";
	return;


}

char PoleChudes::enterLetter()
{
	char letter;
	bool ind;
	cout << "\n enter your letter \n";
	cin >> letter;
	do {
		ind = false;
		for (int i = 0; i != numberOfEnteredLetters; i++) {
			if (letter == enteredLetters[i]) {
				cout << "\nletter " << letter << " is already enterred\nEnter enother one: ";
				ind = true;
				cin >> letter;
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
				cout << "Error. Wrong entering.\nTry again\n";
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
