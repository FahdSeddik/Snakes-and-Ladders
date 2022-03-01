#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "Action.h"
#include "Snake.h"
#include <fstream>
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}
void Grid::RestartGame() {
	for (int i = 0; i < MaxPlayerCount; i++) {
		PlayerList[i]->Restart(this);
	}
}
void Grid::DecrementCurrentPlayer()
{
	if (currPlayerNumber == 0)
	{
		currPlayerNumber = MaxPlayerCount - 1;
		return;
	}
	currPlayerNumber = currPlayerNumber - 1;
}
void Grid::LightningOtherPlayers(Player* callingp) {
	for (int i = 0; i < MaxPlayerCount; i++) {
		if (PlayerList[i] != callingp) {
			PlayerList[i]->DecrementWallet(20);
		}
	}
}
void Grid::DoSpecial(Player* p) {
	
}
// ========= Adding or Removing GameObjects to Cells =========
void Grid::SkipTurnofPlayer(int pnum) {
	PlayerList[pnum]->SetSkipTurn(true);
}
Player* Grid::GetPlayerwithNumber(int c)const {
	return PlayerList[c];
}
bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}


// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}
void Grid::ClearGrid() {
	for (int i = 0; i < NumVerticalCells; i++) {
		for (int j = 0; j < NumHorizontalCells; j++) {
			delete CellList[i][j]->GetGameObject();
			RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
		}
	}
}
void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder* Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder())
				return dynamic_cast<Ladder*>(CellList[i][j]->GetGameObject());

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Player* Grid::GetLowestWallet()const {
	int minwallet = PlayerList[0]->GetWallet();
	Player* result = PlayerList[0];
	for (int i = 1; i < MaxPlayerCount; i++) {
		if (PlayerList[i]->GetWallet() < minwallet) {
			minwallet = PlayerList[i]->GetWallet();
			result = PlayerList[i];
		}
	}
	return result;
}

Player* Grid::GetNextPlayer(const CellPosition& position)
{
	Player* arr[MaxPlayerCount];
	int k = 0;
	for (int i = 0; i < MaxPlayerCount; i++)
	{

		if (PlayerList[i]->GetCell()->GetCellPosition().GetCellNum() > position.GetCellNum())
		{
			arr[k] = PlayerList[i];
			k++;
		}

	}
	if (k == 0)
	{
		return NULL;
	}
	Player* min = arr[0];
	for (int i = 1; i < k; i++)
	{
		if (min->GetCell()->GetCellPosition().GetCellNum() > arr[i]->GetCell()->GetCellPosition().GetCellNum())
			min = arr[i];
	}
	return min;
}

void Grid::setCurrentPlayer(int i)
{
	currPlayerNumber = i;
}

// ========= User Interface Functions =========

