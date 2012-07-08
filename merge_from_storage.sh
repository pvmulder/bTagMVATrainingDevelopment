#!/bin/bash

maindirec=/pnfs/iihe/cms/store/user/`whoami`/BtagExtractor_44X

dirs_to_merge=(QCD_Pt-1000to1400_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-120to170_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-1400to1800_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-15to30_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-170to300_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-1800_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-300to470_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-30to50_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-470to600_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-50to80_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-600to800_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-800to1000_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM QCD_Pt-80to120_Tune4C_7TeV_pythia8_Fall11-PU_S6_START44_V9B-v1_AODSIM)

homedirec=/user/pvmulder/NewEraOfDataAnalysis/BTagServiceWork/CMSSW_4_4_4/src/BTagging/RootFilesPetra

CAT=(CombinedSVRecoVertex CombinedSVPseudoVertex CombinedSVNoVertex)
#CAT=(CombinedSVRecoVertex)
FLAV=(B C DUSG)

cd $homedirec

for l in ${dirs_to_merge[@]} ;
do
	for k in ${CAT[@]} ;
	do
		for j in $( ls $maindirec/$l/${k}_B*); do printf "dcap://maite.iihe.ac.be/$j " >> ${k}Bfiles.txt; done
		for j in $( ls $maindirec/$l/${k}_C*); do printf "dcap://maite.iihe.ac.be/$j " >> ${k}Cfiles.txt; done
		if [ $k=="CombinedSVNoVertex" ]
		then
			let countfiles=0
			for j in $( ls $maindirec/$l/${k}_D*); do
				echo "at file number $countfiles" 
				((countfiles++))
				if [ $countfiles -ne 1 ] ; then if [ $countfiles -eq 10 ] ; then countfiles=0 ; fi ; continue ; fi #this makes sure that only 1/10 files is used!
				printf "dcap://maite.iihe.ac.be/$j " >> ${k}DUSGfiles.txt
			done
			let countfiles=0
			for j in $( ls $maindirec/$l/${k}_U*); do 
				echo "at file number $countfiles" 
				((countfiles++))
				if [ $countfiles -ne 1 ] ; then if [ $countfiles -eq 10 ] ; then countfiles=0 ; fi ; continue ; fi #this makes sure that only 1/10 files is used!
				printf "dcap://maite.iihe.ac.be/$j " >> ${k}DUSGfiles.txt
			done
			let countfiles=0
			for j in $( ls $maindirec/$l/${k}_S*); do 
				echo "at file number $countfiles" 
				((countfiles++))
				if [ $countfiles -ne 1 ] ; then if [ $countfiles -eq 10 ] ; then countfiles=0 ; fi ; continue ; fi #this makes sure that only 1/10 files is used!
				printf "dcap://maite.iihe.ac.be/$j " >> ${k}DUSGfiles.txt
			done
			let countfiles=0
			for j in $( ls $maindirec/$l/${k}_G*); do 
				echo "at file number $countfiles" 
				((countfiles++))
				if [ $countfiles -ne 1 ] ; then if [ $countfiles -eq 10 ] ; then countfiles=0 ; fi ; continue ; fi #this makes sure that only 1/10 files is used!
				printf "dcap://maite.iihe.ac.be/$j " >> ${k}DUSGfiles.txt
			done
		else
			for j in $( ls $maindirec/$l/${k}_D*); do printf "dcap://maite.iihe.ac.be/$j " >> ${k}DUSGfiles.txt; done
			for j in $( ls $maindirec/$l/${k}_U*); do printf "dcap://maite.iihe.ac.be/$j " >> ${k}DUSGfiles.txt; done
			for j in $( ls $maindirec/$l/${k}_S*); do printf "dcap://maite.iihe.ac.be/$j " >> ${k}DUSGfiles.txt; done
			for j in $( ls $maindirec/$l/${k}_G*); do printf "dcap://maite.iihe.ac.be/$j " >> ${k}DUSGfiles.txt; done			
		fi
	done
done	

for k in ${CAT[@]} ;
do
	for i in ${FLAV[@]} ;
	do
		echo cat ${k}${i}files.txt
		rootfiles=`cat ${k}${i}files.txt`
		hadd tmp.root $rootfiles
		mv tmp.root ${k}_${i}.root
	done
done
