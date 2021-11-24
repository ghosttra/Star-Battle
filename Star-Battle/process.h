#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <conio.h>
#include <locale.h>
#include <stdio.h>

#include <list>
#include<vector>
#include<string>
#include<iostream>
#include"menu.h"
#include"functions.h"

#define clear_ system("cls")
#define central_output(n) (80 - n)/2

using namespace std;

void frame()
{
	clear_;
	int i = 0;
	while (i < 79)
	{
		gotoxy(i, 0);
		cout << "=";
		gotoxy(i, 24);
		cout << "=";
		i++;
	}
}
struct Date
{
	int day;
	int month;
	int year;
	int hour;
	int minute;
	void print(ofstream& a)
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);
		year = 1900 + ltm->tm_year;
		month = 1 + ltm->tm_mon;
		day = ltm->tm_mday;
		hour = ltm->tm_hour;
		minute = ltm->tm_min;
		a << hour << " " << minute << " " << day << " " << month << " " << year;
		/*a << " | Время попытки: ";
		if (hour < 10)
			a << "0";
		a << hour << ":";
		if (minute < 10)
			a << "0";
		a << minute << " ";
		if (day < 10)
			a << "0";
		a << day << "/";
		if (month < 10)
			a << "0";
		a << month << "/" << year;*/
	}
	void cprint()
	{
		if (hour < 10)
			cout << "0";
		cout << hour << ":";
		if (minute < 10)
			cout << "0";
		cout << minute << " ";
		if (day < 10)
			cout << "0";
		cout << day << "/";
		if (month < 10)
			cout << "0";
		cout << month << "/" << year << endl;
	}
};
struct Rate
{
	Date date;
	char* name;
	int score;
};
struct Game
{
	int size = 0;
	Rate* p = nullptr;
	void save(int score)
	{
		Rate m;
		char buffer[15];
		bool flag = true;
		while (flag)
		{
			gotoxy(central_output(40),11);
			cout << "Введите свое имя(от 3 до 15 символов): "; gotoxy(central_output(15), 12); cin.getline(buffer, 15);
			if (strlen(buffer) <= 2)
			{
				for (size_t i = 0; i < 3; i++)
				{
					gotoxy(central_output(28),i+12);
					cout << "Введите действительное имя!";
					Sleep(250);
				}
				clear_;
			}
			else {
				m.name = new char[strlen(buffer) + 1];
				strcpy(m.name, buffer);
				m.score = score;
				push_back_Array(p, size, m);
				ofstream a("rate.txt", ios::app);
				for (size_t i = 0; i < size; i++)
				{
					for (size_t i = 0; i < size; i++)
						a << p[i].name << " " << m.score << " "; m.date.print(a);
					cout << endl;
				}
				a.close();
				frame();
				gotoxy((central_output(24)), 11);
				cout << "Твой прогресс сохранен.";
				flag = false;
			}
		}
	}
	void load()
	{
		ifstream check("rate.txt");
		check.seekg(0, ios::end);
		char file_size = check.tellg();
		check.close();
		if (file_size == 0) {
			gotoxy(central_output(25), 12);
			cout << "Статистика отсутствует.\n";
		}
		else {
			Rate m;
			char buff[80]; int size = 0;
			ifstream save("rate.txt");
			m.name = new char[16];
			size_t i = 0;
			int max = 0, hI, r=5;
			while (save >> m.name >> m.score >> m.date.hour >> m.date.minute >> m.date.day >> m.date.month >> m.date.year)
			{
				gotoxy(0, r);
				push_back_Array(p, size, m);
				cout << i + 1 << ". " << p[i].name << " | Счёт: " << p[i].score << " | Время попытки: "; p[i].date.cprint();
				i++; r++;
				gotoxy(0, r);
				for (size_t i = 0; i < size; i++)
				{
					if(p[i].score > max)
					{
						max = p[i].score;
						hI = i;
					}
				}

				gotoxy(central_output(13),1);
				cout << "Рекорд века!" << endl;
				cout << p[hI].name << " | Счёт: " << p[hI].score << " | Время попытки: "; p[hI].date.cprint();
			}
			save.close();
		}
		system("pause>0");
	}
};
int entity_to_destroy()
{
	srand(time(0));
	int rand_len = 30 + rand() % (60 - 30);
	char ch; int x, arr[12], max = 0;
	for (size_t i = 0; i < 4; i++)
	{
		arr[i] = 0;
		x = (80 - rand_len) / 2;
		for (size_t j = 0; j < rand_len; j++)
		{
			arr[i]++;
			ch = 34 + (1 + rand()% (4-1));
			gotoxy(x++, i+3);
			SetColor(7+rand()%(13-7), Black);
			cout << ch;
		}
		rand_len = 30 + rand() % (60 - 30);
		cout << endl;
	}
	for (size_t i = 0; i < 8; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}
void set_score_array(int* shots, int length)
{
	int barrier = (80 - length) / 2;
	for (size_t i = 0; i < 79; i++)
	{
		if (i >= barrier && i <= (size_t)(barrier + length - 1))
			shots[i] = 1;
		else
			shots[i] = 0;
	}
}
void print_plane(int shift, int key, bool f, int right, int left, int shuttle, int& pl_length)
{
	string pl = "plane.txt";
	if (shuttle == 1) { pl = "plane1.txt"; }
	ifstream plane(pl);
	char t[80]; int i = 15;
	SetColor(Yellow, Black);
	while (plane.getline(t, 80))
	{
		int len = strlen(t);
		int x = ((80 - len) / 2);
		if (x + len != 79)
		{
			x += shift;
			i++;
			gotoxy(x, i);
			cout << t << endl;
			if (f) 
			{
				if (key == right)
					x--;
				if (key == left)
					x += len;
				gotoxy(x, i);
				cout << ' ';
			}
		}
		if (len > pl_length)
			pl_length = len;
	}
	SetColor(LightGray, Black);
	plane.close();
}
int shot(int shift, int* shots, int length, size_t i, bool& key, int& y, int& x)
{
	gotoxy(x, y);
	SetColor(LightGreen, Black);
	cout << '!';
	SetColor(LightGray, Black);
	SetColor(LightGray, Black);
	if (i % 60 == 0)
	{
		gotoxy(x,y);
		cout << " ";
		y--;
	}
	if (y == 1)
	{
		key = 0;
		y = 15;
		if (shots[x] != 0)
		{
			shots[x] = 0;
			return 1;
		}
		if (!shots[x])
			return 0;
	}
}
void cord_rand(int *cord_mas_y,int* cord_mas_x, int cord_mas_size, size_t j)
{
		cord_mas_y[j] = 7;
		for (size_t i = 0; i < cord_mas_size; i++)
			cord_mas_x[j] = 30 + rand() % 70 - 30;
}
void enemy(int* cord_mas_x, int* cord_mas_y, int cord_mas_size, int j, int x_shot)
{
	gotoxy(cord_mas_x[j], cord_mas_y[j]);
	cout << " ";
	cord_mas_y[j]++;
	if (cord_mas_y[j] == 22 or x_shot == cord_mas_x[j])
		cord_rand(cord_mas_y, cord_mas_x, cord_mas_size, j);
}
int hitbox(int cord_mas_size, int* cord_mas_x, int* cord_mas_y, int* hb, size_t j)
{
	for (size_t j = 0; j < cord_mas_size; j++)
	{
		if (hb[0] <= cord_mas_x[j] and hb[1] >= cord_mas_x[j] and hb[2] <= cord_mas_y[j]) {
			cord_mas_x[j] = 30 + rand() % 70 - 30;
			cord_mas_y[j] = 7;
			return 1;
			break;
		}
	}
	return 0;
}
#define esc 27
void game_process(int contr, int shuttle)
{
	int left_arrow = 75, right_arrow = 77, shot_ = 72;
	if (contr == 1) {
		left_arrow = 97; right_arrow = 100; shot_ = 119;
	}
	int length = entity_to_destroy();
	int pl_length = 0, y_shot = 15, x_shot=0;
	entity_to_destroy();
	print_plane(0, 0, 0, 0, 0, shuttle, pl_length);
	int barrier = 34, shift = 0, tscore = 0, score = 0, shot_temp, health = 3, seven = 7, i = 0;
	int shots[80];
	bool flag = 0, key_shot = 0;
	gotoxy(1, 23);
	cout << "Score: " << score;
	gotoxy(1, 1);
	SetColor(Red, Black);
	cout << "<3 <3 <3";
	SetColor(LightGray, Black);
	set_score_array(shots, length);
	const int cord_mas_size = 5;
	const int hb_size = 3;
	int cord_mas_x[cord_mas_size];
	int cord_mas_y[cord_mas_size];
	int hb[hb_size];
	hb[2] = 16;
	for (size_t i = 0; i < cord_mas_size; i++) {
		cord_mas_x[i] = 30 + rand() % 70 - 30;
		cord_mas_y[i] = 7;
	}
	while (flag == 0)
	{
		size_t j = 0;
		i++;
		for (size_t j = 0; j < cord_mas_size; j++)
		{
			gotoxy(cord_mas_x[j], cord_mas_y[j]);
			cout << "U";
		}
		SetColor(LightGray, Black);
		if (i % 2000 == 0) {
			enemy(cord_mas_x, cord_mas_y, cord_mas_size, 0, x_shot);
			enemy(cord_mas_x, cord_mas_y, cord_mas_size, 3, x_shot);
		}
		if (i % 1500 == 0) {
			enemy(cord_mas_x, cord_mas_y, cord_mas_size, 1, x_shot);
		}	
		if (i % 1800 == 0) {
			enemy(cord_mas_x, cord_mas_y, cord_mas_size, 2, x_shot);
			enemy(cord_mas_x, cord_mas_y, cord_mas_size, 4, x_shot);
		}	
		int hb_hit = hitbox(cord_mas_size, cord_mas_x, cord_mas_y, hb, j);
		if (_kbhit())
		{
			int key = _getch();
			if (barrier != 0 && key == left_arrow) {
				shift += -1;
				print_plane(shift, key, 1, right_arrow, left_arrow, shuttle, pl_length);
				barrier--;
			}
			if (barrier != 68 && key == right_arrow) {
				shift += 1;
				print_plane(shift, key, 1, right_arrow, left_arrow, shuttle, pl_length);
				barrier++;
			}
			hb[0] = central_output(pl_length) + shift;
			hb[1] = central_output(pl_length) + pl_length + shift-1;
			if (key == shot_) {
				x_shot = 39 + shift;
				key_shot = 1;
			}
			if (key == esc)
				return;
			gotoxy(1, 23);
			cout << "Score: " << score << " " << health;
			if (tscore == length)
			{
				tscore = 0;
				length = entity_to_destroy();
				set_score_array(shots, length);
			}
		}
		if (key_shot)
		{
			shot_temp = shot(shift, shots, length, i, key_shot, y_shot, x_shot);
			if (shot_temp == 1)
			{
				score++;
				tscore++;
			}
			if (shot_temp == 0) {
				health--;
				gotoxy(seven, 1);
				seven -= 3;
				cout << "  ";
			}
		}
		if (health <= 0)
			flag = 1;
		if (hb_hit == 1) {
			hb_hit = 0;
			health--;
			gotoxy(seven, 1);
			seven -= 3;
			cout << "  ";
		}
	}
	clear_;
	frame();
	gotoxy(central_output(15), 2); cout << "Вы проиграли! ";
	gotoxy(central_output(14), 3);
	cout << "Ваш счёт: " << score;
	Game t;
	t.save(score);
	system("pause>0");
}