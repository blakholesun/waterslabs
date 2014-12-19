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
#include "Run.hh"
// #include "nwaterRun.hh"

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterRunAction::nwaterRunAction()
: G4UserRunAction()
  // flayer1currentHCID(-1),
  // flayer2currentHCID(-1),
  // flayer3currentHCID(-1)
{ 
  // // add new units for dose
  // // 
  // const G4double milligray = 1.e-3*gray;
  // const G4double microgray = 1.e-6*gray;
  // const G4double nanogray  = 1.e-9*gray;  
  // const G4double picogray  = 1.e-12*gray;
   
  // new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  // new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  // new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  // new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);

  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B4Analysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);

  // Book histograms, ntuple
  //
  
  //Creating histograms
  // analysisManager->CreateH1("1","Layer 1 Current", 1, 0., 20*MeV);
  // analysisManager->CreateH1("2","Layer 2 Current", 1, 0., 20*MeV);
  // analysisManager->CreateH1("3","Layer 3 Current", 1, 0., 20*MeV);

  // Creating ntuple
  //
  analysisManager->CreateNtuple("nwater", "Current");
  analysisManager->CreateNtupleDColumn("Layer1Curr");
  // analysisManager->CreateNtupleDColumn("Layer2Curr");
  // analysisManager->CreateNtupleDColumn("Layer3Curr");
  analysisManager->FinishNtuple();  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterRunAction::~nwaterRunAction()
{
    delete G4AnalysisManager::Instance();   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// G4Run* nwaterRunAction::GenerateRun()
// {
//   return new nwaterRun; 
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nwaterRunAction::BeginOfRunAction(const G4Run*)
{ 
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "nwaterout";
  analysisManager->OpenFile(fileName);
}

void nwaterRunAction::EndOfRunAction(const G4Run* run)
{

  // G4int NbofEvents = run->GetNumberOfEvent();
  // if (NbofEvents == 0) return;
  // CLHEP::HepRandom::showEngineStatus();  

  const G4HCtable* total = run->GetHCtable();

  G4cout << "+++++++++++++++++++++++++++++++++++++++++   " << total->GetHCname(2) 
    << "   +++++++++++++++++++++++++++++++++" << G4endl;
  G4cout << "+++++++++++++++++++++++++++++++++++++++++   " << total->entries() 
    << "   +++++++++++++++++++++++++++++++++" << G4endl;
  // G4SDManager* SDMan = G4SDManager::GetSDMpointer();
  // G4int layer1proton = SDMan->GetCollectionID(total->GetHCname(0));

  // // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
