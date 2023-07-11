#include "InducedActivity.hh"
#include "G4VProcess.hh"

InducedActivity::InducedActivity(G4String name, G4int depth)
  : G4VPrimitivePlotter(name, depth),
    HCID(-1) {
      new G4UnitDefinition("millibecquerel", "milliBq", "Activity", 1.e-3*CLHEP::Bq);
      new G4UnitDefinition("microbecquerel", "microBq", "Activity", 1.e-6*CLHEP::Bq);
      new G4UnitDefinition("nanobecquerel", "nanoBq", "Activity", 1.e-9*CLHEP::Bq);
      new G4UnitDefinition("picobecquerel", "picoBq", "Activity", 1.e-12*CLHEP::Bq);
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
  
  if (particle->GetIonLifeTime() < 0) return false; // only radioactive ions
  if (aStep->GetTrack()->GetParentID() == 0) return false; // only secondary etc particles
  if (particle->GetAtomicNumber() == 0) return false; // n, e-, etc
  if (aStep->GetTrack()->GetCreatorProcess() && aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "Decay") return false; // only secondary particles
  
  //if (aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "neutronInelastic") return false;
  //if (aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "nCapture") return false;

  //G4cout << aStep->GetTrack()->GetCreatorProcess()->GetProcessName() << G4endl;
  //G4cout << particle->GetParticleName() << " " << G4BestUnit(particle->GetIonLifeTime()/std::log(2), "Time") << G4endl;
    
  G4double activity = particle->GetIonLifeTime()/CLHEP::second;
  G4String name = particle->GetParticleName();

  G4int index = GetIndex(aStep);
  ActivityHit* newHit = new ActivityHit();
  newHit->SetName(name);
  newHit->SetLifeTime(activity);
  tracker->insert(newHit);

  return true;
}
