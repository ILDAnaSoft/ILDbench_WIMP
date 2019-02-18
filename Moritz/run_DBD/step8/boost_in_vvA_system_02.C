#include <string>
#include <TTree.h>
#include <iostream>
#include <iterator>     // std::distance
#include <vector>
#include <TLorentzVector.h>
//using std::vector;
#define PI 3.14159265

int run_id;



void run_boost_in_vvA_system(){

  cout << "\n\n\n------------ boost in vvA system --------------\n";
  
  

//   char filename[256];
   
   // Select input file; process is given by last input variable run_id
   
  TString inputfilename;
  TString outputfilename;
  if (run_id==1){
    cout << "Neutrinos, P(e-) = -1, P(e+) = +1" << endl;
    inputfilename = "../step2/vv_LR.root";
    outputfilename = "vv_boost_LR.root";
  }
 
  if (run_id==2){
    cout << "Neutrinos, P(e-) = +1, P(e+) = -1" << endl;  
    inputfilename = "../step2/vv_RL.root";
    outputfilename = "vv_boost_RL.root";
  }

  cout << "Input file:\t\t\t" << inputfilename << endl;
  cout << "Output file:\t\t\t" << outputfilename << endl;
  
  TFile* f = new TFile(inputfilename,"r");
  TTree* globaltree = (TTree*)f->Get("global");
  
  TFile* g = new TFile(outputfilename, "RECREATE");  
  cout << "\nCopying Global Tree" << endl;
  TTree *newglobaltree = globaltree->CopyTree("");  
  
  TTree* seltree = (TTree*)f->Get("selected_photons"); 
  
  Float_t RCENE[1], RCPHI[1], RCTHETA, MCMOX_6, MCMOX_7, MCMOX_A, MCMOY_6, MCMOY_7, MCMOZ_6, MCMOZ_7, MCMOZ_A, MCMOY_A, MCENE_6, MCENE_7, MCENE_A;
  Int_t events_selected[1];
 
  seltree->SetBranchAddress("RCENE",RCENE);
  seltree->SetBranchAddress("RCPHI",&RCPHI);
  seltree->SetBranchAddress("RCTHETA",&RCTHETA);
  seltree->SetBranchAddress("MCMOX_6",&MCMOX_6);
  seltree->SetBranchAddress("MCMOY_6",&MCMOY_6);
  seltree->SetBranchAddress("MCMOZ_6",&MCMOZ_6);
  seltree->SetBranchAddress("MCENE_6",&MCENE_6);
  seltree->SetBranchAddress("MCMOX_7",&MCMOX_7);
  seltree->SetBranchAddress("MCMOY_7",&MCMOY_7);
  seltree->SetBranchAddress("MCMOZ_7",&MCMOZ_7);
  seltree->SetBranchAddress("MCENE_7",&MCENE_7);
  seltree->SetBranchAddress("MCMOX_A",&MCMOX_A);
  seltree->SetBranchAddress("MCMOY_A",&MCMOY_A);
  seltree->SetBranchAddress("MCMOZ_A",&MCMOZ_A);
  seltree->SetBranchAddress("MCENE_A",&MCENE_A);
  seltree->SetBranchAddress("events_selected",&events_selected);
  
  Float_t rcene, rcphi, rctheta, sqrts_star, mcene_star, mctheta_star, mcphi_star;
  Int_t Events_selected;
  
  TTree* new_tree = new TTree("selected_photons","selected_photons");
  
  TBranch* NEWRCE = new_tree->Branch("rcene",&rcene,"rcene/F");
  TBranch* NEWRCP = new_tree->Branch("rcphi",&rcphi,"rcphi/F");
  TBranch* NEWRCT = new_tree->Branch("rctheta",&rctheta,"rctheta/F");
  TBranch* NEWSQSS = new_tree->Branch("sqrts_star",&sqrts_star,"sqrts_star/F");
  TBranch* NEWMCES = new_tree->Branch("mcene_star",&mcene_star,"mcene_star/F");
  TBranch* NEWMCTS = new_tree->Branch("mctheta_star",&mctheta_star,"mctheta_star/F");
  TBranch* NEWMCPS = new_tree->Branch("mcphi_star",&mcphi_star,"mcphi_star/F");
  TBranch* NEWESEL = new_tree->Branch("Events_selected",&Events_selected,"Events_selected/I");
  
  TTree* out_tree = new TTree("photons_outside","photons_outside");
  
  TBranch* OUTRCE = out_tree->Branch("rcene",&rcene,"rcene/F");
  TBranch* OUTRCP = out_tree->Branch("rcphi",&rcphi,"rcphi/F");
  TBranch* OUTRCT = out_tree->Branch("rctheta",&rctheta,"rctheta/F");
  TBranch* OUTSQSS = out_tree->Branch("sqrts_star",&sqrts_star,"sqrts_star/F");
  TBranch* OUTMCES = out_tree->Branch("mcene_star",&mcene_star,"mcene_star/F");
  TBranch* OUTMCTS = out_tree->Branch("mctheta_star",&mctheta_star,"mctheta_star/F");
  TBranch* OUTMCPS = out_tree->Branch("mcphi_star",&mcphi_star,"mcphi_star/F");
 
  
    
  int n_entries = seltree->GetEntries();
  
  float theta_min(90);
  int n_outside(0);
  
  cout << "in this run, there are " << n_entries << " entries" << endl;
  
  for (int i(0); i < n_entries; i++){//n_entries
   if (i%100000 == 0){ printf("event %i\n",i);fflush(stdout);}
   
   seltree->GetEntry(i);
   
   TLorentzVector vnu(MCMOX_6,MCMOY_6,MCMOZ_6,MCENE_6);
   TLorentzVector vanu(MCMOX_7,MCMOY_7,MCMOZ_7,MCENE_7);
   TLorentzVector vA(MCMOX_A,MCMOY_A,MCMOZ_A,MCENE_A);
   TLorentzVector cms = vnu + vanu + vA;
   TVector3 bv = cms.BoostVector();
   vA.Boost(-bv);
   cms.Boost(-bv);
   mcene_star=vA.E();
   sqrts_star=cms.E();
   mctheta_star=vA.Theta()*180/PI;
   mcphi_star=vA.Phi()*180/PI;
   rcene=RCENE[0];
   rcphi=RCPHI[0];
   rctheta=RCTHETA;
   Events_selected=events_selected[0];
      
   if (mctheta_star<theta_min){
   	theta_min = mctheta_star;
   }
   
   double coscut7 = 0.992546;
   double ptmin_small = 1.92; // phi-dependent: either 1.92 or 5.65
   double e_thresh_small = 15.75; // 15.75 for ptmin=1.92 and 46.36 for ptmin=5.65
   double ptmin_large = 5.65; // phi-dependent: either 1.92 or 5.65
   double e_thresh_large = 46.36; // 15.75 for ptmin=1.92 and 46.36 for ptmin=5.65
   double coscut, ptmin, e_thresh;
   int ph;

   if (TMath::Abs(RCPHI[0])>35){
      	ptmin=ptmin_small;
  		e_thresh=e_thresh_small;
      }
      if (TMath::Abs(RCPHI[0])<=35){
  		ptmin=ptmin_large;
  		e_thresh=e_thresh_large;
   }

   if (mcene_star <= ptmin){
    	coscut=.1;
   }
   if (mcene_star > e_thresh && mcene_star > ptmin){
   	coscut=coscut7;
   }
   if (mcene_star < e_thresh && mcene_star > ptmin){
    	coscut=sqrt(mcene_star*mcene_star-ptmin*ptmin)/mcene_star;
   }
   
//   cout << cos(theta_min*PI/180.) << " vs " << coscut << endl;
   if (TMath::Abs(cos(mctheta_star*PI/180.))>coscut){
   	n_outside++;
   	out_tree->Fill();
   	}
   
   new_tree->Fill();
   
  }
  
  newglobaltree->Write();
  new_tree->Write();
  out_tree->Write();
  
  f->Close();
  g->Close();
  delete f;
  
  cout << "\n\nSmallest theta found: " << theta_min << " or costheta: " << cos(theta_min*PI/180.) << endl;
  
  cout << "\n\n" << n_outside << " entries are not covered by theta integral" << endl;
 

  return;
}

void boost_in_vvA_system(int runID){

  run_id = runID;
  
  run_boost_in_vvA_system();
  
  return;

}
