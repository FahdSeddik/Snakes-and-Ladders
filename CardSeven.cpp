#include "CardSeven.h"

CardSeven::CardSeven(const CellPosition& pos) : Card(pos)
{
	cardNumber = 7;
}

void CardSeven::ReadCardParameters(Grid* pGrid)
{

}
Card* CardSeven::GetCopy() {
	return new CardSeven(position);
}
void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	//need a function to get the cell number of the player and search the cells after it till it find a player (in grid.h)
	Card::Apply(pGrid, pPlayer);

	CellPosition zero(1);
	if (pGrid->GetNextPlayer(pPlayer->GetCell()->GetCellPosition()))
	{
		pGrid->UpdatePlayerCell(pGrid->GetNextPlayer(pPlayer->GetCell()->GetCellPosition()), zero);
	}
}

void CardSeven::Save(ofstream& OutFile,  const CellPosition& startCellPos)
{
	Card::Save(OutFile,  startCellPos);
}

void CardSeven::Load(ifstream& Infile)
{
}

CardSeven::~CardSeven()
{
}


