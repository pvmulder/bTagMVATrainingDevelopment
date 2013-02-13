import FWCore.ParameterSet.Config as cms

process = cms.Process("validation")
process.load("DQMServices.Components.DQMEnvironment_cfi")

#keep the logging output to a nice level
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# load the full reconstraction configuration, to make sure we're getting all needed dependencies
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.GlobalTag.globaltag = "START53_V6::All"

process.load("DQMServices.Core.DQM_cfg")

#process.load("CondCore.DBCommon.CondDBSetup_cfi")
#process.BTauMVAJetTagComputerRecord = cms.ESSource("PoolDBESSource",
#	process.CondDBSetup,
#	timetype = cms.string('runnumber'),
#	toGet = cms.VPSet(cms.PSet(
#		record = cms.string('BTauGenericMVAJetTagComputerRcd'),
#                tag = cms.string('MVAJetTags_CMSSW_4_4_4')
#	)),
#	connect = cms.string("sqlite_file:MVAJetTags.db"),
#	#connect = cms.string('frontier://FrontierDev/CMS_COND_BTAU'),
#	BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService')
#)
#process.es_prefer_BTauMVAJetTagComputerRecord = cms.ESPrefer("PoolDBESSource","BTauMVAJetTagComputerRecord")
#
#process.load("RecoBTag.SecondaryVertex.combinedSecondaryVertexES_cfi")


#define you jet ID
jetID = cms.InputTag("ak5PFJets")
JetCut=cms.string("neutralHadronEnergyFraction < 0.99 && neutralEmEnergyFraction < 0.99 && nConstituents > 1 && chargedHadronEnergyFraction > 0.0 && chargedMultiplicity > 0.0 && chargedEmEnergyFraction < 0.99")


#do the PFnoPU using PF2PAT
process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring('drop *'),
                               fileName = cms.untracked.string('EmptyFile.root')
                               )
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.pfTools import *
postfix="PF2PAT"
usePF2PAT(process,runPF2PAT=True, jetAlgo="AK5", runOnMC=True, postfix=postfix, pvCollection=cms.InputTag('goodOfflinePrimaryVertices'), typeIMetCorrections=False
#,jetCorrections=('AK5PFchs', ['L1FastJet','L2Relative','L3Absolute']), pvCollection=cms.InputTag('goodOfflinePrimaryVertices'), typeIMetCorrections=False, outputModules=['out']
)
process.patJetCorrFactorsPF2PAT.payload = 'AK5PFchs'
process.patJetCorrFactorsPF2PAT.levels = cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute'])
process.pfPileUpPF2PAT.checkClosestZVertex = False
process.patJetsPF2PAT.discriminatorSources = cms.VInputTag(
        cms.InputTag("combinedSecondaryVertexBJetTagsAODPF2PAT")
)
process.btaggingJetTagsAODPF2PAT = cms.Sequence(getattr(process,"combinedSecondaryVertexBJetTagsAODPF2PAT") )
# top projections in PF2PAT:
getattr(process,"pfNoPileUp"+postfix).enable = True
#applyPostfix(process,"patJetCorrFactors",postfix).payload = cms.string('AK5PFchs')
#process.pfPileUpPF2PAT.Vertices = cms.InputTag('goodOfflinePrimaryVertices')
#process.pfPileUpPF2PAT.checkClosestZVertex = cms.bool(False)
process.selectedPatJetsPF2PAT.cut = JetCut
process.JECAlgo = cms.Sequence( getattr(process,"patPF2PATSequence"+postfix) )

newjetID=cms.InputTag("selectedPatJetsPF2PAT")


#JTA for your jets
from RecoJets.JetAssociationProducers.j2tParametersVX_cfi import *
process.myak5JetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
                                                  j2tParametersVX,
                                                  jets = jetID
                                                  )

#new input for impactParameterTagInfos, softleptons
from RecoBTag.Configuration.RecoBTag_cff import *
process.btagging = cms.Sequence(impactParameterTagInfos * secondaryVertexTagInfos * combinedSecondaryVertexBJetTags)
process.impactParameterTagInfos.jetTracks = cms.InputTag("myak5JetTracksAssociatorAtVertex")
softMuonTagInfos.jets = jetID
softElectronTagInfos.jets = jetID

