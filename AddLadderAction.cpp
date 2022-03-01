#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"
AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	check = true;// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	CellPosition startp = pIn->GetCellClicked();
	
	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
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
	if (startp.VCell() <= endp.VCell()) {
		pGrid->PrintErrorMessage("Error: startcell should be below endcell. Click to continue...");
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
	if (startp.VCell() == NumVerticalCells-1) {
		pGrid->PrintErrorMessage("Error: startcell cannot be bottom row. Click to continue...");
		check = false;
		return;
	}
	//set data members with read positions if passed those validations
	startPos = startp;
	endPos = endp;
	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute() 
{
	
	ReadActionParameters();
	if (check) {
		// Create a Ladder object with the parameters read from the user
		Ladder* pLadder = new Ladder(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		bool isoverlap = pGrid->IsOverlapping(pLadder);
		if (isoverlap) {
			pGrid->PrintErrorMessage("Ladder cannot overlap another ladder. Click to continue...");
			delete pLadder;
			return;
		}
		bool added = pGrid->AddObjectToCell(pLadder);
		// if the Ladder cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue...");
			delete pLadder;
		}
		pGrid->GetCellWithPos(endPos)->setisEndCell(true);
		pGrid->GetOutput()->ClearStatusBar();
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
