#!/bin/bash

#Directory where the output of the "extraction" jobs are stored.
DIRECTORY="/storage/9/descroix/MVA"

CAT="Reco Pseudo No"
NOCAT="Reco Pseudo" #Categories which are treated differently fir the NoVertex category.
FLAV="G U D S C B"

#Merge first the pt bins together in separated flavor and vertex category samples
for i in $CAT ; do
	for j in $FLAV ; do
		hadd -f ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_${j}.root ${DIRECTORY}/MC_QCD_Pt*_Tune4C_7TeV_pythia8_*_CombinedSV${i}Vertex_${j}.root
	done
done

#Filter the light flavor samples to a certain ratio to reduce their size. This ratio is defined in FilterEventTree.C
FLAVLIGHT="G U D S"
for i in $FLAVLIGHT ; do
	root -b -q FilterEventTree.C'("MC_QCD_Tune4C_7TeV_pythia8_CombinedSVNoVertex_'${i}'", "CombinedSVNoVertex")'
done

#Merge the light jets in the Reco and Pseudo vertex categories
for i in $NOCAT ; do
	hadd -f ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_DUSG.root ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_U.root ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_D.root ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_S.root ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSV${i}Vertex_G.root 
done

#Finally merge the light jets in the NoVertex category using the filtered samples. They carry the _small suffix.
hadd -f ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSVNoVertex_DUSG.root ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSVNoVertex_U_small.root ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSVNoVertex_D_small.root ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSVNoVertex_S_small.root ${DIRECTORY}/MC_QCD_Tune4C_7TeV_pythia8_CombinedSVNoVertex_G_small.root
