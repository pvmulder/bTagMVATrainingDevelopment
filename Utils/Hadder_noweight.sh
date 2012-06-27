#!/bin/bash

INPUT=$1

CAT="Reco Pseudo No"
FLAV="G U D S C B"
PT="15to30 30to50 50to80 80to120 120to170 170to300 300to470 470to600 600to800 800to1000 1000to1400 1400to1800 1800"

#for i in $CAT ; do
#	hadd -f ${INPUT}../merged/MC_QCD_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_DUSG.root ${INPUT}MC_QCD_*_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_DUSG.root 
#	hadd -f ${INPUT}../merged/MC_QCD_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_B_DUSG.root ${INPUT}MC_QCD_*_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_B_DUSG.root
#	hadd -f ${INPUT}../merged/MC_QCD_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_B_C.root ${INPUT}MC_QCD_*_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_B_C.root
#done

for i in $CAT ; do
	for j in $FLAV ; do
		hadd -f ${INPUT}../merged/MC_QCD_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_${j}.root ${INPUT}MC_QCD_*_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_${j}.root
	done
done
