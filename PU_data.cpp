// #include "AtlasStyle.C"
// #include "AtlasLabels.C"
// #include "AtlasUtils.C"

void PU_data(){

// SetAtlasStyle();

  Int_t ph_convFlag;
  UInt_t n_ph, n_jet, n_e_looseBL, n_mu, ph_isem;
  Double_t ph_pt, ph_phi, ph_eta, ph_iso_et40, ph_iso_et20, ph_iso_pt, ph_z_point;
  Double_t jet_lead_phi,jet_lead_pt, jet_lead_eta, jet_sublead_phi, metTST_pt, metTST_phi, metTSTsignif;
  Double_t error_data_1, error_data_2, error_data_3;
  Double_t N_data_1, N_data_2, N_data_3;
  Int_t nbins=100;

  TH1D *hist_data_full = new TH1D ("hist_data_full", "hist_data_full", nbins, -250, 250);
  TH1D *hist_data_less10 = new TH1D ("hist_data_less10", "hist_data_less10", nbins, -250, 250);
  TH1D *hist_data_more50 = new TH1D ("hist_data_more50", "hist_data_more50", nbins, -250, 250);



  const char *path = "/home/valerian/programs/R_factor_MC/private/data_PU/data-15-18-reproc-21-02-23-checked_met120.root";

    TFile *data = new TFile(path, "READ");
    TTree *tree = (TTree*)data->Get("output_tree");

    tree->SetBranchAddress("n_ph", &n_ph);
    tree->SetBranchAddress("n_jet", &n_jet);
    tree->SetBranchAddress("n_e_looseBL", &n_e_looseBL);
    tree->SetBranchAddress("n_mu", &n_mu);
    tree->SetBranchAddress("ph_pt",&ph_pt);
    tree->SetBranchAddress("ph_phi",&ph_phi);
    tree->SetBranchAddress("ph_eta",&ph_eta);
    tree->SetBranchAddress("ph_iso_et20", &ph_iso_et20);
    tree->SetBranchAddress("ph_iso_pt", &ph_iso_pt);
    tree->SetBranchAddress("ph_isem", &ph_isem);
    tree->SetBranchAddress("ph_z_point", &ph_z_point);
    tree->SetBranchAddress("jet_lead_phi",&jet_lead_phi);
    tree->SetBranchAddress("jet_lead_pt",&jet_lead_pt);
    tree->SetBranchAddress("jet_lead_eta",&jet_lead_eta);
    tree->SetBranchAddress("metTST_pt", &metTST_pt);
    tree->SetBranchAddress("metTST_phi",&metTST_phi);
    tree->SetBranchAddress("metTSTsignif", &metTSTsignif);
    tree->SetBranchAddress("ph_convFlag", &ph_convFlag);

    int entry = (int)tree->GetEntries();

    for (int i=0; i<entry; i++){
    tree->GetEntry(i);

    TLorentzVector *v1 = new TLorentzVector();
    TLorentzVector *v2 = new TLorentzVector();
    TLorentzVector *v3 = new TLorentzVector();
    v1->SetPtEtaPhiM(metTST_pt, 0, metTST_phi, 0);
    v2->SetPtEtaPhiM(jet_lead_pt, jet_lead_eta, jet_lead_phi, 0);
    v3->SetPtEtaPhiM(ph_pt, ph_eta, ph_phi, 0);
    Double_t dphi_1=abs((*v1).DeltaPhi(*v3));
    Double_t dphi_2=abs((*v1).DeltaPhi(*v2));

    if (ph_pt <= 150) continue;
    if (n_ph !=1 || n_e_looseBL !=0 || n_mu!=0) continue;
    if (fabs(ph_z_point) > 250) continue;
    if (metTST_pt <=130) continue;
    if (metTSTsignif <= 11) continue;
    if (dphi_1 <= 0.7) continue;
    if (n_jet >= 1 && dphi_2 <= 0.4) continue;
    if (ph_iso_et20/ph_pt >= 0.065) continue;
    if (ph_iso_pt/ph_pt >= 0.05) continue;
    if (ph_convFlag==0 || ph_convFlag==2 || ph_convFlag==4) continue;
    if (ph_isem != 0) continue;

    if (fabs(ph_z_point) < 10) hist_data_less10->Fill(ph_z_point, 1.0);
    // if (fabs(ph_z_point) > 15) hist_data_more50->Fill(ph_z_point, 1.0);
    if (fabs(ph_z_point) > 50) hist_data_more50->Fill(ph_z_point, 1.0);
    hist_data_full->Fill(ph_z_point, 1.0);

  }
  TFile *file = new TFile ("PU_data.root","RECREATE");
  hist_data_full->Write();
  file->Close();
  TCanvas *c1=new TCanvas("", "");
  c1->SetLogy(1);
  c1->cd();
  hist_data_full->SetMinimum(1.e-1);
  hist_data_full->SetMarkerStyle(8);
  hist_data_full->SetMarkerSize(2);
  hist_data_full->SetMarkerColor(kBlack);
  hist_data_full->Draw();
  
  // TFile *file = new TFile ("PU_data.root","RECREATE");
  // hist_data_full->Write();
  // file->Close();
  // TCanvas *c1=new TCanvas("", "");
  // c1->SetLogy(1);
  // hist_data_full->SetMinimum(1.e-1);
  // hist_data_full->SetLineColor(kViolet+8);
  // hist_data_full->Draw();

  // TCanvas *c1=new TCanvas("", "");
  // hist_data_full->Draw();

  N_data_1=hist_data_less10->IntegralAndError(1, nbins, error_data_1, "");

  N_data_2=hist_data_more50->IntegralAndError(1, nbins, error_data_2, "");

  N_data_3=hist_data_full->IntegralAndError(1, nbins, error_data_3, "");

  std::cout << "N_data_less10= "  << N_data_1 << " +- " << error_data_1 << '\n';

  Double_t N_sig_less10=1058.66, err_sig_less10=5.74346, N_data_less10=4547, err_data_less10=67.4314;

  Double_t scale_factor_1=N_data_less10/N_sig_less10;
  Double_t err_scale_factor_1=(N_data_less10/N_sig_less10)*sqrt(pow(err_data_less10/N_data_less10,2)+pow(err_sig_less10/N_sig_less10,2));

  std::cout << "N_sigMC_less10= 1058.66 +- 5.74346" << '\n';
  std::cout << "SF1= "  << scale_factor_1 << " +- " << err_scale_factor_1 << '\n';
  std::cout << '\n';

  std::cout << "N_data_more50= "  << N_data_2 << " +- " << error_data_2 << '\n';
  // std::cout << "N_data_more15= "  << N_data_2 << " +- " << error_data_2 << '\n';
  std::cout << "N_data_full= "  << N_data_3 << " +- " << error_data_3 << '\n';

}
