#include "InputDiceValueAction.h"
#include "Action.h"
#include "Player.h"

InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) : Action(pApp)
{
	diceNumber = 0;
}

void InputDiceValueAction::ReadActionParameters()
{
	pManager->GetGrid()->GetOutput()->PrintMessage("please enter a dice value between 1-6");
	diceNumber=pManager->GetGrid()->GetInput()->GetInteger(pManager->GetGrid()->GetOutput());
	while (diceNumber > 6 && diceNumber < 0)
	{
		pManager->GetGrid()->GetOutput()->PrintMessage("Error: Invalid Dice Value Please Try Again ");
		diceNumber = pManager->GetGrid()->GetInput()->GetInteger(pManager->GetGrid()->GetOutput());

	}

	pManager->GetGrid()->GetOutput()->ClearStatusBar();
}

void InputDiceValueAction::Execute()
{
	ReadActionParameters();
	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	if (pManager->GetGrid()->GetEndGame())
		return;

	// -- If not ended, do the following --:
	// 
	// 2- Get the "current" player from pGrid
	Player* pPlayer;
	pPlayer = pManager->GetGrid()->GetCurrentPlayer();

	// 3- Move the currentPlayer using function Move of class player
	pPlayer->Move(pManager->GetGrid(), diceNumber);
	// 4- Advance the current player number of pGrid
	pManager->GetGrid()->AdvanceCurrentPlayer();

}

InputDiceValueAction::~InputDiceValueAction()
{
}
