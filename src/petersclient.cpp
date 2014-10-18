#include "petersclient.hpp"

Coordinate choose(Board& b, Coordinate c, bool defend = true)
{
	PointType mid;

	if (defend)
		mid = b.point(c);
	else
		mid = b.point(c) == WHITE ? BLACK : WHITE;
	
	try {
		if (b.point(c.x - 1, c.y - 1) == mid &&
		    b.point(c.x + 1, c.y + 1) == EMPTY)
			return Coordinate(c.x + 1, c.y + 1);
	}
	catch (...) {}

	try {
		if (b.point(c.x + 1, c.y - 1) == mid &&
		    b.point(c.x - 1, c.y + 1) == EMPTY)
			return Coordinate(c.x - 1, c.y + 1);
	}
	catch (...) {}

	try {
		if (b.point(c.x + 1, c.y + 1) == mid &&
		    b.point(c.x - 1, c.y - 1) == EMPTY)
			return Coordinate(c.x - 1, c.y - 1);
	}
	catch (...) {}

	try {
		if (b.point(c.x - 1, c.y + 1) == mid &&
		    b.point(c.x + 1, c.y - 1) == EMPTY)
			return Coordinate(c.x + 1, c.y - 1);
	}
	catch (...) {}

	try {
		if (b.point(c.x + 1, c.y) == mid &&
		    b.point(c.x - 1, c.y) == EMPTY)
			return Coordinate(c.x - 1, c.y);
	}
	catch (...) {}

	try {
		if (b.point(c.x - 1, c.y) == mid &&
		    b.point(c.x + 1, c.y) == EMPTY)
			return Coordinate(c.x + 1, c.y);
	}
	catch (...) {}

	try {
		if (b.point(c.x, c.y + 1) == mid &&
		    b.point(c.x, c.y - 1) == EMPTY)
			return Coordinate(c.x, c.y - 1);
	}
	catch (...) {}

	try {
		if (b.point(c.x, c.y - 1) == mid &&
		    b.point(c.x, c.y + 1) == EMPTY)
			return Coordinate(c.x, c.y + 1);
	}
	catch (...) {}



	try { if (b.point(c.x + 1, c.y + 1) == EMPTY) return Coordinate(c.x + 1, c.y + 1); } catch (...) {}
	try { if (b.point(c.x - 1, c.y + 1) == EMPTY) return Coordinate(c.x - 1, c.y + 1); } catch (...) {}
	try { if (b.point(c.x - 1, c.y - 1) == EMPTY) return Coordinate(c.x - 1, c.y - 1); } catch (...) {}
	try { if (b.point(c.x + 1, c.y - 1) == EMPTY) return Coordinate(c.x + 1, c.y - 1); } catch (...) {}
	try { if (b.point(c.x - 1, c.y) == EMPTY) return Coordinate(c.x - 1, c.y); } catch (...) {}
	try { if (b.point(c.x + 1, c.y) == EMPTY) return Coordinate(c.x + 1, c.y); } catch (...) {}
	try { if (b.point(c.x, c.y - 1) == EMPTY) return Coordinate(c.x, c.y - 1); } catch (...) {}
	try { if (b.point(c.x, c.y + 1) == EMPTY) return Coordinate(c.x, c.y + 1); } catch (...) {}
	


	return Coordinate(0, 0);
}

Coordinate last_move(Board a, Board b, PointType color)
{
	for (int x = 0; x < 19; ++x)
		for (int y = 0; y < 19; ++y)
			if (a.point(x,y) != b.point(x,y) &&
			    a.point(x,y) != color)
				return Coordinate(x,y);
}

bool all_empty(Board b)
{
	for (int x = 0; x < 19; ++x)
		for (int y = 0; y < 19; ++y)
			if (b.point(x, y) != EMPTY)
				return false;
	return true;
}

Coordinate PetersClient::make_a_move(Board& board)
{
	std::cout << "huhuhu" << std::endl;
	if (all_empty(board))
		return Coordinate(9,9);
	std::cout <<"dddddhuhuhu" << std::endl;
	auto res = choose(board, last_move(last, board, m_color));

	std::cout <<  "-----------> " <<res.x << ", " <<res. y << std::endl;
	
	last = board;

	return res;
}
