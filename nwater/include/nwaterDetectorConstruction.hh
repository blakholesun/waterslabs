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
// $Id: nwaterDetectorConstruction.hh 69565 2013-05-08 12:35:31Z gcosmo $
//
/// \file nwaterDetectorConstruction.hh
/// \brief Definition of the nwaterDetectorConstruction class

#ifndef nwaterDetectorConstruction_h
#define nwaterDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
//class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class nwaterDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    nwaterDetectorConstruction();
    virtual ~nwaterDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSD();
    virtual void setCellFlux(G4String detector_name, 
                                  G4String current_name, G4int i);
    virtual G4String makeString(G4int i);

    const G4VPhysicalVolume* GetLayer1() const;
    const G4VPhysicalVolume* GetLayer2() const;
    const G4VPhysicalVolume* GetLayer3() const;

  private:
    G4VPhysicalVolume*  fScoringVolumeLayer1;
    G4VPhysicalVolume*  fScoringVolumeLayer2;
    G4VPhysicalVolume*  fScoringVolumeLayer3;

  // inline functions

};

  inline const G4VPhysicalVolume* nwaterDetectorConstruction::GetLayer1() const { 
    return fScoringVolumeLayer1; 
  }

  inline const G4VPhysicalVolume* nwaterDetectorConstruction::GetLayer2() const  { 
    return fScoringVolumeLayer2; 
  }

  inline const G4VPhysicalVolume* nwaterDetectorConstruction::GetLayer3() const  { 
    return fScoringVolumeLayer3; 
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

