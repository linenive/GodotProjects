#include "CoordinatesSystem.h"

Coordinates VectorToCoordinates(Vector2 vector) {
	int x = (vector.x - MAP_START_POS_X) / TILE_WIDTH;
	int y = (vector.y - MAP_START_POS_Y) / TILE_HEIGHT;
	// �� ���̺귯�������� ��ǥ�� Ÿ�ϸ��� ����� �� �Ű澲�� �ʴ´�.
	if (x < 0) x -= 1;
	if (y < 0) y -= 1;
	// printf("VectorToCoordinates: %d %d\n", x, y);
	return Coordinates(x, y);
}

Vector2 CoordinatesToCenterVector(Coordinates coord){
	float x = coord.x * TILE_WIDTH + TILE_WIDTH / 2;
	float y = coord.y * TILE_HEIGHT + TILE_HEIGHT / 2;

	return Vector2(x, y);
}