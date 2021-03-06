#!/bin/sh
CAT="Reco Pseudo No"

#for i in $CAT ; do
#hadd CombinedSV${i}Vertex_DUSG.root CombinedSV${i}Vertex_G.root CombinedSV${i}Vertex_S.root CombinedSV${i}Vertex_U.root CombinedSV${i}Vertex_D.root
#hadd CombinedSV${i}Vertex_B_DUSG.root CombinedSV${i}Vertex_DUSG.root CombinedSV${i}Vertex_B.root
#hadd CombinedSV${i}Vertex_B_C.root CombinedSV${i}Vertex_C.root  CombinedSV${i}Vertex_B.root
#done

root -l -b histoJetEtaPt.C+ 
#g++ fitJetEtaPt.cpp `root-config --cflags --glibs` -o fitter
mkdir weights
for i in $CAT ; do
	./fitter CombinedSV${i}Vertex_B_C_histo.root
  mv out.txt weights/CombinedSV${i}Vertex_BC_histo.txt
  mv out.root weights/CombinedSV${i}Vertex_BC_histo_check.root

	./fitter CombinedSV${i}Vertex_B_histo.root CombinedSV${i}Vertex_C_histo.root
	mv out.txt weights/CombinedSV${i}Vertex_B_C_ratio.txt
  mv out.root weights/CombinedSV${i}Vertex_B_C_ratio_check.root

	./fitter CombinedSV${i}Vertex_B_DUSG_histo.root 
	mv out.txt weights/CombinedSV${i}Vertex_BL_histo.txt
  mv out.root weights/CombinedSV${i}Vertex_BL_ratio_check.root

	./fitter CombinedSV${i}Vertex_B_histo.root CombinedSV${i}Vertex_DUSG_histo.root
	mv out.txt weights/CombinedSV${i}Vertex_B_DUSG_ratio.txt
  mv out.root weights/CombinedSV${i}Vertex_B_DUSG_ratio_check.root
done

cmsRun MVATrainer_No_B_C_cfg.py
cmsRun MVATrainer_Reco_B_DUSG_cfg.py
cmsRun MVATrainer_Reco_B_C_cfg.py
cmsRun MVATrainer_Pseudo_B_DUSG_cfg.py
cmsRun MVATrainer_Pseudo_B_C_cfg.py
cmsRun MVATrainer_No_B_DUSG_cfg.py

COMBINATIONS="No_B_C Reco_B_DUSG Reco_B_C Pseudo_B_DUSG Pseudo_B_C No_B_DUSG"
for i in $COMBINATIONS ; do
 echo Processing $i
 mkdir tmp$i
 cd tmp$i
 mvaTreeTrainer ../Train_$i.xml tmp.mva ../train_${i}_save.root 
# ../fixup.sh
 cd ..
done

cp tmpReco_B_*/*.xml .
mvaTreeTrainer -l Train_RecoVertex.xml CombinedSVRecoVertex.mva train_Reco_B_DUSG_save.root train_Reco_B_C_save.root
cp tmpPseudo_B_*/*.xml .
mvaTreeTrainer -l Train_PseudoVertex.xml CombinedSVPseudoVertex.mva train_Pseudo_B_DUSG_save.root train_Pseudo_B_C_save.root
cp tmpNo_B_*/*.xml .
mvaTreeTrainer -l Train_NoVertex.xml CombinedSVNoVertex.mva train_No_B_DUSG_save.root train_No_B_C_save.root

