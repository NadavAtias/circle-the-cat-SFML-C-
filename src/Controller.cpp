#include "Controller.h"

//contructor & descontructor
//-------------------------------------------------------------------------------
Controller::Controller()
	:m_window(sf::RenderWindow(sf::VideoMode(1280, 720), "Circle The Cat")), m_event(), m_cat(&m_gameBoard),m_numLevel(1),m_counterSteps(0)
{
	m_gameBoard.implaceLevelCircles(m_level.initRandomizeCircles());
}

//===============================================================================
//                                 Get Function's 
//===============================================================================

//-------------------------------------------------------------------------------
const bool Controller::running() const
{
	return  m_window.isOpen();
}
//-------------------------------------------------------------------------------
const curserPosition Controller::getCurserPosition() const
{
	return m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
}

//===============================================================================
//                             Game managment Function`s
//===============================================================================

//-------------------------------------------------------------------------------
// function that runs the main loop of the game.
//-------------------------------------------------------------------------------
void Controller::runWindow() {


	//The main loop of the game
	while (running())
	{
		pollEvents();

		render();

		handleGamePlay();
	}
}

//-------------------------------------------------------------------------------
// function that handles Events from user input: 
// mouse movement, mouse clicks, exit game 
//-------------------------------------------------------------------------------
void Controller::pollEvents()
{

	while (m_window.pollEvent(m_event))
	{

		switch (m_event.type)
		{
		case CLOSE_WINDOW:
			handleCloseEvent();
			break;

		case OBJECT_CLICKED:
			handleClickEvent();
			break;

		case MOUSEMOVED:
			handleMouseMoved();
			break;
		}

	}
}
//-------------------------------------------------------------------------------
// functions that responsible for game logic. handles game over, level over,
// level lost etc . 
//-------------------------------------------------------------------------------
void Controller::handleGamePlay()
{

	handleGameOver();

	handleGameWin ();
	
}
//-------------------------------------------------------------------------------
// function that responsible for chain of event when player looses. 
// such, upadate and load next level, end game when 3 level completed. 
//-------------------------------------------------------------------------------
void Controller::handleGameOver()
{
	if (!m_cat.checkCatWin() ) return;

	catEscape();

	m_gameScreen.drawTransitionScreen(LoseScreen, m_window);

	m_cat         .resetCatPosition       ();

	m_gameBoard   .rewindUncompleteLevel  ();

	m_counterSteps = 0;
}
//-------------------------------------------------------------------------------
// function that display a short animation of the cat escaping the board.
//-------------------------------------------------------------------------------
void Controller::catEscape()
{
	sf::Clock showTime;
	m_window.setFramerateLimit(15);
	
	while (showTime.getElapsedTime().asSeconds() < 1.15) {
		m_cat.drawEscapeCat(m_window);
		render();
	}

	m_window.setFramerateLimit(60);

}

//-------------------------------------------------------------------------------
// function that responsible for chain of event when player wins.
// such, upadate and load next level, end game when 3 level completed. 
//-------------------------------------------------------------------------------
void Controller::handleGameWin(){

	if (!m_cat.isPlayerWin()) return;   

	m_gameScreen.drawTransitionScreen(winScreen, m_window);

	if (m_numLevel == GAME_END)
		m_window.close();

	m_level.updateLevelInfo();

	++m_numLevel;

	preSetLevel();
	m_cat  .setIsPlayerWin(false);
			

}
//-------------------------------------------------------------------------------
// function that responsible for preparing .
//-------------------------------------------------------------------------------
void Controller::preSetLevel(){

	m_cat       .resetCatPosition   ();
	m_gameBoard .implaceLevelCircles(m_level.initRandomizeCircles());
	m_counterSteps = 0;
}
//-------------------------------------------------------------------------------
// Display function 
//-------------------------------------------------------------------------------
void Controller::render()
{
	m_window.   clear     ();

	m_gameBoard.drawBoard(m_window);
	
	m_cat.      draw     (m_window);

	m_level.	draw	 (m_window);

	m_gameScreen.draw    (m_window, m_numLevel, m_counterSteps);

	m_window.display();
}

//--------------------------------------------------------------------------------
//                          User input managment functions  
//--------------------------------------------------------------------------------

//-------------------------------- handleCloseEvent ------------------------------
void Controller::handleCloseEvent() 
{
	m_window.close();
}

//-------------------------------- handleClickEvent ------------------------------
void Controller::handleClickEvent(){

	isCircleClicked();

	isButtonClicked();
}

//-------------------------------- handleMouseMoved ------------------------------
//Mouse hovering behavior over diffrent game objects (Circles, buttons, etc). 
//--------------------------------------------------------------------------------
void Controller::handleMouseMoved(){

	m_gameBoard.trackingWithMouse(getCurserPosition());
    m_level.     hoverButtons    (getCurserPosition());
}


//--------------------------------------------------------------------------------
//function to handle chain of event when player clicks a Circle.(or not)
//--------------------------------------------------------------------------------
void Controller::isCircleClicked(){

	if (!m_gameBoard.handleCircleClickEvent(getCurserPosition())) return;

		m_window.setFramerateLimit  (FRAME_LIMIT);
		m_cat	.move               ();
		++m_counterSteps;
}

//--------------------------------------------------------------------------------
//function to handle chain of event when player clicks a button.(or not)
//--------------------------------------------------------------------------------
void Controller::isButtonClicked(){

    int button = m_level.handleButtonClickEvent(getCurserPosition());

	switch (button)
	{
	case Undo: 
	{
		// exaption for stack poping
		try {
			m_window.   setFramerateLimit(FRAME_LIMIT);
			m_gameBoard.handleUndo();
			m_cat.      handleUndo();
			--m_counterSteps;
			break;
		}
		catch (const std::out_of_range&)
		{
			break;
		}	
	}
	case Reset:
	{
		preSetLevel();
		break;
	}

	default:
		break;
	}

}