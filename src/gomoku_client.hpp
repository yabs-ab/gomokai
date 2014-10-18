#ifndef GOMOKUCLIENT_HPP_
#define GOMOKUCLIENT_HPP_

#include <vector>
#include <iostream>

using namespace std;

class Coordinate {
public:
	int x;
	int y;
	Coordinate(int x_, int y_) : x(x_), y(y_) { }
};

enum PointType {
	EMPTY = 0,
	WHITE,
	BLACK
};

class Board {
public:
	struct OutOfRange {};
	
	Board()
		: m_board(19 * 19)
	{
	}

	PointType point(Coordinate coord)
	{
		if (test_range(coord))
			throw OutOfRange();

		return m_board[coord.x + 19 * coord.y];
	}

    bool test_range( Coordinate coord) {
        return coord.x < 0 || coord.x > 18 ||
        coord.y < 0 || coord.y > 18;
    }
    
	PointType point(int xIn, int yIn)
	{
		if (xIn < 0 || xIn > 18 ||
		    yIn < 0 || yIn > 18)
			throw OutOfRange();
		
		return m_board[xIn + 19 * yIn];
	}

	void set_point(Coordinate coord, PointType pointTypeIn)
	{
		if (coord.x < 0 || coord.x > 18 ||
		    coord.y < 0 || coord.y > 18)
			throw OutOfRange();

		m_board[coord.x + 19 * coord.y] = pointTypeIn;
	}

    void set_point(int xIn, int yIn, PointType pointTypeIn)
    {
	    if (xIn < 0 || xIn > 18 ||
		yIn < 0 || yIn > 18)
		    throw OutOfRange();
	    
	    m_board[xIn + 19 * yIn] = pointTypeIn;
    }

    void print_board()
    {
        for(int i=0; i<19; ++i)
        {
            for(int j=0; j<19; ++j)
            {
                if(point(j,i) == EMPTY) { cout<<" . "; }
                if(point(j,i) == BLACK) { cout<<" O "; }
                if(point(j,i) == WHITE) { cout<<" X "; }
            }
            cout<<endl;
        }
    }
	
private:
	std::vector<PointType> m_board;
};

class GomokuClient {
public:
	const PointType m_color;
	
	GomokuClient(PointType color)
		: m_color(color)
	{
	}

	virtual Coordinate make_a_move(Board& board) = 0;
};

#endif // GOMOKUCLIENT_HPP_
