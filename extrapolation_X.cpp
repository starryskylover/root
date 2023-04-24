#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.C"

void extrapolation_X(){

  SetAtlasStyle();

  Int_t mc_ph_type;
  UInt_t n_ph, n_jet, n_e_looseBL, n_mu, ph_isem;
  Double_t weight, ph_pt, ph_phi, ph_eta, ph_iso_et20, ph_iso_pt, ph_z_point;
  Double_t jet_lead_phi,jet_lead_pt, jet_lead_eta, metTST_pt, metTST_phi, metTSTsignif, koef;
  Double_t error_SR_jg_MC, N_SR_jg_MC;
  Double_t L_a = 36214.96, L_d = 44307.4, L_e = 58450.1, L_j;
  Int_t nbins=30;

    TH1D *hist_SR_jg_MC = new TH1D ("SR", "jet->gamma_MC", nbins, -0.02, 0.065);

    const char *path = "/home/valerian/programs/R_factor_MC/private/Znunu_";
    const char *nabor[] = {"364222","364223","366011","366012","366013","366014","366015","366016","366017",
    "366020","366021","366022","366023","366024","366025","366026","366029","366030","366031","366032","366033",
    "366034","366035","Wtaunu_700347","Wtaunu_700348","Wtaunu_700349"};

    for (int l = 0; l <= 25; l++) {
    char *Nabor = new char[strlen(path) + strlen(nabor[l]) + 1];
    strcpy(Nabor, path);
    strcat(Nabor, nabor[l]);
    const char *year[] = {"/user.akurova.a.MxAOD.root","/user.akurova.d.MxAOD.root","/user.akurova.e.MxAOD.root"};


     for (int j = 0; j <= 2; j++) {
     char *znunu_MC= new char[strlen(Nabor) + strlen(year[j]) + 1];
     strcpy(znunu_MC,Nabor);
     strcat(znunu_MC,year[j]);

     TFile *znunu = new TFile(znunu_MC, "READ");
     TTree *tree = (TTree*)znunu->Get("output_tree");
     TTree *tree_koef= (TTree*)znunu->Get("norm_tree");
     TTree *tree_sum_w = (TTree*)znunu->Get("output_tree_sw");

     Double_t sumw = 0;
     Double_t sum_of_weights_bk_xAOD;

     tree_sum_w->SetBranchAddress("sum_of_weights_bk_xAOD",&sum_of_weights_bk_xAOD);

     int entry = (int)tree_sum_w->GetEntries();
     for (int k=0; k<entry; k++)
     {
       tree_sum_w->GetEntry(k);
       sumw += sum_of_weights_bk_xAOD;
     }

     tree->SetBranchAddress("n_ph", &n_ph);
     tree->SetBranchAddress("n_jet", &n_jet);
     tree->SetBranchAddress("n_e_looseBL", &n_e_looseBL);
     tree->SetBranchAddress("n_mu", &n_mu);
     tree->SetBranchAddress("weight", &weight);
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
     tree->SetBranchAddress("mc_ph_type", &mc_ph_type);

     tree_koef->SetBranchAddress("koef", &koef);

     int Num_koef = (int)tree_koef->GetEntries();

     for (int g=0; g<Num_koef; g++){
       tree_koef->GetEntry(g);
   }
   //  std::cout << "koef=" << koef << '\n';

   int Num_tree = (int)tree->GetEntries();

   for (int i=0; i<Num_tree; i++){
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
     if (fabs(ph_z_point) >= 250) continue;
     if (l<23 && fabs(weight) >= 100) continue;
     if (metTST_pt <=130) continue;
     if (mc_ph_type >= 13 && mc_ph_type <= 15) continue;
     if (metTSTsignif <= 11) continue;
     if (dphi_1 <= 0.7) continue;
     if (n_jet >= 1 && dphi_2 <= 0.4) continue;
     if (ph_isem !=0) continue;

     Double_t Iso_cal = ph_iso_et20/ph_pt;
     Double_t Iso_track = ph_iso_pt/ph_pt;

     (j == 0) ? L_j=L_a : (j == 1) ? L_j=L_d : L_j=L_e;
     Double_t norm_koef=koef*L_j/sumw;

     if (Iso_cal < 0.065 && Iso_track < 0.05) hist_SR_jg_MC->Fill(ph_iso_et20/ph_pt, weight*norm_koef);
     // if (Iso_cal > 0.065 && Iso_track > 0.05) hist_SR_jg_MC->Fill(ph_iso_et20/ph_pt, weight*norm_koef);
     }
   }
  }

  TFile *file_CR2 = new TFile ("hist","RECREATE");
  TCanvas *c1=new TCanvas("","");
  c1->cd();
  hist_SR_jg_MC->GetXaxis()->SetTitle("E_{T}^{cone20}/p_{T}");
  hist_SR_jg_MC->GetYaxis()->SetTitle("Events");
  hist_SR_jg_MC->SetMarkerStyle(kFullCircle);
  hist_SR_jg_MC->Draw("PLC PMC");

  N_SR_jg_MC=hist_SR_jg_MC->IntegralAndError(1, nbins, error_SR_jg_MC, "");
  std::cout << "N_SR_jg_MC=" << N_SR_jg_MC << "+-" << error_SR_jg_MC <<'\n';
  TF1 *fit = new TF1("fit","landau" ,-0.02, 0.065);
  fit->SetLineColor(kMagenta);
  hist_SR_jg_MC->Fit("fit");
  N_SR_jg_MC=fit->Eval(0.0136);
  std::cout << "N_SR_jg_MC=" << N_SR_jg_MC << '\n';
  std::cout << "Mode= " << fit->GetMaximumX() << '\n';
  std::cout << "N_mode= " << fit->GetMaximum() << '\n';
  hist_SR_jg_MC->Write();
  // Double_t mean=fit->GetParameter(1);
  // std::cout << "mean=" << mean << '\n';
  // Double_t x=hist_SR_jg_MC->GetBinCenter(hist_SR_jg_MC->GetMaximumBin());
  // std::cout << "X=" << x << '\n';

  Double_t chi2=fit->GetChisquare();
  std::cout << "chi2=" << chi2 << '\n';
  Double_t ndof=fit->GetNDF();
  std::cout << "ndof=" << ndof << '\n';

  TLegend *legend=new TLegend(0.6,0.65,0.88,0.85);
  legend->SetTextFont(72);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  // legend->AddEntry(fit,"Landau Fit","l");
  legend->AddEntry(hist_SR_jg_MC,"MC Zj, W(#tau#nu) h.c.");
  legend->AddEntry(fit,"Landau fit", "l");
  legend->AddEntry((TObject*)0, "#chi^{2}/N_{d.o.f.}=27.03/26", "");
  legend->Draw();

  TLatex* latex=new TLatex();
  latex->DrawLatex(1.2,1.2,"#bf{#it{ATLAS}} Internal");
  latex->DrawLatex(1.2,1.2,"#sqrt{s}=13 TeV, 140 fb^{-1}");

}
