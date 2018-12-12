{
TCanvas *c = new TCanvas("calbyp");
c->SetWindowSize(650,400);
ildStyle->SetOptStat(0);
ildStyle->SetTitleOffset(1.2,"x");
ildStyle->SetTitleOffset(0.85,"y");

// number of bins and plotted range
double n_bins 		= 290;
double leftborder 	= -10;
double rightborder 	= 280;

TFile *f1 = new TFile("../step3/vv_LR_PT_origin.root");
TTree* vv_LR_tree = (TTree*)f1.Get("pt_electron_after_signaldef");

TH1F *h1 = new TH1F("h1","simple_histo",n_bins,leftborder,rightborder);
 vv_LR_tree->Draw("pT_e >> h1"); 
 
TFile *f1r = new TFile("../step3/vv_RL_PT_origin.root"); // root file created from lumi.dat using readascii.C
TTree* vv_RL_tree = (TTree*)f1r.Get("pt_electron_after_signaldef");
 
TH1F *h1r = new TH1F("h1r","simple_histo",n_bins,leftborder,rightborder);
 vv_RL_tree->Draw("pT_e >> h1r"); 

TFile *f2 = new TFile("../step3/bhabhas_LL_PT_origin.root");
TTree* ee_LL_tree = (TTree*)f2.Get("pt_electron_after_signaldef");
TH1F *h2 = new TH1F("h2","simple_histo",n_bins,leftborder,rightborder);
 ee_LL_tree->Draw("pT_e >> h2");

TFile *f2lr = new TFile("../step3/bhabhas_LR_PT_origin.root");
TTree* ee_LR_tree = (TTree*)f2lr.Get("pt_electron_after_signaldef");
TH1F *h2lr = new TH1F("h2lr","simple_histo",n_bins,leftborder,rightborder);
 ee_LR_tree->Draw("pT_e >> h2lr");

TFile *f2rl = new TFile("../step3/bhabhas_RL_PT_origin.root");
TTree* ee_RL_tree = (TTree*)f2rl.Get("pt_electron_after_signaldef");
TH1F *h2rl = new TH1F("h2rl","simple_histo",n_bins,leftborder,rightborder);
 ee_RL_tree->Draw("pT_e >> h2rl");
 
TFile *f2rr = new TFile("../step3/bhabhas_RR_PT_origin.root");
TTree* ee_RR_tree = (TTree*)f2rr.Get("pt_electron_after_signaldef");
TH1F *h2rr = new TH1F("h2rr","simple_histo",n_bins,leftborder,rightborder);
 ee_RR_tree->Draw("pT_e >> h2rr");

THStack *hs = new THStack("hs","");

//TH1F *h1 = new TH1F("h1","simple_histo",n_bins,leftborder,rightborder);
// t5->Draw("pT >> h1"); 

//TH1F *h2 = new TH1F("h2","simple_histo",n_bins,leftborder,rightborder);
// t10->Draw("pT >> h2"); 

h1->SetFillColor(kSpring-7);
h1->SetLineWidth(0);
h1->SetLineColor(kSpring-7);
h1->SetMarkerColor(2);
h1->SetMarkerStyle(21);
h1->SetMarkerSize(0.6);
h1->Scale(500*0.25/524.9); // nunug LR; 0.25 because we look at unpolarised; 500 because it's for 500 fb-1 and the remaining number is the MC luminosity - which is different from sample to sample.

h1r->SetFillColor(kSpring-7);
h1r->SetLineWidth(0);
h1r->SetLineColor(kSpring-7);
h1r->SetMarkerColor(2);
h1r->SetMarkerStyle(21);
h1r->SetMarkerSize(0.6);
h1r->Scale(500*0.25/599.4);

h2->SetFillColor(kOrange+6); 
h2->SetLineWidth(0);
h2->SetLineColor(kOrange+6);
h2->SetMarkerStyle(21);
h2->SetMarkerColor(8);
h2->SetMarkerSize(0.6);
h2->Scale(500*0.25/24.16); // bhabhas LL

h2lr->SetFillColor(kOrange+6); 
h2lr->SetLineWidth(0);
h2lr->SetLineColor(kOrange+6);
h2lr->SetMarkerStyle(21);
h2lr->SetMarkerColor(8);
h2lr->SetMarkerSize(0.6);
h2lr->Scale(500*0.25/22.5); // bhabhas LR

h2rl->SetFillColor(kOrange+6);
h2rl->SetLineWidth(0);
h2rl->SetLineColor(kOrange+6);
h2rl->SetMarkerStyle(21);
h2rl->SetMarkerColor(8);
h2rl->SetMarkerSize(0.6);
h2rl->Scale(500*0.25/22.99); // bhabhas RL

h2rr->SetFillColor(kOrange+6);
h2rr->SetLineWidth(0);
h2rr->SetLineColor(kOrange+6);
h2rr->SetMarkerStyle(21);
h2rr->SetMarkerColor(8);
h2rr->SetMarkerSize(0.6);
h2rr->Scale(500*0.25/24.16); // bhabhas RR

h2->Add(h2lr);
h2->Add(h2rl);
h2->Add(h2rr);

hs->Add(h1);
hs->Add(h1r);
hs->Add(h2);
//hs->Add(h2lr);
//hs->Add(h2rl);
//hs->Add(h2rr);

hs->Draw();
hs->SetMaximum(1000000000);
hs->SetMinimum(1);
hs->Draw();


hs->GetXaxis()->SetTitle("p_{T} [GeV]");
hs->GetYaxis()->SetTitle("# particles  [1 / 500fb^{-1} GeV]");

  
/*TLine *l = new TLine(3,0,3,250100000); 
l->SetLineColor(2); 
l->SetLineWidth(3);
l->SetLineStyle(1);
l->Draw();*/


leg = new TLegend(0.23,0.65,0.61,0.9);
leg->SetHeader("Transverse momenta of electrons");
leg->AddEntry(h2,"Bhabha scattering + N#gamma","f");
leg->AddEntry(h1,"neutrino pairs + N#gamma","f");
leg->SetTextFont(42);
 leg->SetTextSize(0.060);
leg->SetFillColor(0);
 leg->SetBorderSize(0);
 leg->SetMargin(0.18);
 leg->Draw();
 
ILDleg = new TLegend(0.855,0.85,0.91,0.91);
ILDleg->SetTextFont(41);
ILDleg->SetHeader(" ILD ");
ILDleg->SetTextSize(0.045);
ILDleg->SetFillColor(kCyan-10);
ILDleg->Draw();

c->SetLogy();  // log scale
c->Update();
c->Modified();
}                                                                                                                                           
