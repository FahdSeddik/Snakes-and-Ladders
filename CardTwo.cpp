#include "CardTwo.h"
#include "Ladder.h"
CardTwo::CardTwo(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number
}

CardTwo::~CardTwo(void)
{
}

void CardTwo::ReadCardParameters(Grid * pGrid)
{
	//No Card parameters
}
Card* CardTwo::GetCopy() {
	return new CardTwo(position);
}
void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	Ladder* NextLadder=pGrid->GetNextLadder(position);//setting the pointer to point on the Nextladder if any
	if(NextLadder==NULL)
	{
		return;
	}
	else
	{
		pPlayer->Move(pGrid,(NextLadder->GetPosition().GetCellNum()-position.GetCellNum()));//Move the current player to the nextt ladder
	}
	
}

void CardTwo::Save(ofstream& OutFile,  const CellPosition& startCellPos)
{
		Card::Save(OutFile,  startCellPos);
		OutFile << endl;
		
}

void CardTwo::Load(ifstream& Infile)
{
}
