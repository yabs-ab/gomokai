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
		return x>=0 && x<19 && y>=0 && y<19;
	}

	bool check_color_existence(int x, int y, PointType colortocheckfor, Board& board)
	{
		return check_if_in_range(x,y) && board.point(Coordinate(x,y))==colortocheckfor;
	}

	bool check_color_empty(int x, int y, Board& board)
	{
		return check_if_in_range(x,y) && board.point(Coordinate(x,y))==EMPTY;
	}

	Coordinate check_and_set_point_if_empty(int x, int y, Board& board)
	{
		if(check_color_empty(x,y,board))
		{
			Coordinate c(x,y);
			board.set_point(c,m_color);
			nomovemade=false;
			return c;
		}
		else return Coordinate(-1,-1);
	}

	//try to avoid making the random move on the edges of the Board
	Coordinate random_move(Board& board)
	{
		while(nomovemade)
		{
			//FIXME: only consider 18x18, is this a problem?
			// 1-17
			int x = rand() % 17+1;
			int y = rand() % 17+1;
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

	Coordinate make_move_near_my_own(Board& board)
	{
		Coordinate c(-1,-1);
		for(int x=0; x<19; x++)
		{
			for(int y=0; y<19; y++)
			{
				//std::cout<<x<<" "<<y<<std::endl;
				PointType p = board.point(Coordinate(x,y));
				if(p==m_color)
				{
					c=check_and_set_point_if_empty(x+1,y,board);
					if(!nomovemade)
						return c;
					c=check_and_set_point_if_empty(x-1,y,board);
					if(!nomovemade)
						return c;
					c=check_and_set_point_if_empty(x,y+1,board);
					if(!nomovemade)
						return c;
					c=check_and_set_point_if_empty(x,y-1,board);
					if(!nomovemade)
						return c;
					c=check_and_set_point_if_empty(x-1,y-1,board);
					if(!nomovemade)
						return c;
					c=check_and_set_point_if_empty(x+1,y+1,board);
					if(!nomovemade)
						return c;
				}
			}
		}
	}

	Coordinate go_over_the_board_four(PointType colortocheckfor, Board& board)
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
					//horizontal
					if(check_color_existence(x+1,y,colortocheckfor,board) && check_color_existence(x+2,y,colortocheckfor,board) && check_color_existence(x+3,y,colortocheckfor,board) )
					{
						if(check_color_empty(x+4,y,board))
						{
							std::cout<<"4) x+ check 1"<<std::endl;
							c=Coordinate(x+4,y);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if(check_color_empty(x-1,y,board))
						{
							std::cout<<"4) x+ check 2"<<std::endl;
							c=Coordinate(x-1,y);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					else if(check_color_existence(x,y-1,colortocheckfor,board) && check_color_existence(x,y-2,colortocheckfor,board) && check_color_existence(x,y-3,colortocheckfor,board) )
					{
						if(check_color_empty(x,y-4,board))
						{
							std::cout<<"4) y- check 1"<<std::endl;
							c=Coordinate(x,y-4);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if(check_color_empty(x,y+1,board))
						{
							std::cout<<"4) y- check 2"<<std::endl;
							c=Coordinate(x,y+1);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					else if(check_color_existence(x-1,y+1,colortocheckfor,board) && check_color_existence(x-2,y+2,colortocheckfor,board) && check_color_existence(x-3,y+3,colortocheckfor,board) )
					{
						if(check_color_empty(x-4,y+4,board))
						{
							std::cout<<"4) x,y/ check 1"<<std::endl;
							c=Coordinate(x-4,y+4);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if(check_color_empty(x+1,y-1,board))
						{
							std::cout<<"4) x,y/ check 2"<<std::endl;
							c=Coordinate(x+1,y-1);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					else if(check_color_existence(x-1,y-1,colortocheckfor,board) && check_color_existence(x-2,y-2,colortocheckfor,board) && check_color_existence(x-3,y-3,colortocheckfor,board) )
					{
						if(check_color_empty(x-4,y-4,board))
						{
							std::cout<<"4) x,y\\ check 1"<<std::endl;
							c=Coordinate(x-4,y-4);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if(check_color_empty(x+1,y+1,board))
						{
							std::cout<<"4) x,y\\ check 2"<<std::endl;
							c=Coordinate(x+1,y+1);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
				}
			}
		}

	
	}

	Coordinate go_over_the_board_three_unbounded(PointType colortocheckfor, Board& board)
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
					if(check_color_existence(x+1,y,colortocheckfor,board) && check_color_existence(x+2,y,colortocheckfor,board) && check_color_empty(x+3,y,board) && check_color_empty(x-1,y,board) )
					{
						// set point on either side, just choose one, it doesn't matter which one
						c=check_and_set_point_if_empty(x-1,y,board);
						if(!nomovemade)
							return c;
					}
					else if(check_color_existence(x,y+1,colortocheckfor,board) && check_color_existence(x,y+2,colortocheckfor,board) && check_color_empty(x,y+3,board) && check_color_empty(x,y-1,board) )
					{
						c=check_and_set_point_if_empty(x,y-1,board);
						if(!nomovemade)
							return c;
					}
					else if(check_color_existence(x+1,y+1,colortocheckfor,board) && check_color_existence(x+2,y+2,colortocheckfor,board) && check_color_empty(x+3,y+3,board) && check_color_empty(x-1,y-1,board) )
					{
						c=check_and_set_point_if_empty(x-1,y-1,board);
						if(!nomovemade)
							return c;
					}
					else if(check_color_existence(x+1,y-1,colortocheckfor,board) && check_color_existence(x+2,y-2,colortocheckfor,board) && check_color_empty(x+3,y-3,board) && check_color_empty(x-1,y+1,board) )
					{
						c=check_and_set_point_if_empty(x-1,y+1,board);
						if(!nomovemade)
							return c;
					}
				}
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
					else if(check_if_in_range(x+1,y) && board.point(Coordinate(x+1,y))==colortocheckfor && check_if_in_range(x+3,y) && board.point(Coordinate(x+3,y))==colortocheckfor)
					{
						if( check_if_in_range(x+2,y) && board.point(Coordinate(x+2,y))==EMPTY )
						{
							std::cout<<"x+ check 3"<<std::endl;
							c=Coordinate(x+2,y);
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
					else if(check_if_in_range(x-1,y) && board.point(Coordinate(x-1,y))==colortocheckfor && check_if_in_range(x-3,y) && board.point(Coordinate(x-3,y))==colortocheckfor)
					{
						if( check_if_in_range(x-2,y) && board.point(Coordinate(x-2,y))==EMPTY )
						{
							std::cout<<"x- check 3"<<std::endl;
							c=Coordinate(x-2,y);
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
					else if(check_if_in_range(x,y+1) && board.point(Coordinate(x,y+1))==colortocheckfor && check_if_in_range(x,y+3) && board.point(Coordinate(x,y+3))==colortocheckfor) 
					{
						if( check_if_in_range(x,y+2) && board.point(Coordinate(x,y+2))==EMPTY )
						{
							std::cout<<"y+ check 3"<<std::endl;
							c=Coordinate(x,y+2);
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
					else if(check_if_in_range(x,y-1) && board.point(Coordinate(x,y-1))==colortocheckfor && check_if_in_range(x,y-3) && board.point(Coordinate(x,y-3))==colortocheckfor) 
					{
						if( check_if_in_range(x,y-2) && board.point(Coordinate(x,y-2))==EMPTY )
						{
							std::cout<<"y- check 3"<<std::endl;
							c=Coordinate(x,y-2);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					//diagonal
					else if ( (check_if_in_range(x-1,y-1) && board.point(Coordinate(x-1,y-1))==colortocheckfor ) && ( check_if_in_range(x-2,y-2) && board.point(Coordinate(x-2,y-2))==colortocheckfor ) )
					{
						if( check_if_in_range(x-3,y-3) && board.point(Coordinate(x-3,y-3))==EMPTY )
						{
							std::cout<<"x,y- check 1"<<std::endl;
							c=Coordinate(x-3,y-3);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if( check_if_in_range(x+1,y+1) && board.point(Coordinate(x+1,y+1))==EMPTY )
						{
							std::cout<<"x,y- check 2"<<std::endl;
							c=Coordinate(x+1,y+1);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					else if ( (check_if_in_range(x+1,y+1) && board.point(Coordinate(x+1,y+1))==colortocheckfor ) && ( check_if_in_range(x+2,y+2) && board.point(Coordinate(x+2,y+2))==colortocheckfor ) )
					{
						if( check_if_in_range(x+3,y+3) && board.point(Coordinate(x+3,y+3))==EMPTY )
						{
							std::cout<<"x,y+ check 1"<<std::endl;
							c=Coordinate(x+3,y+3);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if( check_if_in_range(x-1,y-1) && board.point(Coordinate(x-1,y-1))==EMPTY )
						{
							std::cout<<"x,y+ check 2"<<std::endl;
							c=Coordinate(x-1,y-1);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					// Diagonal Check 2
					else if ( (check_if_in_range(x-1,y+1) && board.point(Coordinate(x-1,y+1))==colortocheckfor ) && ( check_if_in_range(x-2,y+2) && board.point(Coordinate(x-2,y+2))==colortocheckfor ) )
					{
						if( check_if_in_range(x-3,y+3) && board.point(Coordinate(x-3,y+3))==EMPTY )
						{
							std::cout<<"x,y+/ check 1"<<std::endl;
							c=Coordinate(x-3,y+3);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if( check_if_in_range(x+1,y-1) && board.point(Coordinate(x+1,y-1))==EMPTY )
						{
							std::cout<<"x,y+/ check 2"<<std::endl;
							c=Coordinate(x+1,y-1);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					else if ( (check_if_in_range(x+1,y-1) && board.point(Coordinate(x+1,y-1))==colortocheckfor ) && ( check_if_in_range(x+2,y-2) && board.point(Coordinate(x+2,y-2))==colortocheckfor ) )
					{
						if( check_if_in_range(x+3,y-3) && board.point(Coordinate(x+3,y-3))==EMPTY )
						{
							std::cout<<"x,y-/ check 1"<<std::endl;
							c=Coordinate(x+3,y-3);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
						else if( check_if_in_range(x-1,y+1) && board.point(Coordinate(x-1,y+1))==EMPTY )
						{
							std::cout<<"x,y-/ check 2"<<std::endl;
							c=Coordinate(x-1,y+1);
							board.set_point(c,m_color);
							nomovemade=false;
							return c;
						}
					}
					else if(check_if_in_range(x-1,y-1) && board.point(Coordinate(x-1,y-1))==colortocheckfor && check_if_in_range(x+2,y+2) && board.point(Coordinate(x+2,y+2))==colortocheckfor) 
					{
						if( check_if_in_range(x+1,y+1) && board.point(Coordinate(x+1,y+1))==EMPTY )
						{
							std::cout<<"x,y check 3"<<std::endl;
							c=Coordinate(x+1,y+1);
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

		//DEFENSE and ATTACK for 4s
		std::cout<<"attack lead"<<std::endl;
		c=go_over_the_board_four(m_color,board);
		if(!nomovemade)
			std::cout<<">> Ozan won!"<<std::endl;
		if(nomovemade)
		{
			std::cout<<"defense lead"<<std::endl;
			c=go_over_the_board_four(opponentColor,board);
		}
		//DEFENSE and ATTACK for 3s
		if(nomovemade)
		{
			std::cout<<"defense support 1"<<std::endl;
			c=go_over_the_board_three_unbounded(opponentColor,board);
			if(nomovemade)
			{
				std::cout<<"defense support 2"<<std::endl;
				c=go_over_the_board_three(opponentColor,board);
			}
		}
		//ATTACK
		if(nomovemade)
		{
			std::cout<<"attack support 1"<<std::endl;
			c=go_over_the_board_three_unbounded(m_color,board); // checks only for already existing 3-same-color
			if(nomovemade)
			{
				std::cout<<"attack support 2"<<std::endl;
				c=go_over_the_board_three(m_color,board); // checks only for already existing 3-same-color
			}
		}
		if(nomovemade)
		{
			std::cout<<"random attack"<<std::endl;
			c=make_move_near_my_own(board);
		}
		if(nomovemade)
		{
			// no own stuff, just make a move anywhere
			//Q: is there a strategic first move?
			// RANDOM MOVE
			std::cout<<"random move"<<std::endl;
			/* initialize random seed: */
			srand (time(NULL));
			c=random_move(board);
		}
		return c;
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
