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
// $Id: nwaterRunAction.cc 75216 2013-10-29 16:08:11Z gcosmo $
//
/// \file nwaterRunAction.cc
/// \brief Implementation of the nwaterRunAction class

#include "nwaterRunAction.hh"
#include "nwaterPrimaryGeneratorAction.hh"
#include "nwaterDetectorConstruction.hh"
#include "nwaterAnalysis.hh"
#include "nwaterRun.hh"

#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4THitsMap.hh"
#include "G4HCtable.hh"
#include "G4Run.hh"
#include <iostream>
using namespace std;
#include "CLHEP/Random/Random.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterRunAction::nwaterRunAction()
: G4UserRunAction()
{ 
  G4RunManager::GetRunManager()->SetPrintProgress(1);     

  // Create analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);

  G4String titles[6] = {"Proton Spectrum ", "Gamma Spectrum ", "Primary Neutron Spectrum ",
                        "Electron Spectrum ", "Deuteron Spectrum ", "Alpha Spectrum"};


  // Creating histograms
  for(int i = 0; i < 3; i ++){
    for(int j = 0; j < 6; j++){

      analysisManager->CreateH1(makeString(6*i+j+1), // ids
        titles[j] + makeString(5*i+5) + " cm", // Spectrum titles
        200, 0.0000001, 15*MeV,"none", "none","log"); // #bins, start, stop, ~~, scale

    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterRunAction::~nwaterRunAction()
{
  delete G4AnalysisManager::Instance();   
}

G4String nwaterRunAction::makeString(G4int i)
{
  std::ostringstream ss;
  ss << i;
  G4String test = ss.str();
  return test;
}

G4Run* nwaterRunAction::GenerateRun()
{ return new nwaterRun; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// G4Run* nwaterRunAction::GenerateRun()
// {
//   return new nwaterRun; 
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nwaterRunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  if(G4VVisManager::GetConcreteInstance()) {
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/vis/scene/notifyHandlers");
  }
  CLHEP::HepRandom::showEngineStatus();

  total_events = aRun->GetNumberOfEventToBeProcessed();

  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  // Open an output file
  analysisManager->OpenFile("nwater");

}

void nwaterRunAction::EndOfRunAction(const G4Run* aRun)
{
  // Save histograms
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4double normalization = (G4double)total_events;
  for (int i = 0; i<18; i++){
    analysisManager->ScaleH1(i+1, 1/normalization);
  }

  analysisManager->Write();
  analysisManager->CloseFile();

  G4int NbofEvents = aRun->GetNumberOfEvent();
  if (NbofEvents == 0) return;
  CLHEP::HepRandom::showEngineStatus();

  nwaterRun* theRun = (nwaterRun*)aRun;
  
  G4cout << G4endl << " --------- Tallies ---------" << G4endl << G4endl;

  G4cout << " 5 cm depth in water : Layer1 " << G4endl;
  G4cout << " 10 cm depth in water : Layer2 " << G4endl;
  G4cout << " 15 cm depth in water : Layer3 " << G4endl << G4endl;

  G4cout << " Flux_1 : Proton " << G4endl;
  G4cout << " Flux_2 : Gamma " << G4endl;
  G4cout << " Flux_3 : Neutron " << G4endl;
  G4cout << " Flux_4 : Electron " << G4endl;
  G4cout << " Flux_5 : Deuteron " << G4endl;
  G4cout << " Flux_6 : Alpha " << G4endl << G4endl;

  theRun->DumpAllScorer(total_events);
  //theRun->DumpAllScorer();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
