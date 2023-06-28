#ifndef EQUIVALENT_DOSE_HH
#define EQUIVALENT_DOSE_HH

#include "G4VPrimitiveScorer.hh"
#include "G4VPrimitivePlotter.hh"
#include "G4THitsMap.hh"


class EquivalentDose : public G4VPrimitivePlotter {
public:
	EquivalentDose(G4String name, G4int depth = 0);
	~EquivalentDose() override = default	;
	
	void Initialize(G4HCofThisEvent* anEvent);
    void clear() override;
  	void PrintAll() override;

protected:
	G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
	virtual G4double ComputeVolume(G4Step*, G4int idx);

private:
	G4int HCID;
	G4THitsMap<G4double>* EvtMap;
};

#endif