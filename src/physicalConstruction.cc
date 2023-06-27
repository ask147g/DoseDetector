#include "physicalConstruction.hh"

PhysicalConstruction::PhysicalConstruction() {
}

PhysicalConstruction::~PhysicalConstruction() {
}

G4VPhysicalVolume *PhysicalConstruction::Construct() {
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *vacuum = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material *water = nist->FindOrBuildMaterial("G4_WATER");
	

    // Mother Volume
	G4Box *solidWorld = 
        new G4Box(
            "solidWorld", 
            10*CLHEP::cm, 
            10*CLHEP::cm, 
            10*CLHEP::cm);

	G4LogicalVolume *logicWorld = 
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
	
    // Daughter Volume
    G4Box *waterBox = 
        new G4Box(
            "waterBox", 
            5*CLHEP::cm, 
            5*CLHEP::cm, 
            5*CLHEP::cm);

    G4LogicalVolume *waterLogic = 
        new G4LogicalVolume(
            waterBox, 
            water, 
            "waterLogic");

    G4VPhysicalVolume *waterWorld = 
        new G4PVPlacement(
            0, 
			G4ThreeVector(0., 0., 0.), 
			waterLogic, 
			"physWorld", 
			logicWorld, 
			false, 
			0, 
			false); 
    
	return physWorld;
}

void PhysicalConstruction::ConstructSDandField() {
    G4SDParticleFilter* gammaFilter 
        = new G4SDParticleFilter("gammaFilter", "gamma");
  
    G4MultiFunctionalDetector* det = new G4MultiFunctionalDetector("doseDetector");
    G4SDManager::GetSDMpointer()->AddNewDetector(det);

    G4VPrimitiveScorer* primitive;
    primitive = new G4PSEnergyDeposit("Edep");
    primitive->SetFilter(gammaFilter);
    det->RegisterPrimitive(primitive);
    SetSensitiveDetector("waterLogic", det);
}