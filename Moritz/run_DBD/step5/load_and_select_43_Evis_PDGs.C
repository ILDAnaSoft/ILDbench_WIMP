#include <string>
#include <TTree.h>
#include <iostream>
#include <iterator>     // std::distance
#include <vector>
//using std::vector;
#define PI 3.14159265

double E_min;
double E_max;
double costheta_cut;
double pt_min_out;
double pt_min_in;
double phi_step;
double cut_pt;
double cut_pt_e;
double cut_evis;
double cut_evis_strict;
double threshold_evis;
int process_id;



void run_load_and_select(){

  cout << "\n\n\n------------running load_and_select--------------\n";

// in order to work with branches, they have to be defined. 
// load the input root file into root: root -l lctuple.root
// find the name of the tree: .ls 
// create a file with all definitions: lctree->MakeCode("bla.C")
// either include all or select the variables needed
// eg mcpdg: Int_t mcpdg[385]; and lctree->SetBranchAddress("mcpdg",mcpdg); 
// Don't forget to check and change for a new input lctuple file!
  Int_t mcpdg[2136];
  Float_t mcmox[2136];
  Float_t mcmoy[2136];
  Float_t mcmoz[2136];
  Int_t nmcp;
  Int_t nrec;
  Int_t rctyp[185];
  Float_t mcene[2136];
  Float_t rcmox[185];
  Float_t rcmoy[185];
  Float_t rcmoz[185];
  Float_t rcene[185];
  Float_t rccha[185];
  Int_t rcori[185];
   Int_t r2mnrel;
   Int_t r2mf[1000];
   Int_t r2mt[1000];
   Int_t mcsst[2136];
   Int_t  mcpa0[2222];
   Int_t  mcpa1[2222];
    Int_t           mcda0[2222];
    Int_t           mcda1[2222];
    Int_t           mcda2[2222];
    Int_t           mcda3[2222];
    Int_t           mcda4[2222];

  
  Float_t RCMOX_BCal_photon_PTmax[1];
  Float_t RCENE_BCal_photon_PTmax[1];
  Int_t indexPT;
  
   float crosss; 
   float MCLumi;
   float process;
   int N_events;
   float e_pol;
   float p_pol;
   
//   char filename[256];
   
   // Select input file; process is given by last input variable process_id
  TString inputfilename;
  TString outputfilename;
   
  if (process_id==1){
  cout << "Neutrinos, P(e-) = -1, P(e+) = +1" << endl;
  inputfilename = "../step1/boosted_vv_LR.root";
  outputfilename = "vv_LR_PDGs_photon_e_details.root";
  }
 
  if (process_id==2){
  cout << "Neutrinos, P(e-) = +1, P(e+) = -1" << endl;  
  inputfilename = "../step1/boosted_vv_RL.root";
  outputfilename = "vv_RL_PDGs_photon_e_details.root";
  }
  
  if (process_id==3){
  cout << "Bhabhas, P(e-) = -1, P(e+) = -1" << endl;
  inputfilename = "../step1/boosted_bhabhas_LL.root";
  outputfilename = "bhabhas_LL_PDGs_photon_e_details.root";
  }

  if (process_id==4){
  cout << "Bhabhas, P(e-) = -1, P(e+) = +1" << endl;
  inputfilename = "../step1/boosted_bhabhas_LR.root";
  outputfilename = "bhabhas_LR_PDGs_photon_e_details.root";
  }
  
  if (process_id==5){
  cout << "Bhabhas, P(e-) = +1, P(e+) = -1" << endl;
  inputfilename = "../step1/boosted_bhabhas_RL.root";
  outputfilename = "bhabhas_RL_PDGs_photon_e_details.root";
  }
  
  if (process_id==6){
  cout << "Bhabhas, P(e-) = +1, P(e+) = +1" << endl;
  inputfilename = "../step1/boosted_bhabhas_RR.root";
  outputfilename = "bhabhas_RR_PDGs_photon_e_details.root";
  }
  
    
  cout << "Input file:\t\t\t" << inputfilename << endl;
  cout << "Output file:\t\t\t" << outputfilename << endl;
  
  TFile* f = new TFile(inputfilename,"r");
  TTree* lctree = (TTree*)f->Get("MyLCTuple"); 
  // why is lctree;655 cloned? even though I "get" 656 here?
  
  TFile* g = new TFile(outputfilename, "RECREATE");  
  /*cout << "\nCopying LCTuple tree ... takes some time" << endl;
  TTree *newtree = lctree->CopyTree("");  */
 
// also from the bla.C file
  lctree->SetBranchAddress("mcpdg",mcpdg);
  lctree->SetBranchAddress("nmcp",&nmcp);
  lctree->SetBranchAddress("mcmox",&mcmox);
  lctree->SetBranchAddress("mcmoy",&mcmoy);
  lctree->SetBranchAddress("mcmoz",&mcmoz);
  lctree->SetBranchAddress("nrec",&nrec);
  lctree->SetBranchAddress("rctyp",rctyp);
  lctree->SetBranchAddress("mcene",mcene);
  lctree->SetBranchAddress("rcene",rcene);
  lctree->SetBranchAddress("rcmox",rcmox);
  lctree->SetBranchAddress("rcmoy",rcmoy);
  lctree->SetBranchAddress("rcmoz",rcmoz); 
  lctree->SetBranchAddress("rccha",rccha);
  lctree->SetBranchAddress("rcori",rcori);
  lctree->SetBranchAddress("r2mnrel",&r2mnrel);
  lctree->SetBranchAddress("r2mf",&r2mf);
  lctree->SetBranchAddress("r2mt",&r2mt);
  lctree->SetBranchAddress("mcsst",mcsst);
  lctree->SetBranchAddress("mcpa0",mcpa0);
  lctree->SetBranchAddress("mcpa1",mcpa1);
  lctree->SetBranchAddress("mcda0",mcda0);
  lctree->SetBranchAddress("mcda1",mcda1);
  lctree->SetBranchAddress("mcda2",mcda2);
  lctree->SetBranchAddress("mcda3",mcda3);
  lctree->SetBranchAddress("mcda4",mcda4);

  
  int n_entries = lctree->GetEntries();
  
  TTree* BCal_frame = (TTree*)f->Get("BCal_frame");
  
  BCal_frame->SetBranchAddress("RCMOX_BCal_photon_PTmax",RCMOX_BCal_photon_PTmax);
  BCal_frame->SetBranchAddress("RCENE_BCal_photon_PTmax",RCENE_BCal_photon_PTmax);
  BCal_frame->SetBranchAddress("indexPT",&indexPT);




  
  TTree* cut_tree = new TTree("signal_conditions","signal_conditions");
  TTree* global_tree = new TTree("global","global");
  TTree* pt_tree = new TTree("pt_charged_after_signaldef","pt_charged_after_signaldef");
  TTree* pte_tree = new TTree("pt_electron_after_signaldef","pt_electron_after_signaldef");
  TTree* sigdef_tree = new TTree("photon_sig_def","photon_sig_def");
  TTree* afterPt_tree = new TTree("photon_afterPt","photon_afterPt");
  TTree* afterEvis_tree = new TTree("photon_afterEvis","photon_afterEvis");
  TTree* sel_tree = new TTree("selected_photons","selected_photons");
  TTree* eff_tree = new TTree("selection_efficiencies","selection_efficiencies");
   TTree* photon_o_tree = new TTree("gammas_o","gammas_o");
   TTree* electron_o_tree = new TTree("electrons_o","electrons_o");
   TTree* muon_o_tree = new TTree("muons_o","muons_o");
   TTree* V0_o_tree = new TTree("V0_o","V0_o");
   TTree* neutron_o_tree = new TTree("neutrons_o","neutrons_o");
   TTree* pion_o_tree = new TTree("pions_o","pions_o");
 
   TTree* photon_r_tree = new TTree("gammas_r","gammas_r");
   TTree* electron_r_tree = new TTree("electrons_r","electrons_r");
   TTree* muon_r_tree = new TTree("muons_r","muons_r");
   TTree* V0_r_tree = new TTree("V0_r","V0_r");
   TTree* neutron_r_tree = new TTree("neutrons_r","neutrons_r");
   TTree* pion_r_tree = new TTree("pions_r","pions_r");
   TTree* photon_e_tree = new TTree("gammas_e","gammas_e");
   
   TTree* neutron_50_70_tree = new TTree("neutrons_50_70","neutrons_50_70");
   TTree* neutron_80_100_tree = new TTree("neutrons_80_100","neutrons_80_100");
   TTree* neutron_110_130_tree = new TTree("neutrons_110_130","neutrons_110_130");

  
  float PDG_energy;

  TBranch* b01o = photon_o_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  TBranch* b02o = electron_o_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  TBranch* b03o = muon_o_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  TBranch* b04o = V0_o_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  TBranch* b05o = neutron_o_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  TBranch* b06o = pion_o_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F"); 
   
  TBranch* b01r = photon_r_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  TBranch* b02r = electron_r_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  TBranch* b03r = muon_r_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  TBranch* b04r = V0_r_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  TBranch* b05r = neutron_r_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  TBranch* b06r = pion_r_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
   
  TBranch* b01e = photon_e_tree->Branch("PDG_energy",&PDG_energy,"PDG_energy/F");
  
  float MC_pdg, neutron_theta, Eg_sig;
  TBranch* b05_1 = neutron_50_70_tree->Branch("MC_pdg",&MC_pdg,"MC_pdg/F");
  TBranch* b05_2 = neutron_50_70_tree->Branch("neutron_theta",&neutron_theta,"neutron_theta/F");
  TBranch* b05_3 = neutron_50_70_tree->Branch("Eg_sig",&Eg_sig,"Eg_sig/F");
  TBranch* b05_4 = neutron_80_100_tree->Branch("MC_pdg",&MC_pdg,"MC_pdg/F");
  TBranch* b05_5 = neutron_80_100_tree->Branch("neutron_theta",&neutron_theta,"neutron_theta/F");
  TBranch* b05_6 = neutron_80_100_tree->Branch("Eg_sig",&Eg_sig,"Eg_sig/F");
  TBranch* b05_7 = neutron_110_130_tree->Branch("MC_pdg",&MC_pdg,"MC_pdg/F");
  TBranch* b05_8 = neutron_110_130_tree->Branch("neutron_theta",&neutron_theta,"neutron_theta/F");
  TBranch* b05_9 = neutron_110_130_tree->Branch("Eg_sig",&Eg_sig,"Eg_sig/F");
  
  float pT, pT_e, Evis_init, Evis, Evis_strict, Evis_CB, RCENE, RCMOX, RCMOY, RCMOZ, RCTHETA, RCPT, RCPT_BCal, MRECOIL, sigdef, eff_pT, eff_Evis, eff_BCal, RCPHI, BCalFrame_RCENE, BCalFrame_RCMOX, BCalFrame_RCTHETA, BCalFrame_RCPHI, Neutrinos, Bhabhas, electron_polarisation, positron_polarisation;
  int BeamCalCluster_init, BeamCalCluster, number_of_tracks;
  int N_sigdef, N_after_pT_cut, N_after_Evis_cut, N_selected;

  TBranch* MCLUMI = global_tree->Branch("MCLumi",&MCLumi,"MCLumi/F");
  TBranch* CROSSS = global_tree->Branch("crosss",&crosss,"crosss/F");
  TBranch* N_ENTRIES = global_tree->Branch("N_events",&N_events,"N_events/I",1024);

  float cut_e_min_out, cut_e_max, cut_costheta_cut, cut_cos_theta, cut_PT_out, cut_e_min_in, cut_PT_in, cut_PHI_step, evis_cut, evis_cut_strict, evis_threshold, cut_evis_max, pt_cut, cut_pt_max, cut_pt_e_max;
  
  int events_sig_def, events_afterPt, events_afterEvis, events_selected;

  cut_e_min_out = E_min;
  cut_e_max = E_max;
  cut_cos_theta = costheta_cut;
  cut_PT_out = pt_min_out;
  cut_e_min_in = E_min;
  cut_PT_in = pt_min_in;
  cut_PHI_step = phi_step;
  evis_cut = cut_evis;
  evis_cut_strict = cut_evis_strict;
  evis_threshold = threshold_evis;
  cut_evis_max = evis_cut;
  pt_cut = cut_pt;
  cut_pt_max = pt_cut;
  cut_pt_e_max = cut_pt_e;
  

  TBranch* CUTEMINOUT = cut_tree->Branch("cut_e_min_out",&cut_e_min_out,"cut_e_min_out/F");
  TBranch* CUTEMAX = cut_tree->Branch("cut_e_max",&cut_e_max,"cut_e_max/F");
  TBranch* CUTTHEOUT = cut_tree->Branch("cut_cos_theta",&cut_cos_theta,"cut_cos_theta/F");
  TBranch* CUTPTOUT = cut_tree->Branch("cut_PT_out",&cut_PT_out,"cut_PT_out/F");
  TBranch* CUTEMININ = cut_tree->Branch("cut_e_min_in",&cut_e_min_in,"cut_e_min_in/F");
  TBranch* CUTPTIN = cut_tree->Branch("cut_PT_in",&cut_PT_in,"cut_PT_in/F");
  TBranch* CUTPHI = cut_tree->Branch("cut_PHI_step",&cut_PHI_step,"cut_PHI_step/F");
  TBranch* CUTPT = cut_tree->Branch("cut_pt_max",&cut_pt_max,"cut_pt_max/F");
  TBranch* CUTPTE = cut_tree->Branch("cut_pt_e_max",&cut_pt_e_max,"cut_pt_e_max/F");
  TBranch* CUTEVIS = cut_tree->Branch("cut_evis_max",&cut_evis_max,"cut_evis_max/F");
  TBranch* CUTEVISSTRICT = cut_tree->Branch("evis_cut_strict",&evis_cut_strict,"evis_cut_strict/F");
  TBranch* CUTEVISTHRESHOLD = cut_tree->Branch("evis_threshold",&evis_threshold,"evis_threshold/F");
  
  TBranch* RC_pt = pt_tree->Branch("pT",&pT,"pT/F");
  TBranch* RC_pte = pte_tree->Branch("pT_e",&pT_e,"pT/F");
  

  TBranch* RC_Es = sigdef_tree->Branch("RCENE",&RCENE,"RCENE/F");
  TBranch* RC_THs = sigdef_tree->Branch("RCTHETA",&RCTHETA,"RCTHETA/F");
  TBranch* RC_PTs = sigdef_tree->Branch("RCPT",&RCPT,"RCPT/F");
  TBranch* RC_PT_BCals = sigdef_tree->Branch("RCPT_BCal",&RCPT_BCal,"RCPT_BCal/F");
  TBranch* RC_t = sigdef_tree->Branch("number_of_tracks",&number_of_tracks,"number_of_tracks/I");
  TBranch* ind_sig = sigdef_tree->Branch("events_sig_def",&events_sig_def,"events_sig_def/I");

  TBranch* RC_Ep = afterPt_tree->Branch("RCENE",&RCENE,"RCENE/F");
  TBranch* RC_THp = afterPt_tree->Branch("RCTHETA",&RCTHETA,"RCTHETA/F");
  TBranch* RC_PTp = afterPt_tree->Branch("RCPT",&RCPT,"RCPT/F");
  TBranch* RC_PT_BCalp = afterPt_tree->Branch("RCPT_BCal",&RCPT_BCal,"RCPT_BCal/F");
  TBranch* RC_Evis = afterPt_tree->Branch("Evis",&Evis,"Evis/F");
  TBranch* RC_Evis_strict = afterPt_tree->Branch("Evis_strict",&Evis_strict,"Evis_strict/F");
  TBranch* RC_Evis_CB = afterPt_tree->Branch("Evis_CB",&Evis_CB,"Evis_CB/F");  
  TBranch* ind_pt = afterPt_tree->Branch("events_afterPt",&events_afterPt,"events_afterPt/I");

  TBranch* RC_Ee = afterEvis_tree->Branch("RCENE",&RCENE,"RCENE/F");
  TBranch* RC_THe = afterEvis_tree->Branch("RCTHETA",&RCTHETA,"RCTHETA/F");
  TBranch* RC_PTe = afterEvis_tree->Branch("RCPT",&RCPT,"RCPT/F");
  TBranch* RC_PT_BCale = afterEvis_tree->Branch("RCPT_BCal",&RCPT_BCal,"RCPT_BCal/F");
  TBranch* RC_BCC = afterEvis_tree->Branch("BeamCalCluster",&BeamCalCluster,"BeamCalCluster/I");
  TBranch* RC_Evis2 = afterEvis_tree->Branch("Evis",&Evis,"Evis/F"); 
  TBranch* ind_evis = afterEvis_tree->Branch("events_afterEvis",&events_afterEvis,"events_afterEvis/I");

  TBranch* RC_E = sel_tree->Branch("RCENE",&RCENE,"RCENE/F");
  TBranch* RC_mox = sel_tree->Branch("RCMOX",&RCMOX,"RCMOX/F");
  TBranch* RC_moy = sel_tree->Branch("RCMOY",&RCMOY,"RCMOY/F");
  TBranch* RC_moz = sel_tree->Branch("RCMOZ",&RCMOZ,"RCMOZ/F");  
  TBranch* RC_TH = sel_tree->Branch("RCTHETA",&RCTHETA,"RCTHETA/F");
  TBranch* RC_PT = sel_tree->Branch("RCPT",&RCPT,"RCPT/F");
  TBranch* RC_PT_BCal = sel_tree->Branch("RCPT_BCal",&RCPT_BCal,"RCPT_BCal/F");
  TBranch* RC_rec = sel_tree->Branch("MRECOIL",&MRECOIL,"MRECOIL/F");
  TBranch* RC_phi = sel_tree->Branch("RCPHI",&RCPHI,"RCPHI/F");
  TBranch* RC_Ebc = sel_tree->Branch("BCalFrame_RCENE",&BCalFrame_RCENE,"BCalFrame_RCENE/F");
  TBranch* RC_moxbc = sel_tree->Branch("BCalFrame_RCMOX",&BCalFrame_RCMOX,"BCalFrame_RCMOX/F");
  TBranch* RC_THbc = sel_tree->Branch("BCalFrame_RCTHETA",&BCalFrame_RCTHETA,"BCalFrame_RCTHETA/F");
  TBranch* RC_phibc = sel_tree->Branch("BCalFrame_RCPHI",&BCalFrame_RCPHI,"BCalFrame_RCPHI/F");
  TBranch* ind_sel = sel_tree->Branch("events_selected",&events_selected,"events_selected/I");
  
  TBranch* RC_eSD = eff_tree->Branch("sigdef",&sigdef,"sigdef/F");
  TBranch* RC_ePT = eff_tree->Branch("eff_pT",&eff_pT,"eff_pT/F");
  TBranch* RC_eEvis = eff_tree->Branch("eff_Evis",&eff_Evis,"eff_Evis/F");
  TBranch* RC_eBC = eff_tree->Branch("eff_BCal",&eff_BCal,"eff_BCal/F");
  TBranch* RC_NSD = eff_tree->Branch("N_sigdef",&N_sigdef,"N_sigdef/I");
  TBranch* RC_NPT = eff_tree->Branch("N_after_pT_cut",&N_after_pT_cut,"N_after_pT_cut/I");
  TBranch* RC_NEvis = eff_tree->Branch("N_after_Evis_cut",&N_after_Evis_cut,"N_after_Evis_cut/I");
  TBranch* RC_Nsel = eff_tree->Branch("N_selected",&N_selected,"N_selected/I");

/////////////////// PROCESS AND CROSS SECTION FOR GLOBAL TREE

 
 int p = process_id;
  	if (p==1){
  		cout << "\n#####################################\t\t--- Neutrinos ---" << endl;	
  		cout << "\n\t\t\t\t\t P(e-) = -1, P(e+) = +1 \n#####################################" << endl;	
  		crosss=2.8093057E+04;
  		TBranch* Process = global_tree->Branch("Neutrinos",&Neutrinos,"Neutrinos/F");
  		TBranch* EP = global_tree->Branch("electron_polarisation",&electron_polarisation,"electron_polarisation/F");
  		electron_polarisation = -1;
  		TBranch* PP = global_tree->Branch("positron_polarisation",&positron_polarisation,"positron_polarisation/F");
  		positron_polarisation = 1;
  	}
  	  
  	  
  	  if (p==2){
  		cout << "\n#####################################\t\t--- Neutrinos ---" << endl;	
  		cout << "\n\t\t\t\t\t P(e-) = +1, P(e+) = -1 \n#####################################" << endl;	
  		crosss=1.9376141E+03;
  		TBranch* Process = global_tree->Branch("Neutrinos",&Neutrinos,"Neutrinos/F");
  		TBranch* EP = global_tree->Branch("electron_polarisation",&electron_polarisation,"electron_polarisation/F");
  		electron_polarisation = 1;
  		TBranch* PP = global_tree->Branch("positron_polarisation",&positron_polarisation,"positron_polarisation/F");
  		positron_polarisation = -1;
  	}

  	  if (p==3){
  		cout << "\n#####################################\t\t--- Bhabhas ---" << endl;	
  		cout << "\n\t\t\t\t\t P(e-) = -1, P(e+) = -1 \n#####################################" << endl;	
  		crosss=1.2391106E+05;
  		TBranch* Process = global_tree->Branch("Bhabhas",&Bhabhas,"Bhabhas/F");
  		TBranch* EP = global_tree->Branch("electron_polarisation",&electron_polarisation,"electron_polarisation/F");
  		electron_polarisation = -1;
  		TBranch* PP = global_tree->Branch("positron_polarisation",&positron_polarisation,"positron_polarisation/F");
  		positron_polarisation = -1;
  	}  

  	  if (p==4){
  		cout << "\n#####################################\t\t--- Bhabhas ---" << endl;	
  		cout << "\n\t\t\t\t\t P(e-) = -1, P(e+) = +1 \n#####################################" << endl;	
  		crosss=1.3307081E+05;
  		TBranch* Process = global_tree->Branch("Bhabhas",&Bhabhas,"Bhabhas/F");
  		TBranch* EP = global_tree->Branch("electron_polarisation",&electron_polarisation,"electron_polarisation/F");
  		electron_polarisation = -1;
  		TBranch* PP = global_tree->Branch("positron_polarisation",&positron_polarisation,"positron_polarisation/F");
  		positron_polarisation = 1;
  	}  

  	  if (p==5){
  		cout << "\n#####################################\t\t--- Bhabhas ---" << endl;	
  		cout << "\n\t\t\t\t\t P(e-) = +1, P(e+) = -1 \n#####################################" << endl;	
  		crosss=1.3023472E+05;
  		TBranch* Process = global_tree->Branch("Bhabhas",&Bhabhas,"Bhabhas/F");
  		TBranch* EP = global_tree->Branch("electron_polarisation",&electron_polarisation,"electron_polarisation/F");
  		electron_polarisation = 1;
  		TBranch* PP = global_tree->Branch("positron_polarisation",&positron_polarisation,"positron_polarisation/F");
  		positron_polarisation = -1;
  	}  

  	  if (p==6){
  		cout << "\n#####################################\t\t--- Bhabhas ---" << endl;	
  		cout << "\n\t\t\t\t\t P(e-) = +1, P(e+) = +1 \n#####################################" << endl;	
  		crosss=1.2391653E+05;
  		TBranch* Process = global_tree->Branch("Bhabhas",&Bhabhas,"Bhabhas/F");
  		TBranch* EP = global_tree->Branch("electron_polarisation",&electron_polarisation,"electron_polarisation/F");
  		electron_polarisation = 1;
  		TBranch* PP = global_tree->Branch("positron_polarisation",&positron_polarisation,"positron_polarisation/F");
  		positron_polarisation = 1;
  	}  


/////////////////////// LOOP OVER EVENTS

  cout << "lctuple file has " << n_entries << " entries" << endl;
  MCLumi = n_entries/crosss;
  N_events=n_entries;
  global_tree->Fill();
  cut_tree->Fill();

  float e_tot_strict(0), e_tot_hcal(0), e_tot_cb(0);
  float track_pt;
  int n_photons(0);
  float theta;


  //  ############# BOOK KEEPING
 
 
  int n_before = 0;
  int n_after_kinetic_cuts = 0;
  int n_after_evis_cut = 0;
  int n_after_pt_cut = 0;
  int n_after_bcal_cut = 0;
//  int n_after_all_cuts = 0; 
  int n_empty = 0; // no reco photons in event
  int rcori102=0;
  int n_barrel(0);
  int n_tracks(0);
  
  bool overlay=false;
  bool lepton=false;
  int mc;

  
  // ###################### LoohooPING OVER THE EVENTS
  cout << "number of events in file " << n_entries << endl;
  for (int i(0); i < 1000; i++){//n_entries
   if (i%1000 == 0){ printf("event %i\n",i);fflush(stdout);}
   //cout << "\n\n##########################\nEVENT " << i << endl;

   n_before++;
   bool sigdef_pass = false;
   bool pass = false;
   bool pt_pass = true;
   lctree->GetEntry(i);
   BCal_frame->GetEntry(i);
   bool photon = false;
   bool bcalhit=false;
   
  
   for (int n(0); n < nrec; n++){ // loop over the reco particles in the event
   	theta=acos(rcmoz[n]/sqrt(rcmox[n]*rcmox[n]+rcmoy[n]*rcmoy[n]+rcmoz[n]*rcmoz[n]))*180/PI;
   if (rcori[n]==101){
   	n_barrel++;
	    //if(rccha[n]==0){
	   		if((rcene[n]>evis_threshold)&&(n!=indexPT)){
		    		//e_tot+=rcene[n];
		    		if (rctyp[n]==22||rctyp[n]==11||rctyp[n]==-11||rctyp[n]==13||rctyp[n]==-13||rctyp[n]==310||rctyp[n]==3122||rctyp[n]==-3122){
		    			e_tot_strict+=rcene[n];
		    		}
		    		if (rctyp[n]==2112||rctyp[n]==211||rctyp[n]==-211){
		    			e_tot_hcal+=rcene[n];
		    		}
			}
			if(n!=indexPT){
				e_tot_cb+=rcene[n];
			}
	    //}
	    if (rctyp[n] == 22){
     	n_photons++;
         }
	//    pt_pass=true;
	    if(rccha[n]!=0 ){
//	     cout << " I FOUND A TRACK in event " << i << endl;
     	n_tracks++;
     	track_pt = sqrt( (rcmox[n]*rcmox[n]) + (rcmoy[n]*rcmoy[n]) );
//     cout << '\n' << " with a p_t of " << track_pt << endl;
     		if (track_pt > pt_cut){
		      pt_pass = false;
//      cout << " ... so event " << i << " is rejected !" << endl;
     		}
     		else {
     			if (((rctyp[n]==11)||(rctyp[n]==-11))&&(track_pt>cut_pt_e_max)){
     				pt_pass = false;
     			}
     		}
    		}
   	} // if not in BCal  
   	
  	
   	if(rcori[n]==102){
//   	cout << theta << endl;
/*	if (rcori[n]==102){
		rcori101++;
	}*/
   	bcalhit=true;
   	rcori102++;
//   	cout << i << " : BCAL HIT " << endl;
   	}  
   } // nrec loop
//   cout << i << '\t' << n_tracks << '\t' << track_pt << endl;
   
//   cout << "event: " << i << " status of pt_pass 1: " << pt_pass << endl;
   //cout << "\n\nnumber of photons: " << n_photons << endl;
   if (n_photons==0){
//    cout << "not a single reconstructed photon in event "<< i << " :( " << endl;
    photon=false;
   }
   else {
//    cout << "\nthere are " << n_photons << " reconstructed photons in event " << i << endl;
    photon =true;
   }
   n_photons=0;

	// ####################### applying cuts, selecting events, calculating efficiencies
   
   
   if (photon==true){
//    BCal_frame->GetEntry(i);
//    cout << "BCal frame: " << RCENE_BCal_photon[0] << endl;
//    cout << "BCal frame: " << RCMOX_BCal_photon[0] << endl;
    float photoncostheta = rcmoz[indexPT]/sqrt((rcmox[indexPT]*rcmox[indexPT])+(rcmoy[indexPT]*rcmoy[indexPT])+(rcmoz[indexPT]*rcmoz[indexPT]));
    float photonpt = sqrt( (RCMOX_BCal_photon_PTmax[0]*RCMOX_BCal_photon_PTmax[0]) + (rcmoy[indexPT]*rcmoy[indexPT]) );
    float photonphi = atan2(rcmoy[indexPT],RCMOX_BCal_photon_PTmax[0])*180/PI;
    if (TMath::Abs(photonphi) > phi_step){
    	if (rcene[indexPT]> cut_e_min_out && rcene[indexPT] < E_max && TMath::Abs(photoncostheta) < costheta_cut && photonpt > pt_min_out){
    		sigdef_pass = true;
    	}
    //cout << "--- electron around outgoing beam pipe (photon phi: " << photonphi << ")" << endl;
    }
     else { 
      if (rcene[indexPT]> cut_e_min_in && rcene[indexPT] < E_max && TMath::Abs(photoncostheta) < costheta_cut && photonpt > pt_min_in){
    		sigdef_pass = true;
    	}
     //cout << "XXXXX electron around INCOMING beam pipe (photon phi: " << photonphi << ")" << endl;
     }
    if (sigdef_pass == true){
     n_after_kinetic_cuts++;
//	cout << "EVENT: " << i << " status of pt_pass 2: " << pt_pass << endl;
     RCENE=rcene[indexPT];
     RCTHETA=acos(rcmoz[indexPT]/sqrt(rcmox[indexPT]*rcmox[indexPT]+rcmoy[indexPT]*rcmoy[indexPT]+rcmoz[indexPT]*rcmoz[indexPT]))*180/PI;
     RCPT=sqrt(rcmox[indexPT]*rcmox[indexPT]+rcmoy[indexPT]*rcmoy[indexPT]);
     RCPT_BCal=sqrt( (RCMOX_BCal_photon_PTmax[0]*RCMOX_BCal_photon_PTmax[0]) + (rcmoy[indexPT]*rcmoy[indexPT]) );

     number_of_tracks=n_tracks;
     events_sig_def=i;
    // sigdef_tree->Fill();
     
     for (int m(0); m < nrec; m++){
     	if((rccha[m]!=0)&&(rctyp[m]!=11)&&(rctyp[m]!=-11)){
     		pT = sqrt( (rcmox[m]*rcmox[m]) + (rcmoy[m]*rcmoy[m]) );
     		pt_tree->Fill();
     	}
     	if((rctyp[m]==11)||(rctyp[m]==-11)){
     		pT_e = sqrt( (rcmox[m]*rcmox[m]) + (rcmoy[m]*rcmoy[m]) );
     		pte_tree->Fill();
     	}
     	
     }
     if (pt_pass==true){
//      cout << " still true ? " << endl;
      n_after_pt_cut++;
      
      
             for (int r(0); r<nrec; r++){
        	if (rcori[r]==101){
        		for (int k(0); k<r2mnrel; k++){
     			if (r2mf[k]==r){
     				mc=r2mt[k];  				
     				int simstat=mcsst[mc];
     				if(simstat & (0x1<<23)){
     					overlay=true;
     				}
     			}
			}
        		if (rctyp[r]==22&&r!=indexPT){
   				PDG_energy = rcene[r];
   				if (overlay==true){
   					photon_o_tree->Fill();
   				}
   				if (overlay==false){
   					for (int k(0); k<r2mnrel; k++){
   						if (r2mf[k]==r){
   							mc=r2mt[k];
   							if (((mc==6)||(mc==7))&&((mcpdg[mc]==11)||(mcpdg[mc]==-11))){
   								lepton=true;
   								photon_e_tree->Fill();
   								cout << "E=" << rcene[r] << " TH=" << acos(rcmoz[r]/sqrt(rcmox[r]*rcmox[r]+rcmoy[r]*rcmoy[r]+rcmoz[r]*rcmoz[r]))*180/PI << endl;
   							}
   						}
   					}
   				}
   				if ((overlay==false)&&(lepton==false)){
   					photon_r_tree->Fill();
   				}
	   		}
	   		if (rctyp[r]==-11||rctyp[r]==11){
	   			PDG_energy = rcene[r];
	   			if (overlay==true){
   					electron_o_tree->Fill();
   				}
   				if (overlay==false){
   					electron_r_tree->Fill();
   				}
	   		} 
	   		if (rctyp[r]==-13||rctyp[r]==13){
	   			PDG_energy = rcene[r];
	   			if (overlay==true){
   					muon_o_tree->Fill();
   				}
   				if (overlay==false){
   					muon_r_tree->Fill();
   				}	   			
	   		} 
	   		if (rctyp[r]==-3122||rctyp[r]==3122||rctyp[r]==310){
	   			PDG_energy = rcene[r];
	   			if (overlay==true){
   					V0_o_tree->Fill();
   				}
   				if (overlay==false){
   					V0_r_tree->Fill();
   				}	   		   			
	   		} 
	   		if (rctyp[r]==2112){
	   			PDG_energy = rcene[r];
	   			if (overlay==true){
   					neutron_o_tree->Fill();
   				}
   				if (overlay==false){
   					neutron_r_tree->Fill();
   					if (PDG_energy>50&&PDG_energy<70){
   						MC_pdg=mcpdg[mc];
   						neutron_theta=acos(rcmoz[r]/sqrt(rcmox[r]*rcmox[r]+rcmoy[r]*rcmoy[r]+rcmoz[r]*rcmoz[r]))*180/PI;
   						Eg_sig=RCENE;
   						neutron_50_70_tree->Fill();
   					}
   					if (PDG_energy>80&&PDG_energy<100){
   						MC_pdg=mcpdg[mc];
   						neutron_theta=acos(rcmoz[r]/sqrt(rcmox[r]*rcmox[r]+rcmoy[r]*rcmoy[r]+rcmoz[r]*rcmoz[r]))*180/PI;
   						Eg_sig=RCENE;
   						neutron_80_100_tree->Fill();
   					} 
   					if (PDG_energy>110&&PDG_energy<130){
   						MC_pdg=mcpdg[mc];
   						neutron_theta=acos(rcmoz[r]/sqrt(rcmox[r]*rcmox[r]+rcmoy[r]*rcmoy[r]+rcmoz[r]*rcmoz[r]))*180/PI;
   						Eg_sig=RCENE;
   						neutron_110_130_tree->Fill();
   					}   				
   				}

	   		} 
	   		if (rctyp[r]==-211||rctyp[r]==211){
	   			PDG_energy = rcene[r];
	   			if (overlay==true){
   					pion_o_tree->Fill();
   				}
   				if (overlay==false){
   					pion_r_tree->Fill();
   				}	   	
	   		} 
	   	} // if rcori==1 meaning it's a Pandora PFO
	     overlay=false;
	     lepton=false;
	    } // 2nd rec loop
      
      
      
      
      
      pass=true;
      RCENE=rcene[indexPT];
      RCTHETA=acos(rcmoz[indexPT]/sqrt(rcmox[indexPT]*rcmox[indexPT]+rcmoy[indexPT]*rcmoy[indexPT]+rcmoz[indexPT]*rcmoz[indexPT]))*180/PI;
      //Evis=e_tot;
      Evis_strict=e_tot_strict;
      Evis_CB=e_tot_cb;
      events_afterPt=i;
   //   afterPt_tree->Fill();
//      cout << " and no track found " << endl;
//      cout << " \t\t\t\t##### event " << i << ", total energy in detector: " << e_tot << endl;
//      cout << " \t\t\t\t##### energy of most energetic photon: " << rcene[indexPT] << endl;
      
 //        	cout << "\n\nVISIBLE ENERGY IN THE EVENT: " << e_tot << endl;
 //  	cout << "Signal Photon energy: " << rcene[indexPT] << endl;
 //  	cout << "is the difference more than 20? " << Evis << endl;
     /* if (e_tot<=evis_cut&&e_tot_strict<=evis_cut_strict){
 //     cout << "no -> keep event" <<endl;
       n_after_evis_cut++;
//       cout << "this means that detector is empty enough (etot - eg < 20)" << endl;
       pass = true;
       RCENE=rcene[indexPT];
       RCTHETA=acos(rcmoz[indexPT]/sqrt(rcmox[indexPT]*rcmox[indexPT]+rcmoy[indexPT]*rcmoy[indexPT]+rcmoz[indexPT]*rcmoz[indexPT]))*180/PI;
       BeamCalCluster=rcori102;
       events_afterEvis=i;
       afterEvis_tree->Fill();
       if (bcalhit==false){
        n_after_bcal_cut++;
        pass=true;
        RCENE=rcene[indexPT];
        RCMOX=rcmox[indexPT];
        RCMOY=rcmoy[indexPT];
        RCMOZ=rcmoz[indexPT];
        RCTHETA=acos(rcmoz[indexPT]/sqrt(rcmox[indexPT]*rcmox[indexPT]+rcmoy[indexPT]*rcmoy[indexPT]+rcmoz[indexPT]*rcmoz[indexPT]))*180/PI;
        RCPHI=atan2(rcmoy[indexPT],rcmox[indexPT])*180/PI;;
        BCalFrame_RCENE=RCENE_BCal_photon_PTmax[0];
        BCalFrame_RCMOX=RCMOX_BCal_photon_PTmax[0];
        BCalFrame_RCTHETA=acos(rcmoz[indexPT]/sqrt((RCMOX_BCal_photon_PTmax[0]*RCMOX_BCal_photon_PTmax[0])+(rcmoy[indexPT]*rcmoy[indexPT])+(rcmoz[indexPT]*rcmoz[indexPT])))*180/PI;
        BCalFrame_RCPHI=atan2(rcmoy[indexPT],RCMOX_BCal_photon_PTmax[0])*180/PI;
        MRECOIL=500*500-2*500*rcene[indexPT];
        events_selected=i;
        sel_tree->Fill();
       }
      }*/ // evis cut 
//      else {pass=false};
     } // pt cut
    } // kin cuts
   } // photon found
  // e_tot=0;
   e_tot_strict=0;
   e_tot_hcal=0;
   e_tot_cb=0;
   rcori102=0;
   bcalhit=false;
   sigdef_pass=false;
   track_pt=0;
   n_tracks=0;
  }
  global_tree->Write();
  cut_tree->Write();
  pt_tree->Write();
  pte_tree->Write();
  sigdef_tree->Write();
  afterPt_tree->Write();
  afterEvis_tree->Write();
  sel_tree->Write();
  
  sigdef = (float)(n_after_kinetic_cuts)/(float)(n_before);
  eff_pT = (float)(n_after_pt_cut)/(float)(n_after_kinetic_cuts);
  eff_Evis = (float)(n_after_evis_cut)/(float)(n_after_kinetic_cuts);
  eff_BCal = (float)(n_after_bcal_cut)/(float)(n_after_kinetic_cuts);
  N_sigdef = n_after_kinetic_cuts;
  N_after_pT_cut = n_after_pt_cut;
  N_after_Evis_cut = n_after_evis_cut;
  N_selected = n_after_bcal_cut;
  eff_tree->Fill();
  eff_tree->Write();
  
    photon_o_tree->Write();
    electron_o_tree->Write();
    muon_o_tree->Write();
    V0_o_tree->Write();
    neutron_o_tree->Write();
    pion_o_tree->Write();
    
    photon_r_tree->Write();
    electron_r_tree->Write();
    muon_r_tree->Write();
    V0_r_tree->Write();
    neutron_r_tree->Write();
    pion_r_tree->Write();
    
    neutron_50_70_tree->Write();
    neutron_80_100_tree->Write();
    neutron_110_130_tree->Write();
    
    photon_e_tree->Write();
  
  
  cout << "\nPFOs/Barrel = " << n_barrel << endl;
  cout << "\nCross Section = " << crosss << "fb\tNumber of Events = " << n_entries << "\tMCLumi = " << MCLumi << " fb^(-1)" << endl;
  cout << "\nfinal cut flow: \n\tinitial number of events:\t\t\t\t" << n_before;
	  cout << "\n\tnumber of photons that fulfill signal definition:\t" << n_after_kinetic_cuts << " => " << sigdef*100 << "%";
  cout << "\n\tnumber of events that fulfill pt cut:\t\t\t" << n_after_pt_cut << " => (" << (float)(n_after_pt_cut)/(float)(n_before)*100 << "%) => " << eff_pT*100 << "%" << endl;
  cout << "\tnumber of events that fulfill Evis cut:\t\t\t" << n_after_evis_cut << " => (" << (float)(n_after_evis_cut)/(float)(n_before)*100 << "%) => " << (float)(n_after_evis_cut)/(float)(n_after_kinetic_cuts)*100 << "%" << endl;
  cout << "\tnumber of events that fulfill BCal cut:\t\t\t" << n_after_bcal_cut << " => (" << (float)(n_after_bcal_cut)/(float)(n_before)*100 << "%) => " << eff_BCal*100 << "%" << endl;


  f->Close();
  g->Close();
  delete f;
 

  return;
}

void load_and_select(double e_min, double e_max ,double cos_theta, double PT_out, double PT_in, double PHI_step, double cut_PT, double cut_PT_e, double cut_EVIS, double cut_EVIS_strict, double cut_evis_THRESHOLD, int prID){

  E_min = e_min;
  E_max = e_max;
  costheta_cut = cos_theta;
  pt_min_out = PT_out;
  pt_min_in = PT_in;
  phi_step = PHI_step;
  cut_pt = cut_PT;
  cut_pt_e = cut_PT_e;
  cut_evis = cut_EVIS;
  cut_evis_strict = cut_EVIS_strict;
  threshold_evis = cut_evis_THRESHOLD;
  process_id = prID;
  
  run_load_and_select();
  
  return;

}
