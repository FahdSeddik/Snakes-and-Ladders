#pragma once

#include "Action.h"

class CutCardAction : public Action
{
private:
	CellPosition CardPos;
	Card* Pcard;
	bool check;
public:
	CutCardAction(ApplicationManager *pApp); // A Constructor
	virtual void ReadActionParameters(); // Reads CopyCardAction action parameters (CardPos)
	
	virtual void Execute(); 
	

	virtual ~CutCardAction(); // Virtual Destructor
};