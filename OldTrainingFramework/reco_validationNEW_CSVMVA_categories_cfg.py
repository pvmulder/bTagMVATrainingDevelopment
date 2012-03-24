# The following comments couldn't be translated into the new config version:

#! /bin/env cmsRun

import FWCore.ParameterSet.Config as cms

process = cms.Process("validation")
process.load("DQMServices.Components.DQMEnvironment_cfi")

#keep the logging output to a nice level
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load("DQMServices.Core.DQM_cfg")

# load the full reconstraction configuration, to make sure we're getting all needed dependencies
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.GlobalTag.globaltag = "START44_V5::All"#"MC_42_V2::All"

process.load("PhysicsTools.JetMCAlgos.CaloJetsMCFlavour_cfi")  

#process.load("JetMETCorrections.Configuration.DefaultJEC_cff")
#process.ak5JetTracksAssociatorAtVertex.jets = cms.InputTag("ak5CaloJetsL1FastL2L3")
#process.AK5byRef.jets = cms.InputTag("ak5CaloJetsL1FastL2L3")

process.load("RecoBTag.SecondaryVertex.combinedSecondaryVertexES_cfi")

from RecoBTag.SecondaryVertex.combinedSecondaryVertexES_cfi import *

#combinedSecondaryVertex.trackPseudoSelection.totalHitsMin = cms.uint32(8) #ok
#combinedSecondaryVertex.trackPseudoSelection.jetDeltaRMax = cms.double(0.5) #needed for TCHE?  0.3 for vertex reco, 0.5 otherwise... but I can't find what the value is used in TCHE. Here to be set to 99999.9?
#combinedSecondaryVertex.trackPseudoSelection.qualityClass = cms.string('any') #probably on 'any' to be consistent with TCHE
#combinedSecondaryVertex.trackPseudoSelection.pixelHitsMin = cms.uint32(2) #ok
#combinedSecondaryVertex.trackPseudoSelection.maxDistToAxis = cms.double(0.07) #ok
#combinedSecondaryVertex.trackPseudoSelection.maxDecayLen = cms.double(5) #ok
#combinedSecondaryVertex.trackPseudoSelection.sip3dSigMin = cms.double(-99999.9) #no constraint
#combinedSecondaryVertex.trackPseudoSelection.sip3dSigMax = cms.double(99999.9) #no constraint
#combinedSecondaryVertex.trackPseudoSelection.sip2dValMax = cms.double(0.2) #not entirely clear if this is the IP2D they talk about in the track selection
#combinedSecondaryVertex.trackPseudoSelection.ptMin = cms.double(1) #ok
#combinedSecondaryVertex.trackPseudoSelection.sip2dSigMax = cms.double(99999.9) #no constraint
#combinedSecondaryVertex.trackPseudoSelection.sip2dSigMin = cms.double(-99999.9) #no constraint
#combinedSecondaryVertex.trackPseudoSelection.sip3dValMax = cms.double(99999.9) #no constraint
#combinedSecondaryVertex.trackPseudoSelection.sip3dValMin = cms.double(-99999.9) #no constraint
#combinedSecondaryVertex.trackPseudoSelection.sip2dValMin = cms.double(-0.2)#not entirely clear if this is the IP2D they talk about in the track selection
#combinedSecondaryVertex.trackPseudoSelection.normChi2Max = cms.double(5) #ok

#combinedSecondaryVertex.trackSelection.totalHitsMin = cms.uint32(8)
#combinedSecondaryVertex.trackSelection.jetDeltaRMax = cms.double(0.5)
#combinedSecondaryVertex.trackSelection.qualityClass = cms.string('any')
#combinedSecondaryVertex.trackSelection.pixelHitsMin = cms.uint32(2)
#combinedSecondaryVertex.trackSelection.maxDistToAxis = cms.double(0.07)
#combinedSecondaryVertex.trackSelection.maxDecayLen = cms.double(5)
#combinedSecondaryVertex.trackSelection.sip3dSigMin = cms.double(-99999.9)
#combinedSecondaryVertex.trackSelection.sip3dSigMax = cms.double(99999.9)
#combinedSecondaryVertex.trackSelection.sip2dValMax = cms.double(0.2)
#combinedSecondaryVertex.trackSelection.ptMin = cms.double(1)
#combinedSecondaryVertex.trackSelection.sip2dSigMax = cms.double(99999.9)
#combinedSecondaryVertex.trackSelection.sip2dSigMin = cms.double(-99999.9)
#combinedSecondaryVertex.trackSelection.sip3dValMax = cms.double(99999.9)
#combinedSecondaryVertex.trackSelection.sip3dValMin = cms.double(-99999.9)
#combinedSecondaryVertex.trackSelection.sip2dValMin = cms.double(-0.2)
#combinedSecondaryVertex.trackSelection.normChi2Max = cms.double(5)

