#include "parallelWorld.hh"

ParallelWorld::ParallelWorld(G4String name)
:G4VUserParallelWorld(name) {
}

ParallelWorld::~ParallelWorld() {
}

void ParallelWorld::Construct() {
    SetupGeometry();
}

void ParallelWorld::ConstructSD() {
    //SetupDetectors();
}

void ParallelWorld::SetupGeometry() {
    G4VPhysicalVolume* ghostWorld = GetWorld();
    G4LogicalVolume* logicWorld = ghostWorld->GetLogicalVolume();

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

void ParallelWorld::SetupDetectors() {
    G4MultiFunctionalDetector* det = new G4MultiFunctionalDetector("doseDetector");
    G4VPrimitiveScorer* primitive;
    primitive = new EffectiveDose("Edep");
    det->RegisterPrimitive(primitive);
    G4SDManager::GetSDMpointer()->AddNewDetector(det);
    SetSensitiveDetector(waterLogic, det);
}