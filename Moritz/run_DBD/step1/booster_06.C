#include <iostream>

void boost_in_BCal_frame(int prID){
 TFile* f =0;
 TFile* g =0;

 float boost_angle = -0.007; // This angle is defined with respect to z axis in x direction. So the 14 mrad crossing angle of ILD would be boost_angle = 0.007. In order to get from ILD coordinates to BeamCal coordinates it has to be boost_angle = -0.007.


 double gamma_factor = std::sqrt(1 + (tan(boost_angle)*tan(boost_angle)));
 double beta_gamma = std::tan(boost_angle);
 
 cout << "\n*************************************************" << endl;
 cout << "Boost back to Whizard frame\n\twhich is also the BCal coordinate system\n\t\tboost angle = " << boost_angle << "mrad\n\t\tbeta = " << beta_gamma << "\n\t\tgamma = " << gamma_factor << endl;
 cout << "*************************************************\n" << endl;
 
// float PX_ILD;
 float px_bcal;
 float pt_bcal;
 float PX_BCal_Emax;
 float RCENE_BCal_Emax;
 float PX_BCal_PTmax;
 float RCENE_BCal_PTmax; 
 float largest(0);
 float largestpt(0);

 
 // LOADING LCTUPLE FILE
 
 Int_t nrec;
 Float_t rcmox[259];
 Float_t rcmoy[259];
 Float_t rcmoz[259];
 Float_t rcmas[259];
 Int_t rctyp[259];
 Float_t rcene[259];
  if (prID==1){
 	cout << "\t-------- Neutrinos, LR --------\n" << endl;
 	f = new TFile("../root/lctuple_vv_LR.root","r");
 	g = new TFile("boosted_vv_LR.root", "RECREATE");
 }
  if (prID==2){
 	cout << "\t-------- Neutrinos, RL --------\n" << endl;
 	f = new TFile("../root/lctuple_vv_RL.root","r");
 	g = new TFile("boosted_vv_RL.root", "RECREATE");
 }
 if (prID==3){
 	cout << "\t-------- Bhabhas, LL --------\n" << endl;
 	f = new TFile("../root/lctuple_bhabhas_LL.root","r");
 	g = new TFile("boosted_bhabhas_LL.root", "RECREATE");
 }
 if (prID==4){
 	cout << "\t-------- Bhabhas, LR --------\n" << endl;
 	f = new TFile("../root/lctuple_bhabhas_LR.root","r");
 	g = new TFile("boosted_bhabhas_LR.root", "RECREATE");
 }
 if (prID==5){
 	cout << "\t-------- Bhabhas, RL --------\n" << endl;
 	f = new TFile("../root/lctuple_bhabhas_RL.root","r");
 	g = new TFile("boosted_bhabhas_RL.root", "RECREATE");
 }
 if (prID==6){
 	cout << "\t-------- Bhabhas, RR --------\n" << endl;
 	f = new TFile("../root/lctuple_bhabhas_RR.root","r");
 	g = new TFile("boosted_bhabhas_RR.root", "RECREATE");
 }

  if (prID==11){
 	cout << "\t-------- TEST nung, RL --------\n" << endl;
 	f = new TFile("../root/dbd_500GeV.nung.eR.pL_1.root","r");
 	g = new TFile("boosted_vv_RL.root", "RECREATE");
 }
 
  if (prID==12){
 	cout << "\t-------- TEST nung, LR --------\n" << endl;
 	f = new TFile("../root/dbd_500GeV.nung.eL.pR_1.root","r");
 	g = new TFile("boosted_vv_LR.root", "RECREATE");
 }
 if (prID==13){
 	cout << "\t-------- TEST Bhabhas, LL --------\n" << endl;
 	f = new TFile("../root/dbd_500GeV.bhabhang.eL.pL_1.root","r");
 	g = new TFile("boosted_bhabhas_LL.root", "RECREATE");
 }
 if (prID==14){
 	cout << "\t-------- TEST Bhabhas, LR --------\n" << endl;
 	f = new TFile("../root/dbd_500GeV.bhabhang.eL.pR_1.root","r");
 	g = new TFile("boosted_bhabhas_LR.root", "RECREATE");
 }
 if (prID==15){
 	cout << "\t-------- TEST Bhabhas, RL --------\n" << endl;
 	f = new TFile("../root/dbd_500GeV.bhabhang.eR.pL_1.root","r");
 	g = new TFile("boosted_bhabhas_RL.root", "RECREATE");
 }
 if (prID==16){
 	cout << "\t-------- TEST Bhabhas, RR --------\n" << endl;
 	f = new TFile("../root/dbd_500GeV.bhabhang.eR.pR_1.root","r");
 	g = new TFile("boosted_bhabhas_RR.root", "RECREATE");
 }
 
 TTree* MyLCTuple = (TTree*)f->Get("MyLCTuple");
 MyLCTuple->SetBranchAddress("rcmox",rcmox);
 MyLCTuple->SetBranchAddress("rcmoy",rcmoy);
 MyLCTuple->SetBranchAddress("rcmoz",rcmoz);
 MyLCTuple->SetBranchAddress("rcmas",rcmas);
 MyLCTuple->SetBranchAddress("nrec",&nrec);
 MyLCTuple->SetBranchAddress("rctyp",&rctyp);
 MyLCTuple->SetBranchAddress("rcene",&rcene);
 
 int n_entries = MyLCTuple->GetEntries();
 cout << "Number of events in lctuple file: " << n_entries << endl;

 // CREATING OUTPUT FILE
 float RCMOX_BCal_photon_Emax;
 float RCENE_BCal_photon_Emax;
 float RCMOX_BCal_photon_PTmax;
 float RCENE_BCal_photon_PTmax;
 int indexE;
 int indexPT;
  
 
 TTree* boost_tree = new TTree("BCal_frame","BCal_frame");
 TBranch* RC_mox = boost_tree->Branch("RCMOX_BCal_photon_Emax",&RCMOX_BCal_photon_Emax,"RCMOX_BCal_photon_Emax/F");
 TBranch* RC_E = boost_tree->Branch("RCENE_BCal_photon_Emax",&RCENE_BCal_photon_Emax,"RCENE_BCal_photon_Emax/F");
  TBranch* RC_mox_pt = boost_tree->Branch("RCMOX_BCal_photon_PTmax",&RCMOX_BCal_photon_PTmax,"RCMOX_BCal_photon_PTmax/F");
 TBranch* RC_E_pt = boost_tree->Branch("RCENE_BCal_photon_PTmax",&RCENE_BCal_photon_PTmax,"RCENE_BCal_photon_PTmax/F");
 TBranch* RC_ind_pt = boost_tree->Branch("indexPT",&indexPT,"indexPT/I");
 TBranch* RC_ind_E = boost_tree->Branch("indexE",&indexE,"indexE/I");

/*
 */
 cout << "\nCopying LCTuple tree ... takes some time" << endl;
 TTree *newtree = MyLCTuple->CopyTree("");
 // LOOPING OVER THE EVENTS
 // BOOSTING PX BACK TO WHERE IT WAS GENERATED
 
 for (int i(0); i < n_entries; i++){ // n_entries
 	//cout << "number of events: " << n_entries << endl;
 	indexE = -1;
 	if (i%500000 == 0){ printf("event %i\n",i);fflush(stdout);}
 	MyLCTuple->GetEntry(i);
 	for (int n(0); n < nrec; n++){
 		if (rctyp[n]==22){
 			px_bcal = beta_gamma * std::sqrt( rcmox[n]*rcmox[n] + rcmoy[n]*rcmoy[n] + rcmoz[n]*rcmoz[n] ) + gamma_factor * rcmox[n];
 			//pt_bcal=sqrt(px_bcal**2+rcmoy[n]**2);
 			pt_bcal=sqrt(TMath::Power(px_bcal,2)+TMath::Power(rcmoy[n],2));
 			if (rcene[n]>largest){
     		largest=rcene[n];
		     indexE=n;
     		}
     		if (pt_bcal>largestpt){
     		     largestpt=pt_bcal;
     		     indexPT=n;
     		}
  		} // if photon
  	}// recos
 	largest=0;
 	largestpt=0;
 	
 			
if (indexE>0) {
 	PX_BCal_Emax = beta_gamma * std::sqrt( rcmox[indexE]*rcmox[indexE] + rcmoy[indexE]*rcmoy[indexE] + rcmoz[indexE]*rcmoz[indexE] ) + gamma_factor * rcmox[indexE];
 	RCENE_BCal_Emax = std::sqrt( rcmox[indexE]*rcmox[indexE] + rcmoy[indexE]*rcmoy[indexE] + rcmoz[indexE]*rcmoz[indexE]);
 	PX_BCal_PTmax = beta_gamma * std::sqrt( rcmox[indexPT]*rcmox[indexPT] + rcmoy[indexPT]*rcmoy[indexPT] + rcmoz[indexPT]*rcmoz[indexPT] ) + gamma_factor * rcmox[indexPT];
 	RCENE_BCal_PTmax = std::sqrt( rcmox[indexPT]*rcmox[indexPT] + rcmoy[indexPT]*rcmoy[indexPT] + rcmoz[indexPT]*rcmoz[indexPT]); 	
 	RCMOX_BCal_photon_Emax = PX_BCal_Emax;
 	RCENE_BCal_photon_Emax = RCENE_BCal_Emax;
 	RCMOX_BCal_photon_PTmax = PX_BCal_PTmax;
 	RCENE_BCal_photon_PTmax = RCENE_BCal_PTmax;
 	boost_tree->Fill();
}

 	
 } // events
 g->Write();
 f->Close();
 g->Close();
 delete f;
 delete g;

 return;
}
