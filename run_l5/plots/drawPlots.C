void drawPlots() {

  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  TString rootFilePath(topDirPath+"/run_l5/plots/plots.root");
  gROOT->LoadMacro(styleMacroPath.Data());
  TFile* fin = new TFile(rootFilePath.Data());

  TH1F* hPt_ep_nung_other             = static_cast<TH1F*>(fin->Get("hPt_ep_nung_other"));
  TH1F* hPt_ep_nung_ol                = static_cast<TH1F*>(fin->Get("hPt_ep_nung_ol"));
  TH1F* hPt_ep_nung_isr               = static_cast<TH1F*>(fin->Get("hPt_ep_nung_isr"));
  TH1F* hPt_pfo_nung_isr              = static_cast<TH1F*>(fin->Get("hPt_pfo_nung_isr"));
  TH1F* hPt_pfo_nung_ol               = static_cast<TH1F*>(fin->Get("hPt_pfo_nung_isr"));
  TH1F* hPt_pfo_nung_other            = static_cast<TH1F*>(fin->Get("hPt_pfo_nung_other"));
  TH1F* hE_photon_nung_rest           = static_cast<TH1F*>(fin->Get("hE_photon_nung_rest"));
  TH1F* hE_photon_nung_ol             = static_cast<TH1F*>(fin->Get("hE_photon_nung_ol"));
  TH1F* hE_V0_nung_rest               = static_cast<TH1F*>(fin->Get("hE_V0_nung_rest"));
  TH1F* hE_V0_nung_ol                 = static_cast<TH1F*>(fin->Get("hE_V0_nung_ol"));
  TH1F* hE_neutron_nung_rest          = static_cast<TH1F*>(fin->Get("hE_neutron_nung_rest"));
  TH1F* hE_neutron_nung_ol            = static_cast<TH1F*>(fin->Get("hE_neutron_nung_ol"));
  TH1F* hE_electron_nung_rest         = static_cast<TH1F*>(fin->Get("hE_electron_nung_rest"));
  TH1F* hE_electron_nung_ol           = static_cast<TH1F*>(fin->Get("hE_electron_nung_ol"));
  TH1F* hE_muon_nung_rest             = static_cast<TH1F*>(fin->Get("hE_muon_nung_rest"));
  TH1F* hE_muon_nung_ol               = static_cast<TH1F*>(fin->Get("hE_muon_nung_ol"));
  TH1F* hE_pion_nung_rest             = static_cast<TH1F*>(fin->Get("hE_pion_nung_rest"));
  TH1F* hE_pion_nung_ol               = static_cast<TH1F*>(fin->Get("hE_pion_nung_ol"));
  TH1F* hEvis_pfo_nung                = static_cast<TH1F*>(fin->Get("hEvis_pfo_nung"));
  TH1F* hEvis_pfo_wo_pi_n_nung        = static_cast<TH1F*>(fin->Get("hEvis_pfo_wo_pi_n_nung"));
  TH1F* hNBcalClusters_nung           = static_cast<TH1F*>(fin->Get("hNBcalClusters_nung"));
  TH1F* hNBcalClusters1ISR_nung       = static_cast<TH1F*>(fin->Get("hNBcalClusters1ISR_nung"));
  TH1F* hNBcalClustersMultiISR_nung   = static_cast<TH1F*>(fin->Get("hNBcalClustersMultiISR_nung"));

  TH1F* hPt_ep_bhabhang_isr             = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhang_isr"));
  TH1F* hPt_ep_bhabhang_ol              = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhang_ol"));
  TH1F* hPt_ep_bhabhang_other           = static_cast<TH1F*>(fin->Get("hPt_ep_bhabhang_other"));
  TH1F* hPt_pfo_bhabhang_isr            = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhang_isr"));
  TH1F* hPt_pfo_bhabhang_ol             = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhang_ol"));
  TH1F* hPt_pfo_bhabhang_other          = static_cast<TH1F*>(fin->Get("hPt_pfo_bhabhang_other"));
  TH1F* hE_photon_bhabhang_rest         = static_cast<TH1F*>(fin->Get("hE_photon_bhabhang_rest"));
  TH1F* hE_photon_bhabhang_ol           = static_cast<TH1F*>(fin->Get("hE_photon_bhabhang_ol"));
  TH1F* hE_photon_bhabhang_electron     = static_cast<TH1F*>(fin->Get("hE_photon_bhabhang_electron"));
  TH1F* hE_V0_bhabhang_rest             = static_cast<TH1F*>(fin->Get("hE_V0_bhabhang_rest"));
  TH1F* hE_V0_bhabhang_ol               = static_cast<TH1F*>(fin->Get("hE_V0_bhabhang_ol"));
  TH1F* hE_neutron_bhabhang_rest        = static_cast<TH1F*>(fin->Get("hE_neutron_bhabhang_rest"));
  TH1F* hE_neutron_bhabhang_ol          = static_cast<TH1F*>(fin->Get("hE_neutron_bhabhang_ol"));
  TH1F* hE_electron_bhabhang_rest       = static_cast<TH1F*>(fin->Get("hE_electron_bhabhang_rest"));
  TH1F* hE_electron_bhabhang_ol         = static_cast<TH1F*>(fin->Get("hE_electron_bhabhang_ol"));
  TH1F* hE_muon_bhabhang_rest           = static_cast<TH1F*>(fin->Get("hE_muon_bhabhang_rest"));
  TH1F* hE_muon_bhabhang_ol             = static_cast<TH1F*>(fin->Get("hE_muon_bhabhang_ol"));
  TH1F* hE_pion_bhabhang_rest           = static_cast<TH1F*>(fin->Get("hE_pion_bhabhang_rest"));
  TH1F* hE_pion_bhabhang_ol             = static_cast<TH1F*>(fin->Get("hE_pion_bhabhang_ol"));
  TH1F* hEvis_pfo_bhabhang              = static_cast<TH1F*>(fin->Get("hEvis_pfo_bhabhang"));
  TH1F* hEvis_pfo_wo_pi_n_bhabhang      = static_cast<TH1F*>(fin->Get("hEvis_pfo_wo_pi_n_bhabhang"));
  TH1F* hNBcalClusters_bhabhang         = static_cast<TH1F*>(fin->Get("hNBcalClusters_bhabhang"));
  TH1F* hNBcalClusters1ISR_bhabhang     = static_cast<TH1F*>(fin->Get("hNBcalClusters1ISR_bhabhang"));
  TH1F* hNBcalClustersMultiISR_bhabhang = static_cast<TH1F*>(fin->Get("hNBcalClustersMultiISR_bhabhang"));




  hPt_ep_nung_isr->SetFillColor(kAzure+6);
  hPt_ep_nung_ol->SetFillColor(kYellow+1);
  hPt_ep_nung_other->SetFillColor(kGreen+3);
  hPt_pfo_nung_isr->SetFillColor(kAzure+6);
  hPt_pfo_nung_ol->SetFillColor(kYellow+1);
  hPt_pfo_nung_other->SetFillColor(kGreen+3);
  hE_photon_nung_rest->SetFillColor(kGreen+3);
  hE_photon_nung_ol->SetFillColor(kYellow+1);
  hE_V0_nung_rest->SetFillColor(kGreen+3);
  hE_V0_nung_ol->SetFillColor(kYellow+1);
  hE_neutron_nung_rest->SetFillColor(kGreen+3);
  hE_neutron_nung_ol->SetFillColor(kYellow+1);
  hE_electron_nung_rest->SetFillColor(kGreen+3);
  hE_electron_nung_ol->SetFillColor(kYellow+1);
  hE_muon_nung_rest->SetFillColor(kGreen+3);
  hE_muon_nung_ol->SetFillColor(kYellow+1);
  hE_pion_nung_rest->SetFillColor(kGreen+3);
  hE_pion_nung_ol->SetFillColor(kYellow+1);
  hEvis_pfo_nung->SetFillColor(kGreen+3);
  hEvis_pfo_wo_pi_n_nung->SetFillColor(kGreen+3);
  hNBcalClusters1ISR_nung->SetFillColor(kYellow+1);
  hNBcalClustersMultiISR_nung->SetFillColor(kGreen+3);

  hPt_ep_bhabhang_isr->SetFillColor(kOrange+4);
  hPt_ep_bhabhang_ol->SetFillColor(kMagenta+1);
  hPt_ep_bhabhang_other->SetFillColor(kOrange+6);
  hPt_pfo_bhabhang_isr->SetFillColor(kOrange+4);
  hPt_pfo_bhabhang_ol->SetFillColor(kMagenta+1);
  hPt_pfo_bhabhang_other->SetFillColor(kOrange+6);
  hE_photon_bhabhang_rest->SetFillColor(kOrange+6);
  hE_photon_bhabhang_electron->SetFillColor(kOrange+4);
  hE_photon_bhabhang_ol->SetFillColor(kMagenta+1);
  hE_V0_bhabhang_rest->SetFillColor(kOrange+6);
  hE_V0_bhabhang_ol->SetFillColor(kMagenta+1);
  hE_neutron_bhabhang_rest->SetFillColor(kOrange+6);
  hE_neutron_bhabhang_ol->SetFillColor(kMagenta+1);
  hE_electron_bhabhang_rest->SetFillColor(kOrange+6);
  hE_electron_bhabhang_ol->SetFillColor(kMagenta+1);
  hE_muon_bhabhang_rest->SetFillColor(kOrange+6);
  hE_muon_bhabhang_ol->SetFillColor(kMagenta+1);
  hE_pion_bhabhang_rest->SetFillColor(kOrange+6);
  hE_pion_bhabhang_ol->SetFillColor(kMagenta+1);
  hEvis_pfo_bhabhang->SetFillColor(kOrange+6);
  hEvis_pfo_wo_pi_n_bhabhang->SetFillColor(kOrange+6);
  hNBcalClusters_bhabhang->SetFillColor(kOrange+6);



  TCanvas* c1 = new TCanvas("c1","",600,400);
  gPad->SetLogy();
  //THStack* hPt_e_all = new THStack("hPt_e_all","Electron/Positron;P_{T} [GeV];");
  THStack* hPt_e_all = new THStack("hPt_e_all",";P_{T} [GeV];");
  hPt_e_all->SetMaximum(1e10);
  hPt_e_all->SetMinimum(1);
  hPt_e_all->Add(hPt_ep_nung_other);
  hPt_e_all->Add(hPt_ep_nung_ol);
  hPt_e_all->Add(hPt_ep_nung_isr);
  hPt_e_all->Add(hPt_ep_bhabhang_ol);
  hPt_e_all->Add(hPt_ep_bhabhang_isr);
  hPt_e_all->Add(hPt_ep_bhabhang_other);
  hPt_e_all->Draw();
  TLegend* leg_c1_head = new TLegend(0.25,0.85,0.9,0.9,"Transverse momenta of electrons");
  leg_c1_head->SetFillStyle(0);
  leg_c1_head->Draw();
  TLegend* leg_c1 = new TLegend(0.25,0.65,0.45,0.85);
  leg_c1->AddEntry(hPt_ep_nung_isr,  "#nu#nu+N#gamma: photons","f");
  leg_c1->AddEntry(hPt_ep_nung_ol,   "#nu#nu+N#gamma: overlay","f");
  leg_c1->AddEntry(hPt_ep_nung_other,"#nu#nu+N#gamma: other"  ,"f");
  leg_c1->Draw();
  TLegend* leg_c1_2 = new TLegend(0.65,0.65,0.85,0.85);
  leg_c1_2->AddEntry(hPt_ep_bhabhang_isr,  "e^{+}e^{-}+N#gamma: photons","f");
  leg_c1_2->AddEntry(hPt_ep_bhabhang_ol,   "e^{+}e^{-}+N#gamma: overlay","f");
  leg_c1_2->AddEntry(hPt_ep_bhabhang_other,"e^{+}e^{-}+N#gamma: other"  ,"f");
  leg_c1_2->Draw();
}
