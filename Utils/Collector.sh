#!/bin/bash

export CATS="Reco Pseudo No"
export FLAVS="B C DUSG"
export PT="15to30 30to50 50to80 80to120 120to170 170to300 300to470 470to600 600to800 800to1000 1000to1400 1400to1800 1800"
export lightJetPrescale="5"

for CAT in $CATS ; do
   for FLAV in $FLAVS ; do
   	for DATASETNICK in $PT; do
		export CAT
		export FLAV
		export DATASETNICK
		root -l -q AnalyzeLoader.C'("'${CAT}'","'${FLAV}'","'${DATASETNICK}'")'
	done
   done
done

hadd -f Histos.root Histos_*_*_*.root
rm -f Histos_*_*_*.root
