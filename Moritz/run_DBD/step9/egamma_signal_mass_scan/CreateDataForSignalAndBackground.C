  #include "WIMP_functions.C"

#include <fstream>
#include "TFile.h"
#include "TProfile.h"
#define PI 3.14159265


//extern "C" void differentialxsection_(double* s, double* X_photon, double* Theta_photon, double* P_e, double* P_p, double* sigma_diff);



void CreateDataForSignalAndBackground(){
  //void CreateDataForSignalAndBackground(double l, double pe, double pp){

  // ####### PARAMETERS
  
  //double lumi = l;
  //double Pe = pe;
  //double Pp = pp;
  
  double lumi = 500.0;
  double Pe = 0.0;
  double Pp = 0.0;
  
  double cos_cut_7 = 0.992546;
  double ptmin_small = 1.92; // phi-dependent: either 1.92 or 5.65
  double e_thresh_small = 15.75; // 15.75 for ptmin=1.92 and 46.36 for ptmin=5.65
  double ptmin_large = 5.65; // phi-dependent: either 1.92 or 5.65
  double e_thresh_large = 46.36; // 15.75 for ptmin=1.92 and 46.36 for ptmin=5.65
  double coscut;
  
  double ptmin, e_thresh;
  
  double cos_cut = 0;
      
  //_lambda=(double)100;// p-wave = 15, s-wave = 32

 // TFile* f;
  char filename[256];
  char name[256];
  char obj_title[256];
  
  int n_bg0;


  // #########################################################################
  // #########################################################################
  // ##################   SIGNAL DATA TEMPLATES ############################
  // #########################################################################
  


  FILE* wimpfile = fopen("./WIMP.steer","r");
  LoadWIMPParameters(wimpfile);
  _BR = 1.0;
  _BR_eff = 1.0;
  
  int _sigma_eRpL = 0.0;
  int _sigma_eRpR = 0.0;
  int _sigma_eLpL = 0.0;
  int _sigma_eLpR = 0.0;
  
   int k= 0; // Vector	    
//  int k= 1; // Scalar,s-channel
//  int k= 2; // Axial-vector 
  
  //##################### OUTPUTFILES #####################


  char _operator[20];
 
  TFile* f_sig[11];
  TProfile* h_weight[10];
  TH1D* h_array[11][250][10][1]; // pol, M , lambda ,k-operator
 
      for (int m(0); m < 1 ; m++){
	if (m == 0) {
  	  Pe = 0.;
  	  Pp = 0.;
  	}
    
    sprintf(filename,"./1D_Data_Signal_Pe%.1f_Pp%.1f_Lumi%.0f.root",Pe,Pp,lumi);
    f_sig[m] = new TFile(filename,"RECREATE");
   
    h_weight[m] = new TProfile("weights","weights;cos #Theta;w",100,-1.0,1.0);

    for (int i(0); i < 250; i++){
      for (int l(0); l< 1; l++){//l = Lambda

	
	    if (k == 0){
	      sprintf(_operator,"Vector");
	    }
	    if (k == 1){
	      sprintf(_operator,"Scalar,s-channel");
	    }
	    if (k == 2){
		sprintf(_operator,"Axial-vector");
	    }	   
	    if (k == 3){
		sprintf(_operator,"Scalar,t-channel");
	    }
	    if(i==0)
	    cout<<_operator<<endl;	    
	    
	    _mass = (double)i + 1.0;
	    _spin= 1.0/2.0;
	    _lambda=(double)(l+1)*1580;	    

	    sprintf(obj_title,"M%.0f_S%.1f_%s_Lambda%.0f",_mass,_spin,_operator,_lambda);
	    h_array[m][i][l][0] = new TH1D(obj_title,obj_title,300,0.0,300.0);
	    h_array[m][i][l][0]->Sumw2();
	  
      }
    }
  }


  double weight;
  double xsec_bg;
  double xsec_sig;


  // ###################################################################
  // ################ CREATE SIGNAL TEMPLATES ##########################
  // ################### METHOD 2, Weights with dsig/de #######


  // ########### OPEN BACKGROUND CROSS SECTION FILE
  sprintf(filename,"./Xsec_whizard_pt192.root");
  TFile* f_bg_exp192 = new TFile(filename,"OPEN");
  TH2D* h_bg_2d_192 = (TH2D*)f_bg_exp192->Get("vv_Xsec_whizard"); 

  sprintf(filename,"./Xsec_whizard_pt565.root");
  TFile* f_bg_exp565 = new TFile(filename,"OPEN");
  TH2D* h_bg_2d_565 = (TH2D*)f_bg_exp565->Get("vv_Xsec_whizard");  

  sprintf(filename,"./Xsec_whizard_largerThetaRange.root");
  TFile* f_bg_largerTH = new TFile(filename,"OPEN");
  TH2D* h_bg_largerTH = (TH2D*)f_bg_largerTH->Get("vv_Xsec_whizard"); 
  
  // ######## PROJECTION ON ENERGY 
    
  double w = h_bg_2d_192->GetYaxis()->GetBinWidth(1);
  int binx = h_bg_2d_192->GetXaxis()->GetNbins();

  int biny = h_bg_2d_192->GetYaxis()->GetNbins();
  
  cout << "NUMBER OF BINS: X " << binx << " Y " << biny << endl;

  _BR_eff = 1.0;
  TH2D* h_WIMPdsigmadE[250][2]; // dsigma/dE in fb
  TH2D* h_WIMPdsigmadE_largerTH[250];
  for (int ph(0); ph < 2; ph++){   // two phi sections
  	if (ph==0){
  		ptmin=ptmin_small;
  		e_thresh=e_thresh_small;
  	}
  	if (ph==1){
  		ptmin=ptmin_large;
  		e_thresh=e_thresh_large;
  	}
  cout << "\n\n\t\tpreparing sig-Xsec-histograms" << endl;
  for (int i(0); i < 250; i++){
	if (i%10 == 0){ printf("\t\t... at mass %i\n",i);fflush(stdout);}
      int s(0);

      	for (int l(0);l<1;l++){
	
  	_mass = (double)i + 1.0;
  	_spin = (double)1/2.0;
	_lambda=(double)(l+1)*1580;
	
/*	cout << "cos_cut_7 = " << cos_cut_7 << endl;
	cout << "k = " << k << endl;
	cout << "ptmin = " << ptmin << endl;
	cout << "e_thresh = " << e_thresh<< endl;*/
	

  	h_WIMPdsigmadE[i][ph]= new TH2D(Form("DsigmadE_WIMP%i%i",i,ph),"DsigmadE_WIMP;E[GeV];d#sigma /dE [fb]",250,0.5,250.5,502,0,502);
  	DsigmadE_WIMP_new(h_WIMPdsigmadE[i][ph],500.0,cos_cut_7,k,ptmin,e_thresh);
  	
 	
  	if (ph==0){
 		h_WIMPdsigmadE_largerTH[i]= new TH2D(Form("DsigmadE_WIMP_largerTH%i%i",i,ph),"DsigmadE_WIMP_largerTH;E[GeV];d#sigma /dE [fb]",250,0.5,250.5,502,0,502);
  		DsigmadE_WIMP_new2(h_WIMPdsigmadE_largerTH[i],500.0,0.999992,k,0,0);
  	}
	}

  }
  }
   
  cout << "DONE FILLING WIMP X-SEC HISTOGRAM" << endl;
   
  CreatePolarisationWeights(0.0,0.0);
   
  
  //----------------------------------------------------------------------------  
  
  ifstream txtfile2("./Selected_Photons_Neutrinos.txt");
  
  while (true){
    txtfile2.getline(name,256,'\n');
    if (txtfile2.eof()) break;
     
    printf("%s\n",name);
    f = new TFile(name,"OPEN");
    if (f->IsZombie()) continue;
    
    int n_outside(0); 
    //int n_outside_sig(0); 
    // ********** GET BACKGROUND DATA TREES
     
    TTree* seltree = (TTree*)f->Get("selected_photons");
    TTree* globaltree = (TTree*)f->Get("global");
     // TTree* xsectree = (TTree*)f->Get("XSecTree");
    LoadSelPhotonTree(seltree);
    // LoadXSecTree(xsectree);
    LoadGlobalTree(globaltree);
    globaltree->GetEntry(0);

//    double factor = (double)NumberOfEventsInFile/NumberOfEventsInRun;  
    // #########  LOOP OVER ENTRIES
    int nentries = seltree->GetEntries();
//       nentries = (int)1e0;      
      float MCLumi_2 = MCLumi/2.;
      
  double weight = GetEventWeight(lumi, MCLumi_2, electron_polarisation, positron_polarisation);
  
    for (int l(0); l < nentries; l+=2){ //nentries
      if (l%100000 == 0){ printf("event %i\n",l);fflush(stdout);}
//   	cout << "event\t" << l << endl;
//      tree->GetEntry(l);
      seltree->GetEntry(l);
 //     cout << '\n' <<  rcene[0] << " " << rcphi[0] << " " << mcene_star[0] << " " << sqrts_star[0] << endl;
      
      
            
      if (TMath::Abs(rcphi[0])>35){
      	ph=0;
      	ptmin=ptmin_small;
  		e_thresh=e_thresh_small;
      }
      if (TMath::Abs(rcphi[0])<=35){
      	ph=1;
      	ptmin=ptmin_large;
  		e_thresh=e_thresh_large;
      }
      
      if (mcene_star[0] <= ptmin){
    		coscut=.1;
      }
      if (mcene_star[0] > e_thresh && mcene_star[0] > ptmin){
    		coscut=cos_cut_7;
      }
      if (mcene_star[0] < e_thresh && mcene_star[0] > ptmin){
    		coscut=sqrt(mcene_star[0]**2-ptmin**2)/mcene_star[0];
      }
      
      if (TMath::Abs(cos(mctheta_star[0]*PI/180.))>coscut){
      	n_outside++;
      	
      	int _bin_x = h_bg_largerTH->GetXaxis()->FindBin(mcene_star[0]); // dsigma/dE in fb
      	int _bin_y = h_bg_largerTH->GetYaxis()->FindBin(sqrts_star[0]);
      	xsec_bg = h_bg_largerTH->GetBinContent(_bin_x,_bin_y);
 
       	int _bin = h_WIMPdsigmadE_largerTH[0]->GetXaxis()->FindBin(mcene_star[0]);
      	int _binY = h_WIMPdsigmadE_largerTH[0]->GetYaxis()->FindBin(sqrts_star[0]);
      }
      else{ 
      	if (ph==0){
      		int _bin_x = h_bg_2d_192->GetXaxis()->FindBin(mcene_star[0]); // dsigma/dE in fb
      		int _bin_y = h_bg_2d_192->GetYaxis()->FindBin(sqrts_star[0]);
      		xsec_bg = h_bg_2d_192->GetBinContent(_bin_x,_bin_y);
      	}
      	if (ph==1){
      		int _bin_x = h_bg_2d_565->GetXaxis()->FindBin(mcene_star[0]); // dsigma/dE in fb
      		int _bin_y = h_bg_2d_565->GetYaxis()->FindBin(sqrts_star[0]);
      		xsec_bg = h_bg_2d_565->GetBinContent(_bin_x,_bin_y);
      	}
      	int _bin = h_WIMPdsigmadE[0][0]->GetXaxis()->FindBin(mcene_star[0]);
      	int _binY = h_WIMPdsigmadE[0][0]->GetYaxis()->FindBin(sqrts_star[0]);
      }
     //xsec_bg = .1;
    //  cout << "xsec_bg = " << xsec_bg << endl;
//      cout << _bin << "\t" << _binY << endl;
  
      for (int m(0); m < 1 ; m++){
	if (m == 0) {
  	  Pe = 0.;
  	  Pp = 0.;
  	}
  	

  	    
  	for (int i(0); i < 250; i++){
  	  for (int b(0);  b< 1; b++){// b == l ( for _lambda)
  	         int s=0;
  	   if (TMath::Abs(cos(mctheta_star[0]*PI/180.))>coscut){      
			 xsec_sig = h_WIMPdsigmadE_largerTH[i]->GetBinContent(_bin,_binY);
			 //n_outside_sig++;
//			 cout << "OUTSIDE!: sig " << xsec_sig << " bg: " << xsec_bg << endl;
//			 cout << "inside: " << h_WIMPdsigmadE[i][ph]->GetBinContent(_bin,_binY) << endl;
	   }
	   else {
	   		xsec_sig = h_WIMPdsigmadE[i][ph]->GetBinContent(_bin,_binY);
	   		//cout << "inside: sig " << xsec_sig << " bg: " << xsec_bg << endl;
	   }
 	 //    cout << "xsec_sig = "<< xsec_sig << endl;

  		if (k == 0){
		//Vector operator
		  _sigma_eRpL = 1.0;
  		  _sigma_eRpR = 0.0;
  		  _sigma_eLpL = 0.0;
  		  _sigma_eLpR = 1.0;
		  		
		}else
  		if (k == 1||k == 2){
		//Axial-Vector operator And Scalar s-channel
		  _sigma_eRpL = 0.0;
  		  _sigma_eRpR = 1.0;
  		  _sigma_eLpL = 1.0;
  		  _sigma_eLpR = 0.0;
  		}
  		
		      
		  		
		_BR_eff = _BR * Sigma_PolFactor(_sigma_eRpL, _sigma_eRpR, _sigma_eLpL,_sigma_eLpR,Pe,Pp); 
		
//	cout << xsec_sig << endl;
//	cout << xsec_bg << endl;
  		if (xsec_bg > 0.0){
		  double weight2 = weight * _BR_eff * xsec_sig/xsec_bg;
		  //double weight2 = weight * xsec_sig/xsec_bg;
	//	   cout << "w  " << weight2 << endl;
		  h_weight[m]->Fill(TMath::Cos(Theta_prime),weight2);
		  h_array[m][i][b][0]->Fill(rcene[0], weight2);
		}
  	      
  	    }
	 }	     		      
      }
    }
    delete f; 
    cout << "NUMBER OF EVENTS OUTSIDE OF THETA RANGE: " << n_outside << endl;
    //cout << "NUMBER OF EVENTS OUTSIDE OF THETA RANGE (sig): " << n_outside_sig << endl;
    cout << "these events are lost or get wrong weight: " << n_bg0 << endl;
  }

  cout << "reweighting done\n";
  // // ###################################################################
  // // ###############            END           ##########################
  // // ###################################################################
 

  for (int m(0); m < 1; m++){ 

    f_sig[m]->cd();
    h_weight[m]->Write();
   
    for (int i(0); i < 250; i++){
      for (int l(0); l < 1; l++){ // Lambda
	
	  k=0;
	    h_array[m][i][l][k]->Write();
	  	
      }
    }
     cout << "writing output\n";
    f_sig[m]->Close();
  }
 
  return;
}
