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
// $Id: nwaterEventAction.hh 75216 2013-10-29 16:08:11Z gcosmo $
//
/// \file nwaterEventAction.hh
/// \brief Definition of the nwaterEventAction class

#ifndef nwaterEventAction_h
#define nwaterEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4THitsMap.hh"
#include "globals.hh"

/// Event action class
///

class nwaterEventAction : public G4UserEventAction
{
  public:
    nwaterEventAction();
    virtual ~nwaterEventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    //void AddEdep(G4double edep) { fEdep += edep; }

  private:
    // methods
  G4THitsMap<G4double>* GetHitsCollection(G4int hcID,
                                          const G4Event* event) const;
  G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
  //void PrintEventStatistics(G4double layer1current, G4double layer2current,
  //							G4double layer3current) const;
  G4String makeString(G4int i);
  
  void RecordEvent(const G4Event* evt);

  // // data members                   
  // G4int  flayer1currentHCID;
  // G4int  flayer2currentHCID;
  // G4int  flayer3currentHCID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