Cell* Grid::GetCellWithPos(CellPosition pos) {
	return CellList[pos.VCell()][pos.HCell()];

}
void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{

			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

bool Grid::IsOverlapping(GameObject* newObj)const {
	for (int i = 0; i < NumVerticalCells; i++) {
		if(CellList[i][newObj->GetPosition().HCell()]->GetGameObject())
			if (CellList[i][newObj->GetPosition().HCell()]->GetGameObject()->IsOverlapping(newObj))
				return true;
	}
	return false;
}
void Grid::SaveAll(ofstream& OutFile, string filename)
{
	int countLadder = 0;
	int countSnake = 0;
	int countCard = 0;
	OutFile.open(filename, ios::app);
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasLadder())
			{
				countLadder++;
			}
			else if (CellList[i][j]->HasSnake())
			{
				countSnake++;
			}
			else if (CellList[i][j]->HasCard())
			{
				countCard++;
			}
		}
	}
	OutFile << countLadder << endl;
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{

			if (CellList[i][j]->HasLadder())
			{
				CellList[i][j]->HasLadder()->Save(OutFile,  CellList[i][j]->GetCellPosition());
			}
		}
	}
	OutFile << countSnake << endl;
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{

			if (CellList[i][j]->HasSnake())
			{
				CellList[i][j]->HasSnake()->Save(OutFile,  CellList[i][j]->GetCellPosition());
			}
		}
	}
	OutFile << countCard << endl;
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{

			if (CellList[i][j]->HasCard())
			{
				CellList[i][j]->HasCard()->Save(OutFile,  CellList[i][j]->GetCellPosition());
			}
		}
	}
	OutFile.close();
}
void Grid::LoadGrid(ifstream& InFile, string filename)
{
	
	InFile.open(filename, ios::in);
	int countLadder;
	int countSnake;
	int countCard;
	InFile >> countLadder;

	for (int i = 0; i < countLadder; i++)
	{
		int startcell, endcell;
		InFile >> startcell >> endcell;
		CellPosition startpos(startcell);
		CellPosition endpos(endcell);
		Ladder* ptr = new Ladder(startpos, endpos);
		GetCellWithPos(startpos)->SetGameObject(ptr);
	}
	InFile >> countSnake;
	for (int i = 0; i < countSnake; i++)
	{
		int startCell, endCell;
		InFile >> startCell >> endCell;
		CellPosition startpos(startCell);
		CellPosition endpos(endCell);
		Snake* ptr = new Snake(startpos, endpos);
		GetCellWithPos(startpos)->SetGameObject(ptr);
	}
	InFile >> countCard;
	CardOne* ptr1= NULL;
	CardTwo* ptr2 = NULL;
	CardThree* ptr3 = NULL;
	CardFour* ptr4 = NULL;
	CardFive* ptr5 = NULL;
	CardSix* ptr6 = NULL;
	CardSeven* ptr7 = NULL;
	CardEight* ptr8 = NULL;
	CardNine* pCard9 = NULL;
	CardTen* pCard10 = NULL;
	CardEleven* pCard11 = NULL;
	CardTwelve* ptr12 = NULL;
	for (int i = 0; i < countCard; i++)
	{
		int cardType, startCell;
		InFile >> cardType >> startCell;
		CellPosition startpos(startCell);
		switch (cardType)
		{
		case 1:
			ptr1 = new CardOne(startpos);
			ptr1->Load(InFile);
			GetCellWithPos(startpos)->SetGameObject(ptr1);
			break;
		case 2:
			ptr2 = new CardTwo(startpos);
			GetCellWithPos(startpos)->SetGameObject(ptr2);
			break;
		case 3:
			ptr3 = new CardThree(startpos);
			GetCellWithPos(startpos)->SetGameObject(ptr3);
			break;
		case 4:
			ptr4 = new CardFour(startpos);
			GetCellWithPos(startpos)->SetGameObject(ptr4);
			break;
		case 5:
			ptr5 = new CardFive(startpos);
			GetCellWithPos(startpos)->SetGameObject(ptr5);
			break;
		case 6:
			ptr6 = new CardSix(startpos);
			ptr6->Load(InFile);
			GetCellWithPos(startpos)->SetGameObject(ptr6);
			break;
		case 7:
			ptr7 = new CardSeven(startpos);
			GetCellWithPos(startpos)->SetGameObject(ptr7);
			break;
		case 8:
			ptr8 = new CardEight(startpos);
			ptr8->Load(InFile);
			GetCellWithPos(startpos)->SetGameObject(ptr8);
			break;
		case 9:
			pCard9 = new CardNine(startpos);
			pCard9->Load(InFile);
			GetCellWithPos(startpos)->SetGameObject(pCard9);
			break;
		case 10:
			pCard10 = new CardTen(startpos);
			pCard10->Load(InFile);
			GetCellWithPos(startpos)->SetGameObject(pCard10);
			break;
		case 11:
			pCard11 = new CardEleven(startpos);
			pCard11->Load(InFile);
			GetCellWithPos(startpos)->SetGameObject(pCard11);
			break;
		
		case 12:
			ptr12 = new CardTwelve(startpos);
			GetCellWithPos(startpos)->SetGameObject(ptr12);
			break;
		}
	}
	InFile.close();
}
Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}


int Grid::GetCardNineCount()const {
	int count = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // left to right
		{
			if (dynamic_cast<Card*>(CellList[i][j]->GetGameObject()) && CellList[i][j]->GetGameObject()!=NULL) {

				Card* testCard = dynamic_cast<Card*>(CellList[i][j]->GetGameObject());

				if (testCard->GetCardNumber() == 9) 
					count++;
			}
		}
	}

	return count;
}
int Grid::GetCardTenCount()const {
	int count = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // left to right
		{
			if (dynamic_cast<Card*>(CellList[i][j]->GetGameObject()) && CellList[i][j]->GetGameObject() != NULL) {

				Card* testCard = dynamic_cast<Card*>(CellList[i][j]->GetGameObject());

				if (testCard->GetCardNumber() == 10)
					count++;
			}
		}
	}

	return count;
}
int Grid::GetCardElevenCount()const {
	int count = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // left to right
		{
			if (dynamic_cast<Card*>(CellList[i][j]->GetGameObject()) && CellList[i][j]->GetGameObject() != NULL) {

				Card* testCard = dynamic_cast<Card*>(CellList[i][j]->GetGameObject());

				if (testCard->GetCardNumber() == 11)
					count++;
			}
		}
	}

	return count;
}