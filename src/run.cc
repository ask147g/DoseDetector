#include "run.hh"

UserRun::UserRun() {
    G4SDManager* SDMan = G4SDManager::GetSDMpointer();
    fColIDSum = SDMan->GetCollectionID("doseDetector/Edep");
}

UserRun::~UserRun() {
}

void UserRun::RecordEvent(const G4Event* evt) {
    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
    if(!HCE) return;
    G4THitsMap<G4double>* evtMap 
        = (G4THitsMap<G4double>*)(HCE->GetHC(fColIDSum));
    fMapSum += *evtMap;

    
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

G4double UserRun::GetTotalPara(int xx, int yy, int zz, const G4THitsMap<G4double> &map) const {
  G4double tot[20][20][20] = {0., 0., 0.};
  if(map.GetSize()==0) return tot[xx][yy][zz];
  std::map<G4int,G4double*>::iterator itr = map.GetMap()->begin();
  for(; itr != map.GetMap()->end(); itr++) {
    const int x = (itr->first / 400);
    const int y = (itr->first - x*400) / 20;
    const int z = itr->first - x* 400 - y*20;
    tot[x][y][z] += *(itr->second); 
  }
  return tot[xx][yy][zz];
}