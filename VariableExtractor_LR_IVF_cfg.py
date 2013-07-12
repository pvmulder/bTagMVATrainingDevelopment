import FWCore.ParameterSet.Config as cms

process = cms.Process("CSVTrainer")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("RecoBTau.JetTagComputer.jetTagRecord_cfi")
process.load("RecoBTag.SecondaryVertex.combinedSecondaryVertexES_cfi")
#process.combinedSecondaryVertex.trackMultiplicityMin = cms.uint32(2)

# load the full reconstruction configuration, to make sure we're getting all needed dependencies
process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("Configuration.StandardSequences.Geometry_cff") #old one, to use for old releases
process.load("Configuration.Geometry.GeometryIdeal_cff") #new one
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.GlobalTag.globaltag = cms.string("START53_V15::All")

#To use the newest training!
process.load("CondCore.DBCommon.CondDBSetup_cfi")
process.BTauMVAJetTagComputerRecord = cms.ESSource("PoolDBESSource",
       process.CondDBSetup,
       timetype = cms.string('runnumber'),
       toGet = cms.VPSet(cms.PSet(
               record = cms.string('BTauGenericMVAJetTagComputerRcd'),
               tag = cms.string('MVAJetTags_CMSSW_5_3_4')
       )),
       connect = cms.string("sqlite_file:MVAJetTags_withPFnoPU_Adding2HighPtBins.db"),
       #connect = cms.string('frontier://FrontierDev/CMS_COND_BTAU'),
       BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService')
)
process.es_prefer_BTauMVAJetTagComputerRecord = cms.ESPrefer("PoolDBESSource","BTauMVAJetTagComputerRecord")

#for Inclusive Vertex Finder
process.load('RecoVertex/AdaptiveVertexFinder/inclusiveVertexing_cff')
process.load('RecoBTag/SecondaryVertex/inclusiveSecondaryVertexFinderTagInfos_cfi')

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
                                                  jets = jetID # replaced by newjetID later
                                                  )

#new input for impactParameterTagInfos, softleptons
from RecoBTag.Configuration.RecoBTag_cff import *
process.impactParameterTagInfos.jetTracks = cms.InputTag("myak5JetTracksAssociatorAtVertex")

process.load("PhysicsTools.JetMCAlgos.CaloJetsMCFlavour_cfi")  
process.AK5byRef.jets = jetID # replaced by newjetID later

#do the matching
process.flavourSeq = cms.Sequence(
    process.myPartons *
    process.AK5Flavour
    )

############ the following is now done within PF2PAT
#
#select good primary vertex
from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector
process.goodOfflinePrimaryVertices = cms.EDFilter(
    "PrimaryVertexObjectFilter",
    filterParams = pvSelector.clone( minNdof = cms.double(4.0), maxZ = cms.double(24.0) ),
    src=cms.InputTag('offlinePrimaryVertices')
    )
#for the  use of JEC, could change with time : be careful if recommandations change for the correctors
#define you sequence like  process.JECAlgo = cms.Sequence(process.ak5PFJetsJEC * process.PFJetsFilter)
#from JetMETCorrections.Configuration.DefaultJEC_cff import *
#process.load("JetMETCorrections.Configuration.JetCorrectionServices_cff")
#process.ak5PFJetsJEC = cms.EDProducer('PFJetCorrectionProducer',
#    src         = cms.InputTag('ak5PFJets'),
#    correctors  = cms.vstring('ak5PFL2L3')
#    )
#process.PFJetsFilter = cms.EDFilter("PFJetSelector",
#                            src = cms.InputTag("ak5PFJetsJEC"),
#                            cut = JetCut,
#                            filter = cms.bool(True)
#                            )
#process.JECAlgo = cms.Sequence(process.ak5PFJetsJEC * process.PFJetsFilter)
#newjetID=cms.InputTag("PFJetsFilter")

process.myak5JetTracksAssociatorAtVertex.jets = newjetID
process.AK5byRef.jets                         = newjetID

