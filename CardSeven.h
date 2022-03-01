#pragma once
#include "Card.h"
class CardSeven :
    public Card
{
public:
	CardSeven(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);
	//for copy,cut,paste
	virtual Card* GetCopy();

	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual void Save(ofstream& OutFile,  const CellPosition& startCellPos);
	virtual void Load(ifstream& Infile);
	virtual ~CardSeven();

};

