//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: nwaterSteppingAction.cc 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file nwaterSteppingAction.cc
/// \brief Implementation of the nwaterSteppingAction class

#include "nwaterSteppingAction.hh"
#include "nwaterEventAction.hh"
#include "nwaterDetectorConstruction.hh"
#include "nwaterAnalysis.hh"

#include "G4ParticleTypes.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterSteppingAction::nwaterSteppingAction(
                      const nwaterDetectorConstruction* detectorConstruction)
: G4UserSteppingAction(),
  fScoringVolume(detectorConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterSteppingAction::~nwaterSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nwaterSteppingAction::UserSteppingAction(const G4Step* step)
{

  // get volume of the current step
  G4VPhysicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume();

  // check if we are in scoring volume
  if (volume != fScoringVolume->GetLayer1() 
      && volume != fScoringVolume->GetLayer2()
      && volume != fScoringVolume->GetLayer3()) return;
  
  const G4StepPoint* startPoint = step->GetPreStepPoint();

  G4AnalysisManager* analysis = G4AnalysisManager::Instance();

  G4ParticleDefinition* particle = step->GetTrack()->GetDefinition();

  // const std::vector<const G4Track*>* secondary 
  //                                   = step->GetSecondaryInCurrentStep(); 
  G4int ih;

  // Layer 1 Get the energy at the beginning of the step for each particle

  if (volume == fScoringVolume->GetLayer1() && 
    step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary){

    G4double energy = startPoint->GetKineticEnergy();

    //energy spectrum
      ih = 0; 
           if (particle == G4Gamma::Gamma())            ih = 2;
      else if (particle == G4Proton::Proton())          ih = 1;
      else if (particle == G4Neutron::Neutron())        ih = 3;
      else if (particle == G4Electron::Electron())      ih = 4;
      else if (particle == G4Deuteron::Deuteron())      ih = 5;
      else if (particle == G4Alpha::Alpha())            ih = 6; 
      
      if (ih > 0) analysis->FillH1(ih,energy);

  }
  // Layer 2

  if (volume == fScoringVolume->GetLayer2() && 
    step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary){

    G4double energy = startPoint->GetKineticEnergy();

    //energy spectrum
      ih = 0; 
           if (particle == G4Gamma::Gamma())            ih = 8;
      else if (particle == G4Proton::Proton())          ih = 7;
      else if (particle == G4Neutron::Neutron())        ih = 9;
      else if (particle == G4Electron::Electron())      ih = 10;
      else if (particle == G4Deuteron::Deuteron())      ih = 11;
      else if (particle == G4Alpha::Alpha())            ih = 12; 
      
      if (ih > 0) analysis->FillH1(ih,energy);

  }
  // Layer 3

  if (volume == fScoringVolume->GetLayer3() && 
    step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary){

    G4double energy = startPoint->GetKineticEnergy();

    //energy spectrum
      ih = 0; 
           if (particle == G4Gamma::Gamma())            ih = 14;
      else if (particle == G4Proton::Proton())          ih = 13;
      else if (particle == G4Neutron::Neutron())        ih = 15;
      else if (particle == G4Electron::Electron())      ih = 16;
      else if (particle == G4Deuteron::Deuteron())      ih = 17;
      else if (particle == G4Alpha::Alpha())            ih = 18; 
      
      if (ih > 0) analysis->FillH1(ih,energy);

  }


}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

