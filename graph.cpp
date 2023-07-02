#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.C"

void graph() {

  SetAtlasStyle();

  Double_t N_SR_jg_1, N_SR_jg_2, N_SR_jg_3, N_SR_jg_4;
  TCanvas *c1=new TCanvas("", "");

  float x1[5]={0.065, 0.080, 0.095, 0.115, 0.140};
  float ex[5]={0,0,0,0,0};

  float y1[5]={1520, 1313, 1130, 1087, 729};
  float ey1[5]={82, 82, 76, 83, 46};
  TF1 *leaner_fit_1 = new TF1("", "pol1", 0, 0.2);
  leaner_fit_1->SetLineColor(4);
  TGraphErrors *graph1=new TGraphErrors(5, x1, y1, ex, ey1);
  graph1->SetTitle(";E_{T}^{cone20}/p_{T};Estimate");
  graph1->GetXaxis()->SetLimits(0,0.145);
  graph1->GetYaxis()->SetRangeUser(600,2500);
  graph1->SetMarkerStyle(21);
  graph1->SetMarkerColor(4);
  graph1->Fit(leaner_fit_1);
  graph1->Draw("AP");

  N_SR_jg_1=leaner_fit_1->Eval(0.014);
  Double_t er_1=0.010*(leaner_fit_1->GetParameter(1));
  std::cout << "N_SR_ETmiss=" << N_SR_jg_1 << "+-" << er_1 << '\n';
  TLegend *leg = new TLegend(0.6, 0.8, 0.89, 0.89);
  leg->SetBorderSize(0);
  leg->AddEntry(graph1, "Fit to E_{T}^{miss}");
  leg->Draw();

  float y2[5]={1533, 1275, 1080, 1027, 624};
  float ey2[5]={82, 80, 73, 78, 40};
  TF1 *leaner_fit_2 = new TF1("", "pol1", 0, 0.2);
  leaner_fit_2->SetLineColor(3);
  TGraphErrors *graph2=new TGraphErrors(5, x1, y2, ex, ey2);
  graph2->GetXaxis()->SetLimits(0,0.145);
  graph2->GetYaxis()->SetRangeUser(600,2500);
  graph2->SetMarkerStyle(23);
  graph2->SetMarkerColor(3);
  graph2->Fit(leaner_fit_2);
  graph2->Draw("P");

  N_SR_jg_2=leaner_fit_2->Eval(0.014);
  Double_t er_2=0.010*(leaner_fit_2->GetParameter(1));
  std::cout << "N_SR_dphi_jet=" << N_SR_jg_2 << "+-" << er_2 << '\n';
  leg->AddEntry(graph2, "Fit to |#Delta#phi(#vecp_{T}^{miss},j_{1})|");
  leg->Draw();

  float y3[5]={1480, 1217, 1024, 951, 548};
  float ey3[5]={78, 75, 69, 72, 36};
  TF1 *leaner_fit_3 = new TF1("", "pol1", 0, 0.2);
  leaner_fit_3->SetLineColor(6);
  TGraphErrors *graph3=new TGraphErrors(5, x1, y3, ex, ey3);
  graph3->SetMarkerStyle(20);
  graph3->SetMarkerColor(6);
  graph3->GetXaxis()->SetLimits(0,0.145);
  graph3->GetYaxis()->SetRangeUser(600,2500);
  graph3->Fit(leaner_fit_3);
  graph3->Draw("P");
  N_SR_jg_3=leaner_fit_3->Eval(0.014);
  Double_t er_3=0.010*(leaner_fit_3->GetParameter(1));
  std::cout << "N_SR_dphi_gamma=" << N_SR_jg_3 << "+-" << er_3 << '\n';
  leg->AddEntry(graph3, "Fit to |#Delta#phi(#vecp_{T}^{miss},#gamma)|");
  leg->Draw();

  float y4[5]={1516, 1268, 1069, 1031, 649};
  float ey4[5]={90, 86, 79, 84, 46};
  TF1 *leaner_fit_4 = new TF1("", "pol1", 0, 0.2);
  leaner_fit_4->SetLineColor(1);
  TGraphErrors *graph4=new TGraphErrors(5, x1, y4, ex, ey4);
  graph4->SetMinimum(0);
  graph4->SetMarkerStyle(33);
  graph4->SetMarkerColor(1);
  graph4->GetXaxis()->SetLimits(0,0.145);
  graph4->GetYaxis()->SetRangeUser(600,2500);
  graph4->Fit(leaner_fit_4);
  graph4->Draw("P");
  N_SR_jg_4=leaner_fit_4->Eval(0.014);
  Double_t er_4=0.010*(leaner_fit_4->GetParameter(1));
  std::cout << "N_SR_ETmiss_sign=" << N_SR_jg_4 << "+-" << er_4 << '\n';
  leg->AddEntry(graph4, "Fit to E_{T}^{miss} significance");
  leg->Draw();

  TLine *l = new TLine(0.014,0,0.014,2500);
  l->SetY1(600);
  l->SetLineColor(6);
  l->SetLineWidth(3);
  l->SetLineStyle(9);
  l->Draw("SAME");

  // float x5[5]={0.014, 0.014};
  // float y5[2]={0, 2000};
  //
  //
  // TGraph *graph5=new TGraph(2, x5, y5);
  // graph5->SetMinimum(0);
  // graph5->SetMarkerStyle(36);
  // graph5->SetMarkerColor(26);
  // graph5->Fit(leaner_fit_5);
  // graph5->Draw();

  Double_t sigma[4]={100, 110, 120, 110};
  Double_t x[4]={2000, 2020, 2030, 2070};
  Double_t sum_sigma_x=0, sum_sigma=0;
  Double_t N_in_x, er_in_x;

  for (int i=0; i<=3; i++){
    sum_sigma+=1/pow(sigma[i],2);
    sum_sigma_x+=(1/pow(sigma[i],2))*x[i];
   }

   N_in_x=sum_sigma_x/sum_sigma;
   er_in_x=sqrt(1/(sum_sigma));
   std::cout << "N_in_x=" << N_in_x << "+-" << er_in_x <<'\n';


  // TH1D *hist_SR_jg_MC = new TH1D ("", "", 30, 0, 0.065);
  // hist_SR_jg_MC->GetXaxis()->SetRangeUser(0,0.145);
  // hist_SR_jg_MC->Draw("SAME");

}
