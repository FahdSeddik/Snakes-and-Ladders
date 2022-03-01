#pragma once
#include "Card.h"
class CardThree :
    public Card
{

public:
	CardThree(const CellPosition& pos); // A Constructor takes card position

	//for copy,cut,paste

	virtual Card* GetCopy();
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardThree on the passed Player
	virtual void Save(ofstream& OutFile,  const CellPosition& startCellPos);
	virtual void Load(ifstream& Infile);
	virtual ~CardThree(); // A Virtual Destructor
};

