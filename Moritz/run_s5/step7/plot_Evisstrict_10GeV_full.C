{
TCanvas *c = new TCanvas("calbyp");
c->SetWindowSize(650,400);
ildStyle->SetOptStat(0);
ildStyle->SetTitleOffset(1.2,"x");
ildStyle->SetTitleOffset(0.85,"y");

// number of bins and plotted range
double n_bins 		= 780;
double leftborder 	= -30;
double rightborder 	= 750;

TFile *f1 = new TFile("../step2/vv_LR_noBoost_CB_cuts.root");
TTree* vv_LR_tree = (TTree*)f1.Get("photon_afterPt");

TH1F *h1 = new TH1F("h1","simple_histo",n_bins,leftborder,rightborder);
 vv_LR_tree->Draw("Evis_strict >> h1"); 
 
TFile *f1r = new TFile("../step2/vv_RL_noBoost_CB_cuts.root"); // root file created from lumi.dat using readascii.C
TTree* vv_RL_tree = (TTree*)f1r.Get("photon_afterPt");
 
TH1F *h1r = new TH1F("h1r","simple_histo",n_bins,leftborder,rightborder);
 vv_RL_tree->Draw("Evis_strict >> h1r"); 

TFile *f2 = new TFile("../step2/bhabhas_LL_noBoost_CB_cuts.root");
TTree* ee_LL_tree = (TTree*)f2.Get("photon_afterPt");
TH1F *h2 = new TH1F("h2","simple_histo",n_bins,leftborder,rightborder);
 ee_LL_tree->Draw("Evis_strict >> h2");

TFile *f2lr = new TFile("../step2/bhabhas_LR_noBoost_CB_cuts.root");
TTree* ee_LR_tree = (TTree*)f2lr.Get("photon_afterPt");
TH1F *h2lr = new TH1F("h2lr","simple_histo",n_bins,leftborder,rightborder);
 ee_LR_tree->Draw("Evis_strict >> h2lr");

TFile *f2rl = new TFile("../step2/bhabhas_RL_noBoost_CB_cuts.root");
TTree* ee_RL_tree = (TTree*)f2rl.Get("photon_afterPt");
TH1F *h2rl = new TH1F("h2rl","simple_histo",n_bins,leftborder,rightborder);
 ee_RL_tree->Draw("Evis_strict >> h2rl");
 
TFile *f2rr = new TFile("../step2/bhabhas_RR_noBoost_CB_cuts.root");
TTree* ee_RR_tree = (TTree*)f2rr.Get("photon_afterPt");
TH1F *h2rr = new TH1F("h2rr","simple_histo",n_bins,leftborder,rightborder);
 ee_RR_tree->Draw("Evis_strict >> h2rr");

THStack *hs = new THStack("hs","");

//TH1F *h1 = new TH1F("h1","simple_histo",n_bins,leftborder,rightborder);
// t5->Draw("Evis_strict >> h1"); 

//TH1F *h2 = new TH1F("h2","simple_histo",n_bins,leftborder,rightborder);
// t10->Draw("Evis_strict >> h2"); 

h1->SetFillColor(kSpring-7); //kBlue-4
h1->SetMarkerColor(2);
h1->SetLineColor(kSpring-7);
h1->SetMarkerStyle(21);
h1->SetMarkerSize(0.6);
h1->Scale(500*0.25/524.9); // nunug LR; 0.25 because we look at unpolarised; 500 because it's for 500 fb-1 and the remaining number is the MC luminosity - which is different from sample to sample.

h1r->SetFillColor(kSpring-7); 
h1r->SetMarkerColor(2);
h1r->SetLineColor(kSpring-7);
h1r->SetMarkerStyle(21);
h1r->SetMarkerSize(0.6);
h1r->Scale(500*0.25/599.4);

h2->SetFillColor(kOrange+6); //kOrange-3
h2->SetMarkerStyle(21);
h2->SetLineColor(kOrange+6);
h2->SetMarkerColor(kOrange+6);
h2->SetMarkerSize(0.6);
h2->Scale(500*0.25/24.16); // bhabhas LL

h2lr->SetFillColor(kOrange+6); 
h2lr->SetMarkerStyle(21);
h2lr->SetLineColor(kOrange+6);
h2lr->SetMarkerColor(kOrange+6);
h2lr->SetMarkerSize(0.6);
h2lr->Scale(500*0.25/22.5); // bhabhas LR

h2rl->SetFillColor(kOrange+6); 
h2rl->SetMarkerStyle(21);
h2rl->SetLineColor(kOrange+6);
h2rl->SetMarkerColor(kOrange+6);
h2rl->SetMarkerSize(0.6);
h2rl->Scale(500*0.25/22.99); // bhabhas RL

h2rr->SetFillColor(kOrange+6); 
h2rr->SetMarkerStyle(21);
h2rr->SetLineColor(kOrange+6);
h2rr->SetMarkerColor(kOrange+6);
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
hs->SetMaximum(10010000);
hs->SetMinimum(1);
hs->Draw();


hs->GetXaxis()->SetTitle("E_{visible} [GeV]");
hs->GetYaxis()->SetTitle("# events  [1 / 500fb^{-1} GeV]");

/*   Int_t i;
   Int_t n = 2*(100-10);
   TGraph *gr = new TGraph(2*n);
   for (i=0;i<90;i++) {
      Float_t xlow = i+10;
      Float_t xup  = i+11;
      Float_t yup  = 50000000;
      Float_t ydown= 0;
      gr->SetPoint(2*i,  xlow,yup);
      gr->SetPoint(2*i+1,xup, yup);
      gr->SetPoint(2*n-2*i-1,xlow, ydown);
      gr->SetPoint(2*n-2*i-2,xup, ydown);
   }
   gr->SetFillStyle(3013);
   gr->SetFillColor(2);
   gr->Draw("lf");

   Int_t i;
   Int_t n = 2*(760-100);
   TGraph *gr = new TGraph(2*n);
   for (i=0;i<660;i++) {
      Float_t xlow = i+100;
      Float_t xup  = i+101;
      Float_t yup  = 200000;
      Float_t ydown= 0;
      gr->SetPoint(2*i,  xlow,yup);
      gr->SetPoint(2*i+1,xup, yup);
      gr->SetPoint(2*n-2*i-1,xlow, ydown);
      gr->SetPoint(2*n-2*i-2,xup, ydown);
   }
   gr->SetFillStyle(3013);
   gr->SetFillColor(2);
   gr->Draw("lf2");


        TLine *l = new TLine(10,0,10,50000000); 
l->SetLineColor(2); 
l->SetLineWidth(3);
l->SetLineStyle(1);
l->Draw();*/


leg = new TLegend(0.250,0.68,0.7,0.88);
leg->SetHeader("Visible energy: PFOs >5GeV, w/o #pi, n");
leg->AddEntry(h2,"Bhabha scattering + N#gamma","f");
leg->AddEntry(h1,"neutrino pairs + N#gamma","f");
//leg->AddEntry(gr,"E_{visible,max}=20GeV","f");
 leg->SetTextFont(42);
 leg->SetTextSize(0.060);
leg->SetFillColor(0);
 leg->SetMargin(0.18); 
 leg->SetBorderSize(0);
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
