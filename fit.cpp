#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include <TFile.h>
#include <TString.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TBrowser.h>
#include <TObject.h>
#include <TClass.h>

  void fit(){
    gStyle->SetOptFit(kTRUE);
    TH1F *hist = new TH1F("hist","Random Gaussian",50, 15,45);
    double_t par0=47, par1=30, par2=5;
    TF1 * fgaus = new TF1("fgaus","gaus",15,45);
    fgaus->SetParameters(par0,par1,par2);
    hist->FillRandom("fgaus",1000);
    hist->Draw("E");
    hist->Fit("gaus");


    TF1 *gausfit = (TF1*)hist->GetFunction("gaus");
    double_t p0=gausfit->GetParameter(0);
    double_t p1=gausfit->GetParameter(1);
    double_t p2=gausfit->GetParameter(2);
    cout << "difference_p0 = " << abs(p0-47) << endl;
    cout << "difference_p1 = " << abs(p1-30) << endl;
    cout << "difference_p2 = " << abs(p2-5) << endl;
    double_t chi2=gausfit->GetChisquare();
    cout << "rootChi2=" << chi2 << endl;

    int i, nbins=50;
    double_t xi, fi, gi, delta;
    double_t chisquare=0;

    for (i=1; i<nbins; i++){
      xi=hist->GetXaxis()->GetBinCenter(i);
      fi=par0*exp(-0.5*(pow((xi-par1)/par2,2)));
      gi=p0*exp(-0.5*(pow((xi-p1)/p2,2)));
      delta=pow((fi-gi),2)/gi;
      chisquare+=delta;
  }
  cout << "myChi2=" << chisquare << endl;
}
