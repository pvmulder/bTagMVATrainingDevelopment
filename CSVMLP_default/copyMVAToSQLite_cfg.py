import FWCore.ParameterSet.Config as cms

process = cms.Process("MVAJetTagsSQLiteSave")

process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.calib = cms.ESSource("BTauGenericMVAJetTagComputerFileSource",
#	ImpactParameterMVA = cms.string('ImpactParameterMVA.mva'), 
#	CombinedMVA = cms.string('CombinedMVA.mva'),
#	CombinedSVRecoVertex = cms.string('../../../../../../../CMSSW_5_3_4_patch1/src/CombinedSVRecoVertex_2HighPtBins.mva'), 
#	CombinedSVPseudoVertex = cms.string('../../../../../../../CMSSW_5_3_4_patch1/src/CombinedSVPseudoVertex_2HighPtBins.mva'), 
#	CombinedSVNoVertex = cms.string('../../../../../../../CMSSW_5_3_4_patch1/src/CombinedSVNoVertex_2HighPtBins.mva'), 
	CombinedSVMVARecoVertex = cms.string('tmpRecoVertex/CombinedSVMVA_RecoVertex.mva'), 
	CombinedSVMVAPseudoVertex = cms.string('tmpPseudoVertex/CombinedSVMVA_PseudoVertex.mva'), 
	CombinedSVMVANoVertex = cms.string('tmpNoVertex/CombinedSVMVA_NoVertex.mva')
)

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
	BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService'),
	DBParameters = cms.PSet( messageLevel = cms.untracked.int32(0) ),
	timetype = cms.untracked.string('runnumber'),
	connect = cms.string('sqlite_file:MVAJetTags_CSVMVA_20k_eachptetabin_weights_wofactor_bestsofar_CombLinearNew.db'),
	toPut = cms.VPSet(cms.PSet(
		record = cms.string('BTauGenericMVAJetTagComputerRcd'),
		tag = cms.string('MVAJetTags_CMSSW_5_3_4')
	))
)

process.jetTagMVATrainerSave = cms.EDAnalyzer("JetTagMVATrainerSave",
	toPut = cms.vstring(),
	toCopy = cms.vstring(
#		'ImpactParameterMVA', 
#		'CombinedMVA', 
#		'CombinedSVRecoVertex', 
#		'CombinedSVPseudoVertex', 
#		'CombinedSVNoVertex', 
		'CombinedSVMVARecoVertex', 
		'CombinedSVMVAPseudoVertex', 
		'CombinedSVMVANoVertex'
	)
)

process.outpath = cms.EndPath(process.jetTagMVATrainerSave)
