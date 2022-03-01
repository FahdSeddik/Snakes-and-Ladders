#pragma once
#include "Card.h"
class CardEleven :
	public Card
{
private:
	static int price; //same price for all card (10) (static)
	static int fees;  //same fees for all card (10) (static)
	static int numberofCards; //to know if its first time drawing card in design mode (static)
	static Player* Owner; //Owner of 1 card(10) owns all card (10) (static)
	static bool firstSave;
public:
	CardEleven(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member
	virtual void Save(ofstream& OutFile, const CellPosition& startCellPos);
	virtual void Load(ifstream& Infile);
	//for copy,cut,paste
	virtual Card* GetCopy();
	int getPrice()const;
	bool CheckOwner(Player*)const;
	void SetOwner(Player*);
	virtual ~CardEleven(); // A Virtual Destructor
};

