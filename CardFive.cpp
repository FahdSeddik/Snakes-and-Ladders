#include "CardFive.h"

CardFive::CardFive(const CellPosition& pos):Card(pos)
{
	cardNumber = 5;
}

void CardFive::ReadCardParameters(Grid* pGrid)
{
	
}

void CardFive::SetNumberOfDecrementSteps(int x)
{
	NumberOfDecrementSteps = x;
}
CardFive::CardFive(const CellPosition& pos,int num) :Card(pos) {
	cardNumber = 5;
	NumberOfDecrementSteps = num;
}
Card* CardFive::GetCopy() {
	return new CardFive(position,NumberOfDecrementSteps);
}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
	//get just rolled number(need implemntation) in player.h
	// clear position
	//update player cell postion
	//draw player in new cell position
	Card::Apply(pGrid,pPlayer);
	CellPosition n(pPlayer->GetCell()->GetCellPosition().GetCellNum() - pPlayer->GetJustRolled());
	pGrid->UpdatePlayerCell(pPlayer, n);

	if (pPlayer->GetCell()->GetGameObject())
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
	}
}
void CardFive::Save(ofstream& OutFile, const CellPosition& startCellPos)
{
	Card::Save(OutFile, startCellPos);
	OutFile << endl;
}
void CardFive::Load(ifstream& Infile)
{
	Infile >> NumberOfDecrementSteps;
}
CardFive::~CardFive()
{

}