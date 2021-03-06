#pragma once
#include "Action.h"
#include "ApplicationManager.h"
class ToPlayModeAction :
    public Action
{

public:
	ToPlayModeAction(ApplicationManager* pApp);  // Constructor

	// ============ Virtual Functions ============

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 
											 // (code depends on action type so virtual)

	virtual void Execute();  // Executes action (code depends on action type so virtual)

	virtual ~ToPlayModeAction();  // Virtual Destructor
};

