#pragma once
#include "GameRule.h"
#include "Common.h"

class Coordinates {
public:
	int x, y;

	Coordinates() {
		x = -1;
		y = -1;
	}

	Coordinates(int x_coord, int y_coord) {
		x = x_coord;
		y = y_coord;
	}
};

// To-do: ī�޶� ��ġ �ݿ��Ͽ� ���
Coordinates VectorToCoordinates(Vector2 vector);

Vector2 CoordinatesToCenterVector(Coordinates coord);