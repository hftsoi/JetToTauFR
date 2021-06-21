#include <TLatex.h>
#include <TGraph.h>

#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
//#include "iostream.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "TMatrixD.h"
#include "TMinuit.h"
//#include "HttStyles.h"

double square(double x)
{
  return x*x;
}

void makeBinsInteger(TH1* histogram_pass, TH1* histogram_fail)
{
  assert(histogram_pass->GetNbinsX() == histogram_fail->GetNbinsX());
  int numBins = histogram_pass->GetNbinsX();
  for ( int iBin = 1; iBin <= numBins; ++iBin ) {
    if (histogram_pass->GetBinContent(iBin)<0){ histogram_pass->SetBinContent(iBin,0); histogram_pass->SetBinError(iBin,0);}
    if (histogram_fail->GetBinContent(iBin)<0){ histogram_fail->SetBinContent(iBin,0); histogram_fail->SetBinError(iBin,0);}
    double binContent_sum = histogram_pass->GetBinContent(iBin) + histogram_fail->GetBinContent(iBin);
    double binError2_sum = square(histogram_pass->GetBinError(iBin)) + square(histogram_fail->GetBinError(iBin));
    double binError_sum = TMath::Sqrt(binError2_sum);
    if ( binContent_sum > 0. && binError_sum > 0. ) {
      double nEff = square(binContent_sum/binError_sum);
      double avWeight = binContent_sum/nEff;
      double binContent_pass = TMath::Nint(histogram_pass->GetBinContent(iBin)/avWeight);
      double binError_pass = TMath::Sqrt(binContent_pass);
      histogram_pass->SetBinContent(iBin, binContent_pass);
      histogram_pass->SetBinError(iBin, binError_pass);
      double binContent_fail = TMath::Nint(histogram_fail->GetBinContent(iBin)/avWeight);
      double binError_fail = TMath::Sqrt(binContent_fail);
      histogram_fail->SetBinContent(iBin, binContent_fail);
      histogram_fail->SetBinError(iBin, binError_fail);
    }
  }
}

double fitFunction(double x, double par0, double par1) {
    return par0 + par1 *(x-40);
}

Double_t fitFunc_Exp3Par(Double_t *x, Double_t *par) {
    return par[0] + par[1]* (x[0]-40);
}

Double_t fitFunc_Line2Par(Double_t *x, Double_t *par) {
    return par[0] + par[1] * x[0] + par[2] *0;
}

