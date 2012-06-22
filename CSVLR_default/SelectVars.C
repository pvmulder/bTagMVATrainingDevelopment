//The code uses as inputs the Train*.xml files in the folder ./TrainExtraVars
//Then it outputs the modified files in the current directory. It will overwrite there the Train*.xml files
//In principle you are supposed to run it from the folder that contains SelectVars with:
// root -q -l SelectVars.C


std::vector<TString> VetoVariablesReco;
std::vector<TString> VetoVariablesPseudo;
std::vector<TString> VetoVariablesNo;

void InitVetoVariables() {
//Select here the variables you want to veto 6 variables can be vetoed so far
VetoVariablesReco.push_back("trackDeltaR");
VetoVariablesReco.push_back("trackPtRatio");
VetoVariablesReco.push_back("trackJetDist");
VetoVariablesReco.push_back("trackDecayLenVal");
VetoVariablesReco.push_back("trackSumJetEtRatio");
VetoVariablesReco.push_back("vertexJetDeltaR");


VetoVariablesPseudo.push_back("trackDeltaR");
VetoVariablesPseudo.push_back("trackPtRatio");
VetoVariablesPseudo.push_back("trackJetDist");
VetoVariablesPseudo.push_back("trackDecayLenVal");
VetoVariablesPseudo.push_back("trackSumJetEtRatio");
VetoVariablesPseudo.push_back("vertexJetDeltaR");


VetoVariablesNo.push_back("trackDeltaR");
VetoVariablesNo.push_back("trackPtRatio");
VetoVariablesNo.push_back("trackJetDist");
VetoVariablesNo.push_back("trackDecayLenVal");
VetoVariablesNo.push_back("trackSumJetEtRatio");
}

//In principle no need to modify anything below this point

void SelectVars() {
  InitVetoVariables();

  AdaptOneFile("Train_NoVertex.xml", VetoVariablesNo);
  AdaptOneFile("Train_No_B_C.xml", VetoVariablesNo);
  AdaptOneFile("Train_No_B_DUSG.xml", VetoVariablesNo);
  AdaptOneFile("Train_PseudoVertex.xml", VetoVariablesPseudo);
  AdaptOneFile("Train_Pseudo_B_C.xml", VetoVariablesPseudo);
  AdaptOneFile("Train_Pseudo_B_DUSG.xml", VetoVariablesPseudo);
  AdaptOneFile("Train_RecoVertex.xml", VetoVariablesReco);
  AdaptOneFile("Train_Reco_B_C.xml", VetoVariablesReco);
  AdaptOneFile("Train_Reco_B_DUSG.xml", VetoVariablesReco);

}

void AdaptOneFile(TString file = "", std::vector<TString> VetoVars) {
  
  TString dir = "TrainExtraVars/";
  TString outputdir = "./";

  
  
  ifstream ifile(dir + file);
  ofstream of(outputdir + file);

  TString line;

  while (ifile) {
    line.ReadLine(ifile,false);
    
    //If line contains a line with the variable we are copying
    // then we add another line replacing the new variable by the old one
    bool printline = true;
    for (unsigned int i = 0; i < VetoVars.size(); i++) {
      
      //if line contains one of the vetoed variables, then the line is not written
      if (line.Contains(VetoVars[i])) {
        printline = false;
	break;
      }
    
    }//end loop to veto variables vector
    
    if (printline) of << line << endl;
    
  }//end loop to input file lines
}
