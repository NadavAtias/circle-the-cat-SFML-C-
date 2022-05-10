#include "GameScreen.h"

//-------------------------------------------------------------------------------
GameScreen::GameScreen()
{
	m_text = ResourcesManagement::instance().designText(sf::Vector2f(0, 0));
}
//-------------------------------------------------------------------------------
void GameScreen::draw(sf::RenderWindow& window, const int level, const int counter){

	drawText(window, counter, CONTER_POS);
	drawText(window, level, LEVEL_POS);
}
//-------------------------------------------------------------------------------
void GameScreen::drawText(sf::RenderWindow& window, const int data,const sf::Vector2f& position){
	m_text.setPosition(position);
	m_text.setString  (std::to_string(data));
	window.draw(m_text);
}

//-------------------------------------------------------------------------------
// transition screen of winning or losing ad for player.
//-------------------------------------------------------------------------------
void GameScreen::drawTransitionScreen(const enum Screen show, sf::RenderWindow& window) {
	
	sf::RectangleShape backgroaund({1280,720});
	sf::Sprite gameImage(ResourcesManagement::instance().getGameImage((int)show));
	
	backgroaund.setFillColor(sf::Color(255,255,255, 100));
	window.draw   (backgroaund);
	window.draw   (gameImage);
	window.display();
	sf::sleep     (sf::seconds(1.9));
}
