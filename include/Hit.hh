#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class ActivityHit : public G4VHit {   
public:
    ActivityHit() {};
    ~ActivityHit() {};

    virtual void Draw() {};
    virtual void Print() {};

    void SetName(G4String particle) {name = particle;}
    G4String GetName() {return name;}
    void SetLifeTime(G4double life) {lifeTime = life;}
    G4double GetLifeTime() {return lifeTime;}

private:
    G4String name;
    G4double lifeTime;
};

typedef G4THitsCollection<ActivityHit> HitsCollection;

extern G4ThreadLocal G4Allocator<ActivityHit>* ActivityHitAllocator;

#endif