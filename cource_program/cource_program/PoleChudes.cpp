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
	cout <<"min steps " << minSteps(userWord) << "\n";
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
	string word;
	bool ind;
	do {
		ind = false;
		getline(cin, word);
		for (char& c : word) {
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
	return a;
}

 int PoleChudes::minSteps(string word)
 {
	 //char letters[20];
	 //int count = 0, j;
	 //bool ind;
	 //for (int i = 0; i < wordLenght; i++) {
		// j = 0;
		// ind = true;
		// while (j < count && ind) {
		//	 if (word[i] == letters[j]) {
		//		 ind = false;
		//	 }
		//	 j++;
		// }
		// if (ind) {
		//	 letters[j] = word[i];
		//	 count++;
		// }
	 //}
	 ////cout << count << endl;
	 //return count;

	 int count = 0;
	 for (int i = 0; i < wordLenght; i++) //ітерація по слову
		 if (word.find(word[i], i+1) != string::npos)
			 count ++;
	 return wordLenght - count;


 }
