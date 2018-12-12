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
int process_id;



void run_load_and_select(){

  cout << "\n\n\n------------running load_and_select--------------\n";

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
  Int_t mcpa0[2222];
  Int_t mcpa1[2222];
  Int_t mcda0[2222];
  Int_t mcda1[2222];
  Int_t mcda2[2222];
  Int_t mcda3[2222];
  Int_t mcda4[2222];

  
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
  outputfilename = "vv_LR_PT_origin.root";
  }
 
  if (process_id==2){
  cout << "Neutrinos, P(e-) = +1, P(e+) = -1" << endl;  
  inputfilename = "../step1/boosted_vv_RL.root";
  outputfilename = "vv_RL_PT_origin.root";
  }
  
  if (process_id==3){
  cout << "Bhabhas, P(e-) = -1, P(e+) = -1" << endl;
  inputfilename = "../step1/boosted_bhabhas_LL.root";
  outputfilename = "bhabhas_LL_PT_origin.root";
  }

  if (process_id==4){
  cout << "Bhabhas, P(e-) = -1, P(e+) = +1" << endl;
  inputfilename = "../step1/boosted_bhabhas_LR.root";
  outputfilename = "bhabhas_LR_PT_origin.root";
  }
  
  if (process_id==5){
  cout << "Bhabhas, P(e-) = +1, P(e+) = -1" << endl;
  inputfilename = "../step1/boosted_bhabhas_RL.root";
  outputfilename = "bhabhas_RL_PT_origin.root";
  }
  
  if (process_id==6){
  cout << "Bhabhas, P(e-) = +1, P(e+) = +1" << endl;
  inputfilename = "../step1/boosted_bhabhas_RR_.root";
  outputfilename = "bhabhas_RR_PT_origin.root";
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

  TTree* pt_tree = new TTree("pt_charged_after_signaldef","pt_charged_after_signaldef");
  TTree* pte_tree = new TTree("pt_electron_after_signaldef","pt_electron_after_signaldef");
 
  TTree* overlay_tree = new TTree("chargedPTs_from_overlay","chargedPTs_from_overlay");
  TTree* MEp_tree = new TTree("chargedPTs_from_MEphotons","chargedPTs_from_MEphotons"); 
  TTree* others_tree = new TTree("chargedPTs_from_rest","chargedPTs_from_rest");

  TTree* overlay_e_tree = new TTree("electronPTs_from_overlay","electronPTs_from_overlay");
  TTree* MEp_e_tree = new TTree("electronPTs_from_MEphotons","electronPTs_from_MEphotons"); 
  TTree* others_e_tree = new TTree("electronPTs_from_rest","electronPTs_from_rest");
  
  float pt_overlay, pt_MEp, pt_other;
  
  TBranch* pto = overlay_tree->Branch("pt_overlay",&pt_overlay,"pt_overlay/F");
  TBranch* ptp = MEp_tree->Branch("pt_MEp",&pt_MEp,"pt_MEp/F");
  TBranch* ptr =others_tree->Branch("pt_other",&pt_other,"pt_other/F");

  TBranch* ptoe = overlay_e_tree->Branch("pt_overlay",&pt_overlay,"pt_overlay/F");
  TBranch* ptpe = MEp_e_tree->Branch("pt_MEp",&pt_MEp,"pt_MEp/F");
  TBranch* ptre =others_e_tree->Branch("pt_other",&pt_other,"pt_other/F");
  
  float pT, pT_e, Evis_init, Evis, Evis_strict, Evis_CB, RCENE, RCMOX, RCMOY, RCMOZ, RCTHETA, RCPT, RCPT_BCal, MRECOIL, sigdef, eff_pT, eff_Evis, eff_BCal, RCPHI, BCalFrame_RCENE, BCalFrame_RCMOX, BCalFrame_RCTHETA, BCalFrame_RCPHI, Neutrinos, Bhabhas, electron_polarisation, positron_polarisation;
  int BeamCalCluster_init, BeamCalCluster, number_of_tracks;
  int N_sigdef, N_after_pT_cut, N_after_Evis_cut, N_selected;

  float cut_e_min_out, cut_e_max, cut_costheta_cut, cut_cos_theta, cut_PT_out, cut_e_min_in, cut_PT_in, cut_PHI_step, evis_cut, evis_cut_strict, evis_threshold, cut_evis_max, pt_cut, cut_pt_max;
  
  int events_sig_def, events_afterPt, events_afterEvis, events_selected;

  cut_e_min_out = E_min;
  cut_e_max = E_max;
  cut_cos_theta = costheta_cut;
  cut_PT_out = pt_min_out;
  cut_e_min_in = E_min;
  cut_PT_in = pt_min_in;
  cut_PHI_step = phi_step;

  TBranch* RC_pt = pt_tree->Branch("pT",&pT,"pT/F");
  TBranch* RC_pte = pte_tree->Branch("pT_e",&pT_e,"pT/F");  

/////////////////////// LOOP OVER EVENTS

  cout << "lctuple file has " << n_entries << " entries" << endl;
  MCLumi = n_entries/crosss;
  N_events=n_entries;

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
  int n_electrons(0);
  
  bool overlay = false;
  bool ME_p = false;
  int n_overlay(0), n_MEp(0), n_other(0);
  int n_e_overlay(0), n_e_MEp(0), n_e_other(0);
  
  
  // ###################### LoohooPING OVER THE EVENTS
  cout << "number of events in file " << n_entries << endl;
  for (int i(0); i < n_entries; i++){//n_entries
   if (i%500000 == 0){ printf("event %i\n",i);fflush(stdout);}
   //cout << "\n\n##########################\nEVENT " << i << endl;

   n_before++;
   bool sigdef_pass = false;
   bool pass = false;
   bool pt_pass = true;
   lctree->GetEntry(i);
   BCal_frame->GetEntry(i);
   bool photon = false;
   bool bcalhit=false;
   
   int mc;
  
   for (int n(0); n < nrec; n++){ // loop over the reco particles in the event
   	theta=acos(rcmoz[n]/sqrt(rcmox[n]*rcmox[n]+rcmoy[n]*rcmoy[n]+rcmoz[n]*rcmoz[n]))*180/PI;
   if (rcori[n]==101){
   	n_barrel++;
	    //if(rccha[n]==0){
	    //}
	    if (rctyp[n] == 22){
     	n_photons++;
         }
   	} // if not in BCal  
   } // nrec loop
   if (n_photons==0){
    photon=false;
   }
   else {
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
    }
     else { 
      if (rcene[indexPT]> cut_e_min_in && rcene[indexPT] < E_max && TMath::Abs(photoncostheta) < costheta_cut && photonpt > pt_min_in){
    		sigdef_pass = true;
    	}
     }
    if (sigdef_pass == true){
     
     for (int m(0); m < nrec; m++){
     	if ((rccha[m]!=0)&&(rctyp[m]!=11)&&(rctyp[m]!=-11)){
     		pT = sqrt( (rcmox[m]*rcmox[m]) + (rcmoy[m]*rcmoy[m]) );
     		pt_tree->Fill();
     		n_tracks++;
     			for (int k(0); k<r2mnrel; k++){
     				if (r2mf[k]==m){
     					mc=r2mt[k];
     					//pT = sqrt( (mcmox[mc]*mcmox[mc]) + (mcmoy[mc]*mcmoy[mc]) );   				
     					int simstat=mcsst[mc];
     					if(simstat & (0x1<<23)){
     						//cout << "\tOVERLAY" << endl;
     						overlay=true;
     						n_overlay++;
     						pt_overlay=pT;
     						overlay_tree->Fill();
						}	
     					if (overlay==false){
     					
     						int parent=mcpa0[mc];
     						if ((parent==8)||(parent==9)||(parent==10)||(parent==11)){
     						
     							if ((mcpdg[parent]==22)&&(mcpa0[parent]==2)){
     								ME_p=true;
     								pt_MEp=pT;
     								MEp_tree->Fill();
     								n_MEp++;
     							}
     						}
     						/*else { if ((mcpa0[parent]==8)||(mcpa0[parent]==9)||(mcpa0[parent]==10)||(mcpa0[parent]==8)){
     							int grandparent=mcpa0[parent];
     							if ((mcpdg[grandparent]==2)&&(mcpa0[grandparent]==2)){
     								cout << "ancestor ME photon" << endl;
     								ME_p=true;	
     								pt_MEp=pT_e;
     								MEp_tree->Fill();
     								n_MEp++;		
     							}
     						}
     						}*/
     					} // not overlay      				
     				} // if found truth
     			} // truth link loop
     	if (ME_p==false&&overlay==false){
     		n_other++;
     		pt_other=pT;
     		others_tree->Fill();
     	}
     	} // only charged particles
     	
     	
     	
     	if ((rctyp[m]==11)||(rctyp[m]==-11)){
     		pT_e = sqrt( (rcmox[m]*rcmox[m]) + (rcmoy[m]*rcmoy[m]) );
     		pte_tree->Fill();
     		n_electrons++;
     			for (int k(0); k<r2mnrel; k++){
     				if (r2mf[k]==m){
     					mc=r2mt[k];
     					int simstat=mcsst[mc];
     					if(simstat & (0x1<<23)){
     						//cout << "\tOVERLAY" << endl;
     						overlay=true;
     						n_e_overlay++;
     						pt_overlay=pT_e;
     						overlay_e_tree->Fill();
						}	
     					if (overlay==false){
     						int parent=mcpa0[mc];
     						if ((parent==8)||(parent==9)||(parent==10)||(parent==11)){
     						
     							if ((mcpdg[parent]==22)&&(mcpa0[parent]==2)){
     								ME_p=true;
     								pt_MEp=pT_e;
     								MEp_e_tree->Fill();
     								n_e_MEp++;
     							}
     						}
     						/*else { if ((mcpa0[parent]==8)||(mcpa0[parent]==9)||(mcpa0[parent]==10)||(mcpa0[parent]==8)){
     							int grandparent=mcpa0[parent];
     							if ((mcpdg[grandparent]==2)&&(mcpa0[grandparent]==2)){
     								cout << "ancestor ME photon" << endl;
     								ME_p=true;	
     								pt_MEp=pT_e;
     								MEp_e_tree->Fill();
     								n_e_MEp++;		
     							}
     						}
     						}*/
     					} // not overlay      				
     				} // if found truth
     			} // truth link loop
     	if (ME_p==false&&overlay==false){
     		n_e_other++;
     		pt_other=pT_e;
     		others_e_tree->Fill();
     	}
     	} // only electrons
     	
     	
     	
     	
   		sigdef_pass = false;
		overlay = false;
   		ME_p=false;     	
     } // nrec loop
    } // kin cuts
   } // photon found

  } // event loop
 pt_tree->Write();
 overlay_tree->Write();
 MEp_tree->Write();
 others_tree->Write();
 pte_tree->Write();
 overlay_e_tree->Write();
 MEp_e_tree->Write();
 others_e_tree->Write();  

  

  f->Close();
  g->Close();

	cout << "\n\nOrigin of the " << n_tracks << " charged particles: " << endl;
	cout << "\tOverlay:\t" << n_overlay << endl;
	cout << "\tME photons:\t" << n_MEp << endl;
	cout << "\tother sources:\t" << n_other << endl;
	cout << "\t(sum:\t" << n_overlay+n_MEp+n_other << ")" << endl;

	cout << "\n\nOrigin of the " << n_electrons << " electrons: " << endl;
	cout << "\tOverlay:\t" << n_e_overlay << endl;
	cout << "\tME photons:\t" << n_e_MEp << endl;
	cout << "\tother sources:\t" << n_e_other << endl;
	cout << "\t(sum:\t" << n_e_overlay+n_e_MEp+n_e_other << ")" << endl;

  return;
}

void load_and_select(double e_min, double e_max ,double cos_theta, double PT_out, double PT_in, double PHI_step, int prID){

  E_min = e_min;
  E_max = e_max;
  costheta_cut = cos_theta;
  pt_min_out = PT_out;
  pt_min_in = PT_in;
  phi_step = PHI_step;
  process_id = prID;
  
  run_load_and_select();
  
  return;

}
