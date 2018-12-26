void drawPlots(TString fname)
{ 
  TFile* fin = new TFile(fname.Data());

  UpdateMetaData(); // see util.C
  float xs_nungLR = getXsec("nung.eL.pR");
  float xs_nungRL = getXsec("nung.eL.pR");
  float xs_bhabhangLL = getXsec("bhabhang.eL.pL");
  float xs_bhabhangLR = getXsec("bhabhang.eL.pR");
  float xs_bhabhangRL = getXsec("bhabhang.eR.pL");
  float xs_bhabhangRR = getXsec("bhabhang.eR.pR");

  const float L = 500.; 
  const float epol = 0.8;
  const float ppol = 0.3;
  enum POL { LL, LR, RL, RR };
  float pfrac[4];
  pfrac[LL] = 0.1 * L * (1-epol) * (1-ppol) / 4.;
  pfrac[LR] = 0.4 * L * (1-epol) * (1+ppol) / 4.;
  pfrac[RL] = 0.4 * L * (1+epol) * (1-ppol) / 4.;
  pfrac[RR] = 0.1 * L * (1+epol) * (1+ppol) / 4.;
  

  /*
  cerr << xs_nungLR << " "
       << xs_nungRL << " "
       << xs_bhabhangLL << " "
       << xs_bhabhangLR << " "
       << xs_bhabhangRL << " "
       << xs_bhabhangRR << endl; 
  */
  TH1F* hCutStats_nungLR              = static_cast<TH1F*>(fin->Get("hCutStats_nungLR"));
  TH1F* hCutStats_nungRL              = static_cast<TH1F*>(fin->Get("hCutStats_nungRL"));
  TH1F* hCutStats_bhabhangLL          = static_cast<TH1F*>(fin->Get("hCutStats_bhabhangLL"));
  TH1F* hCutStats_bhabhangLR          = static_cast<TH1F*>(fin->Get("hCutStats_bhabhangLR"));
  TH1F* hCutStats_bhabhangRL          = static_cast<TH1F*>(fin->Get("hCutStats_bhabhangRL"));
  TH1F* hCutStats_bhabhangRR          = static_cast<TH1F*>(fin->Get("hCutStats_bhabhangRR"));
  int n_nung_LR = hCutStats_nungLR->GetBinContent(1); // nentries in "nocut" bin
  int n_nung_RL = hCutStats_nungRL->GetBinContent(1); // nentries in "nocut" bin
  int n_bhabhang_LL = hCutStats_bhabhangLL->GetBinContent(1); // nentries in "nocut" bin
  int n_bhabhang_LR = hCutStats_bhabhangLR->GetBinContent(1); // nentries in "nocut" bin
  int n_bhabhang_RL = hCutStats_bhabhangRL->GetBinContent(1); // nentries in "nocut" bin
  int n_bhabhang_RR = hCutStats_bhabhangRR->GetBinContent(1); // nentries in "nocut" bin

  float w_nung_LR = xs_nungLR * pfrac[LR] / n_nung_LR;
  float w_nung_RL = xs_nungRL * pfrac[RL] / n_nung_RL;
  float w_bhabhang_LL = xs_bhabhangLL * pfrac[LL] / n_bhabhang_LL;
  float w_bhabhang_LR = xs_bhabhangLR * pfrac[LR] / n_bhabhang_LR;
  float w_bhabhang_RL = xs_bhabhangRL * pfrac[RL] / n_bhabhang_RL;
  float w_bhabhang_RR = xs_bhabhangRR * pfrac[RR] / n_bhabhang_RR;

  TH1F* hE_photon_nungLR              = static_cast<TH1F*>(fin->Get("hE_photon_nungLR"));
  TH1F* hE_photon_nungRL              = static_cast<TH1F*>(fin->Get("hE_photon_nungRL"));
  TH1F* hE_photon_nungSum             = new TH1F("hE_photon_nungSum",";E [GeV/c];",300,0,300);
  hE_photon_nungSum->Add(hE_photon_nungLR,w_nung_LR);
  hE_photon_nungSum->Add(hE_photon_nungRL,w_nung_RL);

  // photon reco efficiency w.r.t. energy
  TH1F* hNrecNgen_photon_nungLR       = static_cast<TH1F*>(fin->Get("hNrecNgen_photon_nungLR"));
  TH1F* hNrecNgen_photon_nungRL       = static_cast<TH1F*>(fin->Get("hNrecNgen_photon_nungRL"));
  TH1F* hNrecNgen_photon_nungSum      = new TH1F("hNrecNgen_photon_nungSum",";# #gamma_{rec}/#gamma_{gen};",8,0,8);
  hNrecNgen_photon_nungSum->Add(hNrecNgen_photon_nungLR,w_nung_LR);
  hNrecNgen_photon_nungSum->Add(hNrecNgen_photon_nungRL,w_nung_RL);
  TH1F* hNrecNgenEmc_photon_nungLR    = static_cast<TH1F*>(fin->Get("hNrecNgenEmc_photon_nungLR"));
  TH1F* hNrecNgenEmc_photon_nungRL    = static_cast<TH1F*>(fin->Get("hNrecNgenEmc_photon_nungRL"));
  const int xbins_e = 100;
  float xmin_e = 0.;
  float xmax_e = 250.;
  const int ybins_e = 100;
  float ymin_e = 0.;
  float ymax_e = 8.;
  TH2F* hNrecNgenEmc_photon_nungSum   = new TH2F("hNrecNgenEmc_photon_nungSum",";E_{#gamma,MC} [GeV/c];#bar{N_{rec}/N_{gen}}",xbins_e,xmin_e,xmax_e,ybins_e,ymin_e,ymax_e);
  hNrecNgenEmc_photon_nungSum->Add(hNrecNgenEmc_photon_nungLR); // no need to normalize.
  hNrecNgenEmc_photon_nungSum->Add(hNrecNgenEmc_photon_nungRL); // no need to normalize. 
  double x_e[xbins_e], xerr_e[xbins_e], y_e[xbins_e], yerr_e[xbins_e];
  for (int ix = 1; ix <= xbins_e; ix++) {
    x_e[ix-1] = hNrecNgenEmc_photon_nungSum->GetXaxis()->GetBinCenter(ix);
    xerr_e[ix-1] = hNrecNgenEmc_photon_nungSum->GetXaxis()->GetBinWidth(ix)/TMath::Sqrt(12);
    TH1F h_y_e("h_y_e","",ybins_e,ymin_e,ymax_e);
    for (int iy = 1; iy <= ybins_e; iy++) {
      for (int icontent = 0; icontent < hNrecNgenEmc_photon_nungSum->GetBinContent(ix,iy); icontent++) {
        h_y_e.Fill(hNrecNgenEmc_photon_nungSum->GetYaxis()->GetBinCenter(iy)); 
      }
    }
    y_e[ix-1] = h_y_e.GetMean();
    yerr_e[ix-1] = h_y_e.GetRMS() / TMath::Sqrt(h_y_e.GetEntries());
  }
  TGraphErrors* gNrecNgenEmc_photon_nungSum = new TGraphErrors(xbins_e,x_e,y_e,xerr_e,yerr_e);
  gNrecNgenEmc_photon_nungSum->SetTitle(";E_{#gamma,MC} [GeV/c];#bar{N_{rec}/N_{gen}}");
  
  // photon reco efficiency w.r.t. cos(theta)
  TH1F* hNrecNgenCostheta_photon_nungLR    = static_cast<TH1F*>(fin->Get("hNrecNgenCostheta_photon_nungLR"));
  TH1F* hNrecNgenCostheta_photon_nungRL    = static_cast<TH1F*>(fin->Get("hNrecNgenCostheta_photon_nungRL"));
  const int xbins_cos = 100;
  float xmin_cos = 0.;
  float xmax_cos = 1.;
  const int ybins_cos = 100;
  float ymin_cos = 0.;
  float ymax_cos = 8.;
  TH2F* hNrecNgenCostheta_photon_nungSum   = new TH2F("hNrecNgenCostheta_photon_nungSum",";cos#theta_{#gamma,MC};#bar{N_{rec}/N_{gen}}",xbins_cos,xmin_cos,xmax_cos,ybins_cos,ymin_cos,ymax_cos);
  hNrecNgenCostheta_photon_nungSum->Add(hNrecNgenCostheta_photon_nungLR); // no need to normalize.
  hNrecNgenCostheta_photon_nungSum->Add(hNrecNgenCostheta_photon_nungRL); // no need to normalize. 
  double x_cos[xbins_cos], xerr_cos[xbins_cos], y_cos[xbins_cos], yerr_cos[xbins_cos];
  for (int ix = 1; ix <= xbins_cos; ix++) {
    x_cos[ix-1] = hNrecNgenCostheta_photon_nungSum->GetXaxis()->GetBinCenter(ix);
    xerr_cos[ix-1] = hNrecNgenCostheta_photon_nungSum->GetXaxis()->GetBinWidth(ix)/TMath::Sqrt(12);
    TH1F h_y_cos("h_y_cos","",ybins_cos,ymin_cos,ymax_cos);
    for (int iy = 1; iy <= ybins_cos; iy++) {
      for (int icontent = 0; icontent < hNrecNgenCostheta_photon_nungSum->GetBinContent(ix,iy); icontent++) {
        h_y_cos.Fill(hNrecNgenCostheta_photon_nungSum->GetYaxis()->GetBinCenter(iy)); 
      }
    }
    y_cos[ix-1] = h_y_cos.GetMean();
    yerr_cos[ix-1] = h_y_cos.GetRMS() / TMath::Sqrt(h_y_cos.GetEntries());
  }
  TGraphErrors* gNrecNgenCostheta_photon_nungSum = new TGraphErrors(xbins_cos,x_cos,y_cos,xerr_cos,yerr_cos);
  gNrecNgenCostheta_photon_nungSum->SetTitle(";cos#theta_{#gamma,MC};#bar{N_{rec}/N_{gen}}");

  TH1F* hPt_ep_nungLR_other             = static_cast<TH1F*>(fin->Get("hPt_ep_nungLR_other"));
  TH1F* hPt_ep_nungRL_other             = static_cast<TH1F*>(fin->Get("hPt_ep_nungRL_other"));
  TH1F* hPt_ep_nungSum_other            = new TH1F("hPt_ep_nungSum_other" ,";Pt [GeV/c];",270,0,270);
  hPt_ep_nungSum_other->Add(hPt_ep_nungLR_other,w_nung_LR);
  hPt_ep_nungSum_other->Add(hPt_ep_nungRL_other,w_nung_RL);

  TH1F* hPt_ep_nungLR_ol                = static_cast<TH1F*>(fin->Get("hPt_ep_nungLR_ol"));
  TH1F* hPt_ep_nungRL_ol                = static_cast<TH1F*>(fin->Get("hPt_ep_nungRL_ol"));
  TH1F* hPt_ep_nungSum_ol               = new TH1F("hPt_ep_nungSum_ol" ,";Pt [GeV/c];",270,0,270);
  hPt_ep_nungSum_ol->Add(hPt_ep_nungLR_ol,w_nung_LR);
  hPt_ep_nungSum_ol->Add(hPt_ep_nungRL_ol,w_nung_RL);

  TH1F* hPt_ep_nungLR_isr               = static_cast<TH1F*>(fin->Get("hPt_ep_nungLR_isr"));
  TH1F* hPt_ep_nungRL_isr               = static_cast<TH1F*>(fin->Get("hPt_ep_nungRL_isr"));
  TH1F* hPt_ep_nungSum_isr              = new TH1F("hPt_ep_nungSum_isr"   ,";Pt [GeV/c];",270,0,270);
  hPt_ep_nungSum_isr->Add(hPt_ep_nungLR_isr,w_nung_LR);
  hPt_ep_nungSum_isr->Add(hPt_ep_nungRL_isr,w_nung_RL);

  TH1F* hPt_pfo_nungLR_isr              = static_cast<TH1F*>(fin->Get("hPt_pfo_nungLR_isr"));
  TH1F* hPt_pfo_nungRL_isr              = static_cast<TH1F*>(fin->Get("hPt_pfo_nungRL_isr"));
  TH1F* hPt_pfo_nungSum_isr             = new TH1F("hPt_pfo_nungSum_isr"   ,";Pt [GeV/c];",270,0,270);
  hPt_pfo_nungSum_isr->Add(hPt_pfo_nungLR_isr,w_nung_LR);
  hPt_pfo_nungSum_isr->Add(hPt_pfo_nungRL_isr,w_nung_RL);
  TH1F* hPt_pfo_nungLR_ol               = static_cast<TH1F*>(fin->Get("hPt_pfo_nungLR_ol"));
  TH1F* hPt_pfo_nungRL_ol               = static_cast<TH1F*>(fin->Get("hPt_pfo_nungRL_ol"));
  TH1F* hPt_pfo_nungSum_ol             = new TH1F("hPt_pfo_nungSum_ol"   ,";Pt [GeV/c];",270,0,270);
  hPt_pfo_nungSum_ol->Add(hPt_pfo_nungLR_ol,w_nung_LR);
  hPt_pfo_nungSum_ol->Add(hPt_pfo_nungRL_ol,w_nung_RL);
  TH1F* hPt_pfo_nungLR_other            = static_cast<TH1F*>(fin->Get("hPt_pfo_nungLR_other"));
  TH1F* hPt_pfo_nungRL_other            = static_cast<TH1F*>(fin->Get("hPt_pfo_nungRL_other"));
  TH1F* hPt_pfo_nungSum_other             = new TH1F("hPt_pfo_nungSum_other"   ,";Pt [GeV/c];",270,0,270);
  hPt_pfo_nungSum_other->Add(hPt_pfo_nungLR_other,w_nung_LR);
  hPt_pfo_nungSum_other->Add(hPt_pfo_nungRL_other,w_nung_RL);

  TH1F* hE_photon_nungLR_rest           = static_cast<TH1F*>(fin->Get("hE_photon_nungLR_rest"));
  TH1F* hE_photon_nungRL_rest           = static_cast<TH1F*>(fin->Get("hE_photon_nungRL_rest"));
  TH1F* hE_photon_nungSum_rest          = new TH1F("hE_photon_nungSum_rest",";E [GeV];",350,0,350);
  hE_photon_nungSum_rest->Add(hE_photon_nungLR_rest,w_nung_LR);
  hE_photon_nungSum_rest->Add(hE_photon_nungRL_rest,w_nung_RL);
  TH1F* hE_photon_nungLR_ol             = static_cast<TH1F*>(fin->Get("hE_photon_nungLR_ol"));
  TH1F* hE_photon_nungRL_ol             = static_cast<TH1F*>(fin->Get("hE_photon_nungRL_ol"));
  TH1F* hE_photon_nungSum_ol          = new TH1F("hE_photon_nungSum_ol",";E [GeV];",350,0,350);
  hE_photon_nungSum_ol->Add(hE_photon_nungLR_ol,w_nung_LR);
  hE_photon_nungSum_ol->Add(hE_photon_nungRL_ol,w_nung_RL);
  TH1F* hE_V0_nungLR_rest           = static_cast<TH1F*>(fin->Get("hE_V0_nungLR_rest"));
  TH1F* hE_V0_nungRL_rest           = static_cast<TH1F*>(fin->Get("hE_V0_nungRL_rest"));
  TH1F* hE_V0_nungSum_rest          = new TH1F("hE_V0_nungSum_rest",";E [GeV];",350,0,350);
  hE_V0_nungSum_rest->Add(hE_V0_nungLR_rest,w_nung_LR);
  hE_V0_nungSum_rest->Add(hE_V0_nungRL_rest,w_nung_RL);
  TH1F* hE_V0_nungLR_ol             = static_cast<TH1F*>(fin->Get("hE_V0_nungLR_ol"));
  TH1F* hE_V0_nungRL_ol             = static_cast<TH1F*>(fin->Get("hE_V0_nungRL_ol"));
  TH1F* hE_V0_nungSum_ol          = new TH1F("hE_V0_nungSum_ol",";E [GeV];",350,0,350);
  hE_V0_nungSum_ol->Add(hE_V0_nungLR_ol,w_nung_LR);
  hE_V0_nungSum_ol->Add(hE_V0_nungRL_ol,w_nung_RL);
  TH1F* hE_neutron_nungLR_rest           = static_cast<TH1F*>(fin->Get("hE_neutron_nungLR_rest"));
  TH1F* hE_neutron_nungRL_rest           = static_cast<TH1F*>(fin->Get("hE_neutron_nungRL_rest"));
  TH1F* hE_neutron_nungSum_rest          = new TH1F("hE_neutron_nungSum_rest",";E [GeV];",350,0,350);
  hE_neutron_nungSum_rest->Add(hE_neutron_nungLR_rest,w_nung_LR);
  hE_neutron_nungSum_rest->Add(hE_neutron_nungRL_rest,w_nung_RL);
  TH1F* hE_neutron_nungLR_ol             = static_cast<TH1F*>(fin->Get("hE_neutron_nungLR_ol"));
  TH1F* hE_neutron_nungRL_ol             = static_cast<TH1F*>(fin->Get("hE_neutron_nungRL_ol"));
  TH1F* hE_neutron_nungSum_ol          = new TH1F("hE_neutron_nungSum_ol",";E [GeV];",350,0,350);
  hE_neutron_nungSum_ol->Add(hE_neutron_nungLR_ol,w_nung_LR);
  hE_neutron_nungSum_ol->Add(hE_neutron_nungRL_ol,w_nung_RL);
  TH1F* hE_electron_nungLR_rest           = static_cast<TH1F*>(fin->Get("hE_electron_nungLR_rest"));
  TH1F* hE_electron_nungRL_rest           = static_cast<TH1F*>(fin->Get("hE_electron_nungRL_rest"));
  TH1F* hE_electron_nungSum_rest          = new TH1F("hE_electron_nungSum_rest",";E [GeV];",350,0,350);
  hE_electron_nungSum_rest->Add(hE_electron_nungLR_rest,w_nung_LR);
  hE_electron_nungSum_rest->Add(hE_electron_nungRL_rest,w_nung_RL);
  TH1F* hE_electron_nungLR_ol             = static_cast<TH1F*>(fin->Get("hE_electron_nungLR_ol"));
  TH1F* hE_electron_nungRL_ol             = static_cast<TH1F*>(fin->Get("hE_electron_nungRL_ol"));
  TH1F* hE_electron_nungSum_ol          = new TH1F("hE_electron_nungSum_ol",";E [GeV];",350,0,350);
  hE_electron_nungSum_ol->Add(hE_electron_nungLR_ol,w_nung_LR);
  hE_electron_nungSum_ol->Add(hE_electron_nungRL_ol,w_nung_RL);
  TH1F* hE_muon_nungLR_rest           = static_cast<TH1F*>(fin->Get("hE_muon_nungLR_rest"));
  TH1F* hE_muon_nungRL_rest           = static_cast<TH1F*>(fin->Get("hE_muon_nungRL_rest"));
  TH1F* hE_muon_nungSum_rest          = new TH1F("hE_muon_nungSum_rest",";E [GeV];",350,0,350);
  hE_muon_nungSum_rest->Add(hE_muon_nungLR_rest,w_nung_LR);
  hE_muon_nungSum_rest->Add(hE_muon_nungRL_rest,w_nung_RL);
  TH1F* hE_muon_nungLR_ol             = static_cast<TH1F*>(fin->Get("hE_muon_nungLR_ol"));
  TH1F* hE_muon_nungRL_ol             = static_cast<TH1F*>(fin->Get("hE_muon_nungRL_ol"));
  TH1F* hE_muon_nungSum_ol          = new TH1F("hE_muon_nungSum_ol",";E [GeV];",350,0,350);
  hE_muon_nungSum_ol->Add(hE_muon_nungLR_ol,w_nung_LR);
  hE_muon_nungSum_ol->Add(hE_muon_nungRL_ol,w_nung_RL);
  TH1F* hE_pion_nungLR_rest           = static_cast<TH1F*>(fin->Get("hE_pion_nungLR_rest"));
  TH1F* hE_pion_nungRL_rest           = static_cast<TH1F*>(fin->Get("hE_pion_nungRL_rest"));
  TH1F* hE_pion_nungSum_rest          = new TH1F("hE_pion_nungSum_rest",";E [GeV];",350,0,350);
  hE_pion_nungSum_rest->Add(hE_pion_nungLR_rest,w_nung_LR);
  hE_pion_nungSum_rest->Add(hE_pion_nungRL_rest,w_nung_RL);
  TH1F* hE_pion_nungLR_ol             = static_cast<TH1F*>(fin->Get("hE_pion_nungLR_ol"));
  TH1F* hE_pion_nungRL_ol             = static_cast<TH1F*>(fin->Get("hE_pion_nungRL_ol"));
  TH1F* hE_pion_nungSum_ol          = new TH1F("hE_pion_nungSum_ol",";E [GeV];",350,0,350);
  hE_pion_nungSum_ol->Add(hE_pion_nungLR_ol,w_nung_LR);
  hE_pion_nungSum_ol->Add(hE_pion_nungRL_ol,w_nung_RL);

  TH1F* hEvis_pfo_nungLR                = static_cast<TH1F*>(fin->Get("hEvis_pfo_nungLR"));
  TH1F* hEvis_pfo_nungRL                = static_cast<TH1F*>(fin->Get("hEvis_pfo_nungRL"));
  TH1F* hEvis_pfo_nungSum               = new TH1F("hEvis_pfo_nungSum",";E [GeV];",750,0,750);
  hEvis_pfo_nungSum->Add(hEvis_pfo_nungLR);
  hEvis_pfo_nungSum->Add(hEvis_pfo_nungRL);
  TH1F* hEvis_pfo_wo_pi_n_nungLR        = static_cast<TH1F*>(fin->Get("hEvis_pfo_wo_pi_n_nungLR"));
  TH1F* hEvis_pfo_wo_pi_n_nungRL        = static_cast<TH1F*>(fin->Get("hEvis_pfo_wo_pi_n_nungRL"));
  TH1F* hEvis_pfo_wo_pi_n_nungSum       = new TH1F("hEvis_pfo_wo_pi_n_nungSum",";E [GeV];",750,0,750);
  hEvis_pfo_wo_pi_n_nungSum->Add(hEvis_pfo_wo_pi_n_nungLR);
  hEvis_pfo_wo_pi_n_nungSum->Add(hEvis_pfo_wo_pi_n_nungRL);
  TH1F* hNBcalClusters_nungLR           = static_cast<TH1F*>(fin->Get("hNBcalClusters_nungLR"));
  TH1F* hNBcalClusters_nungRL           = static_cast<TH1F*>(fin->Get("hNBcalClusters_nungRL"));
  TH1F* hNBcalClusters_nungSum          = new TH1F("hNBcalClusters_nungSum",";# of BCal clusters;",6,0,6);
  hNBcalClusters_nungSum->Add(hNBcalClusters_nungLR,w_nung_LR);
  hNBcalClusters_nungSum->Add(hNBcalClusters_nungRL,w_nung_RL);
  TH1F* hNBcalClusters1ISR_nungLR       = static_cast<TH1F*>(fin->Get("hNBcalClusters1ISR_nungLR"));
  TH1F* hNBcalClusters1ISR_nungRL       = static_cast<TH1F*>(fin->Get("hNBcalClusters1ISR_nungRL"));
  TH1F* hNBcalClusters1ISR_nungSum      = new TH1F("hNBcalClusters1ISR_nungSum",";# of BCal clusters;",6,0,6);
  hNBcalClusters1ISR_nungSum->Add(hNBcalClusters1ISR_nungLR,w_nung_LR);
  hNBcalClusters1ISR_nungSum->Add(hNBcalClusters1ISR_nungRL,w_nung_RL);
  TH1F* hNBcalClustersMultiISR_nungLR   = static_cast<TH1F*>(fin->Get("hNBcalClustersMultiISR_nungLR"));
  TH1F* hNBcalClustersMultiISR_nungRL   = static_cast<TH1F*>(fin->Get("hNBcalClustersMultiISR_nungRL"));
  TH1F* hNBcalClustersMultiISR_nungSum      = new TH1F("hNBcalClustersMultiISR_nungSum",";# of BCal clusters;",6,0,6);
  hNBcalClustersMultiISR_nungSum->Add(hNBcalClustersMultiISR_nungLR,w_nung_LR);
  hNBcalClustersMultiISR_nungSum->Add(hNBcalClustersMultiISR_nungRL,w_nung_RL);
  TH1F* hPt_bcal_bcalcoord_nungLR       = static_cast<TH1F*>(fin->Get("hPt_bcal_bcalcoord_nungLR"));
  TH1F* hPt_bcal_bcalcoord_nungRL       = static_cast<TH1F*>(fin->Get("hPt_bcal_bcalcoord_nungRL"));
  TH1F* hPt_bcal_bcalcoord_nungSum      = new TH1F("hPt_bcal_bcalcoord_nungSum",";Pt [GeV];",100,0,20);
  hPt_bcal_bcalcoord_nungSum->Add(hPt_bcal_bcalcoord_nungLR,w_nung_LR);
  hPt_bcal_bcalcoord_nungSum->Add(hPt_bcal_bcalcoord_nungRL,w_nung_RL);
  TH1F* hPtMax_bcal_bcalcoord_nungLR    = static_cast<TH1F*>(fin->Get("hPtMax_bcal_bcalcoord_nungLR"));
  TH1F* hPtMax_bcal_bcalcoord_nungRL    = static_cast<TH1F*>(fin->Get("hPtMax_bcal_bcalcoord_nungRL"));
  TH1F* hPtMax_bcal_bcalcoord_nungSum      = new TH1F("hPtMax_bcal_bcalcoord_nungSum",";Pt [GeV];",100,0,20);
  hPtMax_bcal_bcalcoord_nungSum->Add(hPtMax_bcal_bcalcoord_nungLR,w_nung_LR);
  hPtMax_bcal_bcalcoord_nungSum->Add(hPtMax_bcal_bcalcoord_nungRL,w_nung_RL);
  TH1F* hPt_bcal_nungLR                 = static_cast<TH1F*>(fin->Get("hPt_bcal_nungLR"));
  TH1F* hPt_bcal_nungRL                 = static_cast<TH1F*>(fin->Get("hPt_bcal_nungRL"));
  TH1F* hPt_bcal_nungSum      = new TH1F("hPt_bcal_nungSum",";Pt [GeV];",100,0,20);
  hPt_bcal_nungSum->Add(hPt_bcal_nungLR,w_nung_LR);
  hPt_bcal_nungSum->Add(hPt_bcal_nungRL,w_nung_RL);
  TH1F* hE_bcal_nungLR                  = static_cast<TH1F*>(fin->Get("hE_bcal_nungLR"));
  TH1F* hE_bcal_nungRL                  = static_cast<TH1F*>(fin->Get("hE_bcal_nungRL"));
  TH1F* hE_bcal_nungSum                 = new TH1F("hE_bcal_nungSum",";E [GeV];",350,0,350);
  hE_bcal_nungSum->Add(hE_bcal_nungLR,w_nung_LR);
  hE_bcal_nungSum->Add(hE_bcal_nungRL,w_nung_RL);
#if 1
  TH1F* hPt_ep_bhabhangLL_isr             = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangLL_isr"));
  TH1F* hPt_ep_bhabhangLR_isr             = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangLR_isr"));
  TH1F* hPt_ep_bhabhangRL_isr             = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangRL_isr"));
  TH1F* hPt_ep_bhabhangRR_isr             = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangRR_isr"));
  TH1F* hPt_ep_bhabhangSum_isr            = new TH1F("hPt_ep_bhabhangSum_isr" ,";Pt [GeV/c];",270,0,270);
  hPt_ep_bhabhangSum_isr->Add(hPt_ep_bhabhangLL_isr,w_bhabhang_LL);
  hPt_ep_bhabhangSum_isr->Add(hPt_ep_bhabhangLR_isr,w_bhabhang_LR);
  hPt_ep_bhabhangSum_isr->Add(hPt_ep_bhabhangRL_isr,w_bhabhang_RL);
  hPt_ep_bhabhangSum_isr->Add(hPt_ep_bhabhangRR_isr,w_bhabhang_RR);
  TH1F* hPt_ep_bhabhangLL_ol              = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangLL_ol"));
  TH1F* hPt_ep_bhabhangLR_ol              = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangLR_ol"));
  TH1F* hPt_ep_bhabhangRL_ol              = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangRL_ol"));
  TH1F* hPt_ep_bhabhangRR_ol              = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangRR_ol"));
  TH1F* hPt_ep_bhabhangSum_ol             = new TH1F("hPt_ep_bhabhangSum_ol" ,";Pt [GeV/c];",270,0,270);
  hPt_ep_bhabhangSum_ol->Add(hPt_ep_bhabhangLL_ol,w_bhabhang_LL);
  hPt_ep_bhabhangSum_ol->Add(hPt_ep_bhabhangLR_ol,w_bhabhang_LR);
  hPt_ep_bhabhangSum_ol->Add(hPt_ep_bhabhangRL_ol,w_bhabhang_RL);
  hPt_ep_bhabhangSum_ol->Add(hPt_ep_bhabhangRR_ol,w_bhabhang_RR);
  TH1F* hPt_ep_bhabhangLL_other           = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangLL_other"));
  TH1F* hPt_ep_bhabhangLR_other           = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangLR_other"));
  TH1F* hPt_ep_bhabhangRL_other           = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangRL_other"));
  TH1F* hPt_ep_bhabhangRR_other           = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhangRR_other"));
  TH1F* hPt_ep_bhabhangSum_other            = new TH1F("hPt_ep_bhabhangSum_other" ,";Pt [GeV/c];",270,0,270);
  hPt_ep_bhabhangSum_other->Add(hPt_ep_bhabhangLL_other,w_bhabhang_LL);
  hPt_ep_bhabhangSum_other->Add(hPt_ep_bhabhangLR_other,w_bhabhang_LR);
  hPt_ep_bhabhangSum_other->Add(hPt_ep_bhabhangRL_other,w_bhabhang_RL);
  hPt_ep_bhabhangSum_other->Add(hPt_ep_bhabhangRR_other,w_bhabhang_RR);

  TH1F* hPt_pfo_bhabhangLL_isr            = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangLL_isr"));
  TH1F* hPt_pfo_bhabhangLR_isr            = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangLR_isr"));
  TH1F* hPt_pfo_bhabhangRL_isr            = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangRL_isr"));
  TH1F* hPt_pfo_bhabhangRR_isr            = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangRR_isr"));
  TH1F* hPt_pfo_bhabhangSum_isr            = new TH1F("hPt_pfo_bhabhangSum_isr" ,";Pt [GeV/c];",270,0,270);
  hPt_pfo_bhabhangSum_isr->Add(hPt_pfo_bhabhangLL_isr,w_bhabhang_LL);
  hPt_pfo_bhabhangSum_isr->Add(hPt_pfo_bhabhangLR_isr,w_bhabhang_LR);
  hPt_pfo_bhabhangSum_isr->Add(hPt_pfo_bhabhangRL_isr,w_bhabhang_RL);
  hPt_pfo_bhabhangSum_isr->Add(hPt_pfo_bhabhangRR_isr,w_bhabhang_RR);

  TH1F* hPt_pfo_bhabhangLL_ol             = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangLL_ol"));
  TH1F* hPt_pfo_bhabhangLR_ol             = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangLR_ol"));
  TH1F* hPt_pfo_bhabhangRL_ol             = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangRL_ol"));
  TH1F* hPt_pfo_bhabhangRR_ol             = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangRR_ol"));
  TH1F* hPt_pfo_bhabhangSum_ol            = new TH1F("hPt_pfo_bhabhangSum_ol" ,";Pt [GeV/c];",270,0,270);
  hPt_pfo_bhabhangSum_ol->Add(hPt_pfo_bhabhangLL_ol,w_bhabhang_LL);
  hPt_pfo_bhabhangSum_ol->Add(hPt_pfo_bhabhangLR_ol,w_bhabhang_LR);
  hPt_pfo_bhabhangSum_ol->Add(hPt_pfo_bhabhangRL_ol,w_bhabhang_RL);
  hPt_pfo_bhabhangSum_ol->Add(hPt_pfo_bhabhangRR_ol,w_bhabhang_RR);

  TH1F* hPt_pfo_bhabhangLL_other          = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangLL_other"));
  TH1F* hPt_pfo_bhabhangLR_other          = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangLR_other"));
  TH1F* hPt_pfo_bhabhangRL_other          = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangRL_other"));
  TH1F* hPt_pfo_bhabhangRR_other          = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhangRR_other"));
  TH1F* hPt_pfo_bhabhangSum_other            = new TH1F("hPt_pfo_bhabhangSum_other" ,";Pt [GeV/c];",270,0,270);
  hPt_pfo_bhabhangSum_other->Add(hPt_pfo_bhabhangLL_other,w_bhabhang_LL);
  hPt_pfo_bhabhangSum_other->Add(hPt_pfo_bhabhangLR_other,w_bhabhang_LR);
  hPt_pfo_bhabhangSum_other->Add(hPt_pfo_bhabhangRL_other,w_bhabhang_RL);
  hPt_pfo_bhabhangSum_other->Add(hPt_pfo_bhabhangRR_other,w_bhabhang_RR);

  TH1F* hE_photon_bhabhangLL_rest         = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangLL_rest"));
  TH1F* hE_photon_bhabhangLR_rest         = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangLR_rest"));
  TH1F* hE_photon_bhabhangRL_rest         = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangRL_rest"));
  TH1F* hE_photon_bhabhangRR_rest         = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangRR_rest"));
  TH1F* hE_photon_bhabhangSum_rest        = new TH1F("hE_photon_bhabhangSum_rest" ,";E [GeV];",350,0,350);
  hE_photon_bhabhangSum_rest->Add(hE_photon_bhabhangLL_rest,w_bhabhang_LL);
  hE_photon_bhabhangSum_rest->Add(hE_photon_bhabhangLR_rest,w_bhabhang_LR);
  hE_photon_bhabhangSum_rest->Add(hE_photon_bhabhangRL_rest,w_bhabhang_RL);
  hE_photon_bhabhangSum_rest->Add(hE_photon_bhabhangRR_rest,w_bhabhang_RR);

  TH1F* hE_photon_bhabhangLL_ol           = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangLL_ol"));
  TH1F* hE_photon_bhabhangLR_ol           = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangLR_ol"));
  TH1F* hE_photon_bhabhangRL_ol           = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangRL_ol"));
  TH1F* hE_photon_bhabhangRR_ol           = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangRR_ol"));
  TH1F* hE_photon_bhabhangSum_ol          = new TH1F("hE_photon_bhabhangSum_ol" ,";E [GeV];",350,0,350);
  hE_photon_bhabhangSum_ol->Add(hE_photon_bhabhangLL_ol,w_bhabhang_LL);
  hE_photon_bhabhangSum_ol->Add(hE_photon_bhabhangLR_ol,w_bhabhang_LR);
  hE_photon_bhabhangSum_ol->Add(hE_photon_bhabhangRL_ol,w_bhabhang_RL);
  hE_photon_bhabhangSum_ol->Add(hE_photon_bhabhangRR_ol,w_bhabhang_RR);

  TH1F* hE_photon_bhabhangLL_electron     = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangLL_electron"));
  TH1F* hE_photon_bhabhangLR_electron     = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangLR_electron"));
  TH1F* hE_photon_bhabhangRL_electron     = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangRL_electron"));
  TH1F* hE_photon_bhabhangRR_electron     = static_cast<TH1F*>(fin->Get("hE_photon_bhabhangRR_electron"));
  TH1F* hE_photon_bhabhangSum_electron    = new TH1F("hE_photon_bhabhangSum_electron" ,";E [GeV];",350,0,350);
  hE_photon_bhabhangSum_electron->Add(hE_photon_bhabhangLL_electron,w_bhabhang_LL);
  hE_photon_bhabhangSum_electron->Add(hE_photon_bhabhangLR_electron,w_bhabhang_LR);
  hE_photon_bhabhangSum_electron->Add(hE_photon_bhabhangRL_electron,w_bhabhang_RL);
  hE_photon_bhabhangSum_electron->Add(hE_photon_bhabhangRR_electron,w_bhabhang_RR);

  TH1F* hE_V0_bhabhangLL_rest             = static_cast<TH1F*>(fin->Get("hE_V0_bhabhangLL_rest"));
  TH1F* hE_V0_bhabhangLR_rest             = static_cast<TH1F*>(fin->Get("hE_V0_bhabhangLR_rest"));
  TH1F* hE_V0_bhabhangRL_rest             = static_cast<TH1F*>(fin->Get("hE_V0_bhabhangRL_rest"));
  TH1F* hE_V0_bhabhangRR_rest             = static_cast<TH1F*>(fin->Get("hE_V0_bhabhangRR_rest"));
  TH1F* hE_V0_bhabhangSum_rest            = new TH1F("hE_V0_bhabhangSum_rest" ,";E [GeV];",350,0,350);
  hE_V0_bhabhangSum_rest->Add(hE_V0_bhabhangLL_rest,w_bhabhang_LL);
  hE_V0_bhabhangSum_rest->Add(hE_V0_bhabhangLR_rest,w_bhabhang_LR);
  hE_V0_bhabhangSum_rest->Add(hE_V0_bhabhangRL_rest,w_bhabhang_RL);
  hE_V0_bhabhangSum_rest->Add(hE_V0_bhabhangRR_rest,w_bhabhang_RR);

  TH1F* hE_V0_bhabhangLL_ol               = static_cast<TH1F*>(fin->Get("hE_V0_bhabhangLL_ol"));
  TH1F* hE_V0_bhabhangLR_ol               = static_cast<TH1F*>(fin->Get("hE_V0_bhabhangLR_ol"));
  TH1F* hE_V0_bhabhangRL_ol               = static_cast<TH1F*>(fin->Get("hE_V0_bhabhangRL_ol"));
  TH1F* hE_V0_bhabhangRR_ol               = static_cast<TH1F*>(fin->Get("hE_V0_bhabhangRR_ol"));
  TH1F* hE_V0_bhabhangSum_ol              = new TH1F("hE_V0_bhabhangSum_ol" ,";E [GeV];",350,0,350);
  hE_V0_bhabhangSum_ol->Add(hE_V0_bhabhangLL_ol,w_bhabhang_LL);
  hE_V0_bhabhangSum_ol->Add(hE_V0_bhabhangLR_ol,w_bhabhang_LR);
  hE_V0_bhabhangSum_ol->Add(hE_V0_bhabhangRL_ol,w_bhabhang_RL);
  hE_V0_bhabhangSum_ol->Add(hE_V0_bhabhangRR_ol,w_bhabhang_RR);

  TH1F* hE_neutron_bhabhangLL_rest             = static_cast<TH1F*>(fin->Get("hE_neutron_bhabhangLL_rest"));
  TH1F* hE_neutron_bhabhangLR_rest             = static_cast<TH1F*>(fin->Get("hE_neutron_bhabhangLR_rest"));
  TH1F* hE_neutron_bhabhangRL_rest             = static_cast<TH1F*>(fin->Get("hE_neutron_bhabhangRL_rest"));
  TH1F* hE_neutron_bhabhangRR_rest             = static_cast<TH1F*>(fin->Get("hE_neutron_bhabhangRR_rest"));
  TH1F* hE_neutron_bhabhangSum_rest            = new TH1F("hE_neutron_bhabhangSum_rest" ,";E [GeV];",350,0,350);
  hE_neutron_bhabhangSum_rest->Add(hE_neutron_bhabhangLL_rest,w_bhabhang_LL);
  hE_neutron_bhabhangSum_rest->Add(hE_neutron_bhabhangLR_rest,w_bhabhang_LR);
  hE_neutron_bhabhangSum_rest->Add(hE_neutron_bhabhangRL_rest,w_bhabhang_RL);
  hE_neutron_bhabhangSum_rest->Add(hE_neutron_bhabhangRR_rest,w_bhabhang_RR);

  TH1F* hE_neutron_bhabhangLL_ol               = static_cast<TH1F*>(fin->Get("hE_neutron_bhabhangLL_ol"));
  TH1F* hE_neutron_bhabhangLR_ol               = static_cast<TH1F*>(fin->Get("hE_neutron_bhabhangLR_ol"));
  TH1F* hE_neutron_bhabhangRL_ol               = static_cast<TH1F*>(fin->Get("hE_neutron_bhabhangRL_ol"));
  TH1F* hE_neutron_bhabhangRR_ol               = static_cast<TH1F*>(fin->Get("hE_neutron_bhabhangRR_ol"));
  TH1F* hE_neutron_bhabhangSum_ol              = new TH1F("hE_neutron_bhabhangSum_ol" ,";E [GeV];",350,0,350);
  hE_neutron_bhabhangSum_ol->Add(hE_neutron_bhabhangLL_ol,w_bhabhang_LL);
  hE_neutron_bhabhangSum_ol->Add(hE_neutron_bhabhangLR_ol,w_bhabhang_LR);
  hE_neutron_bhabhangSum_ol->Add(hE_neutron_bhabhangRL_ol,w_bhabhang_RL);
  hE_neutron_bhabhangSum_ol->Add(hE_neutron_bhabhangRR_ol,w_bhabhang_RR);

  TH1F* hE_electron_bhabhangLL_rest             = static_cast<TH1F*>(fin->Get("hE_electron_bhabhangLL_rest"));
  TH1F* hE_electron_bhabhangLR_rest             = static_cast<TH1F*>(fin->Get("hE_electron_bhabhangLR_rest"));
  TH1F* hE_electron_bhabhangRL_rest             = static_cast<TH1F*>(fin->Get("hE_electron_bhabhangRL_rest"));
  TH1F* hE_electron_bhabhangRR_rest             = static_cast<TH1F*>(fin->Get("hE_electron_bhabhangRR_rest"));
  TH1F* hE_electron_bhabhangSum_rest            = new TH1F("hE_electron_bhabhangSum_rest" ,";E [GeV];",350,0,350);
  hE_electron_bhabhangSum_rest->Add(hE_electron_bhabhangLL_rest,w_bhabhang_LL);
  hE_electron_bhabhangSum_rest->Add(hE_electron_bhabhangLR_rest,w_bhabhang_LR);
  hE_electron_bhabhangSum_rest->Add(hE_electron_bhabhangRL_rest,w_bhabhang_RL);
  hE_electron_bhabhangSum_rest->Add(hE_electron_bhabhangRR_rest,w_bhabhang_RR);

  TH1F* hE_electron_bhabhangLL_ol               = static_cast<TH1F*>(fin->Get("hE_electron_bhabhangLL_ol"));
  TH1F* hE_electron_bhabhangLR_ol               = static_cast<TH1F*>(fin->Get("hE_electron_bhabhangLR_ol"));
  TH1F* hE_electron_bhabhangRL_ol               = static_cast<TH1F*>(fin->Get("hE_electron_bhabhangRL_ol"));
  TH1F* hE_electron_bhabhangRR_ol               = static_cast<TH1F*>(fin->Get("hE_electron_bhabhangRR_ol"));
  TH1F* hE_electron_bhabhangSum_ol              = new TH1F("hE_electron_bhabhangSum_ol" ,";E [GeV];",350,0,350);
  hE_electron_bhabhangSum_ol->Add(hE_electron_bhabhangLL_ol,w_bhabhang_LL);
  hE_electron_bhabhangSum_ol->Add(hE_electron_bhabhangLR_ol,w_bhabhang_LR);
  hE_electron_bhabhangSum_ol->Add(hE_electron_bhabhangRL_ol,w_bhabhang_RL);
  hE_electron_bhabhangSum_ol->Add(hE_electron_bhabhangRR_ol,w_bhabhang_RR);

  TH1F* hE_muon_bhabhangLL_rest             = static_cast<TH1F*>(fin->Get("hE_muon_bhabhangLL_rest"));
  TH1F* hE_muon_bhabhangLR_rest             = static_cast<TH1F*>(fin->Get("hE_muon_bhabhangLR_rest"));
  TH1F* hE_muon_bhabhangRL_rest             = static_cast<TH1F*>(fin->Get("hE_muon_bhabhangRL_rest"));
  TH1F* hE_muon_bhabhangRR_rest             = static_cast<TH1F*>(fin->Get("hE_muon_bhabhangRR_rest"));
  TH1F* hE_muon_bhabhangSum_rest            = new TH1F("hE_muon_bhabhangSum_rest" ,";E [GeV];",350,0,350);
  hE_muon_bhabhangSum_rest->Add(hE_muon_bhabhangLL_rest,w_bhabhang_LL);
  hE_muon_bhabhangSum_rest->Add(hE_muon_bhabhangLR_rest,w_bhabhang_LR);
  hE_muon_bhabhangSum_rest->Add(hE_muon_bhabhangRL_rest,w_bhabhang_RL);
  hE_muon_bhabhangSum_rest->Add(hE_muon_bhabhangRR_rest,w_bhabhang_RR);

  TH1F* hE_muon_bhabhangLL_ol               = static_cast<TH1F*>(fin->Get("hE_muon_bhabhangLL_ol"));
  TH1F* hE_muon_bhabhangLR_ol               = static_cast<TH1F*>(fin->Get("hE_muon_bhabhangLR_ol"));
  TH1F* hE_muon_bhabhangRL_ol               = static_cast<TH1F*>(fin->Get("hE_muon_bhabhangRL_ol"));
  TH1F* hE_muon_bhabhangRR_ol               = static_cast<TH1F*>(fin->Get("hE_muon_bhabhangRR_ol"));
  TH1F* hE_muon_bhabhangSum_ol              = new TH1F("hE_muon_bhabhangSum_ol" ,";E [GeV];",350,0,350);
  hE_muon_bhabhangSum_ol->Add(hE_muon_bhabhangLL_ol,w_bhabhang_LL);
  hE_muon_bhabhangSum_ol->Add(hE_muon_bhabhangLR_ol,w_bhabhang_LR);
  hE_muon_bhabhangSum_ol->Add(hE_muon_bhabhangRL_ol,w_bhabhang_RL);
  hE_muon_bhabhangSum_ol->Add(hE_muon_bhabhangRR_ol,w_bhabhang_RR);


  TH1F* hE_pion_bhabhangLL_rest             = static_cast<TH1F*>(fin->Get("hE_pion_bhabhangLL_rest"));
  TH1F* hE_pion_bhabhangLR_rest             = static_cast<TH1F*>(fin->Get("hE_pion_bhabhangLR_rest"));
  TH1F* hE_pion_bhabhangRL_rest             = static_cast<TH1F*>(fin->Get("hE_pion_bhabhangRL_rest"));
  TH1F* hE_pion_bhabhangRR_rest             = static_cast<TH1F*>(fin->Get("hE_pion_bhabhangRR_rest"));
  TH1F* hE_pion_bhabhangSum_rest            = new TH1F("hE_pion_bhabhangSum_rest" ,";E [GeV];",350,0,350);
  hE_pion_bhabhangSum_rest->Add(hE_pion_bhabhangLL_rest,w_bhabhang_LL);
  hE_pion_bhabhangSum_rest->Add(hE_pion_bhabhangLR_rest,w_bhabhang_LR);
  hE_pion_bhabhangSum_rest->Add(hE_pion_bhabhangRL_rest,w_bhabhang_RL);
  hE_pion_bhabhangSum_rest->Add(hE_pion_bhabhangRR_rest,w_bhabhang_RR);

  TH1F* hE_pion_bhabhangLL_ol               = static_cast<TH1F*>(fin->Get("hE_pion_bhabhangLL_ol"));
  TH1F* hE_pion_bhabhangLR_ol               = static_cast<TH1F*>(fin->Get("hE_pion_bhabhangLR_ol"));
  TH1F* hE_pion_bhabhangRL_ol               = static_cast<TH1F*>(fin->Get("hE_pion_bhabhangRL_ol"));
  TH1F* hE_pion_bhabhangRR_ol               = static_cast<TH1F*>(fin->Get("hE_pion_bhabhangRR_ol"));
  TH1F* hE_pion_bhabhangSum_ol              = new TH1F("hE_pion_bhabhangSum_ol" ,";E [GeV];",350,0,350);
  hE_pion_bhabhangSum_ol->Add(hE_pion_bhabhangLL_ol,w_bhabhang_LL);
  hE_pion_bhabhangSum_ol->Add(hE_pion_bhabhangLR_ol,w_bhabhang_LR);
  hE_pion_bhabhangSum_ol->Add(hE_pion_bhabhangRL_ol,w_bhabhang_RL);
  hE_pion_bhabhangSum_ol->Add(hE_pion_bhabhangRR_ol,w_bhabhang_RR);


  TH1F* hEvis_pfo_bhabhangLL                = static_cast<TH1F*>(fin->Get("hEvis_pfo_bhabhangLL"));
  TH1F* hEvis_pfo_bhabhangLR                = static_cast<TH1F*>(fin->Get("hEvis_pfo_bhabhangLR"));
  TH1F* hEvis_pfo_bhabhangRL                = static_cast<TH1F*>(fin->Get("hEvis_pfo_bhabhangRL"));
  TH1F* hEvis_pfo_bhabhangRR                = static_cast<TH1F*>(fin->Get("hEvis_pfo_bhabhangRR"));
  TH1F* hEvis_pfo_bhabhangSum               = new TH1F("hEvis_pfo_bhabhangSum",";E [GeV];",750,0,750);
  hEvis_pfo_bhabhangSum->Add(hEvis_pfo_bhabhangLL);
  hEvis_pfo_bhabhangSum->Add(hEvis_pfo_bhabhangLR);
  hEvis_pfo_bhabhangSum->Add(hEvis_pfo_bhabhangRL);
  hEvis_pfo_bhabhangSum->Add(hEvis_pfo_bhabhangRR);
  TH1F* hEvis_pfo_wo_pi_n_bhabhangLL        = static_cast<TH1F*>(fin->Get("hEvis_pfo_wo_pi_n_bhabhangLL"));
  TH1F* hEvis_pfo_wo_pi_n_bhabhangLR        = static_cast<TH1F*>(fin->Get("hEvis_pfo_wo_pi_n_bhabhangLR"));
  TH1F* hEvis_pfo_wo_pi_n_bhabhangRL        = static_cast<TH1F*>(fin->Get("hEvis_pfo_wo_pi_n_bhabhangRL"));
  TH1F* hEvis_pfo_wo_pi_n_bhabhangRR        = static_cast<TH1F*>(fin->Get("hEvis_pfo_wo_pi_n_bhabhangRR"));
  TH1F* hEvis_pfo_wo_pi_n_bhabhangSum       = new TH1F("hEvis_pfo_wo_pi_n_bhabhangSum",";E [GeV];",750,0,750);
  hEvis_pfo_wo_pi_n_bhabhangSum->Add(hEvis_pfo_wo_pi_n_bhabhangLL);
  hEvis_pfo_wo_pi_n_bhabhangSum->Add(hEvis_pfo_wo_pi_n_bhabhangLR);
  hEvis_pfo_wo_pi_n_bhabhangSum->Add(hEvis_pfo_wo_pi_n_bhabhangRL);
  hEvis_pfo_wo_pi_n_bhabhangSum->Add(hEvis_pfo_wo_pi_n_bhabhangRR);

  TH1F* hNBcalClusters_bhabhangLL         = static_cast<TH1F*>(fin->Get("hNBcalClusters_bhabhangLL"));
  TH1F* hNBcalClusters_bhabhangLR         = static_cast<TH1F*>(fin->Get("hNBcalClusters_bhabhangLR"));
  TH1F* hNBcalClusters_bhabhangRL         = static_cast<TH1F*>(fin->Get("hNBcalClusters_bhabhangRL"));
  TH1F* hNBcalClusters_bhabhangRR         = static_cast<TH1F*>(fin->Get("hNBcalClusters_bhabhangRR"));
  TH1F* hNBcalClusters_bhabhangSum        = new TH1F("hNBcalClusters_bhabhangSum",";# of BCal clusters;",6,0,6);
  hNBcalClusters_bhabhangSum->Add(hNBcalClusters_bhabhangLL,w_bhabhang_LL); 
  hNBcalClusters_bhabhangSum->Add(hNBcalClusters_bhabhangLR,w_bhabhang_LR); 
  hNBcalClusters_bhabhangSum->Add(hNBcalClusters_bhabhangRL,w_bhabhang_RL); 
  hNBcalClusters_bhabhangSum->Add(hNBcalClusters_bhabhangRR,w_bhabhang_RR); 

  TH1F* hPt_bcal_bcalcoord_bhabhangLL     = static_cast<TH1F*>(fin->Get("hPt_bcal_bcalcoord_bhabhangLL"));
  TH1F* hPt_bcal_bcalcoord_bhabhangLR     = static_cast<TH1F*>(fin->Get("hPt_bcal_bcalcoord_bhabhangLR"));
  TH1F* hPt_bcal_bcalcoord_bhabhangRL     = static_cast<TH1F*>(fin->Get("hPt_bcal_bcalcoord_bhabhangRL"));
  TH1F* hPt_bcal_bcalcoord_bhabhangRR     = static_cast<TH1F*>(fin->Get("hPt_bcal_bcalcoord_bhabhangRR"));
  TH1F* hPt_bcal_bcalcoord_bhabhangSum    = new TH1F("hPt_bcal_bcalcoord_bhabhangSum",";Pt [GeV];",100,0,20);
  hPt_bcal_bcalcoord_bhabhangSum->Add(hPt_bcal_bcalcoord_bhabhangLL,w_bhabhang_LL);
  hPt_bcal_bcalcoord_bhabhangSum->Add(hPt_bcal_bcalcoord_bhabhangLR,w_bhabhang_LR);
  hPt_bcal_bcalcoord_bhabhangSum->Add(hPt_bcal_bcalcoord_bhabhangRL,w_bhabhang_RL);
  hPt_bcal_bcalcoord_bhabhangSum->Add(hPt_bcal_bcalcoord_bhabhangRR,w_bhabhang_RR);

  TH1F* hPtMax_bcal_bcalcoord_bhabhangLL  = static_cast<TH1F*>(fin->Get("hPtMax_bcal_bcalcoord_bhabhangLL"));
  TH1F* hPtMax_bcal_bcalcoord_bhabhangLR  = static_cast<TH1F*>(fin->Get("hPtMax_bcal_bcalcoord_bhabhangLR"));
  TH1F* hPtMax_bcal_bcalcoord_bhabhangRL  = static_cast<TH1F*>(fin->Get("hPtMax_bcal_bcalcoord_bhabhangRL"));
  TH1F* hPtMax_bcal_bcalcoord_bhabhangRR  = static_cast<TH1F*>(fin->Get("hPtMax_bcal_bcalcoord_bhabhangRR"));
  TH1F* hPtMax_bcal_bcalcoord_bhabhangSum = new TH1F("hPtMax_bcal_bcalcoord_bhabhangSum",";Pt [GeV];",100,0,20);
  hPtMax_bcal_bcalcoord_bhabhangSum->Add(hPtMax_bcal_bcalcoord_bhabhangLL,w_bhabhang_LL);
  hPtMax_bcal_bcalcoord_bhabhangSum->Add(hPtMax_bcal_bcalcoord_bhabhangLR,w_bhabhang_LR);
  hPtMax_bcal_bcalcoord_bhabhangSum->Add(hPtMax_bcal_bcalcoord_bhabhangRL,w_bhabhang_RL);
  hPtMax_bcal_bcalcoord_bhabhangSum->Add(hPtMax_bcal_bcalcoord_bhabhangRR,w_bhabhang_RR);

  TH1F* hPt_bcal_bhabhangLL               = static_cast<TH1F*>(fin->Get("hPt_bcal_bhabhangLL"));
  TH1F* hPt_bcal_bhabhangLR               = static_cast<TH1F*>(fin->Get("hPt_bcal_bhabhangLR"));
  TH1F* hPt_bcal_bhabhangRL               = static_cast<TH1F*>(fin->Get("hPt_bcal_bhabhangRL"));
  TH1F* hPt_bcal_bhabhangRR               = static_cast<TH1F*>(fin->Get("hPt_bcal_bhabhangRR"));
  TH1F* hPt_bcal_bhabhangSum              = new TH1F("hPt_bcal_bhabhangSum",";Pt [GeV];",100,0,20);
  hPt_bcal_bhabhangSum->Add(hPt_bcal_bhabhangLL,w_bhabhang_LL);
  hPt_bcal_bhabhangSum->Add(hPt_bcal_bhabhangLR,w_bhabhang_LR);
  hPt_bcal_bhabhangSum->Add(hPt_bcal_bhabhangRL,w_bhabhang_RL);
  hPt_bcal_bhabhangSum->Add(hPt_bcal_bhabhangRR,w_bhabhang_RR);

  TH1F* hE_bcal_bhabhangLL                = static_cast<TH1F*>(fin->Get("hE_bcal_bhabhangLL"));
  TH1F* hE_bcal_bhabhangLR                = static_cast<TH1F*>(fin->Get("hE_bcal_bhabhangLR"));
  TH1F* hE_bcal_bhabhangRL                = static_cast<TH1F*>(fin->Get("hE_bcal_bhabhangRL"));
  TH1F* hE_bcal_bhabhangRR                = static_cast<TH1F*>(fin->Get("hE_bcal_bhabhangRR"));
  TH1F* hE_bcal_bhabhangSum               = new TH1F("hE_bcal_bhabhangSum",";E [GeV];",350,0,350);
  hE_bcal_bhabhangSum->Add(hE_bcal_bhabhangLL,w_bhabhang_LL);
  hE_bcal_bhabhangSum->Add(hE_bcal_bhabhangLR,w_bhabhang_LR);
  hE_bcal_bhabhangSum->Add(hE_bcal_bhabhangRL,w_bhabhang_RL);
  hE_bcal_bhabhangSum->Add(hE_bcal_bhabhangRR,w_bhabhang_RR);

  hPt_ep_nungSum_isr->SetFillColor(kAzure+6);
  hPt_ep_nungSum_ol->SetFillColor(kYellow+1);
  hPt_ep_nungSum_other->SetFillColor(kGreen+3);
  hPt_pfo_nungSum_isr->SetFillColor(kAzure+6);
  hPt_pfo_nungSum_ol->SetFillColor(kYellow+1);
  hPt_pfo_nungSum_other->SetFillColor(kGreen+3);
  hE_photon_nungSum_rest->SetFillColor(kGreen+3);
  hE_photon_nungSum_ol->SetFillColor(kYellow+1);
  hE_V0_nungSum_rest->SetFillColor(kGreen+3);
  hE_V0_nungSum_ol->SetFillColor(kYellow+1);
  hE_neutron_nungSum_rest->SetFillColor(kGreen+3);
  hE_neutron_nungSum_ol->SetFillColor(kYellow+1);
  hE_electron_nungSum_rest->SetFillColor(kGreen+3);
  hE_electron_nungSum_ol->SetFillColor(kYellow+1);
  hE_muon_nungSum_rest->SetFillColor(kGreen+3);
  hE_muon_nungSum_ol->SetFillColor(kYellow+1);
  hE_pion_nungSum_rest->SetFillColor(kGreen+3);
  hE_pion_nungSum_ol->SetFillColor(kYellow+1);
  hEvis_pfo_nungSum->SetFillColor(kGreen+3);
  hEvis_pfo_wo_pi_n_nungSum->SetFillColor(kGreen+3);
  hNBcalClusters1ISR_nungSum->SetFillColor(kYellow+1);
  hNBcalClustersMultiISR_nungSum->SetFillColor(kGreen+3);
  hPt_bcal_bcalcoord_nungSum->SetFillColor(kGreen+3); 
  hPtMax_bcal_bcalcoord_nungSum->SetFillColor(kGreen+3); 
  hPt_bcal_nungSum->SetFillColor(kGreen+3); 
  hE_bcal_nungSum->SetFillColor(kGreen+3); 

  hPt_ep_bhabhangSum_isr->SetFillColor(kOrange+4);
  hPt_ep_bhabhangSum_ol->SetFillColor(kMagenta+1);
  hPt_ep_bhabhangSum_other->SetFillColor(kOrange+6);
  hPt_pfo_bhabhangSum_isr->SetFillColor(kOrange+4);
  hPt_pfo_bhabhangSum_ol->SetFillColor(kMagenta+1);
  hPt_pfo_bhabhangSum_other->SetFillColor(kOrange+6);
  hE_photon_bhabhangSum_rest->SetFillColor(kOrange+6);
  hE_photon_bhabhangSum_electron->SetFillColor(kOrange+4);
  hE_photon_bhabhangSum_ol->SetFillColor(kMagenta+1);
  hE_V0_bhabhangSum_rest->SetFillColor(kOrange+6);
  hE_V0_bhabhangSum_ol->SetFillColor(kMagenta+1);
  hE_neutron_bhabhangSum_rest->SetFillColor(kOrange+6);
  hE_neutron_bhabhangSum_ol->SetFillColor(kMagenta+1);
  hE_electron_bhabhangSum_rest->SetFillColor(kOrange+6);
  hE_electron_bhabhangSum_ol->SetFillColor(kMagenta+1);
  hE_muon_bhabhangSum_rest->SetFillColor(kOrange+6);
  hE_muon_bhabhangSum_ol->SetFillColor(kMagenta+1);
  hE_pion_bhabhangSum_rest->SetFillColor(kOrange+6);
  hE_pion_bhabhangSum_ol->SetFillColor(kMagenta+1);
  hEvis_pfo_bhabhangSum->SetFillColor(kOrange+6);
  hEvis_pfo_wo_pi_n_bhabhangSum->SetFillColor(kOrange+6);
  hNBcalClusters_bhabhangSum->SetFillColor(kOrange+6);
  hPt_bcal_bcalcoord_bhabhangSum->SetFillColor(kOrange+6); 
  hPtMax_bcal_bcalcoord_bhabhangSum->SetFillColor(kOrange+6); 
  hPt_bcal_bhabhangSum->SetFillColor(kOrange+6); 
  hE_bcal_bhabhangSum->SetFillColor(kOrange+6); 

  TCanvas* c1 = new TCanvas("c1","",600,400);
  gPad->SetLogy();
  THStack* hPt_e_all = new THStack("hPt_e_all",";P_{T} [GeV];");
  hPt_e_all->SetMaximum(1e10);
  hPt_e_all->SetMinimum(1);
  hPt_e_all->Add(hPt_ep_nungSum_other);
  hPt_e_all->Add(hPt_ep_nungSum_ol);
  hPt_e_all->Add(hPt_ep_nungSum_isr);
  hPt_e_all->Add(hPt_ep_bhabhangSum_ol);
  hPt_e_all->Add(hPt_ep_bhabhangSum_isr);
  hPt_e_all->Add(hPt_ep_bhabhangSum_other);
  hPt_e_all->Draw();
  TLegend* leg_c1_head = new TLegend(0.25,0.85,0.9,0.9);
  leg_c1_head->SetTextSize(0.05);
  leg_c1_head->SetTextFont(42);
  leg_c1_head->SetHeader("Transverse momenta of electrons");
  leg_c1_head->SetFillStyle(0);
  leg_c1_head->Draw();
  TLegend* leg_c1 = new TLegend(0.25,0.55,0.45,0.85);
  leg_c1->SetTextSize(0.05);
  leg_c1->SetTextFont(42);
  leg_c1->AddEntry(hPt_ep_nungSum_isr,  "#nu#nu+N#gamma: photons","f");
  leg_c1->AddEntry(hPt_ep_nungSum_ol,   "#nu#nu+N#gamma: overlay","f");
  leg_c1->AddEntry(hPt_ep_nungSum_other,"#nu#nu+N#gamma: other"  ,"f");
  leg_c1->Draw();
  TLegend* leg_c1_2 = new TLegend(0.65,0.55,0.85,0.85);
  leg_c1_2->SetTextSize(0.05);
  leg_c1_2->SetTextFont(42);
  leg_c1_2->AddEntry(hPt_ep_bhabhangSum_other,"e^{+}e^{-}+N#gamma: other"  ,"f");
  leg_c1_2->AddEntry(hPt_ep_bhabhangSum_isr,  "e^{+}e^{-}+N#gamma: photons","f");
  leg_c1_2->AddEntry(hPt_ep_bhabhangSum_ol,   "e^{+}e^{-}+N#gamma: overlay","f");
  leg_c1_2->Draw();

  TCanvas* c2 = new TCanvas("c2","",600,400);
  gPad->SetLogy();
  THStack* hPt_pfo_all = new THStack("hPt_pfo_all",";P_{T} [GeV];");
  hPt_pfo_all->SetMaximum(1e10);
  hPt_pfo_all->SetMinimum(1);
  hPt_pfo_all->Add(hPt_pfo_nungSum_other);
  hPt_pfo_all->Add(hPt_pfo_nungSum_ol);
  hPt_pfo_all->Add(hPt_pfo_nungSum_isr);
  hPt_pfo_all->Add(hPt_pfo_bhabhangSum_ol);
  hPt_pfo_all->Add(hPt_pfo_bhabhangSum_isr);
  hPt_pfo_all->Add(hPt_pfo_bhabhangSum_other);
  hPt_pfo_all->Draw();
  TLegend* leg_c2_head = new TLegend(0.25,0.85,0.9,0.9);
  leg_c2_head->SetTextSize(0.05);
  leg_c2_head->SetTextFont(42);
  leg_c2_head->SetHeader("Transverse momenta of charged PFOs");
  leg_c2_head->SetFillStyle(0);
  leg_c2_head->Draw();
  TLegend* leg_c2 = new TLegend(0.25,0.55,0.45,0.85);
  leg_c2->SetTextSize(0.05);
  leg_c2->SetTextFont(42);
  leg_c2->AddEntry(hPt_pfo_nungSum_isr,  "#nu#nu+N#gamma: photons","f");
  leg_c2->AddEntry(hPt_pfo_nungSum_ol,   "#nu#nu+N#gamma: overlay","f");
  leg_c2->AddEntry(hPt_pfo_nungSum_other,"#nu#nu+N#gamma: other"  ,"f");
  leg_c2->Draw();
  TLegend* leg_c2_2 = new TLegend(0.65,0.55,0.85,0.85);
  leg_c2_2->SetTextSize(0.05);
  leg_c2_2->SetTextFont(42);
  leg_c2_2->AddEntry(hPt_pfo_bhabhangSum_other,"e^{+}e^{-}+N#gamma: other"  ,"f");
  leg_c2_2->AddEntry(hPt_pfo_bhabhangSum_isr,  "e^{+}e^{-}+N#gamma: photons","f");
  leg_c2_2->AddEntry(hPt_pfo_bhabhangSum_ol,   "e^{+}e^{-}+N#gamma: overlay","f");
  leg_c2_2->Draw();

  TCanvas* c3 = new TCanvas("c3","",600,400); gPad->SetLogy();
  THStack* hE_photon_all = new THStack("hE_photon_all",";E [GeV];");
  hE_photon_all->SetMaximum(1e8);
  hE_photon_all->SetMinimum(1);
  hE_photon_all->Add(hE_photon_nungSum_ol);
  hE_photon_all->Add(hE_photon_nungSum_rest);
  hE_photon_all->Add(hE_photon_bhabhangSum_ol);
  hE_photon_all->Add(hE_photon_bhabhangSum_electron);
  hE_photon_all->Add(hE_photon_bhabhangSum_rest);
  hE_photon_all->Draw();
  TLegend* leg_c3_head = new TLegend(0.25,0.85,0.9,0.9);
  leg_c3_head->SetTextSize(0.05);
  leg_c3_head->SetTextFont(42);
  leg_c3_head->SetHeader("Reconstructed photons (non-ISR)");
  leg_c3_head->SetFillStyle(0);
  leg_c3_head->Draw();
  TLegend* leg_c3 = new TLegend(0.25,0.65,0.45,0.85);
  leg_c3->SetTextSize(0.05);
  leg_c3->SetTextFont(42);
  leg_c3->AddEntry(hE_photon_nungSum_rest, "#nu#nu+N#gamma: rest"  ,"f");
  leg_c3->AddEntry(hE_photon_nungSum_ol,   "#nu#nu+N#gamma: overlay","f");
  leg_c3->Draw();
  TLegend* leg_c3_2 = new TLegend(0.65,0.55,0.85,0.85);
  leg_c3_2->SetTextSize(0.05);
  leg_c3_2->SetTextFont(42);
  leg_c3_2->AddEntry(hE_photon_bhabhangSum_rest,     "e^{+}e^{-}+N#gamma: rest"  ,"f");
  leg_c3_2->AddEntry(hE_photon_bhabhangSum_electron, "e^{+}e^{-}+N#gamma: electron","f");
  leg_c3_2->AddEntry(hE_photon_bhabhangSum_ol,       "e^{+}e^{-}+N#gamma: overlay","f");
  leg_c3_2->Draw();

  TCanvas* c4 = new TCanvas("c4","",600,400);
  gPad->SetLogy();
  THStack* hE_V0_all = new THStack("hE_V0_all",";E [GeV];");
  hE_V0_all->SetMaximum(1e8);
  hE_V0_all->SetMinimum(1);
  hE_V0_all->Add(hE_V0_nungSum_ol);
  hE_V0_all->Add(hE_V0_nungSum_rest);
  hE_V0_all->Add(hE_V0_bhabhangSum_ol);
  hE_V0_all->Add(hE_V0_bhabhangSum_rest);
  hE_V0_all->Draw();
  TLegend* leg_c4_head = new TLegend(0.25,0.85,0.9,0.9);
  leg_c4_head->SetTextSize(0.05);
  leg_c4_head->SetTextFont(42);
  leg_c4_head->SetHeader("Reconstructed V0 objects");
  leg_c4_head->SetFillStyle(0);
  leg_c4_head->Draw();
  TLegend* leg_c4 = new TLegend(0.25,0.65,0.45,0.85);
  leg_c4->SetTextSize(0.05);
  leg_c4->SetTextFont(42);
  leg_c4->AddEntry(hE_V0_nungSum_rest, "#nu#nu+N#gamma: rest"  ,"f");
  leg_c4->AddEntry(hE_V0_nungSum_ol,   "#nu#nu+N#gamma: overlay","f");
  leg_c4->Draw();
  TLegend* leg_c4_2 = new TLegend(0.65,0.65,0.85,0.85);
  leg_c4_2->SetTextSize(0.05);
  leg_c4_2->SetTextFont(42);
  leg_c4_2->AddEntry(hE_V0_bhabhangSum_rest,     "e^{+}e^{-}+N#gamma: rest"  ,"f");
  leg_c4_2->AddEntry(hE_V0_bhabhangSum_ol,       "e^{+}e^{-}+N#gamma: overlay","f");
  leg_c4_2->Draw();

  TCanvas* c5 = new TCanvas("c5","",600,400);
  gPad->SetLogy();
  THStack* hE_neutron_all = new THStack("hE_neutron_all",";E [GeV];");
  hE_neutron_all->SetMaximum(1e8);
  hE_neutron_all->SetMinimum(1);
  hE_neutron_all->Add(hE_neutron_nungSum_ol);
  hE_neutron_all->Add(hE_neutron_nungSum_rest);
  hE_neutron_all->Add(hE_neutron_bhabhangSum_ol);
  hE_neutron_all->Add(hE_neutron_bhabhangSum_rest);
  hE_neutron_all->Draw();
  TLegend* leg_c5_head = new TLegend(0.25,0.85,0.9,0.9);
  leg_c5_head->SetTextSize(0.05);
  leg_c5_head->SetTextFont(42);
  leg_c5_head->SetHeader("Reconstructed neutrons");
  leg_c5_head->SetFillStyle(0);
  leg_c5_head->Draw();
  TLegend* leg_c5 = new TLegend(0.25,0.65,0.45,0.85);
  leg_c5->SetTextSize(0.05);
  leg_c5->SetTextFont(42);
  leg_c5->AddEntry(hE_neutron_nungSum_rest, "#nu#nu+N#gamma: rest"  ,"f");
  leg_c5->AddEntry(hE_neutron_nungSum_ol,   "#nu#nu+N#gamma: overlay","f");
  leg_c5->Draw();
  TLegend* leg_c5_2 = new TLegend(0.65,0.65,0.85,0.85);
  leg_c5_2->SetTextSize(0.05);
  leg_c5_2->SetTextFont(42);
  leg_c5_2->AddEntry(hE_neutron_bhabhangSum_rest,     "e^{+}e^{-}+N#gamma: rest"  ,"f");
  leg_c5_2->AddEntry(hE_neutron_bhabhangSum_ol,       "e^{+}e^{-}+N#gamma: overlay","f");
  leg_c5_2->Draw();

  TCanvas* c6 = new TCanvas("c6","",600,400);
  gPad->SetLogy();
  THStack* hE_electron_all = new THStack("hE_electron_all",";E [GeV];");
  hE_electron_all->SetMaximum(1e8);
  hE_electron_all->SetMinimum(1);
  hE_electron_all->Add(hE_electron_nungSum_ol);
  hE_electron_all->Add(hE_electron_nungSum_rest);
  hE_electron_all->Add(hE_electron_bhabhangSum_ol);
  hE_electron_all->Add(hE_electron_bhabhangSum_rest);
  hE_electron_all->Draw();
  TLegend* leg_c6_head = new TLegend(0.25,0.85,0.9,0.9);
  leg_c6_head->SetTextSize(0.05);
  leg_c6_head->SetTextFont(42);
  leg_c6_head->SetHeader("Reconstructed electrons");
  leg_c6_head->SetFillStyle(0);
  leg_c6_head->Draw();
  TLegend* leg_c6 = new TLegend(0.25,0.65,0.45,0.85);
  leg_c6->SetTextSize(0.05);
  leg_c6->SetTextFont(42);
  leg_c6->AddEntry(hE_electron_nungSum_rest, "#nu#nu+N#gamma: rest"  ,"f");
  leg_c6->AddEntry(hE_electron_nungSum_ol,   "#nu#nu+N#gamma: overlay","f");
  leg_c6->Draw();
  TLegend* leg_c6_2 = new TLegend(0.65,0.65,0.85,0.85);
  leg_c6_2->SetTextSize(0.05);
  leg_c6_2->SetTextFont(42);
  leg_c6_2->AddEntry(hE_electron_bhabhangSum_rest,     "e^{+}e^{-}+N#gamma: rest"  ,"f");
  leg_c6_2->AddEntry(hE_electron_bhabhangSum_ol,       "e^{+}e^{-}+N#gamma: overlay","f");
  leg_c6_2->Draw();

  TCanvas* c7 = new TCanvas("c7","",600,400);
  gPad->SetLogy();
  THStack* hE_muon_all = new THStack("hE_muon_all",";E [GeV];");
  hE_muon_all->SetMaximum(1e8);
  hE_muon_all->SetMinimum(1);
  hE_muon_all->Add(hE_muon_nungSum_ol);
  hE_muon_all->Add(hE_muon_nungSum_rest);
  hE_muon_all->Add(hE_muon_bhabhangSum_ol);
  hE_muon_all->Add(hE_muon_bhabhangSum_rest);
  hE_muon_all->Draw();
  TLegend* leg_c7_head = new TLegend(0.25,0.85,0.9,0.9);
  leg_c7_head->SetTextSize(0.05);
  leg_c7_head->SetTextFont(42);
  leg_c7_head->SetHeader("Reconstructed muons");
  leg_c7_head->SetFillStyle(0);
  leg_c7_head->Draw();
  TLegend* leg_c7 = new TLegend(0.25,0.65,0.45,0.85);
  leg_c7->SetTextSize(0.05);
  leg_c7->SetTextFont(42);
  leg_c7->AddEntry(hE_muon_nungSum_rest, "#nu#nu+N#gamma: rest"  ,"f");
  leg_c7->AddEntry(hE_muon_nungSum_ol,   "#nu#nu+N#gamma: overlay","f");
  leg_c7->Draw();
  TLegend* leg_c7_2 = new TLegend(0.65,0.65,0.85,0.85);
  leg_c7_2->SetTextSize(0.05);
  leg_c7_2->SetTextFont(42);
  leg_c7_2->AddEntry(hE_muon_bhabhangSum_rest,     "e^{+}e^{-}+N#gamma: rest"  ,"f");
  leg_c7_2->AddEntry(hE_muon_bhabhangSum_ol,       "e^{+}e^{-}+N#gamma: overlay","f");
  leg_c7_2->Draw();

  TCanvas* c8 = new TCanvas("c8","",600,400);
  gPad->SetLogy();
  THStack* hE_pion_all = new THStack("hE_pion_all",";E [GeV];");
  hE_pion_all->SetMaximum(1e8);
  hE_pion_all->SetMinimum(1);
  hE_pion_all->Add(hE_pion_nungSum_ol);
  hE_pion_all->Add(hE_pion_nungSum_rest);
  hE_pion_all->Add(hE_pion_bhabhangSum_ol);
  hE_pion_all->Add(hE_pion_bhabhangSum_rest);
  hE_pion_all->Draw();
  TLegend* leg_c8_head = new TLegend(0.25,0.85,0.9,0.9);
  leg_c8_head->SetTextSize(0.05);
  leg_c8_head->SetTextFont(42);
  leg_c8_head->SetHeader("Reconstructed pions");
  leg_c8_head->SetFillStyle(0);
  leg_c8_head->Draw();
  TLegend* leg_c8 = new TLegend(0.25,0.65,0.45,0.85);
  leg_c8->SetTextSize(0.05);
  leg_c8->SetTextFont(42);
  leg_c8->AddEntry(hE_pion_nungSum_rest, "#nu#nu+N#gamma: rest"  ,"f");
  leg_c8->AddEntry(hE_pion_nungSum_ol,   "#nu#nu+N#gamma: overlay","f");
  leg_c8->Draw();
  TLegend* leg_c8_2 = new TLegend(0.65,0.65,0.85,0.85);
  leg_c8_2->SetTextSize(0.05);
  leg_c8_2->SetTextFont(42);
  leg_c8_2->AddEntry(hE_pion_bhabhangSum_rest,     "e^{+}e^{-}+N#gamma: rest"  ,"f");
  leg_c8_2->AddEntry(hE_pion_bhabhangSum_ol,       "e^{+}e^{-}+N#gamma: overlay","f");
  leg_c8_2->Draw();

  TCanvas* c9 = new TCanvas("c9","",600,400);
  gPad->SetLogy();
  THStack* hEvis_all = new THStack("hEvis_all",";Evis [GeV];");
  hEvis_all->SetMaximum(1e8);
  hEvis_all->SetMinimum(1);
  hEvis_all->Add(hEvis_pfo_nungSum);
  hEvis_all->Add(hEvis_pfo_bhabhangSum);
  hEvis_all->Draw();
  TLegend* leg_c9_head = new TLegend(0.25,0.85,0.9,0.9);
  leg_c9_head->SetTextSize(0.05);
  leg_c9_head->SetTextFont(42);
  leg_c9_head->SetHeader("Visible energy: PFOs > 5GeV, all types");
  leg_c9_head->SetFillStyle(0);
  leg_c9_head->Draw();
  TLegend* leg_c9 = new TLegend(0.25,0.65,0.45,0.85);
  leg_c9->SetTextSize(0.04);
  leg_c9->SetTextFont(42);
  leg_c9->AddEntry(hEvis_pfo_bhabhangSum, "e^{+}e^{-}+N#gamma" ,"f");
  leg_c9->AddEntry(hEvis_pfo_nungSum,     "#nu#nu+N#gamma"     ,"f");
  leg_c9->Draw();

  TCanvas* c10 = new TCanvas("c10","",600,400);
  gPad->SetLogy();
  THStack* hEvis_wo_pi_n_all = new THStack("hEvis_wo_pi_n_all",";Evis [GeV];");
  hEvis_wo_pi_n_all->SetMaximum(1e8);
  hEvis_wo_pi_n_all->SetMinimum(1);
  hEvis_wo_pi_n_all->Add(hEvis_pfo_wo_pi_n_nungSum);
  hEvis_wo_pi_n_all->Add(hEvis_pfo_wo_pi_n_bhabhangSum);
  hEvis_wo_pi_n_all->Draw();
  TLegend* leg_c10_head = new TLegend(0.25,0.85,0.9,0.9);
  leg_c10_head->SetTextSize(0.05);
  leg_c10_head->SetTextFont(42);
  leg_c10_head->SetHeader("Visible energy: PFOs > 5GeV, w/o #pi,n");
  leg_c10_head->SetFillStyle(0);
  leg_c10_head->Draw();
  TLegend* leg_c10 = new TLegend(0.25,0.65,0.45,0.85);
  leg_c10->SetTextSize(0.04);
  leg_c10->SetTextFont(42);
  leg_c10->AddEntry(hEvis_pfo_wo_pi_n_bhabhangSum, "e^{+}e^{-}+N#gamma" ,"f");
  leg_c10->AddEntry(hEvis_pfo_wo_pi_n_nungSum,     "#nu#nu+N#gamma"     ,"f");
  leg_c10->Draw();

  TCanvas* c11 = new TCanvas("c11","",600,400);
  gPad->SetLogy();
  /* 
   * Note these histograms were not stacked in Moritz thesis,
   */
#if 1 // stacked version. Note that MultiISR means # of ISR to be more than 1.
  THStack* hNBcalClusters_all = new THStack("hNBcalClusters_all",";# of BCal clusters;");
  hNBcalClusters_all->SetMaximum(1e10);
  hNBcalClusters_all->SetMinimum(1);
  hNBcalClusters_all->Add(hNBcalClusters1ISR_nungSum);
  hNBcalClusters_all->Add(hNBcalClustersMultiISR_nungSum);
  hNBcalClusters_all->Add(hNBcalClusters_bhabhangSum);
  hNBcalClusters_all->Draw(); 
  TLegend* leg_c11_head = new TLegend(0.5,0.85,0.9,0.9);
  leg_c11_head->SetTextSize(0.05);
  leg_c11_head->SetTextFont(42);
  leg_c11_head->SetHeader("Number of BeamCal clusters");
  leg_c11_head->SetFillStyle(0);
  leg_c11_head->Draw();
  TLegend* leg_c11 = new TLegend(0.65,0.55,0.9,0.85);
  leg_c11->SetTextSize(0.04);
  leg_c11->SetTextFont(42);
  leg_c11->AddEntry(hNBcalClusters_bhabhangSum,     "e^{+}e^{-}+N#gamma (N>0)" ,"f");
  leg_c11->AddEntry(hNBcalClustersMultiISR_nungSum, "#nu#nu+N#gamma (N>1)"     ,"f");
  leg_c11->AddEntry(hNBcalClusters1ISR_nungSum,     "#nu#nu+1#gamma"           ,"f");
  leg_c11->Draw();
#else // Moritz's version
  hNBcalClustersMultiISR->SetMinimum(1);
  hNBcalClustersMultiISR_nungSum->Draw();
  hNBcalClusters1ISR_nungSum->Draw("same");
  hNBcalClusters_bhabhangSum->Draw("same");
  TLegend* leg_c11_head = new TLegend(0.65,0.85,0.9,0.9,"Number of BeamCal clusters");
  leg_c11_head->SetFillStyle(0);
  leg_c11_head->Draw();
  TLegend* leg_c11 = new TLegend(0.65,0.55,0.9,0.85);
  leg_c11->AddEntry(hNBcalClusters_bhabhangSum,     "e^{+}e^{-}+N#gamma" ,"f");
  leg_c11->AddEntry(hNBcalClustersMultiISR_nungSum, "#nu#nu+N#gamma"     ,"f");
  leg_c11->AddEntry(hNBcalClusters1ISR_nungSum,     "#nu#nu+1#gamma"     ,"f");
  leg_c11->Draw();
#endif

  TCanvas* c12 = new TCanvas("c12","",600,400);
  gPad->SetLogy();
  hE_photon_nungSum->Draw();

  TCanvas* c13 = new TCanvas("c13","",600,400);
  gPad->SetLogy();
  hNrecNgen_photon_nungSum->DrawNormalized();

  TCanvas* c14 = new TCanvas("c14","",600,400);
  gNrecNgenEmc_photon_nungSum->GetXaxis()->SetRangeUser(0.,250.);
  gNrecNgenEmc_photon_nungSum->GetYaxis()->SetRangeUser(0.99,1.03);
  gNrecNgenEmc_photon_nungSum->Draw("ap");

  TCanvas* c15 = new TCanvas("c15","",600,400);
  gNrecNgenCostheta_photon_nungSum->Draw("ap");
  gNrecNgenCostheta_photon_nungSum->GetXaxis()->SetRangeUser(0.,1.);
  gNrecNgenCostheta_photon_nungSum->GetYaxis()->SetRangeUser(0.99,1.15);

  TCanvas* c16 = new TCanvas("c16","",600,400);
  THStack* hPt_bcal_bcalcoord_all = new THStack("hPt_bcal_bcalcoord_all",";Pt [GeV];");
  gPad->SetLogy();
  hPt_bcal_bcalcoord_all->SetMaximum(1e10);
  hPt_bcal_bcalcoord_all->SetMinimum(1);
  hPt_bcal_bcalcoord_all->Add(hPt_bcal_bcalcoord_nungSum);
  hPt_bcal_bcalcoord_all->Add(hPt_bcal_bcalcoord_bhabhangSum);
  hPt_bcal_bcalcoord_all->Draw(); 
  TLegend* leg_c16_head = new TLegend(0.4,0.85,0.9,0.9);
  leg_c16_head->SetTextSize(0.05);
  leg_c16_head->SetTextFont(42);
  leg_c16_head->SetHeader("Pt of BCalClusters in BCal coordinate");
  leg_c16_head->SetFillStyle(0);
  leg_c16_head->Draw();
  TLegend* leg_c16 = new TLegend(0.65,0.55,0.9,0.85);
  leg_c16->SetTextSize(0.04);
  leg_c16->SetTextFont(42);
  leg_c16->AddEntry(hPt_bcal_bcalcoord_bhabhangSum, "e^{+}e^{-}+N#gamma" ,"f");
  leg_c16->AddEntry(hPt_bcal_bcalcoord_nungSum,     "#nu#nu+N#gamma" ,"f");
  leg_c16->Draw();

  TCanvas* c17 = new TCanvas("c17","",600,400);
  THStack* hPtMax_bcal_bcalcoord_all = new THStack("hPtMax_bcal_bcalcoord_all",";Pt [GeV];");
  gPad->SetLogy();
  hPtMax_bcal_bcalcoord_all->SetMaximum(1e10);
  hPtMax_bcal_bcalcoord_all->SetMinimum(1);
  hPtMax_bcal_bcalcoord_all->Add(hPtMax_bcal_bcalcoord_nungSum);
  hPtMax_bcal_bcalcoord_all->Add(hPtMax_bcal_bcalcoord_bhabhangSum);
  hPtMax_bcal_bcalcoord_all->Draw(); 
  TLegend* leg_c17_head = new TLegend(0.35,0.85,0.9,0.9);
  leg_c17_head->SetTextSize(0.05);
  leg_c17_head->SetTextFont(42);
  leg_c17_head->SetHeader("PtMax in BCalClusters in BCal coordinate");
  leg_c17_head->SetFillStyle(0);
  leg_c17_head->Draw();
  TLegend* leg_c17 = new TLegend(0.65,0.55,0.9,0.85);
  leg_c17->SetTextSize(0.04);
  leg_c17->SetTextFont(42);
  leg_c17->AddEntry(hPtMax_bcal_bcalcoord_bhabhangSum, "e^{+}e^{-}+N#gamma" ,"f");
  leg_c17->AddEntry(hPtMax_bcal_bcalcoord_nungSum,     "#nu#nu+N#gamma" ,"f");
  leg_c17->Draw();

  TCanvas* c18 = new TCanvas("c18","",600,400);
  THStack* hPt_bcal_all = new THStack("hPt_bcal_all",";Pt [GeV];");
  gPad->SetLogy();
  hPt_bcal_all->SetMaximum(1e10);
  hPt_bcal_all->SetMinimum(1);
  hPt_bcal_all->Add(hPt_bcal_nungSum);
  hPt_bcal_all->Add(hPt_bcal_bhabhangSum);
  hPt_bcal_all->Draw(); 
  TLegend* leg_c18_head = new TLegend(0.4,0.85,0.9,0.9);
  leg_c18_head->SetTextSize(0.05);
  leg_c18_head->SetTextFont(42);
  leg_c18_head->SetHeader("Pt of BCalClusters in ILD coordinate");
  leg_c18_head->SetFillStyle(0);
  leg_c18_head->Draw();
  TLegend* leg_c18 = new TLegend(0.65,0.55,0.9,0.85);
  leg_c18->SetTextSize(0.04);
  leg_c18->SetTextFont(42);
  leg_c18->AddEntry(hPt_bcal_bhabhangSum, "e^{+}e^{-}+N#gamma" ,"f");
  leg_c18->AddEntry(hPt_bcal_nungSum,     "#nu#nu+N#gamma" ,"f");
  leg_c18->Draw();

  TCanvas* c19 = new TCanvas("c19","",600,400);
  THStack* hE_bcal_all = new THStack("hE_bcal_all",";E [GeV];");
  gPad->SetLogy();
  hE_bcal_all->SetMaximum(1e10);
  hE_bcal_all->SetMinimum(1);
  hE_bcal_all->Add(hE_bcal_nungSum);
  hE_bcal_all->Add(hE_bcal_bhabhangSum);
  hE_bcal_all->Draw(); 
  TLegend* leg_c19_head = new TLegend(0.55,0.85,0.9,0.9);
  leg_c19_head->SetTextSize(0.05);
  leg_c19_head->SetTextFont(42);
  leg_c19_head->SetHeader("Energy of BCalClusters");
  leg_c19_head->SetFillStyle(0);
  leg_c19_head->Draw();
  TLegend* leg_c19 = new TLegend(0.65,0.55,0.9,0.85);
  leg_c19->SetTextSize(0.04);
  leg_c19->SetTextFont(42);
  leg_c19->AddEntry(hE_bcal_bhabhangSum, "e^{+}e^{-}+N#gamma" ,"f");
  leg_c19->AddEntry(hE_bcal_nungSum,     "#nu#nu+N#gamma" ,"f");
  leg_c19->Draw();

  c1->Print("c1.pdf");
  c2->Print("c2.pdf");
  c3->Print("c3.pdf");
  c4->Print("c4.pdf");
  c5->Print("c5.pdf");
  c6->Print("c6.pdf");
  c7->Print("c7.pdf");
  c8->Print("c8.pdf");
  c9->Print("c9.pdf");
  c10->Print("c10.pdf");
  c11->Print("c11.pdf");
  c12->Print("c12.pdf");
  c13->Print("c13.pdf");
  c14->Print("c14.pdf");
  c15->Print("c15.pdf");
  c16->Print("c16.pdf");
  c17->Print("c17.pdf");
  c18->Print("c18.pdf");
  c19->Print("c19.pdf");
#endif
}
