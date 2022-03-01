#pragma once
#include "Action.h"
#include "ApplicationManager.h"
#include "Grid.h"
class InputDiceValueAction :
    public Action
{
    int diceNumber;

public:
    InputDiceValueAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual ~InputDiceValueAction();
};

