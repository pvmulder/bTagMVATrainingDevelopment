void FilterEventTree(TString filename, TString treename) {
// Example of Root macro based on $ROOTSYS/tutorials/tree/copytree3.C
// to record only one entry each N entries of the tree
   
   //Can be needed
   //gSystem->Load("$ROOTSYS/test/libEvent"); 
   
   //Directory to take the input and write the ouput files
   TString Directory="/storage/9/descroix/MVA/merged/";

   int  OneOutOfX = 10;//You can modify the fraction of events you want to keep here
   
   //Get old file, old tree and set top branch address
   TString oldfileName=Directory+filename+".root";
   TFile *oldfile = new TFile(oldfileName);
   TTree *oldtree = (TTree*)oldfile->Get(treename);
   Int_t nentries = (Int_t)oldtree->GetEntries();

   //Create a new file + a clone of old tree in new file
   TString outputName = Directory+filename+"_small.root"; // Add "_small.root" to the name of the output file
   TFile *newfile = new TFile(outputName,"recreate");
   TTree *newtree = oldtree->CloneTree(0);
   
   for (Int_t i=0;i<nentries; i++) {//loop on the events
      if(i%OneOutOfX==0) {//OneOutOfX the number of events after which one event is stored
	      oldtree->GetEntry(i);
	      newtree->Fill();
      }
   }
   //newtree->Print(); // If needed to check the result
   newtree->AutoSave();
   delete oldfile;
   delete newfile;
}
