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

class ScoreBoard {
public:
    struct OutOfRange {};
    
    ScoreBoard()
    : m_board(19 * 19)
    {
    }
    
    int point(Coordinate coord)
    {
        if (test_range(coord))
            throw OutOfRange();
        
        return m_board[coord.x + 19 * coord.y];
    }
    
    bool test_range( Coordinate coord) {
        return coord.x < 0 || coord.x > 18 ||
        coord.y < 0 || coord.y > 18;
    }
    
    int point(int xIn, int yIn)
    {
        if (xIn < 0 || xIn > 18 ||
            yIn < 0 || yIn > 18)
            throw OutOfRange();
        
        return m_board[xIn + 19 * yIn];
    }
    
    void set_point(Coordinate coord, int i )
    {
        if (coord.x < 0 || coord.x > 18 ||
            coord.y < 0 || coord.y > 18)
            throw OutOfRange();
        
        m_board[coord.x + 19 * coord.y] = i ;
    }
    
    void set_point(int xIn, int yIn, int i )
    {
        if (xIn < 0 || xIn > 18 ||
            yIn < 0 || yIn > 18)
            throw OutOfRange();
        
        m_board[xIn + 19 * yIn] = i ;
    }
    
    void print_board()
    {
        for(int i=0; i<19; ++i)
        {
            for(int j=0; j<19; ++j)
            {
                if(point(j,i) == 0) {
                    cout << " . ";
                } else {
                    cout << " " << point(j,i) << " ";
                }
            }
            cout<<endl;
        }
    }
    
    std::vector<int> m_board;
};


