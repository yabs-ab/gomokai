#include "gomoku_client.hpp"
#include <iostream>

using namespace std;

class NagyClient : public GomokuClient{

public:
    int max_depth;

   PointType his_color;

    NagyClient(PointType color) : GomokuClient(color)
    {
        his_color = m_color==WHITE ? BLACK : WHITE;
        max_depth = 6;
    }

    Coordinate make_a_move(Board& board)
    {

        int max_score = 0;
        int score = 0;
        int max_x = 10;
        int max_y = 10;
        for(int x=0;x<19;++x){
            for(int y=0;y<19;++y){
                if(board.point(x,y) == EMPTY){
                    board.set_point(x,y,m_color);
                    score = minmax(board,0,m_color);
                    board.set_point(x,y,EMPTY);
                    if(score > max_score){
                        max_x = x;
                        max_y = y;
                        max_score = score;
                   }
               }
            }
        }

        return Coordinate(max_x,max_y);
    }

    Coordinate make_a_move_test(Board& board)
    {
        int max_score = 0;
        int temp_score = 0;
        int max_x = 10;
        int max_y = 10;
        for(int x=0;x<19;++x){
            for(int y=0;y<19;++y){
                if(board.point(x,y) == EMPTY){
                    temp_score = move_score(board,m_color,x,y);
                    cout<<"score: "<<temp_score<<endl;
                    if(temp_score > max_score){
                        max_x = x;
                        max_y = y;
                        max_score = temp_score;
                   }
               }
            }
        }

        return Coordinate(max_x,max_y);

    }


   int minmax(Board board,int depth, PointType color){
        if(depth > max_depth || has_won(board,color)) {
            return score(board, color); 
        }

        if(color == m_color)
        {
            int max_score = -10000;
            for(int x=0;x<19;++x){
                for(int y=0;y<19;++y){
                    if(board.point(x,y) == EMPTY){
                        board.set_point(x,y,color);
                        int score = minmax(board, depth+1, his_color);
                        board.set_point(x,y,EMPTY);
                        max_score = score>max_score ? score : max_score;
                    }
                }
            }
            return max_score;
        }
        if(color == his_color)
        {
            int max_score = 10000;
            for(int x=0;x<19;++x){
                for(int y=0;y<19;++y){
                    if(board.point(x,y) == EMPTY){
                        board.set_point(x,y,color);
                        int score = minmax(board, depth+1, m_color);
                        board.set_point(x,y,EMPTY);
                        max_score = score>max_score ? max_score : score;
                    }
                }
            }
            return max_score;
        }
    }

    int score(Board board, PointType color)
    {
        PointType other_color = color==WHITE ? BLACK : WHITE;

        if(has_won(board,color)){ return 100000; }
        if(has_won(board,other_color)){ return -100000; }

        int adjacent_friends = total_adjacent_friends(board,color);

        return total_adjacent_friends(board, color);
    }

    int move_score(Board board, PointType color, int x, int y)
    {
        PointType other_color = color==WHITE ? BLACK : WHITE;

        //board.set_point(x,y,color);
        //if(has_won(board,color)){ return 100000; }
        //board.set_point(x,y,EMPTY);
        
        //board.set_point(x,y,other_color);
        //if(has_won(board,other_color)){ return 100000; }
        //board.set_point(x,y,EMPTY);

        board.set_point(x,y,color);
        int adjacent_friends = total_adjacent_friends(board,color);
        board.set_point(x,y,EMPTY);

        return total_adjacent_friends(board, color);
    }



    bool has_won(Board board, PointType color)
    {
       if(row_x(board,color)){ return true; } 
       if(row_y(board,color)){ return true; } 
       if(row_slash(board,color)){ return true; } 
       if(row_backslash(board,color)){ return true; } 

       return false;
    }

