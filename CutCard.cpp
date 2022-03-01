#include "CutCard.h"

#include "Input.h"
#include "Output.h"
#include "Card.h"
CutCardAction::CutCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	check = true;
	Pcard = NULL;
}

CutCardAction::~CutCardAction()
{
}

void CutCardAction::ReadActionParameters() 
{	
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	pGrid->GetOutput()->PrintMessage("Click on the source cell");
	CardPos = pGrid->GetInput()->GetCellClicked();
	if (!CardPos.IsValidCell()) {
		pGrid->GetOutput()->PrintMessage("Error: not a valid cell. Click to continue...");
		check = false;
		return;
	}
	Pcard = dynamic_cast<Card*>(pGrid->GetCellWithPos(CardPos)->GetGameObject());
}


// Execute the action
void CutCardAction::Execute() 
{
	ReadActionParameters();
	if (check) {
		Grid* pGrid = pManager->GetGrid();
		if (Pcard)
		{
			pGrid->SetClipboard(Pcard); //if it contained a card then set clipboard
			pGrid->RemoveObjectFromCell(CardPos);
		}
		else
		{
			//cell doesnt contain a card then cancel operation
			return;
		}
		pGrid->GetOutput()->ClearStatusBar();
	}
}
