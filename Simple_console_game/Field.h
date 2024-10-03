#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>


struct Field {
	const int width = 50;
	const int height = 30;
	std::string controls = { "Control: w, a, s, d, \" space \" to fire, \"esc\" to exit." };

	void set_console() {
		system("mode con cols=51 lines=31"); // установка размеров окна консоли
		MoveWindow(GetConsoleWindow(), 100, 100, 1000, 1000, true);
		SetWindow(60, 50);
		// установка стартовой позиции окна консоли (60 и 50 - это пиксели
		// относительно верхнего левого угла монитора
	}
	void SetWindow(int Width, int Height){
		_COORD coord;
		coord.X = Width;
		coord.Y = Height;
		_SMALL_RECT Rect;
		Rect.Top = 0;
		Rect.Left = 0;
		Rect.Bottom = Height - 1;
		Rect.Right = Width - 1;
		HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleScreenBufferSize(Handle, coord);
		SetConsoleWindowInfo(Handle, TRUE, &Rect);
	}

	void draw_frame(HANDLE h, int color) const {
		SetConsoleTextAttribute(h, color); // установка цвета, которым рисуется рамка поля
		std::string::size_type count = controls.size();
		std::string::size_type runner = 0;

		char s;
		for (int y = 0; y < height; y++) // стандартный двойной цикл на отрисовку рамки
		{
			for (int x = 0; x < (width + count); x++)
			{
				if (x == 0 && y == 0) // в верхнем левом углу поля - символ соответствующего угла
					s = static_cast<char>(176);
				else if (x == 0 && y == height - 1) // нижний левый угол
					s = static_cast<char>(176);
				else if (y == 0 && x == width - 1) // верхний правый угол
					s = static_cast<char>(176);
				else if (y == height - 1 && x == width - 1) // нижний правый угол
					s = static_cast<char>(176);
				else if ((y == 0 || y == height - 1) && x < width) // верхняя и нижняя граница поля
					s = static_cast<char>(176);
				else if (x == 0 || x == width - 1) // левая и правая граница поля
					s = static_cast<char>(176);
				else s = ' '; // во всех остальных случаях должен быть просто пробел (означает пустую область поля)
				putchar(s); // выводим символ
			}
			std::cout << std::endl;
			if (y == (height - 1)) {
				SetConsoleTextAttribute(h, 10);
				std::cout << controls << std::endl;
			}
		}
	}
};
