#pragma once
#include "gomoku_client.hpp"

#define BOARD_POINTS std::vector<PointType>

class eddsonGomokuClient :
public GomokuClient
{
public:
	eddsonGomokuClient(PointType);
	~eddsonGomokuClient();

	Coordinate make_a_move(Board&);

private:
	Coordinate lastMove;
    Board* board;

	bool isMeOrEmpty(PointType);
	BOARD_POINTS getBoardPoints(Board);
	Coordinate getEnemysMove(BOARD_POINTS, BOARD_POINTS);
    Coordinate predictNextMove(BOARD_POINTS, BOARD_POINTS);
};

