#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include <SFML/OpenGL.hpp>

#include <string>
#include <iostream>
#include <fstream>  
#include <cstdlib>

const std::string GAME_IMAGES[] = { "boardScreen2.png", "Win.png","You Lose.png" };
const int NUM_OF_IMAGES = 3;

using curserPosition = sf::Vector2f;
using Position       = std::pair<int, int>;

enum Screen
{
	backGround,winScreen, LoseScreen
};

//----------------------------------------------------------------------------------
//   The ResourcesManagement class using Singleton method and
//   defines the `GetInstance` method that serves as an
//   alternative to constructor and lets clients access the same instance of this
//   class over and over.
//----------------------------------------------------------------------------------
class ResourcesManagement {

public:
	~ResourcesManagement() = default;
	static ResourcesManagement& instance();
	ResourcesManagement(const ResourcesManagement&) = delete; //Singletons should not be cloneable.
	void operator=     (const ResourcesManagement&) = delete; // Singletons should not be assignable.
	

	 //---------------------------------------------------------------	
	 //							 Get functions
	 //---------------------------------------------------------------
	sf::Texture&       getGameImage   (const int);
	sf::Texture&       getFigureImage ();
	sf::Font&          getfont        ();
	sf::Text           designText     (const sf::Vector2f &      );
	sf::RectangleShape designButton   (const float , const float );


private:
	//				 Private functions
	//---------------------------------------------------------------
	ResourcesManagement();
	void loadImages    ();
	
	// fonts
	//---------------------------------------------------------------
	sf::Font                             m_font;

	// Images 
	//---------------------------------------------------------------
	
	std::vector <sf::Texture>            m_gameImages;
	sf::Texture                          m_gameFigureImage;
};