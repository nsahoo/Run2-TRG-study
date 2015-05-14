import FWCore.ParameterSet.Config as cms

process = cms.Process("testHLT")

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MCRUN2_74_V7')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
                            skipEvents = cms.untracked.uint32( 0 ),

                            fileNames = cms.untracked.vstring( 
#                            '/store/relval/CMSSW_7_4_0_pre5/RelValBuJpsiK_13/GEN-SIM-RECO/MCRUN2_73_V7-v1/00000/F0B65CB2-F79D-E411-8A04-002618943842.root'
                            '/store/mc/Phys14DR/TT_Tune4C_13TeV-pythia8-tauola/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/00000/007B37D4-8B70-E411-BC2D-0025905A6066.root'
                            )
)


process.demo = cms.EDAnalyzer("HLTEffAnalyzer",
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    muons = cms.InputTag("slimmedMuons"),
)

process.p = cms.Path(process.demo)
