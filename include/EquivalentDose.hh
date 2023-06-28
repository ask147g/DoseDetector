#ifndef EQUIVALENT_DOSE_HH
#define EQUIVALENT_DOSE_HH

//#include "G4VPrimitiveScorer.hh"
#include "G4VPrimitivePlotter.hh"
#include "G4THitsMap.hh"

#include "G4VSolid.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VPVParameterisation.hh"
#include "G4UnitsTable.hh"
#include "G4VScoreHistFiller.hh"

#include <iostream>

class EquivalentDose : public G4VPrimitivePlotter {
public:
	EquivalentDose(G4String name, G4int depth = 0);
	~EquivalentDose() override = default	;
	
	void Initialize(G4HCofThisEvent* anEvent);

protected:
	G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
	virtual G4double ComputeVolume(G4Step* aStep, G4int idx);

private:
	G4int HCID;
	G4THitsMap<G4double>* EvtMap;

	G4double EquivalentCoefficient(G4Step*);
};

#endif