#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"

void R_factor(){

  const char *znunu_data_1[] ={"/home/valerian/programs/data/Znunu_364222/user.akurova.364222a.MxAOD.root", "/home/valerian/programs/data/Znunu_364222/user.akurova.364222d.MxAOD.root", "/home/valerian/programs/data/Znunu_364222/user.akurova.364222e.MxAOD.root"};

  UInt_t n_ph, n_jet, n_e_looseBL, n_mu, ph_isem;
  double_t weight, ph_pt, ph_phi, ph_iso_et40, ph_iso_et20, ph_iso_pt, ph_z_point;
  double_t jet_lead_phi,jet_sublead_phi, metTST_pt, metTST_phi, metTSTsignif, koef;
  double_t N_BE_data_a = 0, N_DF_data_a = 0, N_E_data_a = 0, N_F_data_a = 0;
  double_t  N_BE_data_d = 0,  N_DF_data_d = 0,  N_E_data_d = 0,  N_F_data_d = 0;
  double_t  N_BE_data_e = 0,  N_DF_data_e = 0,  N_E_data_e = 0,  N_F_data_e = 0;
  double_t N_BE_data, N_DF_data, N_E_data, N_F_data;
  double_t L_a = 36214.96, L_d = 44307.4, L_e = 58450.1, L_j, norm_koef;
  double_t sumw = 0;

  int n = sizeof(znunu_data_1)/sizeof(znunu_data_1[0]);
  for (int j = 0; j <= 2; j++) {

  //  (j==0) ? L_j=L_a : (j==1) ? L_j=L_d : L_j=L_e;
    TFile *znunu= new TFile(znunu_data_1[j], "READ");
    cout << znunu_data_1[j]<< endl;
    TTree *tree = (TTree*)znunu->Get("output_tree");
    TTree *tree_koef= (TTree*)znunu->Get("norm_tree");
    //tree->Show();
    //tree_koef->Show();

    tree->SetBranchAddress("n_ph", &n_ph);
    tree->SetBranchAddress("n_jet", &n_jet);
    tree->SetBranchAddress("n_e_looseBL", &n_e_looseBL);
    tree->SetBranchAddress("n_mu", &n_mu);
    tree->SetBranchAddress("weight", &weight);
    tree->SetBranchAddress("ph_pt",&ph_pt);
    tree->SetBranchAddress("ph_phi",&ph_phi);
    tree->SetBranchAddress("ph_iso_et40", &ph_iso_et40);
    tree->SetBranchAddress("ph_iso_et20", &ph_iso_et20);
    tree->SetBranchAddress("ph_iso_pt", &ph_iso_pt);
    tree->SetBranchAddress("ph_isem", &ph_isem);
    tree->SetBranchAddress("ph_z_point", &ph_z_point);
    tree->SetBranchAddress("jet_lead_phi",&jet_lead_phi);
    tree->SetBranchAddress("jet_sublead_phi",&jet_sublead_phi);
    tree->SetBranchAddress("metTST_pt", &metTST_pt);
    tree->SetBranchAddress("metTST_phi",&metTST_phi);
    tree->SetBranchAddress("metTSTsignif", &metTSTsignif);

    tree_koef->SetBranchAddress("koef", &koef);

    int Num_koef = (int)tree_koef->GetEntries();

    for (int l=0; l<Num_koef; l++){
      tree_koef->GetEntry(l);
    //  tree_koef->Show(l);
    }

  int Num = (int)tree->GetEntries();

  for (int i=0; i<Num; i++){   // Критерии отбора событий для процесса с конечным состоянием
    tree->GetEntry(i);
    if (ph_pt <= 150) continue;                                //Ограничение на поперечный импульс фотона, обусловленное особенностями триггерной системы
    if (n_ph !=1 || n_e_looseBL !=0 || n_mu!=0) continue;      //Условие на число фотонов; лептонное вето, отсеивающее процессы с лептонами в конечном состоянии
    if (abs(ph_z_point) >= 250) continue;                      //Условие на координатную переменную, соответствующую наиболее эффективному отбору для подавления первичных фотонов, которые обусловленн конфигурацией пучка
    if (abs(weight) >= 100) continue;
    if (metTST_pt <=130) continue;                             //Потеренная поперечная энергия(модуль вектора потеренного поперечного импульса)
    if (metTSTsignif <= 11) continue;                          //Значимость, отделяющая события с правдивой величиной от события с ложной величиной потерянной поперечной энергии
    if (abs(metTST_phi - ph_phi) <= 0.7) continue;             //Разность азимутальных углов
    if (n_jet >= 1 && abs(metTST_phi - jet_lead_phi) <= 0.4) continue;

    double_t M_cut = 7, Iso_gap = 2, U_cut = 29.45;
    UInt_t Loose=0x27fc01;

    double_t Iso_cal = ph_iso_et20 - 0.065*ph_pt;                //Калориметрическая изоляция, сооответствующая изоляции FixedCutLoose
    double_t Iso_track = ph_iso_pt/ph_pt;                       //Трековая изоляция

    double_t sum_of_weights_bk_xAOD;
    TTree *tree_sum_w = (TTree*)znunu->Get("output_tree_sw");
    tree_sum_w->SetBranchAddress("sum_of_weights_bk_xAOD",&sum_of_weights_bk_xAOD);
    int entry = (int)tree_sum_w->GetEntries();
    for (int k=0; k<entry; k++)
    {
      tree_sum_w->GetEntry(i);
      sumw += sum_of_weights_bk_xAOD;
    }

    if (Iso_cal > Iso_gap && Iso_cal < M_cut && ph_isem == 0 && Iso_track < 0.05) j==0 ? N_BE_data_a+=1 : j==1 ? N_BE_data_d+=1 : N_BE_data_e+=1;
    if (Iso_cal > M_cut && Iso_cal < U_cut && ph_isem == 0 && Iso_track < 0.05) j==0 ? N_E_data_a+=1 : j==1 ? N_E_data_d+=1 : N_E_data_e+=1;
    if (Iso_cal > Iso_gap && Iso_cal < M_cut && (ph_isem !=0 && (ph_isem & Loose) == 0) && Iso_track < 0.05) j==0 ? N_DF_data_a+=1 : j==1 ? N_DF_data_d+=1 : N_DF_data_e+=1;
    if (Iso_cal > M_cut && Iso_cal < U_cut && (ph_isem != 0 && (ph_isem & Loose) == 0) && Iso_track < 0.05) j==0 ? N_F_data_a+=1 : j==1 ? N_F_data_d+=1 : N_F_data_e+=1;
  //  tree->Show(i);
  }
    // std::cout << "sum_w=" << sumw << '\n';
    // std::cout << "koef=" << koef << '\n';
    // std::cout << "L_j=" << L_j << '\n';
    // std::cout << "N_BE_data_a=" << N_BE_data_a << " " << "N_BE_data_d=" << N_BE_data_d << " " << "N_BE_data_e=" << N_BE_data_e << '\n';
    // std::cout << "  " << '\n';
    // std::cout << "N_BE_data_a=" <<N_BE_data_a << " " << "N_BE_data_d="<< N_BE_data_d<< " "<< "N_E_data_a="<< N_E_data_a << " " << "N_E_data_d="<< N_E_data_d <<'\n';
}
    // std::cout << "koef=" << koef <<  '\n';
    // norm_koef=koef*L_a/sumw;
    // std::cout << "N_BE_data_a=" <<N_BE_data_a << " " << "N_BE_data_d="<< N_BE_data_d<< " "<< "N_E_data_a="<< N_E_data_a << " " << "N_E_data_d="<< N_E_data_d <<'\n';
    // std::cout << "norm_koef=" << norm_koef << '\n';

  N_BE_data_a*=koef*L_a/sumw;
  N_E_data_a*=koef*L_a/sumw;
  N_DF_data_a*=koef*L_a/sumw;
  N_F_data_a*=koef*L_a/sumw;

  N_BE_data_d*=koef*L_d/sumw;
  N_E_data_d*=koef*L_d/sumw;
  N_DF_data_d*=koef*L_d/sumw;
  N_F_data_d*=koef*L_d/sumw;

  N_BE_data_e*=koef*L_e/sumw;
  N_E_data_e*=koef*L_e/sumw;
  N_DF_data_e*=koef*L_e/sumw;
  N_F_data_e*=koef*L_e/sumw;

  N_BE_data=N_BE_data_a+N_BE_data_d+N_BE_data_e;
  N_E_data=N_E_data_a+N_E_data_d+N_E_data_e;
  N_DF_data=N_DF_data_a+N_DF_data_d+N_DF_data_e;
  N_F_data=N_F_data_a+N_F_data_d+N_F_data_e;

    //std::cout << "N_BE_data=" << N_BE_data << '\n';

    double_t R = (N_BE_data*N_F_data)/(N_E_data*N_DF_data);
    cout << "R_factor=" << R << endl;
}
