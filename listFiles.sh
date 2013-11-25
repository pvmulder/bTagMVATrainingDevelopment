#BtagValidation_53X/CSVMVA_trained20k_eachptetabin_weights_wofactor_bestsofarCombLinearNew_ProcMLPallvars_NewTrackSelection_modified1_tighttracksel/

for i in $( ls /pnfs/iihe/cms/store/user/pvmulder/$1) ; do
    if `echo $i | grep "DQMfile" 1>/dev/null 2>&1`
		then echo -n "'/store/user/pvmulder/"$1"/"$i"', "
		fi
done
