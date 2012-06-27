#define MyAnalyzer_cxx
// The class definition in MyAnalyzer.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("MyAnalyzer.C")
// Root > T->Process("MyAnalyzer.C","some options")
// Root > T->Process("MyAnalyzer.C+")
//

#include "MyAnalyzer.h"
#include <TStyle.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

void MyAnalyzer::Init1DHisto(TString name, int nBin, double min, double max) {
	Bool_t s = TH1::AddDirectoryStatus();
	TH1::AddDirectory(kFALSE);
	TH1F* histo = new TH1F(name, name, nBin, min, max);
	histo->Sumw2();
	histoList->Add(histo);
	TH1::AddDirectory(s);
}

void MyAnalyzer::Fill1DHisto(TString name, double value) {
	TH1F* actual_histo;
	actual_histo = (TH1F*) histoList->FindObject(name);
	if(actual_histo)
	{
		if(value>actual_histo->GetXaxis()->GetXmax()){value = actual_histo->GetXaxis()->GetXmax()-0.00001;}
		if(value<actual_histo->GetXaxis()->GetXmin()){value = actual_histo->GetXaxis()->GetXmin()+0.00001;}
		actual_histo->Fill(value, weight);
	}
}

double MyAnalyzer::GetSampleWeight()
{
	double scale=0;
	double NoE;
	double CS=0;
	double lumi=1.0;
	
	if(nick=="15to30")
	{
		NoE=1070600;
		CS=957000000.0;
	}
	if(nick=="30to50")
	{
		NoE=1102288;
		CS=61000000.0;
	}
	if(nick=="50to80")
	{
		NoE=1108386;
		CS=7220000.0;
	}
	if(nick=="80to120")
	{
		NoE=1083808;
		CS=883000.0;
	}
	if(nick=="120to170")
	{
		NoE=849640;
		CS=129000.0;
	}
	if(nick=="170to300")
	{
		NoE=855265;
		CS=27000.0;
	}
	if(nick=="300to470")
	{
		NoE=531232;
		CS=1290.0;
	}
	if(nick=="470to600")
	{
		NoE=525214;
		CS=77.0;
	}
	if(nick=="600to800")
	{
		NoE=516681;
		CS=17.0;
	}
	if(nick=="800to1000")
	{
		NoE=423624;
		CS=2.01;
	}
	if(nick=="1000to1400")
	{
		NoE=403919;
		CS=0.361;
	}
	if(nick=="1400to1800")
	{
		NoE=213376;
		CS=0.0118;
	}
	if(nick=="1800")
	{
		NoE=218323;
		CS=0.000387;
	}
	if(CS==0){cout<<"WARNING! Weight not found, false weight is obviously applied, leading to dramatic consequences."<<endl;}
	
	scale=lumi*CS/NoE;
	return scale;
}

