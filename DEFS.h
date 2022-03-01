#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.
enum SpecialAttackType {
	ICE,
	FIRE,
	POISON,
	LIGHTNING,
	NA_SA //to detect if player still didnt choose
};
enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode

	ADD_LADDER,		// Add Ladder Action
	ADD_SNAKE,		// Add Snake Action	
	ADD_CARD,		// Add Card Action	
	COPY_CARD,		//Copy card action
	CUT_CARD,		//Cut card action
	PASTE_CARD,		//paste card action
	DELETE_OBJECT,	// Deletes game object
	SAVE_GRID,			//Saves grid
	OPEN_GRID,			//Opens grid
	EXIT,			// Exit Application
	TO_PLAY_MODE,	// Go to Play Mode

	///TODO: Add more action types of Design Mode

	//  [2] Actions of Play Mode

	ROLL_DICE,		// Roll Dice Action
	INPUT_DICE_VALUE,
	NEW_GAME,
	TO_DESIGN_MODE,	// Go to Design Mode


	///TODO: Add more action types of Play Mode

	//  [3] Others

	EMPTY,				// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,			// Inside Grid Area
	STATUS 				// Inside StatusBar Area
};

#endif