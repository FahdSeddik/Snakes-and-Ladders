#include "LoadGridAction.h"
#include "Grid.h"
#include <fstream>

LoadGridAction::LoadGridAction(ApplicationManager* pApp) : Action(pApp)
{
}

void LoadGridAction::ReadActionParameters()
{
	pManager->GetGrid()->GetOutput()->PrintMessage("Please enter filename ");
	filename = pManager->GetGrid()->GetInput()->GetSrting(pManager->GetGrid()->GetOutput()) + ".txt";
	pManager->GetGrid()->GetOutput()->ClearStatusBar();
}

void LoadGridAction::Execute()
{
	ReadActionParameters();
	pManager->GetGrid()->ClearGrid();
	pManager->GetGrid()->LoadGrid(InFile,filename); // Loadgrid func
}

LoadGridAction::~LoadGridAction()
{
}



