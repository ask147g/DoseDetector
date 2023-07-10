#ifndef RUN_HH
#define RUN_HH

#include "globals.hh"
#include "G4Run.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "G4HCofThisEvent.hh"

#include <map>
#include <utility>

class G4Event;

class UserRun : public G4Run {
public:
    UserRun();
    virtual ~UserRun();
    
    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);

    G4double GetTotalE(int xx, int yy, int zz) const    { return GetTotalPara(xx, yy, zz, fMapSum); }
    std::map<G4String, std::pair<G4int, G4double> > GetTotalOne() const;
    G4double GetActivity(int xx, int yy, int zz) const    { return GetTotalPara(xx, yy, zz, fMapActivity); }
    G4double GetActivityy(int xx, int yy, int zz) const    { return GetTotalNuclides(xx, yy, zz); }
private:
    G4int fColIDSum;
    G4THitsMap<G4double> fMapSum;

    G4int fColIDActivity;
    G4THitsMap<G4double> fMapActivity; // life time
    G4THitsMap<G4String> fMapActivityName; // particle name

    std::map<G4String, std::pair<G4int, G4double> > nuclides;

    G4double GetTotal(const G4THitsMap<G4double> &map) const;
    G4double GetTotalPara(int x, int y, int z, const G4THitsMap<G4double> &map) const;
    G4double GetTotalNuclides(int x, int y, int z) const;
};

#endif