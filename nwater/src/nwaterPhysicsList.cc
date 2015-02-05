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
// $Id: PhysicsList.cc 83413 2014-08-21 15:21:43Z gcosmo $
//
//---------------------------------------------------------------------------
//
// ClassName:   
//
// Author: 2010 Tatsumi Koi, Gunter Folger
//
//   created from FTFP_BERT
//
// Modified:
// 05.08.2014 K.L.Genser: added provision for Hadronic Physics Variant M
// 16.08.2010 H.Kurashige: Remove inclusion of G4ParticleWithCuts 
// 26.04.2011 T.Koi: Add G4RadioactiveDecayPhysics
// 16.10.2012 A.Ribon: Use new default stopping
// 07.11.2013 T.Koi: Add IonElasticPhysics, Set proton cut to 0 to generate
//                   low energy recoils and activate production of fission
//                   fragments 
//
//----------------------------------------------------------------------------
//

#include "nwaterPhysicsList.hh"

#include <iomanip>   

#include "globals.hh"
#include "G4ios.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmProcessOptions.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonQMDPhysics.hh"
#include "G4IonElasticPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronElasticPhysicsLEND.hh"
#include "G4HadronElasticProcess.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronHPThermalScatteringData.hh"
#include "G4NeutronHPThermalScattering.hh"
#include "G4NeutronHPElastic.hh"
#include "G4VPhysicsConstructor.hh"

#include "G4DataQuestionaire.hh"
#include "G4HadronPhysicsShielding.hh"

nwaterPhysicsList::nwaterPhysicsList(): G4VModularPhysicsList()
{
  G4int verbose = 1;
  // default cut value  (1.0mm) 
  // defaultCutValue = 1.0*CLHEP::mm;
  G4DataQuestionaire it(photon, neutron, radioactive, lowenergy);
  G4cout << "<<< Geant4 User Physics List simulation engine based on Shielding 2.1 "
         <<G4endl;
  G4cout <<G4endl;
  this->defaultCutValue = 0.*CLHEP::mm;  
  this->SetVerboseLevel(verbose);

 // EM Physics
  this->RegisterPhysics( new G4EmStandardPhysics(verbose));
  //G4EmProcessOptions emOptions;
  //emOptions.SetFluo(true); // To activate deexcitation processes and fluorescence
  //emOptions.SetAuger(true); // To activate Auger effect if deexcitation is activated
  //emOptions.SetPIXE(true); // To activate Particle Induced X-Ray Emission (PIXE)   

  // Synchroton Radiation & GN Physics
  this->RegisterPhysics( new G4EmExtraPhysics(verbose) );

  // Decays 
  this->RegisterPhysics( new G4DecayPhysics(verbose) );
  //if ( rad == true ) this->RegisterPhysics( new G4RadioactiveDecayPhysics(verbose) );
  this->RegisterPhysics( new G4RadioactiveDecayPhysics(verbose) );

  //elastic physics
  this->RegisterPhysics( new G4HadronElasticPhysicsHP(verbose) );
  
  //Activate prodcuton of fission fragments in neutronHP
  char env_ff[]="G4NEUTRONHP_PRODUCE_FISSION_FRAGMENTS=1";
  putenv(env_ff);
  
  // Stopping Physics
  this->RegisterPhysics( new G4StoppingPhysics(verbose));

  // Ion Physics
  this->RegisterPhysics( new G4IonQMDPhysics(verbose));
  
  this->RegisterPhysics( new G4IonElasticPhysics(verbose));

  // Register inelastic
  this->RegisterPhysics(new G4HadronPhysicsShielding(verbose));

  // Neutron tracking cut --> not by default
  // this->RegisterPhysics( new G4NeutronTrackingCut(verbose));

}

nwaterPhysicsList::~nwaterPhysicsList()
{
}

void nwaterPhysicsList::ConstructProcess()
{
  G4VModularPhysicsList::ConstructProcess();
  //
  
  // FOR NEUTRON TRANSPORT AT LOW ENERGIES

  G4HadronElasticProcess* theNeutronElasticProcess = new G4HadronElasticProcess();

  // Cross Section Data set 

  G4NeutronHPElasticData* theHPElasticData = new G4NeutronHPElasticData(); 
  theNeutronElasticProcess->AddDataSet( theHPElasticData ); 
  G4NeutronHPThermalScatteringData* theHPThermalScatteringData = 
    new G4NeutronHPThermalScatteringData(); 
  theNeutronElasticProcess->AddDataSet( theHPThermalScatteringData ); 

  // Models 

  G4NeutronHPElastic* theNeutronElasticModel = new G4NeutronHPElastic(); 
  theNeutronElasticModel->SetMinEnergy ( 4.0*eV ); 
  theNeutronElasticProcess->RegisterMe(theNeutronElasticModel); 
  G4NeutronHPThermalScattering* theNeutronThermalElasticModel = 
  new G4NeutronHPThermalScattering(); 
  theNeutronThermalElasticModel->SetMaxEnergy ( 4.0*eV ); 
  theNeutronElasticProcess->RegisterMe(theNeutronThermalElasticModel); 

  // Apply Processes to Process Manager of Neutron 

  //G4ProcessManager* pmanager = G4Neutron::Neutron()-> GetProcessManager();
  //pmanager->AddDiscreteProcess( theNeutronElasticProcess );

}

void nwaterPhysicsList::SetCuts()
{
  if (this->verboseLevel >1){
    G4cout << "Shielding::SetCuts:";
  }  
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
  //   the default cut value for all particle types 

  //this->SetCutsWithDefault();   

  //Set proton cut value to 0 for producing low energy recoil nucleus 
  //this->SetCutValue(0, "proton");    
 
//  if (this->verboseLevel > 0)
//    G4VUserPhysicsList::DumpCutValuesTable();  
}
