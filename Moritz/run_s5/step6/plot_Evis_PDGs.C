{
TCanvas *c = new TCanvas("calbyp");
c->SetWindowSize(650,400);
//ildStyle->SetOpfotat(0);
ildStyle->SetTitleOffset(1.2,"x");
ildStyle->SetTitleOffset(0.85,"y");
// number of bins and plotted range
double n_bins 		= 360;
double leftborder 	= -10;
double rightborder 	= 350;

TFile *f1 = new TFile("../step5/vv_LR_PDGs_photon_e_details.root");
  TTree* photon_o_tree_1 = (TTree*)f1->Get("gammas_o");
  TTree* electron_o_tree_1 = (TTree*)f1->Get("electrons_o");
  TTree* muon_o_tree_1 = (TTree*)f1->Get("muons_o");
  TTree* V0_o_tree_1 = (TTree*)f1->Get("V0_o");
  TTree* neutron_o_tree_1 = (TTree*)f1->Get("neutrons_o");
  TTree* pion_o_tree_1 = (TTree*)f1->Get("pions_o");

  TTree* photon_r_tree_1 = (TTree*)f1->Get("gammas_r");
  TTree* electron_r_tree_1 = (TTree*)f1->Get("electrons_r");
  TTree* muon_r_tree_1 = (TTree*)f1->Get("muons_r");
  TTree* V0_r_tree_1 = (TTree*)f1->Get("V0_r");
  TTree* neutron_r_tree_1 = (TTree*)f1->Get("neutrons_r");
  TTree* pion_r_tree_1 = (TTree*)f1->Get("pions_r");


TH1F *h1_g_o = new TH1F("h1_g_o","simple_histo",n_bins,leftborder,rightborder);
photon_o_tree_1->Draw("PDG_energy >> h1_g_o");

TH1F *h1_g_r = new TH1F("h1_g_r","simple_histo",n_bins,leftborder,rightborder);
photon_r_tree_1->Draw("PDG_energy >> h1_g_r");

TH1F *h1_e_o = new TH1F("h1_e_o","simple_histo",n_bins,leftborder,rightborder);
electron_o_tree_1->Draw("PDG_energy >> h1_e_o");

TH1F *h1_e_r = new TH1F("h1_e_r","simple_histo",n_bins,leftborder,rightborder);
electron_r_tree_1->Draw("PDG_energy >> h1_e_r");

TH1F *h1_m_o = new TH1F("h1_m_o","simple_histo",n_bins,leftborder,rightborder);
muon_o_tree_1->Draw("PDG_energy >> h1_m_o");

TH1F *h1_m_r = new TH1F("h1_m_r","simple_histo",n_bins,leftborder,rightborder);
muon_r_tree_1->Draw("PDG_energy >> h1_m_r");

TH1F *h1_v_o = new TH1F("h1_v_o","simple_histo",n_bins,leftborder,rightborder);
V0_o_tree_1->Draw("PDG_energy >> h1_v_o");

TH1F *h1_v_r = new TH1F("h1_v_r","simple_histo",n_bins,leftborder,rightborder);
V0_r_tree_1->Draw("PDG_energy >> h1_v_r");

TH1F *h1_n_o = new TH1F("h1_n_o","simple_histo",n_bins,leftborder,rightborder);
neutron_o_tree_1->Draw("PDG_energy >> h1_n_o");

TH1F *h1_n_r = new TH1F("h1_n_r","simple_histo",n_bins,leftborder,rightborder);
neutron_r_tree_1->Draw("PDG_energy >> h1_n_r");

TH1F *h1_p_o = new TH1F("h1_p_o","simple_histo",n_bins,leftborder,rightborder);
pion_o_tree_1->Draw("PDG_energy >> h1_p_o");

TH1F *h1_p_r = new TH1F("h1_p_r","simple_histo",n_bins,leftborder,rightborder);
pion_r_tree_1->Draw("PDG_energy >> h1_p_r");


TFile *f2 = new TFile("../step5/vv_RL_PDGs_photon_e_details.root");
  TTree* photon_o_tree_2 = (TTree*)f2->Get("gammas_o");
  TTree* electron_o_tree_2 = (TTree*)f2->Get("electrons_o");
  TTree* muon_o_tree_2 = (TTree*)f2->Get("muons_o");
  TTree* V0_o_tree_2 = (TTree*)f2->Get("V0_o");
  TTree* neutron_o_tree_2 = (TTree*)f2->Get("neutrons_o");
  TTree* pion_o_tree_2 = (TTree*)f2->Get("pions_o");

  TTree* photon_r_tree_2 = (TTree*)f2->Get("gammas_r");
  TTree* electron_r_tree_2 = (TTree*)f2->Get("electrons_r");
  TTree* muon_r_tree_2 = (TTree*)f2->Get("muons_r");
  TTree* V0_r_tree_2 = (TTree*)f2->Get("V0_r");
  TTree* neutron_r_tree_2 = (TTree*)f2->Get("neutrons_r");
  TTree* pion_r_tree_2 = (TTree*)f2->Get("pions_r");
  

TH1F *h2_g_o = new TH1F("h2_g_o","simple_histo",n_bins,leftborder,rightborder);
photon_o_tree_2->Draw("PDG_energy >> h2_g_o");

TH1F *h2_g_r = new TH1F("h2_g_r","simple_histo",n_bins,leftborder,rightborder);
photon_r_tree_2->Draw("PDG_energy >> h2_g_r");

TH1F *h2_e_o = new TH1F("h2_e_o","simple_histo",n_bins,leftborder,rightborder);
electron_o_tree_2->Draw("PDG_energy >> h2_e_o");

TH1F *h2_e_r = new TH1F("h2_e_r","simple_histo",n_bins,leftborder,rightborder);
electron_r_tree_2->Draw("PDG_energy >> h2_e_r");

TH1F *h2_m_o = new TH1F("h2_m_o","simple_histo",n_bins,leftborder,rightborder);
muon_o_tree_2->Draw("PDG_energy >> h2_m_o");

TH1F *h2_m_r = new TH1F("h2_m_r","simple_histo",n_bins,leftborder,rightborder);
muon_r_tree_2->Draw("PDG_energy >> h2_m_r");

TH1F *h2_v_o = new TH1F("h2_v_o","simple_histo",n_bins,leftborder,rightborder);
V0_o_tree_2->Draw("PDG_energy >> h2_v_o");

TH1F *h2_v_r = new TH1F("h2_v_r","simple_histo",n_bins,leftborder,rightborder);
V0_r_tree_2->Draw("PDG_energy >> h2_v_r");

TH1F *h2_n_o = new TH1F("h2_n_o","simple_histo",n_bins,leftborder,rightborder);
neutron_o_tree_2->Draw("PDG_energy >> h2_n_o");

TH1F *h2_n_r = new TH1F("h2_n_r","simple_histo",n_bins,leftborder,rightborder);
neutron_r_tree_2->Draw("PDG_energy >> h2_n_r");

TH1F *h2_p_o = new TH1F("h2_p_o","simple_histo",n_bins,leftborder,rightborder);
pion_o_tree_2->Draw("PDG_energy >> h2_p_o");

TH1F *h2_p_r = new TH1F("h2_p_r","simple_histo",n_bins,leftborder,rightborder);
pion_r_tree_2->Draw("PDG_energy >> h2_p_r");

TFile *f3 = new TFile("../step5/bhabhas_LL_PDGs_photon_e_details.root");
  TTree* photon_o_tree_3 = (TTree*)f3->Get("gammas_o");
  TTree* electron_o_tree_3 = (TTree*)f3->Get("electrons_o");
  TTree* muon_o_tree_3 = (TTree*)f3->Get("muons_o");
  TTree* V0_o_tree_3 = (TTree*)f3->Get("V0_o");
  TTree* neutron_o_tree_3 = (TTree*)f3->Get("neutrons_o");
  TTree* pion_o_tree_3 = (TTree*)f3->Get("pions_o");

  TTree* photon_r_tree_3 = (TTree*)f3->Get("gammas_r");
  TTree* electron_r_tree_3 = (TTree*)f3->Get("electrons_r");
  TTree* muon_r_tree_3 = (TTree*)f3->Get("muons_r");
  TTree* V0_r_tree_3 = (TTree*)f3->Get("V0_r");
  TTree* neutron_r_tree_3 = (TTree*)f3->Get("neutrons_r");
  TTree* pion_r_tree_3 = (TTree*)f3->Get("pions_r");
  
  TTree* photon_e_tree_3 = (TTree*)f3->Get("gammas_e");


TH1F *h3_g_o = new TH1F("h3_g_o","simple_histo",n_bins,leftborder,rightborder);
photon_o_tree_3->Draw("PDG_energy >> h3_g_o");

TH1F *h3_g_r = new TH1F("h3_g_r","simple_histo",n_bins,leftborder,rightborder);
photon_r_tree_3->Draw("PDG_energy >> h3_g_r");

TH1F *h3_e_o = new TH1F("h3_e_o","simple_histo",n_bins,leftborder,rightborder);
electron_o_tree_3->Draw("PDG_energy >> h3_e_o");

TH1F *h3_e_r = new TH1F("h3_e_r","simple_histo",n_bins,leftborder,rightborder);
electron_r_tree_3->Draw("PDG_energy >> h3_e_r");

TH1F *h3_m_o = new TH1F("h3_m_o","simple_histo",n_bins,leftborder,rightborder);
muon_o_tree_3->Draw("PDG_energy >> h3_m_o");

TH1F *h3_m_r = new TH1F("h3_m_r","simple_histo",n_bins,leftborder,rightborder);
muon_r_tree_3->Draw("PDG_energy >> h3_m_r");

TH1F *h3_v_o = new TH1F("h3_v_o","simple_histo",n_bins,leftborder,rightborder);
V0_o_tree_3->Draw("PDG_energy >> h3_v_o");

TH1F *h3_v_r = new TH1F("h3_v_r","simple_histo",n_bins,leftborder,rightborder);
V0_r_tree_3->Draw("PDG_energy >> h3_v_r");

TH1F *h3_n_o = new TH1F("h3_n_o","simple_histo",n_bins,leftborder,rightborder);
neutron_o_tree_3->Draw("PDG_energy >> h3_n_o");

TH1F *h3_n_r = new TH1F("h3_n_r","simple_histo",n_bins,leftborder,rightborder);
neutron_r_tree_3->Draw("PDG_energy >> h3_n_r");

TH1F *h3_p_o = new TH1F("h3_p_o","simple_histo",n_bins,leftborder,rightborder);
pion_o_tree_3->Draw("PDG_energy >> h3_p_o");

TH1F *h3_p_r = new TH1F("h3_p_r","simple_histo",n_bins,leftborder,rightborder);
pion_r_tree_3->Draw("PDG_energy >> h3_p_r");

TH1F *h3_g_e = new TH1F("h3_g_e","simple_histo",n_bins,leftborder,rightborder);
photon_e_tree_3->Draw("PDG_energy >> h3_g_e");

TFile *f4 = new TFile("../step5/bhabhas_LR_PDGs_photon_e_details.root");
  TTree* photon_o_tree_4 = (TTree*)f4->Get("gammas_o");
  TTree* electron_o_tree_4 = (TTree*)f4->Get("electrons_o");
  TTree* muon_o_tree_4 = (TTree*)f4->Get("muons_o");
  TTree* V0_o_tree_4 = (TTree*)f4->Get("V0_o");
  TTree* neutron_o_tree_4 = (TTree*)f4->Get("neutrons_o");
  TTree* pion_o_tree_4 = (TTree*)f4->Get("pions_o");

  TTree* photon_r_tree_4 = (TTree*)f4->Get("gammas_r");
  TTree* electron_r_tree_4 = (TTree*)f4->Get("electrons_r");
  TTree* muon_r_tree_4 = (TTree*)f4->Get("muons_r");
  TTree* V0_r_tree_4 = (TTree*)f4->Get("V0_r");
  TTree* neutron_r_tree_4 = (TTree*)f4->Get("neutrons_r");
  TTree* pion_r_tree_4 = (TTree*)f4->Get("pions_r");
  
  TTree* photon_e_tree_4 = (TTree*)f4->Get("gammas_e");


TH1F *h4_g_o = new TH1F("h4_g_o","simple_histo",n_bins,leftborder,rightborder);
photon_o_tree_4->Draw("PDG_energy >> h4_g_o");

TH1F *h4_g_r = new TH1F("h4_g_r","simple_histo",n_bins,leftborder,rightborder);
photon_r_tree_4->Draw("PDG_energy >> h4_g_r");

TH1F *h4_e_o = new TH1F("h4_e_o","simple_histo",n_bins,leftborder,rightborder);
electron_o_tree_4->Draw("PDG_energy >> h4_e_o");

TH1F *h4_e_r = new TH1F("h4_e_r","simple_histo",n_bins,leftborder,rightborder);
electron_r_tree_4->Draw("PDG_energy >> h4_e_r");

TH1F *h4_m_o = new TH1F("h4_m_o","simple_histo",n_bins,leftborder,rightborder);
muon_o_tree_4->Draw("PDG_energy >> h4_m_o");

TH1F *h4_m_r = new TH1F("h4_m_r","simple_histo",n_bins,leftborder,rightborder);
muon_r_tree_4->Draw("PDG_energy >> h4_m_r");

TH1F *h4_v_o = new TH1F("h4_v_o","simple_histo",n_bins,leftborder,rightborder);
V0_o_tree_4->Draw("PDG_energy >> h4_v_o");

TH1F *h4_v_r = new TH1F("h4_v_r","simple_histo",n_bins,leftborder,rightborder);
V0_r_tree_4->Draw("PDG_energy >> h4_v_r");

TH1F *h4_n_o = new TH1F("h4_n_o","simple_histo",n_bins,leftborder,rightborder);
neutron_o_tree_4->Draw("PDG_energy >> h4_n_o");

TH1F *h4_n_r = new TH1F("h4_n_r","simple_histo",n_bins,leftborder,rightborder);
neutron_r_tree_4->Draw("PDG_energy >> h4_n_r");

TH1F *h4_p_o = new TH1F("h4_p_o","simple_histo",n_bins,leftborder,rightborder);
pion_o_tree_4->Draw("PDG_energy >> h4_p_o");

TH1F *h4_p_r = new TH1F("h4_p_r","simple_histo",n_bins,leftborder,rightborder);
pion_r_tree_4->Draw("PDG_energy >> h4_p_r");

TH1F *h4_g_e = new TH1F("h4_g_e","simple_histo",n_bins,leftborder,rightborder);
photon_e_tree_4->Draw("PDG_energy >> h4_g_e");

TFile *f5 = new TFile("../step5/bhabhas_RL_PDGs_photon_e_details.root");
  TTree* photon_o_tree_5 = (TTree*)f5->Get("gammas_o");
  TTree* electron_o_tree_5 = (TTree*)f5->Get("electrons_o");
  TTree* muon_o_tree_5 = (TTree*)f5->Get("muons_o");
  TTree* V0_o_tree_5 = (TTree*)f5->Get("V0_o");
  TTree* neutron_o_tree_5 = (TTree*)f5->Get("neutrons_o");
  TTree* pion_o_tree_5 = (TTree*)f5->Get("pions_o");

  TTree* photon_r_tree_5 = (TTree*)f5->Get("gammas_r");
  TTree* electron_r_tree_5 = (TTree*)f5->Get("electrons_r");
  TTree* muon_r_tree_5 = (TTree*)f5->Get("muons_r");
  TTree* V0_r_tree_5 = (TTree*)f5->Get("V0_r");
  TTree* neutron_r_tree_5 = (TTree*)f5->Get("neutrons_r");
  TTree* pion_r_tree_5 = (TTree*)f5->Get("pions_r");
  
  TTree* photon_e_tree_5 = (TTree*)f5->Get("gammas_e");


TH1F *h5_g_o = new TH1F("h5_g_o","simple_histo",n_bins,leftborder,rightborder);
photon_o_tree_5->Draw("PDG_energy >> h5_g_o");

TH1F *h5_g_r = new TH1F("h5_g_r","simple_histo",n_bins,leftborder,rightborder);
photon_r_tree_5->Draw("PDG_energy >> h5_g_r");

TH1F *h5_e_o = new TH1F("h5_e_o","simple_histo",n_bins,leftborder,rightborder);
electron_o_tree_5->Draw("PDG_energy >> h5_e_o");

TH1F *h5_e_r = new TH1F("h5_e_r","simple_histo",n_bins,leftborder,rightborder);
electron_r_tree_5->Draw("PDG_energy >> h5_e_r");

TH1F *h5_m_o = new TH1F("h5_m_o","simple_histo",n_bins,leftborder,rightborder);
muon_o_tree_5->Draw("PDG_energy >> h5_m_o");

TH1F *h5_m_r = new TH1F("h5_m_r","simple_histo",n_bins,leftborder,rightborder);
muon_r_tree_5->Draw("PDG_energy >> h5_m_r");

TH1F *h5_v_o = new TH1F("h5_v_o","simple_histo",n_bins,leftborder,rightborder);
V0_o_tree_5->Draw("PDG_energy >> h5_v_o");

TH1F *h5_v_r = new TH1F("h5_v_r","simple_histo",n_bins,leftborder,rightborder);
V0_r_tree_5->Draw("PDG_energy >> h5_v_r");

TH1F *h5_n_o = new TH1F("h5_n_o","simple_histo",n_bins,leftborder,rightborder);
neutron_o_tree_5->Draw("PDG_energy >> h5_n_o");

TH1F *h5_n_r = new TH1F("h5_n_r","simple_histo",n_bins,leftborder,rightborder);
neutron_r_tree_5->Draw("PDG_energy >> h5_n_r");

TH1F *h5_p_o = new TH1F("h5_p_o","simple_histo",n_bins,leftborder,rightborder);
pion_o_tree_5->Draw("PDG_energy >> h5_p_o");

TH1F *h5_p_r = new TH1F("h5_p_r","simple_histo",n_bins,leftborder,rightborder);
pion_r_tree_5->Draw("PDG_energy >> h5_p_r");

TH1F *h5_g_e = new TH1F("h5_g_e","simple_histo",n_bins,leftborder,rightborder);
photon_e_tree_5->Draw("PDG_energy >> h5_g_e");

TFile *f6 = new TFile("../step5/bhabhas_RR_PDGs_photon_e_details.root");
  TTree* photon_o_tree_6 = (TTree*)f6->Get("gammas_o");
  TTree* electron_o_tree_6 = (TTree*)f6->Get("electrons_o");
  TTree* muon_o_tree_6 = (TTree*)f6->Get("muons_o");
  TTree* V0_o_tree_6 = (TTree*)f6->Get("V0_o");
  TTree* neutron_o_tree_6 = (TTree*)f6->Get("neutrons_o");
  TTree* pion_o_tree_6 = (TTree*)f6->Get("pions_o");

  TTree* photon_r_tree_6 = (TTree*)f6->Get("gammas_r");
  TTree* electron_r_tree_6 = (TTree*)f6->Get("electrons_r");
  TTree* muon_r_tree_6 = (TTree*)f6->Get("muons_r");
  TTree* V0_r_tree_6 = (TTree*)f6->Get("V0_r");
  TTree* neutron_r_tree_6 = (TTree*)f6->Get("neutrons_r");
  TTree* pion_r_tree_6 = (TTree*)f6->Get("pions_r");
  
  TTree* photon_e_tree_6 = (TTree*)f6->Get("gammas_e");


TH1F *h6_g_o = new TH1F("h6_g_o","simple_histo",n_bins,leftborder,rightborder);
photon_o_tree_6->Draw("PDG_energy >> h6_g_o");

TH1F *h6_g_r = new TH1F("h6_g_r","simple_histo",n_bins,leftborder,rightborder);
photon_r_tree_6->Draw("PDG_energy >> h6_g_r");

TH1F *h6_e_o = new TH1F("h6_e_o","simple_histo",n_bins,leftborder,rightborder);
electron_o_tree_6->Draw("PDG_energy >> h6_e_o");

TH1F *h6_e_r = new TH1F("h6_e_r","simple_histo",n_bins,leftborder,rightborder);
electron_r_tree_6->Draw("PDG_energy >> h6_e_r");

TH1F *h6_m_o = new TH1F("h6_m_o","simple_histo",n_bins,leftborder,rightborder);
muon_o_tree_6->Draw("PDG_energy >> h6_m_o");

TH1F *h6_m_r = new TH1F("h6_m_r","simple_histo",n_bins,leftborder,rightborder);
muon_r_tree_6->Draw("PDG_energy >> h6_m_r");

TH1F *h6_v_o = new TH1F("h6_v_o","simple_histo",n_bins,leftborder,rightborder);
V0_o_tree_6->Draw("PDG_energy >> h6_v_o");

TH1F *h6_v_r = new TH1F("h6_v_r","simple_histo",n_bins,leftborder,rightborder);
V0_r_tree_6->Draw("PDG_energy >> h6_v_r");

TH1F *h6_n_o = new TH1F("h6_n_o","simple_histo",n_bins,leftborder,rightborder);
neutron_o_tree_6->Draw("PDG_energy >> h6_n_o");

TH1F *h6_n_r = new TH1F("h6_n_r","simple_histo",n_bins,leftborder,rightborder);
neutron_r_tree_6->Draw("PDG_energy >> h6_n_r");

TH1F *h6_p_o = new TH1F("h6_p_o","simple_histo",n_bins,leftborder,rightborder);
pion_o_tree_6->Draw("PDG_energy >> h6_p_o");

TH1F *h6_p_r = new TH1F("h6_p_r","simple_histo",n_bins,leftborder,rightborder);
pion_r_tree_6->Draw("PDG_energy >> h6_p_r");

TH1F *h6_g_e = new TH1F("h6_g_e","simple_histo",n_bins,leftborder,rightborder);
photon_e_tree_6->Draw("PDG_energy >> h6_g_e");


h1_g_o->SetFillColor(kYellow+2);
//h1_g_o->SetFillStyle(3001);
h1_g_o->SetLineWidth(0);
h1_g_o->SetLineColor(kYellow+2);
h1_g_o->Scale(500*0.25/524.9); // nunug LR

h1_g_r->SetFillColor(kGreen+3);
h1_g_r->SetLineWidth(0);
//h1_g_r->SetFillStyle(3001);
h1_g_r->SetLineColor(kGreen+3);
h1_g_r->SetMarkerColor(2);
h1_g_r->Scale(500*0.25/524.9); // nunug LR

h2_g_o->SetFillColor(kYellow+2);
//h2_g_o->SetFillStyle(3001);
h2_g_o->SetLineWidth(0);
h2_g_o->SetLineColor(kYellow+2);
h2_g_o->Scale(500*0.25/599.4); // neutrinos RL

h2_g_r->SetFillColor(kGreen+3);
h2_g_r->SetLineWidth(0);
//h2_g_r->SetFillStyle(3001);
h2_g_r->SetLineColor(kGreen+3);
h2_g_r->SetMarkerColor(2);
h2_g_r->Scale(500*0.25/599.4); // neutrinos RL

h3_g_o->SetFillColor(kPink+8); 
h3_g_o->SetLineWidth(0);
h3_g_o->SetLineColor(kPink+8);
h3_g_o->Scale(500*0.25/24.16); // bhabhas LL

h3_g_r->SetFillColor(kOrange+6); 
h3_g_r->SetLineWidth(0);
h3_g_r->SetLineColor(kOrange+6);
h3_g_r->Scale(500*0.25/24.16); // bhabhas LL

h3_g_e->SetFillColor(kOrange+4); 
h3_g_e->SetLineWidth(0);
h3_g_e->SetLineColor(kOrange+4);
h3_g_e->Scale(500*0.25/24.16); // bhabhas LL

h4_g_o->SetFillColor(kPink+8); 
h4_g_o->SetLineWidth(0);
h4_g_o->SetLineColor(kPink+8);
h4_g_o->Scale(500*0.25/22.5); // bhabhas LR

h4_g_r->SetFillColor(kOrange+6); 
h4_g_r->SetLineWidth(0);
h4_g_r->SetLineColor(kOrange+6);
h4_g_r->Scale(500*0.25/22.5); // bhabhas LR

h4_g_e->SetFillColor(kOrange+4); 
h4_g_e->SetLineWidth(0);
h4_g_e->SetLineColor(kOrange+4);
h4_g_e->Scale(500*0.25/22.5); // bhabhas LR

h5_g_o->SetFillColor(kPink+8); 
h5_g_o->SetLineWidth(0);
h5_g_o->SetLineColor(kPink+8);
h5_g_o->Scale(500*0.25/22.99); // bhabhas RL

h5_g_r->SetFillColor(kOrange+6); 
h5_g_r->SetLineWidth(0);
h5_g_r->SetLineColor(kOrange+6);
h5_g_r->Scale(500*0.25/22.99); // bhabhas RL

h5_g_e->SetFillColor(kOrange+4); 
h5_g_e->SetLineWidth(0);
h5_g_e->SetLineColor(kOrange+4);
h5_g_e->Scale(500*0.25/22.99); // bhabhas RL

h6_g_o->SetFillColor(kPink+8); 
h6_g_o->SetLineWidth(0);
h6_g_o->SetLineColor(kPink+8);
h6_g_o->Scale(500*0.25/24.16); // bhabhas RR

h6_g_r->SetFillColor(kOrange+6); 
h6_g_r->SetLineWidth(0);
h6_g_r->SetLineColor(kOrange+6);
h6_g_r->Scale(500*0.25/24.16); // bhabhas RR

h6_g_e->SetFillColor(kOrange+4); 
h6_g_e->SetLineWidth(0);
h6_g_e->SetLineColor(kOrange+4);
h6_g_e->Scale(500*0.25/24.16); // bhabhas RR

h1_e_o->SetFillColor(kYellow+2);
h1_e_o->SetLineWidth(0);
h1_e_o->SetLineColor(kYellow+2);
h1_e_o->Scale(500*0.25/524.9); // nunug LR

h1_e_r->SetFillColor(kGreen+3);
h1_e_r->SetLineColor(kGreen+3);
h1_e_r->SetMarkerColor(2);
h1_e_r->Scale(500*0.25/524.9); // nunug LR

h2_e_o->SetFillColor(kYellow+2);
h2_e_o->SetLineWidth(0);
h2_e_o->SetLineColor(kYellow+2);
h2_e_o->Scale(500*0.25/599.4); // neutrinos RL

h2_e_r->SetFillColor(kGreen+3);
h2_e_r->SetLineColor(kGreen+3);
h2_e_r->SetMarkerColor(2);
h2_e_r->Scale(500*0.25/599.4); // neutrinos RL

h3_e_o->SetFillColor(kPink+8); 
h3_e_o->SetLineWidth(0);
h3_e_o->SetLineColor(kPink+8);
h3_e_o->Scale(500*0.25/24.16); // bhabhas LL

h3_e_r->SetFillColor(kOrange+6); 
h3_e_r->SetLineWidth(0);
h3_e_r->SetLineColor(kOrange+6);
h3_e_r->Scale(500*0.25/24.16); // bhabhas LL

h4_e_o->SetFillColor(kPink+8); 
h4_e_o->SetLineWidth(0);
h4_e_o->SetLineColor(kPink+8);
h4_e_o->Scale(500*0.25/22.5); // bhabhas LR

h4_e_r->SetFillColor(kOrange+6); 
h4_e_r->SetLineWidth(0);
h4_e_r->SetLineColor(kOrange+6);
h4_e_r->Scale(500*0.25/22.5); // bhabhas LR

h5_e_o->SetFillColor(kPink+8); 
h5_e_o->SetLineWidth(0);
h5_e_o->SetLineColor(kPink+8);
h5_e_o->Scale(500*0.25/22.99); // bhabhas RL

h5_e_r->SetFillColor(kOrange+6); 
h5_e_r->SetLineWidth(0);
h5_e_r->SetLineColor(kOrange+6);
h5_e_r->Scale(500*0.25/22.99); // bhabhas RL

h6_e_o->SetFillColor(kPink+8); 
h6_e_o->SetLineWidth(0);
h6_e_o->SetLineColor(kPink+8);
h6_e_o->Scale(500*0.25/24.16); // bhabhas RR

h6_e_r->SetFillColor(kOrange+6); 
h6_e_r->SetLineWidth(0);
h6_e_r->SetLineColor(kOrange+6);
h6_e_r->Scale(500*0.25/24.16); // bhabhas RR

h1_m_o->SetFillColor(kYellow+2);
h1_m_o->SetLineWidth(0);
h1_m_o->SetLineColor(kYellow+2);
h1_m_o->Scale(500*0.25/524.9); // nunug LR

h1_m_r->SetFillColor(kGreen+3);
h1_m_r->SetLineColor(kGreen+3);
h1_m_r->SetMarkerColor(2);
h1_m_r->Scale(500*0.25/524.9); // nunug LR

h2_m_o->SetFillColor(kYellow+2);
h2_m_o->SetLineWidth(0);
h2_m_o->SetLineColor(kYellow+2);
h2_m_o->Scale(500*0.25/599.4); // neutrinos RL

h2_m_r->SetFillColor(kGreen+3);
h2_m_r->SetLineColor(kGreen+3);
h2_m_r->SetMarkerColor(2);
h2_m_r->Scale(500*0.25/599.4); // neutrinos RL

h3_m_o->SetFillColor(kPink+8); 
h3_m_o->SetLineWidth(0);
h3_m_o->SetLineColor(kPink+8);
h3_m_o->Scale(500*0.25/24.16); // bhabhas LL

h3_m_r->SetFillColor(kOrange+6); 
h3_m_r->SetLineWidth(0);
h3_m_r->SetLineColor(kOrange+6);
h3_m_r->Scale(500*0.25/24.16); // bhabhas LL

h4_m_o->SetFillColor(kPink+8); 
h4_m_o->SetLineWidth(0);
h4_m_o->SetLineColor(kPink+8);
h4_m_o->Scale(500*0.25/22.5); // bhabhas LR

h4_m_r->SetFillColor(kOrange+6); 
h4_m_r->SetLineWidth(0);
h4_m_r->SetLineColor(kOrange+6);
h4_m_r->Scale(500*0.25/22.5); // bhabhas LR

h5_m_o->SetFillColor(kPink+8); 
h5_m_o->SetLineWidth(0);
h5_m_o->SetLineColor(kPink+8);
h5_m_o->Scale(500*0.25/22.99); // bhabhas RL

h5_m_r->SetFillColor(kOrange+6); 
h5_m_r->SetLineWidth(0);
h5_m_r->SetLineColor(kOrange+6);
h5_m_r->Scale(500*0.25/22.99); // bhabhas RL

h6_m_o->SetFillColor(kPink+8); 
h6_m_o->SetLineWidth(0);
h6_m_o->SetLineColor(kPink+8);
h6_m_o->Scale(500*0.25/24.16); // bhabhas RR

h6_m_r->SetFillColor(kOrange+6); 
h6_m_r->SetLineWidth(0);
h6_m_r->SetLineColor(kOrange+6);
h6_m_r->Scale(500*0.25/24.16); // bhabhas RR

h1_v_o->SetFillColor(kYellow+2);
h1_v_o->SetLineWidth(0);
h1_v_o->SetLineColor(kYellow+2);
h1_v_o->Scale(500*0.25/524.9); // nunug LR

h1_v_r->SetFillColor(kGreen+3);
h1_v_r->SetLineColor(kGreen+3);
h1_v_r->SetMarkerColor(2);
h1_v_r->Scale(500*0.25/524.9); // nunug LR

h2_v_o->SetFillColor(kYellow+2);
h2_v_o->SetLineWidth(0);
h2_v_o->SetLineColor(kYellow+2);
h2_v_o->Scale(500*0.25/599.4); // neutrinos RL

h2_v_r->SetFillColor(kGreen+3);
h2_v_r->SetLineColor(kGreen+3);
h2_v_r->SetMarkerColor(2);
h2_v_r->Scale(500*0.25/599.4); // neutrinos RL

h3_v_o->SetFillColor(kPink+8); 
h3_v_o->SetLineWidth(0);
h3_v_o->SetLineColor(kPink+8);
h3_v_o->Scale(500*0.25/24.16); // bhabhas LL

h3_v_r->SetFillColor(kOrange+6); 
h3_v_r->SetLineWidth(0);
h3_v_r->SetLineColor(kOrange+6);
h3_v_r->Scale(500*0.25/24.16); // bhabhas LL

h4_v_o->SetFillColor(kPink+8); 
h4_v_o->SetLineWidth(0);
h4_v_o->SetLineColor(kPink+8);
h4_v_o->Scale(500*0.25/22.5); // bhabhas LR

h4_v_r->SetFillColor(kOrange+6); 
h4_v_r->SetLineWidth(0);
h4_v_r->SetLineColor(kOrange+6);
h4_v_r->Scale(500*0.25/22.5); // bhabhas LR

h5_v_o->SetFillColor(kPink+8); 
h5_v_o->SetLineWidth(0);
h5_v_o->SetLineColor(kPink+8);
h5_v_o->Scale(500*0.25/22.99); // bhabhas RL

h5_v_r->SetFillColor(kOrange+6); 
h5_v_r->SetLineWidth(0);
h5_v_r->SetLineColor(kOrange+6);
h5_v_r->Scale(500*0.25/22.99); // bhabhas RL

h6_v_o->SetFillColor(kPink+8); 
h6_v_o->SetLineWidth(0);
h6_v_o->SetLineColor(kPink+8);
h6_v_o->Scale(500*0.25/24.16); // bhabhas RR

h6_v_r->SetFillColor(kOrange+6); 
h6_v_r->SetLineWidth(0);
h6_v_r->SetLineColor(kOrange+6);
h6_v_r->Scale(500*0.25/24.16); // bhabhas RR

h1_n_o->SetFillColor(kYellow+2);
h1_n_o->SetLineWidth(0);
h1_n_o->SetLineColor(kYellow+2);
h1_n_o->Scale(500*0.25/524.9); // nunug LR

h1_n_r->SetFillColor(kGreen+3);
h1_n_r->SetLineColor(kGreen+3);
h1_n_r->SetMarkerColor(2);
h1_n_r->Scale(500*0.25/524.9); // nunug LR

h2_n_o->SetFillColor(kYellow+2);
h2_n_o->SetLineWidth(0);
h2_n_o->SetLineColor(kYellow+2);
h2_n_o->Scale(500*0.25/599.4); // neutrinos RL

h2_n_r->SetFillColor(kGreen+3);
h2_n_r->SetLineColor(kGreen+3);
h2_n_r->SetMarkerColor(2);
h2_n_r->Scale(500*0.25/599.4); // neutrinos RL

h3_n_o->SetFillColor(kPink+8); 
h3_n_o->SetLineWidth(0);
h3_n_o->SetLineColor(kPink+8);
h3_n_o->Scale(500*0.25/24.16); // bhabhas LL

h3_n_r->SetFillColor(kOrange+6); 
h3_n_r->SetLineWidth(0);
h3_n_r->SetLineColor(kOrange+6);
h3_n_r->Scale(500*0.25/24.16); // bhabhas LL

h4_n_o->SetFillColor(kPink+8); 
h4_n_o->SetLineWidth(0);
h4_n_o->SetLineColor(kPink+8);
h4_n_o->Scale(500*0.25/22.5); // bhabhas LR

h4_n_r->SetFillColor(kOrange+6); 
h4_n_r->SetLineWidth(0);
h4_n_r->SetLineColor(kOrange+6);
h4_n_r->Scale(500*0.25/22.5); // bhabhas LR

h5_n_o->SetFillColor(kPink+8); 
h5_n_o->SetLineWidth(0);
h5_n_o->SetLineColor(kPink+8);
h5_n_o->Scale(500*0.25/22.99); // bhabhas RL

h5_n_r->SetFillColor(kOrange+6); 
h5_n_r->SetLineWidth(0);
h5_n_r->SetLineColor(kOrange+6);
h5_n_r->Scale(500*0.25/22.99); // bhabhas RL

h6_n_o->SetFillColor(kPink+8); 
h6_n_o->SetLineWidth(0);
h6_n_o->SetLineColor(kPink+8);
h6_n_o->Scale(500*0.25/24.16); // bhabhas RR

h6_n_r->SetFillColor(kOrange+6); 
h6_n_r->SetLineWidth(0);
h6_n_r->SetLineColor(kOrange+6);
h6_n_r->Scale(500*0.25/24.16); // bhabhas RR

h1_p_o->SetFillColor(kYellow+2);
h1_p_o->SetLineWidth(0);
h1_p_o->SetLineColor(kYellow+2);
h1_p_o->Scale(500*0.25/524.9); // nunug LR

h1_p_r->SetFillColor(kGreen+3);
h1_p_r->SetLineColor(kGreen+3);
h1_p_r->SetMarkerColor(2);
h1_p_r->Scale(500*0.25/524.9); // nunug LR

h2_p_o->SetFillColor(kYellow+2);
h2_p_o->SetLineWidth(0);
h2_p_o->SetLineColor(kYellow+2);
h2_p_o->Scale(500*0.25/599.4); // neutrinos RL

h2_p_r->SetFillColor(kGreen+3);
h2_p_r->SetLineColor(kGreen+3);
h2_p_r->SetMarkerColor(2);
h2_p_r->Scale(500*0.25/599.4); // neutrinos RL

h3_p_o->SetFillColor(kPink+8); 
h3_p_o->SetLineWidth(0);
h3_p_o->SetLineColor(kPink+8);
h3_p_o->Scale(500*0.25/24.16); // bhabhas LL

h3_p_r->SetFillColor(kOrange+6); 
h3_p_r->SetLineWidth(0);
h3_p_r->SetLineColor(kOrange+6);
h3_p_r->Scale(500*0.25/24.16); // bhabhas LL

h4_p_o->SetFillColor(kPink+8); 
h4_p_o->SetLineWidth(0);
h4_p_o->SetLineColor(kPink+8);
h4_p_o->Scale(500*0.25/22.5); // bhabhas LR

h4_p_r->SetFillColor(kOrange+6); 
h4_p_r->SetLineWidth(0);
h4_p_r->SetLineColor(kOrange+6);
h4_p_r->Scale(500*0.25/22.5); // bhabhas LR

h5_p_o->SetFillColor(kPink+8); 
h5_p_o->SetLineWidth(0);
h5_p_o->SetLineColor(kPink+8);
h5_p_o->Scale(500*0.25/22.99); // bhabhas RL

h5_p_r->SetFillColor(kOrange+6); 
h5_p_r->SetLineWidth(0);
h5_p_r->SetLineColor(kOrange+6);
h5_p_r->Scale(500*0.25/22.99); // bhabhas RL

h6_p_o->SetFillColor(kPink+8); 
h6_p_o->SetLineWidth(0);
h6_p_o->SetLineColor(kPink+8);
h6_p_o->Scale(500*0.25/24.16); // bhabhas RR

h6_p_r->SetFillColor(kOrange+6); 
h6_p_r->SetLineWidth(0);
h6_p_r->SetLineColor(kOrange+6);
h6_p_r->Scale(500*0.25/24.16); // bhabhas RR

THStack *hs1 = new THStack("hs1","");

hs1->Add(h1_g_o);
hs1->Add(h2_g_o);
hs1->Add(h1_g_r);
hs1->Add(h2_g_r);
hs1->Add(h3_g_o);
hs1->Add(h4_g_o);
hs1->Add(h5_g_o);
hs1->Add(h6_g_o);
hs1->Add(h3_g_e);
hs1->Add(h4_g_e);
hs1->Add(h5_g_e);
hs1->Add(h6_g_e);
hs1->Add(h3_g_r);
hs1->Add(h4_g_r);
hs1->Add(h5_g_r);
hs1->Add(h6_g_r);

hs1->Draw();
hs1->SetMaximum(100000000);
hs1->SetMinimum(2);
hs1->Draw();


hs1->GetXaxis()->SetTitle("energy [GeV]");
hs1->GetYaxis()->SetTitle("# particles  [1 / 500fb^{-1} GeV]");

leg = new TLegend(0.25,0.65,0.53,0.88);
leg->SetHeader("reconstructed photons");
leg->AddEntry(h2_g_r,"#nu#nu + N#gamma: rest","f");
leg->AddEntry(h2_g_o,"#nu#nu + N#gamma: overlay","f");
 leg->SetTextFont(42);
 leg->SetTextSize(0.060);
leg->SetFillColor(0);
 leg->SetMargin(0.18); 
 leg->SetBorderSize(0);
 leg->Draw();

leg2 = new TLegend(0.570,0.58,0.85,0.8);
leg2->AddEntry(h3_g_r,"e^{+}e^{-} + N#gamma: rest","f");
leg2->AddEntry(h3_g_e,"e^{+}e^{-} + N#gamma: electrons","f");
leg2->AddEntry(h3_g_o,"e^{+}e^{-} + N#gamma: overlay","f");
 leg2->SetTextFont(42);
 leg2->SetTextSize(0.060);
leg2->SetFillColor(0);
 leg2->SetMargin(0.18); 
 leg2->SetBorderSize(0);
 leg2->Draw();

hs1->GetXaxis()->SetTitle("energy [GeV]");
hs1->GetYaxis()->SetTitle("# particles  [1 / 500fb^{-1} GeV]");
 
ILDleg = new TLegend(0.855,0.85,0.91,0.91);
ILDleg->SetTextFont(41);
ILDleg->SetHeader(" ILD ");
ILDleg->SetTextSize(0.045);
ILDleg->SetFillColor(kCyan-10);
ILDleg->Draw();

c->SetLogy();  // log scale
c->Update();
c->Modified();

TCanvas *c2 = new TCanvas("calbyp2");
c2->SetWindowSize(650,400);

THStack *hs2 = new THStack("hs2","");

hs2->Add(h1_e_o);
hs2->Add(h2_e_o);
hs2->Add(h1_e_r);
hs2->Add(h2_e_r);
hs2->Add(h3_e_o);
hs2->Add(h4_e_o);
hs2->Add(h5_e_o);
hs2->Add(h6_e_o);
hs2->Add(h3_e_r);
hs2->Add(h4_e_r);
hs2->Add(h5_e_r);
hs2->Add(h6_e_r);

hs2->Draw();
hs2->SetMaximum(100000000);
hs2->SetMinimum(2);
hs2->Draw();

hs2->GetXaxis()->SetTitle("energy [GeV]");
hs2->GetYaxis()->SetTitle("# particles  [1 / 500fb^{-1} GeV]");

leg = new TLegend(0.25,0.65,0.53,0.88);
leg->SetHeader("reconstructed electrons");
leg->AddEntry(h2_g_r,"#nu#nu + N#gamma: rest","f");
leg->AddEntry(h2_g_o,"#nu#nu + N#gamma: overlay","f");
 leg->SetTextFont(42);
 leg->SetTextSize(0.060);
leg->SetFillColor(0);
 leg->SetMargin(0.18); 
 leg->SetBorderSize(0);
 leg->Draw();

leg2 = new TLegend(0.570,0.65,0.85,0.8);
leg2->AddEntry(h3_g_r,"e^{+}e^{-} + N#gamma: rest","f");
leg2->AddEntry(h3_g_o,"e^{+}e^{-} + N#gamma: overlay","f");
 leg2->SetTextFont(42);
 leg2->SetTextSize(0.060);
leg2->SetFillColor(0);
 leg2->SetMargin(0.18); 
 leg2->SetBorderSize(0);
 leg2->Draw();

ILDleg->Draw();

c2->SetLogy();  // log scale
c2->Update();
c2->Modified();

TCanvas *c3 = new TCanvas("calbyp3");
c3->SetWindowSize(650,400);

THStack *hs3 = new THStack("hs3","");

hs3->Add(h1_m_o);
hs3->Add(h2_m_o);
hs3->Add(h1_m_r);
hs3->Add(h2_m_r);
hs3->Add(h3_m_o);
hs3->Add(h4_m_o);
hs3->Add(h5_m_o);
hs3->Add(h6_m_o);
hs3->Add(h3_m_r);
hs3->Add(h4_m_r);
hs3->Add(h5_m_r);
hs3->Add(h6_m_r);

hs3->Draw();
hs3->SetMaximum(100000000);
hs3->SetMinimum(2);
hs3->Draw();

hs3->GetXaxis()->SetTitle("energy [GeV]");
hs3->GetYaxis()->SetTitle("# particles  [1 / 500fb^{-1} GeV]");

leg = new TLegend(0.25,0.65,0.53,0.88);
leg->SetHeader("reconstructed muons");
leg->AddEntry(h2_g_r,"#nu#nu + N#gamma: rest","f");
leg->AddEntry(h2_g_o,"#nu#nu + N#gamma: overlay","f");
 leg->SetTextFont(42);
 leg->SetTextSize(0.060);
leg->SetFillColor(0);
 leg->SetMargin(0.18); 
 leg->SetBorderSize(0);
 leg->Draw();

leg2 = new TLegend(0.570,0.65,0.85,0.8);
leg2->AddEntry(h3_g_r,"e^{+}e^{-} + N#gamma: rest","f");
leg2->AddEntry(h3_g_o,"e^{+}e^{-} + N#gamma: overlay","f");
 leg2->SetTextFont(42);
 leg2->SetTextSize(0.060);
leg2->SetFillColor(0);
 leg2->SetMargin(0.18); 
 leg2->SetBorderSize(0);
 leg2->Draw();

ILDleg->Draw();

c3->SetLogy();  // log scale
c3->Update();
c3->Modified();

TCanvas *c4 = new TCanvas("calbyp4");
c4->SetWindowSize(650,400);

THStack *hs4 = new THStack("hs4","");

hs4->Add(h1_v_o);
hs4->Add(h2_v_o);
hs4->Add(h1_v_r);
hs4->Add(h2_v_r);
hs4->Add(h3_v_o);
hs4->Add(h4_v_o);
hs4->Add(h5_v_o);
hs4->Add(h6_v_o);
hs4->Add(h3_v_r);
hs4->Add(h4_v_r);
hs4->Add(h5_v_r);
hs4->Add(h6_v_r);

hs4->Draw();
hs4->SetMaximum(100000000);
hs4->SetMinimum(2);
hs4->Draw();

hs4->GetXaxis()->SetTitle("energy [GeV]");
hs4->GetYaxis()->SetTitle("# particles  [1 / 500fb^{-1} GeV]");

leg = new TLegend(0.25,0.65,0.53,0.88);
leg->SetHeader("reconstructed V0 objects");
leg->AddEntry(h2_g_r,"#nu#nu + N#gamma: rest","f");
leg->AddEntry(h2_g_o,"#nu#nu + N#gamma: overlay","f");
 leg->SetTextFont(42);
 leg->SetTextSize(0.060);
leg->SetFillColor(0);
 leg->SetMargin(0.18); 
 leg->SetBorderSize(0);
 leg->Draw();

leg2 = new TLegend(0.570,0.65,0.85,0.8);
leg2->AddEntry(h3_g_r,"e^{+}e^{-} + N#gamma: rest","f");
leg2->AddEntry(h3_g_o,"e^{+}e^{-} + N#gamma: overlay","f");
 leg2->SetTextFont(42);
 leg2->SetTextSize(0.060);
leg2->SetFillColor(0);
 leg2->SetMargin(0.18); 
 leg2->SetBorderSize(0);
 leg2->Draw();

ILDleg->Draw();

c4->SetLogy();  // log scale
c4->Update();
c4->Modified();

TCanvas *c5 = new TCanvas("calbyp5");
c5->SetWindowSize(650,400);

THStack *hs5 = new THStack("hs5","");

hs5->Add(h1_n_o);
hs5->Add(h2_n_o);
hs5->Add(h1_n_r);
hs5->Add(h2_n_r);
hs5->Add(h3_n_o);
hs5->Add(h4_n_o);
hs5->Add(h5_n_o);
hs5->Add(h6_n_o);
hs5->Add(h3_n_r);
hs5->Add(h4_n_r);
hs5->Add(h5_n_r);
hs5->Add(h6_n_r);

hs5->Draw();
hs5->SetMaximum(100000000);
hs5->SetMinimum(2);
hs5->Draw();

hs5->GetXaxis()->SetTitle("energy [GeV]");
hs5->GetYaxis()->SetTitle("# particles  [1 / 500fb^{-1} GeV]");

leg = new TLegend(0.25,0.65,0.53,0.88);
leg->SetHeader("reconstructed neutrons");
leg->AddEntry(h2_g_r,"#nu#nu + N#gamma: rest","f");
leg->AddEntry(h2_g_o,"#nu#nu + N#gamma: overlay","f");
 leg->SetTextFont(42);
 leg->SetTextSize(0.060);
leg->SetFillColor(0);
 leg->SetMargin(0.18); 
 leg->SetBorderSize(0);
 leg->Draw();

leg2 = new TLegend(0.570,0.65,0.85,0.8);
leg2->AddEntry(h3_g_r,"e^{+}e^{-} + N#gamma: rest","f");
leg2->AddEntry(h3_g_o,"e^{+}e^{-} + N#gamma: overlay","f");
 leg2->SetTextFont(42);
 leg2->SetTextSize(0.060);
leg2->SetFillColor(0);
 leg2->SetMargin(0.18); 
 leg2->SetBorderSize(0);
 leg2->Draw();

ILDleg->Draw();

c5->SetLogy();  // log scale
c5->Update();
c5->Modified();


TCanvas *c6 = new TCanvas("calbyp6");
c6->SetWindowSize(650,400);

THStack *hs6 = new THStack("hs6","");

hs6->Add(h1_p_o);
hs6->Add(h2_p_o);
hs6->Add(h1_p_r);
hs6->Add(h2_p_r);
hs6->Add(h3_p_o);
hs6->Add(h4_p_o);
hs6->Add(h5_p_o);
hs6->Add(h6_p_o);
hs6->Add(h3_p_r);
hs6->Add(h4_p_r);
hs6->Add(h5_p_r);
hs6->Add(h6_p_r);

hs6->Draw();
hs6->SetMaximum(100000000);
hs6->SetMinimum(2);
hs6->Draw();

hs6->GetXaxis()->SetTitle("energy [GeV]");
hs6->GetYaxis()->SetTitle("# particles  [1 / 500fb^{-1} GeV]");

leg = new TLegend(0.25,0.65,0.53,0.88);
leg->SetHeader("reconstructed pions");
leg->AddEntry(h2_g_r,"#nu#nu + N#gamma: rest","f");
leg->AddEntry(h2_g_o,"#nu#nu + N#gamma: overlay","f");
 leg->SetTextFont(42);
 leg->SetTextSize(0.060);
leg->SetFillColor(0);
 leg->SetMargin(0.18); 
 leg->SetBorderSize(0);
 leg->Draw();

leg2 = new TLegend(0.570,0.65,0.85,0.8);
leg2->AddEntry(h3_g_r,"e^{+}e^{-} + N#gamma: rest","f");
leg2->AddEntry(h3_g_o,"e^{+}e^{-} + N#gamma: overlay","f");
 leg2->SetTextFont(42);
 leg2->SetTextSize(0.060);
leg2->SetFillColor(0);
 leg2->SetMargin(0.18); 
 leg2->SetBorderSize(0);
 leg2->Draw();

ILDleg->Draw();

c6->SetLogy();  // log scale
c6->Update();
c6->Modified();



}                                                                                                                                           
