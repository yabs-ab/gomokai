#include <stdlib.h>

#include "eddiegom.h"

const Coordinate null_coord(-1, -1);

bool isEqualCoords(Coordinate a, Coordinate b) {
	return a.x == b.x && a.y == b.y;
}
Coordinate addCoords(Coordinate a, Coordinate b) {
    int x = (a.x + b.x < 18) ? a.x + b.x : 18; x = (x < 0) ? 0 : x;
    int y = (a.y + b.y < 18) ? a.y + b.y : 18; y = (y < 0) ? 0 : y;
	return Coordinate(x, y);
}

Coordinate subCoords(Coordinate a, Coordinate b) {
    return Coordinate(a.x - b.x, a.y - b.y);
}

Coordinate normalizeishCoord(Coordinate a) {
    if (a.x > 0) a.x = 1;
    if (a.x < 0) a.x = -1;
    if (a.y > 0) a.y = 1;
    if (a.y < 0) a.y = -1;
    return a;
}

bool isNullCoord(Coordinate coord) {
	return isEqualCoords(coord, null_coord);
}


eddiegom::eddiegom(PointType color) : GomokuClient(color)
{
}


eddiegom::~eddiegom()
{
}

bool eddiegom::isMeOrEmpty(PointType p) {
	return p == EMPTY || p == this->m_color;
}

BoardColors eddiegom::getBoardPoints(Board board) {
	BoardColors boardPoints;
	for (auto i = 0; i < 19*19; i++)
		boardPoints.push_back(board.point(Coordinate(i % 19, i / 19)));
	return boardPoints;
}


// Check if the board has changed at any coordinate. If it is the enemy then return the coordinate.
Coordinate eddiegom::getEnemysMove(BoardColors currBoardColors, BoardColors lastBoardColors) {
	Coordinate coord = null_coord;
	for (auto i = 0; i < 19*19 - 1; i++)
	{
		if (!isMeOrEmpty(currBoardColors[i]) && currBoardColors[i] != lastBoardColors[i])
		{
			coord = Coordinate(i % 19, i / 19);
			break;
		}
	}
	return coord;
}

Coordinate eddiegom::predictNextEnemyMove(BoardColors currBoardColors, BoardColors lastBoardColors) {
    static Coordinate lastMove(-1, -1);
    Coordinate predictedMove(-1, -1);

    Coordinate currentEnemyMove = this->getEnemysMove(currBoardColors, lastBoardColors);
    if (isNullCoord(currentEnemyMove))
    {
        // Enemy hasn't made a move, make a random move
        predictedMove = Coordinate(rand() % 19, rand() % 19);
    }
    else if (isNullCoord(lastMove)) {
        //Enemy has made a first move, predict its gonna be close
        do {
            predictedMove = addCoords(currentEnemyMove, Coordinate(rand() % 2, rand() % 2));
        } while (isEqualCoords(currentEnemyMove, predictedMove));
    }
    else {
        Coordinate enemyDirection = normalizeishCoord(subCoords(currentEnemyMove, lastMove));

        // Guess that the enemy is a fyllesvin, moving almost unpredictably
        // through the betongdjungel during a typical swedish lönehelg at 4am.
        int fyllesvin = 0;
        while (this->board->point(addCoords(currentEnemyMove, enemyDirection)) != EMPTY)
        {
            switch (fyllesvin)
            {
            case 0:
                enemyDirection.x++;
                break;
            case 1:
                enemyDirection.y++;
                break;
            case 2:
                enemyDirection.x -= 2;
                break;
            default:
                enemyDirection.y -= 2;
                break;
            }
            break;
            fyllesvin = ++fyllesvin % 4;
        }
        predictedMove = addCoords(currentEnemyMove, enemyDirection);
    }

    lastMove = currentEnemyMove;
    return predictedMove;
}

Coordinate eddiegom::make_a_move(Board& board) {
    static BoardColors lastBoardColors(19*19);
    BoardColors currBoardColors = this->getBoardPoints(board);
    this->board = &board;

    // Totally defensive algorithm sets my move to predicted move
    Coordinate nextMove = this->predictNextEnemyMove(currBoardColors, lastBoardColors);

	lastBoardColors = currBoardColors;
	return nextMove;
}
