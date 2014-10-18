#include "AndersGomoku.hpp"
#include <vector>
#include <iostream>

 // AndersGomoku::AndersGomoku(){}

AndersGomoku::AndersGomoku(PointType p ) : GomokuClient(p) {

}

Coordinate AndersGomoku::make_a_move(Board& b) {
    
    Coordinate c(3,3);
    
    std::vector<Coordinate> emptyPlaces;
    std::vector<Coordinate> myPlaces;
    std::vector<Coordinate> itsPlaces;
    
//    b.set_point(2,4,m_color);
//    b.set_point(3,6,m_color);
//    b.set_point(1,1,m_color);
    
    for(int i=0; i<19; ++i)
    {
        for(int j=0; j<19; ++j)
        {
            if ( b.point(i,j) == EMPTY) {
                emptyPlaces.push_back( Coordinate(i,j));
            } else if ( b.point(i,j) == m_color) {
                myPlaces.push_back( Coordinate(i,j));
            } else {
                itsPlaces.push_back( Coordinate(i,j));
            }
        }
    }

    for ( Coordinate coord : myPlaces) {
        Coordinate temp(coord.x+1, coord.y);
        if ( b.point( temp) == EMPTY ) {
            c.x = temp.x;
            c.y = temp.y;
        }
    }
    
/*    b.print_board();

    cout << emptyPlaces.size() << endl;
    cout << myPlaces.size() << endl;
    cout << itsPlaces.size() << endl; */
    
    return c;
}



