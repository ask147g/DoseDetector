#ifndef INDUCED_ACTIVITY_HH
#define INDUCED_ACTIVITY_HH

#include "G4VPrimitivePlotter.hh"
#include "G4THitsMap.hh"

#include "G4VSolid.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VPVParameterisation.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4VScoreHistFiller.hh"

#include <iostream>
#include <map>
#include <utility>

// time in seconds

class InducedActivity : public G4VPrimitivePlotter {
public:
	InducedActivity(G4String name, G4double t = 360000, G4int depth = 0);
	~InducedActivity() override = default	;
	
	void Initialize(G4HCofThisEvent*);

private:
	G4int HCID;
	G4THitsMap<G4double>* EvtMap;
  G4double radiatedTime;

protected:
	G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
};

#endif