#include "GameObject.h"


//Constructor
//---------------------------------------------------------------
// build game board
//---------------------------------------------------------------
GameObject::GameObject(Board* board, const Position& startPosition)
	:m_orignalBoard(board)
{
	setObjectCurrPosition(startPosition);
}

//===============================================================================
//                               Get Function`s
//===============================================================================

//---------------------------------------------------------------
const Position& GameObject::getNextObjectPosition() const
{
	return m_objectNextPosition;
}
//---------------------------------------------------------------
const sf::Vector2f& GameObject::getObjectLoactionInBoard(const Position & objectPosition) const
{
    return m_orignalBoard->getCircleLocation(objectPosition);
}
//===============================================================================
//                               Set Function`s
//===============================================================================

void GameObject::setObjectCurrPosition(const Position& Position)
{
	m_orignalBoard->setObjectPosition(Position);
}

//===============================================================================
//                                 BFS  Function`s
//===============================================================================

//-------------------------------------------------------------------------------
// Function to exacute the BFS traversal
//-------------------------------------------------------------------------------
int GameObject::BFS() 
{

	bool visited[LINE_SIZE][LINE_SIZE] = { {false} };
	std::array<std::array<std::pair<Position, int>, LINE_SIZE>, LINE_SIZE>  bfsDiscoveryNighbers;

	// Stores indices of the matrix cells
	std::queue<Position > bfsQueue;

	// Mark the starting cell as visited
	// and push it into the queue
	auto source = m_orignalBoard->getObjectPosition();
	bfsQueue.push({ source.first, source.second });
	visited[source.first][source.second] = true;

	// Iterate while the queue
	// is not empty
	while (!bfsQueue.empty()) {

		Position cell = bfsQueue.front();

		if (cell.first == 0 || cell.first == 10 || cell.second == 0 || cell.second == 10) {
			return reverseTrackBFS(bfsDiscoveryNighbers, cell); 
		}

		bfsQueue.pop();

		Position adjacent;
		// Go to the adjacent cells
		for (int neighbor = 0; neighbor < 6; ++neighbor) {


			adjacent.first = cell.first   + MEET_NEIGHBORS[rowOffset(cell.first)][neighbor].first;
			adjacent.second = cell.second + MEET_NEIGHBORS[rowOffset(cell.first)][neighbor].second;

			if (m_orignalBoard->isValid(adjacent) && !visited[adjacent.first][adjacent.second])
			{
				bfsQueue.push(adjacent);
				visited[adjacent.first][adjacent.second] = true;
				bfsDiscoveryNighbers[adjacent.first][adjacent.second].first = cell;
				bfsDiscoveryNighbers[adjacent.first][adjacent.second].second = neighbor;
			}
		}
	}
	
	m_objectStuck = true;

	return randomMovment();
}


//-------------------------------------------------------------------------------
// Function to reverse the BFS shortest track to locate the next circle that
// the game object (cat) will go to .  
//-------------------------------------------------------------------------------
int  GameObject::reverseTrackBFS(const std::array<std::array<std::pair<Position, int>, LINE_SIZE>, LINE_SIZE>& bfsNighbers, Position lastBfsPosition) 
{
	Position nextPosition;
	auto currPosition = m_orignalBoard->getObjectPosition();
	while (lastBfsPosition != currPosition)
	{
		nextPosition = lastBfsPosition;
		lastBfsPosition = bfsNighbers[lastBfsPosition.first][lastBfsPosition.second].first;
	}
	
	setObjectNextPosition(nextPosition);
	 
	return bfsNighbers[nextPosition.first][nextPosition.second].second;

}
//-------------------------------------------------------------------------------
// Function to move the game object (cat) randomlly after getting trapeded 
//-------------------------------------------------------------------------------
int GameObject::randomMovment()  
{
	Position adjacent;
	for (int neighbor = 0, dir = rand() % 6; neighbor < 6; ++neighbor, ++dir) {
		
		auto currPosition = m_orignalBoard->getObjectPosition();

		adjacent.first = currPosition.first   + MEET_NEIGHBORS[rowOffset(currPosition.first)][dir % 6].first;
		adjacent.second = currPosition.second + MEET_NEIGHBORS[rowOffset(currPosition.first)][dir % 6].second;

		if (m_orignalBoard->isValid(adjacent)) {
			setObjectNextPosition(adjacent);
			return  dir % 6;
		}
	}

	m_playerWin = true;
	return 0;

}
