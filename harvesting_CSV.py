import FWCore.ParameterSet.Config as cms

process = cms.Process("harvesting")

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.EDMtoMEAtRunEnd_cff')
process.load('Configuration.StandardSequences.Harvesting_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.MessageLogger.cerr.threshold = 'ERROR'

# for the conditions
from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = autoCond['startup']

# Open and read list file
#filename = open('RootFiles/list.list', 'r')
#filelist = cms.untracked.vstring( filename.readlines() )

# Input source
process.source = cms.Source("PoolSource",
  #fileNames = filelist,
  fileNames = cms.untracked.vstring(
	 'file:DQMfile_1_1_Mgj.root', 'file:DQMfile_2_1_4KG.root', 'file:DQMfile_3_1_43d.root', 'file:DQMfile_4_1_FmM.root', 'file:DQMfile_5_1_9vO.root'
#'file:/afs/cern.ch/work/p/pvmulder/public/BTagging/FINAL_NOSPIKES/CMSSW_5_3_4_patch1/src/CrabJobs/TEST/',
#'file:/afs/cern.ch/work/s/sdevissc/SoftLeptonBTag/CMSSW_5_3_9/src/crab_0_130412_003957/res/DQMfile_204_1_NpH.root',
#'file:/afs/cern.ch/work/s/sdevissc/SoftLeptonBTag/CMSSW_5_3_9/src/crab_0_130412_003957/res/DQMfile_220_1_tcg.root',
),
  secondaryFileNames = cms.untracked.vstring(),
  processingMode = cms.untracked.string('RunsAndLumis')
)


process.options = cms.untracked.PSet(
  Rethrow = cms.untracked.vstring('ProductNotFound'),
  fileMode = cms.untracked.string('FULLMERGE')
)

from DQMOffline.RecoB.bTagCommon_cff import*
process.load("DQMOffline.RecoB.bTagCommon_cff")
#process.bTagCommonBlock.ptRecJetMin = cms.double(600.0)
process.bTagCommonBlock.ptRanges = cms.vdouble(0.0,40.0,60.0,90.0, 150.0,400.0,600.0,3000.0)
process.bTagCommonBlock.etaRanges = cms.vdouble(0.0, 1.2, 2.1, 2.4)

###############################################################################################

from Validation.RecoB.bTagAnalysis_cfi import *
process.load("Validation.RecoB.bTagAnalysis_cfi")

process.CustombTagValidation = process.bTagValidation.clone(
    tagConfig = cms.VPSet(
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
        			startEffPur = cms.double(-0.005)
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
)

process.dqmEnv.subSystemFolder = 'BTAG'
process.dqmSaver.producer = 'DQM'
process.dqmSaver.workflow = '/POG/BTAG/BJET'
process.dqmSaver.convention = 'Offline'
process.dqmSaver.saveByRun = cms.untracked.int32(-1)
process.dqmSaver.saveAtJobEnd =cms.untracked.bool(True)
process.dqmSaver.forceRunNumber = cms.untracked.int32(1)

# Path and EndPath definitions
process.edmtome_step = cms.Path(process.EDMtoME)
process.bTagValidation_step = cms.Path(process.CustombTagValidation)
process.dqmsave_step = cms.Path(process.DQMSaver)

# Schedule definition
process.schedule = cms.Schedule(
  process.edmtome_step,
  process.bTagValidation_step,
  process.dqmsave_step
)
