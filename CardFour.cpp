#include "CardFour.h"
#include "RollDiceAction.h"

CardFour::CardFour(const CellPosition& pos) : Card(pos)
{
	cardNumber = 4;
}

Card* CardFour::GetCopy() {
	return new CardFour(position);
}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pPlayer->SetSkipTurn(true);
}

void CardFour::Save(ofstream& OutFile,  const CellPosition& startCellPos)
{
	Card::Save(OutFile,  startCellPos);
	OutFile << endl;

}

void CardFour::Load(ifstream& Infile)
{
}

CardFour::~CardFour()
{
}
