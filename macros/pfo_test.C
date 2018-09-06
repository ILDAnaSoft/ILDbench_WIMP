void pfo_test () 
{
  TFile* fin = new TFile("root/l5_500GeV.nung_1.root");
  TTree* data = static_cast<TTree*>(fin->Get("evtdata"));

  TH1F* hpfo_e = new TH1F("hpfo_e",";E [GeV];",100,0,300);  
  TH2F* hpfo_e_theta = new TH2F("hpfo_e_theta",";#theta [rad];E [GeV]",100,0,TMath::Pi(),100,0,300);  
  TH2F* hpfo_r_z = new TH2F("hpfo_r_z",";z [mm]; r [mm]",200,-3500,3500,200,0,2500);  
  TH2F* hpfo_x_y = new TH2F("hpfo_x_y",";x [mm];y [mm]",200,-2500,2500,200,-2500,2500);  
  TH1F* hres_e = new TH1F("hres_e",";E_{reco} - E_{MC} [GeV];",100,-5,5);  
  TH2F* hres_e_theta = new TH2F("hres_e_theta",";#theta [rad]; E_{reco} - E_{MC} [GeV]",100,0,TMath::Pi(),100,-10,10);  
  TH2F* hres_e_e = new TH2F("hres_e_e",";E [GeV]; E_{reco} - E_{MC} [GeV]",100,0,300,100,-10,10);  

  const int NMAX = 10000;
  int npfos, pfo_pdg[NMAX], mcr_index[NMAX], mcr_nparents[NMAX], mcr_parentIndex[NMAX][10];
  float pfo_e[NMAX], pfo_phi[NMAX], pfo_theta[NMAX];
  float mcr_e[NMAX], mcr_phi[NMAX], mcr_theta[NMAX];
  float pfo_cal_x[NMAX], pfo_cal_y[NMAX], pfo_cal_z[NMAX];
  data->SetBranchAddress("npfos",&npfos);
  data->SetBranchAddress("pfo_pdg",pfo_pdg);
  data->SetBranchAddress("mcr_index",mcr_index);
  data->SetBranchAddress("mcr_nparents",mcr_nparents);
  data->SetBranchAddress("mcr_parentIndex",mcr_parentIndex);
  data->SetBranchAddress("pfo_e",pfo_e);
  data->SetBranchAddress("mcr_e",mcr_e);
  data->SetBranchAddress("pfo_phi",pfo_phi);
  data->SetBranchAddress("pfo_theta",pfo_theta);
  data->SetBranchAddress("pfo_cal_x",pfo_cal_x);
  data->SetBranchAddress("pfo_cal_y",pfo_cal_y);
  data->SetBranchAddress("pfo_cal_z",pfo_cal_z);

  int nevents = data->GetEntries();

  // event loop
  for (int ev = 0; ev < nevents; ev++) {
    data->GetEntry(ev);

    // pfo loop
    for (int i = 0; i < npfos; i++) {
      if (pfo_pdg[i]==22) { // select photon

        TVector3 pos(pfo_cal_x[i],pfo_cal_y[i],pfo_cal_z[i]);
        hpfo_r_z->Fill(pos.Z(),pos.Perp());
        hpfo_x_y->Fill(pos.X(),pos.Y());

        if (mcr_parentIndex[i][0]==2&&mcr_parentIndex[i][1]==3) { // select only initial ones
          //cerr << "ev = " << ev << " " << mcr_index[i] << " " << mcr_parentIndex[i][1] << endl;
          hpfo_e->Fill(pfo_e[i]);
          hpfo_e_theta->Fill(pfo_theta[i],pfo_e[i]);
          hres_e->Fill(pfo_e[i]-mcr_e[i]);
          hres_e_theta->Fill(pfo_theta[i],pfo_e[i]-mcr_e[i]);
          hres_e_e->Fill(pfo_e[i],pfo_e[i]-mcr_e[i]);
        } 
      } 
    }
  }
  TCanvas* ce = new TCanvas("ce","",600,400);
  hpfo_e->Draw();
  TCanvas* cetheta = new TCanvas("cetheta","",600,400);
  hpfo_e_theta->Draw();
  TCanvas* crz = new TCanvas("crz","",600,400);
  hpfo_r_z->Draw("COLZ");
  TCanvas* cxy = new TCanvas("cxy","",600,400);
  hpfo_x_y->Draw("COLZ");
  TCanvas* crese = new TCanvas("crese","",600,400);
  hres_e->Draw();
  TCanvas* cresetheta = new TCanvas("cresetheta","",600,400);
  hres_e_theta->Draw();
  TCanvas* cresethetafit = new TCanvas("cresethetafit","",600,400);
  hres_e_theta->FitSlicesY();
  TH1F* hres_e_theta_2 = static_cast<TH1F*>(gROOT->FindObject("hres_e_theta_2")); // sigma
  hres_e_theta_2->SetTitle(";#theta [rad]; #sigma_{E} [GeV]");
  hres_e_theta_2->Draw();
  TCanvas* cresee = new TCanvas("cresee","",600,400);
  hres_e_e->Draw();
  TCanvas* creseefit = new TCanvas("creseefit","",600,400);
  hres_e_e->FitSlicesY();
  TH1F* hres_e_e_2 = static_cast<TH1F*>(gROOT->FindObject("hres_e_e_2")); //sigma
  hres_e_e_2->SetTitle(";E [GeV]; #sigma_{E} [GeV]");
  hres_e_e_2->Draw();
}
