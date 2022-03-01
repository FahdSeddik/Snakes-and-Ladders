#pragma once
#include "Card.h"
class CardSix :
    public Card
{
	CellPosition MoveToCell;

public:
	CardSix(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid); 
	void SetMoveToCell(CellPosition& cell);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	//for copy,cut,paste
	CardSix(const CellPosition& pos,CellPosition moveto);
	virtual Card* GetCopy();
	virtual void Save(ofstream& OutFile,  const CellPosition& startCellPos);
	virtual void Load(ifstream& Infile);
	virtual ~CardSix();
};