void MyAnalyzer::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	category = getenv("CAT");
	flavor = getenv("FLAV");
	nick = getenv("DATASETNICK");
	
	cout<<"Initializing the "<<category<<" category in "<<flavor<<" flavor."<<endl;
	
	weight = GetSampleWeight();
	
	string filename="Histos_"+category+"_"+flavor+"_"+nick+".root";
	f = new TFile(filename.c_str(),"RECREATE");

	histoList = new TList();

	//Initialize histos with following name: {variable}_{VertexCategory}_{JetFlavor}

	etamin.push_back(0);
	etamin.push_back(0);
	etamin.push_back(1.4);
	
	etamax.push_back(3);
	etamax.push_back(1.4);
	etamax.push_back(2.4);
	
	etabin.push_back("");
	etabin.push_back("_eta0to1p4");
	etabin.push_back("_eta1p4to2p4");
	
	for(unsigned int i=0;i<etamin.size();i++)
	{
		Init1DHisto("jetPt_"+category+"_"+flavor+etabin.at(i),100,0,2000);
		Init1DHisto("jetEta_"+category+"_"+flavor+etabin.at(i),100,-3,3);
		Init1DHisto("trackMomentum_"+category+"_"+flavor+etabin.at(i),100,0,1000);
		Init1DHisto("trackEta_"+category+"_"+flavor+etabin.at(i),100,-3,3);
		Init1DHisto("trackPtRel_"+category+"_"+flavor+etabin.at(i),100,0,200);
		Init1DHisto("trackPPar_"+category+"_"+flavor+etabin.at(i),100,0,1000);
		Init1DHisto("trackDeltaR_"+category+"_"+flavor+etabin.at(i),100,0,0.35);
		Init1DHisto("trackPtRatio_"+category+"_"+flavor+etabin.at(i),100,0,0.4);
		Init1DHisto("trackPParRatio_"+category+"_"+flavor+etabin.at(i),100,0.95,1.01);
		Init1DHisto("trackJetDist_"+category+"_"+flavor+etabin.at(i),200,-0.075,0.075);
		Init1DHisto("trackMultiplicity_"+category+"_"+flavor+etabin.at(i),50,0,50);
		Init1DHisto("trackFirstTrackDist_"+category+"_"+flavor+etabin.at(i),100,0,5);
		Init1DHisto("trackDecayLenVal_"+category+"_"+flavor+etabin.at(i),100,0,5.5);
		Init1DHisto("trackDecayLenSig_"+category+"_"+flavor+etabin.at(i),100,0,500);
		Init1DHisto("trackDecayLenSigTEST_"+category+"_"+flavor+etabin.at(i),100,0,0.02);
		Init1DHisto("trackSumJetEtRatio_"+category+"_"+flavor+etabin.at(i),100,0,3);
		Init1DHisto("trackSumJetDeltaR_"+category+"_"+flavor+etabin.at(i),100,0,2);
		Init1DHisto("trackSip2dSig_"+category+"_"+flavor+etabin.at(i),100,-100,100);
		Init1DHisto("trackSip3dSig_1stTrk_"+category+"_"+flavor+etabin.at(i),100,-100,100);
		Init1DHisto("trackSip3dSig_2ndTrk_"+category+"_"+flavor+etabin.at(i),100,-100,100);
		Init1DHisto("trackSip3dSig_3rdTrk_"+category+"_"+flavor+etabin.at(i),100,-100,100);
		Init1DHisto("trackSip3dSig_restTrk_"+category+"_"+flavor+etabin.at(i),100,-100,100);
		Init1DHisto("trackSip3dSig_"+category+"_"+flavor+etabin.at(i),100,-100,100);
		Init1DHisto("trackSip2dVal_"+category+"_"+flavor+etabin.at(i),100,-0.6,0.6);
		Init1DHisto("trackSip3dVal_"+category+"_"+flavor+etabin.at(i),100,-0.6,0.6);
		Init1DHisto("trackEtaRel_"+category+"_"+flavor+etabin.at(i),100,1,8);
		Init1DHisto("trackSip2dSigAboveCharm_"+category+"_"+flavor+etabin.at(i),100,-50,50);
		Init1DHisto("trackSip3dSigAboveCharm_"+category+"_"+flavor+etabin.at(i),100,-50,50);
		Init1DHisto("vertexMass_"+category+"_"+flavor+etabin.at(i),100,0,200);
		Init1DHisto("vertexNTracks_"+category+"_"+flavor+etabin.at(i),17,1,18);
		Init1DHisto("vertexEnergyRatio_"+category+"_"+flavor+etabin.at(i),100,0,15);
		Init1DHisto("vertexJetDeltaR_"+category+"_"+flavor+etabin.at(i),100,0,0.55);
		Init1DHisto("jetNSecondaryVertices_"+category+"_"+flavor+etabin.at(i),6,0,6);
		Init1DHisto("flightDistance2dSig_"+category+"_"+flavor+etabin.at(i),100,0,200);
		Init1DHisto("flightDistance3dSig_"+category+"_"+flavor+etabin.at(i),100,0,200);
		Init1DHisto("flightDistance2dVal_"+category+"_"+flavor+etabin.at(i),100,0,2.6);
		Init1DHisto("flightDistance3dVal_"+category+"_"+flavor+etabin.at(i),100,0,10);
	}
}

