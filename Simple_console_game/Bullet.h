#pragma once

struct Bullet {
	int oldCoordX;
	int oldCoordY;
	int coordX;
	int coordY;
	bool destroyed = 0;
	char type_bullet = 19;
	char bang = 15;
	Bullet() = delete;
	Bullet(int x, int y) : oldCoordX(x), oldCoordY(y), coordX(x), coordY(y) {}
};
