#include "EquivalentDose.hh"

EquivalentDose::EquivalentDose(G4String name, G4int depth)
    : G4VPrimitivePlotter(name, depth),
    HCID(-1),
    EvtMap(nullptr) {
}

void EquivalentDose::Initialize(G4HCofThisEvent* HCE) {
    EvtMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(),
                                    GetName());
  if(HCID < 0)
  {
    HCID = GetCollectionID(0);
  }
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*) EvtMap);
}

G4bool EquivalentDose::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep == 0.)
    return false;

  G4int idx = ((G4TouchableHistory*) (aStep->GetPreStepPoint()->GetTouchable()))
                ->GetReplicaNumber(indexDepth);
  G4double cubicVolume = ComputeVolume(aStep, idx);

  G4double density = aStep->GetTrack()
                       ->GetStep()
                       ->GetPreStepPoint()
                       ->GetMaterial()
                       ->GetDensity();
  G4double dose  = edep / (density * cubicVolume);
  G4double wei   = aStep->GetPreStepPoint()->GetWeight();
  G4int index    = GetIndex(aStep);
  
  EquivalentCoefficient(aStep);
  // определить тип частицы, энергию и домножить на коэффициент
  G4double dosew = dose * wei;
  EvtMap->add(index, dosew);

  if(!hitIDMap.empty() && hitIDMap.find(index) != hitIDMap.cend())
  {
    auto filler = G4VScoreHistFiller::Instance();
    if(filler == nullptr)
    {
      G4Exception(
        "EquivalentDose::ProcessHits", "SCORER0123", JustWarning,
        "G4TScoreHistFiller is not instantiated!! Histogram is not filled.");
    }
    else
    {
      filler->FillH1(hitIDMap[index], dose, wei);
    }
  }

  return true;

}

G4double EquivalentDose::ComputeVolume(G4Step* aStep, G4int idx)
{
  G4VSolid* solid = ComputeSolid(aStep, idx);
  return solid->GetCubicVolume();
}

G4double EquivalentDose::EquivalentCoefficient(G4Step* aStep) {
    G4double energy = aStep->GetTrack()->GetKineticEnergy();
    G4cout << energy << G4endl;
    return 1;
}