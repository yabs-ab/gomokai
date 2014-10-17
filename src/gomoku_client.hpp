#ifndef GOMOKUCLIENT_HPP_
#define GOMOKUCLIENT_HPP_

class Coordinate {
public:
	int x;
	int y;
	Coordinate(int x_, int y_) : x(x_), y(y_) { }
};

class Board {
public:
	Board()
		: m_board(19 * 19)
	{
	}

	enum PointType {
		EMPTY = 0,
		WHITE,
		BLACK
	};
	

	PointType point(Coordinate coord)
	{
		return m_board[coord.x + 19 * coord.y];
	}

	void set_point(Coordinate coord, PointType pointType)
	{
		m_board[coord.x + 19 * coord.y] = pointType;
	}
	
private:
	std::vector<PointType> m_board;
};

class GomokuClient {
public:
	virtual Coordinate make_a_move(Board& board) = 0;
};

#endif // GOMOKUCLIENT_HPP_
