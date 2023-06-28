#ifndef RUN_HH
#define RUN_HH

#include "globals.hh"
#include "G4Run.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "G4HCofThisEvent.hh"

class G4Event;

class UserRun : public G4Run {
public:
    UserRun();
    virtual ~UserRun();
    
    virtual void RecordEvent(const G4Event*);

    G4double GetTotalE() const    { return GetTotal(fMapSum); }
private:
    G4int fColIDSum;
    G4THitsMap<G4double> fMapSum;

    G4double GetTotal(const G4THitsMap<G4double> &map) const;
};

#endif