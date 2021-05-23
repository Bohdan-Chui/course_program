#include "PoleChudes.h"

/*void PoleChudes::playWithFriend()   
{
	userWord = enteringWord();
	system("cls");
	someCalculating();
	letsPlay();
}

void PoleChudes::playWithComputer()
{
	userWord = randomWord();
	system("cls");
	someCalculating();
	letsPlay();
}*/

void PoleChudes::play(bool playerOrComputer) {
	userWord = playerOrComputer? randomWord(): enteringWord();
	system("cls");
	someCalculating();
	letsPlay();
	final();
}

string PoleChudes::enteringWord()
{
	string word;
	bool ind;
	do {
		system("cls");
		gotoXY(25, 5);
		cout << "Welcome\n\n";
		gotoXY(16, 7);
		cout << "Please, enter one correct word";
		gotoXY(20, 9);
		ind = false;
		getline(cin, word);
		for (char& c : word) {//пробігаємо по слову
			if (!isalpha(c)) {
				ind = true;
			}
		}

		if (word[0] == '\0')
			ind = true;
	} while (ind);

	return word;
}

string PoleChudes::randomWord()
{
	string result;
	try {
		srand((unsigned int)time(0));
		int random = rand() % numberOfWordsInFile + 1;
		ifstream in("words.txt");
		in.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);

		for (int i = 0; i < random; i++) {
			getline(in, result);
		}
		in.close();
	}
	catch (std::exception const& e) {
		system("cls");
		cout << "There was an error: " << e.what() << endl;
		system("pause>null");
	}
	return result;
}

void PoleChudes::someCalculating()
{
	wordLenght = userWord.length();
	guessWordByUser = userWord;
	minAttemptions = minSteps(userWord);
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

int PoleChudes::minSteps(string word)
{
	int count = 0;
	for (int i = 0; i < wordLenght; i++) //ітерація по слову
		if (word.find(word[i], i + 1) != string::npos)
			count++;
	return wordLenght - count;
}

void PoleChudes::letsPlay()
{
	while (numberOfGuessedLetters < wordLenght) {
		gotoXY(20, 2); cout << "POLE CHUDES";
		gotoXY(5, 4);
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -";
		gotoXY(5, 5);
		cout << "|\tmin steps " << minAttemptions << "\t|\t" << "you used " << numberOfEnteredLetters << " attemps\t|\n";
		gotoXY(5, 6);
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -";
		gotoXY(5, 8);
		showEnteredLetters();
		gotoXY(5, 9);
		cout << "\n\nThe current state of the word: " << guessWordByUser;
		fillWord(enterLetter());
		system("cls");
	}
	return;
}

void PoleChudes::fillWord(char letter)
{
	for (int i = 0; i < wordLenght; i++) {
		if (letter == userWord[i]) {
			guessWordByUser[i] = letter;
			numberOfGuessedLetters++;
		}
	}
}

void PoleChudes::showEnteredLetters()
{
	cout << "Your entered letters: ";
	if (numberOfEnteredLetters) {
		for (int i = 0; i < numberOfEnteredLetters; i++) {
			cout << enteredLetters[i] << ' ';
		}
	}
	else cout << "no letters\n\n";
}

char PoleChudes::enterLetter()
{
	char letter;
	bool ind;
	cout << "\nEnter one of few letters: ";
	letter = getLetterFromUser();
	do {
		ind = false;
		for (int i = 0; i != numberOfEnteredLetters; i++) {
			if (letter == enteredLetters[i]) {
				cout << "\nLetter '" << letter << "' is already enterred\nEnter enother one: ";
				ind = true;
				letter = getLetterFromUser();
			}
		}
	} while (ind);

	numberOfEnteredLetters++;
	enteredLetters[numberOfEnteredLetters - 1] = letter;

	return letter;
}

char PoleChudes::getLetterFromUser()
{
	char a;
	bool ind;

	do {
		cin >> a;
		if (isalpha(a)) {
			ind = false;
		}
		else {
			ind = true;
			cout << "\nThat`s exactly not a letter\nTry again: ";
		}
	} while (ind);

	if (isupper(a)) {
		a = tolower(a);
	}
	return a;
}

void PoleChudes::final() {
	gotoXY(0, 2);
	cout << "          ..    ..    ....    ..   ..          ..               ..    ..    ..     .." << endl;
	cout << "           ..  ..    .    .   ..   ..           ..             ..     ..    .. .   .." << endl;
	cout << "             ..      .    .   ..   ..            ..     .     ..      ..    ..  .  .." << endl;
	cout << "             ..      .    .   ..   ..             ..  .. ..  ..       ..    ..   . .." << endl;
	cout << "             ..       ....     .....               ...     ...        ..    ..     .." << endl;
	gotoXY(7, 10);
	cout << "Guessed word: " << guessWordByUser;
	gotoXY(7, 12);
	cout << "You used " << numberOfEnteredLetters << " attemptions";
	gotoXY(7, 13);
	cout << "Minimal attemptions for this word " << minAttemptions;
	gotoXY(7, 16);
	cout << "Bye!";
	gotoXY(5, 19);
	cout << "Use <Enter> to menu";

	system("pause>nul");
	GetAsyncKeyState(VK_RETURN);
}