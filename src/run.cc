#include "run.hh"

UserRun::UserRun() {
    G4SDManager* SDMan = G4SDManager::GetSDMpointer();
    fColIDSum = SDMan->GetCollectionID("doseDetector/Edep");
    fColIDActivity = SDMan->GetCollectionID("doseDetector/Activity");
}

UserRun::~UserRun() {
}

void UserRun::RecordEvent(const G4Event* evt) {
    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
    if(!HCE) return;
    G4THitsMap<G4double>* evtMap 
        = (G4THitsMap<G4double>*)(HCE->GetHC(fColIDSum));
    fMapSum += *evtMap;

    G4THitsMap<G4double>* evtMapA
        = (G4THitsMap<G4double>*)(HCE->GetHC(fColIDActivity));
    
    fMapActivity += *evtMapA;

    G4THitsMap<G4String>* evtMapName
        = (G4THitsMap<G4String>*)(HCE->GetHC(fColIDActivity));
    
    fMapActivityName += *evtMapName;
}

void UserRun::Merge(const G4Run * aRun) {
  const UserRun * localRun = static_cast<const UserRun *>(aRun);

  fMapSum += localRun->fMapSum;
  fMapActivity += localRun->fMapActivity;
  fMapActivityName += localRun->fMapActivityName;

  G4Run::Merge(aRun);
}

G4double UserRun::GetTotal(const G4THitsMap<G4double> &map) const {
  G4double tot = 0.;
  if(map.GetSize()==0) return tot;
  std::map<G4int,G4double*>::iterator itr = map.GetMap()->begin();
  for(; itr != map.GetMap()->end(); itr++) {
    tot += *(itr->second); 
  }
  return tot;
}

G4double UserRun::GetTotalOne() const {
  std::map<G4int,G4double*>::iterator itr = fMapActivity.GetMap()->begin();
  for(; itr != fMapActivity.GetMap()->end(); itr++) {
    G4cout << *(itr->second) << G4endl; 
  }
  return 0.;
}

// amount of detectors
G4double UserRun::GetTotalPara(int xx, int yy, int zz, const G4THitsMap<G4double> &map) const {
  G4double tot[20][20][20] = {0., 0., 0.};
  if(map.GetSize()==0) return tot[xx][yy][zz];
  std::map<G4int,G4double*>::iterator itr = map.GetMap()->begin();
  for(; itr != map.GetMap()->end(); itr++) {
    //G4cout << *(itr->second) << G4endl;
    const int x = (itr->first / 400);
    const int y = (itr->first - x*400) / 20;
    const int z = itr->first - x* 400 - y*20;
    tot[x][y][z] += *(itr->second); 
  }
  return tot[xx][yy][zz];
}

G4double UserRun::GetTotalNuclides(int xx, int yy, int zz) const {
  G4double tot[20][20][20] = {0., 0., 0.};
  if(fMapActivityName.GetSize()==0) return tot[xx][yy][zz];
  std::map<G4int,G4String*>::iterator itr = fMapActivityName.GetMap()->begin();
  for(; itr != fMapActivityName.GetMap()->end(); itr++) {
    G4cout << *(itr->second) << G4endl;
    const int x = (itr->first / 400);
    const int y = (itr->first - x*400) / 20;
    const int z = itr->first - x* 400 - y*20;
    //tot[x][y][z] += *(itr->second); 
  }
  return 0;
}