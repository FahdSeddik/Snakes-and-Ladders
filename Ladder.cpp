#include "Ladder.h"
#include <fstream>
//needed implementation for is overlap
Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
	
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}
bool Ladder::IsOverlapping(GameObject* newObj) const {
	if (dynamic_cast<Ladder*>(newObj)) {
		Ladder* obj = dynamic_cast<Ladder*>(newObj);
		for (int i = position.VCell(); i >= endCellPos.VCell(); i--) {
			if (i >= obj->GetEndPosition().VCell() && i <= obj->GetPosition().VCell()) {
				return true;
			}
		}
	}
	return false;
}
void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");
	
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

	pOut->ClearStatusBar();
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

void Ladder::Save(ofstream& OutFile,  const CellPosition& startCellPos)
{
	OutFile << startCellPos.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}

void Ladder::Load(ifstream& Infile)
{
}

Ladder::~Ladder()
{
	
}
