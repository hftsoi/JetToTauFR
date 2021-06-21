#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "myHelper.h"
#include "tr_Tree_tau.h"
#include "ScaleFactor.h"
#include "LumiReweightingStandAlone.h"
#include "btagSF.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);

    float tes=0;
    float year=2016;
    if (argc > 1) {
        tes = atof(argv[5]);
        year = atof(argv[6]);
    }

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("mmt_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(2);

//Normalization os MC samples
    float xs=1.0; float weight=1.0; float luminosity=36330.0;
    if (year==2017) luminosity=41530.0;
    if (year==2018) luminosity=59740.0;
    if (sample=="data_obs"){weight=1.0;}
    else if (sample=="WZ3LNu") {xs=4.43; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L") {xs=1.212; weight=luminosity*xs/ngen;}
    else cout<<"Attention!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);
    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("npv", &npv);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("iso_1", &iso_1);
    arbre->SetBranchAddress("m_1", &m_1);
    arbre->SetBranchAddress("q_1", &q_1);
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("iso_2", &iso_2);
    arbre->SetBranchAddress("id_m_medium_2", &id_m_medium_2);
    arbre->SetBranchAddress("id_m_medium_1", &id_m_medium_1);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("phi_2", &phi_2);
    arbre->SetBranchAddress("q_3", &q_3);
    arbre->SetBranchAddress("pt_3", &pt_3);
    arbre->SetBranchAddress("eta_3", &eta_3);
    arbre->SetBranchAddress("m_3", &m_3);
    arbre->SetBranchAddress("phi_3", &phi_3);

    arbre->SetBranchAddress("Flag_BadChargedCandidateFilter",&Flag_BadChargedCandidateFilter);
    arbre->SetBranchAddress("Flag_BadPFMuonFilter",&Flag_BadPFMuonFilter);
    arbre->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter",&Flag_EcalDeadCellTriggerPrimitiveFilter);
    arbre->SetBranchAddress("Flag_HBHENoiseFilter",&Flag_HBHENoiseFilter);
    arbre->SetBranchAddress("Flag_HBHENoiseIsoFilter",&Flag_HBHENoiseIsoFilter);
    arbre->SetBranchAddress("Flag_eeBadScFilter",&Flag_eeBadScFilter);
    arbre->SetBranchAddress("Flag_goodVertices",&Flag_goodVertices);
    arbre->SetBranchAddress("Flag_globalSuperTightHalo2016Filter",&Flag_globalSuperTightHalo2016Filter);
    arbre->SetBranchAddress("Flag_ecalBadCalibFilter",&Flag_ecalBadCalibFilter);
    arbre->SetBranchAddress("Flag_duplicateMuons",&Flag_duplicateMuons);
    arbre->SetBranchAddress("Flag_badMuons",&Flag_badMuons);
    arbre->SetBranchAddress("Flag_ecalBadCalibReducedMINIAODFilter",&Flag_ecalBadCalibReducedMINIAODFilter);

    arbre->SetBranchAddress("deepVVVLooseVSjet_3",&deepVVVLooseVSjet_3);
    arbre->SetBranchAddress("deepVVLooseVSjet_3",&deepVVLooseVSjet_3);
    arbre->SetBranchAddress("deepVLooseVSjet_3",&deepVLooseVSjet_3);
    arbre->SetBranchAddress("deepLooseVSjet_3",&deepLooseVSjet_3);
    arbre->SetBranchAddress("deepMediumVSjet_3",&deepMediumVSjet_3);
    arbre->SetBranchAddress("deepTightVSjet_3",&deepTightVSjet_3);
    arbre->SetBranchAddress("deepVTightVSjet_3",&deepVTightVSjet_3);
    arbre->SetBranchAddress("deepVVVLooseVSe_3",&deepVVVLooseVSe_3);
    arbre->SetBranchAddress("deepVVLooseVSe_3",&deepVVLooseVSe_3);
    arbre->SetBranchAddress("deepVLooseVSe_3",&deepVLooseVSe_3);
    arbre->SetBranchAddress("deepLooseVSe_3",&deepLooseVSe_3);
    arbre->SetBranchAddress("deepMediumVSe_3",&deepMediumVSe_3);
    arbre->SetBranchAddress("deepTightVSe_3",&deepTightVSe_3);
    arbre->SetBranchAddress("deepVTightVSe_3",&deepVTightVSe_3);
    arbre->SetBranchAddress("deepVLooseVSmu_3",&deepVLooseVSmu_3);
    arbre->SetBranchAddress("deepLooseVSmu_3",&deepLooseVSmu_3);
    arbre->SetBranchAddress("deepMediumVSmu_3",&deepMediumVSmu_3);
    arbre->SetBranchAddress("deepTightVSmu_3",&deepTightVSmu_3);
    arbre->SetBranchAddress("deepVTightVSmu_3",&deepVTightVSmu_3);

    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("njets", &njets);
    arbre->SetBranchAddress("nbtag", &nbtag);
    arbre->SetBranchAddress("jpt_1", &jpt_1);
    arbre->SetBranchAddress("amcatNLO_weight", &amcatNLO_weight);

    arbre->SetBranchAddress("passMu22eta2p1", &passMu22eta2p1);
    arbre->SetBranchAddress("passTkMu22eta2p1", &passTkMu22eta2p1);
    arbre->SetBranchAddress("matchMu22eta2p1_2", &matchMu22eta2p1_2);
    arbre->SetBranchAddress("matchTkMu22eta2p1_2", &matchTkMu22eta2p1_2);
    arbre->SetBranchAddress("matchMu22eta2p1_1", &matchMu22eta2p1_1);
    arbre->SetBranchAddress("matchTkMu22eta2p1_1", &matchTkMu22eta2p1_1);
    arbre->SetBranchAddress("filterMu22eta2p1_2", &filterMu22eta2p1_2);
    arbre->SetBranchAddress("filterTkMu22eta2p1_2", &filterTkMu22eta2p1_2);
    arbre->SetBranchAddress("filterMu22eta2p1_1", &filterMu22eta2p1_1);
    arbre->SetBranchAddress("filterTkMu22eta2p1_1", &filterTkMu22eta2p1_1);
    arbre->SetBranchAddress("passMu24", &passMu24);
    arbre->SetBranchAddress("matchMu24_2", &matchMu24_2);
    arbre->SetBranchAddress("filterMu24_2", &filterMu24_2);
    arbre->SetBranchAddress("matchMu24_1", &matchMu24_1);
    arbre->SetBranchAddress("filterMu24_1", &filterMu24_1);
    arbre->SetBranchAddress("passMu27", &passMu27);
    arbre->SetBranchAddress("matchMu27_2", &matchMu27_2);
    arbre->SetBranchAddress("filterMu27_2", &filterMu27_2);
    arbre->SetBranchAddress("matchMu27_1", &matchMu27_1);
    arbre->SetBranchAddress("filterMu27_1", &filterMu27_1);

    arbre->SetBranchAddress("l3_decayMode",&l3_decayMode);
    arbre->SetBranchAddress("gen_match_1",&gen_match_1);
    arbre->SetBranchAddress("gen_match_2",&gen_match_2);
    arbre->SetBranchAddress("gen_match_3",&gen_match_3);
    arbre->SetBranchAddress("npu",&npu);
    arbre->SetBranchAddress("genpT",&genpT);
    arbre->SetBranchAddress("genM",&genM);
    arbre->SetBranchAddress("pt_top1",&pt_top1);
    arbre->SetBranchAddress("pt_top2",&pt_top2);
    arbre->SetBranchAddress("numGenJets",&numGenJets);
    arbre->SetBranchAddress("bpt_1",&bpt_1);
    arbre->SetBranchAddress("bpt_2",&bpt_2);
    arbre->SetBranchAddress("bflavor_1",&bflavor_1);
    arbre->SetBranchAddress("bflavor_2",&bflavor_2);

    arbre->SetBranchAddress("genweight",&genweight);
    arbre->SetBranchAddress("bweight",&bweight);
    arbre->SetBranchAddress("prefiring_weight",&prefiring_weight);

   float bins0[] = {20,25,30,35,40,50,60,80,100,120,150};
   float bins1[] = {0.0,1.0,1.5,2.0,2.4,2.8,3.2};

   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;
   int  binnum1 = sizeof(bins1)/sizeof(Float_t) - 1;

   TH1F* hpt_dmall_VLe_Tmu_deepveryveryveryloose = new TH1F ("hpt_dmall_VLe_Tmu_deepveryveryveryloose","hpt_dmall_VLe_Tmu_deepveryveryveryloose",binnum0,bins0); hpt_dmall_VLe_Tmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_deepveryveryloose = new TH1F ("hpt_dmall_VLe_Tmu_deepveryveryloose","hpt_dmall_VLe_Tmu_deepveryveryloose",binnum0,bins0); hpt_dmall_VLe_Tmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_deepveryloose = new TH1F ("hpt_dmall_VLe_Tmu_deepveryloose","hpt_dmall_VLe_Tmu_deepveryloose",binnum0,bins0); hpt_dmall_VLe_Tmu_deepveryloose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_deeploose = new TH1F ("hpt_dmall_VLe_Tmu_deeploose","hpt_dmall_VLe_Tmu_deeploose",binnum0,bins0); hpt_dmall_VLe_Tmu_deeploose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_deepmedium = new TH1F ("hpt_dmall_VLe_Tmu_deepmedium","hpt_dmall_VLe_Tmu_deepmedium",binnum0,bins0); hpt_dmall_VLe_Tmu_deepmedium->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_deeptight = new TH1F ("hpt_dmall_VLe_Tmu_deeptight","hpt_dmall_VLe_Tmu_deeptight",binnum0,bins0); hpt_dmall_VLe_Tmu_deeptight->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_deepverytight = new TH1F ("hpt_dmall_VLe_Tmu_deepverytight","hpt_dmall_VLe_Tmu_deepverytight",binnum0,bins0); hpt_dmall_VLe_Tmu_deepverytight->Sumw2();

   TH1F* hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose = new TH1F ("hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose","hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose",binnum0,bins0); hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_1jet_deepveryveryloose = new TH1F ("hpt_dmall_VLe_Tmu_1jet_deepveryveryloose","hpt_dmall_VLe_Tmu_1jet_deepveryveryloose",binnum0,bins0); hpt_dmall_VLe_Tmu_1jet_deepveryveryloose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_1jet_deepveryloose = new TH1F ("hpt_dmall_VLe_Tmu_1jet_deepveryloose","hpt_dmall_VLe_Tmu_1jet_deepveryloose",binnum0,bins0); hpt_dmall_VLe_Tmu_1jet_deepveryloose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_1jet_deeploose = new TH1F ("hpt_dmall_VLe_Tmu_1jet_deeploose","hpt_dmall_VLe_Tmu_1jet_deeploose",binnum0,bins0); hpt_dmall_VLe_Tmu_1jet_deeploose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_1jet_deepmedium = new TH1F ("hpt_dmall_VLe_Tmu_1jet_deepmedium","hpt_dmall_VLe_Tmu_1jet_deepmedium",binnum0,bins0); hpt_dmall_VLe_Tmu_1jet_deepmedium->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_1jet_deeptight = new TH1F ("hpt_dmall_VLe_Tmu_1jet_deeptight","hpt_dmall_VLe_Tmu_1jet_deeptight",binnum0,bins0); hpt_dmall_VLe_Tmu_1jet_deeptight->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_1jet_deepverytight = new TH1F ("hpt_dmall_VLe_Tmu_1jet_deepverytight","hpt_dmall_VLe_Tmu_1jet_deepverytight",binnum0,bins0); hpt_dmall_VLe_Tmu_1jet_deepverytight->Sumw2();

   TH1F* hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose = new TH1F ("hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose","hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose",binnum0,bins0); hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_bjet_deepveryveryloose = new TH1F ("hpt_dmall_VLe_Tmu_bjet_deepveryveryloose","hpt_dmall_VLe_Tmu_bjet_deepveryveryloose",binnum0,bins0); hpt_dmall_VLe_Tmu_bjet_deepveryveryloose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_bjet_deepveryloose = new TH1F ("hpt_dmall_VLe_Tmu_bjet_deepveryloose","hpt_dmall_VLe_Tmu_bjet_deepveryloose",binnum0,bins0); hpt_dmall_VLe_Tmu_bjet_deepveryloose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_bjet_deeploose = new TH1F ("hpt_dmall_VLe_Tmu_bjet_deeploose","hpt_dmall_VLe_Tmu_bjet_deeploose",binnum0,bins0); hpt_dmall_VLe_Tmu_bjet_deeploose->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_bjet_deepmedium = new TH1F ("hpt_dmall_VLe_Tmu_bjet_deepmedium","hpt_dmall_VLe_Tmu_bjet_deepmedium",binnum0,bins0); hpt_dmall_VLe_Tmu_bjet_deepmedium->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_bjet_deeptight = new TH1F ("hpt_dmall_VLe_Tmu_bjet_deeptight","hpt_dmall_VLe_Tmu_bjet_deeptight",binnum0,bins0); hpt_dmall_VLe_Tmu_bjet_deeptight->Sumw2();
   TH1F* hpt_dmall_VLe_Tmu_bjet_deepverytight = new TH1F ("hpt_dmall_VLe_Tmu_bjet_deepverytight","hpt_dmall_VLe_Tmu_bjet_deepverytight",binnum0,bins0); hpt_dmall_VLe_Tmu_bjet_deepverytight->Sumw2();

   TH1F* hpt_dmall_Te_VLmu_deepveryveryveryloose = new TH1F ("hpt_dmall_Te_VLmu_deepveryveryveryloose","hpt_dmall_Te_VLmu_deepveryveryveryloose",binnum0,bins0); hpt_dmall_Te_VLmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_deepveryveryloose = new TH1F ("hpt_dmall_Te_VLmu_deepveryveryloose","hpt_dmall_Te_VLmu_deepveryveryloose",binnum0,bins0); hpt_dmall_Te_VLmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_deepveryloose = new TH1F ("hpt_dmall_Te_VLmu_deepveryloose","hpt_dmall_Te_VLmu_deepveryloose",binnum0,bins0); hpt_dmall_Te_VLmu_deepveryloose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_deeploose = new TH1F ("hpt_dmall_Te_VLmu_deeploose","hpt_dmall_Te_VLmu_deeploose",binnum0,bins0); hpt_dmall_Te_VLmu_deeploose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_deepmedium = new TH1F ("hpt_dmall_Te_VLmu_deepmedium","hpt_dmall_Te_VLmu_deepmedium",binnum0,bins0); hpt_dmall_Te_VLmu_deepmedium->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_deeptight = new TH1F ("hpt_dmall_Te_VLmu_deeptight","hpt_dmall_Te_VLmu_deeptight",binnum0,bins0); hpt_dmall_Te_VLmu_deeptight->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_deepverytight = new TH1F ("hpt_dmall_Te_VLmu_deepverytight","hpt_dmall_Te_VLmu_deepverytight",binnum0,bins0); hpt_dmall_Te_VLmu_deepverytight->Sumw2();

   TH1F* hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose = new TH1F ("hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose","hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose",binnum0,bins0); hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_1jet_deepveryveryloose = new TH1F ("hpt_dmall_Te_VLmu_1jet_deepveryveryloose","hpt_dmall_Te_VLmu_1jet_deepveryveryloose",binnum0,bins0); hpt_dmall_Te_VLmu_1jet_deepveryveryloose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_1jet_deepveryloose = new TH1F ("hpt_dmall_Te_VLmu_1jet_deepveryloose","hpt_dmall_Te_VLmu_1jet_deepveryloose",binnum0,bins0); hpt_dmall_Te_VLmu_1jet_deepveryloose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_1jet_deeploose = new TH1F ("hpt_dmall_Te_VLmu_1jet_deeploose","hpt_dmall_Te_VLmu_1jet_deeploose",binnum0,bins0); hpt_dmall_Te_VLmu_1jet_deeploose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_1jet_deepmedium = new TH1F ("hpt_dmall_Te_VLmu_1jet_deepmedium","hpt_dmall_Te_VLmu_1jet_deepmedium",binnum0,bins0); hpt_dmall_Te_VLmu_1jet_deepmedium->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_1jet_deeptight = new TH1F ("hpt_dmall_Te_VLmu_1jet_deeptight","hpt_dmall_Te_VLmu_1jet_deeptight",binnum0,bins0); hpt_dmall_Te_VLmu_1jet_deeptight->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_1jet_deepverytight = new TH1F ("hpt_dmall_Te_VLmu_1jet_deepverytight","hpt_dmall_Te_VLmu_1jet_deepverytight",binnum0,bins0); hpt_dmall_Te_VLmu_1jet_deepverytight->Sumw2();

   TH1F* hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose = new TH1F ("hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose","hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose",binnum0,bins0); hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_bjet_deepveryveryloose = new TH1F ("hpt_dmall_Te_VLmu_bjet_deepveryveryloose","hpt_dmall_Te_VLmu_bjet_deepveryveryloose",binnum0,bins0); hpt_dmall_Te_VLmu_bjet_deepveryveryloose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_bjet_deepveryloose = new TH1F ("hpt_dmall_Te_VLmu_bjet_deepveryloose","hpt_dmall_Te_VLmu_bjet_deepveryloose",binnum0,bins0); hpt_dmall_Te_VLmu_bjet_deepveryloose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_bjet_deeploose = new TH1F ("hpt_dmall_Te_VLmu_bjet_deeploose","hpt_dmall_Te_VLmu_bjet_deeploose",binnum0,bins0); hpt_dmall_Te_VLmu_bjet_deeploose->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_bjet_deepmedium = new TH1F ("hpt_dmall_Te_VLmu_bjet_deepmedium","hpt_dmall_Te_VLmu_bjet_deepmedium",binnum0,bins0); hpt_dmall_Te_VLmu_bjet_deepmedium->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_bjet_deeptight = new TH1F ("hpt_dmall_Te_VLmu_bjet_deeptight","hpt_dmall_Te_VLmu_bjet_deeptight",binnum0,bins0); hpt_dmall_Te_VLmu_bjet_deeptight->Sumw2();
   TH1F* hpt_dmall_Te_VLmu_bjet_deepverytight = new TH1F ("hpt_dmall_Te_VLmu_bjet_deepverytight","hpt_dmall_Te_VLmu_bjet_deepverytight",binnum0,bins0); hpt_dmall_Te_VLmu_bjet_deepverytight->Sumw2();

   TH1F* hpt_dm0_deepveryveryveryloose = new TH1F ("hpt_dm0_deepveryveryveryloose","hpt_dm0_deepveryveryveryloose",binnum0,bins0); hpt_dm0_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm0_deepveryveryloose = new TH1F ("hpt_dm0_deepveryveryloose","hpt_dm0_deepveryveryloose",binnum0,bins0); hpt_dm0_deepveryveryloose->Sumw2();
   TH1F* hpt_dm0_deepveryloose = new TH1F ("hpt_dm0_deepveryloose","hpt_dm0_deepveryloose",binnum0,bins0); hpt_dm0_deepveryloose->Sumw2();
   TH1F* hpt_dm0_deeploose = new TH1F ("hpt_dm0_deeploose","hpt_dm0_deeploose",binnum0,bins0); hpt_dm0_deeploose->Sumw2();
   TH1F* hpt_dm0_deepmedium = new TH1F ("hpt_dm0_deepmedium","hpt_dm0_deepmedium",binnum0,bins0); hpt_dm0_deepmedium->Sumw2();
   TH1F* hpt_dm0_deeptight = new TH1F ("hpt_dm0_deeptight","hpt_dm0_deeptight",binnum0,bins0); hpt_dm0_deeptight->Sumw2();
   TH1F* hpt_dm0_deepverytight = new TH1F ("hpt_dm0_deepverytight","hpt_dm0_deepverytight",binnum0,bins0); hpt_dm0_deepverytight->Sumw2();
   TH1F* hpt_dm1_deepveryveryveryloose = new TH1F ("hpt_dm1_deepveryveryveryloose","hpt_dm1_deepveryveryveryloose",binnum0,bins0); hpt_dm1_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm1_deepveryveryloose = new TH1F ("hpt_dm1_deepveryveryloose","hpt_dm1_deepveryveryloose",binnum0,bins0); hpt_dm1_deepveryveryloose->Sumw2();
   TH1F* hpt_dm1_deepveryloose = new TH1F ("hpt_dm1_deepveryloose","hpt_dm1_deepveryloose",binnum0,bins0); hpt_dm1_deepveryloose->Sumw2();
   TH1F* hpt_dm1_deeploose = new TH1F ("hpt_dm1_deeploose","hpt_dm1_deeploose",binnum0,bins0); hpt_dm1_deeploose->Sumw2();
   TH1F* hpt_dm1_deepmedium = new TH1F ("hpt_dm1_deepmedium","hpt_dm1_deepmedium",binnum0,bins0); hpt_dm1_deepmedium->Sumw2();
   TH1F* hpt_dm1_deeptight = new TH1F ("hpt_dm1_deeptight","hpt_dm1_deeptight",binnum0,bins0); hpt_dm1_deeptight->Sumw2();
   TH1F* hpt_dm1_deepverytight = new TH1F ("hpt_dm1_deepverytight","hpt_dm1_deepverytight",binnum0,bins0); hpt_dm1_deepverytight->Sumw2();
   TH1F* hpt_dm10_deepveryveryveryloose = new TH1F ("hpt_dm10_deepveryveryveryloose","hpt_dm10_deepveryveryveryloose",binnum0,bins0); hpt_dm10_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm10_deepveryveryloose = new TH1F ("hpt_dm10_deepveryveryloose","hpt_dm10_deepveryveryloose",binnum0,bins0); hpt_dm10_deepveryveryloose->Sumw2();
   TH1F* hpt_dm10_deepveryloose = new TH1F ("hpt_dm10_deepveryloose","hpt_dm10_deepveryloose",binnum0,bins0); hpt_dm10_deepveryloose->Sumw2();
   TH1F* hpt_dm10_deeploose = new TH1F ("hpt_dm10_deeploose","hpt_dm10_deeploose",binnum0,bins0); hpt_dm10_deeploose->Sumw2();
   TH1F* hpt_dm10_deepmedium = new TH1F ("hpt_dm10_deepmedium","hpt_dm10_deepmedium",binnum0,bins0); hpt_dm10_deepmedium->Sumw2();
   TH1F* hpt_dm10_deeptight = new TH1F ("hpt_dm10_deeptight","hpt_dm10_deeptight",binnum0,bins0); hpt_dm10_deeptight->Sumw2();
   TH1F* hpt_dm10_deepverytight = new TH1F ("hpt_dm10_deepverytight","hpt_dm10_deepverytight",binnum0,bins0); hpt_dm10_deepverytight->Sumw2();
   TH1F* hpt_dm11_deepveryveryveryloose = new TH1F ("hpt_dm11_deepveryveryveryloose","hpt_dm11_deepveryveryveryloose",binnum0,bins0); hpt_dm11_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm11_deepveryveryloose = new TH1F ("hpt_dm11_deepveryveryloose","hpt_dm11_deepveryveryloose",binnum0,bins0); hpt_dm11_deepveryveryloose->Sumw2();
   TH1F* hpt_dm11_deepveryloose = new TH1F ("hpt_dm11_deepveryloose","hpt_dm11_deepveryloose",binnum0,bins0); hpt_dm11_deepveryloose->Sumw2();
   TH1F* hpt_dm11_deeploose = new TH1F ("hpt_dm11_deeploose","hpt_dm11_deeploose",binnum0,bins0); hpt_dm11_deeploose->Sumw2();
   TH1F* hpt_dm11_deepmedium = new TH1F ("hpt_dm11_deepmedium","hpt_dm11_deepmedium",binnum0,bins0); hpt_dm11_deepmedium->Sumw2();
   TH1F* hpt_dm11_deeptight = new TH1F ("hpt_dm11_deeptight","hpt_dm11_deeptight",binnum0,bins0); hpt_dm11_deeptight->Sumw2();
   TH1F* hpt_dm11_deepverytight = new TH1F ("hpt_dm11_deepverytight","hpt_dm11_deepverytight",binnum0,bins0); hpt_dm11_deepverytight->Sumw2();

   TH1F* hpt_dm0_Te_Tmu_deepveryveryveryloose = new TH1F ("hpt_dm0_Te_Tmu_deepveryveryveryloose","hpt_dm0_Te_Tmu_deepveryveryveryloose",binnum0,bins0); hpt_dm0_Te_Tmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm0_Te_Tmu_deepveryveryloose = new TH1F ("hpt_dm0_Te_Tmu_deepveryveryloose","hpt_dm0_Te_Tmu_deepveryveryloose",binnum0,bins0); hpt_dm0_Te_Tmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm0_Te_Tmu_deepveryloose = new TH1F ("hpt_dm0_Te_Tmu_deepveryloose","hpt_dm0_Te_Tmu_deepveryloose",binnum0,bins0); hpt_dm0_Te_Tmu_deepveryloose->Sumw2();
   TH1F* hpt_dm0_Te_Tmu_deeploose = new TH1F ("hpt_dm0_Te_Tmu_deeploose","hpt_dm0_Te_Tmu_deeploose",binnum0,bins0); hpt_dm0_Te_Tmu_deeploose->Sumw2();
   TH1F* hpt_dm0_Te_Tmu_deepmedium = new TH1F ("hpt_dm0_Te_Tmu_deepmedium","hpt_dm0_Te_Tmu_deepmedium",binnum0,bins0); hpt_dm0_Te_Tmu_deepmedium->Sumw2();
   TH1F* hpt_dm0_Te_Tmu_deeptight = new TH1F ("hpt_dm0_Te_Tmu_deeptight","hpt_dm0_Te_Tmu_deeptight",binnum0,bins0); hpt_dm0_Te_Tmu_deeptight->Sumw2();
   TH1F* hpt_dm0_Te_Tmu_deepverytight = new TH1F ("hpt_dm0_Te_Tmu_deepverytight","hpt_dm0_Te_Tmu_deepverytight",binnum0,bins0); hpt_dm0_Te_Tmu_deepverytight->Sumw2();
   TH1F* hpt_dm1_Te_Tmu_deepveryveryveryloose = new TH1F ("hpt_dm1_Te_Tmu_deepveryveryveryloose","hpt_dm1_Te_Tmu_deepveryveryveryloose",binnum0,bins0); hpt_dm1_Te_Tmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm1_Te_Tmu_deepveryveryloose = new TH1F ("hpt_dm1_Te_Tmu_deepveryveryloose","hpt_dm1_Te_Tmu_deepveryveryloose",binnum0,bins0); hpt_dm1_Te_Tmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm1_Te_Tmu_deepveryloose = new TH1F ("hpt_dm1_Te_Tmu_deepveryloose","hpt_dm1_Te_Tmu_deepveryloose",binnum0,bins0); hpt_dm1_Te_Tmu_deepveryloose->Sumw2();
   TH1F* hpt_dm1_Te_Tmu_deeploose = new TH1F ("hpt_dm1_Te_Tmu_deeploose","hpt_dm1_Te_Tmu_deeploose",binnum0,bins0); hpt_dm1_Te_Tmu_deeploose->Sumw2();
   TH1F* hpt_dm1_Te_Tmu_deepmedium = new TH1F ("hpt_dm1_Te_Tmu_deepmedium","hpt_dm1_Te_Tmu_deepmedium",binnum0,bins0); hpt_dm1_Te_Tmu_deepmedium->Sumw2();
   TH1F* hpt_dm1_Te_Tmu_deeptight = new TH1F ("hpt_dm1_Te_Tmu_deeptight","hpt_dm1_Te_Tmu_deeptight",binnum0,bins0); hpt_dm1_Te_Tmu_deeptight->Sumw2();
   TH1F* hpt_dm1_Te_Tmu_deepverytight = new TH1F ("hpt_dm1_Te_Tmu_deepverytight","hpt_dm1_Te_Tmu_deepverytight",binnum0,bins0); hpt_dm1_Te_Tmu_deepverytight->Sumw2();
   TH1F* hpt_dm10_Te_Tmu_deepveryveryveryloose = new TH1F ("hpt_dm10_Te_Tmu_deepveryveryveryloose","hpt_dm10_Te_Tmu_deepveryveryveryloose",binnum0,bins0); hpt_dm10_Te_Tmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm10_Te_Tmu_deepveryveryloose = new TH1F ("hpt_dm10_Te_Tmu_deepveryveryloose","hpt_dm10_Te_Tmu_deepveryveryloose",binnum0,bins0); hpt_dm10_Te_Tmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm10_Te_Tmu_deepveryloose = new TH1F ("hpt_dm10_Te_Tmu_deepveryloose","hpt_dm10_Te_Tmu_deepveryloose",binnum0,bins0); hpt_dm10_Te_Tmu_deepveryloose->Sumw2();
   TH1F* hpt_dm10_Te_Tmu_deeploose = new TH1F ("hpt_dm10_Te_Tmu_deeploose","hpt_dm10_Te_Tmu_deeploose",binnum0,bins0); hpt_dm10_Te_Tmu_deeploose->Sumw2();
   TH1F* hpt_dm10_Te_Tmu_deepmedium = new TH1F ("hpt_dm10_Te_Tmu_deepmedium","hpt_dm10_Te_Tmu_deepmedium",binnum0,bins0); hpt_dm10_Te_Tmu_deepmedium->Sumw2();
   TH1F* hpt_dm10_Te_Tmu_deeptight = new TH1F ("hpt_dm10_Te_Tmu_deeptight","hpt_dm10_Te_Tmu_deeptight",binnum0,bins0); hpt_dm10_Te_Tmu_deeptight->Sumw2();
   TH1F* hpt_dm10_Te_Tmu_deepverytight = new TH1F ("hpt_dm10_Te_Tmu_deepverytight","hpt_dm10_Te_Tmu_deepverytight",binnum0,bins0); hpt_dm10_Te_Tmu_deepverytight->Sumw2();
   TH1F* hpt_dm11_Te_Tmu_deepveryveryveryloose = new TH1F ("hpt_dm11_Te_Tmu_deepveryveryveryloose","hpt_dm11_Te_Tmu_deepveryveryveryloose",binnum0,bins0); hpt_dm11_Te_Tmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm11_Te_Tmu_deepveryveryloose = new TH1F ("hpt_dm11_Te_Tmu_deepveryveryloose","hpt_dm11_Te_Tmu_deepveryveryloose",binnum0,bins0); hpt_dm11_Te_Tmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm11_Te_Tmu_deepveryloose = new TH1F ("hpt_dm11_Te_Tmu_deepveryloose","hpt_dm11_Te_Tmu_deepveryloose",binnum0,bins0); hpt_dm11_Te_Tmu_deepveryloose->Sumw2();
   TH1F* hpt_dm11_Te_Tmu_deeploose = new TH1F ("hpt_dm11_Te_Tmu_deeploose","hpt_dm11_Te_Tmu_deeploose",binnum0,bins0); hpt_dm11_Te_Tmu_deeploose->Sumw2();
   TH1F* hpt_dm11_Te_Tmu_deepmedium = new TH1F ("hpt_dm11_Te_Tmu_deepmedium","hpt_dm11_Te_Tmu_deepmedium",binnum0,bins0); hpt_dm11_Te_Tmu_deepmedium->Sumw2();
   TH1F* hpt_dm11_Te_Tmu_deeptight = new TH1F ("hpt_dm11_Te_Tmu_deeptight","hpt_dm11_Te_Tmu_deeptight",binnum0,bins0); hpt_dm11_Te_Tmu_deeptight->Sumw2();
   TH1F* hpt_dm11_Te_Tmu_deepverytight = new TH1F ("hpt_dm11_Te_Tmu_deepverytight","hpt_dm11_Te_Tmu_deepverytight",binnum0,bins0); hpt_dm11_Te_Tmu_deepverytight->Sumw2();

   TH1F* hpt_dm0_VLe_Tmu_deepveryveryveryloose = new TH1F ("hpt_dm0_VLe_Tmu_deepveryveryveryloose","hpt_dm0_VLe_Tmu_deepveryveryveryloose",binnum0,bins0); hpt_dm0_VLe_Tmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm0_VLe_Tmu_deepveryveryloose = new TH1F ("hpt_dm0_VLe_Tmu_deepveryveryloose","hpt_dm0_VLe_Tmu_deepveryveryloose",binnum0,bins0); hpt_dm0_VLe_Tmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm0_VLe_Tmu_deepveryloose = new TH1F ("hpt_dm0_VLe_Tmu_deepveryloose","hpt_dm0_VLe_Tmu_deepveryloose",binnum0,bins0); hpt_dm0_VLe_Tmu_deepveryloose->Sumw2();
   TH1F* hpt_dm0_VLe_Tmu_deeploose = new TH1F ("hpt_dm0_VLe_Tmu_deeploose","hpt_dm0_VLe_Tmu_deeploose",binnum0,bins0); hpt_dm0_VLe_Tmu_deeploose->Sumw2();
   TH1F* hpt_dm0_VLe_Tmu_deepmedium = new TH1F ("hpt_dm0_VLe_Tmu_deepmedium","hpt_dm0_VLe_Tmu_deepmedium",binnum0,bins0); hpt_dm0_VLe_Tmu_deepmedium->Sumw2();
   TH1F* hpt_dm0_VLe_Tmu_deeptight = new TH1F ("hpt_dm0_VLe_Tmu_deeptight","hpt_dm0_VLe_Tmu_deeptight",binnum0,bins0); hpt_dm0_VLe_Tmu_deeptight->Sumw2();
   TH1F* hpt_dm0_VLe_Tmu_deepverytight = new TH1F ("hpt_dm0_VLe_Tmu_deepverytight","hpt_dm0_VLe_Tmu_deepverytight",binnum0,bins0); hpt_dm0_VLe_Tmu_deepverytight->Sumw2();
   TH1F* hpt_dm1_VLe_Tmu_deepveryveryveryloose = new TH1F ("hpt_dm1_VLe_Tmu_deepveryveryveryloose","hpt_dm1_VLe_Tmu_deepveryveryveryloose",binnum0,bins0); hpt_dm1_VLe_Tmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm1_VLe_Tmu_deepveryveryloose = new TH1F ("hpt_dm1_VLe_Tmu_deepveryveryloose","hpt_dm1_VLe_Tmu_deepveryveryloose",binnum0,bins0); hpt_dm1_VLe_Tmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm1_VLe_Tmu_deepveryloose = new TH1F ("hpt_dm1_VLe_Tmu_deepveryloose","hpt_dm1_VLe_Tmu_deepveryloose",binnum0,bins0); hpt_dm1_VLe_Tmu_deepveryloose->Sumw2();
   TH1F* hpt_dm1_VLe_Tmu_deeploose = new TH1F ("hpt_dm1_VLe_Tmu_deeploose","hpt_dm1_VLe_Tmu_deeploose",binnum0,bins0); hpt_dm1_VLe_Tmu_deeploose->Sumw2();
   TH1F* hpt_dm1_VLe_Tmu_deepmedium = new TH1F ("hpt_dm1_VLe_Tmu_deepmedium","hpt_dm1_VLe_Tmu_deepmedium",binnum0,bins0); hpt_dm1_VLe_Tmu_deepmedium->Sumw2();
   TH1F* hpt_dm1_VLe_Tmu_deeptight = new TH1F ("hpt_dm1_VLe_Tmu_deeptight","hpt_dm1_VLe_Tmu_deeptight",binnum0,bins0); hpt_dm1_VLe_Tmu_deeptight->Sumw2();
   TH1F* hpt_dm1_VLe_Tmu_deepverytight = new TH1F ("hpt_dm1_VLe_Tmu_deepverytight","hpt_dm1_VLe_Tmu_deepverytight",binnum0,bins0); hpt_dm1_VLe_Tmu_deepverytight->Sumw2();
   TH1F* hpt_dm10_VLe_Tmu_deepveryveryveryloose = new TH1F ("hpt_dm10_VLe_Tmu_deepveryveryveryloose","hpt_dm10_VLe_Tmu_deepveryveryveryloose",binnum0,bins0); hpt_dm10_VLe_Tmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm10_VLe_Tmu_deepveryveryloose = new TH1F ("hpt_dm10_VLe_Tmu_deepveryveryloose","hpt_dm10_VLe_Tmu_deepveryveryloose",binnum0,bins0); hpt_dm10_VLe_Tmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm10_VLe_Tmu_deepveryloose = new TH1F ("hpt_dm10_VLe_Tmu_deepveryloose","hpt_dm10_VLe_Tmu_deepveryloose",binnum0,bins0); hpt_dm10_VLe_Tmu_deepveryloose->Sumw2();
   TH1F* hpt_dm10_VLe_Tmu_deeploose = new TH1F ("hpt_dm10_VLe_Tmu_deeploose","hpt_dm10_VLe_Tmu_deeploose",binnum0,bins0); hpt_dm10_VLe_Tmu_deeploose->Sumw2();
   TH1F* hpt_dm10_VLe_Tmu_deepmedium = new TH1F ("hpt_dm10_VLe_Tmu_deepmedium","hpt_dm10_VLe_Tmu_deepmedium",binnum0,bins0); hpt_dm10_VLe_Tmu_deepmedium->Sumw2();
   TH1F* hpt_dm10_VLe_Tmu_deeptight = new TH1F ("hpt_dm10_VLe_Tmu_deeptight","hpt_dm10_VLe_Tmu_deeptight",binnum0,bins0); hpt_dm10_VLe_Tmu_deeptight->Sumw2();
   TH1F* hpt_dm10_VLe_Tmu_deepverytight = new TH1F ("hpt_dm10_VLe_Tmu_deepverytight","hpt_dm10_VLe_Tmu_deepverytight",binnum0,bins0); hpt_dm10_VLe_Tmu_deepverytight->Sumw2();
   TH1F* hpt_dm11_VLe_Tmu_deepveryveryveryloose = new TH1F ("hpt_dm11_VLe_Tmu_deepveryveryveryloose","hpt_dm11_VLe_Tmu_deepveryveryveryloose",binnum0,bins0); hpt_dm11_VLe_Tmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm11_VLe_Tmu_deepveryveryloose = new TH1F ("hpt_dm11_VLe_Tmu_deepveryveryloose","hpt_dm11_VLe_Tmu_deepveryveryloose",binnum0,bins0); hpt_dm11_VLe_Tmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm11_VLe_Tmu_deepveryloose = new TH1F ("hpt_dm11_VLe_Tmu_deepveryloose","hpt_dm11_VLe_Tmu_deepveryloose",binnum0,bins0); hpt_dm11_VLe_Tmu_deepveryloose->Sumw2();
   TH1F* hpt_dm11_VLe_Tmu_deeploose = new TH1F ("hpt_dm11_VLe_Tmu_deeploose","hpt_dm11_VLe_Tmu_deeploose",binnum0,bins0); hpt_dm11_VLe_Tmu_deeploose->Sumw2();
   TH1F* hpt_dm11_VLe_Tmu_deepmedium = new TH1F ("hpt_dm11_VLe_Tmu_deepmedium","hpt_dm11_VLe_Tmu_deepmedium",binnum0,bins0); hpt_dm11_VLe_Tmu_deepmedium->Sumw2();
   TH1F* hpt_dm11_VLe_Tmu_deeptight = new TH1F ("hpt_dm11_VLe_Tmu_deeptight","hpt_dm11_VLe_Tmu_deeptight",binnum0,bins0); hpt_dm11_VLe_Tmu_deeptight->Sumw2();
   TH1F* hpt_dm11_VLe_Tmu_deepverytight = new TH1F ("hpt_dm11_VLe_Tmu_deepverytight","hpt_dm11_VLe_Tmu_deepverytight",binnum0,bins0); hpt_dm11_VLe_Tmu_deepverytight->Sumw2();

   TH1F* hpt_dm0_Te_VLmu_deepveryveryveryloose = new TH1F ("hpt_dm0_Te_VLmu_deepveryveryveryloose","hpt_dm0_Te_VLmu_deepveryveryveryloose",binnum0,bins0); hpt_dm0_Te_VLmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm0_Te_VLmu_deepveryveryloose = new TH1F ("hpt_dm0_Te_VLmu_deepveryveryloose","hpt_dm0_Te_VLmu_deepveryveryloose",binnum0,bins0); hpt_dm0_Te_VLmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm0_Te_VLmu_deepveryloose = new TH1F ("hpt_dm0_Te_VLmu_deepveryloose","hpt_dm0_Te_VLmu_deepveryloose",binnum0,bins0); hpt_dm0_Te_VLmu_deepveryloose->Sumw2();
   TH1F* hpt_dm0_Te_VLmu_deeploose = new TH1F ("hpt_dm0_Te_VLmu_deeploose","hpt_dm0_Te_VLmu_deeploose",binnum0,bins0); hpt_dm0_Te_VLmu_deeploose->Sumw2();
   TH1F* hpt_dm0_Te_VLmu_deepmedium = new TH1F ("hpt_dm0_Te_VLmu_deepmedium","hpt_dm0_Te_VLmu_deepmedium",binnum0,bins0); hpt_dm0_Te_VLmu_deepmedium->Sumw2();
   TH1F* hpt_dm0_Te_VLmu_deeptight = new TH1F ("hpt_dm0_Te_VLmu_deeptight","hpt_dm0_Te_VLmu_deeptight",binnum0,bins0); hpt_dm0_Te_VLmu_deeptight->Sumw2();
   TH1F* hpt_dm0_Te_VLmu_deepverytight = new TH1F ("hpt_dm0_Te_VLmu_deepverytight","hpt_dm0_Te_VLmu_deepverytight",binnum0,bins0); hpt_dm0_Te_VLmu_deepverytight->Sumw2();
   TH1F* hpt_dm1_Te_VLmu_deepveryveryveryloose = new TH1F ("hpt_dm1_Te_VLmu_deepveryveryveryloose","hpt_dm1_Te_VLmu_deepveryveryveryloose",binnum0,bins0); hpt_dm1_Te_VLmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm1_Te_VLmu_deepveryveryloose = new TH1F ("hpt_dm1_Te_VLmu_deepveryveryloose","hpt_dm1_Te_VLmu_deepveryveryloose",binnum0,bins0); hpt_dm1_Te_VLmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm1_Te_VLmu_deepveryloose = new TH1F ("hpt_dm1_Te_VLmu_deepveryloose","hpt_dm1_Te_VLmu_deepveryloose",binnum0,bins0); hpt_dm1_Te_VLmu_deepveryloose->Sumw2();
   TH1F* hpt_dm1_Te_VLmu_deeploose = new TH1F ("hpt_dm1_Te_VLmu_deeploose","hpt_dm1_Te_VLmu_deeploose",binnum0,bins0); hpt_dm1_Te_VLmu_deeploose->Sumw2();
   TH1F* hpt_dm1_Te_VLmu_deepmedium = new TH1F ("hpt_dm1_Te_VLmu_deepmedium","hpt_dm1_Te_VLmu_deepmedium",binnum0,bins0); hpt_dm1_Te_VLmu_deepmedium->Sumw2();
   TH1F* hpt_dm1_Te_VLmu_deeptight = new TH1F ("hpt_dm1_Te_VLmu_deeptight","hpt_dm1_Te_VLmu_deeptight",binnum0,bins0); hpt_dm1_Te_VLmu_deeptight->Sumw2();
   TH1F* hpt_dm1_Te_VLmu_deepverytight = new TH1F ("hpt_dm1_Te_VLmu_deepverytight","hpt_dm1_Te_VLmu_deepverytight",binnum0,bins0); hpt_dm1_Te_VLmu_deepverytight->Sumw2();
   TH1F* hpt_dm10_Te_VLmu_deepveryveryveryloose = new TH1F ("hpt_dm10_Te_VLmu_deepveryveryveryloose","hpt_dm10_Te_VLmu_deepveryveryveryloose",binnum0,bins0); hpt_dm10_Te_VLmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm10_Te_VLmu_deepveryveryloose = new TH1F ("hpt_dm10_Te_VLmu_deepveryveryloose","hpt_dm10_Te_VLmu_deepveryveryloose",binnum0,bins0); hpt_dm10_Te_VLmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm10_Te_VLmu_deepveryloose = new TH1F ("hpt_dm10_Te_VLmu_deepveryloose","hpt_dm10_Te_VLmu_deepveryloose",binnum0,bins0); hpt_dm10_Te_VLmu_deepveryloose->Sumw2();
   TH1F* hpt_dm10_Te_VLmu_deeploose = new TH1F ("hpt_dm10_Te_VLmu_deeploose","hpt_dm10_Te_VLmu_deeploose",binnum0,bins0); hpt_dm10_Te_VLmu_deeploose->Sumw2();
   TH1F* hpt_dm10_Te_VLmu_deepmedium = new TH1F ("hpt_dm10_Te_VLmu_deepmedium","hpt_dm10_Te_VLmu_deepmedium",binnum0,bins0); hpt_dm10_Te_VLmu_deepmedium->Sumw2();
   TH1F* hpt_dm10_Te_VLmu_deeptight = new TH1F ("hpt_dm10_Te_VLmu_deeptight","hpt_dm10_Te_VLmu_deeptight",binnum0,bins0); hpt_dm10_Te_VLmu_deeptight->Sumw2();
   TH1F* hpt_dm10_Te_VLmu_deepverytight = new TH1F ("hpt_dm10_Te_VLmu_deepverytight","hpt_dm10_Te_VLmu_deepverytight",binnum0,bins0); hpt_dm10_Te_VLmu_deepverytight->Sumw2();
   TH1F* hpt_dm11_Te_VLmu_deepveryveryveryloose = new TH1F ("hpt_dm11_Te_VLmu_deepveryveryveryloose","hpt_dm11_Te_VLmu_deepveryveryveryloose",binnum0,bins0); hpt_dm11_Te_VLmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm11_Te_VLmu_deepveryveryloose = new TH1F ("hpt_dm11_Te_VLmu_deepveryveryloose","hpt_dm11_Te_VLmu_deepveryveryloose",binnum0,bins0); hpt_dm11_Te_VLmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm11_Te_VLmu_deepveryloose = new TH1F ("hpt_dm11_Te_VLmu_deepveryloose","hpt_dm11_Te_VLmu_deepveryloose",binnum0,bins0); hpt_dm11_Te_VLmu_deepveryloose->Sumw2();
   TH1F* hpt_dm11_Te_VLmu_deeploose = new TH1F ("hpt_dm11_Te_VLmu_deeploose","hpt_dm11_Te_VLmu_deeploose",binnum0,bins0); hpt_dm11_Te_VLmu_deeploose->Sumw2();
   TH1F* hpt_dm11_Te_VLmu_deepmedium = new TH1F ("hpt_dm11_Te_VLmu_deepmedium","hpt_dm11_Te_VLmu_deepmedium",binnum0,bins0); hpt_dm11_Te_VLmu_deepmedium->Sumw2();
   TH1F* hpt_dm11_Te_VLmu_deeptight = new TH1F ("hpt_dm11_Te_VLmu_deeptight","hpt_dm11_Te_VLmu_deeptight",binnum0,bins0); hpt_dm11_Te_VLmu_deeptight->Sumw2();
   TH1F* hpt_dm11_Te_VLmu_deepverytight = new TH1F ("hpt_dm11_Te_VLmu_deepverytight","hpt_dm11_Te_VLmu_deepverytight",binnum0,bins0); hpt_dm11_Te_VLmu_deepverytight->Sumw2();

   TH1F* hpt_dm0_VLe_VLmu_deepveryveryveryloose = new TH1F ("hpt_dm0_VLe_VLmu_deepveryveryveryloose","hpt_dm0_VLe_VLmu_deepveryveryveryloose",binnum0,bins0); hpt_dm0_VLe_VLmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm0_VLe_VLmu_deepveryveryloose = new TH1F ("hpt_dm0_VLe_VLmu_deepveryveryloose","hpt_dm0_VLe_VLmu_deepveryveryloose",binnum0,bins0); hpt_dm0_VLe_VLmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm0_VLe_VLmu_deepveryloose = new TH1F ("hpt_dm0_VLe_VLmu_deepveryloose","hpt_dm0_VLe_VLmu_deepveryloose",binnum0,bins0); hpt_dm0_VLe_VLmu_deepveryloose->Sumw2();
   TH1F* hpt_dm0_VLe_VLmu_deeploose = new TH1F ("hpt_dm0_VLe_VLmu_deeploose","hpt_dm0_VLe_VLmu_deeploose",binnum0,bins0); hpt_dm0_VLe_VLmu_deeploose->Sumw2();
   TH1F* hpt_dm0_VLe_VLmu_deepmedium = new TH1F ("hpt_dm0_VLe_VLmu_deepmedium","hpt_dm0_VLe_VLmu_deepmedium",binnum0,bins0); hpt_dm0_VLe_VLmu_deepmedium->Sumw2();
   TH1F* hpt_dm0_VLe_VLmu_deeptight = new TH1F ("hpt_dm0_VLe_VLmu_deeptight","hpt_dm0_VLe_VLmu_deeptight",binnum0,bins0); hpt_dm0_VLe_VLmu_deeptight->Sumw2();
   TH1F* hpt_dm0_VLe_VLmu_deepverytight = new TH1F ("hpt_dm0_VLe_VLmu_deepverytight","hpt_dm0_VLe_VLmu_deepverytight",binnum0,bins0); hpt_dm0_VLe_VLmu_deepverytight->Sumw2();
   TH1F* hpt_dm1_VLe_VLmu_deepveryveryveryloose = new TH1F ("hpt_dm1_VLe_VLmu_deepveryveryveryloose","hpt_dm1_VLe_VLmu_deepveryveryveryloose",binnum0,bins0); hpt_dm1_VLe_VLmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm1_VLe_VLmu_deepveryveryloose = new TH1F ("hpt_dm1_VLe_VLmu_deepveryveryloose","hpt_dm1_VLe_VLmu_deepveryveryloose",binnum0,bins0); hpt_dm1_VLe_VLmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm1_VLe_VLmu_deepveryloose = new TH1F ("hpt_dm1_VLe_VLmu_deepveryloose","hpt_dm1_VLe_VLmu_deepveryloose",binnum0,bins0); hpt_dm1_VLe_VLmu_deepveryloose->Sumw2();
   TH1F* hpt_dm1_VLe_VLmu_deeploose = new TH1F ("hpt_dm1_VLe_VLmu_deeploose","hpt_dm1_VLe_VLmu_deeploose",binnum0,bins0); hpt_dm1_VLe_VLmu_deeploose->Sumw2();
   TH1F* hpt_dm1_VLe_VLmu_deepmedium = new TH1F ("hpt_dm1_VLe_VLmu_deepmedium","hpt_dm1_VLe_VLmu_deepmedium",binnum0,bins0); hpt_dm1_VLe_VLmu_deepmedium->Sumw2();
   TH1F* hpt_dm1_VLe_VLmu_deeptight = new TH1F ("hpt_dm1_VLe_VLmu_deeptight","hpt_dm1_VLe_VLmu_deeptight",binnum0,bins0); hpt_dm1_VLe_VLmu_deeptight->Sumw2();
   TH1F* hpt_dm1_VLe_VLmu_deepverytight = new TH1F ("hpt_dm1_VLe_VLmu_deepverytight","hpt_dm1_VLe_VLmu_deepverytight",binnum0,bins0); hpt_dm1_VLe_VLmu_deepverytight->Sumw2();
   TH1F* hpt_dm10_VLe_VLmu_deepveryveryveryloose = new TH1F ("hpt_dm10_VLe_VLmu_deepveryveryveryloose","hpt_dm10_VLe_VLmu_deepveryveryveryloose",binnum0,bins0); hpt_dm10_VLe_VLmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm10_VLe_VLmu_deepveryveryloose = new TH1F ("hpt_dm10_VLe_VLmu_deepveryveryloose","hpt_dm10_VLe_VLmu_deepveryveryloose",binnum0,bins0); hpt_dm10_VLe_VLmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm10_VLe_VLmu_deepveryloose = new TH1F ("hpt_dm10_VLe_VLmu_deepveryloose","hpt_dm10_VLe_VLmu_deepveryloose",binnum0,bins0); hpt_dm10_VLe_VLmu_deepveryloose->Sumw2();
   TH1F* hpt_dm10_VLe_VLmu_deeploose = new TH1F ("hpt_dm10_VLe_VLmu_deeploose","hpt_dm10_VLe_VLmu_deeploose",binnum0,bins0); hpt_dm10_VLe_VLmu_deeploose->Sumw2();
   TH1F* hpt_dm10_VLe_VLmu_deepmedium = new TH1F ("hpt_dm10_VLe_VLmu_deepmedium","hpt_dm10_VLe_VLmu_deepmedium",binnum0,bins0); hpt_dm10_VLe_VLmu_deepmedium->Sumw2();
   TH1F* hpt_dm10_VLe_VLmu_deeptight = new TH1F ("hpt_dm10_VLe_VLmu_deeptight","hpt_dm10_VLe_VLmu_deeptight",binnum0,bins0); hpt_dm10_VLe_VLmu_deeptight->Sumw2();
   TH1F* hpt_dm10_VLe_VLmu_deepverytight = new TH1F ("hpt_dm10_VLe_VLmu_deepverytight","hpt_dm10_VLe_VLmu_deepverytight",binnum0,bins0); hpt_dm10_VLe_VLmu_deepverytight->Sumw2();
   TH1F* hpt_dm11_VLe_VLmu_deepveryveryveryloose = new TH1F ("hpt_dm11_VLe_VLmu_deepveryveryveryloose","hpt_dm11_VLe_VLmu_deepveryveryveryloose",binnum0,bins0); hpt_dm11_VLe_VLmu_deepveryveryveryloose->Sumw2();
   TH1F* hpt_dm11_VLe_VLmu_deepveryveryloose = new TH1F ("hpt_dm11_VLe_VLmu_deepveryveryloose","hpt_dm11_VLe_VLmu_deepveryveryloose",binnum0,bins0); hpt_dm11_VLe_VLmu_deepveryveryloose->Sumw2();
   TH1F* hpt_dm11_VLe_VLmu_deepveryloose = new TH1F ("hpt_dm11_VLe_VLmu_deepveryloose","hpt_dm11_VLe_VLmu_deepveryloose",binnum0,bins0); hpt_dm11_VLe_VLmu_deepveryloose->Sumw2();
   TH1F* hpt_dm11_VLe_VLmu_deeploose = new TH1F ("hpt_dm11_VLe_VLmu_deeploose","hpt_dm11_VLe_VLmu_deeploose",binnum0,bins0); hpt_dm11_VLe_VLmu_deeploose->Sumw2();
   TH1F* hpt_dm11_VLe_VLmu_deepmedium = new TH1F ("hpt_dm11_VLe_VLmu_deepmedium","hpt_dm11_VLe_VLmu_deepmedium",binnum0,bins0); hpt_dm11_VLe_VLmu_deepmedium->Sumw2();
   TH1F* hpt_dm11_VLe_VLmu_deeptight = new TH1F ("hpt_dm11_VLe_VLmu_deeptight","hpt_dm11_VLe_VLmu_deeptight",binnum0,bins0); hpt_dm11_VLe_VLmu_deeptight->Sumw2();
   TH1F* hpt_dm11_VLe_VLmu_deepverytight = new TH1F ("hpt_dm11_VLe_VLmu_deepverytight","hpt_dm11_VLe_VLmu_deepverytight",binnum0,bins0); hpt_dm11_VLe_VLmu_deepverytight->Sumw2();

   TFile *ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2016Legacy.root");
   if (year==2017) ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2017ReReco.root");
   if (year==2018) ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco.root");
   TF1 *fct_tauid= (TF1*) ftauid->Get("Medium_cent");
   TF1 *fct_tauid_up= (TF1*) ftauid->Get("Medium_up");
   TF1 *fct_tauid_down= (TF1*) ftauid->Get("Medium_down");

   TFile fwmc("htt_scalefactors_legacy_2016.root");
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();
   if (year==2017){
     TFile fwmc("htt_scalefactors_legacy_2017.root");
     wmc = (RooWorkspace*)fwmc.Get("w");
     fwmc.Close();
   }
   if (year==2018){
     TFile fwmc("htt_scalefactors_legacy_2018.root");
     wmc = (RooWorkspace*)fwmc.Get("w");
     fwmc.Close();
   }

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting("MC_Moriond17_PU25ns_V1.root", "Data_Pileup_2016_271036-284044_80bins.root", "pileup", "pileup");
   if (year==2017) LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#VBFHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
   if (year==2018)    LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        bool trigger1=true;
	bool trigger2=true;

	 if (year==2016){
	    trigger1=((passMu22eta2p1 && matchMu22eta2p1_1 && filterMu22eta2p1_1 && pt_1>23 && fabs(eta_1)<2.1) or (passTkMu22eta2p1 && matchTkMu22eta2p1_1 && filterTkMu22eta2p1_1 && pt_1>23 && fabs(eta_1)<2.1));
            trigger2=((passMu22eta2p1 && matchMu22eta2p1_2 && filterMu22eta2p1_2 && pt_2>23 && fabs(eta_2)<2.1) or (passTkMu22eta2p1 && matchTkMu22eta2p1_2 && filterTkMu22eta2p1_2 && pt_2>23 && fabs(eta_2)<2.1));
        }
        if (year==2017){
	   trigger1=((passMu24 && matchMu24_1 && filterMu24_1 && pt_1>25 && fabs(eta_1)<2.1) or (passMu27 && matchMu27_1 && filterMu27_1 && pt_1>25 && fabs(eta_1)<2.1)); 
           trigger2=((passMu24 && matchMu24_2 && filterMu24_2 && pt_2>25 && fabs(eta_2)<2.1) or (passMu27 && matchMu27_2 && filterMu27_2 && pt_2>25 && fabs(eta_2)<2.1));
        }
        if (year==2018){
           trigger1=((passMu24 && matchMu24_1>0 && filterMu24_1>0 && pt_1>25 && fabs(eta_1)<2.1) or (passMu27 && matchMu27_1 && filterMu27_1 && pt_1>25 && fabs(eta_1)<2.1));
           trigger2=((passMu24 && matchMu24_2 && filterMu24_2 && pt_2>25 && fabs(eta_2)<2.1) or (passMu27 && matchMu27_2 && filterMu27_2 && pt_2>25 && fabs(eta_2)<2.1));
        }       
	if (!trigger1 && !trigger2) continue;
 	if (pt_1<10 or pt_2<10) continue;

	// Muon ID
        if (!id_m_medium_2) continue;
        if (!id_m_medium_1) continue;

        /*if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;*/

        TLorentzVector mymu1;
        mymu1.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mymu2;
        mymu2.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);

	if ((mymu1+mymu2).M()<76 or (mymu1+mymu2).M()>106) continue;
	if (q_1*q_2>0) continue;

        TLorentzVector mytau;
        mytau.SetPtEtaPhiM(pt_3,eta_3,phi_3,m_3);


	if (iso_1>0.15 or iso_2>0.15) continue; //Muon isolation
        //if (nbtag>0) continue; //No btagged jet to reduce TT

	//ID and iso corrections

        float aweight=1.0;
 	if (year==2016 and sample!="data_obs"){
          if (deepMediumVSjet_3 && gen_match_3==5) aweight=aweight*fct_tauid->Eval(mytau.Pt());
	  aweight=genweight*weight*LumiWeights_12->weight(npu);
          wmc->var("m_pt")->setVal(mymu1.Pt());
          wmc->var("m_eta")->setVal(mymu1.Eta());
          wmc->var("m_iso")->setVal(iso_1);
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_ratio")->getVal();
          float sftrg1=wmc->function("m_trg_ic_ratio")->getVal();
          wmc->var("m_pt")->setVal(mymu2.Pt());
          wmc->var("m_eta")->setVal(mymu2.Eta());
          wmc->var("m_iso")->setVal(iso_2);
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_ratio")->getVal();
          float sftrg2=wmc->function("m_trg_ic_ratio")->getVal();
	  if (trigger1 && trigger2) aweight=aweight*(1-((1-sftrg1)*(1-sftrg2)));
	  else if (trigger1 && !trigger2) aweight=aweight*sftrg1;
          else if (!trigger1 && trigger2) aweight=aweight*sftrg2;
          //aweight=aweight*prefiring_weight;
          //aweight=aweight*bweight;
        } 
        if (year==2017 and sample!="data_obs"){
          if (deepMediumVSjet_3 && gen_match_3==5) aweight=aweight*fct_tauid->Eval(mytau.Pt());
          aweight=genweight*weight*LumiWeights_12->weight(npu);
          wmc->var("m_pt")->setVal(mymu1.Pt());
          wmc->var("m_eta")->setVal(mymu1.Eta());
          wmc->var("m_iso")->setVal(iso_1);
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_ratio")->getVal();
          float sftrg1=wmc->function("m_trg_ic_ratio")->getVal();
          wmc->var("m_pt")->setVal(mymu2.Pt());
          wmc->var("m_eta")->setVal(mymu2.Eta());
          wmc->var("m_iso")->setVal(iso_2);
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_ratio")->getVal();
          float sftrg2=wmc->function("m_trg_ic_ratio")->getVal();
          if (trigger1 && trigger2) aweight=aweight*(1-((1-sftrg1)*(1-sftrg2)));
          else if (trigger1 && !trigger2) aweight=aweight*sftrg1;
          else if (!trigger1 && trigger2) aweight=aweight*sftrg2;
          //aweight=aweight*prefiring_weight;
          //aweight=aweight*bweight;
        }
        if (year==2018 and sample!="data_obs"){
          if (deepMediumVSjet_3 && gen_match_3==5) aweight=aweight*fct_tauid->Eval(mytau.Pt());
          aweight=genweight*weight*LumiWeights_12->weight(npu);
          wmc->var("m_pt")->setVal(mymu1.Pt());
          wmc->var("m_eta")->setVal(mymu1.Eta());
          wmc->var("m_iso")->setVal(iso_1);
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_ratio")->getVal();
          float sftrg1=wmc->function("m_trg_ic_ratio")->getVal();
          wmc->var("m_pt")->setVal(mymu2.Pt());
          wmc->var("m_eta")->setVal(mymu2.Eta());
          wmc->var("m_iso")->setVal(iso_2);
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_ratio")->getVal();
          float sftrg2=wmc->function("m_trg_ic_ratio")->getVal();
          if (trigger1 && trigger2) aweight=aweight*(1-((1-sftrg1)*(1-sftrg2)));
          else if (trigger1 && !trigger2) aweight=aweight*sftrg1;
          else if (!trigger1 && trigger2) aweight=aweight*sftrg2;
          //aweight=aweight*prefiring_weight;
          //aweight=aweight*bweight;
        }

	if (sample=="data_obs") aweight=1.0;
	if (mytau.Pt()<20) continue;

	// DM inclusive
        if (deepTightVSmu_3 and deepVLooseVSe_3){
           if (deepVVVLooseVSjet_3) hpt_dmall_VLe_Tmu_deepveryveryveryloose->Fill(pt_3,aweight);
           //if (deepVVLooseVSjet_3) hpt_dmall_VLe_Tmu_deepveryveryloose->Fill(pt_3,aweight);
           //if (deepVLooseVSjet_3) hpt_dmall_VLe_Tmu_deepveryloose->Fill(pt_3,aweight);
           //if (deepLooseVSjet_3) hpt_dmall_VLe_Tmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3) hpt_dmall_VLe_Tmu_deepmedium->Fill(pt_3,aweight);
           //if (deepTightVSjet_3) hpt_dmall_VLe_Tmu_deeptight->Fill(pt_3,aweight);
           //if (deepVTightVSjet_3) hpt_dmall_VLe_Tmu_deepverytight->Fill(pt_3,aweight);
        }
	if (deepTightVSmu_3 and deepVLooseVSe_3 and nbtag>0){
           if (deepVVVLooseVSjet_3) hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose->Fill(pt_3,aweight);
           //if (deepVVLooseVSjet_3) hpt_dmall_VLe_Tmu_bjet_deepveryveryloose->Fill(pt_3,aweight);
           //if (deepVLooseVSjet_3) hpt_dmall_VLe_Tmu_bjet_deepveryloose->Fill(pt_3,aweight);
           //if (deepLooseVSjet_3) hpt_dmall_VLe_Tmu_bjet_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3) hpt_dmall_VLe_Tmu_bjet_deepmedium->Fill(pt_3,aweight);
           //if (deepTightVSjet_3) hpt_dmall_VLe_Tmu_bjet_deeptight->Fill(pt_3,aweight);
           //if (deepVTightVSjet_3) hpt_dmall_VLe_Tmu_bjet_deepverytight->Fill(pt_3,aweight);
	} 
        if (deepTightVSmu_3 and deepVLooseVSe_3 and njets>0){
           if (deepVVVLooseVSjet_3) hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose->Fill(pt_3,aweight);
           //if (deepVVLooseVSjet_3) hpt_dmall_VLe_Tmu_1jet_deepveryveryloose->Fill(pt_3,aweight);
           //if (deepVLooseVSjet_3) hpt_dmall_VLe_Tmu_1jet_deepveryloose->Fill(pt_3,aweight);
           //if (deepLooseVSjet_3) hpt_dmall_VLe_Tmu_1jet_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3) hpt_dmall_VLe_Tmu_1jet_deepmedium->Fill(pt_3,aweight);
           //if (deepTightVSjet_3) hpt_dmall_VLe_Tmu_1jet_deeptight->Fill(pt_3,aweight);
           //if (deepVTightVSjet_3) hpt_dmall_VLe_Tmu_1jet_deepverytight->Fill(pt_3,aweight);
        }

        if (deepVLooseVSmu_3 and deepTightVSe_3){
           if (deepVVVLooseVSjet_3) hpt_dmall_Te_VLmu_deepveryveryveryloose->Fill(pt_3,aweight);
           //if (deepVVLooseVSjet_3) hpt_dmall_Te_VLmu_deepveryveryloose->Fill(pt_3,aweight);
           //if (deepVLooseVSjet_3) hpt_dmall_Te_VLmu_deepveryloose->Fill(pt_3,aweight);
           //if (deepLooseVSjet_3) hpt_dmall_Te_VLmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3) hpt_dmall_Te_VLmu_deepmedium->Fill(pt_3,aweight);
           //if (deepTightVSjet_3) hpt_dmall_Te_VLmu_deeptight->Fill(pt_3,aweight);
           //if (deepVTightVSjet_3) hpt_dmall_Te_VLmu_deepverytight->Fill(pt_3,aweight);
        }
        if (deepVLooseVSmu_3 and deepTightVSe_3 and nbtag>0){
           if (deepVVVLooseVSjet_3) hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose->Fill(pt_3,aweight);
           //if (deepVVLooseVSjet_3) hpt_dmall_Te_VLmu_bjet_deepveryveryloose->Fill(pt_3,aweight);
           //if (deepVLooseVSjet_3) hpt_dmall_Te_VLmu_bjet_deepveryloose->Fill(pt_3,aweight);
           //if (deepLooseVSjet_3) hpt_dmall_Te_VLmu_bjet_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3) hpt_dmall_Te_VLmu_bjet_deepmedium->Fill(pt_3,aweight);
           //if (deepTightVSjet_3) hpt_dmall_Te_VLmu_bjet_deeptight->Fill(pt_3,aweight);
           //if (deepVTightVSjet_3) hpt_dmall_Te_VLmu_bjet_deepverytight->Fill(pt_3,aweight);
        }
        if (deepVLooseVSmu_3 and deepTightVSe_3 and njets>0){
           if (deepVVVLooseVSjet_3) hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose->Fill(pt_3,aweight);
           //if (deepVVLooseVSjet_3) hpt_dmall_Te_VLmu_1jet_deepveryveryloose->Fill(pt_3,aweight);
           //if (deepVLooseVSjet_3) hpt_dmall_Te_VLmu_1jet_deepveryloose->Fill(pt_3,aweight);
           //if (deepLooseVSjet_3) hpt_dmall_Te_VLmu_1jet_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3) hpt_dmall_Te_VLmu_1jet_deepmedium->Fill(pt_3,aweight);
           //if (deepTightVSjet_3) hpt_dmall_Te_VLmu_1jet_deeptight->Fill(pt_3,aweight);
           //if (deepVTightVSjet_3) hpt_dmall_Te_VLmu_1jet_deepverytight->Fill(pt_3,aweight);
        }
/*
	// DM exclusive
	if (deepTightVSmu_3 and deepVVVLooseVSe_3 and nbtag==0){
	   if (deepVVVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==0) hpt_dm0_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==0) hpt_dm0_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==0) hpt_dm0_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==0) hpt_dm0_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==1) hpt_dm1_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==1) hpt_dm1_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==1) hpt_dm1_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==1) hpt_dm1_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==10) hpt_dm10_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==10) hpt_dm10_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==10) hpt_dm10_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==10) hpt_dm10_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==11) hpt_dm11_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==11) hpt_dm11_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==11) hpt_dm11_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==11) hpt_dm11_deepverytight->Fill(pt_3,aweight);
	}

        if (deepTightVSmu_3 and deepTightVSe_3 and nbtag==0){
           if (deepVVVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_Te_Tmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_Te_Tmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_Te_Tmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==0) hpt_dm0_Te_Tmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==0) hpt_dm0_Te_Tmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==0) hpt_dm0_Te_Tmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==0) hpt_dm0_Te_Tmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_Te_Tmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_Te_Tmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_Te_Tmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==1) hpt_dm1_Te_Tmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==1) hpt_dm1_Te_Tmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==1) hpt_dm1_Te_Tmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==1) hpt_dm1_Te_Tmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_Te_Tmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_Te_Tmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_Te_Tmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==10) hpt_dm10_Te_Tmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==10) hpt_dm10_Te_Tmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==10) hpt_dm10_Te_Tmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==10) hpt_dm10_Te_Tmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_Te_Tmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_Te_Tmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_Te_Tmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==11) hpt_dm11_Te_Tmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==11) hpt_dm11_Te_Tmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==11) hpt_dm11_Te_Tmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==11) hpt_dm11_Te_Tmu_deepverytight->Fill(pt_3,aweight);
        }

        if (deepTightVSmu_3 and deepVLooseVSe_3  and nbtag==0){
           if (deepVVVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_Tmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_Tmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_Tmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_Tmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_Tmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_Tmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_Tmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_Tmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_Tmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_Tmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_Tmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_Tmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_Tmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_Tmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_Tmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_Tmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_Tmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_Tmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_Tmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_Tmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_Tmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_Tmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_Tmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_Tmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_Tmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_Tmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_Tmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_Tmu_deepverytight->Fill(pt_3,aweight);
        }


        if (deepVLooseVSmu_3 and deepTightVSe_3 and nbtag==0){
           if (deepVVVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_Te_VLmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_Te_VLmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_Te_VLmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==0) hpt_dm0_Te_VLmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==0) hpt_dm0_Te_VLmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==0) hpt_dm0_Te_VLmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==0) hpt_dm0_Te_VLmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_Te_VLmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_Te_VLmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_Te_VLmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==1) hpt_dm1_Te_VLmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==1) hpt_dm1_Te_VLmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==1) hpt_dm1_Te_VLmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==1) hpt_dm1_Te_VLmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_Te_VLmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_Te_VLmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_Te_VLmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==10) hpt_dm10_Te_VLmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==10) hpt_dm10_Te_VLmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==10) hpt_dm10_Te_VLmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==10) hpt_dm10_Te_VLmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_Te_VLmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_Te_VLmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_Te_VLmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==11) hpt_dm11_Te_VLmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==11) hpt_dm11_Te_VLmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==11) hpt_dm11_Te_VLmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==11) hpt_dm11_Te_VLmu_deepverytight->Fill(pt_3,aweight);
        }


        if (deepVLooseVSmu_3 and deepVLooseVSe_3 and nbtag==0){
           if (deepVVVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_VLmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_VLmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_VLmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_VLmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_VLmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_VLmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==0) hpt_dm0_VLe_VLmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_VLmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_VLmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_VLmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_VLmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_VLmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_VLmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==1) hpt_dm1_VLe_VLmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_VLmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_VLmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_VLmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_VLmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_VLmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_VLmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==10) hpt_dm10_VLe_VLmu_deepverytight->Fill(pt_3,aweight);
           if (deepVVVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_VLmu_deepveryveryveryloose->Fill(pt_3,aweight);
           if (deepVVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_VLmu_deepveryveryloose->Fill(pt_3,aweight);
           if (deepVLooseVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_VLmu_deepveryloose->Fill(pt_3,aweight);
           if (deepLooseVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_VLmu_deeploose->Fill(pt_3,aweight);
           if (deepMediumVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_VLmu_deepmedium->Fill(pt_3,aweight);
           if (deepTightVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_VLmu_deeptight->Fill(pt_3,aweight);
           if (deepVTightVSjet_3 and l3_decayMode==11) hpt_dm11_VLe_VLmu_deepverytight->Fill(pt_3,aweight);
        }*/

				
    } // end of loop over events


    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    hpt_dmall_VLe_Tmu_deepveryveryveryloose->Write();
    //hpt_dmall_VLe_Tmu_deepveryveryloose->Write();
    //hpt_dmall_VLe_Tmu_deepveryloose->Write();
    //hpt_dmall_VLe_Tmu_deeploose->Write();
    hpt_dmall_VLe_Tmu_deepmedium->Write();
    //hpt_dmall_VLe_Tmu_deeptight->Write();
    //hpt_dmall_VLe_Tmu_deepverytight->Write();
    hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose->Write();
    //hpt_dmall_VLe_Tmu_bjet_deepveryveryloose->Write();
    //hpt_dmall_VLe_Tmu_bjet_deepveryloose->Write();
    //hpt_dmall_VLe_Tmu_bjet_deeploose->Write();
    hpt_dmall_VLe_Tmu_bjet_deepmedium->Write();
    //hpt_dmall_VLe_Tmu_bjet_deeptight->Write();
    //hpt_dmall_VLe_Tmu_bjet_deepverytight->Write();
    hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose->Write();
    //hpt_dmall_VLe_Tmu_1jet_deepveryveryloose->Write();
    //hpt_dmall_VLe_Tmu_1jet_deepveryloose->Write();
    //hpt_dmall_VLe_Tmu_1jet_deeploose->Write();
    hpt_dmall_VLe_Tmu_1jet_deepmedium->Write();
    //hpt_dmall_VLe_Tmu_1jet_deeptight->Write();
    //hpt_dmall_VLe_Tmu_1jet_deepverytight->Write();

    hpt_dmall_Te_VLmu_deepveryveryveryloose->Write();
    //hpt_dmall_Te_VLmu_deepveryveryloose->Write();
    //hpt_dmall_Te_VLmu_deepveryloose->Write();
    //hpt_dmall_Te_VLmu_deeploose->Write();
    hpt_dmall_Te_VLmu_deepmedium->Write();
    //hpt_dmall_Te_VLmu_deeptight->Write();
    //hpt_dmall_Te_VLmu_deepverytight->Write();
    hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose->Write();
    //hpt_dmall_Te_VLmu_bjet_deepveryveryloose->Write();
    //hpt_dmall_Te_VLmu_bjet_deepveryloose->Write();
    //hpt_dmall_Te_VLmu_bjet_deeploose->Write();
    hpt_dmall_Te_VLmu_bjet_deepmedium->Write();
    //hpt_dmall_Te_VLmu_bjet_deeptight->Write();
    //hpt_dmall_Te_VLmu_bjet_deepverytight->Write();
    hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose->Write();
    //hpt_dmall_Te_VLmu_1jet_deepveryveryloose->Write();
    //hpt_dmall_Te_VLmu_1jet_deepveryloose->Write();
    //hpt_dmall_Te_VLmu_1jet_deeploose->Write();
    hpt_dmall_Te_VLmu_1jet_deepmedium->Write(); 
    //hpt_dmall_Te_VLmu_1jet_deeptight->Write();
    //hpt_dmall_Te_VLmu_1jet_deepverytight->Write();
