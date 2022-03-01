#pragma once

#include "Action.h"

class PasteCardAction : public Action
{
private:
	Card* Copiedcard;
	CellPosition c;
	bool check;
public:
	PasteCardAction(ApplicationManager *pApp); // A Constructor
	virtual void ReadActionParameters(); // Reads CopyCardAction action parameters (CardPastePosition)
	
	virtual void Execute(); //pastes the copied card in the desired position
	

	virtual ~PasteCardAction(); // Virtual Destructor
};