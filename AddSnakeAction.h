#pragma once
#include "Action.h"
class AddSnakeAction : public Action
{
	CellPosition startPos; // 1- The start position of the Snake
	CellPosition endPos;   // 2- The end position of the Snake
	bool check;

public:

	AddSnakeAction(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddSnakeAction action parameters (startPos, endPos)
	
	virtual void Execute(); // Creates a new Snake Object 
	                        // then Sets this Snake object to the GameObject Pointer of its Cell
	

	virtual ~AddSnakeAction(); // Virtual Destructor

};

