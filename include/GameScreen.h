#pragma once

//------------------------ Include Section --------------------------

#include "ResourceManagment.h"

//--------------------------- Class Section --------------------------
const auto CONTER_POS = sf::Vector2f(115, 117);
const auto LEVEL_POS  = sf::Vector2f(114, 317);

class GameScreen
{
public:
	     GameScreen() ;
		~GameScreen() {};

		//---------------------------------------------------------------	
		//						Display functions
		//---------------------------------------------------------------
		void drawTransitionScreen(const enum Screen, sf::RenderWindow&);
		
		void draw(sf::RenderWindow&, const int , const int );
		
private:

	sf::Text m_text;
	void drawText(sf::RenderWindow&, const int ,const sf::Vector2f & );

};

