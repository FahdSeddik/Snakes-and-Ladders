#include "ToPlayModeAction.h"
#include "Grid.h"
ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp):Action(pApp) {

} // Constructor

	// ============ Virtual Functions ============
void ToPlayModeAction::ReadActionParameters() {
	//no parameters;

}// Reads parameters required for action to execute 
										 // (code depends on action type so virtual)

void ToPlayModeAction::Execute() {

	pManager->GetGrid()->GetOutput()->CreatePlayModeToolBar();

}  // Executes action (code depends on action type so virtual)

ToPlayModeAction::~ToPlayModeAction() {



}  // Virtual Destructor