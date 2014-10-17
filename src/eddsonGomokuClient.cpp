#include "eddsonGomokuClient.h"

const Coordinate null_coord(-1, -1);

bool isEqualCoords(Coordinate a, Coordinate b) {
	return a.x == b.x && a.y == b.y;
}
Coordinate addCoords(Coordinate a, Coordinate b) {
	return Coordinate(a.x + b.x, a.y + b.y);
}
bool isNullCoord(Coordinate coord) {
	return isEqualCoords(coord, null_coord);
}


eddsonGomokuClient::eddsonGomokuClient(PointType color) : GomokuClient(color), lastMove(-1, -1), distribution(0, 18)
{
	lastBoard = new BOARD_POINTS();
}


eddsonGomokuClient::~eddsonGomokuClient()
{
}

bool eddsonGomokuClient::isMeOrEmpty(PointType p) {
	return p == EMPTY || p == this->m_color;
}

BOARD_POINTS* eddsonGomokuClient::getBoardPoints(Board* board) {
	BOARD_POINTS* boardPoints = new BOARD_POINTS();
	for (auto i = 0; i < 19*19; i++)
		boardPoints->push_back(board->point(Coordinate(i % 19, i / 19)));
	return boardPoints;
}

Coordinate eddsonGomokuClient::getEnemysLastMove(BOARD_POINTS* currentBoard, BOARD_POINTS* lastBoard) {
	Coordinate coord = null_coord;
	for (auto i = 0; i < 19*19; i++)
	{
		if (!isMeOrEmpty((*currentBoard)[i]) && (*currentBoard)[i] != (*lastBoard)[i])
		{
			coord = Coordinate(i % 19, i / 19);
			break;
		}
	}
	return coord;
}

Coordinate eddsonGomokuClient::predictNextMove(Coordinate* currentMove, Coordinate* lastMove) {
	int dx = lastMove->x - currentMove->x;
	int dy = currentMove->y - lastMove->y;
	if (dx > 0) dx = 1;
	if (dx < 0) dx = -1;
	if (dy > 0) dy = 1;
	if (dy < 0) dy = -1;

	return Coordinate(dx, dy);
}

Coordinate eddsonGomokuClient::make_a_move(Board& board) {
	Coordinate nextMove(0,0);
	BOARD_POINTS* currentBoard = getBoardPoints(&board);
	Coordinate currentEnemyMove = this->getEnemysLastMove(currentBoard, lastBoard);

	if (isNullCoord(currentEnemyMove) || isNullCoord(lastMove))
		nextMove = Coordinate(distribution(generator), distribution(generator));
	else {
		Coordinate dir = this->predictNextMove(&currentEnemyMove, &lastMove);
        nextMove = addCoords(currentEnemyMove, dir);
	}

	lastMove = nextMove;
	lastBoard = currentBoard;
	return nextMove;
}
