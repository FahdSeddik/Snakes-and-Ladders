#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"
AddSnakeAction::AddSnakeAction(ApplicationManager *pApp) : Action(pApp)
{
	check = true;// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	CellPosition startp = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	CellPosition endp = pIn->GetCellClicked();
	///TODO: Make the needed validations on the read parameters
	if (pGrid->GetCellWithPos(startp)->getisEndCell()) {
		pGrid->PrintErrorMessage("Error: Startcell is an endcell of another object");
		check = false;
		return;
	}
	if (startp.HCell() != endp.HCell()) {
		pGrid->PrintErrorMessage("Error: Hcell not matching. Click to continue...");
		check = false;
		return;
	}
	if (startp.VCell() >= endp.VCell()) {
		pGrid->PrintErrorMessage("Error: startcell should be above endcell. Click to continue...");
		check = false;
		return;
	}
	if (pGrid->GetCellWithPos(startp)->HasLadder()) {
		pGrid->PrintErrorMessage("Error: startcell contains a ladder. Click to continue...");
		check = false;
		return;
	}
	if (pGrid->GetCellWithPos(startp)->HasSnake()) {
		pGrid->PrintErrorMessage("Error: startcell contains a snake. Click to continue...");
		check = false;
		return;
	}
	if (pGrid->GetCellWithPos(startp)->HasCard()) {
		pGrid->PrintErrorMessage("Error: startcell contains a card. Click to continue...");
		check = false;
		return;
	}
	if (pGrid->GetCellWithPos(endp)->HasLadder()) {
		pGrid->PrintErrorMessage("Error: endcell contains a ladder. Click to continue...");
		check = false;
		return;
	}
	if (pGrid->GetCellWithPos(endp)->HasSnake()) {
		pGrid->PrintErrorMessage("Error: endcell contains a Snake. Click to continue...");
		check = false;
		return;
	}
	if (startp.VCell() == 0) {
		pGrid->PrintErrorMessage("Error: startcell cannot be top row. Click to continue...");
		check = false;
		return;
	}
	//set data members with read positions if passed those validations
	startPos = startp;
	endPos = endp;
	// Clear messages
	pOut->ClearStatusBar();
}


void AddSnakeAction::Execute() 
{
	ReadActionParameters();
	if (check) {
		// Create a Snake object with the parameters read from the user
		Snake* pSnake = new Snake(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the Snake object to the GameObject of its Cell:

		bool isoverlap = pGrid->IsOverlapping(pSnake);
		if (isoverlap) {
			pGrid->PrintErrorMessage("Snake cannot overlap another snake. Click to continue...");
			delete pSnake;
			return;
		}
		bool added = pGrid->AddObjectToCell(pSnake);
		// if the Snake cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue...");
			delete pSnake;
		}
		pGrid->GetCellWithPos(endPos)->setisEndCell(true);
		pGrid->GetOutput()->ClearStatusBar();
	}
	// Here, the Snake is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction
}
