#include "parallelWorldMany.hh"

ParallelWorldMany::ParallelWorldMany(G4String name, G4ThreeVector worldSizes)
    :G4VUserParallelWorld(name) {
}

ParallelWorldMany::~ParallelWorldMany() {
}

void ParallelWorldMany::Construct() {
    SetupGeometry();
}

void ParallelWorldMany::ConstructSD() {
    SetupDetectors();
}

void ParallelWorldMany::SetupGeometry() {
    G4VPhysicalVolume* globalWorld = GetWorld();
    G4LogicalVolume* logicWorld = globalWorld->GetLogicalVolume();

    G4Box *waterBox = 
        new G4Box(
            "waterBox", 
            0.5*CLHEP::cm, 
            0.5*CLHEP::cm, 
            0.5*CLHEP::cm);

    waterLogic = 
        new G4LogicalVolume(
            waterBox, 
            0, 
            "waterLogic");

    G4VPhysicalVolume *waterWorld = 
        new G4PVPlacement(
            new G4RotationMatrix(0, 0., 0.), 
			G4ThreeVector(0., 0., 0.), 
			waterLogic, 
			"waterLogic", 
			logicWorld, 
			false, 
			0); 
}

void ParallelWorldMany::SetupDetectors() {
    G4MultiFunctionalDetector* det = new G4MultiFunctionalDetector("doseDetector");
    G4VPrimitiveScorer* primitive;
    primitive = new EffectiveDose("Edep", 1);
    det->RegisterPrimitive(primitive);
    G4SDManager::GetSDMpointer()->AddNewDetector(det);
    SetSensitiveDetector(waterLogic, det);
}