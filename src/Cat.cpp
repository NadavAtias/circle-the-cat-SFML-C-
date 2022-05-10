#include "Cat.h"

//---------------------------------------------------------------
Cat::Cat(Board * board) 
	:GameObject(board, Position(5, 5)),m_offsetSpriteSheet(Position(0,0)),m_moveAnimation(false)
{
	initSpriteSheet();
}
//===============================================================================
//                             Init Function`s
//===============================================================================
void Cat::initSpriteSheet()
{
	m_catSpriteImage.setTexture (ResourcesManagement::instance().getFigureImage());
	m_catSpriteImage.setOrigin  ({ 7,10 });
	centerSpriteImage			();
	setTextureRect              ();
}

//===============================================================================
//                               Set Function`s
//===============================================================================

void Cat::setTextureRect()
{
	m_catSpriteImage.setTextureRect(sf::IntRect(m_offsetSpriteSheet.second * SPRITE_DIMENSION,
												m_offsetSpriteSheet.first * SPRITE_DIMENSION
						                      , SPRITE_DIMENSION, SPRITE_DIMENSION));
}

//---------------------------------------------------------------
void Cat::centerSpriteImage() {
	sf::Vector2f size = getObjectLoactionInBoard(getObjectPosition());
	m_catSpriteImage.setPosition(size.x - 8.f, size.y - 10.f);
}

//===============================================================
//                    Stack managment functions                 //
//===============================================================
//---------------------------------------------------------------
// Function that responsible for chain of event after player
// click Undo buttton.
//---------------------------------------------------------------
void Cat::handleUndo()
{
	setIsObjectStuck(false);
	auto prevMove   = m_catMoves.pop();
	m_moveAnimation = true;
	setObjectNextPosition(prevMove.first);
	m_offsetSpriteSheet.first = undoDirectionAnimation(prevMove.second);
	setTextureRect   ();
	centerSpriteImage();
}
//---------------------------------------------------------------
void Cat::resetCatPosition()
{
	m_offsetSpriteSheet = Position(0, 0);
	setIsObjectStuck     (false);
	m_catMoves.clearStack();
	m_moveAnimation    = false;
	setObjectCurrPosition(Position(5, 5));
	centerSpriteImage    ();
	setTextureRect       ();
}
//---------------------------------------------------------------
// Function that calculate the cat animaion.
// calc which sprite to render, and position of cat. 
//---------------------------------------------------------------
void Cat::catMovementAnimation(sf::RenderWindow& window)
{
	setTextureRect();
	sf::Vector2f currPosition = getObjectLoactionInBoard(getObjectPosition());
	sf::Vector2f nextPosition = getObjectLoactionInBoard(getNextObjectPosition());

	float deltaX = nextPosition.x - currPosition.x;
	float deltaY = nextPosition.y - currPosition.y;

	calcCatDiffFromNextCircle(deltaX / 7 * m_offsetSpriteSheet.second + 1, deltaY / 7 * m_offsetSpriteSheet.second - 25);

	m_offsetSpriteSheet.second++;
	if (m_offsetSpriteSheet.second  ==  7) {
		m_offsetSpriteSheet.second = 0;
		m_moveAnimation = false;
		setObjectCurrPosition(getNextObjectPosition());
		centerSpriteImage();
		window.setFramerateLimit(60);
	}
}
//===============================================================================
//                               Utilities Function`s
//===============================================================================
//---------------------------------------------------------------
void Cat::move()
{
	
	m_moveAnimation = true;
	
	auto pervPosition = getObjectPosition();

	if (!isObjectStuck())
		 m_offsetSpriteSheet.first = 	BFS();
	else
		m_offsetSpriteSheet.first  = randomMovment();

	m_catMoves.push   (std::make_pair(getObjectPosition(), m_offsetSpriteSheet.first));
}

//---------------------------------------------------------------
// Function to calc a small relative distance from current cat
// position to the next one. 
// ** For animation.  
//---------------------------------------------------------------
void Cat::calcCatDiffFromNextCircle(const float deltaX, const float deltaY)
{
	auto location = getObjectLoactionInBoard(getObjectPosition());
	m_catSpriteImage.setPosition(location.x + deltaX, location.y + deltaY);
}

//---------------------------------------------------------------
void Cat::draw(sf::RenderWindow& window)
{
	if (isAnimation())
	{
		catMovementAnimation(window);
	}

	window.draw(m_catSpriteImage);
}
//---------------------------------------------------------------
void Cat::drawEscapeCat(sf::RenderWindow& window){
	
	m_moveAnimation = false;
	sf::Vector2f currPosition = m_catSpriteImage.getPosition();
	auto delta = eacapeDirection();

	m_offsetSpriteSheet.second++;
	if (m_offsetSpriteSheet.second  ==  7) {
		m_offsetSpriteSheet.second = 4;
	}
	m_catSpriteImage.setPosition(currPosition.x + delta.x, currPosition.y + delta.y);
	setTextureRect();
}
//---------------------------------------------------------------
sf::Vector2f Cat ::eacapeDirection() const {
	auto row = m_offsetSpriteSheet.first;
	if (row == DownRight) return { 12, 12   };
	if (row == DownLeft ) return { -12, 12  };
	if (row == UpRight  ) return {-12, 12   };
	if (row == UpLeft   ) return { -12, -12 };
	if (row == Left     ) return { -12, 0   };
	if (row == Right    ) return { 12, 0    };

	return { 0,0 };
}
//---------------------------------------------------------------
int Cat::undoDirectionAnimation(const int row ) const
{
	
	if (row == DownRight) return UpLeft;
	if (row == DownLeft ) return UpRight;
	if (row == UpRight  ) return DownLeft;
	if (row == UpLeft   ) return DownRight;
	if (row == Left     ) return Right;
	

	return Left; // right 
}
//===============================================================================
//                               Validation Function`s
//===============================================================================

//---------------------------------------------------------------
bool Cat::checkCatWin() const {
	auto currPosition = getObjectPosition();
	return currPosition.first == 0 || currPosition.first == 10 || currPosition.second == 0 || currPosition.second == 10 && !m_moveAnimation;
}


