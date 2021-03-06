#pragma once
#include "Action.h"
#include "ApplicationManager.h"
class ToDesignModeAction :
    public Action
{

public:
	ToDesignModeAction(ApplicationManager* pApp);  // Constructor

	// ============ Virtual Functions ============

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 
											 // (code depends on action type so virtual)

	virtual void Execute();  // Executes action (code depends on action type so virtual)

	virtual ~ToDesignModeAction();  // Virtual Destructor
};

