#pragma once
#include "gomoku_client.hpp"
class eddsonGomokuClient :
	public GomokuClient
{
public:
	eddsonGomokuClient();
	~eddsonGomokuClient();

	Coordinate make_a_move(Board&);
};

