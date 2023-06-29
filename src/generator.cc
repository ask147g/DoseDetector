#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator() {
	fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator() {
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ThreeVector pos = G4ThreeVector(-10*CLHEP::cm, 0, 0);
	G4ThreeVector mom = G4ThreeVector(1, 0.01, 0);
	G4double a = 5*CLHEP::MeV;
	
	G4ParticleDefinition *particle = particleTable->FindParticle("e-");
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleEnergy(a);
	fParticleGun->SetNumberOfParticles(1);
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
}