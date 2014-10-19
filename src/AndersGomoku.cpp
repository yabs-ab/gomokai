#include "AndersGomoku.hpp"
#include <vector>
#include <iostream>

 // AndersGomoku::AndersGomoku(){}

AndersGomoku::AndersGomoku(PointType p ) : GomokuClient(p),
    dirBack(-1,0),
    dirForward(1,0),
    dirUp(0,-1),
    dirDown(0,1)
{

    allDir.push_back(dirForward);
    allDir.push_back(dirBack);
    allDir.push_back(dirUp);
    allDir.push_back(dirDown);
    allDir.push_back(move(dirForward,dirUp));
    allDir.push_back(move(dirBack, dirUp));
    allDir.push_back(move(dirForward,dirDown));
    allDir.push_back(move(dirBack,dirDown));
    
    if (m_color == WHITE)
        itsColor = BLACK;

}

int AndersGomoku::check_n(Board& b, Coordinate c) {
    
    Coordinate temp(c.x, c.y);
    
    int ret_val = 0;
    int temp_score = 0;
    for ( auto dir : allDir ) {
        temp_score = check_val(b, c, dir,0);
        if ( temp_score > ret_val ) ret_val = temp_score;
    }
    
    return ret_val;
}

Coordinate AndersGomoku::move(Coordinate c, Coordinate direction) {
    Coordinate temp(c.x + direction.x ,c.y + direction.y);
    return temp;
}

int AndersGomoku::check_val(Board& b, Coordinate c, Coordinate dir, int ret_val) {
    
    // still on the board?
    if ( b.test_range(c)) return ret_val;
    if ( b.test_range(move(c,dir))) return ret_val;
    
    // nothing in this direction?
    if ( b.point(c) == EMPTY && b.point(move(c,dir)) == EMPTY)
        return ret_val;
    
    // one neighbour
    if ( b.point(c) == EMPTY && b.point(move(c,dir)) != EMPTY) {
        ++ret_val;
        return check_val(b, move(c,dir), dir, ret_val);
    }
    
    // two in a row
    if ( b.point(c) == b.point(move(c,dir))) {
        ++ret_val;
        return check_val(b, move(c,dir), dir, ret_val);
    }
    
    // all other cases
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
    
    vector<int> max_point_i;
    int max_value = 0;
    for (int i = 0; i < emptyPlaces.size(); ++i) {
        sb.set_point( emptyPlaces[i], check_n(b, emptyPlaces[i]) );
        
        if ( max_value < sb.point( emptyPlaces[i])) {
            max_point_i.erase(max_point_i.begin());
            max_value = sb.point( emptyPlaces[i]);
        }

        if ( max_value == sb.point( emptyPlaces[i])) {
            max_point_i.push_back(i);
        }
    }
    
    sb.print_board();
    cout << "Max score:     " << max_value << endl;
    cout << "Num Max score: " << max_point_i.size() << endl;
    
    int index = max_point_i.back();
    
    return emptyPlaces[index];
}











