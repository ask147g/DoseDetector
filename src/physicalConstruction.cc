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
	G4Material *vacuum = nist->FindOrBuildMaterial("G4_AIR");
    
    G4Box *solidWorld = 
        new G4Box(
            "solidWorld", 
            500*CLHEP::cm, 
            500*CLHEP::cm, 
            500*CLHEP::cm);

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
    G4Material *water = nist->FindOrBuildMaterial("G4_AIR");

    G4Box *waterBox = 
        new G4Box(
            "waterBox_main", 
            0.5*CLHEP::cm, 
            0.5*CLHEP::cm, 
            0.5*CLHEP::cm);

    G4LogicalVolume *waterLogic = 
        new G4LogicalVolume(
            waterBox, 
            water, 
            "waterLogic_main");

    G4VPhysicalVolume *waterWorld = 
        new G4PVPlacement(
            new G4RotationMatrix(0, 0., 0.), 
			G4ThreeVector(0., 0., 0.), 
			waterLogic, 
			"physWorld_main", 
			logicWorld, 
			false, 
			0, 
			false); 


    G4MultiFunctionalDetector* det = new G4MultiFunctionalDetector("doseDetector");
    G4VPrimitiveScorer* primitive;
    primitive = new EffectiveDose("Edep");
    det->RegisterPrimitive(primitive);
    G4SDManager::GetSDMpointer()->AddNewDetector(det);
    SetSensitiveDetector(waterLogic, det);
}