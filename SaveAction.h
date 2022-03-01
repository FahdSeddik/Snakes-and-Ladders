#pragma once
#include "Action.h"
#include <fstream>
class SaveAction :
    public Action
{
	ofstream OutFile;
    string filename;
public:
	SaveAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); // Creates a new Card Object of the specific Card Number
							// and Reads the Parameters of This Card Number (if any)
							// then Sets this Card Object to GameObject Pointer of its Cell

	virtual ~SaveAction(); // A Virtual Destructor
};

