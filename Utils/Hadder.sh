#!/bin/bash

INPUT=$1

CAT="Reco Pseudo No"
FLAV="G U D S C B"
#PT="15to30 30to50 50to80 80to120 120to170 170to300 300to470 470to600 600to800 800to1000 1000to1400 1400to1800 1800"
PT="15to30 30to50 50to80 120to170 170to300 300to470 470to600 600to800 800to1000 1000to1400 1400to1800 1800"#Because of mistake with 80to120

for i in $CAT ; do
	for j in $FLAV ; do
		for k in ${PT} ; do
			hadd -f ${INPUT}MC_QCD_Pt${k}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_${j}.root ${INPUT}MC_QCD_Pt${k}_Tune4C_7TeV_pythia8_*_CombinedSV${i}Vertex_${j}.root
		done
	done
done


#Special because of mistake with 80to120

for i in $CAT ; do
	for j in $FLAV ; do
		hadd -f ${INPUT}MC_QCD_Pt80to120_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_${j}.root ${INPUT}QCD_80_120_*_CombinedSV${i}Vertex_${j}.root
	done
done

PT="15to30 30to50 50to80 80to120 120to170 170to300 300to470 470to600 600to800 800to1000 1000to1400 1400to1800 1800"

for i in $CAT ; do
	for j in $PT ; do
		hadd -f ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_DUSG.root ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_G.root ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_S.root ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_U.root ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_D.root
		hadd -f ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_B_DUSG.root ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_DUSG.root ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_B.root
		hadd -f ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_B_C.root ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_C.root  ${INPUT}MC_QCD_Pt${j}_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_B.root
	done
done
