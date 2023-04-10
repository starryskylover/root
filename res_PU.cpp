#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.C"

void res_PU(){

SetAtlasStyle();

  // Double_t N_data_more50=2258, err_data_more50=47.5184, N_sig_more50=525.872, err_sig_more50=4.10708, N_data_full=7078, err_data_full=84.1309;
  // Double_t scale_factor_1=4.30, err_scale_factor_1=0.07, scale_factor_2=1.27, err_scale_factor_2=0.07;
  Double_t N_data_more50=936, err_data_more50=30.5941, N_sig_more50=247.883, err_sig_more50=2.84195, N_data_full=7078, err_data_full=84.1309;
  Double_t scale_factor_1=4.29505, err_scale_factor_1=0.0678235, scale_factor_2=1.48, err_scale_factor_2=0.26;
  // Double_t rate_PU=(N_data_more50-scale_factor_1*scale_factor_2*N_sig_more50)/(0.76*N_data_full);
  // Double_t err_rate_PU=sqrt(pow(err_data_more50/(N_data_full*0.76),2)+pow(rate_PU*err_data_full/N_data_full,2)+pow(scale_factor_2*N_sig_more50*err_scale_factor_1/(0.76*N_data_full),2)+pow(scale_factor_1*N_sig_more50*err_scale_factor_2/(0.76*N_data_full),2)+pow(scale_factor_1*scale_factor_2*err_sig_more50/(0.76*N_data_full),2));
  Double_t rate_PU=(N_data_more50-scale_factor_1*scale_factor_2*N_sig_more50)/(0.32*N_data_full);
  Double_t err_rate_PU=sqrt(pow(err_data_more50/(N_data_full*0.32),2)+pow(rate_PU*err_data_full/N_data_full,2)+pow(scale_factor_2*N_sig_more50*err_scale_factor_1/(0.32*N_data_full),2)+pow(scale_factor_1*N_sig_more50*err_scale_factor_2/(0.32*N_data_full),2)+pow(scale_factor_1*scale_factor_2*err_sig_more50/(0.32*N_data_full),2));


  std::cout << "rate_PU= " << rate_PU <<"+-" << err_rate_PU << '\n';

  const char *path1 = "/home/valerian/programs/files/PU_data.root";
  const char *path2 = "/home/valerian/programs/files/PU_sigMC.root";

  TFile *file_1 = new TFile(path1, "READ");
  TFile *file_2 = new TFile(path2, "READ");

  TH1D *hist_data_full=(file_1->Get<TH1D>("hist_data_full"));
  TH1D *hist_sig_full=(file_2->Get<TH1D>("hist_sig_full"));


  TCanvas *c1=new TCanvas();
  c1->SetLogy(1);
  // gStyle->SetErrorX(0);
  hist_data_full->SetMarkerStyle(8);
  hist_data_full->SetMarkerSize(2);
  hist_data_full->Draw("HISTsame");
  hist_sig_full->SetLineStyle(1);
  hist_sig_full->SetLineColor(kViolet+8);
  hist_sig_full->SetLineWidth(1);
  hist_sig_full->Draw("HISTsame");

  TLine *l_1 = new TLine(-50,0,-50,2100);
  l_1->SetY1(0);
  l_1->SetLineColor(kRed-9);
  l_1->SetLineWidth(1);
  l_1->SetLineStyle(9);
  l_1->Draw();

  TLine *l_2 = new TLine(50,0,50,2100);
  l_2->SetY1(0);
  l_2->SetLineColor(kRed-9);
  l_2->SetLineWidth(1);
  l_2->SetLineStyle(9);
  l_2->Draw("SAME");

  // TLegend *leg1 = new TLegend();
  // leg1->SetBorderSize(0);
  // leg1->AddEntry(hist_data_full,"Data");
  // // leg1->AddEntry(hist_sig_full, "Z(#nu#bar{#nu})#gamma", "f");
  // leg1->Draw();

  TLatex* latex=new TLatex();
  latex->DrawLatex(1.2,1.2,"#bf{#it{ATLAS}} Internal");
  latex->DrawLatex(1.2,1.2,"#sqrt{s}=13 TeV, 140 fb^{-1}");
  latex->DrawLatex(1.2,1.2,"SR");
}
