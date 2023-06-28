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
#include <map>
#include <utility>

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
	
	std::map<
		std::pair< G4String, std::pair <G4double, G4double> >, // first is particle name, pair is a range of energies of particle
			G4double > equivalentCoefficient = { // energies in MeV
				{std::make_pair("gamma", std::make_pair(0, 0)), 1},
				{std::make_pair("e-", std::make_pair(0, 0)), 1},
				{std::make_pair("e+", std::make_pair(0, 0)), 1},
				{std::make_pair("mu-", std::make_pair(0, 0)), 1},
				{std::make_pair("mu+", std::make_pair(0, 0)), 1},
				{std::make_pair("n", std::make_pair(0, 0.01)), 5},
				{std::make_pair("n", std::make_pair(0.01, 0.1)), 10},
				{std::make_pair("n", std::make_pair(0.1, 2)), 20},
				{std::make_pair("n", std::make_pair(2, 20)), 10},
				{std::make_pair("n", std::make_pair(20, 0)), 5},
				{std::make_pair("proton", std::make_pair(2, 0)), 5},
				{std::make_pair("alpha", std::make_pair(0, 0)), 20}
				// как узнать, что частица - ядро?
		};
};

#endif