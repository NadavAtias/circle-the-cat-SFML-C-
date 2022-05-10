#include "Board.h"

//Constructor
//---------------------------------------------------------------
// build game board
//---------------------------------------------------------------

Board::Board(){
	m_mapCircle.reserve   (121);
	initMapCircle         ();
}

//===============================================================
//                    Utilities functions                      //
//===============================================================

//---------------------------------------------------------------
// Function to draw the game board
//---------------------------------------------------------------
void Board::drawBoard(sf::RenderWindow& window) const
{
	static sf::Sprite gameImage(ResourcesManagement::instance().getGameImage(0));
	
	window.draw(gameImage);

	for (const auto& circleRow : m_mapCircle)
	{
		for (const auto& circle : circleRow)
		{
			window.draw(circle);
		}
	}

}
//---------------------------------------------------------------
// Function to handle event when user clicking on a Circle (or not)
//---------------------------------------------------------------
bool Board::handleCircleClickEvent(const curserPosition& currPositon)
{
	
	Position newCircle;
	newCircle.first = newCircle.second = 0;
	for ( auto& circleRow : m_mapCircle)
	{
		newCircle.second = 0;
		for ( auto& circle : circleRow)
		{
			if (circle.getGlobalBounds().contains(currPositon) && unBlockedTile(circle))
			{
				m_undoMoves. push        (newCircle);
				circle     . setFillColor(BLOCK_TILE);
				return true;
			}
			newCircle.second++;
		}
		newCircle.first++;
	}
	return false;
}
//---------------------------------------------------------------
// Function that present the user UI for hovering over board 
// behaviour.
//---------------------------------------------------------------
void Board::trackingWithMouse(const curserPosition& currPositon)
{

	for (auto& circleRow : m_mapCircle)
	{
		for (auto& circle : circleRow)
		{
			if (circle.getGlobalBounds().contains(currPositon))
				unBlockedTile(circle) ? setOutlineColor(circle, VALID_MOVE) :
				setOutlineColor(circle, UNVALID_MOVE);
			else
				circle.setOutlineColor(sf::Color::Transparent);
		}
	}
}

//---------------------------------------------------------------
// Function that enters a new set of "ocuipied circles" 
// to the  board .
//---------------------------------------------------------------
void Board::implaceLevelCircles(const std::vector<Position>& randomCircles)
{

	resetCirclesColor();

	for (const auto& randomCircle : randomCircles)
	{
		if(randomCircle != getObjectPosition() )
		m_mapCircle[randomCircle.first][randomCircle.second].setFillColor(BLOCK_TILE);
	}
}

//===============================================================
//                    Stack managment functions                 //
//===============================================================

//---------------------------------------------------------------
void Board::handleUndo()
{
	auto prevMove = m_undoMoves.pop();
	resetCircleColor(getCircle(prevMove));
}
//---------------------------------------------------------------
void Board::rewindUncompleteLevel()
{

	while (!m_undoMoves.isEmpty()) {
		handleUndo();
	}
}

//===============================================================
//                    Validation functions                     //
//===============================================================

//---------------------------------------------------------------
// Function to check if Circle is available by his color, or the
// Circle is not out of board limit.
//---------------------------------------------------------------
bool Board::isValid(const Position& cell) 
{
	// If cell lies out of bounds
	if (cell.first < 0 || cell.second < 0
		|| cell.first >= LINE_SIZE || cell.second >= LINE_SIZE)
		return false;

	// If cell is already visited
	if (!unBlockedTile(getCircle(cell)))
		return false;

	// Otherwise
	return true;
}

//---------------------------------------------------------------
// Function to check if circle is available by his color.
//---------------------------------------------------------------

bool Board::unBlockedTile(const sf::CircleShape& circle) const
{
	return circle.getFillColor() != BLOCK_TILE && circle.getPosition() != getCircleLocation(m_objectPosition);
}


//===============================================================
//                   Init functions 
//===============================================================

//---------------------------------------------------------------
void Board::initMapCircle()
{

	auto circle = sf::CircleShape(27);
	circle.setOutlineThickness   (7.f);
	circle.setOutlineColor	     (sf::Color::Transparent);


	std::vector<sf::CircleShape> circleRow;
	for (auto i = 0; i < LINE_SIZE; ++i) {
		circleRow.clear();
		circleRow.reserve(11);
		for (auto j = 0; j < LINE_SIZE; ++j) {
			
			if (i % 2 == 0)
				circle.setPosition(328 + j * OFFSET_X, 27 + float(i * OFFSET_Y));
			else
				circle.setPosition(359 + j * OFFSET_X, 27 + float(i * OFFSET_Y));
			
			circleRow.push_back(circle);
		}
		m_mapCircle.push_back(circleRow);
	}
    
}

//---------------------------------------------------------------
void Board::resetCirclesColor() {

	for (auto& circleRow : m_mapCircle)
	{
		for (auto& circle : circleRow)
		{
			resetCircleColor(circle);
		}
	}
}

//---------------------------------------------------------------
void Board::resetCircleColor(sf::CircleShape& circle) {

	circle.setFillColor(UNBLOCK_TILE);
}

//===============================================================
//                       Set functions                         //
//===============================================================

//---------------------------------------------------------------
void Board::setOutlineColor(sf::CircleShape& circle, const sf::Color& color) {

	circle.setOutlineColor(color);
}

