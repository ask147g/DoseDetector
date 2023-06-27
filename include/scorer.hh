#ifndef SCORER_HH
#define SCORER_HH

#include "G4VPrimitiveScorer.hh"

class DoseScorer : public G4VPrimitiveScorer {
public:
	DoseScorer();
	~DoseScorer();
	
	virtual void Initialize(G4HCofThisEvent* anEvent);
    virtual void EndOfEvent(G4HCofThisEvent* anEvent);
};

#endif