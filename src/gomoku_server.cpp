#include <iostream>
#include <cstdlib>
#include "gomoku_client.hpp"

#include "randomclient.hpp"
#include "eddsonGomokuClient.h"

bool five_across(const Board& b, Coordinate c)
{
	return false;
}

bool five_down(const Board& b, Coordinate c)
{
	return false;
}

bool five_diagonally_right(const Board& b, Coordinate c)
{
	return false;
}

bool five_diagonally_left(const Board& b, Coordinate c)
{
	return false;
}

void fight(GomokuClient& a, GomokuClient& b)
{
	Board board;
	
	for (int i = 0; i < (19*19-1)/2; ++i) {
		board.set_point(a.make_a_move(a), WHITE);
		board.set_point(a.make_a_move(b), BLACK);
		
		board.print();
		std::system("sleep 1");
	}	
}

int main(int, char**)
{
	std::cout << "Gomoku AI challenge!" << std::endl;

	RandomClient a(WHITE);
	eddsonGomokuClient b(BLACK);

	fight(a, b);

	return 0;
}
