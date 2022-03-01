#pragma once
#include "Action.h"
class DeleteGameObjectAction :
    public Action
{
	CellPosition ObjectToDeletePos;
public:
	DeleteGameObjectAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters();

	virtual void Execute();


	virtual ~DeleteGameObjectAction(); // Virtual Destructor
};