process.load("PhysicsTools.JetMCAlgos.CaloJetsMCFlavour_cfi")  
process.AK5byRef.jets = jetID

#do the matching
process.flavourSeq = cms.Sequence(
    process.myPartons *
    process.AK5Flavour# *
#    process.AK5byValAlgo
    )

#select good primary vertex
from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector
process.goodOfflinePrimaryVertices = cms.EDFilter(
    "PrimaryVertexObjectFilter",
    filterParams = pvSelector.clone( minNdof = cms.double(4.0), maxZ = cms.double(24.0) ),
    src=cms.InputTag('offlinePrimaryVertices')
    )

#for the  use of JEC, could change with time : be careful if recommandations change for the correctors
#define you sequence like  process.JECAlgo = cms.Sequence(process.ak5PFJetsJEC * process.PFJetsFilter)
JetCut=cms.string("neutralHadronEnergyFraction < 0.99 && neutralEmEnergyFraction < 0.99 && nConstituents > 1 && chargedHadronEnergyFraction > 0.0 && chargedMultiplicity > 0.0 && chargedEmEnergyFraction < 0.99")

from JetMETCorrections.Configuration.DefaultJEC_cff import *
process.load("JetMETCorrections.Configuration.JetCorrectionServices_cff")
process.ak5PFJetsJEC = cms.EDProducer('PFJetCorrectionProducer',
    src         = cms.InputTag('ak5PFJets'),
    correctors  = cms.vstring('ak5PFL2L3')
    )

process.PFJetsFilter = cms.EDFilter("PFJetSelector",
                            src = cms.InputTag("ak5PFJetsJEC"),
                            cut = JetCut,
                            filter = cms.bool(True)
                            )


process.JECAlgo = cms.Sequence(process.ak5PFJetsJEC * process.PFJetsFilter)
newjetID=cms.InputTag("PFJetsFilter")

process.myak5JetTracksAssociatorAtVertex.jets = newjetID
process.softMuonTagInfos.jets                 = newjetID
process.softElectronTagInfos.jets             = newjetID
process.AK5byRef.jets                         = newjetID

#from RecoBTag.Configuration.RecoBTag_cff import *
#process.btagging = cms.Sequence(
#    (
#      # impact parameters and IP-only algorithms
#       impactParameterTagInfos *
#      ( #trackCountingHighEffBJetTags +
#			 	#trackCountingHighPurBJetTags +
#	secondaryVertexTagInfos * combinedSecondaryVertexBJetTags
#      )  
#		)
#)

from DQMOffline.RecoB.bTagCommon_cff import*
process.load("DQMOffline.RecoB.bTagCommon_cff")
process.bTagCommonBlock.ptRanges = cms.vdouble(0.0,40.0,60.0,90.0, 150.0,3000.0)
process.bTagCommonBlock.etaRanges = cms.vdouble(0.0, 1.2, 2.1, 2.4)

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
        ) 
        ,cms.PSet(
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
    input = cms.untracked.int32(100000)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.plots = cms.Path(process.goodOfflinePrimaryVertices * process.JECAlgo * process.flavourSeq * process.myak5JetTracksAssociatorAtVertex * process.btagging * process.bTagValidation * process.dqmSaver)

process.dqmEnv.subSystemFolder = 'BTAG'
process.dqmSaver.producer = 'DQM'
process.dqmSaver.workflow = '/POG/BTAG/OLD'
process.dqmSaver.convention = 'Offline'
process.dqmSaver.saveByRun = cms.untracked.int32(-1)
process.dqmSaver.saveAtJobEnd =cms.untracked.bool(True) 
process.dqmSaver.forceRunNumber = cms.untracked.int32(1)
process.PoolSource.fileNames = [
'/store/mc/Summer12/QCD_Pt-15to3000_TuneZ2_Flat_8TeV_pythia6/AODSIM/PU_S7_START52_V9-v1/0000/02FE9503-3C97-E111-915E-0030487D5D5B.root'
]