#combinedSecondaryVertex.trackFlip = False
#combinedSecondaryVertex.vertexFlip = False
#combinedSecondaryVertex.useTrackWeights = True # vertexCuts_cfi.py
#combinedSecondaryVertex.pseudoMultiplicityMin = 3
#combinedSecondaryVertex.correctVertexMass = False
#combinedSecondaryVertex.trackPairV0Filter.k0sMassWindow = 0.05 # vertexCuts_cfi.py
#combinedSecondaryVertex.charmCut = 1.5
#combinedSecondaryVertex.minimumTrackWeight = 0.5 # from secondaryVertexTagInfos_cfi
#combinedSecondaryVertex.pseudoVertexV0Filter.k0sMassWindow = 0.05
#combinedSecondaryVertex.trackMultiplicityMin = 2
#combinedSecondaryVertex.trackSort = 'sip3dSig'


#combinedSecondaryVertex.useCategories = False
#combinedSecondaryVertex.calibrationRecord = cms.string('myCSVrecord')
combinedSecondaryVertex.useCategories = True
combinedSecondaryVertex.calibrationRecords = cms.vstring('CombinedSVRecoVertex','CombinedSVPseudoVertex','CombinedSVNoVertex')


from RecoBTag.Configuration.RecoBTag_cff import *
process.btagging = cms.Sequence(
    (
      # impact parameters and IP-only algorithms
       impactParameterTagInfos *
      ( #trackCountingHighEffBJetTags +
			 	#trackCountingHighPurBJetTags +
	secondaryVertexTagInfos * combinedSecondaryVertexBJetTags
      )  
		)
)

from Validation.RecoB.bTagAnalysis_cfi import *
process.load("Validation.RecoB.bTagAnalysis_cfi")
process.bTagValidation.jetMCSrc = 'AK5byValAlgo'
process.bTagValidation.allHistograms = True 
#process.bTagValidation.fastMC = True

process.bTagValidation.tagConfig = cms.VPSet(
        cms.PSet(
            bTagTrackIPAnalysisBlock,
            type = cms.string('TrackIP'),
            label = cms.InputTag("impactParameterTagInfos"),
            folder = cms.string("IPTag")
        ), 
        cms.PSet(
    				parameters = cms.PSet(
        			discriminatorStart = cms.double(-35),
        			discriminatorEnd = cms.double(35),
        			nBinEffPur = cms.int32(200),
        			# the constant b-efficiency for the differential plots versus pt and eta
        			effBConst = cms.double(0.5),
        			endEffPur = cms.double(1.005),
        			startEffPur = cms.double(0.005)
    				),
            #bTagTrackCountingAnalysisBlock,
            label = cms.InputTag("trackCountingHighEffBJetTags"),
            folder = cms.string("TCHE")
        ), 
        cms.PSet(
    				parameters = cms.PSet(
        			discriminatorStart = cms.double(-35),
        			discriminatorEnd = cms.double(35),
        			nBinEffPur = cms.int32(200),
        			# the constant b-efficiency for the differential plots versus pt and eta
        			effBConst = cms.double(0.5),
        			endEffPur = cms.double(1.005),
        			startEffPur = cms.double(0.005)
    				),
            #bTagTrackCountingAnalysisBlock,
            label = cms.InputTag("trackCountingHighPurBJetTags"),
            folder = cms.string("TCHP")
        ), 
        cms.PSet(
				    parameters = cms.PSet(
        			discriminatorStart = cms.double(-0.05),
        			discriminatorEnd = cms.double(1.05),
        			nBinEffPur = cms.int32(200),
        			# the constant b-efficiency for the differential plots versus pt and eta
        			effBConst = cms.double(0.5),
        			endEffPur = cms.double(1.005),
        			startEffPur = cms.double(0.005)
    				),
            label = cms.InputTag("combinedSecondaryVertexBJetTags"),
            folder = cms.string("CSV")
        ), 
        cms.PSet(
                parameters = cms.PSet(
                discriminatorStart = cms.double(0.0),
                nBinEffPur = cms.int32(200),
                # the constant b-efficiency for the differential plots versus pt and eta
                effBConst = cms.double(0.5),
                endEffPur = cms.double(1.005),
                discriminatorEnd = cms.double(8.0),
                startEffPur = cms.double(0.005)
                ),              
            label = cms.InputTag("simpleSecondaryVertexHighEffBJetTags"),
            folder = cms.string("SSVHE")
        ),
        cms.PSet(
                parameters = cms.PSet(
                discriminatorStart = cms.double(0.0),
                nBinEffPur = cms.int32(200),
                # the constant b-efficiency for the differential plots versus pt and eta
                effBConst = cms.double(0.5),
                endEffPur = cms.double(1.005),
                discriminatorEnd = cms.double(8.0),
                startEffPur = cms.double(0.005)
                ),              
            label = cms.InputTag("simpleSecondaryVertexHighPurBJetTags"),
            folder = cms.string("SSVHP")
        )
)



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

