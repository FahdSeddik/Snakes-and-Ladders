#include "CardSix.h"
#include <fstream>
CardSix::CardSix(const CellPosition& pos):Card(pos)
{
	cardNumber = 6;
}

void CardSix::ReadCardParameters(Grid* pGrid)
{
	pGrid->GetOutput()->PrintMessage("New CardSix: click A Specific Cell To Move To:");
	CellPosition d;
	d=pGrid->GetInput()->GetCellClicked();
	MoveToCell = d;
	pGrid->GetOutput()->ClearStatusBar();
	
}
CardSix::CardSix(const CellPosition& pos, CellPosition moveto):Card(pos) {
	cardNumber = 6;
	MoveToCell = moveto;
}
Card* CardSix::GetCopy() {
	return new CardSix(position, MoveToCell);
}
void CardSix::SetMoveToCell(CellPosition & cell)
{
	MoveToCell = cell;
}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	pGrid->UpdatePlayerCell(pPlayer, MoveToCell);

	if (pPlayer->GetCell()->GetGameObject())
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
	}
}

void CardSix::Save(ofstream& OutFile,  const CellPosition& startCellPos)
{
	Card::Save(OutFile,  startCellPos);
	OutFile << " " << MoveToCell.GetCellNum() << endl;
}

void CardSix::Load(ifstream& Infile)
{
	int cellnum;
	Infile >> cellnum;
	CellPosition pos(cellnum);
	MoveToCell = pos;
}

CardSix::~CardSix()
{
}
