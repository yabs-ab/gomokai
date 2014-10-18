#pragma once
#include "gomoku_client.hpp"
class AndersGomoku : GomokuClient {
public:
//	AndersGomoku();
    AndersGomoku(PointType);
//	~AndersGomoku();

	Coordinate make_a_move(Board&);
};

