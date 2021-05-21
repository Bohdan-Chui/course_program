#include "PoleChudes.h"

void PoleChudes::enterWordAndGreeting()   
{
	cout << "hello my dear player, welcome\n\n";
	cout << "please, enter word\n";
	userWord = enteringWord();
	system("cls");
	someCalculating();
}

string PoleChudes::enteringWord()
{
	string word;
	bool ind;
	do {
		ind = false;
		getline(cin, word);
		for (char& c : word) {//пробігаємо по слову
			if (!isalpha(c)) {
				ind = true;
			}
		}
		if (ind) {
			cout << "that`s not one correct word.\nTry again, do it correctly\n";
		}
	} while (ind);

	return word;

}

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



void PoleChudes::someCalculating()
{
	wordLenght = userWord.length();
	guessWordByUser = userWord;
	for (int i = 0; i < wordLenght; i++) {
		guessWordByUser[i] = '_';
	}
	numberOfGuessedLetters = 0;
	numberOfEnteredLetters = 0;

	for (int i = 0; i < wordLenght; i++) {
		if (isupper(userWord[i])) {
			userWord[i] = tolower(userWord[i]);
		}
	}

}

void PoleChudes::letsPlay()
{
	while (numberOfGuessedLetters < wordLenght) {
		cout << "min steps " << minSteps(userWord) << "\t\t" << "you done " << numberOfEnteredLetters << " attemps\n\n" ;
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


 char PoleChudes::getLetterFromUser()
{
	char a;
	bool ind;

	do {
		cin >> a;
		if (isalpha(a)){
			ind = false;
		}
		else {
			ind = true;
			cout << "\nthat`s exactly not a letter\nTry again: ";
		}
	} while (ind);

	if (isupper(a)) {
		a = tolower(a);
	}
	return a;
}

 int PoleChudes::minSteps(string word)
 {
	 int count = 0;
	 for (int i = 0; i < wordLenght; i++) //ітерація по слову
		 if (word.find(word[i], i+1) != string::npos)
			 count ++;
	 return wordLenght - count;

 }
