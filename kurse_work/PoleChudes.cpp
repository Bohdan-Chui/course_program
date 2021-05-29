#include "PoleChudes.h"

void PoleChudes::gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void PoleChudes::menu() {
	int menu_item, y;
	bool ind1, ind2;
	do {
		menu_item = 0;
		y = 10;
		system("cls");
		gotoXY(20, 2); cout << "POLE CHUDES";
		gotoXY(24, 5); cout << "MENU";
		gotoXY(5, 7); cout << "- - - - - - - - - - - - - - - - - - - - - - - - -";
		gotoXY(18, 10); cout << "->";

		gotoXY(5, 22); cout << "- - - - - - - - - - - - - - - - - - - - - - - - -";
		gotoXY(12, 24); cout << " Use <PgUp> or <PgDn> to navigate";
		gotoXY(16, 25); cout << " Use <Enter> to choose";

		ind1 = true;
		ind2 = true;
		while (ind1)
		{
			gotoXY(20, 10);  cout << "  How to play";
			gotoXY(20, 13);  cout << "  Play with computer";
			gotoXY(20, 16);  cout << "  Play with friend";
			gotoXY(20, 19);  cout << "  Quit Program";

			system("pause>nul"); // the >nul bit causes it the print no message

			if (GetAsyncKeyState(VK_DOWN) && y != 19) //down button pressed
			{
				gotoXY(18, y); cout << "  ";
				y += 3;
				gotoXY(18, y); cout << "->";
				menu_item++;
			}

			if (GetAsyncKeyState(VK_UP) && y != 10) //up button pressed
			{
				gotoXY(18, y); cout << "  ";
				y -= 3;
				gotoXY(18, y); cout << "->";
				menu_item--;
			}

			if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed
				ind1 = false;

				switch (menu_item) {

				case 0: {
					howToPlay();
					break;
				}


				case 1: {
					play(true);
					break;
				}

				case 2: {
					play(false);
					break;
				}

				case 3: {
					system("cls");
					gotoXY(20, 10);
					cout << "Good luck!";
					gotoXY(20, 20);

					ind2 = false;
					break;
				}
				}
			}
		}
	} while (ind2);

}

void PoleChudes::howToPlay()
{
	system("cls");
	gotoXY(5, 2);   cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(10, 4);  cout << "Friend game mode: ";
	gotoXY(20, 5);  cout << "The first player enters a word.";
	gotoXY(20, 6);  cout << "The second player enters one or more letters";
	gotoXY(20, 7);  cout << "and tries to guess the word in the least number of attempts";
	gotoXY(5, 9);   cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(10, 11); cout << "Computer game mode: ";
	gotoXY(20, 12); cout << "The computer randomly chooses a word for the game.";
	gotoXY(20, 13); cout << "The player tries to guess in the least number of attempts";
	gotoXY(5, 15);  cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(10, 17);  cout << "Rules:";
	gotoXY(20, 18); cout << "You must only enter English alphabet characters";
	gotoXY(20, 19); cout << "If you enter more than one character when entering letters,";
	gotoXY(20, 20); cout << "then only the first is counted";
	
	gotoXY(5, 22);  cout << "Press <enter> to menu";

	system("pause>nul");
	GetAsyncKeyState(VK_RETURN);
}

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
	int numOfLetters;
	do {
		system("cls");
		gotoXY(25, 5);
		cout << "Welcome";
		gotoXY(16, 7);
		cout << "Please, enter one correct word";
		gotoXY(20, 9);
		getline(cin, word);

		numOfLetters = 0;
		ind = false;
		for (char& c : word) {//пробігаємо по слову
			if (!isalpha(c)) {
				ind = true;
			}
			numOfLetters++;
		}
		if (word[0] == '\0')
			ind = true;
		if (numOfLetters > MaxLettersInWord) {
			ind = true;
		}

		if (ind) {
			gotoXY(20, 9);
			clear();
			gotoXY(16, 11);
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
				clear();
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
			clear();
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


void PoleChudes::clear() {
	for (int i = 0; i < 3000; i++) {
		cout << ' ';
	}
	gotoXY(0, 0);
}