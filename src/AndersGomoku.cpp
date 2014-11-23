#include "AndersGomoku.hpp"
#include <list>
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

int AndersGomoku::check_n(Board& b, Coordinate c, PointType pt) {
    
    Coordinate temp(c.x, c.y);
    
    int ret_val = 0;
    int temp_score = 0;
    for ( auto dir : allDir ) {
        temp_score = check_val(b, c, dir, pt, 0);
        
        // Saturate the value (Should be not be sum, but wighted)
        if ( temp_score > ret_val ) ret_val = temp_score;
    }
    
    return ret_val;
}

Coordinate AndersGomoku::move(Coordinate c, Coordinate direction) {
    Coordinate temp(c.x + direction.x ,c.y + direction.y);
    return temp;
}

Coordinate AndersGomoku::moveBack(Coordinate c, Coordinate direction) {
    Coordinate temp(c.x - direction.x ,c.y - direction.y);
    return temp;
}


int AndersGomoku::check_val(Board& b, Coordinate c, Coordinate dir, PointType pt, int ret_val) {
    
    Coordinate neighb = move(c,dir);
    
    // input check
    if ( b.test_range(c)) return ret_val;
    
    // Moving of board, return less value
    if ( b.test_range(neighb)) return --ret_val;
    
    // What's behind me?
    if ( b.test_range(moveBack(c,dir))) {
        --ret_val;
    } else if (b.point(moveBack(c,dir)) == pt) {
        ++ret_val;
    } else if (b.point(moveBack(c,dir)) != pt && b.point(moveBack(c,dir)) != EMPTY) {
        --ret_val;
    }
    
    // nothing in this direction?
    if ( b.point(c) == EMPTY && b.point(neighb) == EMPTY)
        return ret_val;
    
    // one of right type
    if ( b.point(neighb) == pt) {
        ret_val = ret_val + 2;
        return check_val(b, neighb, dir, pt, ret_val);
    }
    
    // open row
    if ( b.point(c) == pt && b.point(neighb) == EMPTY) {
        return ++ret_val;
    }
    
    // all other cases
    return ret_val;
}

Coordinate AndersGomoku::make_a_move(Board& b) {
    
// List of possible placements
    std::list<Coordinate>  myPlaces;  myPlaces.push_back(Coordinate(9,9));
    std::list<Coordinate> itsPlaces; itsPlaces.push_back(Coordinate(9,9));

// Value of placements
    ScoreBoard mySB;
    ScoreBoard itsSB;
    int my_max_value  = 0;
    int its_max_value = 0;

// calculation of placments scores
    for(int i=0; i<19; ++i)
    {
        for(int j=0; j<19; ++j)
        {
            if ( b.point(i,j) == EMPTY) {
                mySB.set_point (i,j,check_n(b,Coordinate(i,j),m_color));
                itsSB.set_point(i,j,check_n(b,Coordinate(i,j),itsColor));
            } else if ( b.point(i,j) == m_color) {
                mySB.set_point(i,j,-1);
                itsSB.set_point(i,j,-1);
            } else {
                mySB.set_point(i,j,-2);
                itsSB.set_point(i,j,-2);
            }
            if (my_max_value < mySB.point(i,j)) {
                myPlaces.clear();
                my_max_value = mySB.point(i,j);
                myPlaces.push_back( Coordinate(i,j));
            }
            if (my_max_value == mySB.point(i,j)) myPlaces.push_back( Coordinate(i,j));

            if (its_max_value < itsSB.point(i,j)) {
                itsPlaces.clear();
                its_max_value = itsSB.point(i,j);
                itsPlaces.push_back( Coordinate(i,j));
            }
        }
    }
    
    
    //  Score printing
 //   itsSB.print_sboard();
 //   mySB.print_sboard();
 //   string tmp; getline(cin, tmp);

    // Attack or defense?
    if ( its_max_value > 6 ) {
        return itsPlaces.back();
    } else if ( my_max_value  > 2) {
        return choose_a_move(mySB, myPlaces);
    } else if ( itsPlaces.size() != 0 ) {
        return itsPlaces.back();
    }

    // Default return
    return Coordinate(0,0);
}

Coordinate AndersGomoku::choose_a_move(ScoreBoard& sb, std::list<Coordinate> places, int callTimes) {
    
    // ok, input?
    if ( places.size() == 0) return Coordinate(9,9);
    
    // Done?
    if ( places.size() == 1 or callTimes > 2) return places.back();

    
    // Calculate the max value
    int max = 0;
    int sum = 0;
    for ( Coordinate c : places) {
//        c.print();
        sum = add_n(sb,c);
        if (max < sum) max = sum;
    }
    
    // remove scores less then max
    for (auto i=std::begin( places); i != std::end(places); ) {
        sum = add_n(sb,*i );
        if ( sum < max) {
            i = places.erase( i );
        } else {
            ++i;
        }
    }
/*
    // set the new scores
    for ( Coordinate c : places) {
        c.print();
    }
  */
    
    // print
/*    cout << "redusing score board: " << endl;
    sb.print_sboard();
    string tmp; getline(cin, tmp);
    cout << "redusing score board, " << endl;
  */
    return choose_a_move(sb, places, ++callTimes);
}

int AndersGomoku::add_n(ScoreBoard& sb, Coordinate c, PointType pt) {
    
    int ret_val=0;
    int tmp =0;
    for ( auto dir : allDir ) {
        if ( !sb.test_range(move(c,dir))) {
            tmp = sb.point(move(c,dir));
            if (tmp > 0) ret_val = ret_val + tmp;
        }
    }
    return ret_val;
}



