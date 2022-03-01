#include "Snake.h"
#include <fstream>
Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos):GameObject(startCellPos) {
	this->endCellPos = endCellPos;

	//do the needed validation
}
// A constructor for initialization

void Snake::Draw(Output* pOut) const {
	pOut->DrawSnake(position, endCellPos);
} // Draws a snake from its start cell to its end cell

void Snake::Apply(Grid* pGrid, Player* pPlayer) {
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 1- Print a message "You have reached a snake. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");
	
	// 2- Apply the snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

	pOut->ClearStatusBar();
}
// Applys the effect of the snake by moving player to snake's end cell

CellPosition Snake::GetEndPosition() const {
	return endCellPos;
}
void Snake::Save(ofstream& OutFile,  const CellPosition& startCellPos)
{
	OutFile << startCellPos.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
	
}

void Snake::Load(ifstream& Infile)
{
}

// A getter for the endCellPos data member

Snake::~Snake() {

}




bool Snake::IsOverlapping(GameObject* newObj) const {
	if (dynamic_cast<Snake*>(newObj)) {

		Snake* obj = dynamic_cast<Snake*>(newObj);
		for (int i = position.VCell(); i <= endCellPos.VCell(); i++) {
			if (i <= obj->GetEndPosition().VCell() && i >= obj->GetPosition().VCell())
				return true;
		}
	}
	return false;
}