void mcp_test () 
{
  TFile* fin = new TFile("root/l5_500GeV.nung_1.root");
  TTree* data = static_cast<TTree*>(fin->Get("evtdata"));

  TH1F* hmcp_e = new TH1F("hmcp_e",";E_{MC} [GeV];",100,0,300);  
  TH2F* hmcp_e_theta = new TH2F("hmcp_e_theta",";#theta [rad];E [GeV]",100,0,TMath::Pi(),100,0,300);  
  TH2F* hmcp_e_phi = new TH2F("hmcp_e_phi",";#phi [rad];E [GeV]",100,-TMath::Pi(),TMath::Pi(),100,0,300);  
  TH2F* hmcp_r_z = new TH2F("hmcp_r_z",";z [mm]; r [mm]",200,-3500,3500,200,0,2500);  
  TH2F* hmcp_x_y = new TH2F("hmcp_x_y",";x [mm]; y[mm]",200,-2500,2500,200,-2500,2500);  

  const int NMAX = 10000;
  int nmcps, mcp_pdg[NMAX], mcp_index[NMAX], mcp_nparents[NMAX], mcp_parentIndex[NMAX][10];
  float mcp_e[NMAX], mcp_phi[NMAX], mcp_theta[NMAX];
  float mcp_endx[NMAX], mcp_endy[NMAX], mcp_endz[NMAX];
  data->SetBranchAddress("nmcps",&nmcps);
  data->SetBranchAddress("mcp_pdg",mcp_pdg);
  data->SetBranchAddress("mcp_index",mcp_index);
  data->SetBranchAddress("mcp_nparents",mcp_nparents);
  data->SetBranchAddress("mcp_parentIndex",mcp_parentIndex);
  data->SetBranchAddress("mcp_e",mcp_e);
  data->SetBranchAddress("mcp_phi",mcp_phi);
  data->SetBranchAddress("mcp_theta",mcp_theta);
  data->SetBranchAddress("mcp_endx",mcp_endx);
  data->SetBranchAddress("mcp_endy",mcp_endy);
  data->SetBranchAddress("mcp_endz",mcp_endz);

  int nevents = data->GetEntries();

  // event loop
  for (int ev = 0; ev < nevents; ev++) {
    data->GetEntry(ev);

    // mcp loop
    for (int i = 0; i < nmcps; i++) {
      if (mcp_pdg[i]==22) { // select photon
        if (mcp_parentIndex[i][0]==2&&mcp_parentIndex[i][1]==3) { // select only initial ones
          //cerr << "ev = " << ev << " " << mcp_index[i] << " " << mcp_parentIndex[i][1] << endl;
          hmcp_e->Fill(mcp_e[i]);
          hmcp_e_theta->Fill(mcp_theta[i],mcp_e[i]);
          hmcp_e_phi->Fill(mcp_phi[i],mcp_e[i]);
          TVector3 endp(mcp_endx[i],mcp_endy[i],mcp_endz[i]);
          hmcp_r_z->Fill(endp.Z(),endp.Perp());
          hmcp_x_y->Fill(endp.X(),endp.Y());
        } 
      } 
    }
  }
  TCanvas* ce = new TCanvas("ce","",600,400);
  hmcp_e->Draw();
  TCanvas* cetheta = new TCanvas("cetheta","",600,400);
  hmcp_e_theta->Draw();
  TCanvas* cephi = new TCanvas("cephi","",600,400);
  hmcp_e_phi->Draw();
  TCanvas* crz = new TCanvas("crz","",600,400);
  hmcp_r_z->Draw("COLZ");
  TCanvas* cxy = new TCanvas("cxy","",600,400);
  hmcp_x_y->Draw("COLZ");
}