TF1 *M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, TH2F * hist2D_lep, Double_t fMin, Double_t fMax, int year) {
    //SetStyle();
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    TH1D *histogram_pass = (TH1D*) Numerator->Rebin(1);
    TH1D *histogram_fail = (TH1D*) Denumerator->Rebin(1);

    makeBinsInteger(histogram_pass, histogram_fail);

    TGraphAsymmErrors* TGraph_FR = new TGraphAsymmErrors(26);
    TGraph_FR->Divide(histogram_pass, histogram_fail, "pois");

    Double_t *yg = TGraph_FR->GetY();
    for (int i = 0; i<3; i++) printf("yg[%d] = %g\n", i,yg[i]);

    //cout<<TGraph_FR->GetBinContent(1)<<" "<<TGraph_FR->GetBinContent(2)<<" "<<TGraph_FR->GetBinContent(11)<<endl;

    const int nPar = 2; // number of parameters in the fit

    TF1 * theFit = new TF1("theFit", fitFunc_Exp3Par, fMin, fMax, nPar);

    theFit->SetParameter(0, 0.1);
    theFit->SetParameter(1, -0.01);

    float xAxisMax = 500;
    TGraph_FR->Fit("theFit", "R0");

    TCanvas* canvas = new TCanvas("canvas", "", 800,727);
    canvas->SetTitle("");
    canvas->SetGrid();
    TGraph_FR->GetYaxis()->SetRangeUser(0.00, 0.16);
    TGraph_FR->GetYaxis()->SetTitle("fake rate");
    TGraph_FR->GetYaxis()->SetTitleOffset(1.5);
    TGraph_FR->GetXaxis()->SetRangeUser(20, 160);
    TGraph_FR->GetXaxis()->SetTitle("#tau_{h} p_{T} [GeV]");
    TGraph_FR->SetTitle("");
    TGraph_FR->Draw("PAE");
    TGraph_FR->SetLineWidth(3);
    std::string outNaming = "plots/fit" + num + "_" + denum + ".png";
    if (year==2016) outNaming = "plots_2016/fit" + num + "_" + denum + ".png";
    if (year==2017) outNaming = "plots_2017/fit" + num + "_" + denum + ".png";
    if (year==2018) outNaming = "plots_2018/fit" + num + "_" + denum + ".png";
    TLatex t = TLatex();
    t.SetNDC();
    t.SetTextFont(42);
    t.SetTextAlign(12);
    t.SetTextSize(0.04);
    if (year==2016) t.DrawLatex(0.55, .95, "36.3 fb^{-1} (2016, 13 TeV)");
    if (year==2017) t.DrawLatex(0.55, .95, "41.5 fb^{-1} (2017, 13 TeV)");
    if (year==2018) t.DrawLatex(0.55, .95, "59.7 fb^{-1} (2018, 13 TeV)");
    float aup; float adown; float bup; float bdown;
    if (denum.find("hpt") < 140 or denum.find("Pt") < 140){
       //theFit->Draw("SAME");
       //theFit->SetLineColor(2);
       std::string lepName="";
       TLatex t3 = TLatex();
       t3.SetNDC();
       t3.SetTextFont(42);
       t3.SetTextAlign(12);
       t3.SetTextSize(0.040);
       std::string region;

       Double_t TauLegParameters[nPar];
       theFit->GetParameters(TauLegParameters);

       for (int i = 0; i < nPar; i++) {
           hist2D_lep->SetBinContent(WP, (2 * i + 1), TauLegParameters[i]);
           hist2D_lep->SetBinContent(WP, (2 * i + 2), theFit->GetParError(i));
       }

       TLatex tt = TLatex();
       tt.SetNDC();
       tt.SetTextFont(42);
       tt.SetTextAlign(12);
       tt.SetTextSize(0.025);
       char buffer[100];
       //if (denum.find("Pt") < 140){
            snprintf(buffer, sizeof(buffer), "f_{#tau}(p_{T}) = %.4f+%.4f#times(p_{T}-40)", TauLegParameters[0], TauLegParameters[1]);
       //}
       //if (denum.find("Eta") < 140){
       //     snprintf(buffer, sizeof(buffer), "f_{#tau}(|#eta|) = %.4f+%.4f#times(|#eta|-1)", TauLegParameters[0], TauLegParameters[1]);
       //}
       //tt.DrawLatex(0.14,0.80,buffer);

       Double_t matrix[2][2];
       gMinuit->mnemat(&matrix[0][0],2);
       TMatrixD mat_D(2,2);
        for (int i=0; i<2; ++i){
           for (int j=0; j<2; ++j){
           	mat_D[i][j]=matrix[i][j];
           }
       }
       TMatrixDEigen mat_sym=TMatrixDEigen (mat_D);
       TMatrixD eigenValues=mat_sym.GetEigenValues();
       TMatrixD eigenVectors=mat_sym.GetEigenVectors();
       TMatrixD eigenVectorsInverted=mat_sym.GetEigenVectors();
       aup = TauLegParameters[0]+eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0])+eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
       bup = TauLegParameters[1]+eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0])+eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);
       adown = TauLegParameters[0]-eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0])-eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
       bdown = TauLegParameters[1]-eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0])-eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);

       float au1=TauLegParameters[0]+eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0]);
       float bu1=TauLegParameters[1]+eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0]);
       float ad1=TauLegParameters[0]-eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0]);
       float bd1=TauLegParameters[1]-eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0]);
       float au2=TauLegParameters[0]+eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
       float bu2=TauLegParameters[1]+eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);
       float ad2=TauLegParameters[0]-eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
       float bd2=TauLegParameters[1]-eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);

