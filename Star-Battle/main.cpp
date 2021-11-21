#define _CRT_SECURE_NO_WARNINGS

#include<windows.h>

#include<iostream>

#include<iomanip>
#include<fstream>

#include"game.h"

using namespace std;

int main()
{
	hidecursor();
	SetConsoleTitleA("StarBattle");
	system("MODE CON COLS=79 LINES=25");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	game();
	system("pause>0");
}