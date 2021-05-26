#include "PoleChudes.h"

void PoleChudes::gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void Menu::menu() {
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

void Menu::howToPlay()
{
	system("cls");
	gotoXY(5, 5);   cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(10, 7);  cout << "Friend game mode: ";
	gotoXY(20, 9);  cout << "The first player enters a word.";
	gotoXY(20, 10); cout << "The second player enters one or more letters";
	gotoXY(20, 11); cout << "and tries to guess the word in the least number of attempts";
	gotoXY(5, 13);  cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(10, 15); cout << "Computer game mode: ";
	gotoXY(20, 17); cout << "The computer randomly chooses a word for the game.";
	gotoXY(20, 19); cout << "The player tries to guess in the least number of attempts";
	gotoXY(5, 21);  cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	gotoXY(5, 26);  cout << "Press <enter> to menu";

	system("pause>nul");
	GetAsyncKeyState(VK_RETURN);
}