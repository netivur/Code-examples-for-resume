#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <random>
#include <list>
#include "User_plane.h"
#include "Field.h"
#include "Bullet.h"
#include "Enemy_plane.h"

int sleep_time = 90; // переменная задержки отрисовки в мс
void find_collision(std::list<Enemy_plane>& lep, std::list<Bullet>& lb, int& coe, COORD& coBull, HANDLE& h, User_Plane& UP, unsigned int& body_count);
int main() {
	
	std::cout << "Hello, user! \nDo you want to play a game? (y / n): ";
	char choice = ' ';
	std::cin >> choice;
	while (choice != 'n' && choice != 'N') {
		system("cls");

		unsigned int body_count = 0;
		Field base_field;
		User_Plane UP;
		std::list<Bullet> list_of_bullets;
		std::list<Enemy_plane> list_of_enem_planes;

		COORD c = { UP.coordX, UP.coordY }; // объект для хранения координат самолёта игрока
		COORD coBull = { 0, 0 }; // объект для хранения координат пули
		COORD coEnemy = { 0, 0 };// объект для хранения координат самолёта противника

		int count_of_enemy = 7;
		int time_of_spawn_enemy = 15; //время в циклах программы(частота появления врагов) 
		static std::default_random_engine rand_num(time(0));
		static std::uniform_int_distribution<unsigned> int_distrib_width(3, base_field.width - 3);

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // создание хендла потока вывода
		CONSOLE_CURSOR_INFO cci = { sizeof(cci), false }; // создание параметров на отображение курсора
		SetConsoleCursorInfo(h, &cci); //связывание параметров и хендла
		SetConsoleCursorPosition(h, coBull);
		base_field.draw_frame(h, 3); // 3 - голубой цвет

		SetConsoleCursorPosition(h, c); // отправляем курсор на позицию самолёта игрока
		SetConsoleTextAttribute(h, 4); // устанавливаем красный цвет для отрисовки самолёта игрока
		putchar(UP.body); // отображаем символ самолёта
		// игровой цикл
		bool flag = true;
		do {
			Sleep(sleep_time); // задержка потока программы на заданный ранее интервал

			if ((count_of_enemy != 0) && time_of_spawn_enemy == 0) {
				list_of_enem_planes.push_back(Enemy_plane(int_distrib_width(rand_num), 1));
				--count_of_enemy;
				time_of_spawn_enemy = 15;
			}
			--time_of_spawn_enemy;
			auto itb_list_enem_pl = list_of_enem_planes.begin();
			for (auto plane = itb_list_enem_pl; plane != list_of_enem_planes.end();) {
				if ((*plane).coordY == 1) {

					coEnemy.X = (*plane).oldCoordX;
					coEnemy.Y = (*plane).oldCoordY;
					SetConsoleCursorPosition(h, coEnemy);
					SetConsoleTextAttribute(h, 10);
					putchar((*plane).body);
					++(*plane).coordY;
				}
				if ((*plane).coordY >= 1) {
					coEnemy.X = (*plane).oldCoordX;
					coEnemy.Y = (*plane).oldCoordY++;
					SetConsoleCursorPosition(h, coEnemy);
					putchar(' ');
					coEnemy.X = (*plane).coordX;
					coEnemy.Y = (*plane).coordY++;
					SetConsoleCursorPosition(h, coEnemy);
					putchar((*plane).body);
				}
				if ((*plane).coordY == (base_field.height - 1)) {
					coEnemy.X = (*plane).oldCoordX;
					coEnemy.Y = (*plane).oldCoordY;
					SetConsoleCursorPosition(h, coEnemy);
					putchar(' ');
					plane = list_of_enem_planes.erase(plane);
					++count_of_enemy;
				}
				else {
					plane++;
				}
			}

			if (_kbhit()) // проверяем, была ли нажата какая-либо клавиша и запускаем её обработку
			{
				int k = _getch(); // считываем код клавиши из буфера
				if (k == 0 || k == 224) // если первый код - вспомогательный, считываем второй код
					k = _getch();
				switch (k) // пропускаем код нажатой клавиши внутрь оператора выбора
				{
				case 115: // если была нажата клавиша вниз
					if (UP.coordY < base_field.height - 2)
						UP.move_down();
					break;
				case 235: // если была нажата клавиша вниз
					if (UP.coordY < base_field.height - 2)
						UP.move_down();
					break;
				case 119: // если вверх			
					if (UP.coordY > 1)
						UP.move_up();
					break;
				case 230: // если вверх
					if (UP.coordY > 1)
						UP.move_up();
					break;
				case 97: // если влево
					if (UP.coordX > 1)
						UP.move_left();
					break;
				case 228: // если влево
					if (UP.coordX > 1)
						UP.move_left();
					break;
				case 100: // если вправо
					if (UP.coordX < (base_field.width - 2))
						UP.move_right();
					break;
				case 162: // если вправо
					if (UP.coordX < (base_field.width - 2))
						UP.move_right();
					break;
				case 32: // если space

					list_of_bullets.push_back(Bullet(UP.coordX, UP.coordY - 1));
					break;
				case 27: // если была нажата клавиша ESC
					flag = false; // устанавливаем флажок на false, чтоб закончить показ движения
					break;
				}
			}
			auto itb_of_bull_list = list_of_bullets.begin();
			for (auto bullet = itb_of_bull_list; bullet != list_of_bullets.end(); ) {
				if ((*bullet).coordY == UP.coordY - 1) {
					(*bullet).oldCoordX = (*bullet).coordX;
					(*bullet).oldCoordY = (*bullet).coordY;
					coBull.X = (*bullet).oldCoordX;
					coBull.Y = (*bullet).oldCoordY;
					SetConsoleCursorPosition(h, coBull);
					putchar((*bullet).type_bullet);
					--(*bullet).coordY;
				}
				if ((*bullet).coordY >= 1) {
					coBull.X = (*bullet).oldCoordX;
					coBull.Y = (*bullet).oldCoordY--;
					SetConsoleCursorPosition(h, coBull);
					putchar(' ');
					coBull.X = (*bullet).coordX;
					coBull.Y = (*bullet).coordY--;
					SetConsoleTextAttribute(h, 6);
					SetConsoleCursorPosition(h, coBull);
					putchar((*bullet).type_bullet);
					SetConsoleTextAttribute(h, 10);
				}
				if ((*bullet).coordY == 0) {
					coBull.X = (*bullet).oldCoordX;
					coBull.Y = (*bullet).oldCoordY;
					SetConsoleCursorPosition(h, coBull);
					putchar(' ');
					bullet = list_of_bullets.erase(bullet);
				}
				else {
					bullet++;
				}

			}
			int X = UP.coordX;
			int Y = UP.coordY;

			if (c.X != X || c.Y != Y) {
				SetConsoleCursorPosition(h, c);
				putchar(' ');
				c.X = X;
				c.Y = Y;
				SetConsoleCursorPosition(h, c); // двигаем туда курсора
				SetConsoleTextAttribute(h, 4);// устанавливаем красный цвет для отрисовки
				putchar(UP.body); // отображаем символ самолёта игрока
				SetConsoleTextAttribute(h, 10);// устанавливаем зеленый цвет для отрисовки
			}
			//проверка коллизии
			find_collision(list_of_enem_planes, list_of_bullets, count_of_enemy, coBull, h, UP, body_count);
			if (UP.destroyed) {
				flag = false;
			}

		} while (flag);

		system("cls"); // очищаем экран
		std::cout << "Game over!\n"; // выводим сообщение о конце игры

		std::cout << body_count << " planes destroyed.\n";
		std::cout << "Try again? (y / n): ";
		std::cin >> choice;
	}
	std::cout << "\nBye!\n";
	std::cin.get();
	return 0;
}

