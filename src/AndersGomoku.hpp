#pragma once
#include "gomoku_client.hpp"
class AndersGomoku : public GomokuClient {
public:

    AndersGomoku(PointType);
    
    // default
    PointType itsColor=WHITE;
    
	Coordinate make_a_move(Board&);
    int check_n(Board& b, Coordinate c);
    int check_val(Board& b, Coordinate c);
};

