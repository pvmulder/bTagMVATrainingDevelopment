import FWCore.ParameterSet.Config as cms

process = cms.Process("IPTrainer")

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))

process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.combinedSVTrainer = cms.EDAnalyzer("JetTagMVATreeTrainer",
	useCategories		= cms.bool(False),
	calibrationRecord	= cms.string("CombinedSVNoVertex"),
	ignoreFlavours		= cms.vint32(0, 1, 2, 3, 21),
	signalFlavours		= cms.vint32(5, 7),
	minimumTransverseMomentum = cms.double(10.0),
	minimumPseudoRapidity	= cms.double(0),
	maximumPseudoRapidity	= cms.double(2.5),

	factor = cms.double(50),
	bound = cms.double(50),

	fileNames = cms.vstring(
		"CombinedSVNoVertex_B.root",
		"CombinedSVNoVertex_C.root"
	),
	weightFile = cms.string("weights/CombinedSVNoVertex_BC_histo.txt"),
	biasFiles = cms.vstring(
		"-",
		"*",
		"weights/CombinedSVNoVertex_B_C_ratio.txt"
	)
)

process.looper = cms.Looper("JetTagMVATrainerLooper",
	trainers = cms.VPSet(
		cms.PSet(
			calibrationRecord = cms.string("CombinedSVNoVertex"),
			trainDescription = cms.untracked.string("Save_No_B_C.xml"),
			loadState = cms.untracked.bool(False),
			saveState = cms.untracked.bool(False)
		)
	)
)

process.p = cms.Path(process.combinedSVTrainer)
