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
	std::vector<PointType>* lastBoard;

	void getBoardPoints(Board*, BOARD_POINTS*);
	Coordinate getEnemysLastMove(BOARD_POINTS*, BOARD_POINTS*);
	Coordinate predictNextMove(Coordinate*, Coordinate*);
};

