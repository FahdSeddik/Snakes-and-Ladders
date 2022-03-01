#pragma once
#include "Card.h"
class CardEight :
    public Card
{
	int CoinsToExit;

public:
	CardEight(const CellPosition& pos);

	//for copy,cut,paste
	CardEight(const CellPosition& pos,int bail);
	virtual Card* GetCopy();

	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual void Save(ofstream& OutFile,  const CellPosition& startCellPos);
	virtual void Load(ifstream& Infile);
	virtual ~CardEight();
};

