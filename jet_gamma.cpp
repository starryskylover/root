void jet_gamma(){
  Double_t error_CR1_bac_1, error_CR1_bac_2, error_CR1_bac_3, error_CR1_bac_4, error_CR1_bac_5;
  Double_t N_FR_bac_1, N_CR1_bac_1, N_CR1_bac_2, N_CR1_bac_3, N_CR1_bac_4, N_CR1_bac_5;
  Double_t error_CR1_data_1, error_CR1_data_2, error_CR1_data_3, error_CR1_data_4, error_CR1_data_5;
  Double_t N_CR1_data_1, N_CR1_data_2, N_CR1_data_3, N_CR1_data_4, N_CR1_data_5;
  Double_t error_CR1_sig_1, error_CR1_sig_2, error_CR1_sig_3, error_CR1_sig_4, error_CR1_sig_5;
  Double_t N_CR1_sig_1, N_CR1_sig_2, N_CR1_sig_3, N_CR1_sig_4, N_CR1_sig_5;

  Int_t nbins=3;
  Double_t xbins[4] = {120, 170, 270, 1200};

  const char *path1 = "/home/valerian/programs/files/CR1_data.root";
  const char *path2 = "/home/valerian/programs/files/CR1_sig.root";
  const char *path3 = "/home/valerian/programs/files/CR1_bac.root";

  TFile *file_1 = new TFile(path1, "READ");
  TFile *file_2 = new TFile(path2, "READ");
  TFile *file_3 = new TFile(path3, "READ");

  TH1D *hist_CR1_jetgamma_1 = new TH1D ("hist1", "hist1", nbins, 0, 1200);
  TH1D *hist_CR1_jetgamma_2 = new TH1D ("hist2", "hist2", nbins, 0, 1200);
  TH1D *hist_CR1_jetgamma_3 = new TH1D ("hist3", "hist3", nbins, 0, 1200);
  TH1D *hist_CR1_jetgamma_4 = new TH1D ("hist4", "hist4", nbins, 0, 1200);
  TH1D *hist_CR1_jetgamma_5 = new TH1D ("hist5", "hist5", nbins, 0, 1200);

  TH1D *hist_CR1_data_1 = new TH1D ("hist1", "hist1", nbins, 0, 1200);
  TH1D *hist_CR1_data_2 = new TH1D ("hist2", "hist2", nbins, 0, 1200);
  TH1D *hist_CR1_data_3 = new TH1D ("hist3", "hist3", nbins, 0, 1200);
  TH1D *hist_CR1_data_4 = new TH1D ("hist4", "hist4", nbins, 0, 1200);
  TH1D *hist_CR1_data_5 = new TH1D ("hist5", "hist5", nbins, 0, 1200);

  TH1D *hist_CR1_sig_1 = new TH1D ("hist1", "hist1", nbins, 0, 1200);
  TH1D *hist_CR1_sig_2 = new TH1D ("hist2", "hist2", nbins, 0, 1200);
  TH1D *hist_CR1_sig_3 = new TH1D ("hist3", "hist3", nbins, 0, 1200);
  TH1D *hist_CR1_sig_4 = new TH1D ("hist4", "hist4", nbins, 0, 1200);
  TH1D *hist_CR1_sig_5 = new TH1D ("hist5", "hist5", nbins, 0, 1200);

  TH1D *hist_CR1_bac_1 = new TH1D ("hist1", "hist1", nbins, 0, 1200);
  TH1D *hist_CR1_bac_2 = new TH1D ("hist2", "hist2", nbins, 0, 1200);
  TH1D *hist_CR1_bac_3 = new TH1D ("hist3", "hist3", nbins, 0, 1200);
  TH1D *hist_CR1_bac_4 = new TH1D ("hist4", "hist4", nbins, 0, 1200);
  TH1D *hist_CR1_bac_5 = new TH1D ("hist5", "hist5", nbins, 0, 1200);

  hist_CR1_jetgamma_1 = dynamic_cast<TH1D*>(hist_CR1_jetgamma_1->Rebin(nbins,"hist1",xbins));
  hist_CR1_jetgamma_2 = dynamic_cast<TH1D*>(hist_CR1_jetgamma_2->Rebin(nbins,"hist2",xbins));
  hist_CR1_jetgamma_3 = dynamic_cast<TH1D*>(hist_CR1_jetgamma_3->Rebin(nbins,"hist3",xbins));
  hist_CR1_jetgamma_4 = dynamic_cast<TH1D*>(hist_CR1_jetgamma_4->Rebin(nbins,"hist4",xbins));
  hist_CR1_jetgamma_5 = dynamic_cast<TH1D*>(hist_CR1_jetgamma_5->Rebin(nbins,"hist5",xbins));

  hist_CR1_data_1 = dynamic_cast<TH1D*>(hist_CR1_data_1->Rebin(nbins,"hist1",xbins));
  hist_CR1_data_2 = dynamic_cast<TH1D*>(hist_CR1_data_2->Rebin(nbins,"hist2",xbins));
  hist_CR1_data_3 = dynamic_cast<TH1D*>(hist_CR1_data_3->Rebin(nbins,"hist3",xbins));
  hist_CR1_data_4 = dynamic_cast<TH1D*>(hist_CR1_data_4->Rebin(nbins,"hist4",xbins));
  hist_CR1_data_5 = dynamic_cast<TH1D*>(hist_CR1_data_5->Rebin(nbins,"hist5",xbins));

  hist_CR1_sig_1 = dynamic_cast<TH1D*>(hist_CR1_sig_1->Rebin(nbins,"hist1",xbins));
  hist_CR1_sig_2 = dynamic_cast<TH1D*>(hist_CR1_sig_2->Rebin(nbins,"hist2",xbins));
  hist_CR1_sig_3 = dynamic_cast<TH1D*>(hist_CR1_sig_3->Rebin(nbins,"hist3",xbins));
  hist_CR1_sig_4 = dynamic_cast<TH1D*>(hist_CR1_sig_4->Rebin(nbins,"hist4",xbins));
  hist_CR1_sig_5 = dynamic_cast<TH1D*>(hist_CR1_sig_5->Rebin(nbins,"hist5",xbins));

  hist_CR1_bac_1 = dynamic_cast<TH1D*>(hist_CR1_bac_1->Rebin(nbins,"hist1",xbins));
  hist_CR1_bac_2 = dynamic_cast<TH1D*>(hist_CR1_bac_2->Rebin(nbins,"hist2",xbins));
  hist_CR1_bac_3 = dynamic_cast<TH1D*>(hist_CR1_bac_3->Rebin(nbins,"hist3",xbins));
  hist_CR1_bac_4 = dynamic_cast<TH1D*>(hist_CR1_bac_4->Rebin(nbins,"hist4",xbins));
  hist_CR1_bac_5 = dynamic_cast<TH1D*>(hist_CR1_bac_5->Rebin(nbins,"hist5",xbins));

    hist_CR1_bac_1=(file_3->Get<TH1D>("hist1"));
    hist_CR1_bac_2=(file_3->Get<TH1D>("hist2"));
    hist_CR1_bac_3=(file_3->Get<TH1D>("hist3"));
    hist_CR1_bac_4=(file_3->Get<TH1D>("hist4"));
    hist_CR1_bac_5=(file_3->Get<TH1D>("hist5"));

    hist_CR1_data_1=(file_1->Get<TH1D>("hist1"));
    hist_CR1_data_2=(file_1->Get<TH1D>("hist2"));
    hist_CR1_data_3=(file_1->Get<TH1D>("hist3"));
    hist_CR1_data_4=(file_1->Get<TH1D>("hist4"));
    hist_CR1_data_5=(file_1->Get<TH1D>("hist5"));

    hist_CR1_sig_1=(file_2->Get<TH1D>("hist1"));
    hist_CR1_sig_2=(file_2->Get<TH1D>("hist2"));
    hist_CR1_sig_3=(file_2->Get<TH1D>("hist3"));
    hist_CR1_sig_4=(file_2->Get<TH1D>("hist4"));
    hist_CR1_sig_5=(file_2->Get<TH1D>("hist5"));

    hist_CR1_jetgamma_1->Add(hist_CR1_data_1);
    hist_CR1_jetgamma_2->Add(hist_CR1_data_2);
    hist_CR1_jetgamma_3->Add(hist_CR1_data_3);
    hist_CR1_jetgamma_4->Add(hist_CR1_data_4);
    hist_CR1_jetgamma_5->Add(hist_CR1_data_5);

    hist_CR1_jetgamma_1->Add(hist_CR1_sig_1,-1);
    hist_CR1_jetgamma_2->Add(hist_CR1_sig_2,-1);
    hist_CR1_jetgamma_3->Add(hist_CR1_sig_3,-1);
    hist_CR1_jetgamma_4->Add(hist_CR1_sig_4,-1);
    hist_CR1_jetgamma_5->Add(hist_CR1_sig_5,-1);

    hist_CR1_jetgamma_1->Add(hist_CR1_bac_1,-1);
    hist_CR1_jetgamma_2->Add(hist_CR1_bac_2,-1);
    hist_CR1_jetgamma_3->Add(hist_CR1_bac_3,-1);
    hist_CR1_jetgamma_4->Add(hist_CR1_bac_4,-1);
    hist_CR1_jetgamma_5->Add(hist_CR1_bac_5,-1);

     TFile *file_CR1 = new TFile ("CR1_jetgamma.root","UPDATE");
        hist_CR1_jetgamma_1->Write();
        hist_CR1_jetgamma_2->Write();
        hist_CR1_jetgamma_3->Write();
        hist_CR1_jetgamma_4->Write();
        hist_CR1_jetgamma_5->Write();
        file_CR1->Close();

        // N_CR1_data_1=hist_CR1_data_1->IntegralAndError(1, nbins, error_CR1_data_1, "");
        // N_CR1_data_2=hist_CR1_data_2->IntegralAndError(1, nbins, error_CR1_data_2, "");
        // N_CR1_data_3=hist_CR1_data_3->IntegralAndError(1, nbins, error_CR1_data_3, "");
        // N_CR1_data_4=hist_CR1_data_4->IntegralAndError(1, nbins, error_CR1_data_4, "");
        // N_CR1_data_5=hist_CR1_data_5->IntegralAndError(1, nbins, error_CR1_data_5, "");
        //
        // N_CR1_sig_1=hist_CR1_sig_1->IntegralAndError(1, nbins, error_CR1_sig_1, "");
        // N_CR1_sig_2=hist_CR1_sig_2->IntegralAndError(1, nbins, error_CR1_sig_2, "");
        // N_CR1_sig_3=hist_CR1_sig_3->IntegralAndError(1, nbins, error_CR1_sig_3, "");
        // N_CR1_sig_4=hist_CR1_sig_4->IntegralAndError(1, nbins, error_CR1_sig_4, "");
        // N_CR1_sig_5=hist_CR1_sig_5->IntegralAndError(1, nbins, error_CR1_sig_5, "");
        //
        // N_CR1_bac_1=hist_CR1_bac_1->IntegralAndError(1, nbins, error_CR1_bac_1, "");
        // N_CR1_bac_2=hist_CR1_bac_2->IntegralAndError(1, nbins, error_CR1_bac_2, "");
        // N_CR1_bac_3=hist_CR1_bac_3->IntegralAndError(1, nbins, error_CR1_bac_3, "");
        // N_CR1_bac_4=hist_CR1_bac_4->IntegralAndError(1, nbins, error_CR1_bac_4, "");
        // N_CR1_bac_5=hist_CR1_bac_5->IntegralAndError(1, nbins, error_CR1_bac_5, "");
        //
        // std::cout << "slice 1 " << " N_CR1_data_1=" << N_CR1_data_1 << " +- " << error_CR1_data_1 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 2 " << " N_CR1_data_2=" << N_CR1_data_2 << " +- " << error_CR1_data_2 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 3 " << " N_CR1_data_3=" << N_CR1_data_3 << " +- " << error_CR1_data_3 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 4 " << " N_CR1_data_4=" << N_CR1_data_4 << " +- " << error_CR1_data_4 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 5 " <<" N_CR1_data_5=" << N_CR1_data_5 << " +- " << error_CR1_data_5 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 1 " << " N_CR1_bac_1=" << N_CR1_bac_1 << " +- " << error_CR1_bac_1 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 2 " << " N_CR1_bac_2=" << N_CR1_bac_2 << " +- " << error_CR1_bac_2 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 3 " << " N_CR1_bac_3=" << N_CR1_bac_3 << " +- " << error_CR1_bac_3 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 4 " << " N_CR1_bac_4=" << N_CR1_bac_4 << " +- " << error_CR1_bac_4 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 5 " <<" N_CR1_bac_5=" << N_CR1_bac_5 << " +- " << error_CR1_bac_5 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 1 " << " N_CR1_sig_1=" << N_CR1_sig_1 << " +- " << error_CR1_sig_1 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 2 " << " N_CR1_sig_2=" << N_CR1_sig_2 << " +- " << error_CR1_sig_2 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 3 " << " N_CR1_sig_3=" << N_CR1_sig_3 << " +- " << error_CR1_sig_3 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 4 " << " N_CR1_sig_4=" << N_CR1_sig_4 << " +- " << error_CR1_sig_4 << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 5 " <<" N_CR1_sig_5=" << N_CR1_sig_5 << " +- " << error_CR1_sig_5 << '\n';
        // std::cout << "" << '\n';
        //
        //
        // std::cout << "slice 1 " << " N_CR1_jetgamma_1=" << N_CR1_data_1-N_CR1_sig_1-N_CR1_bac_1 << " +- " << sqrt(pow(error_CR1_sig_1,2)+pow(error_CR1_data_1,2)+pow(error_CR1_bac_1,2)) << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 2 " <<" N_CR1_jetgamma_2=" << N_CR1_data_2-N_CR1_sig_2-N_CR1_bac_2 << " +- " << sqrt(pow(error_CR1_sig_2,2)+pow(error_CR1_data_2,2)+pow(error_CR1_bac_2,2)) << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 3 " << " N_CR1_jetgamma_3=" << N_CR1_data_3-N_CR1_sig_3-N_CR1_bac_3 << " +- " << sqrt(pow(error_CR1_sig_3,2)+pow(error_CR1_data_3,2)+pow(error_CR1_bac_3,2)) << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 4 " << " N_CR1_jetgamma_4=" << N_CR1_data_4-N_CR1_sig_4-N_CR1_bac_4 << " +- " << sqrt(pow(error_CR1_sig_4,2)+pow(error_CR1_data_4,2)+pow(error_CR1_bac_4,2)) << '\n';
        // std::cout << "" << '\n';
        //
        // std::cout << "slice 5 " <<" N_CR1_jetgamma_5=" << N_CR1_data_5-N_CR1_sig_5-N_CR1_bac_5 << " +- " << sqrt(pow(error_CR1_sig_5,2)+pow(error_CR1_data_5,2)+pow(error_CR1_bac_5,2)) << '\n';
        // std::cout << "" << '\n';

}
