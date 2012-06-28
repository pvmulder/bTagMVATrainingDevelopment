#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>

#include <TROOT.h>
#include "TH1F.h"
#include "TText.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TAttPad.h"
#include "TStyle.h"
#include "THStack.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include "TApplication.h"
#include "TMath.h"
#include "TTree.h"
#include "TLeaf.h"

#include "cmsstyle.hpp"

using namespace std;

TH1F* get_histo(const TString & filename, const TString & histoname)
{
	TH1F::AddDirectory(false);
	TFile f(filename, "read");
	
	if(!f.IsOpen()){cerr << "get_histo: could not open " << filename << endl;}
	
	TH1F* res=0;
	res = (TH1F*)(gDirectory->FindObjectAny(histoname));
	
	if (res==0){cerr << "get_histo: didn't find " << histoname << " in " << filename << endl;}
	
	return res;
}

std::vector<TH1F*> PlotLoader(string cat, string var)
{

	char histoname[500];
	
	std::vector<TH1F*> Histos;
	
	string rootname="Histos.root";
	
	//B-jets
	sprintf(histoname,"%s_%s_B",var.c_str(),cat.c_str());
	TH1F* Histo_B = (TH1F*) get_histo(rootname.c_str() ,histoname)->Clone();
	Histos.push_back(Histo_B);
	
	//C-jets
	sprintf(histoname,"%s_%s_C",var.c_str(),cat.c_str());
	TH1F* Histo_C = (TH1F*) get_histo(rootname.c_str() ,histoname)->Clone();
	Histos.push_back(Histo_C);
	
	//DUSG-jets
	sprintf(histoname,"%s_%s_DUSG",var.c_str(),cat.c_str());
	TH1F* Histo_DUSG = (TH1F*) get_histo(rootname.c_str() ,histoname)->Clone();
	Histos.push_back(Histo_DUSG);
	
	
	//Scale
	double scale;
	for(int i=0;i<Histos.size();i++)
	{
		scale=1/Histos.at(i)->Integral();
		Histos.at(i)->Scale(scale);
	}
	
	return Histos;
}

