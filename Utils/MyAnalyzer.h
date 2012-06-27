//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr  3 15:52:48 2012 by ROOT version 5.27/06b
// from TTree CombinedSVRecoVertex/CombinedSVRecoVertex_B
// found on file: /storage/9/descroix/OldTrainingFramework/CombinedSVRecoVertex_B.root
//////////////////////////////////////////////////////////

#ifndef MyAnalyzer_h
#define MyAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TH1.h>
#include <TSelector.h>
#include <vector>
#include <string>
#include <iostream>

class MyAnalyzer : public TSelector {
public :
   
   TFile* f;
   TList* histoList;
   
   string category;
   string flavor;
   string nick;
   
   vector<double> etamin;
   vector<double> etamax;
   vector<string> etabin;
   
   double weight;
   
   Long64_t lightJetPrescale;
   
   template<typename T>
   T getEnv(const std::string & varname);
   
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           flavour;
   Double_t        jetPt;
   Double_t        jetEta;
   Int_t           vertexCategory;
   vector<double>  *trackSip2dSig;
   vector<double>  *trackSip3dSig;
   vector<double>  *trackSip2dVal;
   vector<double>  *trackSip3dVal;
   vector<double>  *trackMomentum;
   vector<double>  *trackEta;
   vector<double>  *trackPtRel;
   vector<double>  *trackPPar;
   vector<double>  *trackEtaRel;
   vector<double>  *trackDeltaR;
   vector<double>  *trackPtRatio;
   vector<double>  *trackPParRatio;
   vector<double>  *trackJetDist;
   vector<double>  *trackDecayLenVal;
   vector<double>  *trackDecayLenSig;
   vector<double>  *trackDecayLenSigTEST;
   Double_t        vertexMass;
   Int_t           vertexNTracks;
   Double_t        vertexEnergyRatio;
   Double_t        trackSip2dSigAboveCharm;
   Double_t        trackSip3dSigAboveCharm;
   Double_t        flightDistance2dSig;
   Double_t        flightDistance3dSig;
   Double_t        flightDistance2dVal;
   Double_t        flightDistance3dVal;
   Double_t        trackSumJetEtRatio;
   Int_t           jetNSecondaryVertices;
   Double_t        vertexJetDeltaR;
   Double_t        trackSumJetDeltaR;

   // List of branches
   TBranch        *b_flavour;   //!
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_vertexCategory;   //!
   TBranch        *b_trackSip2dSig;   //!
   TBranch        *b_trackSip3dSig;   //!
   TBranch        *b_trackSip2dVal;   //!
   TBranch        *b_trackSip3dVal;   //!
   TBranch        *b_trackMomentum;   //!
   TBranch        *b_trackEta;   //!
   TBranch        *b_trackPtRel;   //!
   TBranch        *b_trackPPar;   //!
   TBranch        *b_trackEtaRel;   //!
   TBranch        *b_trackDeltaR;   //!
   TBranch        *b_trackPtRatio;   //!
   TBranch        *b_trackPParRatio;   //!
   TBranch        *b_trackJetDist;   //!
   TBranch        *b_trackDecayLenVal;   //!
   TBranch        *b_trackDecayLenSig;   //!
   TBranch        *b_trackDecayLenSigTEST;   //!
   TBranch        *b_vertexMass;   //!
   TBranch        *b_vertexNTracks;   //!
   TBranch        *b_vertexEnergyRatio;   //!
   TBranch        *b_trackSip2dSigAboveCharm;   //!
   TBranch        *b_trackSip3dSigAboveCharm;   //!
   TBranch        *b_flightDistance2dSig;   //!
   TBranch        *b_flightDistance3dSig;   //!
   TBranch        *b_flightDistance2dVal;   //!
   TBranch        *b_flightDistance3dVal;   //!
   TBranch        *b_trackSumJetEtRatio;   //!
   TBranch        *b_jetNSecondaryVertices;   //!
   TBranch        *b_vertexJetDeltaR;   //!
   TBranch        *b_trackSumJetDeltaR;   //!

   MyAnalyzer(TTree * /*tree*/ =0) { }
   virtual ~MyAnalyzer() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();
   void    Init1DHisto(TString name, int nBin, double min, double max);
   void    Fill1DHisto(TString name, double value);
   double  GetSampleWeight();
   ClassDef(MyAnalyzer,0);
};

#endif

