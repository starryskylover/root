#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.C"

void matrix_fit() {

  SetAtlasStyle();

  Double_t N_SR_jg, N_SR_jg_2, N_SR_jg_3, N_SR_jg_4;
  TCanvas *c1=new TCanvas("", "");

  float x1[8]={0.065, 0.085, 0.105, 0.125, 0.145, 0.165, 0.185, 0.205}; //координаты слайсов
  float ex[8]={0,0,0,0,0,0,0,0};

  float y1[8]={660, 406, 253, 135, 108, 62, 42, 44};         //число фоновых jet->gamma событий для каждого слайса
  float ey1[8]={20, 17, 14, 11, 11, 8, 7, 6};                //стат погрешность
   TF1 *fit = new TF1("", "gaus", 0, 0.200);        //фит
  // TF1 *fit = new TF1("", "expo", 0, 0.200);
  // TF1 *fit = new TF1("", "pol3", -0.05, 0.200);
  // TF1 *fit = new TF1("", "landau", 0, 0.200);
  // TF1 *fit = new TF1("", "gausn", 0, 0.200);

  fit->SetLineColor(9);
  TGraphErrors *graph1=new TGraphErrors(8, x1, y1, ex, ey1);
  graph1->SetTitle(";E_{T}^{cone20}/p_{T};Estimate");
  graph1->GetXaxis()->SetLimits(0,0.2);
  graph1->GetYaxis()->SetRangeUser(10,3000);
  graph1->SetMarkerStyle(20);
  graph1->SetMarkerColor(1);
  graph1->Fit(fit);
  graph1->Draw("AP");

  Double_t chi2=fit->GetChisquare();
  std::cout << "chi2=" << chi2 << '\n';
  Double_t ndof=fit->GetNDF();
  std::cout << "ndof=" << ndof << '\n';

  N_SR_jg=fit->Eval(0.014);

   Double_t er_1=N_SR_jg*sqrt(pow(fit->GetParError(0)/fit->GetParameter(0),2)+pow((0.014-fit->GetParameter(1))*(fit->GetParError(1))/pow(fit->GetParameter(2),2),2)+pow(pow(0.014-(fit->GetParameter(1)),2)*(fit->GetParError(2))/pow(fit->GetParameter(2),3),2));
  // Double_t er_1=N_SR_jg*sqrt(pow(fit->GetParError(0),2)+pow(0.014*(fit->GetParError(1)),2));

  std::cout << "N_SR_jet_gamma=" << N_SR_jg << "+-" << er_1 << '\n';
  TLegend *leg = new TLegend(0.6, 0.8, 0.89, 0.89);
  leg->SetBorderSize(0);
  leg->AddEntry(graph1, "jet->gamma in i slice");

  leg->AddEntry(fit,"Gaus fit", "l");
//  leg->AddEntry(fit,"Expo fit", "l");
//  leg->AddEntry(fit,"Pol3 fit", "l");
  leg->AddEntry((TObject*)0, "#chi^{2}/N_{d.o.f.}=21.21/5", ""); //gaus
//  leg->AddEntry((TObject*)0, "#chi^{2}/N_{d.o.f.}=16.37/6", ""); //expo
//  leg->AddEntry((TObject*)0, "#chi^{2}/N_{d.o.f.}=6.27/4", ""); //pol3
  leg->Draw();

  TLine *l = new TLine(0.014,0,0.014,3000);
  l->SetY1(0);
  l->SetLineColor(6);
  l->SetLineWidth(3);
  l->SetLineStyle(9);
  l->Draw("SAME");
}
