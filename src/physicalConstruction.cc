#include "physicalConstruction.hh"

PhysicalConstruction::PhysicalConstruction() {
}

PhysicalConstruction::~PhysicalConstruction() {
}

G4VPhysicalVolume *PhysicalConstruction::Construct() {
	G4VPhysicalVolume *physWorld = SetupGeometry();
	return physWorld;
}

G4VPhysicalVolume* PhysicalConstruction::SetupGeometry() {
    G4VPhysicalVolume *physWorld = BuildMotherVolume();
    BuildWorldConstruction();

    return physWorld;
}

G4VPhysicalVolume* PhysicalConstruction::BuildMotherVolume() {
    G4NistManager *nist = G4NistManager::Instance();
	G4Material *vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    
    G4Box *solidWorld = 
        new G4Box(
            "solidWorld", 
            10*CLHEP::cm, 
            10*CLHEP::cm, 
            10*CLHEP::cm);

	logicWorld = 
        new G4LogicalVolume(
            solidWorld, 
            vacuum, 
            "logicWorld");
	
	G4VPhysicalVolume *physWorld = 
        new G4PVPlacement(
            0, 
			G4ThreeVector(0., 0., 0.), 
			logicWorld, 
			"physWorld", 
			0, 
			false, 
			0, 
			false); 

    return physWorld;
}

void PhysicalConstruction::BuildWorldConstruction() {
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *water = nist->FindOrBuildMaterial("G4_WATER");

    G4Box *waterBox = 
        new G4Box(
            "waterBox_main", 
            5*CLHEP::cm, 
            5*CLHEP::cm, 
            5*CLHEP::cm);

    G4LogicalVolume *waterLogic = 
        new G4LogicalVolume(
            waterBox, 
            water, 
            "waterLogic_main");

    G4VPhysicalVolume *waterWorld = 
        new G4PVPlacement(
            0, 
			G4ThreeVector(0., 0., 0.), 
			waterLogic, 
			"physWorld_main", 
			logicWorld, 
			false, 
			0, 
			false); 
}