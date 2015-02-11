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
// $Id: nwaterActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file nwaterActionInitialization.cc
/// \brief Implementation of the nwaterActionInitialization class

#include "nwaterActionInitialization.hh"
#include "nwaterPrimaryGeneratorAction.hh"
#include "nwaterRunAction.hh"
#include "nwaterEventAction.hh"
#include "nwaterSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterActionInitialization::nwaterActionInitialization(
	nwaterDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
 fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterActionInitialization::~nwaterActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nwaterActionInitialization::BuildForMaster() const
{
  SetUserAction(new nwaterRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nwaterActionInitialization::Build() const
{
  SetUserAction(new nwaterPrimaryGeneratorAction);
  SetUserAction(new nwaterRunAction);
  SetUserAction(new nwaterEventAction);
  SetUserAction(new nwaterSteppingAction(fDetConstruction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
