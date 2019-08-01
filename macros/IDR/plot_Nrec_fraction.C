//#define __l5__
#define __s5__

void plot_Nrec_fraction()
{
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  gROOT->LoadMacro(styleMacroPath.Data());

#ifdef __l5__
  TString filePath(topDirPath+"run_l5/plots/plots.root");
  TFile* fin = new TFile(filePath.Data());
#endif
#ifdef __s5__
  TString filePath(topDirPath+"run_s5/plots/plots.root");
  TFile* fin = new TFile(filePath.Data());
#endif
  TNtuple* SignalPhoton_nungLR = static_cast<TNtuple*>(fin->Get("SignalPhoton_nungLR"));
  TNtuple* SignalPhoton_nungRL = static_cast<TNtuple*>(fin->Get("SignalPhoton_nungRL"));
  SignalPhoton_nungLR->Draw("fabs(TMath::Cos(gen_theta))>>h0LR(50,0,1)","nrec==0&&gen_e>2&&isMCSignalEvt");
  SignalPhoton_nungLR->Draw("fabs(TMath::Cos(gen_theta))>>h1LR(50,0,1)","nrec==1&&gen_e>2&&isMCSignalEvt");
  SignalPhoton_nungLR->Draw("fabs(TMath::Cos(gen_theta))>>h2LR(50,0,1)","nrec>1&&gen_e>2&&isMCSignalEvt");
  SignalPhoton_nungLR->Draw("fabs(TMath::Cos(gen_theta))>>hallLR(50,0,1)","gen_e>2&&isMCSignalEvt");
  SignalPhoton_nungRL->Draw("fabs(TMath::Cos(gen_theta))>>h0RL(50,0,1)","nrec==0&&gen_e>2&&isMCSignalEvt");
  SignalPhoton_nungRL->Draw("fabs(TMath::Cos(gen_theta))>>h1RL(50,0,1)","nrec==1&&gen_e>2&&isMCSignalEvt");
  SignalPhoton_nungRL->Draw("fabs(TMath::Cos(gen_theta))>>h2RL(50,0,1)","nrec>1&&gen_e>2&&isMCSignalEvt");
  SignalPhoton_nungRL->Draw("fabs(TMath::Cos(gen_theta))>>hallRL(50,0,1)","gen_e>2&&isMCSignalEvt");

  TH1D* h0LR = static_cast<TH1D*>(gROOT->FindObject("h0LR"));
  TH1D* h1LR = static_cast<TH1D*>(gROOT->FindObject("h1LR"));
  TH1D* h2LR = static_cast<TH1D*>(gROOT->FindObject("h2LR"));
  TH1D* hallLR = static_cast<TH1D*>(gROOT->FindObject("hallLR"));
  TH1D* h0RL = static_cast<TH1D*>(gROOT->FindObject("h0RL"));
  TH1D* h1RL = static_cast<TH1D*>(gROOT->FindObject("h1RL"));
  TH1D* h2RL = static_cast<TH1D*>(gROOT->FindObject("h2RL"));
  TH1D* hallRL = static_cast<TH1D*>(gROOT->FindObject("hallRL"));

  TH1D* h0 = new TH1D("h0","",50,0,1);
  TH1D* h1 = new TH1D("h1","",50,0,1);
  TH1D* h2 = new TH1D("h2","",50,0,1);
  TH1D* hall = new TH1D("hall","",50,0,1);


  h0->Add(h0LR);
  h0->Add(h0RL);
  h1->Add(h1LR);
  h1->Add(h1RL);
  h2->Add(h2LR);
  h2->Add(h2RL);
  hall->Add(hallLR);
  hall->Add(hallRL);

  h0->Divide(hall);
  h1->Divide(hall);
  h2->Divide(hall);

  h0->SetFillColor(3);
  h1->SetFillColor(2);
  h2->SetFillColor(4);

  TCanvas* c = new TCanvas("c","",600,600);
  TH1D* axis = new TH1D("axis",";cos#theta_{MC};",100,0,1);
  axis->SetMaximum(1);
  axis->SetMinimum(0.97);
  THStack* hs = new THStack("hs","");
  hs->Add(h1);
  hs->Add(h0);
  hs->Add(h2);
  //h1LR->Draw();
  //h2LR->Draw();
  //h0LR->Draw("same");
  axis->Draw();
  hs->Draw("same");

  c->RedrawAxis();
  TLine* l = new TLine(0.8,0.97,0.8,1);
  l->SetLineColor(16);
  l->Draw("same");
  l = new TLine(0.6,0.97,0.6,1);
  l->SetLineColor(16);
  l->Draw("same");
  l = new TLine(0.4,0.97,0.4,1);
  l->SetLineColor(16);
  l->Draw("same");
  l = new TLine(0.2,0.97,0.2,1);
  l->SetLineColor(16);
  l->Draw("same");

  TLegend *leg = new TLegend(0.25,0.65,0.6,0.45);
  leg->SetTextFont(62);
  leg->SetTextSize(0.03); 
  leg->SetTextAlign(12);
#ifdef __l5__
  leg->SetHeader("IDR-L","C");
#endif
#ifdef __s5__
  leg->SetHeader("IDR-S","C");
#endif
  leg->AddEntry(h2,"Nrec>1","f"); 
  leg->AddEntry(h0,"Nrec=0","f"); 
  leg->AddEntry(h1,"Nrec=1","f"); 
  leg->Draw();
  
#ifdef __l5__
  c->Print("Nrec_fraction_l5.pdf");
  c->Print("Nrec_fraction_l5.C");
#endif
#ifdef __s5__
  c->Print("Nrec_fraction_s5.pdf");
  c->Print("Nrec_fraction_s5.C");
#endif

}
