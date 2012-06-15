#!/bin/sh
CAT="Reco Pseudo No"
#for i in $CAT ; do
#hadd CombinedSVMVA${i}Vertex_DUSG.root CombinedSVMVA${i}Vertex_G.root CombinedSVMVA${i}Vertex_S.root CombinedSVMVA${i}Vertex_U.root CombinedSVMVA${i}Vertex_D.root
#hadd CombinedSVMVA${i}Vertex_B_DUSG.root CombinedSVMVA${i}Vertex_DUSG.root CombinedSVMVA${i}Vertex_B.root
#hadd CombinedSVMVA${i}Vertex_B_C.root CombinedSVMVA${i}Vertex_C.root  CombinedSVMVA${i}Vertex_B.root
#done

root -l -b -q histoJetEtaPt.C+ 
#g++ fitJetEtaPt.cpp `root-config --cflags --glibs` -o fitter
mkdir weights
for i in $CAT ; do
	./fitter CombinedSVMVA${i}Vertex_B_C_histo.root
  mv out.txt weights/CombinedSVMVA${i}Vertex_BC_histo.txt
  mv out.root weights/CombinedSVMVA${i}Vertex_BC_histo_check.root

	./fitter CombinedSVMVA${i}Vertex_B_histo.root CombinedSVMVA${i}Vertex_C_histo.root
	mv out.txt weights/CombinedSVMVA${i}Vertex_B_C_ratio.txt
  mv out.root weights/CombinedSVMVA${i}Vertex_B_C_ratio_check.root

	./fitter CombinedSVMVA${i}Vertex_B_DUSG_histo.root 
	mv out.txt weights/CombinedSVMVA${i}Vertex_BL_histo.txt
  mv out.root weights/CombinedSVMVA${i}Vertex_BL_ratio_check.root

	./fitter CombinedSVMVA${i}Vertex_B_histo.root CombinedSVMVA${i}Vertex_DUSG_histo.root
	mv out.txt weights/CombinedSVMVA${i}Vertex_B_DUSG_ratio.txt
  mv out.root weights/CombinedSVMVA${i}Vertex_B_DUSG_ratio_check.root
done

cmsRun MVATrainer_No_B_C_cfg.py
cmsRun MVATrainer_Reco_B_DUSG_cfg.py
cmsRun MVATrainer_Reco_B_C_cfg.py
cmsRun MVATrainer_Pseudo_B_DUSG_cfg.py
cmsRun MVATrainer_Pseudo_B_C_cfg.py
cmsRun MVATrainer_No_B_DUSG_cfg.py

COMBINATIONS="No_B_DUSG No_B_C Reco_B_DUSG Reco_B_C Pseudo_B_DUSG Pseudo_B_C"
for i in $COMBINATIONS ; do
 echo Processing $i
 mkdir tmp$i
 cd tmp$i
 mvaTreeTrainer ../Train_CSVMVA_$i.xml tmp.mva ../train_${i}_save.root 
# ../fixup.sh
 cd ..
done

#cp tmpReco_B_*/*.xml .
echo "global training for RecoVertex"
mvaTreeTrainer -l Train_CSVMVA_RecoVertex.xml CombinedSVMVARecoVertex.mva train_Reco_B_DUSG_save.root train_Reco_B_C_save.root
#cp tmpPseudo_B_*/*.xml .
echo "global training for PseudoVertex"
mvaTreeTrainer -l Train_CSVMVA_PseudoVertex.xml CombinedSVMVAPseudoVertex.mva train_Pseudo_B_DUSG_save.root train_Pseudo_B_C_save.root
#cp tmpNo_B_*/*.xml .
echo "global training for NoVertex"
mvaTreeTrainer -l Train_CSVMVA_NoVertex.xml CombinedSVMVANoVertex.mva train_No_B_DUSG_save.root train_No_B_C_save.root

cmsRun copyMVAToSQLite_cfg.py
cmsRun reco_validationNEW_CSVMVA_categories_cfg.py