//Edit a basic plot configuration depending on the variable to plot
void variableConf(string var, string * Axis_title, int * n_Rebin)
{
	string Ytitle="Normalized to unit area";
	
	if(var.find("trackMomentum")!=string::npos)
	{
		*Axis_title=";Track Momentum [GeV/c];"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackEta")!=string::npos)
	{
		*Axis_title=";Track #eta;"+Ytitle;
		*n_Rebin=1;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	if(var.find("jetPt")!=string::npos)
	{
		*Axis_title=";Jet Momentum [GeV/c];"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("jetEta")!=string::npos)
	{
		*Axis_title=";Jet #eta;"+Ytitle;
		*n_Rebin=1;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(var.find("trackSip2dSig")!=string::npos)
	{
		*Axis_title=";IP2D significance;"+Ytitle;
		*n_Rebin=1;
	}
	if(var=="trackSip3dSig")
	{
		*Axis_title=";IP3D significance;"+Ytitle;
		*n_Rebin=1;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(var.find("trackSip3dSig_1")!=string::npos)
	{
		*Axis_title=";1st IP3D sig;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackSip3dSig_2")!=string::npos)
	{
		*Axis_title=";2nd IP3D sig;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackSip3dSig_3")!=string::npos)
	{
		*Axis_title=";3rd IP3D sig;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackSip3dSig_rest")!=string::npos)
	{
		*Axis_title=";Remaining IP3D sig;"+Ytitle;
		*n_Rebin=1;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(var.find("trackSip2dVal")!=string::npos)
	{
		*Axis_title=";IP2D value;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackSip3dVal")!=string::npos)
	{
		*Axis_title=";IP3D value;"+Ytitle;
		*n_Rebin=1;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(var.find("trackPtRel")!=string::npos)
	{
		*Axis_title=";Track p_{T}^{rel};"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackPPar")!=string::npos)
	{
		*Axis_title=";Track p_{par};"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackPtRatio")!=string::npos)
	{
		*Axis_title=";Track p_{T}^{ratio};"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackPParRatio")!=string::npos)
	{
		*Axis_title=";Track p_{par}^{ratio};"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackEtaRel")!=string::npos)
	{
		*Axis_title=";Track #eta^{rel};"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackDeltaR")!=string::npos)
	{
		*Axis_title=";Track-Jet #Delta R;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackJetDist")!=string::npos)
	{
		*Axis_title=";Track-Jet distance;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackMultiplicity")!=string::npos)
	{
		*Axis_title=";Track Multiplicity;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackDecayLenVal")!=string::npos)
	{
		*Axis_title=";Track Decay Length Value;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackDecayLenSig")!=string::npos)
	{
		*Axis_title=";Track Decay Length Significance;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackSumJetDeltaR")!=string::npos)
	{
		*Axis_title=";#Delta R(Jet, Track-Sum);"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackSumJetEtRatio")!=string::npos)
	{
		*Axis_title=";Ratio(Track-Sum, Jet-E_{T});"+Ytitle;
		*n_Rebin=1;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(var.find("vertexMass")!=string::npos)
	{
		*Axis_title=";Vertex Mass [GeV/c^{2}];"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("vertexNTracks")!=string::npos)
	{
		*Axis_title=";Vertex Track Multiplicity;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("vertexEnergyRatio")!=string::npos)
	{
		*Axis_title=";Vertex-Jet Energy Ratio;"+Ytitle;
		*n_Rebin=1;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(var.find("trackSip2dSigAboveCharm")!=string::npos)
	{
		*Axis_title=";IP2D significance above Charm;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("trackSip3dSigAboveCharm")!=string::npos)
	{
		*Axis_title=";IP3D significance above Charm;"+Ytitle;
		*n_Rebin=1;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(var.find("flightDistance2dSig")!=string::npos)
	{
		*Axis_title=";2D Flight Distance significance;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("flightDistance3dSig")!=string::npos)
	{
		*Axis_title=";3D Flight Distance significance;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("flightDistance2dVal")!=string::npos)
	{
		*Axis_title=";2D Flight Distance value;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("flightDistance3dVal")!=string::npos)
	{
		*Axis_title=";3D Flight Distance value;"+Ytitle;
		*n_Rebin=1;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(var.find("jetNSecondaryVertices")!=string::npos)
	{
		*Axis_title=";Secondary Vertex Multiplicity;"+Ytitle;
		*n_Rebin=1;
	}
	if(var.find("vertexJetDeltaR")!=string::npos)
	{
		*Axis_title=";Vertex-Jet #Delta R;"+Ytitle;
		*n_Rebin=1;
	}
}

void FindMax(std::vector<TH1F*> plotted, double * Maximum, string var)
{
	double Max=-999999999;
	double ram;
	for(int i=0;i<plotted.size();i++)
	{
		ram=plotted.at(i)->GetMaximum();
		if(ram>Max){Max=ram;}
	}
	*Maximum=Max*1.1;
}

void FindMin(std::vector<TH1F*> plotted, double * Minimum, string var)
{
	double Min=999999999;
	double ram;
	for(int i=0;i<plotted.size();i++)
	{
		ram=plotted.at(i)->GetMinimum();
		if(ram<Min){Min=ram;}
	}
	if(Min>0){*Minimum=0.85*Min;}
	if(Min<=0){*Minimum=0.00000001;}
}

void Drawer(string cat, string var, string log)
{	
	CMSStyle *Style = new CMSStyle();
	
//Build objects to trace the plots
//Canvas for stack plots
	TCanvas *c1 = new TCanvas();
	
	c1->SetTicks();
	c1->cd()->SetRightMargin(0.04);

//Legend
	TLegend *l = new TLegend(0.6997487,0.6573427,0.9949749,0.9300699,"","brNDC");
	l->SetBorderSize(0);
	l->SetLineStyle(0);
	l->SetTextFont(42);
	l->SetFillStyle(0);
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//loading the plots

	std::vector<TH1F*> Histos;
	Histos = PlotLoader(cat,var);

	
	
	//Defining Rebining and axis titles depending on the variable to plot
	int n_Rebin=1;
	string Axis_title;
	
	variableConf(var,&Axis_title, &n_Rebin);
	
	//Rebinning
	for(int i=0;i<Histos.size();i++)
	{
		Histos.at(i)->Rebin(n_Rebin);
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//"Adding" histograms in a new one in order to get the CMSStyle!

	std::vector<TH1F*> Samples;
	
	const int nBins=Histos.at(0)->GetNbinsX();
	double Xmin=Histos.at(0)->GetXaxis()->GetXmin();
	double Xmax=Histos.at(0)->GetXaxis()->GetXmax();
	double BinWidth=Xmax-Xmin/nBins;
	
	
	TH1F* Hist0 = new TH1F("Hist0","",nBins,Xmin,Xmax);
	Samples.push_back(Hist0);
	TH1F* Hist1 = new TH1F("Hist1","",nBins,Xmin,Xmax);
	Samples.push_back(Hist1);
	TH1F* Hist2 = new TH1F("Hist2","",nBins,Xmin,Xmax);
	Samples.push_back(Hist2);
	
	Samples.at(0)->Add(Histos.at(0));//B
	Samples.at(1)->Add(Histos.at(1));//C
	Samples.at(2)->Add(Histos.at(2));//DUSG
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//Decide what to draw

	std::vector<TH1F*> ToDraw;
	TH1F* ToDraw0 = new TH1F("ToDraw0","",nBins,Xmin,Xmax);
	ToDraw.push_back(ToDraw0);
	TH1F* ToDraw1 = new TH1F("ToDraw1","",nBins,Xmin,Xmax);
	ToDraw.push_back(ToDraw1);
	TH1F* ToDraw2 = new TH1F("ToDraw2","",nBins,Xmin,Xmax);
	ToDraw.push_back(ToDraw2);
	
	ToDraw.at(0)->Add(Samples.at(0));//B
	ToDraw.at(1)->Add(Samples.at(1));//C
	ToDraw.at(2)->Add(Samples.at(2));//DUSG
	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Styling
	
	Color_t Color[11];
	Color[0]=kRed+1;
	Color[1]=kMagenta;
	Color[2]=kGreen-3;
	Color[3]=kAzure-2;
	Color[4]=kYellow;
	Color[5]=kOrange+8;
	Color[6]=kOrange+8;
	Color[7]=kOrange+8;
	Color[8]=kOrange+8;
	
	for(int i=0;i<ToDraw.size();i++)
	{
		Style->setup_style(ToDraw.at(i), Axis_title, Color[i], false, false);
	}

	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Text
	string title = "Jets of "+cat+"Vertex category";
	TText *t = new TText(0.19,0.9,title.c_str());
	t->SetNDC(kTRUE);
	t->SetTextSize(0.032);
	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Drawing

	std::vector<TH1F*> Plotted;
	
	double Max,Min;
	c1->cd();
	if(log.find("log")!=string::npos){c1->SetLogy();}
		
	ToDraw.at(0)->Draw("hist");
	Plotted.push_back(ToDraw.at(0));
	for(int j=1;j<ToDraw.size();j++)
	{
		ToDraw.at(j)->Draw("histsame");
		Plotted.push_back(ToDraw.at(j));
	}

	Plotted.at(Plotted.size()-1)->Draw("axissame");

	FindMax(Plotted, &Max, var);
	FindMin(Plotted, &Min, var);
	if(log=="log")
	{
		Plotted.at(0)->SetMaximum(Max*20);
		Plotted.at(ToDraw.size()-1)->SetMinimum(Min);
	}
	if(log=="lin")
	{
		Plotted.at(0)->SetMaximum(Max);
		Plotted.at(ToDraw.size()-1)->SetMinimum(Min);

	}
	t->Draw();
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Working out the legend

	l->SetHeader("MC QCD sample:");
	l->AddEntry(ToDraw.at(0),"b-jets","L");
	l->AddEntry(ToDraw.at(1),"c-jets","L");
	l->AddEntry(ToDraw.at(2),"dusg-jets","L");
	l->Draw();
	
//Saving Histos		
	
	string outFileName=var+"_"+cat+"Vertex_"+log+"_unitNorm.pdf";
	c1->Print(outFileName.c_str());
	outFileName=var+"_"+cat+"Vertex_"+log+"_unitNorm.png";
	c1->Print(outFileName.c_str());
	outFileName=var+"_"+cat+"Vertex_"+log+"_unitNorm.root";
	c1->Print(outFileName.c_str());
}

int main(int argc, char** argv)
{
	TApplication App("App", &argc, argv);
	
	gStyle->SetOptStat(0);
	
	string vertCat,rep;
	
	vertCat = "Reco";
	rep = "lin";

	 Drawer(vertCat,"jetPt",rep);
	Drawer(vertCat,"jetEta",rep);
	Drawer(vertCat,"trackMultiplicity",rep);
	
	Drawer(vertCat,"trackSip2dSig",rep);
	Drawer(vertCat,"trackSip3dSig",rep);
	Drawer(vertCat,"trackSip3dSig_1stTrk",rep);
	Drawer(vertCat,"trackSip3dSig_2ndTrk",rep);
	Drawer(vertCat,"trackSip3dSig_3rdTrk",rep);
	Drawer(vertCat,"trackSip3dSig_restTrk",rep);
	Drawer(vertCat,"trackSip2dVal",rep);
	Drawer(vertCat,"trackSip3dVal",rep);
	
	Drawer(vertCat,"trackMomentum",rep);
	Drawer(vertCat,"trackEta",rep);
	Drawer(vertCat,"trackPtRel",rep);
	Drawer(vertCat,"trackPPar",rep);
	Drawer(vertCat,"trackEtaRel",rep);
	Drawer(vertCat,"trackDeltaR",rep);
	Drawer(vertCat,"trackPtRatio",rep);
	Drawer(vertCat,"trackPParRatio",rep);
	Drawer(vertCat,"trackJetDist",rep);
	Drawer(vertCat,"trackDecayLenVal",rep);
	Drawer(vertCat,"trackDecayLenSig",rep);
	Drawer(vertCat,"trackDecayLenSigTEST",rep);
	Drawer(vertCat,"trackSip2dSigAboveCharm",rep);
	Drawer(vertCat,"trackSip3dSigAboveCharm",rep);
	Drawer(vertCat,"trackSumJetEtRatio",rep);
	Drawer(vertCat,"trackSumJetDeltaR",rep);
	
	if(vertCat!="No")
	{
		Drawer(vertCat,"vertexMass",rep);
		Drawer(vertCat,"vertexNTracks",rep);
		Drawer(vertCat,"vertexEnergyRatio",rep);
		Drawer(vertCat,"vertexJetDeltaR",rep);
	}
	if((vertCat!="No")&&(vertCat!="Pseudo"))
	{	
		Drawer(vertCat,"jetNSecondaryVertices",rep);
		Drawer(vertCat,"flightDistance2dSig",rep);
		Drawer(vertCat,"flightDistance3dSig",rep);
		Drawer(vertCat,"flightDistance2dVal",rep);
		Drawer(vertCat,"flightDistance3dVal",rep);
	}
		
	App.Run();
	return 0;
}
