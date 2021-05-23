#include "PoleChudes.h"

void PoleChudes::playWithFriend()   
{
	userWord = enteringWord();
	system("cls");
	someCalculating();
	letsPlay();
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
		cout << "please, enter one correct word";
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

void PoleChudes::letsPlay()
{
	while (numberOfGuessedLetters < wordLenght) {
		gotoXY(20, 2); cout << "POLE CHUDES";
		gotoXY(5, 4);
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -";
		gotoXY(5, 5);
		cout << "|\tmin steps " << minAttemptions << "\t|\t" << "you used " << numberOfEnteredLetters << " attemps\t|\n" ;
		gotoXY(5, 6);
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -";
		gotoXY(5, 8);
		showEnteredLetters();
		gotoXY(5, 9);
		cout << "\n\nThe current state of the word: " << guessWordByUser;
		fillWord(guessWordByUser, enterLetter());
		system("cls");
	}
	return;
}

char PoleChudes::enterLetter()
{
	char letter;
	bool ind;
	cout << "\nEnter one of few letters ";
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

 string PoleChudes::getword()
 {
	 return guessWordByUser;
 }

 void PoleChudes::gotoXY(int x, int y)
 {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
 }

 void PoleChudes::playWithComputer()
 {
	 userWord = randomWord();
	 system("cls");
	 someCalculating();
	 letsPlay();
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
	 catch(std::exception const& e) {
		 system("cls");
		 cout << "There was an error: " << e.what() << endl;
		 system("pause>null");
	 }
	 return result;
 }

 int PoleChudes::getUsedAttemption()
 {
	 return numberOfEnteredLetters;
 }

 int PoleChudes::getMinAttemption()
 {
	 return minAttemptions;
 }

 void Menu::menu() {
	 bool ind1, ind2;
	 do {
		 menu_item = 0;
		 run = 0;
		 x = 10;
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

			 if (GetAsyncKeyState(VK_DOWN) && x != 19) //down button pressed
			 {
				 gotoXY(18, x); cout << "  ";
				 x += 3;
				 gotoXY(18, x); cout << "->";
				 menu_item++;


			 }

			 if (GetAsyncKeyState(VK_UP) && x != 10) //up button pressed
			 {
				 gotoXY(18, x); cout << "  ";
				 x -= 3;
				 gotoXY(18, x); cout << "->";
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
						 playWithComputer();
						 final(getword(), getMinAttemption(), getUsedAttemption());
						 break;
					 }

					 case 2: {
						 playWithFriend();
						 final(getword(), getMinAttemption(), getUsedAttemption());
						 break;
					 }

					 case 3: {
						 system("cls");
						 gotoXY(20, 10);
						 cout << "Good luck!";
						 gotoXY(20, 20);
						 
						 ind2 = false;
					 }

				 }

			 }

		 }
	 } while (ind2);

 }

 void Menu::howToPlay()
 {
	 system("cls");
	 gotoXY(5, 5); cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	 gotoXY(10, 7); cout << "Friend game mode: ";
	 gotoXY(28, 9); cout << "The first player enters a word.";
	 gotoXY(28, 10); cout << "The second player enters one or more letters";
	 gotoXY(28, 11); cout << "and tries to guess the word in the least number of attempts";
	 gotoXY(5, 13); cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	 gotoXY(10, 15); cout << "Computer game mode: ";
	 gotoXY(28, 17); cout << "The computer randomly chooses a word for the game.";
	 gotoXY(28, 19); cout << "The player tries to guess in the least number of attempts";
	 gotoXY(5, 21); cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	 gotoXY(5, 26); cout << "Press <enter> to menu";
	 do {
		 system("pause>null");
	 } while (!GetAsyncKeyState(VK_RETURN));


 }

 void Menu::final(string word, int min, int used) {
	 gotoXY(0, 2);
	 cout << "          ..    ..    ....    ..   ..          ..               ..    ..    ..     .." << endl;
	 cout << "           ..  ..    .    .   ..   ..           ..             ..     ..    .. .   .." << endl;
	 cout << "             ..      .    .   ..   ..            ..     .     ..      ..    ..  .  .." << endl;
	 cout << "             ..      .    .   ..   ..             ..  .. ..  ..       ..    ..   . .." << endl;
	 cout << "             ..       ....     .....               ...     ...        ..    ..     .." << endl;
	 gotoXY(7, 10);
	 cout << "Guessed word: " << word;
	 gotoXY(7, 12);
	 cout << "You used " << used << " attemptions";
	 gotoXY(7, 13);
	 cout << "Minimal attemptions for this word " << min;
	 gotoXY(7, 16);
	 cout << "Bye!";
	 gotoXY(5, 19);
	 cout << "press enter to menu";
	 system("pause>nul");

	 if (GetAsyncKeyState(VK_RETURN)) {

	 }
 }