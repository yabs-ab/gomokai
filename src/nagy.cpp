#include "gomoku_client.hpp"

class NagyClient : public GomokuClient{

public:
    NagyClient(PointType color) : GomokuClient(color)
    {

    }

    Coordinate make_a_move(Board &board)
    {
        make_a_move_1(board);

    }

    Coordinate make_a_move_1(Board &board)
    {
        int max_score = 0;
        int score = 0;
        int x_max = 0;
        int y_max = 0;

        for(int x=0;x<19;++x){
            for(int y=0;y<19;++y){
                if(board.point(x,y)==EMPTY){

                    board.set_point(x,y,m_color);
                    score = board_value1(board,m_color);
                    if(score>max_score){
                        max_score = score;
                        x_max = x;
                        y_max = y;
                    }
                    board.set_point(x,y,EMPTY);

                }
            }
        }

        return Coordinate(x_max,y_max);
    }

    int board_value1(Board board, PointType my_color)
    {
        return total_adjacent_friends(board,my_color);
    }

    bool is_winning_move(Board board, PointType my_color, int x, int y)
    {
        int i = x;
        int j = y;


        return true;
    }

    bool has_4_to_left(Board board, int x, int y)
    {
        if(x<4){ return false; }
        if(board.point(x-1) == m_color
            && board.point(x-2) == m_color
            && board.point(x-3) == m_color
            && board.point(x-4) == m_color )
        {
            return true;
        }
    }
    bool has_4_to_right(Board board, int x, int y)
    {
        if(x>14){ return false; }
        if(board.point(x+1) == m_color
            && board.point(x+2) == m_color
            && board.point(x+3) == m_color
            && board.point(x+4) == m_color )
        {
            return true;
        }
    }
    bool has_4_to_up(Board board, int x, int y)
    {
        if(y>14){ return false; }
        if(board.point(x+1) == m_color
            && board.point(x+2) == m_color
            && board.point(x+3) == m_color
            && board.point(x+4) == m_color )
        {
            return true;
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
