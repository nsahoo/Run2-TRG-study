// -*- C++ -*-
//
// Package:    BphTRG/HLTEffAnalyzer
// Class:      HLTEffAnalyzer
// 
/**\class HLTEffAnalyzer HLTEffAnalyzer.cc BphTRG/HLTEffAnalyzer/plugins/HLTEffAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Niladribihari Sahoo
//         Created:  Thu, 14 May 2015 21:54:13 GMT
//
//


// system include files
#include <memory>
#include <fstream>
#include <sys/time.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TH1.h>

#include "TCanvas.h"
#include "TStyle.h"


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

using namespace std;
using namespace edm;

//
// class declaration
//

class HLTEffAnalyzer : public edm::EDAnalyzer {
   public:
      explicit HLTEffAnalyzer(const edm::ParameterSet&);
      ~HLTEffAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  edm::EDGetTokenT<pat::MuonCollection> muonToken_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HLTEffAnalyzer::HLTEffAnalyzer(const edm::ParameterSet& iConfig):
  vtxToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
  muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons")))

{
   //now do what ever initialization is needed

}


HLTEffAnalyzer::~HLTEffAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
HLTEffAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(vtxToken_, vertices);
  if (vertices->empty()) return; // skip the event if no PV found                                                                                            
                  
  const reco::Vertex &PV = vertices->front();


  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByToken(muonToken_, muons);
  for (const pat::Muon &mu : *muons) {
    if (mu.pt() < 5 || !mu.isLooseMuon()) continue;
    printf("muon with pt %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d\n",
           mu.pt(), mu.muonBestTrack()->dz(PV.position()), mu.isLooseMuon(), mu.isTightMuon(PV));
  }


}


// ------------ method called once each job just before starting event loop  ------------
void 
HLTEffAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HLTEffAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
HLTEffAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
HLTEffAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
HLTEffAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
HLTEffAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HLTEffAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HLTEffAnalyzer);
