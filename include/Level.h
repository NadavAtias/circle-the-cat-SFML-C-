#pragma once
//------------------------ Include Section --------------------------

#include "ResourceManagment.h"
#include <algorithm>

//------------------------ Const Section ----------------------------
const int NUM_OF_TEXTS = 2;
//------------------------ Class Section ----------------------------
class Level
{
public:
	
	//Constructors & Destructors
    //---------------------------------------------------------------
	 Level ();
	~Level () {};

	//---------------------------------------------------------------	
	//							 Set functions
	//---------------------------------------------------------------
    std::vector<Position> initRandomizeCircles      () ;
	
	void				  updateLevelInfo           ( );
	//---------------------------------------------------------------	
	//				      Utilities functions
	//---------------------------------------------------------------

	void draw                     (sf::RenderWindow &) const;
	
	void hoverButtons             (const curserPosition&);
	
	int  handleButtonClickEvent   (const curserPosition& );

private:

	//				 Private functions
	//---------------------------------------------------------------
	void               initButtons();

	//				 Private members
	//---------------------------------------------------------------
	std::vector       <sf::RectangleShape>      m_buttons;
	int                                         m_numOfRandomCircles = 14;
};

