#ifndef RANDOMCLIENT_HPP_
#define RANDOMCLIENT_HPP_

#include <random>
#include "gomoku_client.hpp"

class RandomClient : public GomokuClient {
public:
	RandomClient(PointType p)
		: GomokuClient(p)
		, e(0)
		, ud(0, 18)
	{
	}

	Coordinate make_a_move(Board& b)
	{
		Coordinate c(0, 0);

		do {
			c = Coordinate{ud(e), ud(e)};
		} while (b.point(Coordinate(ud(e), ud(e))) != EMPTY);

		return c;
	}
	
private:
	std::default_random_engine e;
	std::uniform_int_distribution<int> ud;
};

#endif // RANDOMCLIENT_HPP_