    bool row_x(Board board, PointType color)
    {
        for(int x=0;x<14;++x){
            for(int y=0;y<19;++y){
                if(board.point(x,y)==color &&
                    board.point(x+1,y)==color &&
                    board.point(x+2,y)==color &&
                    board.point(x+3,y)==color &&
                    board.point(x+4,y)==color)
                {
                    return true;
                }
            }
        }

        return false;
    }


    bool row_y(Board board, PointType color)
    {
        for(int x=0;x<19;++x){
            for(int y=0;y<14;++y){
                if(board.point(x,y)==color &&
                    board.point(x,y+1)==color &&
                    board.point(x,y+2)==color &&
                    board.point(x,y+3)==color &&
                    board.point(x,y+4)==color)
                {
                    return true;
                }
            }
        }

        return false;
    }


    bool row_slash(Board board, PointType color)
    {
        for(int x=0;x<14;++x){
            if( board.point(x,0)==color &&
                board.point(x+1,1)==color &&
                board.point(x+2,2)==color &&
                board.point(x+3,3)==color &&
                board.point(x+4,4)==color)
            {
                return true;
            }
        }
        for(int x=0;x<14;++x){
            if( board.point(x,5)==color &&
                board.point(x+1,6)==color &&
                board.point(x+2,7)==color &&
                board.point(x+3,8)==color &&
                board.point(x+4,9)==color)
            {
                return true;
            }
        }
        for(int x=0;x<14;++x){
            if( board.point(x,10)==color &&
                board.point(x+1,11)==color &&
                board.point(x+2,12)==color &&
                board.point(x+3,13)==color &&
                board.point(x+4,14)==color)
            {
                return true;
            }
        }
        for(int x=0;x<14;++x){
            if( board.point(x,14)==color &&
                board.point(x+1,15)==color &&
                board.point(x+2,16)==color &&
                board.point(x+3,17)==color &&
                board.point(x+4,18)==color)
            {
                return true;
            }
        return false;
        }
    }

    bool row_backslash(Board board, PointType color)
    {
        for(int x=0;x<14;++x){
            if( board.point(x,18)==color &&
                board.point(x+1,17)==color &&
                board.point(x+2,16)==color &&
                board.point(x+3,15)==color &&
                board.point(x+4,14)==color)
            {
                return true;
            }
        }
        for(int x=0;x<14;++x){
            if( board.point(x,13)==color &&
                board.point(x+1,12)==color &&
                board.point(x+2,11)==color &&
                board.point(x+3,10)==color &&
                board.point(x+4,9)==color)
            {
                return true;
            }
        }
        for(int x=0;x<14;++x){
            if( board.point(x,8)==color &&
                board.point(x+1,7)==color &&
                board.point(x+2,6)==color &&
                board.point(x+3,5)==color &&
                board.point(x+4,4)==color)
            {
                return true;
            }
        }
        for(int x=0;x<14;++x){
            if( board.point(x,4)==color &&
                board.point(x+1,3)==color &&
                board.point(x+2,2)==color &&
                board.point(x+3,1)==color &&
                board.point(x+4,0)==color)
            {
                return true;
            }
        return false;
        }
    }


    int adjacent_empties(Board board, PointType my_color, int x, int y)
    {
        int empties = 0;
        if(board.point(x+1,y) == EMPTY){ ++empties; }
        if(board.point(x-1,y) == EMPTY){ ++empties; }
        if(board.point(x,y+1) == EMPTY){ ++empties; }
        if(board.point(x,y-1) == EMPTY){ ++empties; }

        if(board.point(x-1,y-1) == EMPTY){ ++empties; }
        if(board.point(x+1,y-1) == EMPTY){ ++empties; }
        if(board.point(x-1,y+1) == EMPTY){ ++empties; }
        if(board.point(x+1,y+1) == EMPTY){ ++empties; }

        return empties;
    }

