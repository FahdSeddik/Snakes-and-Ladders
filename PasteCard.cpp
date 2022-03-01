 #include "PasteCard.h"

#include "Input.h"
#include "Output.h"
#include "Card.h"
PasteCardAction::PasteCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	Copiedcard = NULL;
	check = true;
}

PasteCardAction::~PasteCardAction()
{
	
}

void PasteCardAction::ReadActionParameters() 
{	
	Grid* pGrid = pManager->GetGrid();// We get a pointer to the Grid from the ApplicationManager
	Copiedcard = pGrid->GetClipboard()->GetCopy();//Make CopiedCard pointer points to CopiedCard
	if (Copiedcard)//checking if the pointer is not equal NULL which means Points to card so SetTheCard in the Grid
	{
		pGrid->GetOutput()->PrintMessage("Click on the destination cell.");
		c = pGrid->GetInput()->GetCellClicked();
		if (!c.IsValidCell()) {
			pGrid->GetOutput()->PrintMessage("Error: not a valid cell.");
			check = false;
			return;
		}
	}
	else {
		pGrid->PrintErrorMessage("Error: Clipboard is empty. Click to continue...");
		check = false;
		return;
	}
}


// Execute the action
void PasteCardAction::Execute() 
{

	ReadActionParameters();//Reading paramaters from the user
	if (check) {
		Grid* pGrid = pManager->GetGrid();// We get a pointer to the Grid from the ApplicationManager
		Copiedcard->setPosition(c);
		pGrid->GetCellWithPos(c)->SetGameObject(Copiedcard);
		pGrid->GetOutput()->ClearStatusBar();
	}
}
