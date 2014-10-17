#include <iostream>
#include "gomoku_client.hpp"

// #include "din_client.cpp"
// typedef DinClient ClientType;

int main(int, char**)
{
	std::cout << "Gomoku AI challenge!" << std::endl;

	ClientType client(BLACK);
	Board b;
	Coordinate c = client.make_a_move(b);

	std::cout << "Your move: " << c.x << ", " << c.y << std::endl;

	return 0;
}
