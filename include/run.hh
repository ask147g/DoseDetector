#ifndef RUN_HH
#define RUN_HH

class UserRun : public G4Run {
public:
    UserRun();
    ~UserRun();
    
    virtual void RecordEvent(const G4Event* aRun);
    virtual void Merge(const G4Run* aRun);
private:
}

#endif