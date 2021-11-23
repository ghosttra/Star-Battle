#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include"menu.h"
#include"process.h"
#include"settings.h"
#define clear system("cls")
using namespace std;
void game()
{
	int contr, shuttle;
	ifstream load("settings.txt");
	load >> contr >> shuttle;
	load.close();
	while (true)
	{
		clear;
		gotoxy((80 - 12) / 2, 8);
		SetColor(LightCyan, Black);
		cout << "Star Battle";
		SetColor(LightGray, Black);
		Game Game;
		Menu menu;
		vector<string> m = {
			"Начать новую игру",
			"Рейтинг",
			"Настройки игры",
			"Выход"
		};
		int ch = menu.select_vertical(m);
		switch (ch)
		{
		case 0:
			frame();
			game_process(contr,shuttle);
			frame();
			break;
		case 1:
			frame();
			Game.load();
			break;
		case 2:
			settings(contr, shuttle);
			break;
		case 3:
			exit(0);
		default:
			break;
		}
	}
}