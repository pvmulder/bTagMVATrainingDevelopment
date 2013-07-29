#read -p "PARALLEL PROCESSING: how many cores can you afford? " answer

answer=6

path_to_rootfiles=/afs/cern.ch/work/p/pvmulder/public/BTagging/CSVMVA/CMSSW_5_3_4_patch1/src/RootFiles/
Combinations="NoVertex_B_DUSG NoVertex_B_C PseudoVertex_B_DUSG PseudoVertex_B_C RecoVertex_B_DUSG RecoVertex_B_C"
CAT="Reco Pseudo No"
prefix="CombinedSV"

echo "Filling the 2D pt/eta histograms" 

g++ ./histoJetEtaPt.cpp `root-config --cflags --glibs` -o histos
./histos $path_to_rootfiles $prefix

echo "Reweighting the trees according to the pt/eta weights and saving the relevant variables " 

files=("MVATrainer_No_B_DUSG_cfg.py" "MVATrainer_No_B_C_cfg.py" "MVATrainer_Pseudo_B_DUSG_cfg.py" "MVATrainer_Pseudo_B_C_cfg.py" "MVATrainer_Reco_B_DUSG_cfg.py" "MVATrainer_Reco_B_C_cfg.py")

l=0
while [ $l -lt 6 ]
do
	jobsrunning=0
	while [ $jobsrunning -lt $answer ]
	do
echo ${files[l]}
		nohup cmsRun ${files[l]} &
		let jobsrunning=$jobsrunning+1
		let l=$l+1
	done
	wait
done


echo "Do the actual training"

CombinationsArray=("NoVertex_B_DUSG" "NoVertex_B_C" "PseudoVertex_B_DUSG" "PseudoVertex_B_C" "RecoVertex_B_DUSG" "RecoVertex_B_C")
l=0
while [ $l -lt 6 ]
do
	jobsrunning=0
	while [[ $jobsrunning -lt $answer && $jobsrunning -lt 6 ]] 
	do
		echo Processing ${CombinationsArray[l]}
 		mkdir tmp${CombinationsArray[l]}
 		cd tmp${CombinationsArray[l]}
		nohup mvaTreeTrainer ../CSV_CMSSWMLP_${CombinationsArray[l]}.xml tmp.mva ../train_${CombinationsArray[l]}_save.root &
		cd ..
		let jobsrunning=$jobsrunning+1
		let l=$l+1
	done
	wait
done


echo "Combine the B versus DUSG and B versus C training "

VertexCategory=("NoVertex" "PseudoVertex" "RecoVertex")
l=0
while [ $l -lt 3 ]
do
	jobsrunning=0
	while [[ $jobsrunning -lt $answer  && $jobsrunning -lt 3 ]] 
	do
 		mkdir tmp${VertexCategory[l]}
 		cd tmp${VertexCategory[l]}
		cp ../tmp${VertexCategory[l]}_B_C/*.xml .
		cp ../tmp${VertexCategory[l]}_B_C/*.txt .
		cp ../tmp${VertexCategory[l]}_B_DUSG/*.xml .
		cp ../tmp${VertexCategory[l]}_B_DUSG/*.txt .
 		nohup mvaTreeTrainer -l ../CSV_CMSSWMLP_${VertexCategory[l]}.xml ${prefix}MVA_${VertexCategory[l]}.mva ../train_${VertexCategory[l]}_B_DUSG_save.root ../train_${VertexCategory[l]}_B_C_save.root &
		cd ..
		let jobsrunning=$jobsrunning+1
		let l=$l+1
	done
	wait
done

