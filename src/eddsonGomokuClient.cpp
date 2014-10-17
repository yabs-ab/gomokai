#include "eddsonGomokuClient.h"
const Coordinate null_coord(-1, -1);

void eddsonGomokuClient::getBoardPoints(Board* board, BOARD_POINTS* boardPoints) {
	for (auto i = 0; i < 19*19; i++)
		boardPoints->push_back(board->point(Coordinate(i % 19, i / 19)));
}

Coordinate eddsonGomokuClient::getEnemysLastMove(BOARD_POINTS* currentBoard, BOARD_POINTS* lastBoard) {
	Coordinate coord = null_coord;
	for (auto i = 0; i < 19*19; i++)
	{
		if ((*currentBoard)[i] != EMPTY && (*currentBoard)[i] != this->m_color && (*currentBoard)[i] != (*lastBoard)[i])
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

eddsonGomokuClient::eddsonGomokuClient(PointType color) : GomokuClient(color), lastMove(0,0)
{
	lastBoard = new BOARD_POINTS();
}


eddsonGomokuClient::~eddsonGomokuClient()
{
}

Coordinate eddsonGomokuClient::make_a_move(Board& board) {
	Coordinate coord(0,0);
	BOARD_POINTS *currentBoard = new BOARD_POINTS();
	getBoardPoints(&board, currentBoard);
	Coordinate currentMove = this->getEnemysLastMove(currentBoard, lastBoard);

	coord = currentMove;

	lastMove = currentMove;
	lastBoard = currentBoard;
	return coord;
}
