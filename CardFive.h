#pragma once
#include "Card.h"
class CardFive :
    public Card
{
    int NumberOfDecrementSteps;

public:
	CardFive(const CellPosition& pos); 
	//for copy,cut,paste
	CardFive(const CellPosition& pos,int num);
	virtual Card* GetCopy();
	virtual void ReadCardParameters(Grid* pGrid); 
	void SetNumberOfDecrementSteps(int);
	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	virtual void Save(ofstream& OutFile,  const CellPosition& startCellPos);
	virtual void Load(ifstream& Infile);
	virtual ~CardFive(); 
};

