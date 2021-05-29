#include "PoleChudes.h"

void PoleChudes::gotoXY(int x, int y)//переносить курсор на позицію (x, y)
{
	CursorPosition.X = x;//задає позицію курсора по x
	CursorPosition.Y = y;//задає позицію курсора по н
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);//встановлює курсор на позицію CursorPosition
}

void PoleChudes::menu() {
	int menu_item, y;//вибраний пункт меню; позиція по координаті y
	bool ind;//індикатор вибору пунктц меню
	
	menu_item = 0;//встановлюе обраний пункт меню на перший
	
	y = 10;//встановлює координату на 10
	system("cls");//очищує єкран
	gotoXY(20, 2); cout << "POLE CHUDES";
	gotoXY(24, 5); cout << "MENU";
	gotoXY(5, 7); cout << "- - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(22, 10);  cout << "How to play";
	gotoXY(22, 13);  cout << "Play with computer";
	gotoXY(22, 16);  cout << "Play with friend";
	gotoXY(22, 19);  cout << "Quit Program";
	gotoXY(5, 22); cout << "- - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(12, 24); cout << "Use <up arrow> or <down arrow> to navigate";
	gotoXY(16, 25); cout << "Use <Enter> to choose";

	gotoXY(18, 10); cout << "->";

	ind = true;
	while (ind)
	{
		system("pause>nul"); //затрмка экрану 

		if (GetAsyncKeyState(VK_DOWN) && y != 19) //нажата кнопка "вниз"
		{
			gotoXY(18, y); cout << "  ";
			y += 3;
			gotoXY(18, y); cout << "->";
			menu_item++;
		}
		
		else if (GetAsyncKeyState(VK_UP) && y != 10) //нажата кнопка "вверх"
		{
			gotoXY(18, y); cout << "  ";
			y -= 3;
			gotoXY(18, y); cout << "->";
			menu_item--;
		}

		else if (GetAsyncKeyState(VK_RETURN)) { //нажата кнопка "Enter"
			ind = false; //вибор пункта меню завершить свою роботу

			switch (menu_item) {

			case 0: {
				howToPlay();
				break;
			}

			case 1: {
				play(true);// гра з компютером
				break;
			}

			case 2: {
				play(false);// гра з іншим гравцем
				break;
			}

			case 3: {
				system("cls");
				gotoXY(20, 10); cout << "Good luck!";
				
				gotoXY(5, 22);  cout << "Press any key";
				system("pause>nul");
				break;
			}
			}
		}
	}
}

void PoleChudes::howToPlay() //правила игры
{
	system("cls");
	gotoXY(5, 0);   cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(10, 2);  cout << "Friend game mode:";
	gotoXY(20, 4);  cout << "The first player enters a word.";
	gotoXY(20, 5);  cout << "The second player enters one or more letters";
	gotoXY(20, 6);  cout << "and tries to guess the word in the least number of attempts.";
	gotoXY(5, 8);   cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(10, 10); cout << "Computer game mode:";
	gotoXY(20, 12); cout << "The computer randomly chooses a word for the game.";
	gotoXY(20, 13); cout << "The player tries to guess in the least number of attempts.";
	gotoXY(5, 15);  cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(10, 17);  cout << "Rules:";
	gotoXY(20, 19); cout << "You must only enter English alphabet characters.";
	gotoXY(20, 20); cout << "If you enter more than one character when entering letters,";
	gotoXY(20, 21); cout << "then only the first is counted.";
	
	gotoXY(5, 24);  cout << "Press any key to menu";

	system("pause>nul");
	GetAsyncKeyState(VK_RETURN);//очищує ввід клавіш
	menu();
}

void PoleChudes::play(bool computerOrPlayer) {
	computerOrPlayer ? randomWord() : enteringWord();// якщо computerOrPlayer мае значення true, то спрацює гра з комп'ютером, в іншому випадк гра з іншим гравцем
	someCalculating();
	letsPlay();
	final();
}

void PoleChudes::randomWord()
{	
	int num; //номер слова з фалу
	
	srand((unsigned int)time(0)); //задаємо початкове значення функції рандом
	num = rand() % NumberOfWordsInFile; //випадкове значення з діапазону від нуля до кількості слів.
	
	try {
		ifstream in("words.txt"); //підключаеє файл 
		in.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);//генерує exception при винекненні помилок
		//зчитує слово з номером num+1
		for (int i = 0; i <= num; i++) {
			getline(in, userWord);
		}
		in.close();//закриває файл
	}
	catch (exception const& e) {//ловить exception, виводить повідомлення на екран
		system("cls");
		gotoXY(5, 2); cout << "There was an error: " << e.what();
		gotoXY(5, 4); cout << "Press any key to continue";
		system("pause>null");
	}
}

