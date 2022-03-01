#pragma once

#include "Grid.h"
#include "Cell.h"

class Player
{
	Cell * pCell;		   // pointer to the current Cell of the player

	const int playerNum;   // the player number (from 0 to MaxPlayerCount-1)
	                       // player number does NOT change after construction (const.)

	int stepCount;		   // step count which is the same as his cellNum: from 1 to NumVerticalCells*NumHorizontalCells
	int wallet;		       // player's wallet (how many coins he has -- integer)
	int justRolledDiceNum; // the current dice number which is just rolled by the player
	int turnCount;         // a counter that starts with 0, is incremented with each dice roll
	                       // and reset again when reached 3
	                       // it is used to indicate when to move and when to add to your wallet
	bool inPrison;
	int prisonCount;
	bool skipturn;
	SpecialAttackType SA;
	int firecount;
	int SpecialUses;
	int poisoned;
public:

	Player(Cell * pCell, int playerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell * cell);		// A setter for the pCell
	Cell* GetCell() const;			// A getter for the pCell

	void SetWallet(int wallet);		// A setter for the wallet
	int GetWallet() const;			// a getter for the wallet

	int GetTurnCount() const;		// A getter for the turnCount
	void SetSkipTurn(bool);
	int GetJustRolled()const;
	void DecrementWallet(int);
	bool getPrison() const;
	void setPrisonCount(int);
	void setinPrison(bool);
	void setSpecialAttack(SpecialAttackType);
	SpecialAttackType getSpecialAttack();
	int getSpecialUses()const;
	void setSpecialUses(int);
	void setFirecount(int);
	void SetPoisoned(int);
	void SetTurnCount(int = 0);
	void Restart(Grid*);
	///TODO: You can add setters and getters for data members here (if needed)

	// ====== Drawing Functions ======

	void Draw(Output* pOut) const;			// Draws the Player's Circle on its current cell

	void ClearDrawing(Output* pOut) const;	// Clears the Player's Circle from its current cell

	// ====== Game Functions ======

	void Move(Grid * pGrid, int diceNumber);	// Moves the Player with the passed diceNumber 
	                                            // and Applies the Game Object's effect (if any) of the end reached cell 
	                                            // for example, if the end cell contains a ladder, take it
	int TransferCoins(Player* to, int amount); //transfers coins to passed player
												//if calling player doesnt have enough coins then it will transfer all the wallet
												//and return -1
	void IncrementWallet(int amount);			//increments calling player's wallet with amount
	void AppendPlayerInfo(string & playersInfo) const; // Appends player's info to the input string, 
	                                                   // for example: P0(wallet, turnCount)

};

