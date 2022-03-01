#pragma once
#include "Card.h"
#include "Grid.h"
#include "Player.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"

class CardTwelve :
    public Card
{
private:
	CardNine* pCard9;
	CardTen* pCard10;
	CardEleven* pCard11;
public:
	CardTwelve(const CellPosition& pos);
	//for copy,cut,paste
	virtual Card* GetCopy();

	virtual void ReadCardParameters(Grid* pGrid); // It reads the parameters specific for each Card Type
												   // It is a virtual function (implementation depends on Card Type)
	virtual void Save(ofstream& OutFile,  const CellPosition& startCellPos);
	virtual void Load(ifstream& Infile);
	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual ~CardTwelve();
};

