#pragma once
#include "Card.h"
class CardTen :
	public Card
{
private:
	static int price; //same price for all card (10) (static)
	static int fees;  //same fees for all card (10) (static)
	static int numberofCards; //to know if its first time drawing card in design mode (static)
	static Player* Owner; //Owner of 1 card(10) owns all card (10) (static)
	static bool firstSave;
public:
	CardTen(const CellPosition& pos); // A Constructor takes card position
	void SetFees(int);
	void SetPrice(int);
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount
	//for copy,cut,paste

	virtual Card* GetCopy();
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	virtual void Save(ofstream& OutFile, const CellPosition& startCellPos);
													  // by decrementing the player's wallet by the walletAmount data member
	virtual void Load(ifstream& Infile);
	int getPrice()const;
	bool CheckOwner(Player*)const;
	void SetOwner(Player*);
	virtual ~CardTen(); // A Virtual Destructor
};

