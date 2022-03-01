#include "NewGameAction.h"
#include "Grid.h"
#include "Player.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
}

void NewGameAction::ReadActionParameters()
{
}

void NewGameAction::Execute()
{
	CellPosition origin(1);
	pManager->GetGrid()->setCurrentPlayer();
	Grid* pGrid = pManager->GetGrid();
	CardNine* pCard9 = new CardNine(origin);
	CardTen* pCard10 = new CardTen(origin);
	CardEleven* pCard11 = new CardEleven(origin);
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		pGrid->RestartGame();
		pCard9->SetOwner(NULL);
		pCard10->SetOwner(NULL);
		pCard11->SetOwner(NULL);
	}
	delete pCard9;
	pCard9 = NULL;
	delete pCard10;
	pCard10 = NULL;
	delete pCard11;
	pCard11 = NULL;

	pGrid->SetEndGame(false);
}

NewGameAction::~NewGameAction()
{
}
