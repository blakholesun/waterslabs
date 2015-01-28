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
// $Id: nwaterDetectorConstruction.cc 75117 2013-10-28 09:38:37Z gcosmo $
//
/// \file nwaterDetectorConstruction.cc
/// \brief Implementation of the nwaterDetectorConstruction class

#include "nwaterDetectorConstruction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSCellFlux.hh"
#include "G4SDParticleFilter.hh"
#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterDetectorConstruction::nwaterDetectorConstruction()
: G4VUserDetectorConstruction()

{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nwaterDetectorConstruction::~nwaterDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* nwaterDetectorConstruction::Construct()
{  
  // Get nist material manager
  //G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  // G4double env_sizeXY = 20*cm, env_sizeZ = 30*cm;
  // G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  // New element for thermal neutron transport
  //
  G4double density = 1.0*g/cm3;
  G4int ncomponents, natoms;
  G4Element* elTSHW = new G4Element( "TS_H_of_Water" , "H_WATER" , 1.0 , 1.0079*g/mole );
  G4Element* elO  = new G4Element("Oxygen"  ,"O" , 8.0, 16.00*g/mole);

  G4Material* matH2O_TS = new G4Material( "Water_TS" , density, ncomponents = 2 );
  matH2O_TS -> AddElement(elTSHW,natoms=2);
  matH2O_TS -> AddElement(elO,natoms=1); 
  // World
  //
  G4double world_sizeXYZ = 30*cm;
  G4double density2     = 1.e-25*g/cm3;                
  G4double pressure    = 1.e-19*pascal;
  G4double temperature = 0.1*kelvin;
  G4Material* world_mat = new G4Material("Galactic", 1., 1.008*g/mole, density2,
                   kStateGas,temperature,pressure);
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       world_sizeXYZ, world_sizeXYZ, world_sizeXYZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
 
  //     
  // Shape 1
  //  
  
  G4ThreeVector pos1 = G4ThreeVector(0, 0, 10*cm);
        
  // Cubic section shape       
  G4double shape1_xyz = 10*cm;
  G4Box* solidShape1 =    
    new G4Box("Shape1", 
    shape1_xyz, shape1_xyz, shape1_xyz);
                      
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        matH2O_TS,          //its material
                        "Shape1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  //
  // First layer at 5 cm
  //

  G4ThreeVector pos2 = G4ThreeVector(0, 0, -4.5*cm);
        
  // Plane section shape       
  G4double shape2_xyz = 10*cm;
  G4Box* solidLayer1 =    
    new G4Box("Layer1", 
    shape2_xyz, shape2_xyz, 0.05*shape2_xyz);
                      
  G4LogicalVolume* logicLayer1 =                         
    new G4LogicalVolume(solidLayer1,         //its solid
                        matH2O_TS,          //its material
                        "Layer1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicLayer1,             //its logical volume
                    "Layer1",                //its name
                    logicShape1,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  // Second layer at 10 cm
  //

  G4ThreeVector pos3 = G4ThreeVector(0, 0, 0);
        
  // Plane section shape       
  G4double shape3_xyz = 10*cm;
  G4Box* solidLayer2 =    
    new G4Box("Layer2", 
    shape3_xyz, shape3_xyz, 0.05*shape3_xyz);
                      
  G4LogicalVolume* logicLayer2 =                         
    new G4LogicalVolume(solidLayer2,         //its solid
                        matH2O_TS,          //its material
                        "Layer2");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos3,                    //at position
                    logicLayer2,             //its logical volume
                    "Layer2",                //its name
                    logicShape1,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
    // Second layer at 15 cm
  //

  G4ThreeVector pos4 = G4ThreeVector(0, 0, 4.5*cm);
        
  // Plane section shape       
  G4double shape4_xyz = 10*cm;
  G4Box* solidLayer3 =    
    new G4Box("Layer3", 
    shape4_xyz, shape4_xyz, 0.05*shape4_xyz);
                      
  G4LogicalVolume* logicLayer3 =                         
    new G4LogicalVolume(solidLayer3,         //its solid
                        matH2O_TS,          //its material
                        "Layer3");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos4,                    //at position
                    logicLayer3,             //its logical volume
                    "Layer3",                //its name
                    logicShape1,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  //
  //always return the physical World
  //

  ConstructSD();
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void nwaterDetectorConstruction::ConstructSD()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  // 
  //
  //
  /////////// declare layer 1 as a MultiFunctionalDetector scorer /////////
  //
  G4String detector_name = "Layer1";
  G4String current_name = "Flux_";
  setCellFlux(detector_name, current_name, 0);

  /////////// declare layer 2 as a MultiFunctionalDetector scorer //////////
  //  
  detector_name = "Layer2";
  current_name = "Flux_";
  setCellFlux(detector_name, current_name, 0);

  //////////// declare layer 3 as a MultiFunctionalDetector scorer//////////
  //  
  detector_name = "Layer3";
  current_name = "Flux_";
  setCellFlux(detector_name, current_name, 0);   
}

void nwaterDetectorConstruction::setCellFlux(G4String detector_name, 
                                                  G4String current_name, G4int i)
{
  // add an integer to passage current_name, no confusion

  G4SDParticleFilter* protonFilter1 =
    new G4SDParticleFilter("protonFilter", "proton");

  // -- electron filtering
  G4SDParticleFilter* electronFilter1 = 
    new G4SDParticleFilter("electronFilter","e-");
    
  // -- neutron filtering
  G4SDParticleFilter* neutronFilter1 = 
    new G4SDParticleFilter("neutronFilter","neutron");

  // -- gamma filtering 
  G4SDParticleFilter* gammaFilter1 = 
    new G4SDParticleFilter("gammaFilter","gamma");

  // -- Generic Ion filtering
  G4SDParticleFilter* genericionFilter1 = 
    new G4SDParticleFilter("genericionFilter","GenericIon");

  // -- alpha filtering
  G4SDParticleFilter* alphaFilter1 = 
    new G4SDParticleFilter("alphaFilter","alpha");

//////////////////////////////////////////////////////////////////////////

  G4MultiFunctionalDetector* layer3 
    = new G4MultiFunctionalDetector(detector_name);

  G4VPrimitiveScorer* primitive;
  primitive = new G4PSCellFlux(current_name + makeString(i+1));
  primitive->SetFilter(protonFilter1);
  layer3->RegisterPrimitive(primitive);

  // filter photon
  primitive = new G4PSCellFlux(current_name + makeString(i+2));
  primitive->SetFilter(gammaFilter1);
  layer3->RegisterPrimitive(primitive);

  // filter neutron
  primitive = new G4PSCellFlux(current_name + makeString(i+3));
  primitive->SetFilter(neutronFilter1);
  layer3->RegisterPrimitive(primitive);

  // filter electron
  primitive = new G4PSCellFlux(current_name + makeString(i+4));
  primitive->SetFilter(electronFilter1);
  layer3->RegisterPrimitive(primitive);

  // filter Generic Ion
  primitive = new G4PSCellFlux(current_name + makeString(i+5));
  primitive->SetFilter(genericionFilter1);
  layer3->RegisterPrimitive(primitive);

  // filter alpha
  primitive = new G4PSCellFlux(current_name + makeString(i+6));
  primitive->SetFilter(alphaFilter1);
  layer3->RegisterPrimitive(primitive);

  //G4SDManager::GetSDMpointer()->AddNewDetector(layer3);
  SetSensitiveDetector(detector_name,layer3); 
}

G4String nwaterDetectorConstruction::makeString(G4int i)
{
  std::ostringstream ss;
  ss << i;
  G4String test = ss.str();
  return test;
}
