#include <iostream>


#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QBBC.hh"

#include "physicalConstruction.hh"
#include "action.hh"

int main(int argc, char** argv) {
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    CLHEP::HepRandom::setTheSeed(time(NULL));

    G4UIExecutive* ui = nullptr;
    if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv); }

	G4RunManager *runManager = new G4RunManager();
	
	runManager->SetUserInitialization(new PhysicalConstruction());
	runManager->SetUserInitialization(new QBBC());
	runManager->SetUserInitialization(new MyActionInitialization());
	
	runManager->Initialize();
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if ( ! ui ) {
    // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else {
    // interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }
	
    delete visManager;
    delete runManager;
	return 0;
}