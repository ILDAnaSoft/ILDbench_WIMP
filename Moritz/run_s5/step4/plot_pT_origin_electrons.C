{
TCanvas *c = new TCanvas("calbyp");
c->SetWindowSize(650,600);
ildStyle->SetOptStat(0);
ildStyle->SetTitleOffset(1.2,"x");
ildStyle->SetTitleOffset(1.4,"y");
ildStyle->SetLabelSize(0.04,"xyz");
ildStyle->SetTitleSize(0.045,"xyz");

// number of bins and plotted range
double n_bins 		= 290;
double leftborder 	= -10;
double rightborder 	= 280;

TFile *f1 = new TFile("../step3/vv_LR_PT_origin.root");
TTree* vv_LR_tree_o = (TTree*)f1.Get("electronPTs_from_overlay");
TTree* vv_LR_tree_p = (TTree*)f1.Get("electronPTs_from_MEphotons");
TTree* vv_LR_tree_r = (TTree*)f1.Get("electronPTs_from_rest");

TH1F *h1_o = new TH1F("h1_o","simple_histo",n_bins,leftborder,rightborder);
 vv_LR_tree_o->Draw("pt_overlay >> h1_o");


TH1F *h1_p = new TH1F("h1_p","simple_histo",n_bins,leftborder,rightborder);
 vv_LR_tree_p->Draw("pt_MEp >> h1_p");

 
TH1F *h1_r = new TH1F("h1_r","simple_histo",n_bins,leftborder,rightborder);
 vv_LR_tree_r->Draw("pt_other >> h1_r");

 
TFile *f1r = new TFile("../step3/vv_RL_PT_origin.root"); // root file created from lumi.dat using readascii.C
TTree* vv_RL_tree_o = (TTree*)f1r.Get("electronPTs_from_overlay");
TTree* vv_RL_tree_p = (TTree*)f1r.Get("electronPTs_from_MEphotons");
TTree* vv_RL_tree_r = (TTree*)f1r.Get("electronPTs_from_rest");


TH1F *h1r_o = new TH1F("h1r_o","simple_histo",n_bins,leftborder,rightborder);
 vv_RL_tree_o->Draw("pt_overlay >> h1r_o");


TH1F *h1r_p = new TH1F("h1r_p","simple_histo",n_bins,leftborder,rightborder);
 vv_RL_tree_p->Draw("pt_MEp >> h1r_p");

 
TH1F *h1r_r = new TH1F("h1r_r","simple_histo",n_bins,leftborder,rightborder);
 vv_RL_tree_r->Draw("pt_other >> h1r_r");


TFile *f2 = new TFile("../step3/bhabhas_LL_PT_origin.root");
TTree* ee_LL_tree_o = (TTree*)f2.Get("electronPTs_from_overlay");
TTree* ee_LL_tree_p = (TTree*)f2.Get("electronPTs_from_MEphotons");
TTree* ee_LL_tree_r = (TTree*)f2.Get("electronPTs_from_rest");

TH1F *h2_o = new TH1F("h2_o","simple_histo",n_bins,leftborder,rightborder);
 ee_LL_tree_o->Draw("pt_overlay >> h2_o");

TH1F *h2_p = new TH1F("h2_p","simple_histo",n_bins,leftborder,rightborder);
 ee_LL_tree_p->Draw("pt_MEp >> h2_p");
 
TH1F *h2_r = new TH1F("h2_r","simple_histo",n_bins,leftborder,rightborder);
 ee_LL_tree_r->Draw("pt_other >> h2_r");



TFile *f2lr = new TFile("../step3/bhabhas_LR_PT_origin.root");
TTree* ee_LR_tree_o = (TTree*)f2lr.Get("electronPTs_from_overlay");
TTree* ee_LR_tree_p = (TTree*)f2lr.Get("electronPTs_from_MEphotons");
TTree* ee_LR_tree_r = (TTree*)f2lr.Get("electronPTs_from_rest");

TH1F *h2lr_o = new TH1F("h2lr_o","simple_histo",n_bins,leftborder,rightborder);
 ee_LR_tree_o->Draw("pt_overlay >> h2lr_o");

TH1F *h2lr_p = new TH1F("h2lr_p","simple_histo",n_bins,leftborder,rightborder);
 ee_LR_tree_p->Draw("pt_MEp >> h2lr_p");
 
TH1F *h2lr_r = new TH1F("h2lr_r","simple_histo",n_bins,leftborder,rightborder);
 ee_LR_tree_r->Draw("pt_other >> h2lr_r");


TFile *f2rl = new TFile("../step3/bhabhas_RL_PT_origin.root");
TTree* ee_RL_tree_o = (TTree*)f2rl.Get("electronPTs_from_overlay");
TTree* ee_RL_tree_p = (TTree*)f2rl.Get("electronPTs_from_MEphotons");
TTree* ee_RL_tree_r = (TTree*)f2rl.Get("electronPTs_from_rest");

TH1F *h2rl_o = new TH1F("h2rl_o","simple_histo",n_bins,leftborder,rightborder);
 ee_RL_tree_o->Draw("pt_overlay >> h2rl_o");

TH1F *h2rl_p = new TH1F("h2rl_p","simple_histo",n_bins,leftborder,rightborder);
 ee_RL_tree_p->Draw("pt_MEp >> h2rl_p");
 
TH1F *h2rl_r = new TH1F("h2rl_r","simple_histo",n_bins,leftborder,rightborder);
 ee_RL_tree_r->Draw("pt_other >> h2rl_r");
 
 
TFile *f2rr = new TFile("../step3/bhabhas_RR_PT_origin.root");
TTree* ee_RR_tree_o = (TTree*)f2rr.Get("electronPTs_from_overlay");
TTree* ee_RR_tree_p = (TTree*)f2rr.Get("electronPTs_from_MEphotons");
TTree* ee_RR_tree_r = (TTree*)f2rr.Get("electronPTs_from_rest");
 
TH1F *h2rr_o = new TH1F("h2rr_o","simple_histo",n_bins,leftborder,rightborder);
 ee_RR_tree_o->Draw("pt_overlay >> h2rr_o");

TH1F *h2rr_p = new TH1F("h2rr_p","simple_histo",n_bins,leftborder,rightborder);
 ee_RR_tree_p->Draw("pt_MEp >> h2rr_p");
 
TH1F *h2rr_r = new TH1F("h2rr_r","simple_histo",n_bins,leftborder,rightborder);
 ee_RR_tree_r->Draw("pt_other >> h2rr_r");

THStack *hs = new THStack("hs","");

//TH1F *h1 = new TH1F("h1","simple_histo",n_bins,leftborder,rightborder);
// t5->Draw("pT >> h1"); 

//TH1F *h2 = new TH1F("h2","simple_histo",n_bins,leftborder,rightborder);
// t10->Draw("pT >> h2"); 

h1_o->SetFillColor(kYellow+2);
h1_o->SetLineWidth(0);
h1_o->SetLineColor(kYellow+2);
h1_o->SetMarkerColor(2);
h1_o->SetMarkerStyle(21);
h1_o->SetMarkerSize(0.6);
h1_o->Scale(500*0.25/524.9); // nunug LR; 0.25 because we look at unpolarised; 500 because it's for 500 fb-1 and the remaining number is the MC luminosity - which is different from sample to sample.

h1_p->SetFillColor(kAzure+6);
h1_p->SetLineWidth(0);
h1_p->SetLineColor(kAzure+6);
h1_p->SetMarkerColor(2);
h1_p->SetMarkerStyle(21);
h1_p->SetMarkerSize(0.6);
h1_p->Scale(500*0.25/524.9); // nunug LR

h1_r->SetFillColor(kGreen+3);
h1_r->SetLineWidth(0);
h1_r->SetLineColor(kGreen+3);
h1_r->SetMarkerColor(2);
h1_r->SetMarkerStyle(21);
h1_r->SetMarkerSize(0.6);
h1_r->Scale(500*0.25/524.9); // nunug LR


h1r_o->SetFillColor(kYellow+2);
h1r_o->SetLineWidth(0);
h1r_o->SetLineColor(kYellow+2);
h1r_o->SetMarkerColor(2);
h1r_o->SetMarkerStyle(21);
h1r_o->SetMarkerSize(0.6);
h1r_o->Scale(500*0.25/599.4);

h1r_p->SetFillColor(kAzure+6);
h1r_p->SetLineWidth(0);
h1r_p->SetLineColor(kAzure+6);
h1r_p->SetMarkerColor(2);
h1r_p->SetMarkerStyle(21);
h1r_p->SetMarkerSize(0.6);
h1r_p->Scale(500*0.25/599.4);

h1r_r->SetFillColor(kGreen+3);
h1r_r->SetLineWidth(0);
h1r_r->SetLineColor(kGreen+3);
h1r_r->SetMarkerColor(2);
h1r_r->SetMarkerStyle(21);
h1r_r->SetMarkerSize(0.6);
h1r_r->Scale(500*0.25/599.4);

h2_o->SetFillColor(kPink+8); 
h2_o->SetLineWidth(0);
h2_o->SetLineColor(kPink+8);
h2_o->SetMarkerStyle(21);
h2_o->SetMarkerColor(8);
h2_o->SetMarkerSize(0.6);
h2_o->Scale(500*0.25/24.16); // bhabhas LL

h2_p->SetFillColor(kOrange+4); 
h2_p->SetLineWidth(0);
h2_p->SetLineColor(kOrange+4);
h2_p->SetMarkerStyle(21);
h2_p->SetMarkerColor(8);
h2_p->SetMarkerSize(0.6);
h2_p->Scale(500*0.25/24.16); // bhabhas LL

h2_r->SetFillColor(kOrange+6); 
h2_r->SetLineWidth(0);
h2_r->SetLineColor(kOrange+6);
h2_r->SetMarkerStyle(21);
h2_r->SetMarkerColor(8);
h2_r->SetMarkerSize(0.6);
h2_r->Scale(500*0.25/24.16); // bhabhas LL

h2lr_o->SetFillColor(kPink+8); 
h2lr_o->SetLineWidth(0);
h2lr_o->SetLineColor(kPink+8);
h2lr_o->SetMarkerStyle(21);
h2lr_o->SetMarkerColor(8);
h2lr_o->SetMarkerSize(0.6);
h2lr_o->Scale(500*0.25/22.5); // bhabhas LR

h2lr_p->SetFillColor(kOrange+4); 
h2lr_p->SetLineWidth(0);
h2lr_p->SetLineColor(kOrange+4);
h2lr_p->SetMarkerStyle(21);
h2lr_p->SetMarkerColor(8);
h2lr_p->SetMarkerSize(0.6);
h2lr_p->Scale(500*0.25/22.5); // bhabhas LR

h2lr_r->SetFillColor(kOrange+6); 
h2lr_r->SetLineWidth(0);
h2lr_r->SetLineColor(kOrange+6);
h2lr_r->SetMarkerStyle(21);
h2lr_r->SetMarkerColor(8);
h2lr_r->SetMarkerSize(0.6);
h2lr_r->Scale(500*0.25/22.5); // bhabhas LR

h2rl_o->SetFillColor(kPink+8);
h2rl_o->SetLineWidth(0);
h2rl_o->SetLineColor(kPink+8);
h2rl_o->SetMarkerStyle(21);
h2rl_o->SetMarkerColor(8);
h2rl_o->SetMarkerSize(0.6);
h2rl_o->Scale(500*0.25/22.99); // bhabhas RL

h2rl_p->SetFillColor(kOrange+4);
h2rl_p->SetLineWidth(0);
h2rl_p->SetLineColor(kOrange+4);
h2rl_p->SetMarkerStyle(21);
h2rl_p->SetMarkerColor(8);
h2rl_p->SetMarkerSize(0.6);
h2rl_p->Scale(500*0.25/22.99); // bhabhas RL

h2rl_r->SetFillColor(kOrange+6);
h2rl_r->SetLineWidth(0);
h2rl_r->SetLineColor(kOrange+6);
h2rl_r->SetMarkerStyle(21);
h2rl_r->SetMarkerColor(8);
h2rl_r->SetMarkerSize(0.6);
h2rl_r->Scale(500*0.25/22.99); // bhabhas RL

h2rr_o->SetFillColor(kPink+8);
h2rr_o->SetLineWidth(0);
h2rr_o->SetLineColor(kPink+8);
h2rr_o->SetMarkerStyle(21);
h2rr_o->SetMarkerColor(8);
h2rr_o->SetMarkerSize(0.6);
h2rr_o->Scale(500*0.25/24.16); // bhabhas RR

h2rr_p->SetFillColor(kOrange+4);
h2rr_p->SetLineWidth(0);
h2rr_p->SetLineColor(kOrange+4);
h2rr_p->SetMarkerStyle(21);
h2rr_p->SetMarkerColor(8);
h2rr_p->SetMarkerSize(0.6);
h2rr_p->Scale(500*0.25/24.16); // bhabhas RR

h2rr_r->SetFillColor(kOrange+6);
h2rr_r->SetLineWidth(0);
h2rr_r->SetLineColor(kOrange+6);
h2rr_r->SetMarkerStyle(21);
h2rr_r->SetMarkerColor(8);
h2rr_r->SetMarkerSize(0.6);
h2rr_r->Scale(500*0.25/24.16); // bhabhas RR


hs->Add(h1_r);
hs->Add(h1r_r);
hs->Add(h1_o);
hs->Add(h1r_o);
hs->Add(h1_p);
hs->Add(h1r_p);

hs->Add(h2lr_o);
hs->Add(h2rl_o);
hs->Add(h2rr_o);
hs->Add(h2_o);

hs->Add(h2lr_p);
hs->Add(h2rl_p);
hs->Add(h2rr_p);
hs->Add(h2_p);

hs->Add(h2lr_r);
hs->Add(h2rl_r);
hs->Add(h2rr_r);
hs->Add(h2_r);

//hs->Add(h2lr);
//hs->Add(h2rl);
//hs->Add(h2rr);

hs->Draw();
hs->SetMaximum(10000000000);
hs->SetMinimum(1);
hs->Draw();


hs->GetXaxis()->SetTitle("p_{T} [GeV]");
hs->GetYaxis()->SetTitle("# particles  [1 / 500fb^{-1} GeV]");

  
/*TLine *l = new TLine(3,0,3,250100000); 
l->SetLineColor(2); 
l->SetLineWidth(3);
l->SetLineStyle(1);
l->Draw();*/


leg2 = new TLegend(0.2,0.83,0.61,0.9);
leg2->SetHeader("Transverse momenta of electrons");
leg2->SetTextFont(42);
 leg2->SetTextSize(0.040);
leg2->SetFillColor(0);
 leg2->SetBorderSize(0);
 leg2->SetMargin(0.18);
 leg2->Draw();
 
 
leg = new TLegend(0.2,0.66,0.55,0.83);
leg->AddEntry(h1_p,"#nu#nu + N#gamma:   photons","f");
leg->AddEntry(h1_o,"#nu#nu + N#gamma:   overlay","f");
leg->AddEntry(h1_r,"#nu#nu + N#gamma:   other","f");

leg->SetTextFont(42);
 leg->SetTextSize(0.040);
leg->SetFillColor(0);
 leg->SetBorderSize(0);
 leg->SetMargin(0.15);
 leg->Draw();


leg3 = new TLegend(0.55,0.66,0.85,0.83);
leg3->AddEntry(h2_r,"e^{+}e^{-} + N#gamma: other","f");
leg3->AddEntry(h2_p,"e^{+}e^{-} + N#gamma: photons","f");
leg3->AddEntry(h2_o,"e^{+}e^{-} + N#gamma: overlay","f");
leg3->SetTextFont(42);
 leg3->SetTextSize(0.040);
leg3->SetFillColor(0);
 leg3->SetBorderSize(0);
 leg3->SetMargin(0.18);
 leg3->Draw();


leg->SetTextFont(42);
 leg->SetTextSize(0.040);
leg->SetFillColor(0);
 leg->SetBorderSize(0);
 leg->SetMargin(0.18);
 leg->Draw();
 
ILDleg = new TLegend(0.855,0.87,0.91,0.91);
ILDleg->SetTextFont(41);
ILDleg->SetHeader(" ILD ");
ILDleg->SetTextSize(0.03);
ILDleg->SetFillColor(kCyan-10);
ILDleg->Draw();

c->SetLogy();  // log scale
c->Update();
c->Modified();
}                                                                                                                                           
