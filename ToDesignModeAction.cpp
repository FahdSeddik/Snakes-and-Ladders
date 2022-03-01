#include "ToDesignModeAction.h"
#include "Grid.h"
ToDesignModeAction::ToDesignModeAction(ApplicationManager* pApp):Action(pApp) {

} // Constructor

	// ============ Virtual Functions ============
void ToDesignModeAction::ReadActionParameters() {
	//no parameters;

}// Reads parameters required for action to execute 
										 // (code depends on action type so virtual)

void ToDesignModeAction::Execute() {

	pManager->GetGrid()->GetOutput()->CreateDesignModeToolBar();

}  // Executes action (code depends on action type so virtual)

ToDesignModeAction::~ToDesignModeAction() {



}  // Virtual Destructor