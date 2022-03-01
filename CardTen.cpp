#include "CardTen.h"
int CardTen::numberofCards = 0;
int CardTen::price = -1;
int CardTen::fees = -1;
Player* CardTen::Owner = NULL;
bool CardTen::firstSave = true;
CardTen::CardTen(const CellPosition& pos) :Card(pos) {
	cardNumber = 10;
	numberofCards++;
}
void CardTen::SetFees(int x)
{
	fees = x;
}
void CardTen::SetPrice(int x)
{
	price = x;
}
// A Constructor takes card position

Card* CardTen::GetCopy() {
	return new CardTen(position);
}
void CardTen::ReadCardParameters(Grid* pGrid) {
	//check if its the first time defining
	if (numberofCards > 1)
		return;
	//read price
	//read fees
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Enter card(10) price: ");
	int p = pIn->GetInteger(pOut);
	pOut->PrintMessage("Enter card(10) fees: ");
	int f = pIn->GetInteger(pOut);

	//validations for price and fees (no negative price or fees)
	while (p < 0) {
		pGrid->PrintErrorMessage("ERROR: entered price(int) is negative or invalid. Click to continue");
		pOut->PrintMessage("Enter card(10) price: ");
		p = pIn->GetInteger(pOut);
	}
	price = p;

	while (f < 0) {
		pGrid->PrintErrorMessage("ERROR: entered fees(int) is negative or invalid. Click to continue");
		pOut->PrintMessage("Enter card(10) fees: ");
		f = pIn->GetInteger(pOut);
	}
	fees = f;


	pOut->ClearStatusBar();
}

void CardTen::Apply(Grid* pGrid, Player* pPlayer) {
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
		pOut->PrintMessage("Buy Stations(10) (price= " + to_string(price) + " fees= " + to_string(fees) + " ) ?(1 to buy)");
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

void CardTen::Save(ofstream& OutFile, const CellPosition& startCellPos)
{
	Card::Save(OutFile, startCellPos);
	if (firstSave) {
		OutFile << " " << price << " " << fees << endl;
		firstSave = false;
	}
	else
		OutFile << endl;
}

CardTen::~CardTen() {
	numberofCards--;
	if (numberofCards == 0) {
		price = -1;
		fees = -1;
		Owner = NULL;
		firstSave = true;
	}
}
void CardTen::Load(ifstream& Infile)
{
	if(price==-1)
		Infile >> price >> fees;
}
int CardTen::getPrice()const {
	return price;
}
bool CardTen::CheckOwner(Player* p)const {
	if (Owner == p)
		return true;
	else
		false;

}


void CardTen::SetOwner(Player* p) {
	Owner = p;
}
