#include "gomoku_client.hpp"
#include <iostream>
#include <cstdlib>

class MyClient1 : public GomokuClient
{
	PointType opponentColor;

	public:
	bool nomovemade;

	bool check_if_in_range(int x, int y)
	{
		if(x>=0 && x<19 && y>=0 && y<19)
			return true;
		else return false;
	}

	Coordinate random_move(Board& board)
	{
		while(nomovemade)
		{
			int x = rand() % 19; 	
			int y = rand() % 19;
			Coordinate c(x,y);
			//std::cout<<x<<" "<<y<<std::endl;
			if(board.point(c)==EMPTY)
			{
				board.set_point(c,m_color);
				nomovemade=false;
				return c;
			}
		}

	}

	Coordinate go_over_the_board_three(PointType colortocheckfor, Board& board)
	{
		Coordinate c(-1,-1);
		for(int x=0; x<19; x++)
		{
			for(int y=0; y<19; y++)
			{
				//std::cout<<x<<" "<<y<<std::endl;
				PointType p = board.point(Coordinate(x,y));
				if(p==colortocheckfor)
				{
					//check vertically, horizontally, diagonally for 3 in a row

					//horizontal
					if(check_if_in_range(x+1,y) && board.point(Coordinate(x+1,y))==colortocheckfor && check_if_in_range(x+2,y) && board.point(Coordinate(x+2,y))==colortocheckfor)
					{
						//std::cout<<"checking.."<<std::endl;
						// put a point at x-1 or x+3 assuming they are still in range
						// and assuming those points are EMPTY and not colortocheckfor
						if( check_if_in_range(x-1,y) && board.point(Coordinate(x-1,y))==EMPTY )
						{
							std::cout<<"x+ check 1"<<std::endl;
							c=Coordinate(x-1,y);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if( check_if_in_range(x+3,y) && board.point(Coordinate(x+3,y))==EMPTY )
						{
							std::cout<<"x+ check 2"<<std::endl;
							c=Coordinate(x+3,y);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					else if(check_if_in_range(x-1,y) && board.point(Coordinate(x-1,y))==colortocheckfor && check_if_in_range(x-2,y) && board.point(Coordinate(x-2,y))==colortocheckfor)
					{
						//std::cout<<"checking.."<<std::endl;
						// put a point at x-3 or x+1 assuming they are still in range
						// and assuming those points are EMPTY and not colortocheckfor
						if( check_if_in_range(x-3,y) && board.point(Coordinate(x-3,y))==EMPTY )
						{
							std::cout<<"x- check 1"<<std::endl;
							c=Coordinate(x-3,y);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if( check_if_in_range(x+1,y) && board.point(Coordinate(x+1,y))==EMPTY )
						{
							std::cout<<"x- check 2"<<std::endl;
							c=Coordinate(x+1,y);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					//vertical
					else if(check_if_in_range(x,y+1) && board.point(Coordinate(x,y+1))==colortocheckfor && check_if_in_range(x,y+2) && board.point(Coordinate(x,y+2))==colortocheckfor) 
					{
						//std::cout<<"checking.."<<std::endl;
						// put a point at y-1 or y+3 assuming they are still in range
						// and assuming those points are EMPTY and not colortocheckfor
						if( check_if_in_range(x,y-1) && board.point(Coordinate(x,y-1))==EMPTY )
						{
							std::cout<<"y+ check 1"<<std::endl;
							c=Coordinate(x,y-1);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if( check_if_in_range(x,y+3) && board.point(Coordinate(x,y+3))==EMPTY )
						{
							std::cout<<"y+ check 2"<<std::endl;
							c=Coordinate(x,y+3);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					else if(check_if_in_range(x,y-1) && board.point(Coordinate(x,y-1))==colortocheckfor && check_if_in_range(x,y-2) && board.point(Coordinate(x,y-2))==colortocheckfor)
					{
						//std::cout<<"checking.."<<std::endl;
						// put a point at y-3 or y+1 assuming they are still in range
						// and assuming those points are EMPTY and not colortocheckfor
						if( check_if_in_range(x,y-3) && board.point(Coordinate(x,y-3))==EMPTY )
						{
							std::cout<<"y- check 1"<<std::endl;
							c=Coordinate(x,y-3);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if( check_if_in_range(x,y+1) && board.point(Coordinate(x,y+1))==EMPTY )
						{
							std::cout<<"y- check 2"<<std::endl;
							c=Coordinate(x,y+1);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}

					//diagonal
					else if ( (check_if_in_range(x-1,y-1) && board.point(Coordinate(x-1,y-1))==colortocheckfor ) && ( check_if_in_range(x+1,y+1) && board.point(Coordinate(x+1,y+1))==colortocheckfor ) )
					{
						//std::cout<<"checking.."<<std::endl;
						// put a point at x-2,y-2 OR x+2,y+2 assuming they are still in range
						// and assuming those points are EMPTY and not colortocheckfor
						if( check_if_in_range(x-2,y-2) && board.point(Coordinate(x-2,y-2))==EMPTY )
						{
							std::cout<<"x,y-"<<std::endl;
							c=Coordinate(x-2,y-2);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if( check_if_in_range(x+2,y+2) && board.point(Coordinate(x+2,y+2))==EMPTY )
						{
							std::cout<<"x,y+"<<std::endl;
							c=Coordinate(x+2,y+2);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
				}
			}
		}

	}

	Coordinate make_a_move(Board& board)
	{
		nomovemade=true;
		Coordinate c(-1,-1);
			
		//DEFENSE
		std::cout<<"defense"<<std::endl;
		c=go_over_the_board_three(opponentColor,board);
		//ATTACK
		if(nomovemade)
			std::cout<<"attack"<<std::endl;
			c=go_over_the_board_three(m_color,board); // checks only for already existing 3-same-color
		if(nomovemade)
			std::cout<<"random move"<<std::endl;
			 /* initialize random seed: */
			srand (time(NULL));
			c=random_move(board);
			// TODO: check for any of my own color, and make a new move near it
			//...
			// no own stuff, just make a move anywhere
			//std::cout<<"Making first move."<<std::endl;
			//Q: is there a strategic first move?
			//board.set_point(c,m_color);

		return c;
			//randomly put a point at some EMPTY area
			// or try to find your own 3-areas and try to continue that streak
	}
	MyClient1(PointType color) : GomokuClient(color) {
		opponentColor=m_color==WHITE?BLACK:WHITE;
		nomovemade=true;
	}
};

//int main()
//{
//	Board board;
//	MyClient1 client(WHITE);
//	client.make_a_move(board);
//
//	return 0;
//}
