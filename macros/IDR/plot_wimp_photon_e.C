void plot_wimp_photon_e()
{
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  gROOT->LoadMacro(styleMacroPath.Data());
  TCanvas* c = new TCanvas("c","",600,400);
  gPad->SetLogy();

  TFile* fin_vv1g = new TFile("plots_test.root");
  //TFile* fin_wimp = new TFile("run_l5/plots/outputs/output_mass200_epol-0.8_ppol0.3_op0.root");
  TFile* fin_wimp = new TFile("run_l5/plots/outputs_lambda3000GeV/output_mass10_epol-0.8_ppol0.3_op0.root");
 
  TNtuple* SignalEvent_nungLR = static_cast<TNtuple*>(fin_vv1g->Get("SignalEvent_nungLR")); 
  TNtuple* SignalEvent_nungRL = static_cast<TNtuple*>(fin_vv1g->Get("SignalEvent_nungRL")); 
  TH1D* hE_wimp = static_cast<TH1D*>(fin_wimp->Get("hE_wimp"));
  hE_wimp->SetMarkerStyle(20);
  hE_wimp->SetMarkerSize(0.6);

  TH1D* hL = new TH1D("hL","",260,0,260);
  TH1D* hR = new TH1D("hR","",260,0,260);
  SignalEvent_nungLR->Draw("e>>hL");
  SignalEvent_nungRL->Draw("e>>hR");
  hL->SetTitle(";E_{#gamma} [GeV];Events");
  hL->SetLineColor(2);
  hR->SetLineColor(4);
  hE_wimp->SetMarkerColor(8);
  hE_wimp->SetLineColor(8);
  hL->Draw();
  hL->SetMaximum(1e10);
  hL->SetMinimum(1);
  hR->Draw("same");
  hE_wimp->Draw("same");

  hL->SetStats(0);
  TLegend* leg = new TLegend(0.16,0.60,0.89,0.90);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.036);
  leg->SetTextFont(42);
  leg->AddEntry(hL,     "#nu#nu+N#gamma, (Pe^{-},Pe^{+})=(-1.0,+1.0), L=600fb^{-1}","l");
  leg->AddEntry(hR,     "#nu#nu+N#gamma, (Pe^{-},Pe^{+})=(+1.0,-1.0), L=600fb^{-1}","l");
  //leg->AddEntry(hE_wimp, "#splitline{Reweighted for WIMP (M_{#chi}=200GeV, #Lambda=3TeV, Vector op.),}{(Pe^{-},Pe^{+})=(-0.8,+0.3), L=500fb^{-1}}" ,"lp");
  leg->AddEntry(hE_wimp, "#splitline{Reweighted for WIMP (M_{#chi}=10GeV, #Lambda=3TeV, Vector op.),}{(Pe^{-},Pe^{+})=(-0.8,+0.3), L=500fb^{-1}}" ,"lp");
  leg->Draw();

}
