#include "CopyCard.h"

#include "Input.h"
#include "Output.h"
#include "Card.h"
CopyCardAction::CopyCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	Pcard = NULL;
	check = true;
}

CopyCardAction::~CopyCardAction()
{
	
}

void CopyCardAction::ReadActionParameters() 
{	
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	pGrid->GetOutput()->PrintMessage("Click on source cell.");
	CardPos = pGrid->GetInput()->GetCellClicked();
	if (!CardPos.IsValidCell()) {
		pGrid->GetOutput()->PrintMessage("Error: not a valid cell. Click to continue...");
		check = false;
		return;
	}
	Pcard = dynamic_cast<Card*>(pGrid->GetCellWithPos(CardPos)->GetGameObject());

}


// Execute the action
void CopyCardAction::Execute() 
{
	ReadActionParameters();
	if (check) {
		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
		if (Pcard)
			pGrid->SetClipboard(Pcard);
		else
			return; //cancel operation if it doesnt contain a card
		pGrid->GetOutput()->ClearStatusBar();
	}
}
