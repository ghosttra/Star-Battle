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
void sett_controls(int& contr, int shuttle)
{
	clear_;
	gotoxy(central_output(41),2); cout << "Добро пожаловать в настройки управления!\n";
	gotoxy(central_output(35),3); cout << "Как вы желаете управлять кораблем?";
	gotoxy(central_output(49),4); cout << "По умолчанию: (Стелочки вправо и влево и вверх)";
	Menu menu;
	vector<string> m = {
		"A-Влево, D-Вправо, W-Выстрел",
		"По умолчанию",
		"Выход"
	};
	int ch = menu.select_vertical(m);
	ofstream save("settings.txt");
	switch (ch)
	{
	case 0:
		contr = 1;
		save << contr << " " << shuttle;
		save.close();
		break;
	case 1:
		contr = 0;
		save << contr << " " << shuttle;
		save.close();
		break;
	case 2:
		return;
	default:
		break;
	}
}
void sett_shuttleSkin(int& shuttle, int contr)
{
	clear_;
	gotoxy(central_output(41), 2); cout << "Добро пожаловать в настройки шаттла!\n";
	gotoxy(central_output(35), 3); cout << "Как вы хотите видеть свой корабль?";
	Menu menu;
	vector<string> m = {
		"Прототип №173",
		"Стандартный",
		"Выход"
	};
	int ch = menu.select_vertical(m);
	ofstream save("settings.txt");
	switch (ch)
	{
	case 0:
		shuttle = 1;
		save << contr << " " << shuttle;
		save.close();
		break;
	case 1:
		shuttle = 0;
		save << contr << " " << shuttle;
		save.close();
		break;
	case 2:
		return;
	default:
		break;
	}
}
void settings(int &contr, int&shuttle)
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
		sett_controls(contr, shuttle);
		break;
	case 1:
		sett_shuttleSkin(shuttle, contr);
		break;
	case 2:
		return;
	default:
		break;
	}
}