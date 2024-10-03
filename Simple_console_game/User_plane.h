#pragma once

struct User_Plane {
	int coordX = 25;
	int coordY = 15;
	char body = static_cast<char>(30);
	bool destroyed = 0;
	void move_up() { --coordY; }
	void move_down() { ++coordY; }
	void move_left() { --coordX; }
	void move_right() { ++coordX; }
};
