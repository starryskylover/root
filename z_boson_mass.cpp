#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TBranch.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TBrowser.h>
#include <TObject.h>
#include <TClass.h>
#include <Rtypes.h>

  void z_boson_mass(){

    const char *ftask = "/home/valerian/programs/data/task.root";

    TFile *task_data = new TFile(ftask, "READ");
    cout << ftask << endl;
    TTree *tree = (TTree*)task_data->Get("output");
    float_t ph_E, ph_pt, ph_phi, ph_eta;
    float_t l1_E, l1_pt, l1_phi, l1_eta;
    float_t l2_E, l2_pt, l2_phi, l2_eta;
    float_t ll_m, llg_m;
    float_t inv_z_massll, inv_mass_ll_TLV, inv_mass_llg_TLV;

    tree->SetBranchAddress("ph.E",&ph_E);
    tree->SetBranchAddress("ph.pt",&ph_pt);
    tree->SetBranchAddress("ph.phi",&ph_phi);
    tree->SetBranchAddress("ph.eta",&ph_eta);
    tree->SetBranchAddress("l1.E",&l1_E);
    tree->SetBranchAddress("l1.pt",&l1_pt);
    tree->SetBranchAddress("l1.phi",&l1_phi);
    tree->SetBranchAddress("l1.eta",&l1_eta);
    tree->SetBranchAddress("l2.E",&l2_E);
    tree->SetBranchAddress("l2.pt",&l2_pt);
    tree->SetBranchAddress("l2.phi",&l2_phi);
    tree->SetBranchAddress("l2.eta",&l2_eta);
    tree->SetBranchAddress("ll.m",&ll_m);
    tree->SetBranchAddress("llg.m",&llg_m);


    TLorentzVector *lept1 = new TLorentzVector();
    TLorentzVector *lept2 = new TLorentzVector();
    TLorentzVector *photon= new TLorentzVector();


    TH1F *hist1 = new TH1F("h_ll_m", "inv_mass_z_boson_ll", 100, 35, 110);
    TH1F *hist2 = new TH1F("h_ll_m_TLV", "inv_mass__z_boson_ll_TLV", 100, 35, 110);
    TH1F *hist3 = new TH1F("h_llg_m", "inv_mass_llg", 200, 45, 130);
    TH1F *hist4 = new TH1F("h_llg_m", "inv_mass_llg_TLV", 200, 45, 130);

    TFile *file = new TFile ("z_boson.root","RECREATE");
    file->mkdir("tree");
    file->cd("tree");
    TTree *m_tree = new TTree ("m_tree","variables");

    m_tree->Branch("ph_E",&ph_E,"ph_E/F");
    m_tree->Branch("ph_pt",&ph_pt,"ph_pt/F");
    m_tree->Branch("ph_eta",&ph_eta,"ph_eta/F");
    m_tree->Branch("ph_phi",&ph_phi,"ph_phi/F");
    m_tree->Branch("l1_E",&l1_E,"l1_E/F");
    m_tree->Branch("l1_pt",&l1_pt,"l1_pt/F");
    m_tree->Branch("l1_eta",&l1_eta,"l1_eta/F");
    m_tree->Branch("l1_phi",&l1_phi,"l1_phi/F");
    m_tree->Branch("l2_E",&l2_E,"l2_E/F");
    m_tree->Branch("l2_pt",&l2_pt,"l2_pt/F");
    m_tree->Branch("l2_eta",&l2_eta,"l2_eta/F");
    m_tree->Branch("l2_phi",&l2_phi,"l2_phi/F");
    m_tree->Branch("ll_m",&ll_m,"ll_m/F");
    m_tree->Branch("llg_m",&llg_m,"llg_m/F");
    m_tree->Branch("inv_z_massll",&inv_z_massll,"inv_z_massll/F");
    m_tree->Branch("inv_mass_ll_TLV",&inv_mass_ll_TLV,"inv_mass_ll_TLV/F");
    m_tree->Branch("inv_mass_llg_TLV",&inv_mass_llg_TLV,"inv_mass_llg_TLV/F");

    int Num = (int)tree->GetEntries();
    double_t l1_M=0,l2_M=0,ph_M=0;
    for (int i = 0; i < Num; i++){
      tree->GetEntry(i);
      inv_z_massll=sqrt(2*l1_pt*l2_pt*(cosh(l1_eta-l2_eta)-cos(l1_phi-l2_phi)));
      //  cout << inv_z_massll << " " << endl;
      //  cout << abs(inv_z_massll - ll_m)/ll_m << endl;
      //  cout << ll_m << endl;
      lept1->SetPtEtaPhiM(l1_pt, l1_eta, l1_phi, l1_M);
      lept2->SetPtEtaPhiM(l2_pt, l2_eta, l2_phi, l2_M);
      photon->SetPtEtaPhiM(ph_pt, ph_eta, ph_phi, ph_M);
      inv_mass_ll_TLV=(*lept1+*lept2).M();
      inv_mass_llg_TLV=(*lept1+*lept2+*photon).M();
      ll_m=ll_m/1000;
      llg_m=llg_m/1000;
      inv_mass_ll_TLV=inv_mass_ll_TLV/1000;
      inv_mass_llg_TLV=inv_mass_llg_TLV/1000;
      //  cout << inv_mass_ll_TLV << endl;
      //  cout << inv_mass_llg_TVL << endl;
      //  cout << abs(inv_mass_tlv-ll_m)/ll_m << endl;
      //  cout << abs(inv_mass_llg_TLV-llg_m)/llg_m << endl;
      hist1->Fill(ll_m);
      hist2->Fill(inv_mass_ll_TLV);
      hist3->Fill(llg_m);
      hist4->Fill(inv_mass_llg_TLV);
      m_tree->Fill();
  //  m_tree->Show(i);
    }
   file->Write();
   file->cd();
   file->mkdir("histograms");
   file->cd("histograms");

      TCanvas *c1 = new TCanvas("decay_ll", "decay_ll");
      hist1->SetStats(0);
      hist1->SetFillColor(41);
      hist1->GetXaxis()->SetTitle("inv mass, GeV");
      hist1->GetYaxis()->SetTitle("Events");
      hist1->Draw();
      hist2->SetLineColor(4);
      hist2->SetLineWidth(3);
      hist2->Draw("same");
      c1->Write();
      c1->Print("z_boson");


      TLegend *leg1 = new TLegend(0.6, 0.7, 0.9, 0.9);
      leg1->AddEntry(hist1, "ll_m branch data", "f");
      leg1->AddEntry(hist2, "TLV data", "l");
      leg1->Draw();


      TCanvas *c2 = new TCanvas("decay_llg", "decay_llg");
      hist3->SetStats(0);
      hist3->SetFillColor(20);
      hist3->GetXaxis()->SetTitle("inv mass, GeV");
      hist3->GetYaxis()->SetTitle("Events");
      hist3->Draw();
      hist4->SetLineColor(4);
      hist4->SetLineWidth(3);
      hist4->Draw("same");
      c2->Write();
      c2->Print("z_boson");


      TLegend *leg2 = new TLegend(0.6, 0.7, 0.9, 0.9);
      leg2->AddEntry(hist3, "llg_m branch data", "f");
      leg2->AddEntry(hist4, "TLV data", "l");
      leg2->Draw();
      file->Close();
  }
