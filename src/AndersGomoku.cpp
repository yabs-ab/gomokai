#include "AndersGomoku.hpp"
#include <vector>
#include <iostream>

 // AndersGomoku::AndersGomoku(){}

AndersGomoku::AndersGomoku(PointType p ) : GomokuClient(p) {

    if (m_color == WHITE)
        itsColor = BLACK;
    
}

int AndersGomoku::check_n(Board& b, Coordinate c) {
    //
    //
    //
    
    Coordinate temp(c.x, c.y);
    
    int ret_val = 0;
    
    // forward (x+1)
    temp.x = temp.x+1;
    if (!b.test_range(temp)) ret_val += check_val(b,temp);
    // back (x-1)
    temp.x = temp.x-2;
    if (!b.test_range(temp) ) ret_val += check_val(b,temp);
    // center
    temp.x = temp.x+1;
    
    // down (y+1)
    temp.y = temp.y+1;
    if (!b.test_range(temp)) ret_val += check_val(b,temp);
    // up (y-1)
    temp.y = temp.y-2;
    if (!b.test_range(temp)) ret_val += check_val(b,temp);
    
    // up (y-1), forward (x+1)
    temp.x = temp.x+1;
    if (!b.test_range(temp)) ret_val += check_val(b,temp);
    
    // down (y+1), forward (x+1)
    temp.y = temp.y+2;
    if (!b.test_range(temp)) ret_val += check_val(b,temp);
    
    // down (y+1), back (x-1)
    temp.x = temp.x-2;
    if (!b.test_range(temp)) ret_val += check_val(b,temp);

    // up (y-1), back (x+1)
    temp.y = temp.y-2;
    if (!b.test_range(temp)) ret_val += check_val(b,temp);
    
    return ret_val;
}

int AndersGomoku::check_val(Board& b, Coordinate c) {
    if (b.point(c) == m_color) {
        return 1;
    } else if (b.point(c) == itsColor) {
            return -1;
    }
    return 0;
}


Coordinate AndersGomoku::make_a_move(Board& b) {
    
    std::vector<Coordinate> emptyPlaces;
    std::vector<Coordinate> myPlaces;
    std::vector<Coordinate> itsPlaces;

    ScoreBoard sb;
    
    for(int i=0; i<19; ++i)
    {
        for(int j=0; j<19; ++j)
        {
            if ( b.point(i,j) == EMPTY) {
                emptyPlaces.push_back( Coordinate(i,j));
                sb.set_point(i,j,0);
            } else if ( b.point(i,j) == m_color) {
                myPlaces.push_back( Coordinate(i,j));
            } else {
                itsPlaces.push_back( Coordinate(i,j));
            }
        }
    }

    // init draw
    Coordinate c(3,3);
    if ( b.point(c.x,c.y) == EMPTY ) {
        return c;
    }
    
    int max_point_i=0;
    int max_value = 0;
    for (int i = 0; i < emptyPlaces.size(); ++i) {
        sb.set_point( emptyPlaces[i], check_n(b, emptyPlaces[i]) );
        
        if ( max_value < sb.point( emptyPlaces[i])) {
            max_point_i = i;
            max_value = sb.point( emptyPlaces[i]);
        }

    }
    
//    sb.print_board();
    cout << "Max score: " << max_value << endl;
    
    return emptyPlaces[max_point_i];
}











