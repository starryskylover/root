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

void chektree(){

  const char *ftask1 = "/home/valerian/z_boson.root";

  TFile *file = new TFile(ftask1, "READ");
  cout << ftask1 << endl;
  TTree *tree = (TTree*)file->Get("ll_m");
  float_t ll_m;
  TH1F *hist = new TH1F("hist", "Histogram", 100, 35000, 110000);

  tree->SetBranchAddress("ll_m",&ll_m);

  int Num = (int)tree->GetEntries();
  for (int i = 0; i < Num; i++){
    tree->GetEntry(i);
    cout << ll_m << endl;
    hist->Fill(ll_m);
  }
  hist->Draw();
  file->Close();
}
