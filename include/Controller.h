#pragma once

//------------------------- Include Section --------------------------

#include <vector>
#include <memory>
#include "Board.h"
#include "Level.h"
#include "Cat.h"
#include "GameScreen.h"

//------------------------- Events && Movement Section ---------------

const auto CLOSE_WINDOW   =      sf::Event::Closed;
const auto OBJECT_CLICKED =      sf::Event::MouseButtonReleased;
const auto MOUSEMOVED     =      sf::Event::MouseMoved;
const int  GAME_END       =      3;
const int  FRAME_LIMIT    =      18;

//----------------------------- Enums Section ------------------------

enum GameButtons
{
	Undo,Reset
};

//--------------------------- Class Section --------------------------
class Controller
{
public:
	
 
	//					Constructors & Destructors
	//---------------------------------------------------------------
	  Controller                  ();
	 ~Controller				  (){};
	
	//---------------------------------------------------------------
	//functions responsable for running the game
	//---------------------------------------------------------------
	
	void                         runWindow          ();

private:
	 //---------------------------------------------------------------
	 //                    Mangement Game Functions
	 //---------------------------------------------------------------
	 void                        render             ();
	 void                        pollEvents         ();
	 void                        handleCloseEvent   ();
	 void                        handleClickEvent   ();
	 void                        handleMouseMoved   ();
	 void                        handleGamePlay     ();
	 void                        handleGameOver     ();
	 void                        handleGameWin      ();
	 void                        catEscape          ();
	 
	 //---------------------------------------------------------------	
	 //							 Set functions
	 //---------------------------------------------------------------
	 void                        preSetLevel        ();
	 
	 //---------------------------------------------------------------	
	 //							 Get functions
	 //---------------------------------------------------------------
	 
	 const curserPosition        getCurserPosition  () const;
	 const bool                  running            () const;
	 
	 //---------------------------------------------------------------	
     //						Validation functions
	 //---------------------------------------------------------------
	 
	 void                        isCircleClicked    ()      ;
	 void                        isButtonClicked    ()      ;
	 
	 //------------------------- Members ----------------------------- 
	 
	 Board			   m_gameBoard;
	 GameScreen		   m_gameScreen;
	 Level             m_level;
	 Cat               m_cat;
	 int               m_counterSteps;
	 int               m_numLevel;
	 sf::RenderWindow  m_window;
	 sf::Event         m_event;
};

