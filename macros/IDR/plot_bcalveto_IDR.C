#include "../util.C"

void plot(TString fname = "run_l5/plots/plots.root", TString label = "output")
{
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  gROOT->LoadMacro(styleMacroPath.Data());
  TCanvas* c11 = new TCanvas("c11","",400,400);
  gPad->SetLogy();


  TFile* fin = new TFile(fname.Data());

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
  TH1F* hNBcalClusters_bhabhangLL         = static_cast<TH1F*>(fin->Get("hNBcalClusters_bhabhangLL"));
  TH1F* hNBcalClusters_bhabhangLR         = static_cast<TH1F*>(fin->Get("hNBcalClusters_bhabhangLR"));
  TH1F* hNBcalClusters_bhabhangRL         = static_cast<TH1F*>(fin->Get("hNBcalClusters_bhabhangRL"));
  TH1F* hNBcalClusters_bhabhangRR         = static_cast<TH1F*>(fin->Get("hNBcalClusters_bhabhangRR"));
  TH1F* hNBcalClusters_bhabhangSum        = new TH1F("hNBcalClusters_bhabhangSum",";# of BCal clusters;",6,0,6);
  hNBcalClusters_bhabhangSum->Add(hNBcalClusters_bhabhangLL,w_bhabhang_LL); 
  hNBcalClusters_bhabhangSum->Add(hNBcalClusters_bhabhangLR,w_bhabhang_LR); 
  hNBcalClusters_bhabhangSum->Add(hNBcalClusters_bhabhangRL,w_bhabhang_RL); 
  hNBcalClusters_bhabhangSum->Add(hNBcalClusters_bhabhangRR,w_bhabhang_RR); 

  hNBcalClusters1ISR_nungSum->SetFillColor(kYellow+1);
  hNBcalClustersMultiISR_nungSum->SetFillColor(kGreen+3);
  hNBcalClusters_bhabhangSum->SetFillColor(kOrange+6);

  // stacked version. Note that MultiISR means # of ISR to be more than 1.
  THStack* hNBcalClusters_all = new THStack("hNBcalClusters_all",";Number of BCal clusters;Events");
  hNBcalClusters_all->SetMaximum(1e10);
  hNBcalClusters_all->SetMinimum(1);
  hNBcalClusters_all->Add(hNBcalClusters_bhabhangSum);
  hNBcalClusters_all->Add(hNBcalClustersMultiISR_nungSum);
  hNBcalClusters_all->Add(hNBcalClusters1ISR_nungSum);
  hNBcalClusters_all->Draw(); 
  hNBcalClusters_all->GetYaxis()->SetTitleOffset(1.3);
  TLegend* leg_c11_head = new TLegend(0.5,0.85,0.9,0.9);
  leg_c11_head->SetTextSize(0.05);
  leg_c11_head->SetTextFont(42);
  //leg_c11_head->SetHeader("Number of BeamCal clusters");
  leg_c11_head->SetFillStyle(0);
  leg_c11_head->Draw();
  TLegend* leg_c11 = new TLegend(0.61,0.60,0.86,0.90);
  leg_c11->SetTextSize(0.04);
  leg_c11->SetTextFont(42);
  leg_c11->AddEntry(hNBcalClusters1ISR_nungSum,     "#nu#nu+1#gamma"           ,"f");
  leg_c11->AddEntry(hNBcalClustersMultiISR_nungSum, "#nu#nu+N#gamma (N>1)"     ,"f");
  leg_c11->AddEntry(hNBcalClusters_bhabhangSum,     "e^{+}e^{-}+N#gamma (N>0)" ,"f");
  leg_c11->Draw();

  TLatex *tex = new TLatex();
  tex->SetTextSize(0.05);
  tex->DrawLatexNDC(0.24,0.8,"#scale[1.5]{#font[62]{ILD}} #font[42]{preliminary}");

  tex->SetTextSize(0.05);
  tex->DrawLatexNDC(0.24,0.75,label);

  c11->SetLeftMargin(0.18);
  //c11->SetRightMargin(0.05);
  c11->SetTopMargin(0.05);
  c11->SetBottomMargin(0.15);

  c11->RedrawAxis(); 
  c11->Update(); 
  TString pdfname = "bcalveto_" + label + ".pdf";
  TString macroname = "bcalveto_" + label + ".root";
  c11->Print(pdfname.Data());
  c11->Print(macroname.Data());
}

void plot_bcalveto_IDR()
{
  UpdateMetaData(); // see util.C
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString filePath_l5(topDirPath+"run_l5/plots/plots.root");
  TString filePath_s5(topDirPath+"run_s5/plots/plots.root");
  plot(filePath_l5.Data(),"IDR-L");
  plot(filePath_s5.Data(),"IDR-S");
}
