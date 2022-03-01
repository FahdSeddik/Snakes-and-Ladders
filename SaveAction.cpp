#include "SaveAction.h"
#include "Grid.h"
#include <fstream>

SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SaveAction::ReadActionParameters()
{
	pManager->GetGrid()->GetOutput()->PrintMessage("Please enter filename ");
	filename = pManager->GetGrid()->GetInput()->GetSrting(pManager->GetGrid()->GetOutput()) + ".txt";
	pManager->GetGrid()->GetOutput()->ClearStatusBar();
}

void SaveAction::Execute()
{
	ReadActionParameters();
	pManager->GetGrid()->SaveAll(OutFile, filename); // saveAll func
}

SaveAction::~SaveAction()
{
}