void PoleChudes::enteringWord()
{
	bool ind; //індикатор правельності вводу
	int numOfLetters; //кількість літер
	do {
		system("cls");
		gotoXY(25, 5);
		cout << "Welcome";
		gotoXY(16, 7);
		cout << "Please, enter one correct word";
		gotoXY(20, 9);

		getline(cin, userWord);//зчитує сторку

		numOfLetters = 0;
		ind = false;
		for (char& c : userWord) {//пробігає по слову, перевіряє чм правельний ввід, рахує кількість літер 
			if (!isalpha(c)) {
				ind = true;
			}
			numOfLetters++;
		}
		if (userWord[0] == '\0' ||  numOfLetters > MaxLettersInWord)//якщо не введено жодного символу, або занадто довге слово
			ind = true;

		if (ind) {//при винекнені помилки виводить повідомлення про неправельний ввід
			gotoXY(20, 9);
			clear();
			gotoXY(16, 11);
			cout << "Entering isn't correct";
			gotoXY(5, 19);
			cout << "Press any key to continue";
			system("pause>nul");//затримка єкрану
			GetAsyncKeyState(VK_RETURN);//очищує ввід клавіш
		}

	} while (ind);//проки ввід неправельний
}

void PoleChudes::someCalculating()
{
	wordLenght = userWord.length();//довжина рядку userWord
	guessWordByUser = userWord;//ініціалізація змінної
	minAttemptions = minSteps();//мінімальна к-ть кроків до виграшу
	for (int i = 0; i < wordLenght; i++) {//заповнюємо слово символом "_", та змінюємо регістр всіх літер у слові на нижній
		guessWordByUser[i] = '_';
		if (isupper(userWord[i])) {
			userWord[i] = tolower(userWord[i]);
		}
	}
	//кількість вгаданих і введених літер дорівнює нулю
	numberOfGuessedLetters = 0;
	numberOfEnteredLetters = 0;
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
	while (numberOfGuessedLetters < wordLenght) {//пока не вгадані всі літери
		system("cls");
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
	}
}

void PoleChudes::showEnteredLetters()
{
	cout << "Your entered letters: ";
	if (numberOfEnteredLetters) {//якшо введена хочаб одна літера
		for (int i = 0; i < numberOfEnteredLetters; i++) {//виводить введені літери
			cout << enteredLetters[i] << ' ';
		}
	}
	else cout << "no letters"; // якщо не введено жодної літери
}

void PoleChudes::fillWord(char letter)
{
	for (int i = 0; i < wordLenght; i++) {
		if (letter == userWord[i]) {//якщо літера є в слові введеному користувачем ставить її на туж позіцію в слові яке виводиться
			guessWordByUser[i] = letter;
			numberOfGuessedLetters++;//збільшує кількість відгаданих літер
		}
	}
}

char PoleChudes::enterLetter()
{
	char letter;//введена літера
	bool ind;//індикатор неповторюваності вводу
	gotoXY(5, 12);
	cout << "Enter one of few letters: ";
	letter = getLetterFromUser();
	do {
		ind = false;
		for (int i = 0; i < numberOfEnteredLetters && !ind; i++) {
			if (letter == enteredLetters[i]) {//якщо літера уже була введена
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
	} while (ind);//поки вводяться вже введені літери

	numberOfEnteredLetters++;//збільшеє кількість введених літер
	enteredLetters[numberOfEnteredLetters - 1] = letter;//добавляє літеру в масив введених літер

	return letter;//повертає літеру 
}

char PoleChudes::getLetterFromUser()
{
	char c;//введена літера
	bool ind;//індикатор правельності вводу

	do {
		cin >> c;//зчитує символ
		if (isalpha(c)) {//якщо символ літера
			ind = false;
		}
		else {//якщо не літера віводить повідомлення про помилку
			ind = true;
			gotoXY(5, 12);
			cout << "That`s exactly not a letter";
			clear();
			gotoXY(5, 13);
			cout << "Try again:  ";
			gotoXY(16, 13);
		}
		while (getchar() != '\n');
	} while (ind);//поки ввід неправельний

	if (isupper(c)) {
		c = tolower(c);//змінює регістр на нижній
	}
	return c;
}

void PoleChudes::final() {//віводить повідомлення про перемогу та деяку інформацію про партію
	system("cls");
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
	cout << "Press any key to continue";
	system("pause>nul");//затримка памяті 
	GetAsyncKeyState(VK_RETURN);//очищує ввід клавіш
	menu();
}

void PoleChudes::clear() {
	cout << string(NumberOfWhiteSpaces, ' ');//виводить певну кількість пробілів
	gotoXY(0, 0);
}