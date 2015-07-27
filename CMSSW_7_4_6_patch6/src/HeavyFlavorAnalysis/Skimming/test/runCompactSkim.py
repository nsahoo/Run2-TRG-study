from FWCore.ParameterSet.VarParsing import VarParsing
opt = VarParsing ('analysis')
opt.parseArguments()

#outFileName = opt.outputFile
outFileName = 'Onia2MuMuPAT-Run2015B.root'
#inFileNames = opt.inputFiles
inFileNames = '/store/data/Run2015B/MuOnia/AOD/PromptReco-v1/000/251/168/00000/04916A37-CF26-E511-8DCD-02163E013406.root'
#Global_Tag  = 'auto:run2_mc'
Global_Tag  = '74X_dataRun2_Prompt_v0'
MC          = False
Filter      = True

import FWCore.ParameterSet.Config as cms
process = cms.Process('PAT')

from HeavyFlavorAnalysis.Skimming.CompactSkim_cff import CompactSkim
CompactSkim(process,inFileNames,outFileName,Global_Tag,MC,Filter)
