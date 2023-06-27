#ifndef CONSTRUCTION.HH
#define CONSTRUCTION.HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDParticleFilter.hh"

class PhysicalConstruction : public G4VUserDetectorConstruction {
public:
	PhysicalConstruction();
	~PhysicalConstruction();
	
	virtual G4VPhysicalVolume *Construct();	//
    void ConstructSDandField();
};

#endif