#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator() {
	gun = new G4SingleParticleSource();
}

MyPrimaryGenerator::~MyPrimaryGenerator() {
	delete gun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ThreeVector pos = G4ThreeVector(-10*CLHEP::cm, 0*CLHEP::cm, 0);
	G4ThreeVector mom = G4ThreeVector(1, 0, 0);
	//G4double a = 1.3325*CLHEP::MeV;
	
	G4ParticleDefinition *particle = particleTable->FindParticle("neutron");

	gun->SetParticleDefinition(particle);
	
	G4SPSEneDistribution* energy = gun->GetEneDist();
	energy->SetEnergyDisType("Mono");
	G4double a = 1.3325;
	energy->SetMonoEnergy(50*CLHEP::MeV);
	
	G4SPSPosDistribution* position = gun->GetPosDist();
	position->SetPosDisType("Point");
	position->SetCentreCoords(pos);
	
	G4SPSAngDistribution* angular = gun->GetAngDist();
	angular->SetParticleMomentumDirection(mom);
	angular -> SetAngDistType("iso");
	angular -> SetMinPhi(135*degree);
	angular -> SetMaxPhi(225*degree);
	angular -> SetMinTheta(45*degree);
	angular -> SetMaxTheta(135*degree);

	gun->GeneratePrimaryVertex(anEvent);

	energy->SetMonoEnergy(100*CLHEP::MeV);

	gun->GeneratePrimaryVertex(anEvent);
}