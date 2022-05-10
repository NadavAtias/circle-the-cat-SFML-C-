#pragma once

//------------------------ Include Section --------------------------

#include "ResourceManagment.h"
#include "Board.h"
#include <queue>
#include <array>

//------------------------ Const Section ----------------------------

const std::pair<int, int> MEET_NEIGHBORS[2][6] = { { {1,-1}, {0,-1}  , {1, 0} ,{0,1}, {-1,-1},{-1,0}  } ,
												  {  {1, 0}, { 0,-1 }, {1, 1} ,{0,1}, {-1,0}, {-1,1} } };

//------------------------ Enum Section ----------------------------

enum Directions
{
	DownLeft, Left, DownRight, Right, UpLeft, UpRight

};

//--------------------------- Class Section --------------------------
class GameObject
{

public:
	
	//					Constructors & Destructors
	//--------------------------------------------------------------- 
	  GameObject(Board* board, const Position &); 
	 ~GameObject() {};
	
	//				Movment functions
	//---------------------------------------------------------------
	int  BFS            () ;
	
	int  reverseTrackBFS(const std::array<std::array<std::pair<Position, int>, LINE_SIZE>, LINE_SIZE>&, Position) ;
	
	int  randomMovment  ()  ;
	//---------------------------------------------------------------	
	//							 Set functions
	//---------------------------------------------------------------
	void                 setObjectNextPosition (const Position& nextPosition) { m_objectNextPosition = nextPosition; }
	
	void                 setObjectCurrPosition (const Position& );
	
	void                 setIsObjectStuck      (const bool status) { m_objectStuck = status;}

	void                 setIsPlayerWin        (const bool status) { m_playerWin = status;  }
	//---------------------------------------------------------------	
	//							 Get functions
	//---------------------------------------------------------------
	const Position&      getNextObjectPosition   () const;
	
	const sf::Vector2f & getObjectLoactionInBoard(const Position&) const;
	
	bool                 isObjectStuck           () const { return m_objectStuck; }
	
	bool				 isPlayerWin             () const { return m_playerWin;   }
	
	const Position&      getObjectPosition		 () const { return m_orignalBoard->getObjectPosition(); }
private:
	
	//Private functions
	//---------------------------------------------------------------
	bool         rowOffset(const int row) const { return row % 2 != 0; }

	//Private members
	//---------------------------------------------------------------	

	Position     m_objectNextPosition;
	Board*       m_orignalBoard;
	bool         m_objectStuck = false;
	bool         m_playerWin   = false;
	
};


