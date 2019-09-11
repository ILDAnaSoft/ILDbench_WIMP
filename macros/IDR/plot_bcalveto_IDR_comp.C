#include "macros/util.C"

void plot_bcalveto_IDR_comp()
{
  UpdateMetaData(); // see util.C

  TString fnamel5 = "run_l5/plots/plots_test.root";
  TString fnames5 = "run_s5/plots/plots_test_sum.root";
  TString labell5 = "IDR-L";
  TString labels5 = "IDR-S";

  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  gROOT->LoadMacro(styleMacroPath.Data());
  TCanvas* c = new TCanvas("c","",400,400);
  gPad->SetLogy();


  TFile* finl5 = new TFile(fnamel5.Data());
  TFile* fins5 = new TFile(fnames5.Data());

  float xs_nungLR = getXsec("nung.eL.pR");
  float xs_nungRL = getXsec("nung.eL.pR");
  float xs_bhabhangLL = getXsec("bhabhang.eL.pL");
  float xs_bhabhangLR = getXsec("bhabhang.eL.pR");
  float xs_bhabhangRL = getXsec("bhabhang.eR.pL");
  float xs_bhabhangRR = getXsec("bhabhang.eR.pR");

  const float L = 500.; 
  const float epol = 0.0;
  const float ppol = 0.0;
  enum POL { LL, LR, RL, RR };
  float pfrac[4]; // with luminocity sharing fraction.
  pfrac[LL] = 1. * L * (1-epol) * (1-ppol) / 4.;
  pfrac[LR] = 1. * L * (1-epol) * (1+ppol) / 4.;
  pfrac[RL] = 1. * L * (1+epol) * (1-ppol) / 4.;
  pfrac[RR] = 1. * L * (1+epol) * (1+ppol) / 4.;

  TH1F* hCutStats_l5_nungLR              = static_cast<TH1F*>(finl5->Get("hCutStats_nungLR"));
  TH1F* hCutStats_l5_nungRL              = static_cast<TH1F*>(finl5->Get("hCutStats_nungRL"));
  TH1F* hCutStats_l5_bhabhangLL          = static_cast<TH1F*>(finl5->Get("hCutStats_bhabhangLL"));
  TH1F* hCutStats_l5_bhabhangLR          = static_cast<TH1F*>(finl5->Get("hCutStats_bhabhangLR"));
  TH1F* hCutStats_l5_bhabhangRL          = static_cast<TH1F*>(finl5->Get("hCutStats_bhabhangRL"));
  TH1F* hCutStats_l5_bhabhangRR          = static_cast<TH1F*>(finl5->Get("hCutStats_bhabhangRR"));
  TH1F* hCutStats_s5_nungLR              = static_cast<TH1F*>(fins5->Get("hCutStats_nungLR"));
  TH1F* hCutStats_s5_nungRL              = static_cast<TH1F*>(fins5->Get("hCutStats_nungRL"));
  TH1F* hCutStats_s5_bhabhangLL          = static_cast<TH1F*>(fins5->Get("hCutStats_bhabhangLL"));
  TH1F* hCutStats_s5_bhabhangLR          = static_cast<TH1F*>(fins5->Get("hCutStats_bhabhangLR"));
  TH1F* hCutStats_s5_bhabhangRL          = static_cast<TH1F*>(fins5->Get("hCutStats_bhabhangRL"));
  TH1F* hCutStats_s5_bhabhangRR          = static_cast<TH1F*>(fins5->Get("hCutStats_bhabhangRR"));
  int n_l5_nung_LR     = hCutStats_l5_nungLR->GetBinContent(1); // nentries in "nocut" bin
  int n_l5_nung_RL     = hCutStats_l5_nungRL->GetBinContent(1); // nentries in "nocut" bin
  int n_l5_bhabhang_LL = hCutStats_l5_bhabhangLL->GetBinContent(1); // nentries in "nocut" bin
  int n_l5_bhabhang_LR = hCutStats_l5_bhabhangLR->GetBinContent(1); // nentries in "nocut" bin
  int n_l5_bhabhang_RL = hCutStats_l5_bhabhangRL->GetBinContent(1); // nentries in "nocut" bin
  int n_l5_bhabhang_RR = hCutStats_l5_bhabhangRR->GetBinContent(1); // nentries in "nocut" bin
  int n_s5_nung_LR     = hCutStats_s5_nungLR->GetBinContent(1); // nentries in "nocut" bin
  int n_s5_nung_RL     = hCutStats_s5_nungRL->GetBinContent(1); // nentries in "nocut" bin
  int n_s5_bhabhang_LL = hCutStats_s5_bhabhangLL->GetBinContent(1); // nentries in "nocut" bin
  int n_s5_bhabhang_LR = hCutStats_s5_bhabhangLR->GetBinContent(1); // nentries in "nocut" bin
  int n_s5_bhabhang_RL = hCutStats_s5_bhabhangRL->GetBinContent(1); // nentries in "nocut" bin
  int n_s5_bhabhang_RR = hCutStats_s5_bhabhangRR->GetBinContent(1); // nentries in "nocut" bin

  float w_l5_nung_LR     = xs_nungLR * pfrac[LR] /     n_l5_nung_LR;
  float w_l5_nung_RL     = xs_nungRL * pfrac[RL] /     n_l5_nung_RL;
  float w_l5_bhabhang_LL = xs_bhabhangLL * pfrac[LL] / n_l5_bhabhang_LL;
  float w_l5_bhabhang_LR = xs_bhabhangLR * pfrac[LR] / n_l5_bhabhang_LR;
  float w_l5_bhabhang_RL = xs_bhabhangRL * pfrac[RL] / n_l5_bhabhang_RL;
  float w_l5_bhabhang_RR = xs_bhabhangRR * pfrac[RR] / n_l5_bhabhang_RR;
  float w_s5_nung_LR     = xs_nungLR * pfrac[LR] /     n_s5_nung_LR;
  float w_s5_nung_RL     = xs_nungRL * pfrac[RL] /     n_s5_nung_RL;
  float w_s5_bhabhang_LL = xs_bhabhangLL * pfrac[LL] / n_s5_bhabhang_LL;
  float w_s5_bhabhang_LR = xs_bhabhangLR * pfrac[LR] / n_s5_bhabhang_LR;
  float w_s5_bhabhang_RL = xs_bhabhangRL * pfrac[RL] / n_s5_bhabhang_RL;
  float w_s5_bhabhang_RR = xs_bhabhangRR * pfrac[RR] / n_s5_bhabhang_RR;

  TH1F* hNBcalClusters1ISR_l5_nungLR       = static_cast<TH1F*>(finl5->Get("hNBcalClusters1ISR_nungLR"));
  TH1F* hNBcalClusters1ISR_l5_nungRL       = static_cast<TH1F*>(finl5->Get("hNBcalClusters1ISR_nungRL"));
  TH1F* hNBcalClusters1ISR_l5_nungSum      = new TH1F("hNBcalClusters1ISR_l5_nungSum",";# of BeamCal clusters;Events",6,0,6);
  hNBcalClusters1ISR_l5_nungSum->Add(hNBcalClusters1ISR_l5_nungLR,w_l5_nung_LR);
  hNBcalClusters1ISR_l5_nungSum->Add(hNBcalClusters1ISR_l5_nungRL,w_l5_nung_RL);
  TH1F* hNBcalClustersMultiISR_l5_nungLR   = static_cast<TH1F*>(finl5->Get("hNBcalClustersMultiISR_nungLR"));
  TH1F* hNBcalClustersMultiISR_l5_nungRL   = static_cast<TH1F*>(finl5->Get("hNBcalClustersMultiISR_nungRL"));
  TH1F* hNBcalClustersMultiISR_l5_nungSum      = new TH1F("hNBcalClustersMultiISR_l5_nungSum",";# of BeamCal clusters;Events",6,0,6);
  hNBcalClustersMultiISR_l5_nungSum->Add(hNBcalClustersMultiISR_l5_nungLR,w_l5_nung_LR);
  hNBcalClustersMultiISR_l5_nungSum->Add(hNBcalClustersMultiISR_l5_nungRL,w_l5_nung_RL);
  TH1F* hNBcalClusters_l5_bhabhangLL         = static_cast<TH1F*>(finl5->Get("hNBcalClusters_bhabhangLL"));
  TH1F* hNBcalClusters_l5_bhabhangLR         = static_cast<TH1F*>(finl5->Get("hNBcalClusters_bhabhangLR"));
  TH1F* hNBcalClusters_l5_bhabhangRL         = static_cast<TH1F*>(finl5->Get("hNBcalClusters_bhabhangRL"));
  TH1F* hNBcalClusters_l5_bhabhangRR         = static_cast<TH1F*>(finl5->Get("hNBcalClusters_bhabhangRR"));
  TH1F* hNBcalClusters_l5_bhabhangSum        = new TH1F("hNBcalClusters_l5_bhabhangSum",";# of BeamCal clusters;Events",6,0,6);
  hNBcalClusters_l5_bhabhangSum->Add(hNBcalClusters_l5_bhabhangLL,w_l5_bhabhang_LL); 
  hNBcalClusters_l5_bhabhangSum->Add(hNBcalClusters_l5_bhabhangLR,w_l5_bhabhang_LR); 
  hNBcalClusters_l5_bhabhangSum->Add(hNBcalClusters_l5_bhabhangRL,w_l5_bhabhang_RL); 
  hNBcalClusters_l5_bhabhangSum->Add(hNBcalClusters_l5_bhabhangRR,w_l5_bhabhang_RR); 

  TH1F* hNBcalClusters1ISR_s5_nungLR       = static_cast<TH1F*>(fins5->Get("hNBcalClusters1ISR_nungLR"));
  TH1F* hNBcalClusters1ISR_s5_nungRL       = static_cast<TH1F*>(fins5->Get("hNBcalClusters1ISR_nungRL"));
  TH1F* hNBcalClusters1ISR_s5_nungSum      = new TH1F("hNBcalClusters1ISR_s5_nungSum",";# of BeamCal clusters;Events",6,0,6);
  hNBcalClusters1ISR_s5_nungSum->Add(hNBcalClusters1ISR_s5_nungLR,w_s5_nung_LR);
  hNBcalClusters1ISR_s5_nungSum->Add(hNBcalClusters1ISR_s5_nungRL,w_s5_nung_RL);
  TH1F* hNBcalClustersMultiISR_s5_nungLR   = static_cast<TH1F*>(fins5->Get("hNBcalClustersMultiISR_nungLR"));
  TH1F* hNBcalClustersMultiISR_s5_nungRL   = static_cast<TH1F*>(fins5->Get("hNBcalClustersMultiISR_nungRL"));
  TH1F* hNBcalClustersMultiISR_s5_nungSum      = new TH1F("hNBcalClustersMultiISR_s5_nungSum",";# of BeamCal clusters;Events",6,0,6);
  hNBcalClustersMultiISR_s5_nungSum->Add(hNBcalClustersMultiISR_s5_nungLR,w_s5_nung_LR);
  hNBcalClustersMultiISR_s5_nungSum->Add(hNBcalClustersMultiISR_s5_nungRL,w_s5_nung_RL);
  TH1F* hNBcalClusters_s5_bhabhangLL         = static_cast<TH1F*>(fins5->Get("hNBcalClusters_bhabhangLL"));
  TH1F* hNBcalClusters_s5_bhabhangLR         = static_cast<TH1F*>(fins5->Get("hNBcalClusters_bhabhangLR"));
  TH1F* hNBcalClusters_s5_bhabhangRL         = static_cast<TH1F*>(fins5->Get("hNBcalClusters_bhabhangRL"));
  TH1F* hNBcalClusters_s5_bhabhangRR         = static_cast<TH1F*>(fins5->Get("hNBcalClusters_bhabhangRR"));
  TH1F* hNBcalClusters_s5_bhabhangSum        = new TH1F("hNBcalClusters_s5_bhabhangSum",";# of BeamCal clusters;Events",6,0,6);
  hNBcalClusters_s5_bhabhangSum->Add(hNBcalClusters_s5_bhabhangLL,w_s5_bhabhang_LL); 
  hNBcalClusters_s5_bhabhangSum->Add(hNBcalClusters_s5_bhabhangLR,w_s5_bhabhang_LR); 
  hNBcalClusters_s5_bhabhangSum->Add(hNBcalClusters_s5_bhabhangRL,w_s5_bhabhang_RL); 
  hNBcalClusters_s5_bhabhangSum->Add(hNBcalClusters_s5_bhabhangRR,w_s5_bhabhang_RR); 

  hNBcalClusters1ISR_l5_nungSum->SetLineColor(kBlue);
  hNBcalClusters1ISR_l5_nungSum->SetLineWidth(2);
  hNBcalClustersMultiISR_l5_nungSum->SetLineColor(kBlue);
  hNBcalClustersMultiISR_l5_nungSum->SetLineWidth(2);
  hNBcalClusters_l5_bhabhangSum->SetLineColor(kBlue);
  hNBcalClusters_l5_bhabhangSum->SetLineWidth(2);

  hNBcalClusters1ISR_s5_nungSum->SetLineColor(kRed);
  hNBcalClusters1ISR_s5_nungSum->SetLineStyle(4);
  hNBcalClustersMultiISR_s5_nungSum->SetLineColor(kRed);
  hNBcalClustersMultiISR_s5_nungSum->SetLineStyle(4);
  hNBcalClusters_s5_bhabhangSum->SetLineColor(kRed);
  hNBcalClusters_s5_bhabhangSum->SetLineStyle(4);

  hNBcalClusters1ISR_l5_nungSum->Draw();
  hNBcalClusters1ISR_s5_nungSum->Draw("same");

  TLegend* leg_c = new TLegend(0.71,0.60,0.95,0.70);
  leg_c->SetTextSize(0.04);
  leg_c->SetTextFont(42);
  leg_c->AddEntry(hNBcalClusters1ISR_l5_nungSum,     "IDR-L"           ,"l");
  leg_c->AddEntry(hNBcalClusters1ISR_s5_nungSum,     "IDR-S"           ,"l");
  leg_c->Draw();
  TLatex *tex = new TLatex();
  tex->SetTextSize(0.05);
  tex->DrawLatexNDC(0.57,0.8,"#scale[1.5]{#font[62]{ILD}} #font[42]{preliminary}");
  tex->SetTextSize(0.05);
  tex->DrawLatexNDC(0.73,0.72,"#nu#nu+1#gamma");

  c->SetLeftMargin(0.18);
  //c11->SetRightMargin(0.05);
  c->SetTopMargin(0.05);
  c->SetBottomMargin(0.15);

  c->RedrawAxis(); 
  c->Update(); 

  TCanvas* c2 = new TCanvas("c2","",400,400);
  gPad->SetLogy();
  hNBcalClustersMultiISR_l5_nungSum->Draw();
  hNBcalClustersMultiISR_s5_nungSum->Draw("same");
  leg_c->Draw();
  tex->SetTextSize(0.05);
  tex->DrawLatexNDC(0.57,0.8,"#scale[1.5]{#font[62]{ILD}} #font[42]{preliminary}");
  tex->SetTextSize(0.05);
  tex->DrawLatexNDC(0.73,0.72,"#nu#nu+N#gamma");
  c2->SetLeftMargin(0.18);
  c2->SetTopMargin(0.05);
  c2->SetBottomMargin(0.15);
  c2->RedrawAxis(); 
  c2->Update(); 

  TCanvas* c3 = new TCanvas("c3","",400,400);
  gPad->SetLogy();
  hNBcalClusters_l5_bhabhangSum->Draw();
  hNBcalClusters_s5_bhabhangSum->Draw("same");
  leg_c->Draw();
  tex->DrawLatexNDC(0.57,0.8,"#scale[1.5]{#font[62]{ILD}} #font[42]{preliminary}");
  tex->SetTextSize(0.05);
  tex->DrawLatexNDC(0.7,0.73,"e^{+}e^{-}+N#gamma");
  c3->SetLeftMargin(0.18);
  c3->SetTopMargin(0.05);
  c3->SetBottomMargin(0.15);
  c3->RedrawAxis(); 
  c3->Update(); 
  TString pdfname = "bcalveto_vv1g_comp.pdf";
  TString macroname = "bcalveto_vv1g_comp.C";
  c->Print(pdfname.Data());
  c->Print(macroname.Data());
  TString pdfname2 = "bcalveto_vvNg_comp.pdf";
  TString macroname2 = "bcalveto_vvNg_comp.C";
  c2->Print(pdfname2.Data());
  c2->Print(macroname2.Data());
  TString pdfname3 = "bcalveto_eeNg_comp.pdf";
  TString macroname3 = "bcalveto_eeNg_comp.C";
  c3->Print(pdfname3.Data());
  c3->Print(macroname3.Data());
}
