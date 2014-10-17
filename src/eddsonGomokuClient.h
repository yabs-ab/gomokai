#pragma once
#include <random>
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

	std::knuth_b generator;
	std::uniform_int_distribution<int> distribution;

	bool isMeOrEmpty(PointType);
	BOARD_POINTS* getBoardPoints(Board*);
	Coordinate getEnemysLastMove(BOARD_POINTS*, BOARD_POINTS*);
	Coordinate predictNextMove(Coordinate*, Coordinate*);
};

