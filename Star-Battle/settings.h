#pragma once
#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <conio.h>
#include <locale.h>

#include <list>
#include<iostream>
#include<fstream>

#include"functions.h"
#include"process.h"
#include"menu.h"

#define central_output(n) (80 - n)/2
#define clear_ system("cls")

using namespace std;
void sett_controls(int& contr)
{
	clear_;
	gotoxy(central_output(41),2); cout << "Добро пожаловать в настройки управления!\n";
	gotoxy(central_output(35),3); cout << "Как вы желаете управлять кораблем?";
	gotoxy(central_output(49),4); cout << "По умолчанию: (Стелочки вправо и влево и пробел)";
	Menu menu;
	vector<string> m = {
		"A-Влево, D-Вправо, Shift-Выстрел",
		"По умолчанию",
		"Выход"
	};
	int ch = menu.select_vertical(m);
	switch (ch)
	{
	case 0:
		contr = 1;
		break;
	case 1:
		contr = 0;
		break;
	case 2:
		return;
	default:
		break;
	}
	/*ofstream save("settings.bin", ios::binary);
	for (size_t i = 0; i < 5; i++)
	{
		save.write((char*)&, sizeof(int));
	}
	int* a = nullptr; int size = 0;
	ifstream load("settings.bin", ios::binary);
	int t;
	while (load.read((char*)&t, sizeof(int)))
	{
		push_back_Array(a, size, t);
	}*/
}
void sett_shuttleSkin()
{

}
void settings(int &contr)
{
	clear_;
	Menu menu;
	vector<string> m = {
		"Настройки управления",
		"Вид шатла",
		"Выход"
	};
	int ch = menu.select_vertical(m);
	switch (ch)
	{
	case 0:
		sett_controls(contr);
		break;
	case 1:
		/*sett_shuttleSkin();*/
		break;
	case 2:
		return;
	default:
		break;
	}
}