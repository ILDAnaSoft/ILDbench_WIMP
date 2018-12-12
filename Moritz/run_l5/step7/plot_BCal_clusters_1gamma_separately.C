{
TCanvas *c = new TCanvas("calbyp");
c->SetWindowSize(650,600);

ildStyle->SetTitleOffset(1,"x");
ildStyle->SetTitleOffset(1.2,"y");

// number of bins and plotted range
double n_bins 		= 6;
double leftborder 	= 0;
double rightborder 	= 6;

TFile *f1 = new TFile("../step2/vv_LR.root");
TTree* vv_LR_tree = (TTree*)f1->Get("photon_afterEvis");

TH1F *h1 = new TH1F("h1","simple_histo",n_bins,leftborder,rightborder);
 vv_LR_tree->Draw("BeamCalCluster >> h1"); 
 
TFile *f1r = new TFile("../step2/vv_RL.root"); // root file created from lumi.dat using readascii.C
TTree* vv_RL_tree = (TTree*)f1r->Get("photon_afterEvis");
 
TH1F *h1r = new TH1F("h1r","simple_histo",n_bins,leftborder,rightborder);
 vv_RL_tree->Draw("BeamCalCluster >> h1r"); 

#if 1
TFile *f2 = new TFile("../step2/ee_LL.root");
TTree* ee_LL_tree = (TTree*)f2->Get("photon_afterEvis");
#endif
TH1F *h2 = new TH1F("h2","simple_histo",n_bins,leftborder,rightborder);
#if 1
 ee_LL_tree->Draw("BeamCalCluster >> h2");
#endif

TFile *f2lr = new TFile("../step2/ee_LR.root");
TTree* ee_LR_tree = (TTree*)f2lr->Get("photon_afterEvis");
TH1F *h2lr = new TH1F("h2lr","simple_histo",n_bins,leftborder,rightborder);
 ee_LR_tree->Draw("BeamCalCluster >> h2lr");

TFile *f2rl = new TFile("../step2/ee_RL.root");
TTree* ee_RL_tree = (TTree*)f2rl->Get("photon_afterEvis");
TH1F *h2rl = new TH1F("h2rl","simple_histo",n_bins,leftborder,rightborder);
 ee_RL_tree->Draw("BeamCalCluster >> h2rl");
 
TFile *f2rr = new TFile("../step2/ee_RR.root");
TTree* ee_RR_tree = (TTree*)f2rr->Get("photon_afterEvis");
TH1F *h2rr = new TH1F("h2rr","simple_histo",n_bins,leftborder,rightborder);
 ee_RR_tree->Draw("BeamCalCluster >> h2rr");
THStack *hs = new THStack("hs","");
//hs->SetTitle("Number of BeamCal clusters: after visible energy cut, 500 fb^{-1}, unpol");

//TH1F *h1 = new TH1F("h1","simple_histo",n_bins,leftborder,rightborder);
// t5->Draw("BeamCalCluster >> h1"); 

//TH1F *h2 = new TH1F("h2","simple_histo",n_bins,leftborder,rightborder);
// t10->Draw("BeamCalCluster >> h2"); 

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

#if 1
h2->SetFillColor(kOrange+6); 
h2->SetLineWidth(0);
h2->SetLineColor(kOrange+6);
h2->SetMarkerStyle(21);
h2->SetMarkerColor(8);
h2->SetMarkerSize(0.6);
h2->Scale(500*0.25/24.16); // bhabhas LL
#endif

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
cout << "\n\tneutrinos:\n\t\tno BCal cluster: " << h1->Integral(0,1)+h1r->Integral(0,1) << "\tor " << (h1->Integral(0,1)+h1r->Integral(0,1))/(h1->Integral()+h1r->Integral())*100 << "%\n\t\tseveral BCal clusters: " << h1->Integral(2,6)+h1r->Integral(2,60) << "\tor " << (h1->Integral(2,6)+h1r->Integral(2,6))/(h1->Integral()+h1r->Integral())*100 << "%" << endl;

#if 1
cout << "\n\tBhabhas:\n\t\tno BCal cluster: " << h2->Integral(0,1)+h2lr->Integral(0,1)+h2rl->Integral(0,1)+h2rr->Integral(0,1) << "\t\tor " << (h2->Integral(0,1)+h2lr->Integral(0,1)+h2rl->Integral(0,1)+h2rr->Integral(0,1))/(h2->Integral()+h2lr->Integral()+h2rl->Integral()+h2rr->Integral())*100 << "%" << endl;
#endif
h2->Add(h2lr);
h2->Add(h2rl);
h2->Add(h2rr);

hs->Add(h1);
hs->Add(h1r);
#if 1
hs->Add(h2);
#endif
//hs->Add(h2lr);
//hs->Add(h2rl);
//hs->Add(h2rr);

hs->Draw();
hs->SetMaximum(10000000000);
hs->SetMinimum(1);

TFile *f1_1 = new TFile("../step2/vv_LR_only1g.root");
TTree* vv_LR_tree_1 = (TTree*)f1_1->Get("photon_afterEvis");
 
TH1F *h1_1 = new TH1F("h1_1","simple_histo",n_bins,leftborder,rightborder);
 vv_LR_tree_1->Draw("BeamCalCluster >> h1_1"); 

TFile *f1r_1 = new TFile("../step2/vv_RL_only1g.root"); // root file created from lumi.dat using readascii.C
TTree* vv_RL_tree_1 = (TTree*)f1r_1->Get("photon_afterEvis");
 
TH1F *h1r_1 = new TH1F("h1r","simple_histo",n_bins,leftborder,rightborder);
 vv_RL_tree_1->Draw("BeamCalCluster >> h1r_1"); 

cout << "\n\tneutrinos with 1gamma:\n\t\tno BCal cluster: " << h1_1->Integral(0,1)+h1r_1->Integral(0,1) << "\tor " << (h1_1->Integral(0,1)+h1r_1->Integral(0,1))/(h1_1->Integral()+h1r_1->Integral())*100 << "%\n\t\tseveral BCal clusters: " << h1_1->Integral(2,6)+h1r_1->Integral(2,60) << "\tor " << (h1_1->Integral(2,6)+h1r_1->Integral(2,6))/(h1_1->Integral()+h1r_1->Integral())*100 << "%" << endl;



THStack *hs_1 = new THStack("hs_1","");

h1_1->SetFillColor(kYellow+1); 
h1_1->SetLineWidth(0);
h1_1->SetLineColor(kYellow+1); 
//h1_1->SetMarkerColor(2);
//h1_1->SetMarkerStyle(21);
//h1_1->SetMarkerSize(0.6);
h1_1->Scale(500*0.25/524.9); // nunug LR; 0.25 because we look at unpolarised; 500 because it's for 500 fb-1 and the remaining number is the MC luminosity - which is different from sample to sample.

h1r_1->SetFillColor(kYellow+1); 
h1r_1->SetLineWidth(0);
h1r_1->SetLineColor(kYellow+1); 
//h1r_1->SetMarkerColor(2);
//h1r_1->SetMarkerStyle(21);
//h1r_1->SetMarkerSize(0.6);
h1r_1->Scale(500*0.25/599.4);

hs_1->Add(h1_1);
hs_1->Add(h1r_1);


hs->Draw();
//h1_1->Draw("same");
hs_1->Draw("same");

c->RedrawAxis();

hs->GetXaxis()->SetTitle("# reconstructed BeamCal clusters");
hs->GetYaxis()->SetTitle("# events  [1 / 500fb^{-1}]");

hs->GetXaxis()->SetNdivisions(7);


#if 1
   Int_t i;
   Int_t n = 2*(110-10);
   TGraph *gr = new TGraph(2*n);
   for (i=0;i<100;i++) {
      Float_t xlow = i*0.1+1;
      Float_t xup  = i*0.1+2;
      Float_t yup  = 3400000;
      Float_t ydown= 0;
      gr->SetPoint(2*i,  xlow,yup);
      gr->SetPoint(2*i+1,xup, yup);
      gr->SetPoint(2*n-2*i-1,xlow, ydown);
      gr->SetPoint(2*n-2*i-2,xup, ydown);
   }
   gr->SetFillStyle(3944);
   gr->SetFillColor(2);
   gr->Draw("lf");




TLine *l = new TLine(1,0,1,3400000); 
l->SetLineColor(2); 
l->SetLineWidth(3);
l->SetLineStyle(1);
l->Draw();
#endif
leg = new TLegend(0.39,0.68,0.81,0.9);
leg->SetHeader("Number of BeamCal clusters");
//leg->AddEntry(h2,"Bhabha scattering +N#gamma","f");
leg->AddEntry(h1,"neutrino pairs +N#gamma","f");
leg->AddEntry(h1_1,"neutrino pairs +1#gamma","f");
//leg->AddEntry(gr,"no BCal clusters","f");
leg->SetTextFont(42);
 leg->SetTextSize(0.040);
 leg->SetMargin(0.18);
leg->SetFillColor(0);
 leg->SetBorderSize(0);
 leg->Draw();

ILDleg = new TLegend(0.855,0.85,0.91,0.91);
ILDleg->SetTextFont(41);
ILDleg->SetHeader(" ILD ");
ILDleg->SetTextSize(0.030);
ILDleg->SetFillColor(kCyan-10);
ILDleg->Draw();

/*   TLatex latex;
   latex.SetTextSize(0.025);
//   latex.SetTextAlign(12);
   latex.DrawLatex(-3,50000000,"Number of BeamCal clusters: after visible energy cut, 500 fb^{-1}, unpol");*/

 

c->SetLogy();  // log scale
c->Update();
c->Modified();
}                                                                                                                                           
