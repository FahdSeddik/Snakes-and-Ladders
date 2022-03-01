#include "CardNine.h"
int CardNine::numberofCards = 0;
int CardNine::price = -1;
int CardNine::fees = -1;
Player* CardNine::Owner = NULL;
bool CardNine::firstSave = true;
CardNine::CardNine(const CellPosition& pos):Card(pos) {
	cardNumber = 9;
	numberofCards++;
}
void CardNine::SetFees(int x)
{
	fees = x;
}
void CardNine::SetPrice(int x)
{
	price = x;
}
// A Constructor takes card position
Card* CardNine::GetCopy() {
	return new CardNine(position);
}

void CardNine::ReadCardParameters(Grid* pGrid) {
	//check if its the first time defining
	if (numberofCards > 1)
		return;
	//read price
	//read fees
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Enter card(9) price: ");
	int p=pIn->GetInteger(pOut);
	pOut->PrintMessage("Enter card(9) fees: ");
	int f = pIn->GetInteger(pOut);

	//validations for price and fees (no negative price or fees)
	while (p < 0) {
		pGrid->PrintErrorMessage("ERROR: entered price(int) is negative or invalid. Click to continue");
		pOut->PrintMessage("Enter card(9) price: ");
		p= pIn->GetInteger(pOut);
	}
	price = p;

	while (f < 0) {
		pGrid->PrintErrorMessage("ERROR: entered fees(int) is negative or invalid. Click to continue");
		pOut->PrintMessage("Enter card(9) fees: ");
		f = pIn->GetInteger(pOut);
	}
	fees = f;

	pOut->ClearStatusBar();
}

void CardNine::Apply(Grid* pGrid, Player* pPlayer) {
	//call  apply of base class
	Card::Apply(pGrid, pPlayer);

	
	//if Owner nothing happens
	if (Owner == pPlayer)
		return;

	//input & output pointers
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//check if first player
	if (Owner == NULL) {
		pOut->PrintMessage("Buy Stations(9) (price= " + to_string(price) + " fees= " + to_string(fees) + " ) ?(1 to buy)");
		int ans = pIn->GetInteger(pOut);
		if (ans == 1) {
			if (pPlayer->GetWallet() >= price) {
				pPlayer->DecrementWallet(price);
				Owner = pPlayer;
			}
			else
				pGrid->PrintErrorMessage("Not enough Coins in wallet. Click anywhere to continue.");
		}

	}
	else {
		int c=pPlayer->TransferCoins(Owner, fees);
		if (c == -1)
			pGrid->PrintErrorMessage("Transferred fees to station owner. Click to continue...");
		else
			pGrid->PrintErrorMessage("Player did not have enough money. Tranferred player's wallet. Click to continue...");
	}
	pGrid->GetOutput()->ClearStatusBar();
}

void CardNine::Save(ofstream& OutFile, const CellPosition& startCellPos)
{
	Card::Save(OutFile, startCellPos);
	if (firstSave) {
		OutFile << " " << price << " " << fees << endl;
		firstSave = false;
	}
	else
		OutFile << endl;
}

void CardNine::Load(ifstream& Infile)
{
	if(price==-1)
		Infile >> price >> fees;
}

CardNine::~CardNine() {
	numberofCards--;
	if (numberofCards == 0) {
		price = -1;
		fees = -1;
		Owner = NULL;
		firstSave = true;
	}
}
int CardNine::getPrice()const {
	return price;
}
bool CardNine::CheckOwner(Player* p)const {
	if (Owner == p)
		return true;
	else
		false;

}

void CardNine::SetOwner(Player* p) {
	Owner = p;
}