void find_collision(std::list<Enemy_plane>& lep, std::list<Bullet>& lb, int& coe, COORD& coBull, HANDLE& h, User_Plane& UP, unsigned int& body_count) {
	auto lepit = lep.begin();
	auto lbit = lb.begin();

	for (auto plane = lepit; plane != lep.end(); ) {
		for (auto bullet = lbit; bullet != lb.end(); ) {

			if (((*plane).oldCoordX == (*bullet).oldCoordX) && ((*plane).oldCoordY == (*bullet).oldCoordY) ||
				((*plane).coordX == (*bullet).oldCoordX) && ((*plane).coordY == (*bullet).oldCoordY)) {

				coBull.X = (*bullet).oldCoordX;
				coBull.Y = (*bullet).oldCoordY;
				SetConsoleCursorPosition(h, coBull);
				putchar(' ');
				coBull.X = (*bullet).coordX;
				coBull.Y = (*bullet).coordY;
				SetConsoleTextAttribute(h, 14);
				SetConsoleCursorPosition(h, coBull);
				putchar((*bullet).bang);
				putchar(' ');
				SetConsoleTextAttribute(h, 10);

				(*plane).destroyed = 1;
				(*bullet).destroyed = 1;

				++coe;
				++body_count;
				break;
			}
			else {

				++bullet;
			}

		}

		if ((*plane).destroyed == 1) {
			plane = lep.erase(plane);
		}
		else if ((*plane).destroyed == 0) {
			if ((UP.coordX == (*plane).coordX) && (UP.coordY == (*plane).coordY)) {

				plane = lep.end();
				UP.destroyed = 1;
			}
			else {
				if (plane != lep.end()) { ++plane; }
			}
		}
	}
	//удаление пуль после столкновения с самолётом противника
	if (!lb.empty()) {
		for (auto iter = lb.begin(); iter != lb.end(); ) {

			if ((*iter).destroyed == 1) {
				iter = lb.erase(iter);
			}
			else if (iter != lb.end()) {
				++iter;
			}
			else {
				break;
			}
		}
	}
}
