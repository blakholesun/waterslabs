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
  for ( it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it++) {
    sumValue += *(it->second);
  }
  return sumValue;  
}  

// void nwaterEventAction::RecordEvent(const G4Event* evt)
// {
//   G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
//   if(!HCE) return;
//   numberOfEvent++;
//   for(size_t i=0;i<6;i++)
//   {
//     for(size_t j=0;j<6;j++)
//     {
//       G4THitsMap<G4double>* evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(colIDSum[i][j]));
//       mapSum[i][j] += *evtMap;
//     }
//     for(size_t k=0;k<3;k++)
//     {
//       G4THitsMap<G4double>* evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(colIDMin[i][k]));
//       std::map<G4int,G4double*>::iterator itr = evtMap->GetMap()->begin();
//       for(; itr != evtMap->GetMap()->end(); itr++)
//       {
//         G4int key = (itr->first);
//         G4double val = *(itr->second);
//         G4double* mapP = mapMin[i][k][key];
//         if( mapP && (val>*mapP) ) continue;
//         mapMin[i][k].set(key,val);
//       }
//     }
//   }
// }

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

void nwaterEventAction::EndOfEventAction( const G4Event*)
{

  G4String detName[3] = {"Layer1","Layer2","Layer3"};
  G4String primName[3][6];
  for (size_t j=0;j<3;j++)
  {
    for(size_t i=0;i<6;i++)
      {
      primName[j][i] = "Current_" + makeString(i+1);
      }
  }

// get all collection ids from the SD manager

  G4SDManager* SDMan = G4SDManager::GetSDMpointer();
  G4String fullName;
  G4int colIDSum[3][6];
  for(size_t i=0;i<3;i++)
  {
    for(size_t j=0;j<6;j++)
    {
      fullName = detName[i]+"/"+primName[i][j];
      colIDSum[i][j] = SDMan->GetCollectionID(fullName);
    }
  }   

  // // get analysis manager
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  // // fill ntuple with hit collections of each event and passage current
  // //
  // for (size_t i=0;i<3;i++)
  // {
  //   for(size_t j=0;j<6;j++)
  //   {
  //       analysisManager->FillNtupleDColumn(i*6 + j, 
  //               GetSum(GetHitsCollection(colIDSum[i][j], event)));
  //   }
  // }

  // analysisManager->AddNtupleRow();  
  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
