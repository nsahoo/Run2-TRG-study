from FWCore.ParameterSet.VarParsing import VarParsing
opt = VarParsing ('analysis')
opt.parseArguments()

#outFileName = opt.outputFile
outFileName = 'Onia2MuMuPAT-mc.root'
#inFileNames = opt.inputFiles
inFileNames = '/store/relval/CMSSW_7_4_6_patch1/RelValBuJpsiK_13/GEN-SIM-RECO/MCRUN2_74_V9-v1/00000/7C57573C-891E-E511-A5FE-0025905A611C.root','/store/relval/CMSSW_7_4_6_patch1/RelValBuJpsiK_13/GEN-SIM-RECO/MCRUN2_74_V9-v1/00000/92DDC045-891E-E511-8DC8-0025905A6134.root'
nEvents = -1
#Global_Tag  = 'auto:run2_mc'
Global_Tag  = 'MCRUN2_74_V9'
MC          = True
Filter      = True

import FWCore.ParameterSet.Config as cms
process = cms.Process('PAT')

from HeavyFlavorAnalysis.Skimming.CompactSkim_cff import CompactSkim
CompactSkim(process,inFileNames,outFileName,nEvents,Global_Tag,MC,Filter)
