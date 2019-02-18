
#include "WIMP_functions.C"

#include <fstream>
#include "TFile.h"
#include "TProfile.h"




void CreateDataBackground(){


  // ####### PARAMETERS

  
  double lumi = 500.0;
  //double Pe = 0.0;
  //double Pp = 0.0;
  double Pe = 0.8;
  double Pp = -0.3;

  TFile* f;
  char filename[256];
  char name[256];
  char obj_title[256];

  double fullBG;

  // #########################################################################
  // #########################################################################
  // ##################   BACKGROUND DATA TEMPLATES ######################
  // #########################################################################
  
  //##################### OUTPUTFILES #####################
  TFile* f_data_bg[11];
  TH1D* h_data_bg_E[11];
  
  for (int m(0); m < 1; m++){
	if (m == 0) {
  	  Pe = 0.;
  	  Pp = 0.;
  	}
   
    sprintf(filename,"Data_Background_Pe%.1f_Pp%.1f_Lumi%.0f.root",Pe,Pp,lumi);
    f_data_bg[m] = new TFile(filename,"RECREATE");
      
    sprintf(obj_title,"Background_Pe%.1f_Pp%.1f_Lumi%.0f",Pe,Pp,lumi);
    h_data_bg_E[m] = new TH1D(obj_title,"Background;E [GeV]; Entries",300,0.0,300.0);
    h_data_bg_E[m]->Sumw2();
  }
  
 
  // ################ CREATE BACKGROUND TEMPLATES ############
    
  ifstream txtfile("Selected_Photons.txt");
   
    
  while (!txtfile.eof()){
    txtfile.getline(name,256,'\n');
    printf("%s\n",name);
    f = new TFile(name,"OPEN");
    if (f->IsZombie()) continue;
      
    // ********** GET BACKGROUND DATA TREES
    TTree* seltree = (TTree*)f->Get("selected_photons");
    TTree* globaltree = (TTree*)f->Get("global");
    LoadSelPhotonTree(seltree);
    LoadGlobalTree(globaltree);
    
    globaltree->GetEntry(0);
    
    cout << "X section: " << crosss << endl;

    int stepsize;
    int start;
#if 1 // RY added
    float MCLumi_2;
#endif
    
    if (crosss>100000){
    cout << "\nThis is a Bhabhas file\n\n" << endl;
    stepsize=1;
    start=0;
//    cout << MCLumi << endl;
#if 0
    float MCLumi_2=MCLumi;
#else
    MCLumi_2=MCLumi;
#endif
//    cout << MCLumi_2 << endl;
    }
    else {
    cout << "\nThis is a Neutrinos file\n\n" << endl;
    stepsize=2;
    start=1;
//    cout << MCLumi << endl;
    MCLumi_2=MCLumi/2;
//    cout << MCLumi_2 << endl;
    }
    
    // ********** LOOP OVER ENTRIES
     int n_entries = seltree->GetEntries();

    for (int j(start); j < n_entries; j+=stepsize){
      if (j%100000 == 1) printf("event %i\n",j);
      seltree->GetEntry(j);

  for (int m(0); m < 1; m++){
	if (m == 0) {
  	  Pe = 0.;
  	  Pp = 0.;
  	} 
  	
   	CreatePolarisationWeights(Pe,Pp);
   	double weight = GetEventWeight(lumi, MCLumi_2, electron_polarisation, positron_polarisation);
   	fullBG+=weight;
   	h_data_bg_E[m]->Fill(RCENE[0],weight);
//	cout << "P(e-) = " << Pe << ", P(e+) = " << Pp << ", Event: " << j << ", weight: " << weight << endl;
//	cout<<"Weight = "<<weight<<"| Photon_energy = "<<SelPhoton_energy[0]<<"| Pe = "<<Pe <<"| Pp = "<<Pp<<endl;
      }
    }
    delete f;
  }
  
  for ( int m(0); m < 1; m++){
    f_data_bg[m]->cd();
    h_data_bg_E[m]->Write();
    f_data_bg[m]->Close();
  }
  cout << "fullBG = " << fullBG << endl;
  return;  
}   
 

