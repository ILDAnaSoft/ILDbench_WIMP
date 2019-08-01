void plot_NrecNgenE_IDR() 
{
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  gROOT->LoadMacro(styleMacroPath.Data());

  TString filePath_l5(topDirPath+"run_l5/plots/plots.root");
  TString filePath_s5(topDirPath+"run_s5/plots/plots.root");
  TFile* finl5 = new TFile(filePath_l5.Data());
  TFile* fins5 = new TFile(filePath_s5.Data());
  TNtuple* SignalPhoton_nungLR = static_cast<TNtuple*>(finl5->Get("SignalPhoton_nungLR"));
  //TNtuple* SignalPhoton_nungRL = static_cast<TNtuple*>(finl5->Get("SignalPhoton_nungRL"));
  TNtuple* SignalPhoton_nungLR_s5 = static_cast<TNtuple*>(fins5->Get("SignalPhoton_nungLR"));
  //TNtuple* SignalPhoton_nungRL = static_cast<TNtuple*>(finl5->Get("SignalPhoton_nungRL"));

  const int nxbins = 17;
  const double xbins[nxbins] = {0,5,10,15,20,25,30,35,40,45,50,70,90,120,150,200,250};
  TH2F* hSuml5 = new TH2F("hSuml5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);
  TH2F* hSums5 = new TH2F("hSums5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);
  TH2F* hPl5 = new TH2F("hPl5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);
  TH2F* hPs5 = new TH2F("hPs5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);
  TH2F* hNPl5 = new TH2F("hNPl5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);
  TH2F* hNPs5 = new TH2F("hNPs5",";E_{MC} [GeV/c];N_{rec}",nxbins-1,xbins,8,-0.5,7.5);

  SignalPhoton_nungLR->Draw("nrec_pfoAsPhoton+nrec_pfoAsNonPhoton:gen_e>>hSuml5","nAcceptablePhoton_MC_per_evt==1&&gen_e>2&&fabs(gen_theta)>7*TMath::Pi()/180.&&fabs(gen_theta)<173*TMath::Pi()/180.&&nISR==1&&gen_ndaughters<2");
  SignalPhoton_nungLR_s5->Draw("nrec_pfoAsPhoton+nrec_pfoAsNonPhoton:gen_e>>hSums5","nAcceptablePhoton_MC_per_evt==1&&gen_e>2&&fabs(gen_theta)>7*TMath::Pi()/180.&&fabs(gen_theta)<173*TMath::Pi()/180.&&nISR==1&&gen_ndaughters<2");
  SignalPhoton_nungLR->Draw("nrec_pfoAsPhoton:gen_e>>hPl5","nAcceptablePhoton_MC_per_evt==1&&gen_e>2&&fabs(gen_theta)>7*TMath::Pi()/180.&&fabs(gen_theta)<173*TMath::Pi()/180.&&nISR==1&&gen_ndaughters<2");
  SignalPhoton_nungLR_s5->Draw("nrec_pfoAsPhoton:gen_e>>hPs5","nAcceptablePhoton_MC_per_evt==1&&gen_e>2&&fabs(gen_theta)>7*TMath::Pi()/180.&&fabs(gen_theta)<173*TMath::Pi()/180.&&nISR==1&&gen_ndaughters<2");
  SignalPhoton_nungLR->Draw("nrec_pfoAsNonPhoton:gen_e>>hNPl5","nAcceptablePhoton_MC_per_evt==1&&gen_e>2&&fabs(gen_theta)>7*TMath::Pi()/180.&&fabs(gen_theta)<173*TMath::Pi()/180.&&nISR==1&&gen_ndaughters<2");
  SignalPhoton_nungLR_s5->Draw("nrec_pfoAsNonPhoton:gen_e>>hNPs5","nAcceptablePhoton_MC_per_evt==1&&gen_e>2&&fabs(gen_theta)>7*TMath::Pi()/180.&&fabs(gen_theta)<173*TMath::Pi()/180.&&nISR==1&&gen_ndaughters<2");

  //TH2D* hSuml5 = static_cast<TH2D*>(gROOT->FindObject("hSuml5"));
  //TH2D* hSums5 = static_cast<TH2D*>(gROOT->FindObject("hSums5"));
  //TH2D* hPl5 = static_cast<TH2D*>(gROOT->FindObject("hPl5"));
  //TH2D* hPs5 = static_cast<TH2D*>(gROOT->FindObject("hPs5"));
  //TH2D* hNPl5 = static_cast<TH2D*>(gROOT->FindObject("hNPl5"));
  //TH2D* hNPs5 = static_cast<TH2D*>(gROOT->FindObject("hNPs5"));

  TGraphErrors* gSuml5 = new TGraphErrors();
  TGraphErrors* gSums5 = new TGraphErrors();
  TGraphErrors* gPl5 = new TGraphErrors();
  TGraphErrors* gPs5 = new TGraphErrors();
  TGraphErrors* gNPl5 = new TGraphErrors();
  TGraphErrors* gNPs5 = new TGraphErrors();

  for (int ix = 0; ix < nxbins-1; ix++) {
    stringstream hname_l5, hname_s5;
    stringstream hname_Pl5, hname_Ps5;
    stringstream hname_NPl5, hname_NPs5;
    hname_l5 << "bsuml5" << ix << ends;
    hname_s5 << "bsums5" << ix << ends;
    hname_Pl5 << "bPl5" << ix << ends;
    hname_Ps5 << "bPs5" << ix << ends;
    hname_NPl5 << "bNPl5" << ix << ends;
    hname_NPs5 << "bNPs5" << ix << ends;
    hSuml5->ProjectionY(hname_l5.str().data(),ix,ix+1);
    hSums5->ProjectionY(hname_s5.str().data(),ix,ix+1);
    hPl5->ProjectionY(hname_Pl5.str().data(),ix,ix+1);
    hPs5->ProjectionY(hname_Ps5.str().data(),ix,ix+1);
    hNPl5->ProjectionY(hname_NPl5.str().data(),ix,ix+1);
    hNPs5->ProjectionY(hname_NPs5.str().data(),ix,ix+1);
    TH1D* hpSuml5 = static_cast<TH1D*>(gROOT->FindObject(hname_l5.str().data()));
    TH1D* hpSums5 = static_cast<TH1D*>(gROOT->FindObject(hname_s5.str().data()));
    TH1D* hpPl5 = static_cast<TH1D*>(gROOT->FindObject(hname_Pl5.str().data()));
    TH1D* hpPs5 = static_cast<TH1D*>(gROOT->FindObject(hname_Ps5.str().data()));
    TH1D* hpNPl5 = static_cast<TH1D*>(gROOT->FindObject(hname_NPl5.str().data()));
    TH1D* hpNPs5 = static_cast<TH1D*>(gROOT->FindObject(hname_NPs5.str().data()));
    gSuml5->SetPoint(ix,(xbins[ix]+xbins[ix+1])/2.,hpSuml5->GetMean());
    gSuml5->SetPointError(ix,(xbins[ix+1]-xbins[ix])/2.,hpSuml5->GetRMS()/TMath::Sqrt(hpSuml5->GetEntries()));

    gSums5->SetPoint(ix,(xbins[ix]+xbins[ix+1])/2.,hpSums5->GetMean());
    gSums5->SetPointError(ix,(xbins[ix+1]-xbins[ix])/2.,hpSums5->GetRMS()/TMath::Sqrt(hpSums5->GetEntries()));
    gPl5->SetPoint(ix,(xbins[ix]+xbins[ix+1])/2.,hpPl5->GetMean());
    gPl5->SetPointError(ix,(xbins[ix+1]-xbins[ix])/2.,hpPl5->GetRMS()/TMath::Sqrt(hpPl5->GetEntries()));
    gPs5->SetPoint(ix,(xbins[ix]+xbins[ix+1])/2.,hpPs5->GetMean());
    gPs5->SetPointError(ix,(xbins[ix+1]-xbins[ix])/2.,hpPs5->GetRMS()/TMath::Sqrt(hpPs5->GetEntries()));
    gNPl5->SetPoint(ix,(xbins[ix]+xbins[ix+1])/2.,hpNPl5->GetMean());
    gNPl5->SetPointError(ix,(xbins[ix+1]-xbins[ix])/2.,hpNPl5->GetRMS()/TMath::Sqrt(hpNPl5->GetEntries()));
    gNPs5->SetPoint(ix,(xbins[ix]+xbins[ix+1])/2.,hpNPs5->GetMean());
    gNPs5->SetPointError(ix,(xbins[ix+1]-xbins[ix])/2.,hpNPs5->GetRMS()/TMath::Sqrt(hpNPs5->GetEntries()));
cerr << " ix = " << ix << " hpNPl5->GetMean() = " << hpNPl5->GetMean() << endl;
  }

  TLatex *tex = new TLatex();
  tex->SetTextSize(0.05);

  TCanvas* csum = new TCanvas("csum","",600,600);
  gSuml5->SetName("gSuml5");
  gSums5->SetName("gSums5");
  gSuml5->SetTitle(";E_{MC} [GeV];#bar{N_{rec}/N_{gen}}");
  gSuml5->GetXaxis()->SetRangeUser(0.,250.);
  gSuml5->GetYaxis()->SetRangeUser(0.98,1.2);
  gSuml5->GetYaxis()->SetTitleOffset(1.4);
  gSums5->SetMarkerStyle(kOpenCircle);
  gSuml5->SetMarkerColor(kBlue);
  gSums5->SetMarkerColor(kRed);
  gSuml5->SetLineColor(kBlue);
  gSums5->SetLineColor(kRed);
  gSuml5->Draw("ape");
  gSums5->Draw("pe same");
  TLegend *leg = new TLegend(0.25,0.77,0.4,0.67);
  leg->SetTextFont(62);
  leg->SetTextSize(0.03); 
  leg->SetTextAlign(12);
  leg->AddEntry(gSuml5,"IDR-L","elp"); 
  leg->AddEntry(gSums5,"IDR-S","elp"); 
  leg->Draw();
  tex->DrawLatexNDC(0.25,0.8,"#scale[1.5]{#font[62]{ILD}} #font[42]{preliminary}");
  //tex->DrawLatexNDC(0.4,0.7,"#scale[0.5]{#font[42]{All PFOs}}");
  //TPaveText* pt = new TPaveText(0.55,0.855,0.895,0.895,"NDC");
  //pt->AddText("All PFOs");
  //pt->SetTextFont(42);
  //pt->SetTextSize(0.02);
  //pt->Draw();
  csum->SetLeftMargin(0.2);
  csum->Print("NrecNgenE_allpfo_IDR.pdf");
  csum->Print("NrecNgenE_allpfo_IDR.C");

  TCanvas* cP = new TCanvas("cP","",600,600);
  gPl5->SetName("gPl5");
  gPs5->SetName("gPs5");
  gPl5->SetTitle(";E_{MC} [GeV];#bar{N_{rec}/N_{gen}}");
  gPl5->GetYaxis()->SetTitleOffset(1.4);
  gPl5->GetYaxis()->SetRangeUser(0.98,1.03);
  gPl5->GetXaxis()->SetRangeUser(0.,250.);
  gPs5->SetMarkerStyle(kOpenCircle);
  gPl5->SetMarkerColor(kBlue);
  gPs5->SetMarkerColor(kRed);
  gPl5->SetLineColor(kBlue);
  gPs5->SetLineColor(kRed);
  gPl5->Draw("ape");
  gPs5->Draw("pe same");
  TLegend *leg2 = new TLegend(0.25,0.77,0.5,0.67);
  leg2->SetTextFont(62);
  leg2->SetTextSize(0.03); 
  leg2->SetTextAlign(12);
  leg2->AddEntry(gPl5,"IDR-L","elp"); 
  leg2->AddEntry(gPs5,"IDR-S","elp"); 
  leg2->Draw();
  tex->DrawLatexNDC(0.25,0.8,"#scale[1.5]{#font[62]{ILD}} #font[42]{preliminary}");
  //tex->DrawLatexNDC(0.4,0.7,"#scale[0.5]{#font[42]{PFOs reconstructed as photons}}");
  //TPaveText* pt2 = new TPaveText(0.4,0.75,0.8,0.7,"NDC");
  //TPaveText* pt2 = new TPaveText(0.55,0.855,0.895,0.895,"NDC");
  //pt2->AddText("PFOs reconstructed as photons");
  //pt2->SetTextFont(42);
  //pt2->SetTextSize(0.02);
  //pt2->Draw();
  cP->SetLeftMargin(0.2);
  cP->Print("NrecNgenE_photon_IDR.pdf");
  cP->Print("NrecNgenE_photon_IDR.C");

  TCanvas* cNP = new TCanvas("cNP","",600,600);
  gNPl5->SetName("gNPl5");
  gNPs5->SetName("gNPs5");
  gNPl5->SetTitle(";E_{MC} [GeV];#bar{N_{rec}/N_{gen}}");
  gNPl5->GetYaxis()->SetRangeUser(0.,0.15);
  gNPl5->GetYaxis()->SetTitleOffset(1.4);
  gNPl5->GetXaxis()->SetRangeUser(0.,250.);
  gNPs5->SetMarkerStyle(kOpenCircle);
  gNPl5->SetMarkerColor(kBlue);
  gNPs5->SetMarkerColor(kRed);
  gNPl5->SetLineColor(kBlue);
  gNPs5->SetLineColor(kRed);
  gNPl5->Draw("ape");
  gNPs5->Draw("pe same");
  TLegend *leg3 = new TLegend(0.25,0.77,0.5,0.67);
  leg3->SetTextFont(62);
  leg3->SetTextSize(0.03); 
  leg3->SetTextAlign(12);
  leg3->AddEntry(gNPl5,"IDR-L","elp"); 
  leg3->AddEntry(gNPs5,"IDR-S","elp"); 
  leg3->Draw();
  tex->Draw();
  tex->DrawLatexNDC(0.25,0.8,"#scale[1.5]{#font[62]{ILD}} #font[42]{preliminary}");
  //tex->DrawLatexNDC(0.4,0.7,"#scale[0.5]{#font[42]{PFOs reconstructed as non-photons}}");
  //TPaveText* pt3 = new TPaveText(0.55,0.855,0.895,0.895,"NDC");
  //pt3->AddText("PFOs reconstructed as non-photons");
  //pt3->SetTextFont(42);
  //pt3->SetTextSize(0.02);
  //pt3->Draw();

  cNP->SetLeftMargin(0.2);
  cNP->Print("NrecNgenE_nonphoton_IDR.pdf");
  cNP->Print("NrecNgenE_nonphoton_IDR.C");
}
