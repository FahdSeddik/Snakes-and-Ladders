#pragma once

#include "Action.h"

class CopyCardAction : public Action
{
private:
	CellPosition CardPos;
	Card* Pcard;
	bool check;
public:
	CopyCardAction(ApplicationManager *pApp); // A Constructor
	virtual void ReadActionParameters(); // Reads CopyCardAction action parameters (CardPos)
	
	virtual void Execute();
	

	virtual ~CopyCardAction(); // Virtual Destructor
};