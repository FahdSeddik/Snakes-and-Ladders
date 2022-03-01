#include "CardEight.h"

CardEight::CardEight(const CellPosition& pos): Card(pos)
{
	cardNumber = 8;
}

void CardEight::ReadCardParameters(Grid* pGrid)
{
	pGrid->GetOutput()->PrintMessage("New CardEight: Enter The Amount Of Coins Needed To Go Out Of Prison:");
	CoinsToExit=pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	pGrid->GetOutput()->ClearStatusBar();

}

//for copy,cut,paste
CardEight::CardEight(const CellPosition& pos, int bail):Card(pos) {
	cardNumber = 8;
	CoinsToExit = bail;
}
Card* CardEight::GetCopy() {
	return new CardEight(position, CoinsToExit);
}
void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	if (pPlayer->getPrison())
		return;

	Card::Apply(pGrid, pPlayer);

	pGrid->GetOutput()->PrintMessage("Enter 1 to pay and get out, 0 otherwise:");
	int s;
	s= pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	while (s != 1 && s!=0)
	{
		pGrid->PrintErrorMessage("ERROR: Invalid input (Enter 1 to pay 0 otherwise). Click to continue...");
		pGrid->GetOutput()->PrintMessage("Enter 1 to pay and get out, 0 otherwise:");
		s = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
		pGrid->GetOutput()->ClearStatusBar();
	}
	if (s == 1)
	{
		//add function in player.h
		
		if (pPlayer->GetWallet()<CoinsToExit)
		{
			pGrid->PrintErrorMessage("You don't have enough money. Click to continue...");
			pPlayer->setinPrison(true);
			pPlayer->setPrisonCount(3);
		}
		else {
			pPlayer->DecrementWallet(CoinsToExit);
			pGrid->PrintErrorMessage("Deducted " + to_string(CoinsToExit) + " coins. Click to continue...");
		}
	}
	else
	{
		pGrid->PrintErrorMessage("Player entered prison for 3 turns. Click to continue...");
		pPlayer->setPrisonCount(3);
		pPlayer->setinPrison(true);
	}

}

void CardEight::Save(ofstream& OutFile,  const CellPosition& startCellPos)
{
	Card::Save(OutFile,  startCellPos);
	OutFile << " " << CoinsToExit << endl;
}

void CardEight::Load(ifstream& Infile)
{
	Infile >> CoinsToExit;
}

CardEight::~CardEight()
{
}
