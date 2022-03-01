#include "SpecialAttack.h"



SpecialAttack::SpecialAttack(Grid* Gr) {
	check = true;
	pGrid = Gr;
}  // Constructor

	// ============ Virtual Functions ============

void SpecialAttack::ReadParameters() {
	
	Player* pPlayer = pGrid->GetCurrentPlayer();
	if (pPlayer->getSpecialUses()>0) {
		pGrid->GetOutput()->PrintMessage("Choose a special attack type (ice=0,fire=1,poison=2,lightning=3): ");
		int attack = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
		if (attack != ICE && attack != FIRE && attack != POISON && attack != LIGHTNING) {
			pGrid->PrintErrorMessage("Error: invalid input. Click to continue..");
			check = false;
			return;
		}
		if (pPlayer->getSpecialAttack() == (SpecialAttackType)attack) {
			pGrid->PrintErrorMessage("You already chose this attack before. Click to continue...");
			check = false;
			return;
		}
		pPlayer->setSpecialAttack((SpecialAttackType)attack);
		
	}
	else
		check = false;
	

} // Reads parameters required for action to execute 
// (code depends on action type so virtual)

bool SpecialAttack::Execute() {
	
	Player* pPlayer = pGrid->GetCurrentPlayer();
	ReadParameters();
	if (check == true) {
		if (pPlayer->getSpecialAttack() == ICE) {
			pGrid->GetOutput()->PrintMessage("ICE ATTACK: Choose player number to prevent from next turn:");
			int playertoprevent = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
			pGrid->SkipTurnofPlayer(playertoprevent);
			pPlayer->setSpecialUses(pPlayer->getSpecialUses() - 1);
		}
		else if (pPlayer->getSpecialAttack() == FIRE) {
			pGrid->GetOutput()->PrintMessage("FIRE ATTACK: Choose player number to burn:");
			int playertoburn= pGrid->GetInput()->GetInteger(pGrid->GetOutput());
			Player* ap=pGrid->GetPlayerwithNumber(playertoburn);
			ap->setFirecount(3);
			pPlayer->setSpecialUses(pPlayer->getSpecialUses() - 1);
		}
		else if (pPlayer->getSpecialAttack() == POISON) {
			pGrid->GetOutput()->PrintMessage("POISON ATTACK: Choose player number to poison:");
			int playertopoison = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
			Player* ap = pGrid->GetPlayerwithNumber(playertopoison);
			ap->SetPoisoned(5);
			pPlayer->setSpecialUses(pPlayer->getSpecialUses() - 1);
		}
		else if (pPlayer->getSpecialAttack() == LIGHTNING) {
			pGrid->PrintErrorMessage("DEDUCTING 20 COINS FROM ALL OTHER PLAYERS. Click to continue...");
			pGrid->LightningOtherPlayers(pPlayer);
			pPlayer->setSpecialUses(pPlayer->getSpecialUses() - 1);
		}
		pGrid->GetOutput()->ClearStatusBar();
		return true;
	}
	else
		return false;
	
}  // Executes action (code depends on action type so virtual)

SpecialAttack::~SpecialAttack() {



}  // Virtual Destructor