#ifdef MyAnalyzer_cxx
void MyAnalyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   
   // Set object pointer
   trackSip2dSig = 0;
   trackSip3dSig = 0;
   trackSip2dVal = 0;
   trackSip3dVal = 0;
   trackMomentum = 0;
   trackEta = 0;
   trackPtRel = 0;
   trackPPar = 0;
   trackEtaRel = 0;
   trackDeltaR = 0;
   trackPtRatio = 0;
   trackPParRatio = 0;
   trackJetDist = 0;
   trackDecayLenVal = 0;
   trackDecayLenSig = 0;
   trackDecayLenSigTEST = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("flavour", &flavour, &b_flavour);
   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
   fChain->SetBranchAddress("vertexCategory", &vertexCategory, &b_vertexCategory);
   fChain->SetBranchAddress("trackSip2dSig", &trackSip2dSig, &b_trackSip2dSig);
   fChain->SetBranchAddress("trackSip3dSig", &trackSip3dSig, &b_trackSip3dSig);
   fChain->SetBranchAddress("trackSip2dVal", &trackSip2dVal, &b_trackSip2dVal);
   fChain->SetBranchAddress("trackSip3dVal", &trackSip3dVal, &b_trackSip3dVal);
   fChain->SetBranchAddress("trackMomentum", &trackMomentum, &b_trackMomentum);
   fChain->SetBranchAddress("trackEta", &trackEta, &b_trackEta);
   fChain->SetBranchAddress("trackPtRel", &trackPtRel, &b_trackPtRel);
   fChain->SetBranchAddress("trackPPar", &trackPPar, &b_trackPPar);
   fChain->SetBranchAddress("trackEtaRel", &trackEtaRel, &b_trackEtaRel);
   fChain->SetBranchAddress("trackDeltaR", &trackDeltaR, &b_trackDeltaR);
   fChain->SetBranchAddress("trackPtRatio", &trackPtRatio, &b_trackPtRatio);
   fChain->SetBranchAddress("trackPParRatio", &trackPParRatio, &b_trackPParRatio);
   fChain->SetBranchAddress("trackJetDist", &trackJetDist, &b_trackJetDist);
   fChain->SetBranchAddress("trackDecayLenVal", &trackDecayLenVal, &b_trackDecayLenVal);
   fChain->SetBranchAddress("trackDecayLenSig", &trackDecayLenSig, &b_trackDecayLenSig);
   fChain->SetBranchAddress("trackDecayLenSigTEST", &trackDecayLenSigTEST, &b_trackDecayLenSigTEST);
   fChain->SetBranchAddress("trackSip2dSigAboveCharm", &trackSip2dSigAboveCharm, &b_trackSip2dSigAboveCharm);
   fChain->SetBranchAddress("trackSip3dSigAboveCharm", &trackSip3dSigAboveCharm, &b_trackSip3dSigAboveCharm);
   fChain->SetBranchAddress("trackSumJetDeltaR", &trackSumJetDeltaR, &b_trackSumJetDeltaR);
   if(category=="Reco")
   {
	   fChain->SetBranchAddress("flightDistance2dSig", &flightDistance2dSig, &b_flightDistance2dSig);
	   fChain->SetBranchAddress("flightDistance3dSig", &flightDistance3dSig, &b_flightDistance3dSig);
	   fChain->SetBranchAddress("flightDistance2dVal", &flightDistance2dVal, &b_flightDistance2dVal);
	   fChain->SetBranchAddress("flightDistance3dVal", &flightDistance3dVal, &b_flightDistance3dVal);
	   fChain->SetBranchAddress("jetNSecondaryVertices", &jetNSecondaryVertices, &b_jetNSecondaryVertices);
   }
   if((category=="Reco")||(category=="Pseudo"))
   {
	   fChain->SetBranchAddress("vertexMass", &vertexMass, &b_vertexMass);
	   fChain->SetBranchAddress("vertexNTracks", &vertexNTracks, &b_vertexNTracks);
	   fChain->SetBranchAddress("vertexEnergyRatio", &vertexEnergyRatio, &b_vertexEnergyRatio);
	   fChain->SetBranchAddress("vertexJetDeltaR", &vertexJetDeltaR, &b_vertexJetDeltaR);
	   fChain->SetBranchAddress("trackSumJetEtRatio", &trackSumJetEtRatio, &b_trackSumJetEtRatio);
   }
}

Bool_t MyAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef MyAnalyzer_cxx