#process.GlobalTag.toGet = cms.VPSet(
# cms.PSet(
#		record = cms.string('BTauGenericMVAJetTagComputerRcd'),
#  	tag = cms.string('MVAJetTags_CMSSW_4_2_0_pre6_TEST'),
#  	connect = cms.untracked.string('sqlite_file:CombinedSecondaryVertexBJetTags.db')
#  )
#)

#from CondCore.DBCommon.CondDBSetup_cfi import *

##from RecoBTau.JetTagComputer.MVAJetTagsFrontierConditions_cfi import *
##BTauMVAJetTagComputerRecord.connect = 'frontier://cms_conditions_data/CMS_COND_20X_BTAU'
process.load("CondCore.DBCommon.CondDBSetup_cfi")

process.BTauMVAJetTagComputerRecord = cms.ESSource("PoolDBESSource",
	process.CondDBSetup,
	timetype = cms.string('runnumber'),
	toGet = cms.VPSet(cms.PSet(
		record = cms.string('BTauGenericMVAJetTagComputerRcd'),
                tag = cms.string('MVAJetTagsNEW')
		#tag = cms.string('MVAJetTags_CMSSW_2_0_0_mc')
		#tag = cms.string('MVAJetTags_test')
		#tag = cms.string('MVAJetTags_trackSip3dSig_2nd_B_vs_UDSG')
		#tag = cms.string('MVAJetTags_trackSip3dSig_2nd_B_vs_C')
	)),
	connect = cms.string("sqlite_file:MVAJetTagsFakeConditionsNEW.db"),
	#connect = cms.string('frontier://FrontierDev/CMS_COND_BTAU'),
	BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService')
)
process.es_prefer_BTauMVAJetTagComputerRecord = cms.ESPrefer("PoolDBESSource","BTauMVAJetTagComputerRecord")




#if JEC are applied, the plots are empty...
#process.plots = cms.Path(process.ak5CaloJetsL1FastL2L3 * process.ak5JetTracksAssociatorAtVertex * process.myPartons* process.AK5Flavour * process.btagging * process.bTagValidation * process.dqmSaver)
process.plots = cms.Path(process.myPartons* process.AK5Flavour * process.btagging * process.bTagValidation * process.dqmSaver)

