#include <string>
#include <iostream>

void AnalyzeLoader(string cat , string flav, string pt)
{
	string filename="rfio:/castor/cern.ch/user/d/descroix/MVA-Samples-PtSplit/MC_QCD_Pt"+pt+"_Tune4C_7TeV_pythia8_CombinedSV"+cat+"Vertex_"+flav+".root";
	TFile *_file = TFile::Open(filename.c_str());
	if(cat=="Reco"){CombinedSVRecoVertex->Process( "MyAnalyzer.C+" );}
	else if(cat=="Pseudo"){CombinedSVPseudoVertex->Process( "MyAnalyzer.C+" );}
	else if(cat=="No"){CombinedSVNoVertex->Process( "MyAnalyzer.C+" );}
}
