#pragma once
#include "Card.h"
class CardNine:
    public Card
{
private:
    static int price; //same price for all card (9) (static)
    static int fees;  //same fees for all card (9) (static)
	static int numberofCards; //to know if its first time drawing card in design mode (static)
	static Player* Owner; //Owner of 1 card(9) owns all card (9) (static)
	static bool firstSave;
public:
	CardNine(const CellPosition& pos); // A Constructor takes card position
	void SetFees(int);
	void SetPrice(int);
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount
	//for copy,cut,paste
	virtual Card* GetCopy();
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member
	virtual void Save(ofstream& OutFile, const CellPosition& startCellPos);
	virtual void Load(ifstream& Infile);
	int getPrice()const;
	bool CheckOwner(Player*)const;
	void SetOwner(Player*);
	virtual ~CardNine(); // A Virtual Destructor
};

