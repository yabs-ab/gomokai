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
    
    // forward
    temp.x = temp.x+1;
    if (!b.test_range(temp))
        ret_val += check_val(b,temp);
    // back
    temp.x = temp.x-2;
    if (!b.test_range(temp) )
        ret_val += check_val(b,temp);
    // center
    temp.x = temp.x+1;
    
    // down
    temp.y = temp.y+1;
    if (!b.test_range(temp))
        ret_val += check_val(b,temp);
    // up
    temp.y = temp.y-2;
    if (!b.test_range(temp))
        ret_val += check_val(b,temp);
    
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
    std::vector<int> points;
    
    for(int i=0; i<19; ++i)
    {
        for(int j=0; j<19; ++j)
        {
            if ( b.point(i,j) == EMPTY) {
                emptyPlaces.push_back( Coordinate(i,j));
                points.push_back(0);
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
    for (int i = 0; i < emptyPlaces.size(); ++i) {
        points[i] = check_n(b, emptyPlaces[i]);
//        cout << ", " << points[i];
        if ( max_point_i < points[i])
            max_point_i = i;

    }
//    cout << endl;
    
    return emptyPlaces[max_point_i];
}



