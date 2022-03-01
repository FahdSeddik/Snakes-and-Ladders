#include "CardEleven.h"
int CardEleven::numberofCards = 0;
int CardEleven::price = -1;
int CardEleven::fees = -1;
Player* CardEleven::Owner = NULL;
bool CardEleven::firstSave = true;
CardEleven::CardEleven(const CellPosition& pos) :Card(pos) {
	cardNumber = 11;
	numberofCards++;
}

// A Constructor takes card position

void CardEleven::ReadCardParameters(Grid* pGrid) {
	//check if its the first time defining
	if (numberofCards > 1)
		return;
	//read price
	//read fees
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Enter card(11) price: ");
	int p = pIn->GetInteger(pOut);
	pOut->PrintMessage("Enter card(11) fees: ");
	int f = pIn->GetInteger(pOut);

	//validations for price and fees (no negative price or fees)
	while (p < 0) {
		pGrid->PrintErrorMessage("ERROR: entered price(int) is negative or invalid. Click to continue");
		pOut->PrintMessage("Enter card(11) price: ");
		p = pIn->GetInteger(pOut);
	}
	price = p;

	while (f < 0) {
		pGrid->PrintErrorMessage("ERROR: entered fees(int) is negative or invalid. Click to continue");
		pOut->PrintMessage("Enter card(11) fees: ");
		f = pIn->GetInteger(pOut);
	}
	fees = f;


	pOut->ClearStatusBar();
}

void CardEleven::Apply(Grid* pGrid, Player* pPlayer) {
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
		pOut->PrintMessage("Buy Stations(11) (price= " + to_string(price) + " fees= " + to_string(fees) + " ) ?(1 to buy)");
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
		int c = pPlayer->TransferCoins(Owner, fees);
		if (c == -1)
			pGrid->PrintErrorMessage("Transferred fees to station owner. Click to continue...");
		else
			pGrid->PrintErrorMessage("Player did not have enough money. Tranferred player's wallet. Click to continue...");
	}


	pGrid->GetOutput()->ClearStatusBar();
}

void CardEleven::Save(ofstream& OutFile, const CellPosition& startCellPos)
{
	Card::Save(OutFile, startCellPos);
	if (firstSave) {
		OutFile << " " << price << " " << fees << endl;
		firstSave = false;
	}
	else
		OutFile << endl;
}

void CardEleven::Load(ifstream& Infile)
{
	if(price==-1)
		Infile >> price >> fees;
}

CardEleven::~CardEleven() {
	numberofCards--;
	if (numberofCards == 0) {
		price = -1;
		fees = -1;
		Owner = NULL;
		firstSave = true;
	}
}
int CardEleven::getPrice()const {
	return price;
}
bool CardEleven::CheckOwner(Player* p)const {
	if (Owner == p)
		return true;
	else
		false;

}


void CardEleven::SetOwner(Player* p) {
	Owner = p;
}

Card* CardEleven::GetCopy() {
	return new CardEleven(position);
}
