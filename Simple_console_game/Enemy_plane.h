#pragma once

struct Enemy_plane {
	int oldCoordX;
	int oldCoordY;
	int coordX;
	int coordY;
	bool destroyed = 0;
	char body = static_cast<char>(206);
	Enemy_plane() = delete;
	Enemy_plane(int x, int y) : oldCoordX(x), oldCoordY(y), coordX(x), coordY(y) {}
};
