#include "EquivalentDose.hh"

EquivalentDose::EquivalentDose(G4String name, G4int depth)
    : G4VPrimitivePlotter(name, depth),
    HCID(-1),
    EvtMap(nullptr) {
}

void EquivalentDose::Initialize(G4HCofThisEvent* anEvent) {
}

void EquivalentDose::clear() {
}

void EquivalentDose::PrintAll() {
}


G4bool EquivalentDose::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
}

G4double EquivalentDose::ComputeVolume(G4Step* aStep, G4int idx) {
}