cout<<au1<<" "<<bu1<<endl;
cout<<ad1<<" "<<bd1<<endl;
cout<<au2<<" "<<bu2<<endl;
cout<<ad2<<" "<<bd2<<endl;
/*
       TF1 * theFitup1 = new TF1("theFit", fitFunc_Exp3Par, fMin, fMax, nPar);
       theFitup1->SetParameter(0, au1);
       theFitup1->SetParameter(1, bu1);
       theFitup1->SetLineColor(kViolet+1);
       theFitup1->Draw("same");
       TF1 * theFitup2 = new TF1("theFit", fitFunc_Exp3Par, fMin, fMax, nPar);
       theFitup2->SetParameter(0, au2);
       theFitup2->SetParameter(1, bu2);
       theFitup2->SetLineColor(kGreen-3);
       theFitup2->Draw("same");
       TF1 * theFitdown1 = new TF1("theFit", fitFunc_Exp3Par, fMin, fMax, nPar);
       theFitdown1->SetParameter(0, ad1);
       theFitdown1->SetParameter(1, bd1);
       theFitdown1->SetLineColor(kViolet+1);
       theFitdown1->Draw("same");
       TF1 * theFitdown2 = new TF1("theFit", fitFunc_Exp3Par, fMin, fMax, nPar);
       theFitdown2->SetParameter(0, ad2);
       theFitdown2->SetParameter(1, bd2);
       theFitdown2->SetLineColor(kGreen-3);
       theFitdown2->Draw("same");
       TLegend *l = new TLegend(0.55, 0.74, 0.7, 0.89, NULL, "brNDC");
       l->SetBorderSize(0);
       l->SetFillColor(0);
       l->SetTextSize(.03);
       l->SetFillColor(0);
       l->AddEntry(theFit, "Best fit", "l");
       l->AddEntry(theFitup1, "1st uncertainty #pm 1#sigma", "l");
       l->AddEntry(theFitup2, "2nd uncertainty #pm 1#sigma", "l");
       l->Draw("same");*/
    }

    canvas->SaveAs(outNaming.c_str());

    if (denum.find("Eta") < 140 or denum.find("Pt") < 140){
       hist2D_lep->SetBinContent(WP, 5, aup);
       hist2D_lep->SetBinContent(WP, 7, bup);
       hist2D_lep->SetBinContent(WP, 9, adown);
       hist2D_lep->SetBinContent(WP, 11, bdown);
    }

    std::string fithistofile="FitHistograms_tauFR_2016.root";
    if (year==2017) fithistofile="FitHistograms_tauFR_2017.root";
    if (year==2018) fithistofile="FitHistograms_tauFR_2018.root";
    TFile *FR_H = new TFile(fithistofile.c_str(), "UPDATE");
    FR_H->cd();
    TGraph_FR->SetName(TString(num) + "_" + TString(denum));
    TGraph_FR->Write();
    FR_H->Close();

    return theFit;
}

void FitFakeRateTau(int year) {

    std::string fitvaluefile="FitValues_tauFR_2016.root";
    if (year==2017) fitvaluefile="FitValues_tauFR_2017.root";
    if (year==2018) fitvaluefile="FitValues_tauFR_2018.root";
    TFile *FR_File = new TFile(fitvaluefile.c_str(), "RECREATE");

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 40, 0, 40, 40, 0, 40);

    Double_t fMin = 20;
    Double_t fMax = 150;
    std::string datafile="files_mmt_2016/DataSub.root";
    if (year==2017) datafile="files_mmt_2017/DataSub.root";
    if (year==2018) datafile="files_mmt_2018/DataSub.root";
