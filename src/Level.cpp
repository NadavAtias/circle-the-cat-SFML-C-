#include "Level.h"

//Constructor
//---------------------------------------------------------------
Level::Level()
{
	initButtons			    ();
	initRandomizeCircles    ();
}
//===============================================================
//                       Initialize functions                  //       
//===============================================================

void Level::initButtons()
{
	for (int i = 0; i < 2; i++)
	{
		auto buttonLoaction = ResourcesManagement::instance().designButton((float)20, (float)90 * i + 550);
		m_buttons.push_back(buttonLoaction);
	}

}

//---------------------------------------------------------------
// function that randomize diffrennt Circles that when a game
// starts they will be Ocupied.
//---------------------------------------------------------------
 std::vector<Position> Level::initRandomizeCircles()  
{
	std::vector<Position> randomizeCircles;
	int  diff = rand() % (3);

	Position randomCell;

	for (int i = 0; i < m_numOfRandomCircles - diff; ++i)
	{
		randomCell.first  = rand() % (11);
		randomCell.second = rand() % (11);
		if (std::find(randomizeCircles.begin(), randomizeCircles.end(), randomCell) == randomizeCircles.end())
		{
			randomizeCircles.push_back(randomCell);
		}
	}

	return randomizeCircles;
}

//===============================================================
//                       Set functions                         //
//===============================================================
void Level::updateLevelInfo() {
	 m_numOfRandomCircles -= 3;
}

//===============================================================
//                    Utilities functions                      //
//===============================================================
//---------------------------------------------------------------
void Level::draw(sf::RenderWindow& window) const{
	for (auto& button : m_buttons)
	{
		window.draw(button);
	}
}
//---------------------------------------------------------------
// function to highlight the button user hovering on
//---------------------------------------------------------------

void Level::hoverButtons(const curserPosition& currPositon) {

		for (auto& button : m_buttons)
		{
			if (button.getGlobalBounds().contains(currPositon))
				button.setFillColor(sf::Color(0, 245, 91, 40));
			else
				button.setFillColor(sf::Color::Transparent);
		}
}
//---------------------------------------------------------------
int Level::handleButtonClickEvent(const curserPosition& currPositon){

	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i].getGlobalBounds().contains(currPositon))
		{
			return i;
		}
	}

	return -1;
}

