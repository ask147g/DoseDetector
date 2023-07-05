#include "InducedActivity.hh"

InducedActivity::InducedActivity(G4String name, G4double t, G4int depth)
  : G4VPrimitivePlotter(name, depth),
    HCID(-1),
    EvtMap(nullptr),
    radiatedTime(t) {
}

void InducedActivity::Initialize(G4HCofThisEvent* HCE) {
  EvtMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(),
                                    GetName());
  if(HCID < 0)
  {
    HCID = GetCollectionID(0);
  }
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*) EvtMap);
}

G4bool InducedActivity::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
  auto particle = aStep->GetTrack()->GetParticleDefinition();
  if (particle->GetIonLifeTime() < 0) return false;
  if (aStep->GetTrack()->GetParentID() == 0) return false;
  if (particle->GetAtomicNumber() == 0) return false;
  G4int pdg = particle->GetPDGEncoding();
  G4double energy = aStep->GetTrack()->GetTotalEnergy();
  //G4cout << particle->GetParticleName() << " " << G4BestUnit(particle->GetPDGLifeTime(), "Time") << 
  //  " " << particle->GetPDGLifeTime()/CLHEP::second << G4endl;
  G4int idx = ((G4TouchableHistory*) (aStep->GetPreStepPoint()->GetTouchable()))
                ->GetReplicaNumber(indexDepth);

  G4double activity = (1-std::exp(-std::log(2)/particle->GetPDGLifeTime()/CLHEP::second*radiatedTime))/radiatedTime;
  G4int index = GetIndex(aStep);
  
  EvtMap->add(index, activity);

  return true;
}
