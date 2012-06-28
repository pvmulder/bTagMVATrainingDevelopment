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

std::vector<TH1F*> PlotLoader(string cat, string var, string etabin)
{

	char histoname[500];
	
	std::vector<TH1F*> Histos;
	
	string rootname="Histos.root";
	
	//B-jets
	sprintf(histoname,"%s_%s_B%s",var.c_str(),cat.c_str(),etabin.c_str());
	TH1F* Histo_B = (TH1F*) get_histo(rootname.c_str() ,histoname)->Clone();
	Histos.push_back(Histo_B);
	
	//C-jets
	sprintf(histoname,"%s_%s_C%s",var.c_str(),cat.c_str(),etabin.c_str());
	TH1F* Histo_C = (TH1F*) get_histo(rootname.c_str() ,histoname)->Clone();
	Histos.push_back(Histo_C);
	
	//DUSG-jets
	sprintf(histoname,"%s_%s_DUSG%s",var.c_str(),cat.c_str(),etabin.c_str());
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

void Drawer(string cat, string var, string log,string config)
{	
	CMSStyle *Style = new CMSStyle();
	
//Build objects to trace the plots
//Canvas for stack plots

	std::vector<TCanvas*> Canvas;
	
	TCanvas *c1 = new TCanvas();
	c1->SetTicks();
	c1->cd()->SetRightMargin(0.04);
	
	TCanvas *c2 = new TCanvas();
	c2->SetTicks();
	c2->cd()->SetRightMargin(0.04);
	
	Canvas.push_back(c1);
	Canvas.push_back(c2);
	
	if(config=="etaComp")
	{
		TCanvas *c3 = new TCanvas();
		c3->SetTicks();
		c3->cd()->SetRightMargin(0.04);
		Canvas.push_back(c3);
	}
	
	
//Legend
	std::vector<TLegend*> Legends;
	
	TLegend *l1 = new TLegend(0.669598,0.6713287,0.9648241,0.9440559,"","brNDC");
	TLegend *l2 = new TLegend(0.669598,0.6713287,0.9648241,0.9440559,"","brNDC");
	TLegend *l3 = new TLegend(0.669598,0.6713287,0.9648241,0.9440559,"","brNDC");
	
	if(config=="etaComp")
	{
		l1->SetBorderSize(0);
		l1->SetLineStyle(0);
		l1->SetTextFont(42);
		l1->SetFillStyle(0);
		l1->SetHeader("b-jets:");

		l2->SetBorderSize(0);
		l2->SetLineStyle(0);
		l2->SetTextFont(42);
		l2->SetFillStyle(0);
		l2->SetHeader("c-jets:");

		l3->SetBorderSize(0);
		l3->SetLineStyle(0);
		l3->SetTextFont(42);
		l3->SetFillStyle(0);
		l3->SetHeader("light-jets:");
	}
	if(config=="flavComp")
	{
		l1->SetBorderSize(0);
		l1->SetLineStyle(0);
		l1->SetTextFont(42);
		l1->SetFillStyle(0);
		l1->SetHeader("jet-#eta < 1.4:");

		l2->SetBorderSize(0);
		l2->SetLineStyle(0);
		l2->SetTextFont(42);
		l2->SetFillStyle(0);
		l2->SetHeader("jet-#eta > 1.4:");
	}
	
	
	Legends.push_back(l1);
	Legends.push_back(l2);
	if(config=="etaComp"){Legends.push_back(l3);}
	
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//loading the plots

	std::vector<TH1F*> Histos_eta0;
	std::vector<TH1F*> Histos_eta1;
	
	Histos_eta0 = PlotLoader(cat,var,"_eta0to1p4");
	Histos_eta1 = PlotLoader(cat,var,"_eta1p4to2p4");

	//Defining Rebining and axis titles depending on the variable to plot
	int n_Rebin=1;
	string Axis_title;
	
	variableConf(var,&Axis_title, &n_Rebin);
	
	//Rebinning
	for(int i=0;i<Histos_eta0.size();i++)
	{
		Histos_eta0.at(i)->Rebin(n_Rebin);
		Histos_eta1.at(i)->Rebin(n_Rebin);
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//"Adding" histograms in a new one in order to get the CMSStyle!

	std::vector<TH1F*> Samples_eta0;
	std::vector<TH1F*> Samples_eta1;
	std::vector<std::vector<TH1F*> > Samples;
	
	const int nBins=Histos_eta0.at(0)->GetNbinsX();
	double Xmin=Histos_eta0.at(0)->GetXaxis()->GetXmin();
	double Xmax=Histos_eta0.at(0)->GetXaxis()->GetXmax();
	double BinWidth=Xmax-Xmin/nBins;
	
	
	TH1F* Histb0 = new TH1F("Histb0","",nBins,Xmin,Xmax);
	Samples_eta0.push_back(Histb0);
	TH1F* Histb1 = new TH1F("Histb1","",nBins,Xmin,Xmax);
	Samples_eta1.push_back(Histb1);
	TH1F* Histc0 = new TH1F("Histc0","",nBins,Xmin,Xmax);
	Samples_eta0.push_back(Histc0);
	TH1F* Histc1 = new TH1F("Histc1","",nBins,Xmin,Xmax);
	Samples_eta1.push_back(Histc1);
	TH1F* Histl0 = new TH1F("Histl0","",nBins,Xmin,Xmax);
	Samples_eta0.push_back(Histl0);
	TH1F* Histl1 = new TH1F("Histl1","",nBins,Xmin,Xmax);
	Samples_eta1.push_back(Histl1);
	
	Samples_eta0.at(0)->Add(Histos_eta0.at(0));//B
	Samples_eta0.at(1)->Add(Histos_eta0.at(1));//C
	Samples_eta0.at(2)->Add(Histos_eta0.at(2));//DUSG
	
	Samples_eta1.at(0)->Add(Histos_eta1.at(0));//B
	Samples_eta1.at(1)->Add(Histos_eta1.at(1));//C
	Samples_eta1.at(2)->Add(Histos_eta1.at(2));//DUSG
	
	Samples.push_back(Samples_eta0);
	Samples.push_back(Samples_eta1);
	
	
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
	
	if(config=="etaComp")
	{
		for(int i=0;i<Samples_eta0.size();i++)
		{
			Style->setup_style(Samples_eta0.at(i), Axis_title, Color[0], false, false);
			Style->setup_style(Samples_eta1.at(i), Axis_title, Color[3], false, false);
		}
	}
	if(config=="flavComp")
	{
		for(int i=0;i<Samples_eta0.size();i++)
		{
			Style->setup_style(Samples_eta0.at(i), Axis_title, Color[i], false, false);
			Style->setup_style(Samples_eta1.at(i), Axis_title, Color[i], false, false);
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Working out the legend
	if(config=="etaComp")
	{
		for(int i=0;i<Legends.size();i++)
		{
			Legends.at(i)->AddEntry(Samples_eta0.at(0),"|jet-#eta| < 1.4","L");
			Legends.at(i)->AddEntry(Samples_eta1.at(0),"1.4<|jet-#eta|<2.4","L");
		}
	}
	if(config=="flavComp")
	{
		for(int i=0;i<Legends.size();i++)
		{
			Legends.at(i)->AddEntry(Samples_eta0.at(0),"b-jets","L");
			Legends.at(i)->AddEntry(Samples_eta0.at(1),"c-jets","L");
			Legends.at(i)->AddEntry(Samples_eta0.at(2),"light jets","L");
		}
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Text
	string title = "Jets of "+cat+"Vertex category";
	TText *t = new TText(0.19,0.9,title.c_str());
	t->SetNDC(kTRUE);
	t->SetTextSize(0.035);
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Drawing
	
	std::vector<TH1F*> Plotted;
	
	if(log.find("log")!=string::npos){for(int i=0;i<Canvas.size();i++){Canvas.at(i)->SetLogy();}}
	
	double Max,Min;
	if(config=="etaComp")
	{
		for(int i=0;i<Canvas.size();i++)
		{
			Canvas.at(i)->cd();
			Samples_eta0.at(i)->Draw("hist");
			Samples_eta1.at(i)->Draw("histsame");
			Samples_eta1.at(i)->Draw("axissame");
			Plotted.push_back(Samples_eta0.at(i));
			Plotted.push_back(Samples_eta1.at(i));
			FindMax(Plotted, &Max, var);
			FindMin(Plotted, &Min, var);
			if(log=="log")
			{
				Plotted.at(i*3)->SetMaximum(Max*2);
				Plotted.at((i*3)+2)->SetMinimum(Min);
			}
			if(log=="lin")
			{
				Plotted.at(i*3)->SetMaximum(Max);
				Plotted.at((3*i)+2)->SetMinimum(Min);
				
			}
			Legends.at(i)->Draw();
			t->Draw();
		}
	}
	if(config=="flavComp")
	{
		for(int i=0;i<Samples.size();i++)
		{
			Canvas.at(i)->cd();
			Samples.at(i).at(0)->Draw("hist");
			Samples.at(i).at(1)->Draw("histsame");
			Samples.at(i).at(2)->Draw("histsame");
			Samples.at(i).at(0)->Draw("axissame");
			Plotted.push_back(Samples.at(i).at(0));
			Plotted.push_back(Samples.at(i).at(1));
			Plotted.push_back(Samples.at(i).at(2));
			FindMax(Plotted, &Max, var);
			FindMin(Plotted, &Min, var);
			if(log=="log")
			{
				Plotted.at(i*3)->SetMaximum(Max*2);
				Plotted.at((i*3)+2)->SetMinimum(Min);
			}
			if(log=="lin")
			{
				Plotted.at(i*3)->SetMaximum(Max);
				Plotted.at((3*i)+2)->SetMinimum(Min);
				
			}
			Legends.at(i)->Draw();
			t->Draw();
		}
	}
	
//Saving Histos		
	vector<string> outName;
	if(config=="etaComp")
	{
		outName.push_back(var+"_"+cat+"Vertex_"+log+"_unitNorm_EtaBinComp_B");
		outName.push_back(var+"_"+cat+"Vertex_"+log+"_unitNorm_EtaBinComp_C");
		outName.push_back(var+"_"+cat+"Vertex_"+log+"_unitNorm_EtaBinComp_DUSG");
	}
	if(config=="flavComp")
	{
		outName.push_back(var+"_"+cat+"Vertex_"+log+"_unitNorm_JetEtal1p4");
		outName.push_back(var+"_"+cat+"Vertex_"+log+"_unitNorm_JetEtam1p4");
	}
	string outFileName;
	
	for(int i=0;i<Canvas.size();i++)
	{
		outFileName=outName.at(i)+".png";
		Canvas.at(i)->Print(outFileName.c_str());
		outFileName=outName.at(i)+".pdf";
		Canvas.at(i)->Print(outFileName.c_str());
		outFileName=outName.at(i)+".root";
		Canvas.at(i)->Print(outFileName.c_str());
	}
}

int main(int argc, char** argv)
{
	TApplication App("App", &argc, argv);
	
	gStyle->SetOptStat(0);
	
	string vertCat,rep,etabin,conf;
	
	vertCat = "Reco";
	rep = "log";
	
//	conf = "etaComp";
	conf = "flavComp";
	

	Drawer(vertCat,"jetPt",rep,conf);
	Drawer(vertCat,"jetEta",rep,conf);
	Drawer(vertCat,"trackMultiplicity",rep,conf);
	
	Drawer(vertCat,"trackSip2dSig",rep,conf);
	Drawer(vertCat,"trackSip3dSig",rep,conf);
	Drawer(vertCat,"trackSip3dSig_1stTrk",rep,conf);
	Drawer(vertCat,"trackSip3dSig_2ndTrk",rep,conf);
	Drawer(vertCat,"trackSip3dSig_3rdTrk",rep,conf);
	Drawer(vertCat,"trackSip3dSig_restTrk",rep,conf);
	Drawer(vertCat,"trackSip2dVal",rep,conf);
	Drawer(vertCat,"trackSip3dVal",rep,conf);
	
	Drawer(vertCat,"trackMomentum",rep,conf);
	Drawer(vertCat,"trackEta",rep,conf);
	Drawer(vertCat,"trackPtRel",rep,conf);
	Drawer(vertCat,"trackPPar",rep,conf);
	Drawer(vertCat,"trackEtaRel",rep,conf);
	Drawer(vertCat,"trackDeltaR",rep,conf);
	Drawer(vertCat,"trackPtRatio",rep,conf);
	Drawer(vertCat,"trackPParRatio",rep,conf);
	Drawer(vertCat,"trackJetDist",rep,conf);
	Drawer(vertCat,"trackDecayLenVal",rep,conf);
	Drawer(vertCat,"trackDecayLenSig",rep,conf);
	Drawer(vertCat,"trackDecayLenSigTEST",rep,conf);
	Drawer(vertCat,"trackSip2dSigAboveCharm",rep,conf);
	Drawer(vertCat,"trackSip3dSigAboveCharm",rep,conf);
	Drawer(vertCat,"trackSumJetEtRatio",rep,conf);
	Drawer(vertCat,"trackSumJetDeltaR",rep,conf);
	
	if(vertCat!="No")
	{
		Drawer(vertCat,"vertexMass",rep,conf);
		Drawer(vertCat,"vertexNTracks",rep,conf);
		Drawer(vertCat,"vertexEnergyRatio",rep,conf);
		Drawer(vertCat,"vertexJetDeltaR",rep,conf);
	}
	if((vertCat!="No")&&(vertCat!="Pseudo"))
	{	
		Drawer(vertCat,"jetNSecondaryVertices",rep,conf);
		Drawer(vertCat,"flightDistance2dSig",rep,conf);
		Drawer(vertCat,"flightDistance3dSig",rep,conf);
		Drawer(vertCat,"flightDistance2dVal",rep,conf);
		Drawer(vertCat,"flightDistance3dVal",rep,conf);
	}

	App.Run();
	return 0;
}