/*
    TF1* m110 = M_FR(10, "Exp3Par", datafile, "hpt_dm0_deeptight", "hpt_dm0_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m111 = M_FR(11, "Exp3Par", datafile, "hpt_dm0_deepverytight", "hpt_dm0_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m112 = M_FR(12, "Exp3Par", datafile, "hpt_dm0_deepmedium", "hpt_dm0_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m113 = M_FR(13, "Exp3Par", datafile, "hpt_dm0_deeploose", "hpt_dm0_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m114 = M_FR(14, "Exp3Par", datafile, "hpt_dm0_deepveryloose", "hpt_dm0_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m115 = M_FR(15, "Exp3Par", datafile, "hpt_dm0_deepveryveryloose", "hpt_dm0_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m116 = M_FR(16, "Exp3Par", datafile, "hpt_dm1_deeptight", "hpt_dm1_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m117 = M_FR(17, "Exp3Par", datafile, "hpt_dm1_deepverytight", "hpt_dm1_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m118 = M_FR(18, "Exp3Par", datafile, "hpt_dm1_deepmedium", "hpt_dm1_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m119 = M_FR(19, "Exp3Par", datafile, "hpt_dm1_deeploose", "hpt_dm1_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m120 = M_FR(20, "Exp3Par", datafile, "hpt_dm1_deepveryloose", "hpt_dm1_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m121 = M_FR(21, "Exp3Par", datafile, "hpt_dm1_deepveryveryloose", "hpt_dm1_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m122 = M_FR(22, "Exp3Par", datafile, "hpt_dm10_deeptight", "hpt_dm10_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m123 = M_FR(23, "Exp3Par", datafile, "hpt_dm10_deepverytight", "hpt_dm10_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m124 = M_FR(24, "Exp3Par", datafile, "hpt_dm10_deepmedium", "hpt_dm10_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m125 = M_FR(25, "Exp3Par", datafile, "hpt_dm10_deeploose", "hpt_dm10_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m126 = M_FR(26, "Exp3Par", datafile, "hpt_dm10_deepveryloose", "hpt_dm10_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m127 = M_FR(27, "Exp3Par", datafile, "hpt_dm10_deepveryveryloose", "hpt_dm10_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m128 = M_FR(28, "Exp3Par", datafile, "hpt_dm11_deeptight", "hpt_dm11_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m129 = M_FR(29, "Exp3Par", datafile, "hpt_dm11_deepverytight", "hpt_dm11_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m130 = M_FR(30, "Exp3Par", datafile, "hpt_dm11_deepmedium", "hpt_dm11_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m131 = M_FR(31, "Exp3Par", datafile, "hpt_dm11_deeploose", "hpt_dm11_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m132 = M_FR(32, "Exp3Par", datafile, "hpt_dm11_deepveryloose", "hpt_dm11_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m133 = M_FR(33, "Exp3Par", datafile, "hpt_dm11_deepveryveryloose", "hpt_dm11_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);

    TF1* m210 = M_FR(410, "Exp3Par", datafile, "hpt_dm0_Te_Tmu_deeptight", "hpt_dm0_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m211 = M_FR(411, "Exp3Par", datafile, "hpt_dm0_Te_Tmu_deepverytight", "hpt_dm0_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m212 = M_FR(412, "Exp3Par", datafile, "hpt_dm0_Te_Tmu_deepmedium", "hpt_dm0_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m213 = M_FR(413, "Exp3Par", datafile, "hpt_dm0_Te_Tmu_deeploose", "hpt_dm0_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m214 = M_FR(414, "Exp3Par", datafile, "hpt_dm0_Te_Tmu_deepveryloose", "hpt_dm0_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m215 = M_FR(415, "Exp3Par", datafile, "hpt_dm0_Te_Tmu_deepveryveryloose", "hpt_dm0_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m216 = M_FR(416, "Exp3Par", datafile, "hpt_dm1_Te_Tmu_deeptight", "hpt_dm1_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m217 = M_FR(417, "Exp3Par", datafile, "hpt_dm1_Te_Tmu_deepverytight", "hpt_dm1_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m218 = M_FR(418, "Exp3Par", datafile, "hpt_dm1_Te_Tmu_deepmedium", "hpt_dm1_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m219 = M_FR(419, "Exp3Par", datafile, "hpt_dm1_Te_Tmu_deeploose", "hpt_dm1_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m220 = M_FR(420, "Exp3Par", datafile, "hpt_dm1_Te_Tmu_deepveryloose", "hpt_dm1_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m221 = M_FR(421, "Exp3Par", datafile, "hpt_dm1_Te_Tmu_deepveryveryloose", "hpt_dm1_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m222 = M_FR(422, "Exp3Par", datafile, "hpt_dm10_Te_Tmu_deeptight", "hpt_dm10_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m223 = M_FR(423, "Exp3Par", datafile, "hpt_dm10_Te_Tmu_deepverytight", "hpt_dm10_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m224 = M_FR(424, "Exp3Par", datafile, "hpt_dm10_Te_Tmu_deepmedium", "hpt_dm10_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m225 = M_FR(425, "Exp3Par", datafile, "hpt_dm10_Te_Tmu_deeploose", "hpt_dm10_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m226 = M_FR(426, "Exp3Par", datafile, "hpt_dm10_Te_Tmu_deepveryloose", "hpt_dm10_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m227 = M_FR(427, "Exp3Par", datafile, "hpt_dm10_Te_Tmu_deepveryveryloose", "hpt_dm10_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m228 = M_FR(428, "Exp3Par", datafile, "hpt_dm11_Te_Tmu_deeptight", "hpt_dm11_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m229 = M_FR(429, "Exp3Par", datafile, "hpt_dm11_Te_Tmu_deepverytight", "hpt_dm11_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m230 = M_FR(430, "Exp3Par", datafile, "hpt_dm11_Te_Tmu_deepmedium", "hpt_dm11_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m231 = M_FR(431, "Exp3Par", datafile, "hpt_dm11_Te_Tmu_deeploose", "hpt_dm11_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m232 = M_FR(432, "Exp3Par", datafile, "hpt_dm11_Te_Tmu_deepveryloose", "hpt_dm11_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m233 = M_FR(433, "Exp3Par", datafile, "hpt_dm11_Te_Tmu_deepveryveryloose", "hpt_dm11_Te_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);

    TF1* m310 = M_FR(110, "Exp3Par", datafile, "hpt_dm0_VLe_Tmu_deeptight", "hpt_dm0_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m311 = M_FR(111, "Exp3Par", datafile, "hpt_dm0_VLe_Tmu_deepverytight", "hpt_dm0_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m312 = M_FR(112, "Exp3Par", datafile, "hpt_dm0_VLe_Tmu_deepmedium", "hpt_dm0_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m313 = M_FR(113, "Exp3Par", datafile, "hpt_dm0_VLe_Tmu_deeploose", "hpt_dm0_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m314 = M_FR(114, "Exp3Par", datafile, "hpt_dm0_VLe_Tmu_deepveryloose", "hpt_dm0_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m315 = M_FR(115, "Exp3Par", datafile, "hpt_dm0_VLe_Tmu_deepveryveryloose", "hpt_dm0_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m316 = M_FR(116, "Exp3Par", datafile, "hpt_dm1_VLe_Tmu_deeptight", "hpt_dm1_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m317 = M_FR(117, "Exp3Par", datafile, "hpt_dm1_VLe_Tmu_deepverytight", "hpt_dm1_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m318 = M_FR(118, "Exp3Par", datafile, "hpt_dm1_VLe_Tmu_deepmedium", "hpt_dm1_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m319 = M_FR(119, "Exp3Par", datafile, "hpt_dm1_VLe_Tmu_deeploose", "hpt_dm1_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m320 = M_FR(120, "Exp3Par", datafile, "hpt_dm1_VLe_Tmu_deepveryloose", "hpt_dm1_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m321 = M_FR(121, "Exp3Par", datafile, "hpt_dm1_VLe_Tmu_deepveryveryloose", "hpt_dm1_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m322 = M_FR(122, "Exp3Par", datafile, "hpt_dm10_VLe_Tmu_deeptight", "hpt_dm10_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m323 = M_FR(123, "Exp3Par", datafile, "hpt_dm10_VLe_Tmu_deepverytight", "hpt_dm10_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m324 = M_FR(124, "Exp3Par", datafile, "hpt_dm10_VLe_Tmu_deepmedium", "hpt_dm10_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m325 = M_FR(125, "Exp3Par", datafile, "hpt_dm10_VLe_Tmu_deeploose", "hpt_dm10_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m326 = M_FR(126, "Exp3Par", datafile, "hpt_dm10_VLe_Tmu_deepveryloose", "hpt_dm10_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m327 = M_FR(127, "Exp3Par", datafile, "hpt_dm10_VLe_Tmu_deepveryveryloose", "hpt_dm10_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m328 = M_FR(128, "Exp3Par", datafile, "hpt_dm11_VLe_Tmu_deeptight", "hpt_dm11_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m329 = M_FR(129, "Exp3Par", datafile, "hpt_dm11_VLe_Tmu_deepverytight", "hpt_dm11_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m330 = M_FR(130, "Exp3Par", datafile, "hpt_dm11_VLe_Tmu_deepmedium", "hpt_dm11_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m331 = M_FR(131, "Exp3Par", datafile, "hpt_dm11_VLe_Tmu_deeploose", "hpt_dm11_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m332 = M_FR(132, "Exp3Par", datafile, "hpt_dm11_VLe_Tmu_deepveryloose", "hpt_dm11_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m333 = M_FR(133, "Exp3Par", datafile, "hpt_dm11_VLe_Tmu_deepveryveryloose", "hpt_dm11_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);

    TF1* m410 = M_FR(210, "Exp3Par", datafile, "hpt_dm0_Te_VLmu_deeptight", "hpt_dm0_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m411 = M_FR(211, "Exp3Par", datafile, "hpt_dm0_Te_VLmu_deepverytight", "hpt_dm0_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m412 = M_FR(212, "Exp3Par", datafile, "hpt_dm0_Te_VLmu_deepmedium", "hpt_dm0_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m413 = M_FR(213, "Exp3Par", datafile, "hpt_dm0_Te_VLmu_deeploose", "hpt_dm0_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m414 = M_FR(214, "Exp3Par", datafile, "hpt_dm0_Te_VLmu_deepveryloose", "hpt_dm0_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m415 = M_FR(215, "Exp3Par", datafile, "hpt_dm0_Te_VLmu_deepveryveryloose", "hpt_dm0_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m416 = M_FR(216, "Exp3Par", datafile, "hpt_dm1_Te_VLmu_deeptight", "hpt_dm1_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m417 = M_FR(217, "Exp3Par", datafile, "hpt_dm1_Te_VLmu_deepverytight", "hpt_dm1_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m418 = M_FR(218, "Exp3Par", datafile, "hpt_dm1_Te_VLmu_deepmedium", "hpt_dm1_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m419 = M_FR(219, "Exp3Par", datafile, "hpt_dm1_Te_VLmu_deeploose", "hpt_dm1_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m420 = M_FR(220, "Exp3Par", datafile, "hpt_dm1_Te_VLmu_deepveryloose", "hpt_dm1_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m421 = M_FR(221, "Exp3Par", datafile, "hpt_dm1_Te_VLmu_deepveryveryloose", "hpt_dm1_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m422 = M_FR(222, "Exp3Par", datafile, "hpt_dm10_Te_VLmu_deeptight", "hpt_dm10_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m423 = M_FR(223, "Exp3Par", datafile, "hpt_dm10_Te_VLmu_deepverytight", "hpt_dm10_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m424 = M_FR(224, "Exp3Par", datafile, "hpt_dm10_Te_VLmu_deepmedium", "hpt_dm10_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m425 = M_FR(225, "Exp3Par", datafile, "hpt_dm10_Te_VLmu_deeploose", "hpt_dm10_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m426 = M_FR(226, "Exp3Par", datafile, "hpt_dm10_Te_VLmu_deepveryloose", "hpt_dm10_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m427 = M_FR(227, "Exp3Par", datafile, "hpt_dm10_Te_VLmu_deepveryveryloose", "hpt_dm10_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m428 = M_FR(228, "Exp3Par", datafile, "hpt_dm11_Te_VLmu_deeptight", "hpt_dm11_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m429 = M_FR(229, "Exp3Par", datafile, "hpt_dm11_Te_VLmu_deepverytight", "hpt_dm11_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m430 = M_FR(230, "Exp3Par", datafile, "hpt_dm11_Te_VLmu_deepmedium", "hpt_dm11_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m431 = M_FR(231, "Exp3Par", datafile, "hpt_dm11_Te_VLmu_deeploose", "hpt_dm11_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m432 = M_FR(232, "Exp3Par", datafile, "hpt_dm11_Te_VLmu_deepveryloose", "hpt_dm11_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m433 = M_FR(233, "Exp3Par", datafile, "hpt_dm11_Te_VLmu_deepveryveryloose", "hpt_dm11_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);

    TF1* m510 = M_FR(310, "Exp3Par", datafile, "hpt_dm0_VLe_VLmu_deeptight", "hpt_dm0_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m511 = M_FR(311, "Exp3Par", datafile, "hpt_dm0_VLe_VLmu_deepverytight", "hpt_dm0_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m512 = M_FR(312, "Exp3Par", datafile, "hpt_dm0_VLe_VLmu_deepmedium", "hpt_dm0_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m513 = M_FR(313, "Exp3Par", datafile, "hpt_dm0_VLe_VLmu_deeploose", "hpt_dm0_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m514 = M_FR(314, "Exp3Par", datafile, "hpt_dm0_VLe_VLmu_deepveryloose", "hpt_dm0_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m515 = M_FR(315, "Exp3Par", datafile, "hpt_dm0_VLe_VLmu_deepveryveryloose", "hpt_dm0_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m516 = M_FR(316, "Exp3Par", datafile, "hpt_dm1_VLe_VLmu_deeptight", "hpt_dm1_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m517 = M_FR(317, "Exp3Par", datafile, "hpt_dm1_VLe_VLmu_deepverytight", "hpt_dm1_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m518 = M_FR(318, "Exp3Par", datafile, "hpt_dm1_VLe_VLmu_deepmedium", "hpt_dm1_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m519 = M_FR(319, "Exp3Par", datafile, "hpt_dm1_VLe_VLmu_deeploose", "hpt_dm1_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m520 = M_FR(320, "Exp3Par", datafile, "hpt_dm1_VLe_VLmu_deepveryloose", "hpt_dm1_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m521 = M_FR(321, "Exp3Par", datafile, "hpt_dm1_VLe_VLmu_deepveryveryloose", "hpt_dm1_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m522 = M_FR(322, "Exp3Par", datafile, "hpt_dm10_VLe_VLmu_deeptight", "hpt_dm10_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m523 = M_FR(323, "Exp3Par", datafile, "hpt_dm10_VLe_VLmu_deepverytight", "hpt_dm10_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m524 = M_FR(324, "Exp3Par", datafile, "hpt_dm10_VLe_VLmu_deepmedium", "hpt_dm10_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m525 = M_FR(325, "Exp3Par", datafile, "hpt_dm10_VLe_VLmu_deeploose", "hpt_dm10_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m526 = M_FR(326, "Exp3Par", datafile, "hpt_dm10_VLe_VLmu_deepveryloose", "hpt_dm10_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m527 = M_FR(327, "Exp3Par", datafile, "hpt_dm10_VLe_VLmu_deepveryveryloose", "hpt_dm10_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m528 = M_FR(328, "Exp3Par", datafile, "hpt_dm11_VLe_VLmu_deeptight", "hpt_dm11_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m529 = M_FR(329, "Exp3Par", datafile, "hpt_dm11_VLe_VLmu_deepverytight", "hpt_dm11_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m530 = M_FR(330, "Exp3Par", datafile, "hpt_dm11_VLe_VLmu_deepmedium", "hpt_dm11_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m531 = M_FR(331, "Exp3Par", datafile, "hpt_dm11_VLe_VLmu_deeploose", "hpt_dm11_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m532 = M_FR(332, "Exp3Par", datafile, "hpt_dm11_VLe_VLmu_deepveryloose", "hpt_dm11_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m533 = M_FR(333, "Exp3Par", datafile, "hpt_dm11_VLe_VLmu_deepveryveryloose", "hpt_dm11_VLe_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
*/
    //TF1* m610 = M_FR(510, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_deeptight", "hpt_dmall_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m611 = M_FR(511, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_deepverytight", "hpt_dmall_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m612 = M_FR(512, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_deepmedium", "hpt_dmall_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m613 = M_FR(513, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_deeploose", "hpt_dmall_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m614 = M_FR(514, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_deepveryloose", "hpt_dmall_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m615 = M_FR(515, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_deepveryveryloose", "hpt_dmall_VLe_Tmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m622 = M_FR(522, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_1jet_deeptight", "hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m623 = M_FR(523, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_1jet_deepverytight", "hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m624 = M_FR(524, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_1jet_deepmedium", "hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m625 = M_FR(525, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_1jet_deeploose", "hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m626 = M_FR(526, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_1jet_deepveryloose", "hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m627 = M_FR(527, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_1jet_deepveryveryloose", "hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m634 = M_FR(534, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_bjet_deeptight", "hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m635 = M_FR(535, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_bjet_deepverytight", "hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m636 = M_FR(536, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_bjet_deepmedium", "hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m637 = M_FR(537, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_bjet_deeploose", "hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m638 = M_FR(538, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_bjet_deepveryloose", "hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m639 = M_FR(539, "Exp3Par", datafile, "hpt_dmall_VLe_Tmu_bjet_deepveryveryloose", "hpt_dmall_VLe_Tmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);

    //TF1* m710 = M_FR(610, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_deeptight", "hpt_dmall_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m711 = M_FR(611, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_deepverytight", "hpt_dmall_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m712 = M_FR(612, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_deepmedium", "hpt_dmall_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m713 = M_FR(613, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_deeploose", "hpt_dmall_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m714 = M_FR(614, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_deepveryloose", "hpt_dmall_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m715 = M_FR(615, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_deepveryveryloose", "hpt_dmall_Te_VLmu_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m722 = M_FR(622, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_1jet_deeptight", "hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m723 = M_FR(623, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_1jet_deepverytight", "hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m724 = M_FR(624, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_1jet_deepmedium", "hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m725 = M_FR(625, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_1jet_deeploose", "hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m726 = M_FR(626, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_1jet_deepveryloose", "hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m727 = M_FR(627, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_1jet_deepveryveryloose", "hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m734 = M_FR(634, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_bjet_deeptight", "hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m735 = M_FR(635, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_bjet_deepverytight", "hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    TF1* m736 = M_FR(636, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_bjet_deepmedium", "hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m737 = M_FR(637, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_bjet_deeploose", "hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m738 = M_FR(638, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_bjet_deepveryloose", "hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);
    //TF1* m739 = M_FR(639, "Exp3Par", datafile, "hpt_dmall_Te_VLmu_bjet_deepveryveryloose", "hpt_dmall_Te_VLmu_bjet_deepveryveryveryloose", Fit_Value_tau, fMin, fMax, year);

  
    FR_File->Write();
    FR_File->cd();
    //m11->SetName("DM0"); m11->Write();
    //m14->SetName("DM1"); m14->Write();
    //m17->SetName("DM10"); m17->Write();
    FR_File->Close();
}

