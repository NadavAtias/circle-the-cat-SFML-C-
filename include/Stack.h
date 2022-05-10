#pragma once
//------------------------ Include Section --------------------------

#include "ResourceManagment.h"
#include <algorithm>
#include <stack>

//------------------------ Const Section ----------------------------

template<class T>
class Stack
{
public:
	//Constructors & Destructors
	//---------------------------------------------------------------
	Stack() {};
	~Stack() {};
	
	//---------------------------------------------------------------	
	//				      Utilities functions
	//---------------------------------------------------------------
	void push       (const T&);
	void clearStack ();
	const T& pop    ();
	bool isEmpty() { return m_stack.empty(); }

private:
	//				 Private members
	//---------------------------------------------------------------
	std::stack<T> m_stack; 
};


//---------------------------------------------------------------
// Function to push object to stack
//---------------------------------------------------------------
template<class T>
void Stack<T>::push(const T& prevPosition)
{
	m_stack.push(prevPosition);
} 
//---------------------------------------------------------------
// Function to pop object to stack, and return the value.
//---------------------------------------------------------------
template<class T>
const T& Stack<T>::pop()
{
	
		if (m_stack.empty()) throw std::out_of_range("");
		
		auto prevPosition = m_stack.top();
		m_stack.pop();
		return prevPosition;

}
//---------------------------------------------------------------
// Function to empty a stack
//---------------------------------------------------------------
template<class T>
void Stack<T>::clearStack()
{
	while (!m_stack.empty())
		m_stack.pop();
}

