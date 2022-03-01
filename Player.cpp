#include "Player.h"
#include "SpecialAttack.h"
#include "GameObject.h"
#include "DEFS.h"
Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	this->inPrison = false;
	this->wallet = 100;
	this->skipturn = false;
	SpecialUses = 2;
	SA = NA_SA;
	firecount = 0;
	poisoned = 0;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======
void Player::Restart(Grid* pGrid) {
	CellPosition origin(1);
	pGrid->UpdatePlayerCell(this, origin);
	this->turnCount = 0;
	this->inPrison = false;
	this->wallet = 100;
	this->skipturn = false;
	SpecialUses = 2;
	SA = NA_SA;
	firecount = 0;
	poisoned = 0;
}
int Player::getSpecialUses()const {
	return SpecialUses;
}
void Player::setSpecialUses(int s) {
	if (s < 0)
		s = 0;
	else
		SpecialUses = s;
}

void Player::setSpecialAttack(SpecialAttackType s) {
	SA = s;
}
SpecialAttackType Player::getSpecialAttack() {
	return SA;
}
void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}
void Player::SetPoisoned(int b) {
	poisoned = b;
}
void Player::SetTurnCount(int i)
{
	turnCount = i;
}
void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
	if (this->wallet < 0)
		this->wallet = 0;
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}
int Player::GetJustRolled()const
{
	return justRolledDiceNum;
}
void Player::SetSkipTurn(bool b) {
	skipturn = b;
}

bool Player::getPrison() const
{
	return inPrison;
}

void Player::setPrisonCount(int c)
{
	prisonCount = c;
}

void Player::setinPrison(bool i)
{
	inPrison = i;
}
// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	
	
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
}

// ====== Game Functions ======

void Player::DecrementWallet(int value)
{
	if (value >= wallet)
		wallet = 0;
	else
		wallet -= value;
}
int Player::TransferCoins(Player* to, int amount) {
	if (amount > wallet) {
		int ret = wallet;
		to->IncrementWallet(wallet);
		this->DecrementWallet(wallet);
		return ret;
	}
	else {
		to->IncrementWallet(amount);
		this->DecrementWallet(amount);
		return -1;
	}
}
void Player::IncrementWallet(int amount) {
	wallet += amount;
}
void Player::setFirecount(int c) {
	firecount = c;
}
void Player::Move(Grid * pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	turnCount++;

	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (poisoned > 0) {
		diceNumber--;
		poisoned--;
	}
	
	//fire apply
	if (firecount > 0) {
		firecount--;
		DecrementWallet(20);
	}
	//if skip turn set skip turn to false then return
	if (skipturn) {
		skipturn = false;
		if (turnCount % 3 == 0)
			turnCount = 0;
		return;
	}
	//if count==0 set in prison false
	if (prisonCount == 0)
		inPrison = false;
	//if in prison  decrement count return
	if (inPrison == true && prisonCount > 0) {
		prisonCount--;
		if (turnCount % 3 == 0) {
			wallet += diceNumber * 10;
			turnCount = 0;
		}
		return;
	}
	//if at charge wallet
	if (turnCount % 3 == 0 && SpecialUses>0) {
		pGrid->GetOutput()->PrintMessage("Do you wish to launch a special attack instead of recharging? y/n"); //ask
		string inp = pGrid->GetInput()->GetSrting(pGrid->GetOutput());
		if (inp == "y") { //if yes
			SpecialAttack sp(pGrid); 
			if (sp.Execute()) { //try to execute special
				turnCount = 0; //if success then reset turn count else continue and increment wallet
				return;
			}
		}
		
		pGrid->GetOutput()->ClearStatusBar();
	}
	if (turnCount % 3 == 0) {
		pGrid->PrintErrorMessage("Player " + to_string(playerNum) + " recharging " + to_string(diceNumber * 10) + " to wallet. Click to to continue.");
		wallet += diceNumber * 10;
		turnCount = 0;
		return;
	}
	if (wallet == 0)
		return;

	//if poisoned deduct dice 1
	
		
	// 3- Set the justRolledDiceNum with the passed diceNumber
	
	justRolledDiceNum = diceNumber;

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	pGrid->PrintErrorMessage("Player " + to_string(playerNum) + " just rolled " + to_string(justRolledDiceNum) + " .Click to continue.");
	int cellnum=pCell->GetCellPosition().GetCellNum() + justRolledDiceNum;
	//have to get to 100 but will be drawn on 99
	bool reached100=false;
	if (cellnum == NumVerticalCells * NumHorizontalCells + 1) {
		cellnum = NumVerticalCells * NumHorizontalCells;
		reached100 = true;
	}
	if (cellnum > (NumVerticalCells) * (NumHorizontalCells)+1)
		return;

	CellPosition pos(cellnum);

	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(this, pos);
	// 6- Apply() the game object of the reached cell (if any)
	if (pCell->GetGameObject())
		pCell->GetGameObject()->Apply(pGrid, this);

	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if (reached100) {
		pGrid->SetEndGame(true);
		pGrid->PrintErrorMessage("Player" + to_string(playerNum) + " has WON!. Click to continue...");
	}
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}