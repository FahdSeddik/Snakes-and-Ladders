#pragma once
#include "Card.h"
class CardFour :
    public Card
{

	
public:
	CardFour(const CellPosition& pos); // A Constructor takes card position
	//for copy,cut,paste
	virtual Card* GetCopy();

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
													  // 

	virtual void Save(ofstream& OutFile,  const CellPosition& startCellPos);
	virtual void Load(ifstream& Infile);
	virtual ~CardFour(); // A Virtual Destructor
};

