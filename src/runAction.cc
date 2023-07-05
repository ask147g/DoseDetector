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
    std::ofstream out;
    out.open("dose.csv");

    std::ofstream outActivity;
    outActivity.open("activity.csv");

    if (out.is_open())
    {
        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                for (int z = 0; z < 20; z++) {
                    out << theRun->GetTotalE(x, y, z)*0.25/CLHEP::joule*CLHEP::kilogram/1.e-12 << std::endl;
                    outActivity << theRun->GetActivity(x, y, z)*0.25 << std::endl;
                    //out << G4BestUnit(theRun->GetTotalE(x, y, z)*0.25, "Effective Dose") << std::endl;
                }
            }
        }
    }
    out.close(); 
    outActivity.close(); 
}