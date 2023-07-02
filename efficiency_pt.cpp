#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.C"
void efficiency_pt(){

    SetAtlasStyle();

  Int_t nbins=100;
  UInt_t n_e_looseBL, n_mu, n_ph,tr_ph_n, tr_mu_n, tr_el_n;
  Double_t ph_pt, tr_ph_pt, tr_Z_pt;
  Double_t metTST_pt;

  TH1D *hist_1 = new TH1D ("hist_1", "", nbins, 135, 600);
  TH1D *hist_2 = new TH1D ("hist_2", "hist_2", nbins, 135, 600);

  const char *path = "/home/valerian/programs/MCData16a_345784_aMcAtNloPythia8_NNPDF30NLO_FxFx_nunugamma_pty_140_v5.root";
  TFile *file = new TFile(path, "READ");
  TTree *tree1 = (TTree*)file->Get("output_tree");
  TTree *tree2= (TTree*)file->Get("output_tr_tree");

  int entry1 = (int)tree1->GetEntries();
  std::cout << "entry1= " << entry1<< '\n';
  int entry2 = (int)tree2->GetEntries();
  std::cout << "entry2= " << entry2<< '\n';


  tree1->SetBranchAddress("n_e_looseBL", &n_e_looseBL);
  tree1->SetBranchAddress("n_mu", &n_mu);
  tree1->SetBranchAddress("ph_pt",&ph_pt);
  tree1->SetBranchAddress("metTST_pt", &metTST_pt);
  tree1->SetBranchAddress("n_ph", &n_ph);

  tree2->SetBranchAddress("tr_Z_pt", &tr_Z_pt);
  tree2->SetBranchAddress("tr_ph_pt", &tr_ph_pt);
  tree2->SetBranchAddress("tr_ph_n", &tr_ph_n);
  tree2->SetBranchAddress("tr_mu_n", &tr_mu_n);
  tree2->SetBranchAddress("tr_el_n", &tr_el_n);

  for (int i=0; i<entry1; i++){
    tree1->GetEntry(i);

    if (metTST_pt <=150) continue;
    if (n_ph!=1 || n_e_looseBL !=0 || n_mu!=0) continue;

    hist_1->Fill(ph_pt, 1);
  }

  for (int i=0; i<entry2; i++){
    tree2->GetEntry(i);

    if (tr_Z_pt <=150) continue;
    if (tr_ph_n!=1 || tr_el_n!=0 || tr_mu_n!=0) continue;

    hist_2->Fill(tr_ph_pt, 1);
  }

  Double_t overflow_1 = hist_1->GetBinContent(nbins)+hist_1->GetBinContent(nbins+1);
  Double_t overflow_2 = hist_2->GetBinContent(nbins)+hist_2->GetBinContent(nbins+1);

  hist_1->SetBinContent(nbins, overflow_1);
  hist_2->SetBinContent(nbins, overflow_2);

  Double_t overflow_err_1 = sqrt(pow(hist_1->GetBinError(nbins), 2) + pow(hist_1->GetBinError(nbins+1), 2));
  Double_t overflow_err_2 = sqrt(pow(hist_2->GetBinError(nbins), 2) + pow(hist_2->GetBinError(nbins+1), 2));

  hist_1->SetBinError(nbins, overflow_err_1);
  hist_2->SetBinError(nbins, overflow_err_2);
  // std::cout << "hist1 entry=" << hist_1->GetEntries() << '\n';
  // std::cout << "hist2 entry=" << hist_2->GetEntries() << '\n';

  std::cout << "ph_pt integral=" << hist_1->Integral() << '\n';
  std::cout << "tr_ph_pt integral=" << hist_2->Integral() << '\n';

  hist_1->Divide(hist_2);
  TCanvas *c1=new TCanvas("", "");
  hist_1->GetXaxis()->SetTitle("p^{#gamma}_{T}");
  hist_1->GetYaxis()->SetTitle("Efficiency ph_pt");
  hist_1->SetMarkerStyle(kFullCircle);
  hist_1->Draw("PLC PMC");
  TLine *l = new TLine(135,1,600,1);
  l->SetY1(1);
  l->SetLineColor(6);
  l->SetLineWidth(3);
  l->SetLineStyle(9);
  l->Draw("SAME");
  // TLegend *legend=new TLegend(0.6,0.65,0.88,0.85);
  // legend->SetTextFont(72);
  // legend->SetTextSize(0.04);
  // legend->SetBorderSize(0);
  // legend->AddEntry(hist_1,"Efficiency ph_pt");
  // legend->Draw();
}
