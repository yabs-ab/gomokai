#ifndef PETERSCLIENT_HPP_
#define PETERSCLIENT_HPP_

#include "gomoku_client.hpp"

class PetersClient : public GomokuClient {
	Board last;
public:
	PetersClient(PointType color)
		: GomokuClient(color)
	{
	}

	Coordinate make_a_move(Board& board);
};

#endif // PETERSCLIENT_HPP_