#Reproduce b-tagging (for IVF-CSV)
process.myIVFCombinedSecondaryVertex = process.combinedSecondaryVertex.clone()  #maybe redundant
process.myIVFCombinedSecondaryVertexBJetTags = process.combinedSecondaryVertexBJetTags.clone(
  jetTagComputer = cms.string('combinedSecondaryVertex'),
  tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"),
                           cms.InputTag("inclusiveSecondaryVertexFinderTagInfos"))
)
process.myIVFbtagging = cms.Sequence(
    process.myIVFCombinedSecondaryVertexBJetTags
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

process.source = cms.Source("PoolSource",
#	fileNames = cms.untracked.vstring('file:testTagInfos.root')
	fileNames = cms.untracked.vstring(
'/store/mc/Summer12_DR53X/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FED775BD-B8E1-E111-8ED5-003048C69036.root'
	)
)


process.combinedSVMVATrainer = cms.EDAnalyzer("JetTagMVAExtractor",
	variables = cms.untracked.VPSet(
		cms.untracked.PSet( label = cms.untracked.string("CombinedSVRecoVertex"),  variables=cms.untracked.vstring(
"jetPt","jetEta","vertexCategory","trackSip2dSig","trackSip3dSig","trackSip2dVal","trackSip3dVal","trackMomentum","trackEta","trackPtRel","trackPPar","trackEtaRel","trackDeltaR","trackPtRatio","trackPParRatio","trackJetDist","trackDecayLenVal","trackDecayLenSig","vertexMass","vertexNTracks","vertexEnergyRatio","trackSip2dSigAboveCharm","trackSip3dSigAboveCharm","flightDistance2dSig","flightDistance3dSig","flightDistance2dVal","flightDistance3dVal","trackSumJetEtRatio","jetNSecondaryVertices","vertexJetDeltaR","trackSumJetDeltaR"
)),
		cms.untracked.PSet( label = cms.untracked.string("CombinedSVPseudoVertex"),  variables=cms.untracked.vstring(
"jetPt","jetEta","vertexCategory","trackSip2dSig","trackSip3dSig","trackSip2dVal","trackSip3dVal","trackMomentum","trackEta","trackPtRel","trackPPar","trackEtaRel","trackDeltaR","trackPtRatio","trackPParRatio","trackJetDist","trackDecayLenVal","trackDecayLenSig","vertexMass","vertexNTracks","vertexEnergyRatio","trackSip2dSigAboveCharm","trackSip3dSigAboveCharm","trackSumJetEtRatio","vertexJetDeltaR","trackSumJetDeltaR"
)),

		cms.untracked.PSet( label = cms.untracked.string("CombinedSVNoVertex"),  variables=cms.untracked.vstring(
"jetPt","jetEta","vertexCategory","trackSip2dSig","trackSip3dSig","trackSip2dVal","trackSip3dVal","trackMomentum","trackEta","trackPtRel","trackPPar","trackEtaRel","trackDeltaR","trackPtRatio","trackPParRatio","trackJetDist","trackDecayLenVal","trackDecayLenSig","trackSip2dSigAboveCharm","trackSip3dSigAboveCharm","trackSumJetEtRatio","trackSumJetDeltaR"
))


	),
	ipTagInfos = cms.InputTag("impactParameterTagInfos"),
	#svTagInfos =cms.InputTag("secondaryVertexTagInfos"),
	svTagInfos =cms.InputTag("inclusiveSecondaryVertexFinderTagInfos"),
	
	minimumTransverseMomentum = cms.double(15.0),
	maximumTransverseMomentum = cms.double(9999999.),
	useCategories = cms.bool(True),
        calibrationRecords = cms.vstring(
                'CombinedSVRecoVertex',
                'CombinedSVPseudoVertex',
                'CombinedSVNoVertex'),
	categoryVariableName = cms.string('vertexCategory'), # vertexCategory = Reco,Pseudo,No
	maximumPseudoRapidity = cms.double(2.5),
	signalFlavours = cms.vint32(5, 7),
	minimumPseudoRapidity = cms.double(0.0),
	jetTagComputer = cms.string('combinedSecondaryVertex'),
	jetFlavourMatching = cms.InputTag("AK5byValAlgo"),
	ignoreFlavours = cms.vint32(0)
)

process.p = cms.Path(
process.goodOfflinePrimaryVertices * 
process.JECAlgo * 
process.inclusiveVertexing * 
#process.inclusiveMergedVerticesFiltered * 
#process.bToCharmDecayVertexMerged * 
process.myak5JetTracksAssociatorAtVertex * 
process.impactParameterTagInfos * 
process.inclusiveSecondaryVertexFinderTagInfos *
process.flavourSeq * 
process.myIVFbtagging *  
process.combinedSVMVATrainer 
)

 
