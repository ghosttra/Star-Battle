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
	int contr;
	while (true)
	{
		clear;
		Rate rate;
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
			game_process(contr);
			frame();
			break;
		case 1:
			frame();
			Game.load();
			break;
		case 2:
			settings(contr);
			break;
		case 3:
			exit(0);
		default:
			break;
		}
	}
}