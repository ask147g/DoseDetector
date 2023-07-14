#include "InducedActivity.hh"
#include "G4VProcess.hh"

#include <fstream>

InducedActivity::InducedActivity(G4String name, G4int depth)
  : G4VPrimitivePlotter(name, depth),
    HCID(-1) {
}

void InducedActivity::Initialize(G4HCofThisEvent* HCE) {
  tracker = new HitsCollection(GetMultiFunctionalDetector()->GetName(), GetName());
  
  if(HCID < 0) {
    HCID = GetCollectionID(0);
  }
  HCE->AddHitsCollection(HCID, tracker);
}

G4bool InducedActivity::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
  auto particle = aStep->GetTrack()->GetParticleDefinition();
  
  //if (aStep->GetTrack()->GetParentID() != 0) return false;

  //if (particle->GetIonLifeTime() < 0) return false; // only radioactive ions
  if (aStep->GetTrack()->GetParentID() == 0) return false; // only secondary etc particles
  //if (particle->GetAtomicNumber() == 0) return false; // n, e-, etc
  //if (aStep->GetTrack()->GetCreatorProcess() && aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "Decay") return false;
  
  //if (aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "photonNuclear") return false;
  
  //if (aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "neutronInelastic") return false;
  //if (aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "nCapture") return false;

  
  //G4cout << aStep->GetTrack()->GetCreatorProcess()->GetProcessName() << G4endl;
  //G4cout << particle->GetParticleName() << " " << G4BestUnit(particle->GetIonLifeTime()/std::log(2), "Time") << G4endl;
  
  //if (particle->GetParticleName() != "Mo100" && 
  //  aStep->GetTrack()->GetParentID() != 1) return false;

  std::ofstream test;
  test.open("test.csv", std::ios::app);
  if (test.is_open()) {
    test << particle->GetParticleName() << " " << aStep->GetTrack()->GetCreatorProcess()->GetProcessName() << std::endl;
  }

  G4double activity = particle->GetIonLifeTime()/CLHEP::second;
  G4String name = particle->GetParticleName();

  G4int index = GetIndex(aStep);
  ActivityHit* newHit = new ActivityHit();
  newHit->SetName(name);
  newHit->SetLifeTime(activity);
  tracker->insert(newHit);

  return true;
}
