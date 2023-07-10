#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"

class Hit : public G4VHit {   
public:
    Hit();
    ~Hit();

    void Draw() const;
    void Print() const;

private:

};

typedef G4THitsCollection<Hit> HitsCollection;

#endif