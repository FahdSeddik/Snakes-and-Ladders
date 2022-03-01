#pragma once
#include "GameObject.h"
#include <fstream>
class Snake :	public GameObject
{
private:
	CellPosition endCellPos; //startcell in gameobject
public:
	Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to ladder's end cell
	virtual bool IsOverlapping(GameObject* newObj)const;
	CellPosition GetEndPosition() const; // A getter for the endCellPos data member
	virtual void Save(ofstream& OutFile,  const CellPosition& startCellPos);
	virtual void Load(ifstream& Infile);
	virtual ~Snake(); // Virtual destructor
};