/*
    hpt_dm0_deepveryveryveryloose->Write();
    hpt_dm0_deepveryveryloose->Write();
    hpt_dm0_deepveryloose->Write();
    hpt_dm0_deeploose->Write();
    hpt_dm0_deepmedium->Write();
    hpt_dm0_deeptight->Write();
    hpt_dm0_deepverytight->Write();
    hpt_dm1_deepveryveryveryloose->Write();
    hpt_dm1_deepveryveryloose->Write();
    hpt_dm1_deepveryloose->Write();
    hpt_dm1_deeploose->Write();
    hpt_dm1_deepmedium->Write();
    hpt_dm1_deeptight->Write();
    hpt_dm1_deepverytight->Write();
    hpt_dm10_deepveryveryveryloose->Write();
    hpt_dm10_deepveryveryloose->Write();
    hpt_dm10_deepveryloose->Write();
    hpt_dm10_deeploose->Write();
    hpt_dm10_deepmedium->Write();
    hpt_dm10_deeptight->Write();
    hpt_dm10_deepverytight->Write();
    hpt_dm11_deepveryveryveryloose->Write();
    hpt_dm11_deepveryveryloose->Write();
    hpt_dm11_deepveryloose->Write();
    hpt_dm11_deeploose->Write();
    hpt_dm11_deepmedium->Write();
    hpt_dm11_deeptight->Write();
    hpt_dm11_deepverytight->Write();

    hpt_dm0_Te_Tmu_deepveryveryveryloose->Write();
    hpt_dm0_Te_Tmu_deepveryveryloose->Write();
    hpt_dm0_Te_Tmu_deepveryloose->Write();
    hpt_dm0_Te_Tmu_deeploose->Write();
    hpt_dm0_Te_Tmu_deepmedium->Write();
    hpt_dm0_Te_Tmu_deeptight->Write();
    hpt_dm0_Te_Tmu_deepverytight->Write();
    hpt_dm1_Te_Tmu_deepveryveryveryloose->Write();
    hpt_dm1_Te_Tmu_deepveryveryloose->Write();
    hpt_dm1_Te_Tmu_deepveryloose->Write();
    hpt_dm1_Te_Tmu_deeploose->Write();
    hpt_dm1_Te_Tmu_deepmedium->Write();
    hpt_dm1_Te_Tmu_deeptight->Write();
    hpt_dm1_Te_Tmu_deepverytight->Write();
    hpt_dm10_Te_Tmu_deepveryveryveryloose->Write();
    hpt_dm10_Te_Tmu_deepveryveryloose->Write();
    hpt_dm10_Te_Tmu_deepveryloose->Write();
    hpt_dm10_Te_Tmu_deeploose->Write();
    hpt_dm10_Te_Tmu_deepmedium->Write();
    hpt_dm10_Te_Tmu_deeptight->Write();
    hpt_dm10_Te_Tmu_deepverytight->Write();
    hpt_dm11_Te_Tmu_deepveryveryveryloose->Write();
    hpt_dm11_Te_Tmu_deepveryveryloose->Write();
    hpt_dm11_Te_Tmu_deepveryloose->Write();
    hpt_dm11_Te_Tmu_deeploose->Write();
    hpt_dm11_Te_Tmu_deepmedium->Write();
    hpt_dm11_Te_Tmu_deeptight->Write();
    hpt_dm11_Te_Tmu_deepverytight->Write();

    hpt_dm0_VLe_Tmu_deepveryveryveryloose->Write();
    hpt_dm0_VLe_Tmu_deepveryveryloose->Write();
    hpt_dm0_VLe_Tmu_deepveryloose->Write();
    hpt_dm0_VLe_Tmu_deeploose->Write();
    hpt_dm0_VLe_Tmu_deepmedium->Write();
    hpt_dm0_VLe_Tmu_deeptight->Write();
    hpt_dm0_VLe_Tmu_deepverytight->Write();
    hpt_dm1_VLe_Tmu_deepveryveryveryloose->Write();
    hpt_dm1_VLe_Tmu_deepveryveryloose->Write();
    hpt_dm1_VLe_Tmu_deepveryloose->Write();
    hpt_dm1_VLe_Tmu_deeploose->Write();
    hpt_dm1_VLe_Tmu_deepmedium->Write();
    hpt_dm1_VLe_Tmu_deeptight->Write();
    hpt_dm1_VLe_Tmu_deepverytight->Write();
    hpt_dm10_VLe_Tmu_deepveryveryveryloose->Write();
    hpt_dm10_VLe_Tmu_deepveryveryloose->Write();
    hpt_dm10_VLe_Tmu_deepveryloose->Write();
    hpt_dm10_VLe_Tmu_deeploose->Write();
    hpt_dm10_VLe_Tmu_deepmedium->Write();
    hpt_dm10_VLe_Tmu_deeptight->Write();
    hpt_dm10_VLe_Tmu_deepverytight->Write();
    hpt_dm11_VLe_Tmu_deepveryveryveryloose->Write();
    hpt_dm11_VLe_Tmu_deepveryveryloose->Write();
    hpt_dm11_VLe_Tmu_deepveryloose->Write();
    hpt_dm11_VLe_Tmu_deeploose->Write();
    hpt_dm11_VLe_Tmu_deepmedium->Write();
    hpt_dm11_VLe_Tmu_deeptight->Write();
    hpt_dm11_VLe_Tmu_deepverytight->Write();

    hpt_dm0_Te_VLmu_deepveryveryveryloose->Write();
    hpt_dm0_Te_VLmu_deepveryveryloose->Write();
    hpt_dm0_Te_VLmu_deepveryloose->Write();
    hpt_dm0_Te_VLmu_deeploose->Write();
    hpt_dm0_Te_VLmu_deepmedium->Write();
    hpt_dm0_Te_VLmu_deeptight->Write();
    hpt_dm0_Te_VLmu_deepverytight->Write();
    hpt_dm1_Te_VLmu_deepveryveryveryloose->Write();
    hpt_dm1_Te_VLmu_deepveryveryloose->Write();
    hpt_dm1_Te_VLmu_deepveryloose->Write();
    hpt_dm1_Te_VLmu_deeploose->Write();
    hpt_dm1_Te_VLmu_deepmedium->Write();
    hpt_dm1_Te_VLmu_deeptight->Write();
    hpt_dm1_Te_VLmu_deepverytight->Write();
    hpt_dm10_Te_VLmu_deepveryveryveryloose->Write();
    hpt_dm10_Te_VLmu_deepveryveryloose->Write();
    hpt_dm10_Te_VLmu_deepveryloose->Write();
    hpt_dm10_Te_VLmu_deeploose->Write();
    hpt_dm10_Te_VLmu_deepmedium->Write();
    hpt_dm10_Te_VLmu_deeptight->Write();
    hpt_dm10_Te_VLmu_deepverytight->Write();
    hpt_dm11_Te_VLmu_deepveryveryveryloose->Write();
    hpt_dm11_Te_VLmu_deepveryveryloose->Write();
    hpt_dm11_Te_VLmu_deepveryloose->Write();
    hpt_dm11_Te_VLmu_deeploose->Write();
    hpt_dm11_Te_VLmu_deepmedium->Write();
    hpt_dm11_Te_VLmu_deeptight->Write();
    hpt_dm11_Te_VLmu_deepverytight->Write();

    hpt_dm0_VLe_VLmu_deepveryveryveryloose->Write();
    hpt_dm0_VLe_VLmu_deepveryveryloose->Write();
    hpt_dm0_VLe_VLmu_deepveryloose->Write();
    hpt_dm0_VLe_VLmu_deeploose->Write();
    hpt_dm0_VLe_VLmu_deepmedium->Write();
    hpt_dm0_VLe_VLmu_deeptight->Write();
    hpt_dm0_VLe_VLmu_deepverytight->Write();
    hpt_dm1_VLe_VLmu_deepveryveryveryloose->Write();
    hpt_dm1_VLe_VLmu_deepveryveryloose->Write();
    hpt_dm1_VLe_VLmu_deepveryloose->Write();
    hpt_dm1_VLe_VLmu_deeploose->Write();
    hpt_dm1_VLe_VLmu_deepmedium->Write();
    hpt_dm1_VLe_VLmu_deeptight->Write();
    hpt_dm1_VLe_VLmu_deepverytight->Write();
    hpt_dm10_VLe_VLmu_deepveryveryveryloose->Write();
    hpt_dm10_VLe_VLmu_deepveryveryloose->Write();
    hpt_dm10_VLe_VLmu_deepveryloose->Write();
    hpt_dm10_VLe_VLmu_deeploose->Write();
    hpt_dm10_VLe_VLmu_deepmedium->Write();
    hpt_dm10_VLe_VLmu_deeptight->Write();
    hpt_dm10_VLe_VLmu_deepverytight->Write();
    hpt_dm11_VLe_VLmu_deepveryveryveryloose->Write();
    hpt_dm11_VLe_VLmu_deepveryveryloose->Write();
    hpt_dm11_VLe_VLmu_deepveryloose->Write();
    hpt_dm11_VLe_VLmu_deeploose->Write();
    hpt_dm11_VLe_VLmu_deepmedium->Write();
    hpt_dm11_VLe_VLmu_deeptight->Write();
    hpt_dm11_VLe_VLmu_deepverytight->Write();
*/

    fout->Close();
} 


