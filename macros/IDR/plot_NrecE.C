void plot_NrecE() 
{
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  gROOT->LoadMacro(styleMacroPath.Data());

  //TFile* finl5 = new TFile("run_l5/plots/plots.root");
  TFile* fins5 = new TFile("run_s5/plots/plots.root");
  //TNtuple* SignalPhoton_nungLR = static_cast<TNtuple*>(finl5->Get("SignalPhoton_nungLR"));
  //TNtuple* SignalPhoton_nungRL = static_cast<TNtuple*>(finl5->Get("SignalPhoton_nungRL"));
  TNtuple* SignalPhoton_nungLR_s5 = static_cast<TNtuple*>(fins5->Get("SignalPhoton_nungLR"));
  //TNtuple* SignalPhoton_nungRL = static_cast<TNtuple*>(finl5->Get("SignalPhoton_nungRL"));

  const int nxbins = 17;
  const double xbins[nxbins] = {0,5,10,15,20,25,30,35,40,45,50,70,90,120,150,200,250};
  //TH2F* hSuml5 = new TH2F("hSuml5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);
  //TH2F* hSums5 = new TH2F("hSums5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);
  //TH2F* hPl5 = new TH2F("hPl5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);
  TH2F* hPs5 = new TH2F("hPs5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);
  //TH2F* hNPl5 = new TH2F("hNPl5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);
  //TH2F* hNPs5 = new TH2F("hNPs5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);

  TCanvas* c = new TCanvas("c","",600,600);
  SignalPhoton_nungLR_s5->Draw("nrec_pfoAsPhoton:gen_e>>hPs5","nAcceptablePhoton_MC_per_evt==1&&gen_e>2&&fabs(gen_theta)>7*TMath::Pi()/180.&&fabs(gen_theta)<173*TMath::Pi()/180.&&nISR==1&&gen_ndaughters<2");
  gPad->SetRightMargin(0.2);
  hPs5->GetYaxis()->SetTickLength(0.01);
  gPad->SetLogz();
  hPs5->SetNdivisions(708, "Y");
  hPs5->Draw("COLZ");
  c->Print("NrecNgenE_photon_example.pdf");
}
