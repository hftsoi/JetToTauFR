#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include "makeHisto.h"
#include "mmt_Tree.h"
//#include "LumiReweightingStandAlone.h"

int main(int argc, char** argv) {

    using namespace std;
    myMap1 = new map<string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    string status_sample = *(argv + 1);
    bool isMC = false;
    bool isData = false;
    bool isEmbedded=false;
    if (status_sample.compare("mc") == 0) isMC = true;
    if (status_sample.compare("data") == 0) isData = true;
    if (status_sample.compare("embedded") == 0) isEmbedded = true;
    string out = *(argv + 2);
    string outname= out;
    TFile *fout = TFile::Open(outname.c_str(), "RECREATE");

    string in = *(argv + 3);
    string inname= in;
    TFile *fIn = TFile::Open(inname.c_str());

    int recoil=0;
    string recoilType = *(argv + 4);
    if (recoilType.compare("W") == 0)  recoil=1;
    if (recoilType.compare("Z") == 0)  recoil=2;

    string year_sample = *(argv + 5);
    int year=2018;
    if (year_sample.compare("2016") == 0) year=2016;
    if (year_sample.compare("2017") == 0) year=2017;

    TTree* treePtr = (TTree*) fIn->Get("mmt/final/Ntuple");
    TH1F *evCounter = (TH1F*) fIn->Get("mmt/eventCount");
    TH1F *evCounterW = (TH1F*) fIn->Get("mmt/summedWeights");
    HTauTauTree_mmt* tree = new HTauTauTree_mmt (treePtr);

    TTree *Run_Tree = new TTree("mmt_tree", "mmt_tree");
    Run_Tree->SetDirectory(0);
    Run_Tree->Branch("run", &run, "run/I");
    Run_Tree->Branch("lumi", &lumi, "lumi/I");
    Run_Tree->Branch("evt", &evt, "evt/I");

    Run_Tree->Branch("npv", &npv, "npv/F");
    Run_Tree->Branch("npu", &npu, "npu/F");
    Run_Tree->Branch("amcatNLO_weight", &aMCatNLO_weight, "aMCatNLO_weight/F");

    Run_Tree->Branch("jetpt_1", &jetpt_1, "jetpt_1/F");
    Run_Tree->Branch("jetpt_2", &jetpt_2, "jetpt_2/F");
    Run_Tree->Branch("jetpt_3", &jetpt_3, "jetpt_3/F");
    Run_Tree->Branch("pt_1", &pt_1, "pt_1/F");
    Run_Tree->Branch("phi_1", &phi_1, "phi_1/F");
    Run_Tree->Branch("eta_1", &eta_1, "eta_1/F");
    Run_Tree->Branch("m_1", &m_1, "m_1/F");
    Run_Tree->Branch("e_1", &e_1, "e_1/F");
    Run_Tree->Branch("q_1", &q_1, "q_1/F");
    Run_Tree->Branch("mt_1", &mt_1, "mt_1/F");
    Run_Tree->Branch("iso_1", &iso_1, "iso_1/F");
    Run_Tree->Branch("id_m_medium_2", &id_m_medium_2, "id_m_medium_2/F");
    Run_Tree->Branch("id_m_medium_1", &id_m_medium_1, "id_m_medium_1/F");
    Run_Tree->Branch("pt_2", &pt_2, "pt_2/F");
    Run_Tree->Branch("phi_2", &phi_2, "phi_2/F");
    Run_Tree->Branch("eta_2", &eta_2, "eta_2/F");
    Run_Tree->Branch("m_2", &m_2, "m_2/F");
    Run_Tree->Branch("e_2", &e_2, "e_2/F");
    Run_Tree->Branch("q_2", &q_2, "q_2/F");
    Run_Tree->Branch("iso_2", &iso_2, "iso_2/F");
    Run_Tree->Branch("genpX", &genpX, "genpX/F");
    Run_Tree->Branch("genpY", &genpY, "genpY/F");
    Run_Tree->Branch("genpT", &genpT, "genpT/F");
    Run_Tree->Branch("genM", &genM, "genM/F");
    Run_Tree->Branch("vispX", &vispX, "vispX/F");
    Run_Tree->Branch("vispY", &vispY, "vispY/F");

    Run_Tree->Branch("passMu22eta2p1", &passMu22eta2p1, "passMu22eta2p1/F");
    Run_Tree->Branch("passTkMu22eta2p1", &passTkMu22eta2p1, "passTkMu22eta2p1/F");
    Run_Tree->Branch("matchMu22eta2p1_2", &matchMu22eta2p1_2, "matchMu22eta2p1_2/F");
    Run_Tree->Branch("matchTkMu22eta2p1_2", &matchTkMu22eta2p1_2, "matchTkMu22eta2p1_2/F");
    Run_Tree->Branch("matchMu22eta2p1_1", &matchMu22eta2p1_1, "matchMu22eta2p1_1/F");
    Run_Tree->Branch("matchTkMu22eta2p1_1", &matchTkMu22eta2p1_1, "matchTkMu22eta2p1_1/F");
    Run_Tree->Branch("filterMu22eta2p1_2", &filterMu22eta2p1_2, "filterMu22eta2p1_2/F");
    Run_Tree->Branch("filterTkMu22eta2p1_2", &filterTkMu22eta2p1_2, "filterTkMu22eta2p1_2/F");
    Run_Tree->Branch("filterMu22eta2p1_1", &filterMu22eta2p1_1, "filterMu22eta2p1_1/F");
    Run_Tree->Branch("filterTkMu22eta2p1_1", &filterTkMu22eta2p1_1, "filterTkMu22eta2p1_1/F");
    Run_Tree->Branch("passMu24", &passMu24, "passMu24/F");
    Run_Tree->Branch("matchMu24_2", &matchMu24_2, "matchMu24_2/F");
    Run_Tree->Branch("filterMu24_2", &filterMu24_2, "filterMu24_2/F");
    Run_Tree->Branch("matchMu24_1", &matchMu24_1, "matchMu24_1/F");
    Run_Tree->Branch("filterMu24_1", &filterMu24_1, "filterMu24_1/F");
    Run_Tree->Branch("passMu27", &passMu27, "passMu27/F");
    Run_Tree->Branch("matchMu27_2", &matchMu27_2, "matchMu27_2/F");
    Run_Tree->Branch("filterMu27_2", &filterMu27_2, "filterMu27_2/F");
    Run_Tree->Branch("matchMu27_1", &matchMu27_1, "matchMu27_1/F");
    Run_Tree->Branch("filterMu27_1", &filterMu27_1, "filterMu27_1/F");

    Run_Tree->Branch("pt_3", &pt_3, "pt_3/F");
    Run_Tree->Branch("phi_3", &phi_3, "phi_3/F");
    Run_Tree->Branch("eta_3", &eta_3, "eta_3/F");
    Run_Tree->Branch("m_3", &m_3, "m_3/F");
    Run_Tree->Branch("e_3", &e_3, "e_3/F");
    Run_Tree->Branch("q_3", &q_3, "q_3/F");
    Run_Tree->Branch("iso_3", &iso_3, "iso_3/F");
    Run_Tree->Branch("l3_decayMode", &l3_decayMode, "l3_decayMode/F");

    Run_Tree->Branch("deepVVVLooseVSjet_3", &deepVVVLooseVSjet_3, "deepVVVLooseVSjet_3/F");
    Run_Tree->Branch("deepVVLooseVSjet_3", &deepVVLooseVSjet_3, "deepVVLooseVSjet_3/F");
    Run_Tree->Branch("deepVLooseVSjet_3", &deepVLooseVSjet_3, "deepVLooseVSjet_3/F");
    Run_Tree->Branch("deepLooseVSjet_3", &deepLooseVSjet_3, "deepLooseVSjet_3/F");
    Run_Tree->Branch("deepMediumVSjet_3", &deepMediumVSjet_3, "deepMediumVSjet_3/F");
    Run_Tree->Branch("deepTightVSjet_3", &deepTightVSjet_3, "deepTightVSjet_3/F");
    Run_Tree->Branch("deepVTightVSjet_3", &deepVTightVSjet_3, "deepVTightVSjet_3/F");
    Run_Tree->Branch("deepVLooseVSmu_3", &deepVLooseVSmu_3, "deepVLooseVSmu_3/F");
    Run_Tree->Branch("deepLooseVSmu_3", &deepLooseVSmu_3, "deepLooseVSmu_3/F");
    Run_Tree->Branch("deepMediumVSmu_3", &deepMediumVSmu_3, "deepMediumVSmu_3/F");
    Run_Tree->Branch("deepTightVSmu_3", &deepTightVSmu_3, "deepTightVSmu_3/F");
    Run_Tree->Branch("deepVTightVSmu_3", &deepVTightVSmu_3, "deepVTightVSmu_3/F");
    Run_Tree->Branch("deepVVVLooseVSe_3", &deepVVVLooseVSe_3, "deepVVVLooseVSe_3/F");
    Run_Tree->Branch("deepVVLooseVSe_3", &deepVVLooseVSe_3, "deepVVLooseVSe_3/F");
    Run_Tree->Branch("deepVLooseVSe_3", &deepVLooseVSe_3, "deepVLooseVSe_3/F");
    Run_Tree->Branch("deepLooseVSe_3", &deepLooseVSe_3, "deepLooseVSe_3/F");
    Run_Tree->Branch("deepMediumVSe_3", &deepMediumVSe_3, "deepMediumVSe_3/F");
    Run_Tree->Branch("deepTightVSe_3", &deepTightVSe_3, "deepTightVSe_3/F");
    Run_Tree->Branch("deepVTightVSe_3", &deepVTightVSe_3, "deepVTightVSe_3/F");

    Run_Tree->Branch("numGenJets", &numGenJets, "numGenJets/F");
    Run_Tree->Branch("pt_top1", &pt_top1, "pt_top1/F");
    Run_Tree->Branch("pt_top2", &pt_top2, "pt_top2/F");
    Run_Tree->Branch("genweight", &genweight, "genweight/F");

    Run_Tree->Branch("met", &met, "met/F");
    Run_Tree->Branch("metphi", &metphi, "metphi/F");

    Run_Tree->Branch("gen_match_1", &gen_match_1, "gen_match_1/I");
    Run_Tree->Branch("gen_match_2", &gen_match_2, "gen_match_2/I");
    Run_Tree->Branch("gen_match_3", &gen_match_3, "gen_match_3/I");

    Run_Tree->Branch("nbtag", &nbtag, "nbtag/I");
    Run_Tree->Branch("nbtagL", &nbtagL, "nbtagL/I");
    Run_Tree->Branch("njets", &njets, "njets/I");
    Run_Tree->Branch("jpt_1", &jpt_1, "jpt_1/F");
    Run_Tree->Branch("jeta_1", &jeta_1, "jeta_1/F");
    Run_Tree->Branch("jphi_1", &jphi_1, "jphi_1/F");
    Run_Tree->Branch("jcsv_1", &jcsv_1, "jcsv_1/F");

    Run_Tree->Branch("jpt_2", &jpt_2, "jpt_2/F");
    Run_Tree->Branch("jeta_2", &jeta_2, "jeta_2/F");
    Run_Tree->Branch("jphi_2", &jphi_2, "jphi_2/F");
    Run_Tree->Branch("jcsv_2", &jcsv_2, "jcsv_2/F");

    Run_Tree->Branch("bpt_1", &bpt_1, "bpt_1/F");
    Run_Tree->Branch("beta_1", &beta_1, "beta_1/F");
    Run_Tree->Branch("bphi_1", &bphi_1, "bphi_1/F");
    Run_Tree->Branch("bcsv_1", &bcsv_1, "bcsv_1/F");
    Run_Tree->Branch("bflavor_1", &bflavor_1, "bflavor_1/F");

    Run_Tree->Branch("bpt_2", &bpt_2, "bpt_2/F");
    Run_Tree->Branch("beta_2", &beta_2, "beta_2/F");
    Run_Tree->Branch("bphi_2", &bphi_2, "bphi_2/F");
    Run_Tree->Branch("bcsv_2", &bcsv_2, "bcsv_2/F");
    Run_Tree->Branch("bflavor_2", &bflavor_2, "bflavor_2/F");

    int bestEntry=-1;
    ULong64_t evt_now=0;
    ULong64_t evt_before=-1;
    float lt_before=0;
    bool print=false;
    plotFill("nevents",0,9,0,9,evCounter->GetBinContent(1));
    plotFill("nevents",1,9,0,9,evCounterW->GetBinContent(1));
    for (int iEntry = 0; iEntry < tree->GetEntries() ; iEntry++)
    {
        float pu=1.0;
        tree->GetEntry(iEntry);
        bool print=false;
        if (iEntry % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d ", iEntry);
        fflush(stdout);
        plotFill("pileup_mc",tree->nTruePU,80,0,80);
        TLorentzVector dau1;
        TLorentzVector dau2;
        TLorentzVector dau3;
        dau1.SetPtEtaPhiM(tree->m1Pt,tree->m1Eta,tree->m1Phi,tree->m1Mass);
        dau2.SetPtEtaPhiM(tree->m2Pt,tree->m2Eta,tree->m2Phi,tree->m2Mass);
        dau3.SetPtEtaPhiM(tree->tPt,tree->tEta,tree->tPhi,tree->tMass);
        if (dau1.DeltaR(dau3)<0.5) continue;
        if (dau2.DeltaR(dau3)<0.5) continue;
        if (dau1.DeltaR(dau2)<0.3) continue;
	if (fabs(tree->m1PVDXY)>0.045) continue;
        if (fabs(tree->m1PVDZ)>0.2) continue;
        if (fabs(tree->m2PVDXY)>0.045) continue;
        if (fabs(tree->m2PVDZ)>0.2) continue;
        if (fabs(tree->tPVDZ)>0.2) continue;
        if (dau1.Pt()<9.5 or dau2.Pt()<9.5 or dau3.Pt()<19.5) continue;//FIXME
	if (dau1.Pt()<22 and dau2.Pt()<22) continue;
        if (fabs(dau1.Eta())>2.4 or fabs(dau2.Eta())>2.4 or fabs(dau3.Eta())>2.3) continue;
        if (!tree->m1PFIDMedium or !tree->m2PFIDMedium) continue;
	if (tree->m1Charge*tree->m2Charge>0) continue;
	if ((dau1+dau2).M()>106 or (dau1+dau2).M()<76) continue; //FIXME loosen next time to get ttbar
	if (tree->m1RelPFIsoDBDefault>0.15 or tree->m2RelPFIsoDBDefault>0.15) continue;
	evt_now=tree->evt;
	if (tree->eVetoZTTp001dxyzR0>0) continue;//FIXME
	if (tree->muVetoZTTp001dxyzR0>2) continue;//FIXME
        if (tree->tDecayMode==5 or tree->tDecayMode==6) continue;
        if (!(tree->tVVVLooseDeepTau2017v2p1VSe && tree->tVLooseDeepTau2017v2p1VSmu && tree->tVVVLooseDeepTau2017v2p1VSjet)) continue;
	if (evt_now!=evt_before){
	   lt_before=tree->m1Pt + tree->m2Pt + tree->tPt;
	}
        if (evt_now!=evt_before){
           if (bestEntry>-1)
              fillTree(Run_Tree,tree,bestEntry,recoil,isMC,year);
           bestEntry=iEntry;
	}
	if (evt_now==evt_before){
	   if (tree->m1Pt + tree->m2Pt + tree->tPt>lt_before+0.0001){
		bestEntry=iEntry;
	 	lt_before=tree->m1Pt + tree->m2Pt + tree->tPt;
	   }
	}
	evt_before=evt_now;
    }
    if (bestEntry>-1)
      fillTree(Run_Tree,tree,bestEntry,recoil,isMC,year);
    fout->cd();
    Run_Tree->Write();
    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();
    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();
    for (; iMap2 != jMap2; ++iMap2)
        nplot2(iMap2->first)->Write();

    fout->Close();
    return 0;
}