    int adjacent_friends(Board board, PointType my_color, int x, int y)
    {
        int friends = 0;
        if(board.point(x+1,y) == my_color){ ++friends; }
        if(board.point(x-1,y) == my_color){ ++friends; }
        if(board.point(x,y+1) == my_color){ ++friends; }
        if(board.point(x,y-1) == my_color){ ++friends; }

        if(board.point(x-1,y-1) == my_color){ ++friends; }
        if(board.point(x+1,y-1) == my_color){ ++friends; }
        if(board.point(x-1,y+1) == my_color){ ++friends; }
        if(board.point(x+1,y+1) == my_color){ ++friends; }

        return friends;
    }

    int adjacent_enemies(Board board, PointType my_color, int x, int y)
    {
        PointType his_color = my_color==WHITE ? BLACK : WHITE;

        int enemies = 0;
        if(board.point(x+1,y) == his_color){ ++enemies; }
        if(board.point(x-1,y) == his_color){ ++enemies; }
        if(board.point(x,y+1) == his_color){ ++enemies; }
        if(board.point(x,y-1) == his_color){ ++enemies; }

        if(board.point(x-1,y-1) == his_color){ ++enemies; }
        if(board.point(x+1,y-1) == his_color){ ++enemies; }
        if(board.point(x-1,y+1) == his_color){ ++enemies; }
        if(board.point(x+1,y+1) == his_color){ ++enemies; }

        return enemies;
    }

    int total_adjacent_empties(Board board, PointType my_color){
        int nr = 0;
        PointType his_color = my_color==WHITE ? BLACK : WHITE;

        for(int x=1; x<18; ++x){
            for(int y=1; y<18; ++y){
                if(board.point(x,y) == my_color)
                {
                    if(board.point(x+1,y) == EMPTY){ ++nr; }
                    if(board.point(x-1,y) == EMPTY){ ++nr; }
                    if(board.point(x,y+1) == EMPTY){ ++nr; }
                    if(board.point(x,y-1) == EMPTY){ ++nr; }

                    if(board.point(x-1,y-1) == EMPTY){ ++nr; }
                    if(board.point(x+1,y-1) == EMPTY){ ++nr; }
                    if(board.point(x-1,y+1) == EMPTY){ ++nr; }
                    if(board.point(x+1,y+1) == EMPTY){ ++nr; }
                }
            }
        }

        return nr;
    }

    int total_adjacent_friends(Board board, PointType my_color){
        int nr = 0;
        PointType his_color = my_color==WHITE ? BLACK : WHITE;

        for(int x=1; x<18; ++x){
            for(int y=1; y<18; ++y){
                if(board.point(x,y) == my_color)
                {
                    if(board.point(x+1,y) == my_color){ ++nr; }
                    if(board.point(x-1,y) == my_color){ ++nr; }
                    if(board.point(x,y+1) == my_color){ ++nr; }
                    if(board.point(x,y-1) == my_color){ ++nr; }

                    if(board.point(x-1,y-1) == my_color){ ++nr; }
                    if(board.point(x+1,y-1) == my_color){ ++nr; }
                    if(board.point(x-1,y+1) == my_color){ ++nr; }
                    if(board.point(x+1,y+1) == my_color){ ++nr; }
                }
            }
        }

        return nr;
    }

    int total_adjacent_enemies(Board board, PointType my_color){
        int nr = 0;
        PointType his_color = my_color==WHITE ? BLACK : WHITE;

        for(int x=1; x<18; ++x){
            for(int y=1; y<18; ++y){
                if(board.point(x,y) == my_color)
                {
                    if(board.point(x+1,y) == his_color){ ++nr; }
                    if(board.point(x-1,y) == his_color){ ++nr; }
                    if(board.point(x,y+1) == his_color){ ++nr; }
                    if(board.point(x,y-1) == his_color){ ++nr; }

                    if(board.point(x-1,y-1) == his_color){ ++nr; }
                    if(board.point(x+1,y-1) == his_color){ ++nr; }
                    if(board.point(x-1,y+1) == his_color){ ++nr; }
                    if(board.point(x+1,y+1) == his_color){ ++nr; }
                }
            }
        }

        return nr;
    }


};
