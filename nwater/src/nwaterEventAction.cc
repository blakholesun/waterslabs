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
// $Id: nwaterEventAction.cc 75117 2013-10-28 09:38:37Z gcosmo $
//
/// \file nwaterEventAction.cc
/// \brief Implementation of the nwaterEventAction class

#include "nwaterEventAction.hh"
// #include "nwaterRun.hh"
#include "nwaterAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4VHit.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterEventAction::nwaterEventAction()
 :	G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterEventAction::~nwaterEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4THitsMap<G4double>* 
nwaterEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  G4THitsMap<G4double>* hitsCollection 
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4dEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double nwaterEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0;
  std::map<G4int, G4double*>::iterator it;
  for ( it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it ++) {
    sumValue += *(it->second);
  }
  return sumValue;  
}

G4String nwaterEventAction::makeString(G4int i)
{
  std::ostringstream ss;
  ss << i;
  G4String test = ss.str();
  return test;
}

void nwaterEventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nwaterEventAction::EndOfEventAction( const G4Event*) //event)
{

  // Layer hits collections filling histogram
  // Make into loop for elegance
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // G4String fullname;
  // G4double fluxes[3][6];
  // G4cout << "-------NEW EVENT------" << G4endl;
  // G4THitsMap<G4double>* hitsMap = GetHitsCollection(G4SDManager::GetSDMpointer()->GetCollectionID("Layer1/Flux_3"),event);
  // //hitsMap->PrintAllHits();
  // std::map<G4int, G4double*>::iterator it;
  //   for ( it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it ++) {
  //     G4cout << "Key: " << it->first << "   Value: " << *(it->second) << G4endl;
  //   }

  // for(int i = 0; i<3; i++){
  //   for(int j = 0; j<6; j++){

  //     fullname = "Layer" + makeString(i+1) + "/Flux_" + makeString(j+1);
  //     fluxes[i][j] = GetSum(GetHitsCollection
  //       (G4SDManager::GetSDMpointer()->GetCollectionID(fullname),event));
      // G4cout << fluxes[i][j] << G4endl;
      // analysisManager->FillH1(6*i+j+1, fluxes[i][j]);
  //   }
  // }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
