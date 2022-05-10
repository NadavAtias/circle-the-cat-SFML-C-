#pragma once

//------------------------ Include Section --------------------------

#include "ResourceManagment.h"
#include "Board.h"
#include "Stack.h"
#include "GameObject.h"
#include <queue>
#include <array>

//------------------------ Const Section ----------------------------

const int SPRITE_DIMENSION = 90;

//------------------------ Class Section ----------------------------

class Cat : public GameObject
{
public:

	//					Constructors & Destructors
	//---------------------------------------------------------------
	 Cat(Board * ptrBoard);
	~Cat() {};

	//---------------------------------------------------------------	
	//						Set functions
	//---------------------------------------------------------------
	void resetCatPosition         ();
	void handleUndo               ();

	//----------------------------------------------------------------
	//				         Get Function           
	//----------------------------------------------------------------
	bool checkCatWin     () const;
	bool isAnimation     () const { return m_moveAnimation; }
	
	//---------------------------------------------------------------	
	//				      Utilities functions
	//---------------------------------------------------------------
	void draw            (sf::RenderWindow&);
	void drawEscapeCat   (sf::RenderWindow&);
	void move            ();
private:

	//				 Private functions
	//---------------------------------------------------------------
	void         initSpriteSheet();
	//---------------------------------------------------------------	
    //						Set functions
    //---------------------------------------------------------------
	sf::Vector2f eacapeDirection       ()          const;
	int          undoDirectionAnimation(const int) const;
	void setTextureRect();
	void calcCatDiffFromNextCircle(const float, const float);
	void catMovementAnimation     (sf::RenderWindow&);
	void centerSpriteImage        ();
	//				 Private members
	//---------------------------------------------------------------

    Position         m_offsetSpriteSheet;
	Stack <std::pair<Position,int>> m_catMoves;
	bool             m_moveAnimation;
	sf::Sprite       m_catSpriteImage ;
};
