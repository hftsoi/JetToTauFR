import ROOT
import re
from array import array
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--tes', default="nominal", choices=['nominal', 'up', 'down'], help="TES?")
parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Year?")
options = parser.parse_args()

hist=["hpt_dmall_VLe_Tmu_deepveryveryveryloose","hpt_dmall_VLe_Tmu_deepmedium","hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose","hpt_dmall_VLe_Tmu_bjet_deepmedium","hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose","hpt_dmall_VLe_Tmu_1jet_deepmedium","hpt_dmall_Te_VLmu_deepveryveryveryloose","hpt_dmall_Te_VLmu_deepmedium","hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose","hpt_dmall_Te_VLmu_bjet_deepmedium","hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose","hpt_dmall_Te_VLmu_1jet_deepmedium"]

fileData=ROOT.TFile("files_mmt_"+options.year+"/data_obs.root","r")
fileVV=ROOT.TFile("files_mmt_"+options.year+"/VV.root","r")
fileDataSub=ROOT.TFile("files_mmt_"+options.year+"/DataSub.root","recreate")

for i in range(len(hist)):
   print hist[i]
   Data=fileData.Get(hist[i])
   print Data.Integral()
   Data.Add(fileVV.Get(hist[i]),-1)
   Data.SetName(hist[i])
   fileDataSub.cd()
   Data.Write()

