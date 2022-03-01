#pragma once
#include "Action.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Player.h"
#include <string>
class SpecialAttack
{
protected:
	Grid* pGrid;
	bool check;
public:

	SpecialAttack(Grid* Gr);  // Constructor

	// ============ Virtual Functions ============

	virtual void ReadParameters(); // Reads parameters required for action to execute 
											 // (code depends on action type so virtual)

	virtual bool Execute();  // Executes action (code depends on action type so virtual)

	virtual ~SpecialAttack();  // Virtual Destructor
};

