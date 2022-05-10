#include "ResourceManagment.h"

//Constructor
//---------------------------------------------------------------
ResourcesManagement::ResourcesManagement() {
	
	loadImages();
	m_font           .loadFromFile ("Baguette.ttf");
	m_gameFigureImage.loadFromFile ("cat.png"); 
	m_gameFigureImage.setSmooth    (true);

}
//---------------------------------------------------------------
void ResourcesManagement::loadImages()
{
	sf::Texture image;
	for(auto i = 0 ; i < NUM_OF_IMAGES; ++i ){
		image.loadFromFile(GAME_IMAGES[i]);
		image.setSmooth(true);
		m_gameImages.push_back(image);
		
	}
}

//---------------------------------------------------------------
ResourcesManagement& ResourcesManagement::instance()
{
	static ResourcesManagement instance;
	return instance;
}
//===============================================================
//                     Multi Usage functions
//===============================================================
//---------------------------------------------------------------
// function to Design the text 
//---------------------------------------------------------------

sf::Text ResourcesManagement::designText(const sf::Vector2f& loaction)
{
	sf::Text text;

	text.setFont         (ResourcesManagement::instance().getfont());
	text.setCharacterSize(45);
	text.setColor        (sf::Color().Black);
	text.setStyle        (1);
	text.setPosition     (loaction);

	return text;
}

//---------------------------------------------------------------
// function to Design a button 
//---------------------------------------------------------------

sf::RectangleShape ResourcesManagement::designButton(const float row, const float col)
{
	sf::RectangleShape  buttonLoaction({ 125,59 });
	sf::Vector2f        Loaction      (row, col);
	buttonLoaction.setPosition        (Loaction);
	buttonLoaction.setFillColor       (sf::Color(255, 255, 255, 0));
	buttonLoaction.setOutlineThickness(3.f);
	buttonLoaction.setOutlineColor    (sf::Color().Black);

	return  buttonLoaction;
}

//===============================================================
//                      Get Function's 
//===============================================================

sf::Texture& ResourcesManagement::getGameImage(const int wantedImage)
{
	return m_gameImages[wantedImage];

}
//---------------------------------------------------------------

sf::Texture& ResourcesManagement::getFigureImage()
{
	return m_gameFigureImage;
}

//---------------------------------------------------------------

sf::Font& ResourcesManagement::getfont()
{
	return m_font;
}
