#pragma once
#include "gomoku_client.hpp"

typedef std::vector<PointType> BoardColors;

class eddiegom :
public GomokuClient
{
public:
	eddiegom(PointType);
	~eddiegom();

	Coordinate make_a_move(Board&);

private:
    Board* board;

	bool isMeOrEmpty(PointType);
	BoardColors getBoardPoints(Board);
	Coordinate getEnemysMove(BoardColors, BoardColors);
    Coordinate predictNextEnemyMove(BoardColors, BoardColors);
};

