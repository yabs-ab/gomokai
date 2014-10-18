#include <stdlib.h>

#include "eddsonGomokuClient.h"

const Coordinate null_coord(-1, -1);

bool isEqualCoords(Coordinate a, Coordinate b) {
	return a.x == b.x && a.y == b.y;
}
Coordinate addCoords(Coordinate a, Coordinate b) {
    int x = (a.x + b.x < 18) ? a.x + b.x : 18; x = (x < 0) ? 0 : x;
    int y = (a.y + b.y < 18) ? a.y + b.y : 18; y = (y < 0) ? 0 : y;
	return Coordinate(x, y);
}
bool isNullCoord(Coordinate coord) {
	return isEqualCoords(coord, null_coord);
}


eddsonGomokuClient::eddsonGomokuClient(PointType color) : GomokuClient(color), lastMove(-1, -1)
{
}


eddsonGomokuClient::~eddsonGomokuClient()
{
}

bool eddsonGomokuClient::isMeOrEmpty(PointType p) {
	return p == EMPTY || p == this->m_color;
}

BOARD_POINTS eddsonGomokuClient::getBoardPoints(Board board) {
	BOARD_POINTS boardPoints;
	for (auto i = 0; i < 19*19; i++)
		boardPoints.push_back(board.point(Coordinate(i % 19, i / 19)));
	return boardPoints;
}

Coordinate eddsonGomokuClient::getEnemysMove(BOARD_POINTS currentBoard, BOARD_POINTS lastBoard) {
	Coordinate coord = null_coord;
	for (auto i = 0; i < 19*19 - 1; i++)
	{
		if (!isMeOrEmpty(currentBoard[i]) && currentBoard[i] != lastBoard[i])
		{
			coord = Coordinate(i % 19, i / 19);
			break;
		}
	}
	return coord;
}

Coordinate subCoords(Coordinate a, Coordinate b) {
    return Coordinate(a.x - b.x, b.y - a.y);
}

Coordinate normalizeCoord(Coordinate a) {
    if (a.x > 0) a.x = 1;
    if (a.x < 0) a.x = -1;
    if (a.y > 0) a.y = 1;
    if (a.y < 0) a.y = -1;
    return a;
}

Coordinate eddsonGomokuClient::predictNextMove(BOARD_POINTS currentBoard, BOARD_POINTS lastBoard) {
    static Coordinate lastMove(-1, -1);
    Coordinate currentEnemyMove = this->getEnemysMove(currentBoard, lastBoard);
    if (isNullCoord(currentEnemyMove))
    {
        // Enemy hasn't made a move, move to random coord
        return Coordinate(rand() % 19, rand() % 19);
    }

    Coordinate dir = normalizeCoord(subCoords(lastMove, currentEnemyMove));

    int fyllesvin = 0;
    while (this->board->point(addCoords(currentEnemyMove, dir)) != EMPTY)
    {
        switch (fyllesvin)
        {
        case 0:
            dir.x++;
            break;
        case 1:
            dir.y++;
            break;
        case 2:
            dir.x = dir.x - 2;
            break;
        default:
            dir.y = dir.y - 2;
            break;
        }
        break;
        fyllesvin = ++fyllesvin % 4;
    }

    lastMove = currentEnemyMove;
    return addCoords(currentEnemyMove, dir);
}

/*

*/
Coordinate eddsonGomokuClient::make_a_move(Board& board) {
    static BOARD_POINTS lastBoard(19*19);
    BOARD_POINTS currentBoard = getBoardPoints(board);
    this->board = &board;

    Coordinate nextMove = this->predictNextMove(currentBoard, lastBoard);

	lastMove = nextMove;
	lastBoard = currentBoard;
	return nextMove;
}
