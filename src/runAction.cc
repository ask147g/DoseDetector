#include "runAction.hh"

UserRunAction::UserRunAction() {
}

UserRunAction::~UserRunAction() {
}

G4Run* UserRunAction::GenerateRun() {
    return new UserRun;
}

void UserRunAction::BeginOfRunAction(const G4Run* aRun) {

}

void UserRunAction::EndOfRunAction(const G4Run* aRun) {
    const UserRun* theRun = (const UserRun*)aRun;

    G4cout << G4BestUnit(theRun->GetTotalE()*0.25, "Effective Dose") << G4endl;
}