void MyAnalyzer::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
}

Bool_t MyAnalyzer::Process(Long64_t entry)
{
	// The Process() function is called for each entry in the tree (or possibly
	// keyed object in the case of PROOF) to be processed. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	// It can be passed to either MyAnalyzer::GetEntry() or TBranch::GetEntry()
	// to read either all or the required parts of the data. When processing
	// keyed objects with PROOF, the object is already loaded and is available
	// via the fObject pointer.
	//
	// This function should contain the "body" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	//
	// Use fStatus to set the return value of TTree::Process().
	//
	// The return value is currently not used.
	MyAnalyzer::GetEntry( entry );

	for(unsigned int i=0;i<etamin.size();i++)
	{
		if((fabs(jetEta)<etamax.at(i))&&(fabs(jetEta)>=etamin.at(i))){
			Fill1DHisto("jetPt_"+category+"_"+flavor+etabin.at(i),jetPt);
			Fill1DHisto("jetEta_"+category+"_"+flavor+etabin.at(i),jetEta);

			for(unsigned j=0;j<trackMomentum->size();j++)
			{
				Fill1DHisto("trackSip2dSig_"+category+"_"+flavor+etabin.at(i),trackSip2dSig->at(j));
				Fill1DHisto("trackSip3dSig_"+category+"_"+flavor+etabin.at(i),trackSip3dSig->at(j));
				Fill1DHisto("trackSip2dVal_"+category+"_"+flavor+etabin.at(i),trackSip2dVal->at(j));
				Fill1DHisto("trackSip3dVal_"+category+"_"+flavor+etabin.at(i),trackSip3dVal->at(j));
				Fill1DHisto("trackMomentum_"+category+"_"+flavor+etabin.at(i),trackMomentum->at(j));
				Fill1DHisto("trackDeltaR_"+category+"_"+flavor+etabin.at(i),trackDeltaR->at(j));
				Fill1DHisto("trackDecayLenVal_"+category+"_"+flavor+etabin.at(i),trackDecayLenVal->at(j));
				Fill1DHisto("trackDecayLenSig_"+category+"_"+flavor+etabin.at(i),trackDecayLenSig->at(j));
				Fill1DHisto("trackDecayLenSigTEST_"+category+"_"+flavor+etabin.at(i),trackDecayLenSigTEST->at(j));
				Fill1DHisto("trackEta_"+category+"_"+flavor+etabin.at(i),trackEta->at(j));
				Fill1DHisto("trackPtRel_"+category+"_"+flavor+etabin.at(i),trackPtRel->at(j));
				Fill1DHisto("trackPPar_"+category+"_"+flavor+etabin.at(i),trackPPar->at(j));
				Fill1DHisto("trackPtRatio_"+category+"_"+flavor+etabin.at(i),trackPtRatio->at(j));
				Fill1DHisto("trackPParRatio_"+category+"_"+flavor+etabin.at(i),trackPParRatio->at(j));
				Fill1DHisto("trackJetDist_"+category+"_"+flavor+etabin.at(i),trackJetDist->at(j));
				//Fill1DHisto("trackFirstTrackDist_"+category+"_"+flavor+etabin.at(i),trackFirstTrackDist->at(j));
			}
			
			double IPMAX=-999999999.9;
			unsigned MAXID=0;
			unsigned MAX2ID=0;
			unsigned MAX3ID=0;
			for(unsigned j=0;j<trackMomentum->size();j++)
			{
				if(trackSip3dSig->at(j)>IPMAX)
				{
					IPMAX=trackSip3dSig->at(j);
					MAXID=j;
				}
			}
			IPMAX=-999999999.9;
			for(unsigned j=0;j<trackMomentum->size();j++)
			{
				if((trackSip3dSig->at(j)>IPMAX)&&(j!=MAXID))
				{
					IPMAX=trackSip3dSig->at(j);
					MAX2ID=j;
				}
			}
			IPMAX=-999999999.9;
			for(unsigned j=0;j<trackMomentum->size();j++)
			{
				if((trackSip3dSig->at(j)>IPMAX)&&(j!=MAXID)&&(j!=MAX2ID))
				{
					IPMAX=trackSip3dSig->at(j);
					MAX3ID=j;
				}
			}
			if(trackMomentum->size()>0){Fill1DHisto("trackSip3dSig_1stTrk_"+category+"_"+flavor+etabin.at(i),trackSip3dSig->at(MAXID));}
			if(trackMomentum->size()>1){Fill1DHisto("trackSip3dSig_2ndTrk_"+category+"_"+flavor+etabin.at(i),trackSip3dSig->at(MAX2ID));}
			if(trackMomentum->size()>2){Fill1DHisto("trackSip3dSig_3rdTrk_"+category+"_"+flavor+etabin.at(i),trackSip3dSig->at(MAX3ID));}
			
			for(unsigned j=0;j<trackMomentum->size();j++)
			{
				if((j!=MAXID)&&(j!=MAX2ID)&&(j!=MAX3ID)&&(trackMomentum->size()>3))
				{
					Fill1DHisto("trackSip3dSig_restTrk_"+category+"_"+flavor+etabin.at(i),IPMAX);
				}
			}
			
			Fill1DHisto("trackMultiplicity_"+category+"_"+flavor+etabin.at(i),trackMomentum->size());
			for(unsigned j=0;j<trackEtaRel->size();j++)
			{
				Fill1DHisto("trackEtaRel_"+category+"_"+flavor+etabin.at(i),trackEtaRel->at(j));
			}
			Fill1DHisto("trackSip2dSigAboveCharm_"+category+"_"+flavor+etabin.at(i),trackSip2dSigAboveCharm);
			Fill1DHisto("trackSip3dSigAboveCharm_"+category+"_"+flavor+etabin.at(i),trackSip3dSigAboveCharm);
			Fill1DHisto("trackSumJetEtRatio_"+category+"_"+flavor+etabin.at(i),trackSumJetEtRatio);
			Fill1DHisto("trackSumJetDeltaR_"+category+"_"+flavor+etabin.at(i),trackSumJetDeltaR);

			if(category=="Reco")
			{
				Fill1DHisto("flightDistance2dSig_"+category+"_"+flavor+etabin.at(i),flightDistance2dSig);
				Fill1DHisto("flightDistance3dSig_"+category+"_"+flavor+etabin.at(i),flightDistance3dSig);
				Fill1DHisto("flightDistance2dVal_"+category+"_"+flavor+etabin.at(i),flightDistance2dVal);
				Fill1DHisto("flightDistance3dVal_"+category+"_"+flavor+etabin.at(i),flightDistance3dVal);
				Fill1DHisto("jetNSecondaryVertices_"+category+"_"+flavor+etabin.at(i),jetNSecondaryVertices);
			}
			if((category=="Reco")||(category=="Pseudo"))
			{
				Fill1DHisto("vertexMass_"+category+"_"+flavor+etabin.at(i),vertexMass);
				Fill1DHisto("vertexNTracks_"+category+"_"+flavor+etabin.at(i),vertexNTracks);
				Fill1DHisto("vertexEnergyRatio_"+category+"_"+flavor+etabin.at(i),vertexEnergyRatio);
				Fill1DHisto("vertexJetDeltaR_"+category+"_"+flavor+etabin.at(i),vertexJetDeltaR);
			}
		}
	}


	return kTRUE;
}

void MyAnalyzer::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.
}

void MyAnalyzer::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.

	cout<<"Storing"<<endl;
	histoList->Write();
	f->Close();
}
