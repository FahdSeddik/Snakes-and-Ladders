#include "DeleteGameObjectAction.h"
#include "Action.h"
#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
}

void DeleteGameObjectAction::ReadActionParameters()
{
	pManager->GetGrid()->GetOutput()->PrintMessage("Please select object to delete ");
	ObjectToDeletePos = pManager->GetGrid()->GetInput()->GetCellClicked();
}

void DeleteGameObjectAction::Execute()
{
	ReadActionParameters();
	Cell* deleteCell;

	deleteCell = pManager->GetGrid()->GetCellWithPos(ObjectToDeletePos);
	if (pManager->GetGrid()->GetCellWithPos(ObjectToDeletePos)->GetGameObject()==NULL)
	{
		pManager->GetGrid()->GetOutput()->PrintMessage("Error Cell doesn't have object");
		return;
	}
	if (deleteCell->HasLadder())
	{
		pManager->GetGrid()->GetCellWithPos(deleteCell->HasLadder()->GetEndPosition())->setisEndCell(false);
	}
	else if (deleteCell->HasSnake())
	{
		pManager->GetGrid()->GetCellWithPos(deleteCell->HasSnake()->GetEndPosition())->setisEndCell(false);
	}
	delete pManager->GetGrid()->GetCellWithPos(ObjectToDeletePos)->GetGameObject();
	pManager->GetGrid()->RemoveObjectFromCell(ObjectToDeletePos);
	pManager->GetGrid()->GetOutput()->ClearStatusBar();
}

DeleteGameObjectAction::~DeleteGameObjectAction()
{
}
