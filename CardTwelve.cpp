#include "CardTwelve.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include <fstream>
CardTwelve::CardTwelve(const CellPosition& pos) :Card(pos){
	cardNumber = 12;
	pCard9 = NULL;
	pCard10 = NULL;
	pCard11 = NULL;

}

Card* CardTwelve::GetCopy() {
	return new CardTwelve(position);
}
void CardTwelve::ReadCardParameters(Grid* pGrid) {
	//no card parameters
}

void CardTwelve::Save(ofstream& OutFile,  const CellPosition& startCellPos)
{
	Card::Save(OutFile,  startCellPos);
	OutFile << endl;
}

void CardTwelve::Load(ifstream& Infile)
{
}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer) {

	//base class apply
	Card::Apply(pGrid, pPlayer);
	CellPosition fake;

	//check if cards 9 to 11 exist
	if (pGrid->GetCardNineCount() > 0)
		pCard9 = new CardNine(fake);
	if (pGrid->GetCardTenCount() > 0)
		pCard10 = new CardTen(fake);
	if (pGrid->GetCardElevenCount() > 0)
		pCard11 = new CardEleven(fake);




	Player* plow = pGrid->GetLowestWallet();
	int maxprice = 0;
	int cardnum = 0;
	//get the highest price station owned by player on card
	if(pCard9)
		if (pCard9->CheckOwner(pPlayer)) {
			maxprice = pCard9->getPrice();
			cardnum = 9;
		}
	if(pCard10)
		if (pCard10->CheckOwner(pPlayer) && pCard10->getPrice()>maxprice) {
			maxprice = pCard10->getPrice();
			cardnum = 10;
		}
	if(pCard11)
		if (pCard11->CheckOwner(pPlayer)&& pCard11->getPrice() >maxprice) {
			maxprice = pCard11->getPrice();
			cardnum = 11;
		}
	
	//set owner of station with lowest wallet player
	if (cardnum == 9) 
		pCard9->SetOwner(plow);
	else if (cardnum == 10) 
		pCard10->SetOwner(plow);
	else if (cardnum == 11)
		pCard11->SetOwner(plow);


	if (pCard9) {
		delete pCard9;
		pCard9 = NULL;
	}
	if (pCard10) {
		delete pCard10;
		pCard10 = NULL;
	}
	if (pCard11) {
		delete pCard11;
		pCard11 = NULL;
	}
}

CardTwelve::~CardTwelve() {

}