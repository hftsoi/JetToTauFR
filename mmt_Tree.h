#ifndef THTH_TREE_H
#define	THTH_TREE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "HTauTauTree_mmt.h"
#include "RecoilCorrector.h"
//#include "myHelper.h"

using namespace std;

float deepVVVLooseVSjet_3,deepVVLooseVSjet_3,deepVLooseVSjet_3,deepLooseVSjet_3,deepMediumVSjet_3,deepTightVSjet_3,deepVTightVSjet_3;
float deepVVVLooseVSe_3,deepVVLooseVSe_3,deepVLooseVSe_3,deepLooseVSe_3,deepMediumVSe_3,deepTightVSe_3,deepVTightVSe_3;
float deepVVVLooseVSmu_3,deepVVLooseVSmu_3,deepVLooseVSmu_3,deepLooseVSmu_3,deepMediumVSmu_3,deepTightVSmu_3,deepVTightVSmu_3;
float trackpt_3, jetPt_3;
unsigned int run, lumi, evt, NUP = -10;
bool secondMuon=false;
int gen_match_1, gen_match_2, gen_match_3=0;
float jetpt_1, jetpt_2, jetpt_3;
float met_norecoil;
float npu, rho, npv=-1, puweight, weight;
bool isZtt, isZmt, isZet, isZee, isZmm, isZem, isZEE, isZMM, isZLL, isFake;
float passMu27, filterMu27_2, matchMu27_2, filterMu27_1, matchMu27_1;
float passMu24, filterMu24_2, matchMu24_2, filterMu24_1, matchMu24_1;
float matchTkMu22eta2p1_2, matchTkMu22eta2p1_1, passMu22eta2p1, passTkMu22eta2p1, matchMu22eta2p1_2, matchMu22eta2p1_1, filterMu22eta2p1_2, filterMu22eta2p1_1,filterTkMu22eta2p1_2, filterTkMu22eta2p1_1;
float againstElectronLooseMVA6_3, againstElectronMediumMVA6_3, againstElectronTightMVA6_3, againstElectronVLooseMVA6_3, againstElectronVTightMVA6_3, againstMuonLoose3_3, againstMuonTight3_3, decayModeFinding_3;
float e_1, px_1, py_1, pz_1, pt_1, phi_1, eta_1, m_1, q_1, d0_1, dZ_1, mt_1, iso_1;
float eid90_1, eid80_1;
float e_2, px_2, py_2, pz_2, pt_2, phi_2, eta_2, m_2, q_2, d0_2, dZ_2, mt_2, iso_2, l2_decayMode;
float e_3, px_3, py_3, pz_3, pt_3, phi_3, eta_3, m_3, q_3, d0_3, dZ_3, mt_3, iso_3, l3_decayMode;
float id_m_medium_2,id_m_medium2016_2, id_m_tight_2;
float id_m_medium_1,id_m_medium2016_1, id_m_tight_1;
float trigweight_3, byCombinedIsolationDeltaBetaCorrRaw3Hits_3, byIsolationMVA3oldDMwoLTraw_3, byIsolationMVA3oldDMwLTraw_3, byIsolationMVA3newDMwoLTraw_3, byIsolationMVA3newDMwLTraw_3, chargedIsoPtSum_3, neutralIsoPtSum_3, puCorrPtSum_3;
float mjj, jdeta, jdphi, dijetpt, dijetphi, hdijetphi, visjeteta, ptvis;
float mjj_JESDown, jdeta_JESDown,mjj_JESUp,jdeta_JESUp;
int njetingap, njetingap20, nbtag, njets, njetspt20, nbtagL;
int njetingap_JESDown, njetingap20_JESDown, njets_JESDown, njetspt20_JESDown;
int njetingap_JESUp, njetingap20_JESUp, njets_JESUp, njetspt20_JESUp;
float je_1, jmass_1, jpt_1, jpx_1, jpy_1, jpz_1, jeta_1, jphi_1, jrawf_1, jmva_1, jpfid_1, jpuid_1, jcsv_1;
float je_2, jmass_2, jpx_2, jpy_2, jpz_2, jpt_2, jeta_2, jphi_2, jrawf_2, jmva_2, jpfid_2, jpuid_2, jcsv_2;
float bpt_1, beta_1, bphi_1, brawf_1, bmva_1, bpfid_1, bpuid_1, bcsv_1, bflavor_1;
float bpt_2, beta_2, bphi_2, brawf_2, bmva_2, bpfid_2, bpuid_2, bcsv_2, bflavor_2;
float met, metphi, mvaMet, mvaMetphi, pzetavis, pzetamiss, mvacov00, mvacov01, mvacov11, mvacov10;
int nb_extra_electrons, nb_extra_muons=0;
float top_reweighting, gen_Higgs_pt, gen_Higgs_mass=1.0;
float extraelec_veto, extramuon_veto, dilepton_veto=false;
float byLooseCombinedIsolationDeltaBetaCorr3Hits_3, byMediumCombinedIsolationDeltaBetaCorr3Hits_3, byTightCombinedIsolationDeltaBetaCorr3Hits_3;
float byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_3, byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_3, byTightCombinedIsolationDeltaBetaCorr3HitsdR03_3;
float extratau_veto, pt_top1, pt_top2, genweight, dphi_12, dphi_mumet, dphi_taumet;
float aMCatNLO_weight, numGenJets,jetPt_2;
float met_px, met_py;
float byVLooseIsolationMVArun2v1DBnewDMwLT_3,  byVLooseIsolationMVArun2v1DBoldDMwLT_3,  byVLooseIsolationMVArun2v1DBdR03oldDMwLT_3;
float byLooseIsolationMVArun2v1DBnewDMwLT_3,  byLooseIsolationMVArun2v1DBoldDMwLT_3,  byLooseIsolationMVArun2v1DBdR03oldDMwLT_3;
float byMediumIsolationMVArun2v1DBnewDMwLT_3,  byMediumIsolationMVArun2v1DBoldDMwLT_3,  byMediumIsolationMVArun2v1DBdR03oldDMwLT_3;
float byTightIsolationMVArun2v1DBnewDMwLT_3,  byTightIsolationMVArun2v1DBoldDMwLT_3,  byTightIsolationMVArun2v1DBdR03oldDMwLT_3;
float byVTightIsolationMVArun2v1DBnewDMwLT_3,  byVTightIsolationMVArun2v1DBoldDMwLT_3,  byVTightIsolationMVArun2v1DBdR03oldDMwLT_3;
float byVVTightIsolationMVArun2v1DBnewDMwLT_3,  byVVTightIsolationMVArun2v1DBoldDMwLT_3,  byVVTightIsolationMVArun2v1DBdR03oldDMwLT_3;
float metSig, metcov00, metcov01, metcov10,metcov11, mvaMetcov00, mvaMetcov01,mvaMetcov10,mvaMetcov11, metcov00_v2, metcov01_v2, metcov10_v2,metcov11_v2;
float genM,genpT,genpX,genpY,vispX,vispY;
float met_JERDown,met_JESDown,met_UESDown,met_MESDown,met_EESDown,met_TESDown,met_PESDown;
float met_JERUp,met_JESUp,met_UESUp,met_MESUp,met_EESUp,met_TESUp,met_PESUp;
float metphi_JERDown,metphi_JESDown,metphi_UESDown,metphi_MESDown,metphi_EESDown,metphi_TESDown,metphi_PESDown;
float metphi_JERUp,metphi_JESUp,metphi_UESUp,metphi_MESUp,metphi_EESUp,metphi_TESUp,metphi_PESUp;
float genDR_2;
float byVLooseIsolationRerunMVArun2v1DBoldDMwLT_2, byVTightIsolationRerunMVArun2v1DBoldDMwLT_2, byLooseIsolationRerunMVArun2v1DBoldDMwLT_2, byMediumIsolationRerunMVArun2v1DBoldDMwLT_2, byTightIsolationRerunMVArun2v1DBoldDMwLT_2, byVVTightIsolationRerunMVArun2v1DBoldDMwLT_2,byIsolationRerunMVA3oldDMwLTraw_2;
float matchIsoMu22eta2p1_2,matchIsoTkMu22eta2p1_2,matchIsoMu22_2,matchIsoTkMu22_2,matchIsoMu24_2,matchIsoTkMu24_2,filterIsoMu22eta2p1_2,filterIsoTkMu22eta2p1_2,filterIsoMu22_2,filterIsoTkMu22_2,filterIsoMu24_2,filterIsoTkMu24_2,matchIsoMu19Tau20_3,matchIsoMu21Tau20_3,filterIsoMu19Tau20_3,filterIsoMu21Tau20_3;
int njets_JetAbsoluteFlavMapDown,njets_JetAbsoluteMPFBiasDown,njets_JetAbsoluteScaleDown,njets_JetAbsoluteStatDown,njets_JetEnDown,njets_JetFlavorQCDDown,njets_JetFragmentationDown,njets_JetPileUpDataMCDown,njets_JetPileUpPtBBDown,njets_JetPileUpPtEC1Down,njets_JetPileUpPtEC2Down,njets_JetPileUpPtHFDown,njets_JetPileUpPtRefDown,njets_JetRelativeBalDown,njets_JetRelativeFSRDown,njets_JetRelativeJEREC1Down,njets_JetRelativeJEREC2Down,njets_JetRelativeJERHFDown,njets_JetRelativePtBBDown,njets_JetRelativePtEC1Down,njets_JetRelativePtEC2Down,njets_JetRelativePtHFDown,njets_JetRelativeStatECDown,njets_JetRelativeStatFSRDown,njets_JetRelativeStatHFDown,njets_JetSinglePionECALDown,njets_JetSinglePionHCALDown,njets_JetTimePtEtaDown;
int njets_JetAbsoluteFlavMapUp,njets_JetAbsoluteMPFBiasUp,njets_JetAbsoluteScaleUp,njets_JetAbsoluteStatUp,njets_JetEnUp,njets_JetFlavorQCDUp,njets_JetFragmentationUp,njets_JetPileUpDataMCUp,njets_JetPileUpPtBBUp,njets_JetPileUpPtEC1Up,njets_JetPileUpPtEC2Up,njets_JetPileUpPtHFUp,njets_JetPileUpPtRefUp,njets_JetRelativeBalUp,njets_JetRelativeFSRUp,njets_JetRelativeJEREC1Up,njets_JetRelativeJEREC2Up,njets_JetRelativeJERHFUp,njets_JetRelativePtBBUp,njets_JetRelativePtEC1Up,njets_JetRelativePtEC2Up,njets_JetRelativePtHFUp,njets_JetRelativeStatECUp,njets_JetRelativeStatFSRUp,njets_JetRelativeStatHFUp,njets_JetSinglePionECALUp,njets_JetSinglePionHCALUp,njets_JetTimePtEtaUp;
float mjj_JetAbsoluteFlavMapDown,mjj_JetAbsoluteMPFBiasDown,mjj_JetAbsoluteScaleDown,mjj_JetAbsoluteStatDown,mjj_JetEnDown,mjj_JetFlavorQCDDown,mjj_JetFragmentationDown,mjj_JetPileUpDataMCDown,mjj_JetPileUpPtBBDown,mjj_JetPileUpPtEC1Down,mjj_JetPileUpPtEC2Down,mjj_JetPileUpPtHFDown,mjj_JetPileUpPtRefDown,mjj_JetRelativeBalDown,mjj_JetRelativeFSRDown,mjj_JetRelativeJEREC1Down,mjj_JetRelativeJEREC2Down,mjj_JetRelativeJERHFDown,mjj_JetRelativePtBBDown,mjj_JetRelativePtEC1Down,mjj_JetRelativePtEC2Down,mjj_JetRelativePtHFDown,mjj_JetRelativeStatECDown,mjj_JetRelativeStatFSRDown,mjj_JetRelativeStatHFDown,mjj_JetSinglePionECALDown,mjj_JetSinglePionHCALDown,mjj_JetTimePtEtaDown;
float mjj_JetAbsoluteFlavMapUp,mjj_JetAbsoluteMPFBiasUp,mjj_JetAbsoluteScaleUp,mjj_JetAbsoluteStatUp,mjj_JetEnUp,mjj_JetFlavorQCDUp,mjj_JetFragmentationUp,mjj_JetPileUpDataMCUp,mjj_JetPileUpPtBBUp,mjj_JetPileUpPtEC1Up,mjj_JetPileUpPtEC2Up,mjj_JetPileUpPtHFUp,mjj_JetPileUpPtRefUp,mjj_JetRelativeBalUp,mjj_JetRelativeFSRUp,mjj_JetRelativeJEREC1Up,mjj_JetRelativeJEREC2Up,mjj_JetRelativeJERHFUp,mjj_JetRelativePtBBUp,mjj_JetRelativePtEC1Up,mjj_JetRelativePtEC2Up,mjj_JetRelativePtHFUp,mjj_JetRelativeStatECUp,mjj_JetRelativeStatFSRUp,mjj_JetRelativeStatHFUp,mjj_JetSinglePionECALUp,mjj_JetSinglePionHCALUp,mjj_JetTimePtEtaUp;
float flag_BadChargedCandidate, flag_BadPFMuon, flag_EcalDeadCellTriggerPrimitive, flag_HBHENoise, flag_HBHENoiseIso, flag_badCloneMuon, flag_badGlobalMuon, flag_eeBadSc, flag_globalTightHalo2016, flag_goodVertices;
float passDoubleMu, matchDoubleMu_1, matchDoubleMu_2;