process.dqmEnv.subSystemFolder = 'BTAG'
process.dqmSaver.producer = 'DQM'
process.dqmSaver.workflow = '/POG/BTAG/categories'
process.dqmSaver.convention = 'Offline'
process.dqmSaver.saveByRun = cms.untracked.int32(-1)
process.dqmSaver.saveAtJobEnd =cms.untracked.bool(True) 
process.dqmSaver.forceRunNumber = cms.untracked.int32(1)
process.PoolSource.fileNames = [
#'/store/mc/Fall11/QCD_Pt-15to30_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/0274AD40-0540-E111-AB25-003048C693D6.root',
#'/store/mc/Fall11/QCD_Pt-15to30_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/0298AD46-0840-E111-9562-0030487F92B5.root',
#'/store/mc/Fall11/QCD_Pt-15to30_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/067FE203-F43F-E111-AFC4-003048F0EBBE.root',
#'/store/mc/Fall11/QCD_Pt-30to50_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/0CD1765D-0F43-E111-B481-002481E94B6C.root',
#'/store/mc/Fall11/QCD_Pt-30to50_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/10FD9235-0E43-E111-A0F3-003048C691DC.root',
#'/store/mc/Fall11/QCD_Pt-30to50_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/147270BD-0743-E111-A7EF-003048F0E526.root',
#'/store/mc/Fall11/QCD_Pt-50to80_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/00225C27-4744-E111-8583-003048C692E4.root',
'/store/mc/Fall11/QCD_Pt-50to80_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/3E388000-4B44-E111-B4BD-003048C6617E.root',
'/store/mc/Fall11/QCD_Pt-50to80_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/405D6520-4C44-E111-9507-003048C6763A.root',
'/store/mc/Fall11/QCD_Pt-80to120_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/96EAC216-6044-E111-97CE-00266CF32F00.root',
'/store/mc/Fall11/QCD_Pt-80to120_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/98781810-4F44-E111-8172-003048F0E1B0.root',
'/store/mc/Fall11/QCD_Pt-120to170_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/EE43F557-7E47-E111-8DA0-003048D436FE.root',
'/store/mc/Fall11/QCD_Pt-170to300_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/9EA16095-7F44-E111-99F8-00266CF25320.root',
'/store/mc/Fall11/QCD_Pt-300to470_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/5C4A6EDE-673F-E111-9D16-0030487DA061.root',
'/store/mc/Fall11/QCD_Pt-470to600_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/AA674985-F145-E111-A7E2-002481E0D50C.root',
'/store/mc/Fall11/QCD_Pt-600to800_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/9C5299B2-F73F-E111-86DF-003048C6763A.root',
'/store/mc/Fall11/QCD_Pt-800to1000_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/78A13BF8-5844-E111-B1AA-0025901D4C44.root',
'/store/mc/Fall11/QCD_Pt-1000to1400_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/A2420654-8B43-E111-A302-0030487D7105.root',
'/store/mc/Fall11/QCD_Pt-1400to1800_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/CEDE79FB-1346-E111-8583-003048C693E4.root',
'/store/mc/Fall11/QCD_Pt-1800_Tune4C_7TeV_pythia8/AODSIM/PU_S6_START44_V9B-v1/0000/A0E0689F-2744-E111-8452-003048F02CB8.root'
#'/store/mc/Fall11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/BC6A4711-A20F-E111-A340-0026189438A7.root'    
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//74623280-FC97-E011-B646-001A92810A9E.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//762D80C4-F297-E011-863C-003048678ED2.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//76C51022-FE97-E011-81F6-001BFCDBD1BE.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//783E1B29-F997-E011-8E2D-001A92971B0C.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//788A01A5-F597-E011-A2E1-003048678FF4.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//78B55751-F097-E011-9796-003048678FA6.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//78C88F59-FC97-E011-AE0E-002618943861.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//7C4297D7-F397-E011-9146-0018F3D0962E.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//7C42B699-F497-E011-BD0B-001A92810AF4.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//7C5EE9F6-F297-E011-A880-003048D25B68.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//8085065C-FF97-E011-95AD-0018F3D0968A.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//82015EEC-F397-E011-A7A4-002618943977.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//88128AC5-F097-E011-B55D-00248C0BE014.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//8C0863D2-F797-E011-89C2-001A92810AD4.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//8C60EC78-FC97-E011-9742-0026189438A0.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//90B0328F-F697-E011-8C51-003048678BAA.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//90F7432C-F297-E011-B6C9-002354EF3BDF.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//9A8D19C4-FD97-E011-B3CC-002618943905.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//A255379A-F897-E011-893A-001A92971B32.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//A6884CB4-F197-E011-8591-003048B835A2.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//AA05DF76-F397-E011-AD42-003048678B86.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//AA897344-FE97-E011-9984-0018F3D09710.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//AC646E48-FF97-E011-8BAC-002354EF3BE6.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//B0321F5B-F197-E011-B841-003048678B18.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//B04F9181-F097-E011-8713-003048678B18.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//B0E4FCCB-F097-E011-A58F-003048678CA2.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//B2CACB7E-FF97-E011-9977-002618FDA279.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//B69A6019-F797-E011-B589-001A92971B90.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//B8290C9D-F097-E011-98F6-003048D25B68.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//BC71FC32-FB97-E011-9CE2-00261894380A.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//BE124BB3-F797-E011-A1BC-00261894384F.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//C0FE791B-FF97-E011-BA50-003048D3C010.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//C265A7E1-F297-E011-BEC1-0018F3D0960C.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//C82FE3DD-F497-E011-A367-0018F3D09708.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//CC3467B2-F297-E011-B698-00304867C0EA.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//D2C0EDF0-F097-E011-99D2-003048678ED2.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//D419D0BA-F397-E011-A992-0018F3D0960A.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//D6489581-FF97-E011-8F1A-001A9281172A.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//D6886400-FE97-E011-BCCC-003048D42DC8.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//D8DA30C8-F797-E011-8E8C-001BFCDBD1BC.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//DCD6B9DA-F297-E011-BB4D-003048679164.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//DE53234D-FC97-E011-A622-0018F3D0962A.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//E25B3712-F997-E011-81D1-001A92810AF2.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//E6A50E41-FF97-E011-A7E6-0026189438A0.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//E8E1AA04-F397-E011-81BA-003048D15E24.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//EA0075EA-F997-E011-BEEA-0018F3D096EA.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//EA9E9779-FA97-E011-8B22-001A92811744.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//F0871461-FC97-E011-B7C6-002618943958.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//FA55A8A8-F397-E011-8E23-003048678FF4.root',
#'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/GEN-SIM-RECO/PU_S4_START42_V11-v1/0000//FCB78C13-F597-E011-91AC-0018F3D0963C.root',
]
