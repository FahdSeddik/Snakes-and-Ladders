#include "CardThree.h"
#include <fstream>

CardThree::CardThree(const CellPosition& pos) : Card(pos)
{
	cardNumber = 3;
}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	pGrid->DecrementCurrentPlayer();
}
Card* CardThree::GetCopy() {
	return new CardThree(position);
}
void CardThree::Save(ofstream& OutFile, const CellPosition& startCellPos)
{
	Card::Save(OutFile, startCellPos);
	OutFile << endl;
}

void CardThree::Load(ifstream& Infile)
{
}

CardThree::~CardThree()
{
}
