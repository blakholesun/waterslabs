#include "nwaterRun.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"

nwaterRun::nwaterRun()
{
  G4String detName[3] = {"Layer1","Layer2","Layer3"};
  G4SDManager* SDMan = G4SDManager::GetSDMpointer();
  G4String fullName;

  for (size_t j=0;j<3;j++)
  {
    for(size_t i=0;i<6;i++)
      {
      theCollName.push_back(detName[j]+"/Current_" + makeString(i+1));
      theCollID.push_back(SDMan->GetCollectionID(fullName));
      theRunMap.push_back(new G4THitsMap<G4double>(detName[j],
                          "/Current_" + makeString(i+1)));
      }
  }
}

//
// Destructor
//    clear all data members.
Run::~Run()
{
  //--- Clear HitsMap for RUN
  G4int Nmap = theRunMap.size();
  for ( G4int i = 0; i < Nmap; i++){
    if(theRunMap[i] ) theRunMap[i]->clear();
  }
  theCollName.clear();
  theCollID.clear();
  theRunMap.clear();
}

//
//  RecordEvent is called at end of event.
//  For scoring purpose, the resultant quantity in a event,
//  is accumulated during a Run.
void Run::RecordEvent(const G4Event* aEvent)
{
  numberOfEvent++;  // This is an original line.

  //=============================
  // HitsCollection of This Event
  //============================
  G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
  if (!HCE) return;

  //=======================================================
  // Sum up HitsMap of this Event  into HitsMap of this RUN
  //=======================================================
  G4int Ncol = theCollID.size();
  for ( G4int i = 0; i < Ncol ; i++ ){  // Loop over HitsCollection
    G4THitsMap<G4double>* EvtMap=0;
    if ( theCollID[i] >= 0 ){           // Collection is attached to HCE
      EvtMap = (G4THitsMap<G4double>*)(HCE->GetHC(theCollID[i]));
    }else{
      G4cout <<" Error EvtMap Not Found "<< i << G4endl;
    }
    if ( EvtMap )  {
      //=== Sum up HitsMap of this event to HitsMap of RUN.===
      *theRunMap[i] += *EvtMap;
      //======================================================
    }
  }
}

//=================================================================
//  Access method for HitsMap of the RUN
//
//-----
// Access HitsMap.
//  By  MultiFunctionalDetector name and Collection Name.
G4THitsMap<G4double>* Run::GetHitsMap(const G4String& detName,
					 const G4String& colName){
    G4String fullName = detName+"/"+colName;
    return GetHitsMap(fullName);
}

//-----
// Access HitsMap.
//  By full description of collection name, that is
//    <MultiFunctional Detector Name>/<Primitive Scorer Name>
G4THitsMap<G4double>* Run::GetHitsMap(const G4String& fullName){
    G4int Ncol = theCollName.size();
    for ( G4int i = 0; i < Ncol; i++){
	if ( theCollName[i] == fullName ){
	    return theRunMap[i];
	}
    }
    return NULL;
}

//-----
// - Dump All HitsMap of this RUN. (for debuging and monitoring of quantity).
//   This method calls G4THisMap::PrintAll() for individual HitsMap.
void Run::DumpAllScorer(){

  // - Number of HitsMap in this RUN.
  G4int n = GetNumberOfHitsMap();
  // - GetHitsMap and dump values.
  for ( G4int i = 0; i < n ; i++ ){
    G4THitsMap<G4double>* RunMap =GetHitsMap(i);
    if ( RunMap ) {
      G4cout << " PrimitiveScorer RUN " 
	     << RunMap->GetSDname() <<","<< RunMap->GetName() << G4endl;
      G4cout << " Number of entries " << RunMap->entries() << G4endl;
      std::map<G4int,G4double*>::iterator itr = RunMap->GetMap()->begin();
      for(; itr != RunMap->GetMap()->end(); itr++) {
	G4cout << "  copy no.: " << itr->first
	       << "  Run Value : " << *(itr->second) 
	       << G4endl;
      }
    }
  }
}


