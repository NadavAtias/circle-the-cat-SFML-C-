#pragma once

//------------------------ Include Section --------------------------

#include "ResourceManagment.h"
#include "Level.h"
#include "Stack.h"

//------------------------ Const Section ----------------------------

using circles               = std::vector<std::vector<sf::CircleShape>>;
const auto     BLOCK_TILE   = sf::Color(0, 50, 100, 126);
const auto     UNBLOCK_TILE = sf::Color(0, 245, 91, 91) ;
const auto     VALID_MOVE   = sf::Color(0, 245, 91, 91) ;
const auto     UNVALID_MOVE = sf::Color(192, 69, 51, 90);
const int      LINE_SIZE    = 11; // for map of circle (11*11)
const double   OFFSET_X     = 71.2;
const double   OFFSET_Y     = 62.2;

//------------------------ Class Section ----------------------------

class Board
{
public:

	//					Constructors & Destructors
	//---------------------------------------------------------------
	 Board  ();
	~Board  () {};
	//---------------------------------------------------------------	
	//						Set functions
	//---------------------------------------------------------------
	void setObjectPosition(const Position& currPosition) { m_objectPosition = currPosition; }
	
	void rewindUncompleteLevel ();

	void implaceLevelCircles   (const std::vector<Position>&);

	//---------------------------------------------------------------	
	//						Get functions
	//---------------------------------------------------------------

	const Position&     getObjectPosition()  const { return m_objectPosition; }

	const sf::Vector2f& getCircleLocation(const Position& Circle) const { return m_mapCircle[Circle.first][Circle.second].getPosition(); }
	
   sf::CircleShape&     getCircle(const Position& Circle) { return m_mapCircle[Circle.first][Circle.second]; }
	
	bool                isValid	           (const Position&);
	//---------------------------------------------------------------	
	//					  Utilities functions
	//---------------------------------------------------------------
	void drawBoard              (sf::RenderWindow &   )     const ;
	
	bool handleCircleClickEvent (const curserPosition& );
	
	void trackingWithMouse      (const curserPosition&)      ;
	
    void  handleUndo            ();
private:
	//				 Private functions
	//---------------------------------------------------------------
	bool       unBlockedTile(const sf::CircleShape&) const;
	void       initMapCircle();
	
	//---------------------------------------------------------------	
	//						Set functions
	//---------------------------------------------------------------
	void setOutlineColor(sf::CircleShape&, const sf::Color&);


	void resetCirclesColor();

	void resetCircleColor(sf::CircleShape&);

	//				 Private members
	//---------------------------------------------------------------
	Stack <Position> m_undoMoves;
	Position         m_objectPosition;
	circles          m_mapCircle;
    
	
};
