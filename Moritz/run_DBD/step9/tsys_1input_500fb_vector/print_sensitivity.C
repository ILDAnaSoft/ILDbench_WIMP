#include <TTree.h>
#include <iostream>



void print_sensitivity(double MASS, double Pe, double Pp){

	float wimp_mass = MASS;
	float electron_pol = Pe;
	float positron_pol = Pp;
	char filename[256];	

	sprintf(filename,"Sensitivity_Pe%.1f_Pp%.1f_Lumi500_Mass%.0f_2Sigma_lumi_pole_polp_beamspec_select_withsys_corel.root",electron_pol,positron_pol,wimp_mass);
	
	TFile *f = new TFile(filename);
//	f.ls();
	TH1F *h1 = new TH1F("h1","Sensitivity_Vector", 100, 0 ,4);
	h1 = (TH1F*)f->Get("Sensitivity Vector");
//	h1->Draw();
	float lambda = h1->GetBinContent(wimp_mass);
	cout << "Lambda for Pe=" << electron_pol << ", Pp=" << positron_pol << " and the WIMP mass " << wimp_mass << " is " << lambda << endl;
	
	return;
}
