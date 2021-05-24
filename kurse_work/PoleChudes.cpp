#include "PoleChudes.h"

void PoleChudes::play(bool computerOrPlayer) {
	userWord = computerOrPlayer ? randomWord() : enteringWord();
	system("cls");
	someCalculating();
	letsPlay();
	final();
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
		cout << "Press <enter> to continue";
		system("pause>null");
	}
	return result;
}

string PoleChudes::enteringWord()
{
	string word;
	bool ind;
	do {
		system("cls");
		gotoXY(25, 5);
		cout << "Welcome";
		gotoXY(16, 7);
		cout << "Please, enter one correct word";
		gotoXY(20, 9);
		getline(cin, word);

		ind = false;
		for (char& c : word) {//пробігаємо по слову
			if (!isalpha(c)) {
				ind = true;
			}
		}
		if (word[0] == '\0')
			ind = true;

		if (ind) {
			gotoXY(16, 9);
			cout << "Entering isn't correct";
			gotoXY(5, 19);
			cout << "Use <Enter> to continue";
			system("pause>nul");
			GetAsyncKeyState(VK_RETURN);
		}


	} while (ind);

	return word;
}

void PoleChudes::someCalculating()
{
	wordLenght = userWord.length();
	guessWordByUser = userWord;
	minAttemptions = minSteps();
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

int PoleChudes::minSteps()
{
	int count = 0;
	for (int i = 0; i < wordLenght; i++) //ітерація по слову
		if (userWord.find(userWord[i], i + 1) != string::npos)
			count++;
	return wordLenght - count;
}

void PoleChudes::letsPlay()
{
	while (numberOfGuessedLetters < wordLenght) {
		gotoXY(20, 2); 
		cout << "POLE CHUDES";
		gotoXY(5, 4);
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -";
		gotoXY(5, 5);
		cout << "|\tmin steps " << minAttemptions << "\t|\tyou used " << numberOfEnteredLetters << " attemps\t|";
		gotoXY(5, 6);
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -";
		gotoXY(5, 8);
		showEnteredLetters();
		gotoXY(5, 11);
		cout << "The current state of the word: " << guessWordByUser;
		fillWord(enterLetter());
		system("cls");
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
	else cout << "no letters";
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

char PoleChudes::enterLetter()
{
	char letter;
	bool ind;
	gotoXY(5, 12);
	cout << "Enter one of few letters: ";
	letter = getLetterFromUser();
	do {
		ind = false;
		for (int i = 0; i < numberOfEnteredLetters; i++) {
			if (letter == enteredLetters[i]) {
				gotoXY(5, 12);
				cout << "Letter '" << letter << "' is already enterred";
				gotoXY(5, 13);
				cout << "Enter enother one:  ";
				gotoXY(24, 13);
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
	char c;
	bool ind;

	do {
		cin >> c;
		if (isalpha(c)) {
			ind = false;
		}
		else {
			ind = true;
			gotoXY(5, 12);
			cout << "That`s exactly not a letter";
			gotoXY(5, 13);
			cout << "Try again:  ";
			gotoXY(16, 13);
		}
		while (getchar() != '\n');
	} while (ind);

	if (isupper(c)) {
		c = tolower(c);
	}
	return c;
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
	cout << "Use <Enter> to continue";
	system("pause>nul");
	GetAsyncKeyState(VK_RETURN);
}