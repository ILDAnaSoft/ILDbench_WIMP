#include <TTree.h>
#include <iostream>



//void print_sensitivity(double MASS, double Pe, double Pp){
void print_sensitivity(double MASS){

	//float wimp_mass = MASS;
	double wimp_mass = MASS;
	char filename[256];	

	//sprintf(filename,"outputs/Sensitivity_Pe%.1f_Pp%.1f_Lumi500_Mass%.0f_2Sigma_lumi_pole_polp_beamspec_select_withsys_corel.root",electron_pol,positron_pol,wimp_mass);
    //sprintf(filename, "outputs_test/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass%.0f_2Sigma.root",wimp_mass); 
    sprintf(filename, "outputs/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass%.3g_2Sigma.root",wimp_mass); 
	
	TFile *f = new TFile(filename);
//	f.ls();
	//TH1F *h1 = new TH1F("h1","Sensitivity_Vector", 100, 0 ,4);
	//h1 = (TH1F*)f->Get("Sensitivity Vector");
	TH1F* h1 = (TH1F*)f->Get("Sensitivity Vector");
    //int bin = h1->FindBin(1e-06);
    //cerr << "h1->GetBinContent(bin) = " << h1->GetBinContent(bin) << endl;
//	h1->Draw();
	//float lambda = h1->GetBinContent(wimp_mass);
	cerr << "wimp_mass = " << wimp_mass << endl;
    cerr << "h1->GetNbinX() = " << h1->GetNbinsX() << endl;
    int bin = h1->FindBin(wimp_mass);
    cerr << "bin = " << bin << endl;
    cerr << "h1->GetBinCenter(bin) = " << h1->GetBinCenter(bin) << endl;
	float lambda = h1->GetBinContent(int(h1->FindBin(wimp_mass)));
	//cout << "Lambda for Pe=" << electron_pol << ", Pp=" << positron_pol << " and the WIMP mass " << wimp_mass << " is " << lambda << endl;
	cout << "Lambda for the WIMP mass " << wimp_mass << " is " << lambda << endl;
	
	return;
}