RecoilCorrector recoilPFMetCorrector("SMH_et_2016/HTT-utilities/RecoilCorrections/data/Type1_PFMET_2017.root");
//MEtSys metSys("SMH_et_2016/HTT-utilities/RecoilCorrections/data/PFMEtSys_2017.root");

void fillTree(TTree *Run_Tree, HTauTauTree_mmt *tree, int entry_tree, int recoil, bool ismc, int year){
    tree->GetEntry(entry_tree);
    run = tree->run;
    lumi = tree->lumi;
    evt =tree->evt;
    aMCatNLO_weight = tree->GenWeight;

    passMu24=tree->IsoMu24Pass;
    matchMu24_2=tree->m2MatchesIsoMu24Path;
    filterMu24_2=tree->m2MatchesIsoMu24Filter;
    matchMu24_1=tree->m1MatchesIsoMu24Path;
    filterMu24_1=tree->m1MatchesIsoMu24Filter;
    passMu27=tree->IsoMu27Pass;
    matchMu27_2=tree->m2MatchesIsoMu27Path;
    filterMu27_2=tree->m2MatchesIsoMu27Filter;
    matchMu27_1=tree->m1MatchesIsoMu27Path;
    filterMu27_1=tree->m1MatchesIsoMu27Filter;
    passMu22eta2p1=tree->singleIsoMu22eta2p1Pass;
    passTkMu22eta2p1=tree->singleIsoTkMu22eta2p1Pass;
    matchMu22eta2p1_1=tree->m1MatchesIsoMu22eta2p1Path;
    matchTkMu22eta2p1_1=tree->m1MatchesIsoTkMu22eta2p1Path;
    matchMu22eta2p1_2=tree->m2MatchesIsoMu22eta2p1Path;
    matchTkMu22eta2p1_2=tree->m2MatchesIsoTkMu22eta2p1Path;
    filterMu22eta2p1_1=tree->m1MatchesIsoMu22eta2p1Filter;
    filterTkMu22eta2p1_1=tree->m1MatchesIsoTkMu22eta2p1Filter;
    filterMu22eta2p1_2=tree->m2MatchesIsoMu22eta2p1Filter;
    filterTkMu22eta2p1_2=tree->m2MatchesIsoTkMu22eta2p1Filter;

    genpX=tree->genpX;
    genpY=tree->genpY;
    genpT=tree->genpT;
    genM=tree->genM;
    vispX=tree->vispX;
    vispY=tree->vispY;

    pt_top1=tree->topQuarkPt1;
    pt_top2=tree->topQuarkPt2;

    TLorentzVector tau1;
    TLorentzVector tau2;
    TLorentzVector tau3;
    tau1.SetPtEtaPhiM(tree->m1Pt,tree->m1Eta,tree->m1Phi,tree->m1Mass);
    tau2.SetPtEtaPhiM(tree->m2Pt,tree->m2Eta,tree->m2Phi,tree->m2Mass);
    tau3.SetPtEtaPhiM(tree->tPt,tree->tEta,tree->tPhi,tree->tMass);

    TLorentzVector mymet;
    mymet.SetPtEtaPhiM(tree->type1_pfMetEt,0,tree->type1_pfMetPhi,0);
    met_norecoil=tree->type1_pfMetEt;
    float pfmetcorr_ex=mymet.Px();
    float pfmetcorr_ey=mymet.Py();

    if (ismc && tree->tZTTGenMatching==5 && tree->tDecayMode==0) mymet=mymet+tau3-1.007*tau3;
    else if (ismc && tree->tZTTGenMatching==5 && tree->tDecayMode==1) mymet=mymet+tau3-0.998*tau3;
    else if (ismc && tree->tZTTGenMatching==5 && tree->tDecayMode==10) mymet=mymet+tau3-1.001*tau3;
    if (ismc && (tree->tZTTGenMatching==1 or tree->tZTTGenMatching==3) && tree->tDecayMode==0) mymet=mymet+tau3-1.003*tau3;
    else if (ismc && (tree->tZTTGenMatching==1 or tree->tZTTGenMatching==3) && tree->tDecayMode==1) mymet=mymet+tau3-1.036*tau3;

    if (recoil==1){
         recoilPFMetCorrector.CorrectByMeanResolution(
         mymet.Px(), // uncorrected type I pf met px (float)
         mymet.Py(), // uncorrected type I pf met py (float)
         tree->genpX, // generator Z/W/Higgs px (float)
         tree->genpY, // generator Z/W/Higgs py (float)
         tree->vispX, // generator visible Z/W/Higgs px (float)
         tree->vispY, // generator visible Z/W/Higgs py (float)
         tree->jetVeto30+1,  // number of jets (hadronic jet multiplicity) (int)
         pfmetcorr_ex, // corrected type I pf met px (float)
         pfmetcorr_ey  // corrected type I pf met py (float)
        );
    }
    if (recoil==2){
        recoilPFMetCorrector.CorrectByMeanResolution(
        mymet.Px(), // uncorrected type I pf met px (float)
        mymet.Py(), // uncorrected type I pf met py (float)
        tree->genpX, // generator Z/W/Higgs px (float)
        tree->genpY, // generator Z/W/Higgs py (float)
        tree->vispX, // generator visible Z/W/Higgs px (float)
        tree->vispY, // generator visible Z/W/Higgs py (float)
        tree->jetVeto30,  // number of jets (hadronic jet multiplicity) (int)
        pfmetcorr_ex, // corrected type I pf met px (float)
        pfmetcorr_ey  // corrected type I pf met py (float)
        );
    }
    mymet.SetPxPyPzE(pfmetcorr_ex,pfmetcorr_ey,0,sqrt(pfmetcorr_ex*pfmetcorr_ex+pfmetcorr_ey*pfmetcorr_ey));

    met=mymet.Pt();
    metphi=mymet.Phi();
    met_px=mymet.Px();
    met_py=mymet.Py();

    metSig=tree->metSig;
    metcov00=tree->metcov00;
    metcov01=tree->metcov01;
    metcov10=tree->metcov10;
    metcov11=tree->metcov11;

    njets = tree->jetVeto30;
    nbtag = tree->bjetDeepCSVVeto20Medium_2017_DR0p5;
    //nbtagL = tree->bjetCISVVeto20Loose;
    njetspt20=tree->jetVeto20;

    njets_JESDown = tree->jetVeto30_JetEnDown;
    njetspt20_JESDown=tree->jetVeto20_JetEnDown;
    njets_JESUp = tree->jetVeto30_JetEnUp;
    njetspt20_JESUp=tree->jetVeto20_JetEnUp;

    gen_match_1=tree->m1ZTTGenMatching;
    gen_match_2=tree->m2ZTTGenMatching;
    gen_match_3=tree->tZTTGenMatching;

    extraelec_veto=(tree->eVetoZTTp001dxyzR0>0);
    extramuon_veto=(tree->muVetoZTTp001dxyzR0>2);
    dilepton_veto=(tree->dimuonVeto>0);
 
    l3_decayMode=tree->tDecayMode;

    if (ismc && tree->tZTTGenMatching==5 && tree->tDecayMode==0) tau2=tau2*1.007;
    else if (ismc && tree->tZTTGenMatching==5 && tree->tDecayMode==1) tau2=tau2*0.998;
    else if (ismc && tree->tZTTGenMatching==5 && tree->tDecayMode==10) tau2=tau2*1.001;
    if (ismc && (tree->tZTTGenMatching==1 or tree->tZTTGenMatching==3) && tree->tDecayMode==0) tau2=tau2*1.003;
    else if (ismc && (tree->tZTTGenMatching==1 or tree->tZTTGenMatching==3) && tree->tDecayMode==1) tau2=tau2*1.036;

    m_1 = tau1.M();
    px_1 = tau1.Px();
    py_1 = tau1.Py();
    pz_1 = tau1.Pz();
    e_1 = tau1.E();
    pt_1 = tau1.Pt();
    phi_1 = tau1.Phi();
    eta_1 = tau1.Eta();
    d0_1 = tree->m1PVDXY;
    dZ_1 = tree->m1PVDZ;
    q_1 = tree->m1Charge;
    id_m_medium_1 = tree->m1PFIDMedium;
    id_m_tight_1 = tree->m1PFIDTight;
    iso_1 = tree->m1RelPFIsoDBDefault;
    jetpt_1=tree->m1JetPt;

    m_2 = tau2.M();
    px_2 = tau2.Px();
    py_2 = tau2.Py();
    pz_2 = tau2.Pz();
    e_2 = tau2.E();
    pt_2 = tau2.Pt();
    phi_2 = tau2.Phi();
    eta_2 = tau2.Eta();
    d0_2 = tree->m2PVDXY;
    dZ_2 = tree->m2PVDZ;
    q_2 = tree->m2Charge;
    id_m_medium_2 = tree->m2PFIDMedium;
    id_m_tight_2 = tree->m2PFIDTight;
    iso_2 = tree->m2RelPFIsoDBDefault;
    jetpt_2=tree->m2JetPt;

    m_3 = tau3.M();
    if (tree->tDecayMode==0) m_3=tree->tMass;
    px_3 = tau3.Px();
    py_3 = tau3.Py();
    pz_3 = tau3.Pz();
    e_3 = tau3.E();
    pt_3 = tau3.Pt();
    phi_3 = tau3.Phi();
    eta_3 = tau3.Eta();
    dZ_3 = tree->tPVDZ;
    d0_3=tree->tPVDXY;
    iso_3=tree->tByIsolationMVArun2v1DBoldDMwLTraw;
    q_3 = tree->tCharge;
    trackpt_3=tree->tLeadTrackPt;
    numGenJets=tree->numGenJets;
    jetPt_3=tree->tJetPt;
    jetpt_3=tree->tJetPt;

    againstMuonTight3_3 = tree->tAgainstMuonTight3;
    againstMuonLoose3_3 = tree->tAgainstMuonLoose3;
    againstElectronVLooseMVA6_3 = tree->tAgainstElectronVLooseMVA62018;
    againstElectronLooseMVA6_3 = tree->tAgainstElectronLooseMVA62018;
    againstElectronMediumMVA6_3 = tree->tAgainstElectronMediumMVA62018;
    againstElectronTightMVA6_3 = tree->tAgainstElectronTightMVA62018;
    againstElectronVTightMVA6_3 = tree->tAgainstElectronVTightMVA62018;
    byVLooseIsolationMVArun2v1DBoldDMwLT_3 = tree->tRerunMVArun2v2DBoldDMwLTVLoose;
    byLooseIsolationMVArun2v1DBoldDMwLT_3 = tree->tRerunMVArun2v2DBoldDMwLTLoose;
    byMediumIsolationMVArun2v1DBoldDMwLT_3 = tree->tRerunMVArun2v2DBoldDMwLTMedium;
    byTightIsolationMVArun2v1DBoldDMwLT_3 = tree->tRerunMVArun2v2DBoldDMwLTTight;
    byVTightIsolationMVArun2v1DBoldDMwLT_3 = tree->tRerunMVArun2v2DBoldDMwLTVTight;
    byVVTightIsolationMVArun2v1DBoldDMwLT_3 = tree->tRerunMVArun2v2DBoldDMwLTVVTight;
    byCombinedIsolationDeltaBetaCorrRaw3Hits_3=tree->tByCombinedIsolationDeltaBetaCorrRaw3Hits;
    byIsolationMVA3oldDMwoLTraw_3=tree->tByIsolationMVArun2v1DBoldDMwLTraw;
    decayModeFinding_3=tree->tDecayModeFinding;
    deepVVVLooseVSjet_3=tree->tVVVLooseDeepTau2017v2p1VSjet;
    deepVVLooseVSjet_3=tree->tVVLooseDeepTau2017v2p1VSjet;
    deepVLooseVSjet_3=tree->tVLooseDeepTau2017v2p1VSjet;
    deepLooseVSjet_3=tree->tLooseDeepTau2017v2p1VSjet;
    deepMediumVSjet_3=tree->tMediumDeepTau2017v2p1VSjet;
    deepTightVSjet_3=tree->tTightDeepTau2017v2p1VSjet;
    deepVTightVSjet_3=tree->tVTightDeepTau2017v2p1VSjet;
    deepVVVLooseVSmu_3=tree->tVVVLooseDeepTau2017v2p1VSmu;
    deepVVLooseVSmu_3=tree->tVVLooseDeepTau2017v2p1VSmu;
    deepVLooseVSmu_3=tree->tVLooseDeepTau2017v2p1VSmu;
    deepLooseVSmu_3=tree->tLooseDeepTau2017v2p1VSmu;
    deepMediumVSmu_3=tree->tMediumDeepTau2017v2p1VSmu;
    deepTightVSmu_3=tree->tTightDeepTau2017v2p1VSmu;
    deepVTightVSmu_3=tree->tVTightDeepTau2017v2p1VSmu;
    deepVVVLooseVSe_3=tree->tVVVLooseDeepTau2017v2p1VSe;
    deepVVLooseVSe_3=tree->tVVLooseDeepTau2017v2p1VSe;
    deepVLooseVSe_3=tree->tVLooseDeepTau2017v2p1VSe;
    deepLooseVSe_3=tree->tLooseDeepTau2017v2p1VSe;
    deepMediumVSe_3=tree->tMediumDeepTau2017v2p1VSe;
    deepTightVSe_3=tree->tTightDeepTau2017v2p1VSe;
    deepVTightVSe_3=tree->tVTightDeepTau2017v2p1VSe;
    
    jpt_1=tree->j1pt;
    jpt_2=tree->j2pt;
    jeta_1=tree->j1eta;
    jeta_2=tree->j2eta;
    jphi_1=tree->j1phi;
    jphi_2=tree->j2phi;
    jcsv_1=tree->j1csv;
    jcsv_2=tree->j2csv;

    bpt_1=tree->jb1pt_2017;
    bpt_2=tree->jb2pt_2017;
    beta_1=tree->jb1eta_2017;
    beta_2=tree->jb2eta_2017;
    bphi_1=tree->jb1phi_2017;
    bphi_2=tree->jb2phi_2017;
    //bcsv_1=tree->jb1csv;
    //bcsv_2=tree->jb2csv;
    bflavor_1=tree->jb1hadronflavor_2017;
    bflavor_2=tree->jb2hadronflavor_2017;
   

  NUP=tree->NUP;
  npu=tree->nTruePU;
  npv=tree->nvtx;
  rho=tree->rho;

  extratau_veto=tree->tauVetoPt20Loose3HitsVtx;
  Run_Tree->Fill();
}

#endif


