#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TRandom3.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TLimit.h>
#include <TConfidenceLevel.h>
#include <TSysLimitChannel.h>
#include <TSysLimit.h>
#include <TSysLimitResult.h>
#include <TSysLimitScan.h>
#include "TTree.h"

using namespace std;

#define Systematics

int main(int argc, char const *argv[]) {





//    TH1::SetDefaultSumw2(kTRUE);

//#########################################################
// Input data

  Double_t lumi = 500.0; // set to desired lumi
  Double_t input_lumi = 500.0; // this probably never changes
  Double_t lumi_weight = lumi/input_lumi;
  Double_t Pe = 100.; // input from command line
  Double_t Pp = 100.; // input from command line
  char filename[256];
  char _operator[20];
  Double_t _mass=1000; // input from command line
  Double_t _spin=0.5;
  Double_t _lambda =1580;
  Double_t ExpCL = 0.9545; //0.9
  
   
    if(argc>1) {
	cout <<" Mass = "<< argv[1] << endl;
	cout <<" Pe = "<< argv[2] << endl;
	cout <<" Pp = "<< argv[3] << endl;	
	    _mass=atof(argv[1]);
	     Pe=atof(argv[2]);
	     Pp=atof(argv[3]);
    } else { exit(1); } 
    

    cout<<" Pe = "<<Pe<<"| Pp = "<<Pp<<endl;
    
    sprintf(filename,"Sensitivity_Pe%.1f_Pp%.1f_Lumi%.0f_Mass%.0f_2Sigma_lumi_pole_polp_beamspec_select_withsys_corel.root",Pe,Pp,lumi,_mass);
//    sprintf(filename,"Results/Sensitivity_Pe%.1f_Pp%.1f_Lumi%.0f_Mass%.0f_3Sigma_CLTSys_onebin_with_errors.root",Pe,Pp,lumi,_mass);
//    sprintf(filename,"Results/Sensitivity_Pe%.1f_Pp%.1f_Lumi%.0f_Mass%.0f_90CLTSys_lumi_pole_polp_beamspec_select_withsys_corel.root",Pe,Pp,lumi,_mass);    
    
    cout<<filename<<endl;
    TFile * f= new TFile(filename,"recreate");
    TTree * t1=new TTree("Parameters","All parameters used in calculation");
    TList* list = new TList();
    TH1D* Sensitivity;
    
	 t1->Branch("Pe", &Pe, "new_v/D");
	 t1->Branch("Pp", &Pp, "new_v/D");	 
	 t1->Branch("Lumi", &lumi, "new_v/D");
	 t1->Branch("ExpCL", &ExpCL, "new_v/D"); 
	 
	 bool OPvector=false;
	 bool OPscalarS=false;
	 bool OPaxialv=false;
	 
for (int l=0;l<1;l++){
	
	if (l == 0){
    		sprintf(_operator,"Vector");  
    		OPvector=true;
     } else
	if (l == 1){
	    	sprintf(_operator,"Scalar,s-channel");
	    	OPscalarS=true;
   	    }  else
	    if (l == 2){ 
	    	sprintf(_operator,"Axial-vector");  
	    	OPaxialv=true;
    } else {cout<<"###########################FALD ############################### "<<endl;}

    sprintf(filename,"Sensitivity %s",_operator);
     Sensitivity = new TH1D(filename,filename,250,1,250);
    cout<<_operator<<endl;


 
//Create Beam spectra effect
 TH1D* beamspec_bg_up = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_bg_down = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_sig_up = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_sig_down = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);

    
    cout<<" Mass = "<<_mass<<endl;
   
    sprintf(filename,"../egamma_signal_single_mass/1D_Data_Signal_Pe%.1f_Pp%.1f_Lumi%.0f.root",Pe,Pp,input_lumi);
    TFile * infile_sig = new TFile(filename,"READ");
    infile_sig->cd();
    
    
    sprintf(filename,"M%.0f_S%.1f_%s_Lambda%.0f",_mass,_spin,_operator,_lambda); 
    TH1D* sh=(TH1D*)infile_sig->Get(filename);
    
       
    sprintf(filename,"../egamma_background/Data_Background_Pe%.1f_Pp%.1f_Lumi%.0f.root",Pe,Pp,input_lumi);
//    sprintf(filename,"/afs/desy.de/group/flc/pool/achaus/WIMPs/data/Templates_Andrii/Data_Background_Pe%.1f_Pp%.1f_Lumi%.0f.root",Pe,Pp,lumi);
    TFile * infile_bg = new TFile(filename,"READ");
    infile_bg->cd();

    sprintf(filename,"Background_Pe%.1f_Pp%.1f_Lumi%.0f",Pe,Pp,input_lumi);
    TH1D* bh=(TH1D*)infile_bg->Get(filename);
 


//    cout<<" Integral after 1/lambda^4 :"<<sh->Integral()<<endl;
//    cout<<" Integral Background       :"<<bh->Integral()<<endl;
    
//       sh->Rebin(300);
//       bh->Rebin(300); 
  cout<<" Nbins        :"<<bh->GetNbinsX()<<endl;

#ifdef Systematics
   cout<<" Calculation with systematic errors  :"<<endl;
    // consider NSYS systematic sources
    // create histograms with relative errors
    Int_t NSYS=6;
    TString sys_names[NSYS];
    sys_names[0]="luminosity";
    sys_names[1]="polp";
    sys_names[2]="pole";
    sys_names[3]="beam";
    sys_names[4]="select";
    sys_names[5]="whizard";   
    TH1D *histBgrSys[NSYS][2];
    TH1D *histSignalSys[NSYS][2];
    for(Int_t s=0;s<NSYS;s++) {
       	for(Int_t ds=0;ds<2;ds++) {
	    TString name("Sys_error_");
	    name += sys_names[s];
	    
	    TString name1,name2;
	    
            name2 =name+"_background";
	    name2 +=ds;
	    cout<<name2<<endl;
	    histBgrSys[s][ds]=new TH1D(name2,"Background errors",300,0.0,300.0);

	    name1 =name+"_signal";
	    name1 +=ds;
	    histSignalSys[s][ds]=new TH1D(name1,"Signal errors",300,0.0,300.0);
            cout<<name1<<endl;
    	}
    }
#endif     
 	bh->Scale(lumi_weight);
 	sh->Scale(lumi_weight);
	sh->Scale(pow(_lambda,4));

#ifdef Systematics
// Fill errors histograms
cout<<"BINS = "<<histBgrSys[0][0]->GetNbinsX()<<endl;
  

  
  //FILL  LUMINOSITY Systematic errors
    Int_t s=0;

	for(Int_t i=1;i<=histBgrSys[s][0]->GetNbinsX();i++){
	Double_t bg_sys=0.0026,sig_sys=0.0026;
	if(i==1){
	 t1->Branch("bg_sys_lumi", &bg_sys);
	 t1->Branch("sig_sys_lumi", &sig_sys);}	
	histBgrSys[s][0]->Fill(i,bg_sys);
	histSignalSys[s][0]->Fill(i,sig_sys);
	}

  //FILL WHIZARD SYSTEMATIC ERRORS
	s=5;
	
	for (Int_t i=1; i<=histBgrSys[s][0]->GetNbinsX(); i++){
		Double_t bg_sys=0.0013, sig_sys=0.0013;
		if(i==1){
	 	t1->Branch("bg_sys_lumi", &bg_sys);
	 	t1->Branch("sig_sys_lumi", &sig_sys);}	
	 	histBgrSys[s][0]->Fill(i,bg_sys);
	 	histSignalSys[s][0]->Fill(i,sig_sys);
	}   
  


  //FILL  Pp Systematic errors 
        s=1; 
	
	for(Int_t i=1;i<=histBgrSys[s][0]->GetNbinsX();i++){
	Double_t error_size= 0.0025;
	if (Pp==0.3){
		error_size=0.0008;
	}
	if (Pp==-0.3){
		error_size=0.0004;
	}
	if(i==1){cout<<"POL P eroor ="<<error_size<<endl;
		 t1->Branch("Pp_Systematic_error", &error_size);}
	Double_t signal_bin = sh->GetBinContent(i);
	Double_t bg_bin = bh->GetBinContent(i);	
//	cout<<"signal_bin = "<<signal_bin<<"| bg_bin = "<<bg_bin<<" ;"<<endl;
		 
	Double_t 	 bg_sysup=bg_bin*(1.0+error_size);
	Double_t 	 bg_sysdown=bg_bin*(1.0-error_size);
	Double_t	 sig_sysup=signal_bin*(1.0+error_size);
	Double_t	 sig_sysdown=signal_bin*(1.0-error_size);
	
	histBgrSys[s][0]->Fill(i,bg_sysup);
	histBgrSys[s][1]->Fill(i,bg_sysdown);	
	histSignalSys[s][0]->Fill(i,sig_sysup);
	histSignalSys[s][1]->Fill(i,sig_sysdown);	
	
	}
  
 
  //FILL  Pe Systematic errors 
        s=2;
	for(Int_t i=1;i<=histBgrSys[s][0]->GetNbinsX();i++){
	Double_t error_size= 0.0025;
	if (Pe==0.8){
		error_size=0.0002;
	}
	if (Pe==-0.8){
		error_size=0.0008;
	}
	if(i==1){cout<<"POL E eroor ="<<error_size<<endl;
		 t1->Branch("Pe_Systematic_error", &error_size);}	
	Double_t signal_bin = sh->GetBinContent(i);
	Double_t bg_bin = bh->GetBinContent(i);	
//	cout<<"signal_bin = "<<signal_bin<<"| bg_bin = "<<bg_bin<<" ;"<<endl;
		 
	Double_t 	 bg_sysup=bg_bin*(1.0+error_size);
	Double_t 	 bg_sysdown=bg_bin*(1.0-error_size);
	Double_t	 sig_sysup=signal_bin*(1.0+error_size);
	Double_t	 sig_sysdown=signal_bin*(1.0-error_size);
	
//        cout<<"sig_sys = "<<sig_sys<<"| bg_sys  = "<<bg_sys<<" ;"<<endl;

	histBgrSys[s][0]->Fill(i,bg_sysup);
	histBgrSys[s][1]->Fill(i,bg_sysdown);	
	histSignalSys[s][0]->Fill(i,sig_sysup);
	histSignalSys[s][1]->Fill(i,sig_sysdown);	
	
	}
 
 //##########################################################################
  //FILL  Beam spectra parameters   

Double_t error_size=0;
bool found_pol = false;

if (Pe==0&&Pp==0){

	found_pol = true;

	for(Int_t i=1;i<=220;i++){		 
if(i<=4)error_size=0.00297927;	else
if(i<=12)error_size=0.00287164;	else
if(i<=20)error_size=0.00366326;	else
if(i<=28)error_size=0.00362043;	else
if(i<=36)error_size=0.00304237;	else
if(i<=44)error_size=0.00252882;	else
if(i<=52)error_size=0.00282464;	else
if(i<=60)error_size=0.00276186;	else
if(i<=68)error_size=0.00387198;	else
if(i<=76)error_size=0.00513453;	else
if(i<=84)error_size=0.00636796;	else
if(i<=92)error_size=0.00671272;	else
if(i<=100)error_size=0.00649512;	else
if(i<=108)error_size=0.00691525;	else
if(i<=116)error_size=0.0067924;	else
if(i<=124)error_size=0.00672372;	else
if(i<=132)error_size=0.00644821;	else
if(i<=140)error_size=0.00621241;	else
if(i<=148)error_size=0.00646465;	else
if(i<=156)error_size=0.00647837;	else
if(i<=164)error_size=0.00693909;	else
if(i<=172)error_size=0.00781038;	else
if(i<=180)error_size=0.00909505;	else
if(i<=188)error_size=0.011391;	else
if(i<=196)error_size=0.0125632;	else
if(i<=204)error_size=0.0129041;	else
if(i<=212)error_size=0.0131019;	else
if(i<=220)error_size=0.0120902;	else{cout<<"Same size";}

		beamspec_bg_up->Fill(i,error_size);
	
	}

	for(Int_t i=1;i<=220;i++){		 

if(i<=4)error_size=-0.00318529;	else
if(i<=12)error_size=-0.00307022;	else
if(i<=20)error_size=-0.0039166;	else
if(i<=28)error_size=-0.00387081;	else
if(i<=36)error_size=-0.00325276;	else
if(i<=44)error_size=-0.00270368;	else
if(i<=52)error_size=-0.00301997;	else
if(i<=60)error_size=-0.00295285;	else
if(i<=68)error_size=-0.00413976;	else
if(i<=76)error_size=-0.00548965;	else
if(i<=84)error_size=-0.00680841;	else
if(i<=92)error_size=-0.00717701;	else
if(i<=100)error_size=-0.00694436;	else
if(i<=108)error_size=-0.00739356;	else
if(i<=116)error_size=-0.00726221;	else
if(i<=124)error_size=-0.00718877;	else
if(i<=132)error_size=-0.0068942;	else
if(i<=140)error_size=-0.00664209;	else
if(i<=148)error_size=-0.00691178;	else
if(i<=156)error_size=-0.00692645;	else
if(i<=164)error_size=-0.00741904;	else
if(i<=172)error_size=-0.00835061;	else
if(i<=180)error_size=-0.00972415;	else
if(i<=188)error_size=-0.0121789;	else
if(i<=196)error_size=-0.0134322;	else
if(i<=204)error_size=-0.0137967;	else
if(i<=212)error_size=-0.0140082;	else
if(i<=220)error_size=-0.0129265;	else {cout<<"Same size";}

		beamspec_bg_down->Fill(i,error_size);
	
	}

}


if (Pe==0.8&&Pp==-0.3){

	found_pol = true;

	for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=0.00513901;	else
if(i<=12)error_size=0.00564924;	else
if(i<=20)error_size=0.00907805;	else
if(i<=28)error_size=0.0107942;	else
if(i<=36)error_size=0.00741422;	else
if(i<=44)error_size=0.00558221;	else
if(i<=52)error_size=0.00717615;	else
if(i<=60)error_size=0.00739937;	else
if(i<=68)error_size=0.0127861;	else
if(i<=76)error_size=0.0199377;	else
if(i<=84)error_size=0.025701;	else
if(i<=92)error_size=0.026607;	else
if(i<=100)error_size=0.0245228;	else
if(i<=108)error_size=0.0258784;	else
if(i<=116)error_size=0.0248568;	else
if(i<=124)error_size=0.0249768;	else
if(i<=132)error_size=0.0221094;	else
if(i<=140)error_size=0.021107;	else
if(i<=148)error_size=0.0204976;	else
if(i<=156)error_size=0.0197112;	else
if(i<=164)error_size=0.0180937;	else
if(i<=172)error_size=0.0203634;	else
if(i<=180)error_size=0.0218546;	else
if(i<=188)error_size=0.022685;	else
if(i<=196)error_size=0.0230076;	else
if(i<=204)error_size=0.0217947;	else
if(i<=212)error_size=0.0200269;	else
if(i<=220)error_size=0.0167556;	else{cout<<"Same size";}

 beamspec_bg_up->Fill(i,error_size);

}

	for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=-0.00549443;	else
if(i<=12)error_size=-0.00603997;	else
if(i<=20)error_size=-0.00970597;	else
if(i<=28)error_size=-0.0115409;	else
if(i<=36)error_size=-0.00792705;	else
if(i<=44)error_size=-0.00596829;	else
if(i<=52)error_size=-0.0076725;	else
if(i<=60)error_size=-0.00791117;	else
if(i<=68)error_size=-0.0136706;	else
if(i<=76)error_size=-0.0213169;	else
if(i<=84)error_size=-0.0274788;	else
if(i<=92)error_size=-0.0284476;	else
if(i<=100)error_size=-0.0262192;	else
if(i<=108)error_size=-0.0276685;	else
if(i<=116)error_size=-0.0265763;	else
if(i<=124)error_size=-0.0267045;	else
if(i<=132)error_size=-0.0236388;	else
if(i<=140)error_size=-0.0225671;	else
if(i<=148)error_size=-0.0219155;	else
if(i<=156)error_size=-0.0210747;	else
if(i<=164)error_size=-0.0193453;	else
if(i<=172)error_size=-0.021772;	else
if(i<=180)error_size=-0.0233664;	else
if(i<=188)error_size=-0.0242542;	else
if(i<=196)error_size=-0.0245992;	else
if(i<=204)error_size=-0.0233023;	else
if(i<=212)error_size=-0.0214122;	else
if(i<=220)error_size=-0.0179146;	else{cout<<"Same size";}

 beamspec_bg_down->Fill(i,error_size);

}

}

if (Pe==-0.8&&Pp==-0.3){

found_pol = true;

for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=0.00280361;	else
if(i<=12)error_size=0.00273614;	else
if(i<=20)error_size=0.00333707;	else
if(i<=28)error_size=0.003042;	else
if(i<=36)error_size=0.00288497;	else
if(i<=44)error_size=0.00239821;	else
if(i<=52)error_size=0.00258238;	else
if(i<=60)error_size=0.00235638;	else
if(i<=68)error_size=0.00325895;	else
if(i<=76)error_size=0.00394164;	else
if(i<=84)error_size=0.00472285;	else
if(i<=92)error_size=0.00490326;	else
if(i<=100)error_size=0.00476331;	else
if(i<=108)error_size=0.00505717;	else
if(i<=116)error_size=0.00496697;	else
if(i<=124)error_size=0.00476661;	else
if(i<=132)error_size=0.00467325;	else
if(i<=140)error_size=0.00442174;	else
if(i<=148)error_size=0.00466676;	else
if(i<=156)error_size=0.00467285;	else
if(i<=164)error_size=0.00529449;	else
if(i<=172)error_size=0.00575798;	else
if(i<=180)error_size=0.0068041;	else
if(i<=188)error_size=0.0090587;	else
if(i<=196)error_size=0.0100875;	else
if(i<=204)error_size=0.0104986;	else
if(i<=212)error_size=0.0110027;	else
if(i<=220)error_size=0.0105148;	else{cout<<"Same size";}

 beamspec_bg_up->Fill(i,error_size);

}

for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=-0.00299749;	else
if(i<=12)error_size=-0.00292535;	else
if(i<=20)error_size=-0.00356785;	else
if(i<=28)error_size=-0.00325236;	else
if(i<=36)error_size=-0.00308448;	else
if(i<=44)error_size=-0.00256404;	else
if(i<=52)error_size=-0.00276095;	else
if(i<=60)error_size=-0.00251931;	else
if(i<=68)error_size=-0.00348433;	else
if(i<=76)error_size=-0.00421424;	else
if(i<=84)error_size=-0.00504949;	else
if(i<=92)error_size=-0.00524238;	else
if(i<=100)error_size=-0.00509275;	else
if(i<=108)error_size=-0.00540694;	else
if(i<=116)error_size=-0.0053105;	else
if(i<=124)error_size=-0.00509628;	else
if(i<=132)error_size=-0.00499646;	else
if(i<=140)error_size=-0.00472755;	else
if(i<=148)error_size=-0.00498952;	else
if(i<=156)error_size=-0.00499603;	else
if(i<=164)error_size=-0.00566068;	else
if(i<=172)error_size=-0.00615623;	else
if(i<=180)error_size=-0.00727471;	else
if(i<=188)error_size=-0.00968528;	else
if(i<=196)error_size=-0.0107852;	else
if(i<=204)error_size=-0.0112248;	else
if(i<=212)error_size=-0.0117638;	else
if(i<=220)error_size=-0.0112421;	else{cout<<"Same size";}

 beamspec_bg_down->Fill(i,error_size);

}

}


if (Pe==0.8&&Pp==0.3){

found_pol = true;

for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=0.00402824;	else
if(i<=12)error_size=0.00385267;	else
if(i<=20)error_size=0.00659368;	else
if(i<=28)error_size=0.00761976;	else
if(i<=36)error_size=0.00509665;	else
if(i<=44)error_size=0.00354126;	else
if(i<=52)error_size=0.00453881;	else
if(i<=60)error_size=0.00436874;	else
if(i<=68)error_size=0.00663879;	else
if(i<=76)error_size=0.0105587;	else
if(i<=84)error_size=0.0130251;	else
if(i<=92)error_size=0.0138745;	else
if(i<=100)error_size=0.0131999;	else
if(i<=108)error_size=0.0140603;	else
if(i<=116)error_size=0.0137221;	else
if(i<=124)error_size=0.01396;	else
if(i<=132)error_size=0.0128512;	else
if(i<=140)error_size=0.0124966;	else
if(i<=148)error_size=0.0125833;	else
if(i<=156)error_size=0.0124315;	else
if(i<=164)error_size=0.0121525;	else
if(i<=172)error_size=0.0139495;	else
if(i<=180)error_size=0.0155867;	else
if(i<=188)error_size=0.0174633;	else
if(i<=196)error_size=0.0184684;	else
if(i<=204)error_size=0.0181606;	else
if(i<=212)error_size=0.0173438;	else
if(i<=220)error_size=0.0150411;	else{cout<<"Same size";}

 beamspec_bg_up->Fill(i,error_size);

}

for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=-0.00430683;	else
if(i<=12)error_size=-0.00411912;	else
if(i<=20)error_size=-0.00704974;	else
if(i<=28)error_size=-0.0081468;	else
if(i<=36)error_size=-0.00544915;	else
if(i<=44)error_size=-0.00378617;	else
if(i<=52)error_size=-0.00485272;	else
if(i<=60)error_size=-0.00467088;	else
if(i<=68)error_size=-0.00709797;	else
if(i<=76)error_size=-0.011289;	else
if(i<=84)error_size=-0.0139261;	else
if(i<=92)error_size=-0.0148342;	else
if(i<=100)error_size=-0.014113;	else
if(i<=108)error_size=-0.0150329;	else
if(i<=116)error_size=-0.0146713;	else
if(i<=124)error_size=-0.0149256;	else
if(i<=132)error_size=-0.0137401;	else
if(i<=140)error_size=-0.013361;	else
if(i<=148)error_size=-0.0134537;	else
if(i<=156)error_size=-0.0132914;	else
if(i<=164)error_size=-0.0129931;	else
if(i<=172)error_size=-0.0149144;	else
if(i<=180)error_size=-0.0166649;	else
if(i<=188)error_size=-0.0186712;	else
if(i<=196)error_size=-0.019746;	else
if(i<=204)error_size=-0.0194168;	else
if(i<=212)error_size=-0.0185435;	else
if(i<=220)error_size=-0.0160815;	else{cout<<"Same size";}

 beamspec_bg_down->Fill(i,error_size);

}

}


if (Pe==-0.8&&Pp==0.3){

found_pol = true;

for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=0.00272412;	else
if(i<=12)error_size=0.00254912;	else
if(i<=20)error_size=0.00284029;	else
if(i<=28)error_size=0.00267035;	else
if(i<=36)error_size=0.00243211;	else
if(i<=44)error_size=0.00217688;	else
if(i<=52)error_size=0.00229674;	else
if(i<=60)error_size=0.00233151;	else
if(i<=68)error_size=0.00300775;	else
if(i<=76)error_size=0.00362598;	else
if(i<=84)error_size=0.00442343;	else
if(i<=92)error_size=0.00457797;	else
if(i<=100)error_size=0.00445481;	else
if(i<=108)error_size=0.00467976;	else
if(i<=116)error_size=0.00459239;	else
if(i<=124)error_size=0.0043614;	else
if(i<=132)error_size=0.00429879;	else
if(i<=140)error_size=0.00403875;	else
if(i<=148)error_size=0.00427632;	else
if(i<=156)error_size=0.00427506;	else
if(i<=164)error_size=0.00492252;	else
if(i<=172)error_size=0.00529256;	else
if(i<=180)error_size=0.00627951;	else
if(i<=188)error_size=0.0085112;	else
if(i<=196)error_size=0.0094918;	else
if(i<=204)error_size=0.00990129;	else
if(i<=212)error_size=0.010463;	else
if(i<=220)error_size=0.0100911;	else{cout<<"Same size";}

 beamspec_bg_up->Fill(i,error_size);

}
for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=-0.00291249;	else
if(i<=12)error_size=-0.00272539;	else
if(i<=20)error_size=-0.00303671;	else
if(i<=28)error_size=-0.00285501;	else
if(i<=36)error_size=-0.00260029;	else
if(i<=44)error_size=-0.0023274;	else
if(i<=52)error_size=-0.00245555;	else
if(i<=60)error_size=-0.00249272;	else
if(i<=68)error_size=-0.00321575;	else
if(i<=76)error_size=-0.00387674;	else
if(i<=84)error_size=-0.00472936;	else
if(i<=92)error_size=-0.00489459;	else
if(i<=100)error_size=-0.00476291;	else
if(i<=108)error_size=-0.00500342;	else
if(i<=116)error_size=-0.00491;	else
if(i<=124)error_size=-0.00466303;	else
if(i<=132)error_size=-0.00459609;	else
if(i<=140)error_size=-0.00431806;	else
if(i<=148)error_size=-0.00457208;	else
if(i<=156)error_size=-0.00457072;	else
if(i<=164)error_size=-0.00526297;	else
if(i<=172)error_size=-0.00565861;	else
if(i<=180)error_size=-0.00671384;	else
if(i<=188)error_size=-0.00909991;	else
if(i<=196)error_size=-0.0101483;	else
if(i<=204)error_size=-0.0105862;	else
if(i<=212)error_size=-0.0111867;	else
if(i<=220)error_size=-0.0107891;	else{cout<<"Same size";}

 beamspec_bg_down->Fill(i,error_size);

}

}

if (Pe==-0.8&&Pp==0.){

	found_pol = true;

	for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=0.00275224;	else
if(i<=12)error_size=0.00261531;	else
if(i<=20)error_size=0.00301709;	else
if(i<=28)error_size=0.00280205;	else
if(i<=36)error_size=0.0025922;	else
if(i<=44)error_size=0.00225508;	else
if(i<=52)error_size=0.00239777;	else
if(i<=60)error_size=0.00234027;	else
if(i<=68)error_size=0.00309616;	else
if(i<=76)error_size=0.00373705;	else
if(i<=84)error_size=0.00452876;	else
if(i<=92)error_size=0.00469245;	else
if(i<=100)error_size=0.00456346;	else
if(i<=108)error_size=0.0048126;	else
if(i<=116)error_size=0.00472428;	else
if(i<=124)error_size=0.00450418;	else
if(i<=132)error_size=0.00443083;	else
if(i<=140)error_size=0.00417391;	else
if(i<=148)error_size=0.00441425;	else
if(i<=156)error_size=0.00441572;	else
if(i<=164)error_size=0.00505423;	else
if(i<=172)error_size=0.00545767;	else
if(i<=180)error_size=0.00646596;	else
if(i<=188)error_size=0.00870642;	else
if(i<=196)error_size=0.00970496;	else
if(i<=204)error_size=0.0101159;	else
if(i<=212)error_size=0.0106577;	else
if(i<=220)error_size=0.0102445;	else{cout<<"Same size";}

 beamspec_bg_up->Fill(i,error_size);

}

	for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=-0.00294256;	else
if(i<=12)error_size=-0.00279616;	else
if(i<=20)error_size=-0.00322573;	else
if(i<=28)error_size=-0.00299582;	else
if(i<=36)error_size=-0.00277145;	else
if(i<=44)error_size=-0.00241101;	else
if(i<=52)error_size=-0.00256357;	else
if(i<=60)error_size=-0.0025021;	else
if(i<=68)error_size=-0.00331028;	else
if(i<=76)error_size=-0.0039955;	else
if(i<=84)error_size=-0.00484198;	else
if(i<=92)error_size=-0.00501699;	else
if(i<=100)error_size=-0.00487907;	else
if(i<=108)error_size=-0.00514545;	else
if(i<=116)error_size=-0.00505102;	else
if(i<=124)error_size=-0.00481569;	else
if(i<=132)error_size=-0.00473727;	else
if(i<=140)error_size=-0.00446258;	else
if(i<=148)error_size=-0.00471954;	else
if(i<=156)error_size=-0.00472112;	else
if(i<=164)error_size=-0.00540379;	else
if(i<=172)error_size=-0.00583514;	else
if(i<=180)error_size=-0.00691318;	else
if(i<=188)error_size=-0.00930863;	else
if(i<=196)error_size=-0.0103762;	else
if(i<=204)error_size=-0.0108156;	else
if(i<=212)error_size=-0.0113948;	else
if(i<=220)error_size=-0.0109531;	else{cout<<"Same size";}

 beamspec_bg_down->Fill(i,error_size);

}

}


if (Pe==0.8&&Pp==0.){

	found_pol = true;

	for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=0.00448831;	else
if(i<=12)error_size=0.00459003;	else
if(i<=20)error_size=0.00763754;	else
if(i<=28)error_size=0.00893583;	else
if(i<=36)error_size=0.00605312;	else
if(i<=44)error_size=0.0043819;	else
if(i<=52)error_size=0.00564108;	else
if(i<=60)error_size=0.00562965;	else
if(i<=68)error_size=0.00920139;	else
if(i<=76)error_size=0.0145297;	else
if(i<=84)error_size=0.0184666;	else
if(i<=92)error_size=0.0194648;	else
if(i<=100)error_size=0.0182551;	else
if(i<=108)error_size=0.0194128;	else
if(i<=116)error_size=0.018814;	else
if(i<=124)error_size=0.0190878;	else
if(i<=132)error_size=0.0172303;	else
if(i<=140)error_size=0.0166363;	else
if(i<=148)error_size=0.0164531;	else
if(i<=156)error_size=0.0160472;	else
if(i<=164)error_size=0.0151597;	else
if(i<=172)error_size=0.0172693;	else
if(i<=180)error_size=0.0188936;	else
if(i<=188)error_size=0.02029;	else
if(i<=196)error_size=0.0209827;	else
if(i<=204)error_size=0.0202137;	else
if(i<=212)error_size=0.0188828;	else
if(i<=220)error_size=0.0160377;	else{cout<<"Same size";}

 beamspec_bg_up->Fill(i,error_size);

}

	for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=-0.00479873;	else
if(i<=12)error_size=-0.00490748;	else
if(i<=20)error_size=-0.00816581;	else
if(i<=28)error_size=-0.00955391;	else
if(i<=36)error_size=-0.00647178;	else
if(i<=44)error_size=-0.00468496;	else
if(i<=52)error_size=-0.00603124;	else
if(i<=60)error_size=-0.00601902;	else
if(i<=68)error_size=-0.00983784;	else
if(i<=76)error_size=-0.0155347;	else
if(i<=84)error_size=-0.019744;	else
if(i<=92)error_size=-0.0208113;	else
if(i<=100)error_size=-0.0195179;	else
if(i<=108)error_size=-0.0207556;	else
if(i<=116)error_size=-0.0201154;	else
if(i<=124)error_size=-0.0204082;	else
if(i<=132)error_size=-0.0184221;	else
if(i<=140)error_size=-0.0177871;	else
if(i<=148)error_size=-0.0175912;	else
if(i<=156)error_size=-0.0171572;	else
if(i<=164)error_size=-0.0162083;	else
if(i<=172)error_size=-0.0184639;	else
if(i<=180)error_size=-0.0202005;	else
if(i<=188)error_size=-0.0216935;	else
if(i<=196)error_size=-0.0224341;	else
if(i<=204)error_size=-0.021612;	else
if(i<=212)error_size=-0.020189;	else
if(i<=220)error_size=-0.0171471;	else{cout<<"Same size";}

 beamspec_bg_down->Fill(i,error_size);

}

}






if (Pe==0.8&&Pp==-0.6){

	found_pol = true;

	for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=0.00612975;	else
if(i<=12)error_size=0.00729991;	else
if(i<=20)error_size=0.0111945;	else
if(i<=28)error_size=0.0136174;	else
if(i<=36)error_size=0.00950562;	else
if(i<=44)error_size=0.00743584;	else
if(i<=52)error_size=0.00946159;	else
if(i<=60)error_size=0.0100637;	else
if(i<=68)error_size=0.018157;	else
if(i<=76)error_size=0.0277358;	else
if(i<=84)error_size=0.0357909;	else
if(i<=92)error_size=0.0360533;	else
if(i<=100)error_size=0.0324989;	else
if(i<=108)error_size=0.0338451;	else
if(i<=116)error_size=0.0321445;	else
if(i<=124)error_size=0.0318101;	else
if(i<=132)error_size=0.0275805;	else
if(i<=140)error_size=0.0259506;	else
if(i<=148)error_size=0.024729;	else
if(i<=156)error_size=0.0234255;	else
if(i<=164)error_size=0.0209573;	else
if(i<=172)error_size=0.0232543;	else
if(i<=180)error_size=0.0245214;	else
if(i<=188)error_size=0.0247408;	else
if(i<=196)error_size=0.0246737;	else
if(i<=204)error_size=0.0230496;	else
if(i<=212)error_size=0.0209109;	else
if(i<=220)error_size=0.0172973;	else{cout<<"Same size";}

 beamspec_bg_up->Fill(i,error_size);

}

	for(Int_t i=1;i<=220;i++){
if(i<=4)error_size=-0.00655372;	else
if(i<=12)error_size=-0.00780482;	else
if(i<=20)error_size=-0.0119688;	else
if(i<=28)error_size=-0.0145593;	else
if(i<=36)error_size=-0.0101631;	else
if(i<=44)error_size=-0.00795016;	else
if(i<=52)error_size=-0.010116;	else
if(i<=60)error_size=-0.0107598;	else
if(i<=68)error_size=-0.0194129;	else
if(i<=76)error_size=-0.0296544;	else
if(i<=84)error_size=-0.0382667;	else
if(i<=92)error_size=-0.0385473;	else
if(i<=100)error_size=-0.034747;	else
if(i<=108)error_size=-0.0361863;	else
if(i<=116)error_size=-0.0343681;	else
if(i<=124)error_size=-0.0340106;	else
if(i<=132)error_size=-0.0294883;	else
if(i<=140)error_size=-0.0277457;	else
if(i<=148)error_size=-0.0264396;	else
if(i<=156)error_size=-0.0250459;	else
if(i<=164)error_size=-0.022407;	else
if(i<=172)error_size=-0.0248629;	else
if(i<=180)error_size=-0.0262176;	else
if(i<=188)error_size=-0.0264522;	else
if(i<=196)error_size=-0.0263805;	else
if(i<=204)error_size=-0.0246441;	else
if(i<=212)error_size=-0.0223574;	else
if(i<=220)error_size=-0.0184938;	else{cout<<"Same size";}

 beamspec_bg_down->Fill(i,error_size);

}

}




if (found_pol==false) {
	cout << "NO BEAM SPECTRUM SYSTEMATICS IMPLEMENTED FOR THIS POLARISATION COMBINATION!" << endl;
	cout << "...now stopping..." << endl;
	return 0;
}




for(Int_t i=1;i<=220;i++){

if(i<=4)error_size=-0.00199127;	else
if(i<=16)error_size=-0.00214161;	else
if(i<=28)error_size=-0.00238241;	else
if(i<=40)error_size=-0.00240578;	else
if(i<=52)error_size=-0.00247291;	else
if(i<=64)error_size=-0.00263827;	else
if(i<=76)error_size=-0.00273896;	else
if(i<=88)error_size=-0.00292077;	else
if(i<=100)error_size=-0.00312058;	else
if(i<=112)error_size=-0.00318233;	else
if(i<=124)error_size=-0.00330692;	else
if(i<=136)error_size=-0.00352949;	else
if(i<=148)error_size=-0.00345355;	else
if(i<=160)error_size=-0.00395572;	else
if(i<=172)error_size=-0.00396147;	else
if(i<=184)error_size=-0.00421733;	else
if(i<=196)error_size=-0.0044173;	else
if(i<=208)error_size=-0.00468491;	else
if(i<=220)error_size=-0.0048324;	else {cout<<"Same size";}


if (OPvector==true){
	error_size=error_size*(0.997+0.000043*_mass*_mass);
	cout << "LS systematics scaled with vector fit function" << endl;
}
if (OPaxialv==true||OPscalarS==true){
	error_size=error_size*(0.756+exp(-1.382+0.0106*_mass));
	cout << "LS systematics scaled with axial-vector/scalar fit function" << endl;
}

beamspec_sig_up->Fill(i,error_size);

}

for(Int_t i=1;i<=220;i++){


if(i<=4)error_size=0.0021291;	else
if(i<=16)error_size=0.00228983;	else
if(i<=28)error_size=0.00254729;	else
if(i<=40)error_size=0.00257227;	else
if(i<=52)error_size=0.00264405;	else
if(i<=64)error_size=0.00282085;	else
if(i<=76)error_size=0.0029285;	else
if(i<=88)error_size=0.00312289;	else
if(i<=100)error_size=0.00333652;	else
if(i<=112)error_size=0.00340255;	else
if(i<=124)error_size=0.00353576;	else
if(i<=136)error_size=0.00377372;	else
if(i<=148)error_size=0.00369253;	else
if(i<=160)error_size=0.00422943;	else
if(i<=172)error_size=0.00423558;	else
if(i<=184)error_size=0.00450914;	else
if(i<=196)error_size=0.00472295;	else
if(i<=208)error_size=0.00500906;	else
if(i<=220)error_size=0.00516676;	else {cout<<"Same size";}


if (OPvector==true){
	error_size=error_size*(0.997+0.000043*_mass*_mass);
	cout << "LS systematics scaled with vector fit function" << endl;
}
if (OPaxialv==true||OPscalarS==true){
	error_size=error_size*(0.756+exp(-1.382+0.0106*_mass));
	cout << "LS systematics scaled with axial-vector/scalar fit function" << endl;
}

beamspec_sig_down->Fill(i,error_size);
}

  //FILL  Beam spectra parameters   errors 
        s=3;
//  TH1D h3 =   (*bh)+(*bh)*(*beamspec);
//  TH1D h4 =   (*bh)-(*bh)*(*beamspec);
//  histBgrSys[s][0]->Add(&h3);


 	histBgrSys[s][0]->Multiply(bh,beamspec_bg_up);
	histBgrSys[s][0]->Add(bh);	

 	histBgrSys[s][1]->Multiply(bh,beamspec_bg_down);
	histBgrSys[s][1]->Add(bh);

	histSignalSys[s][0]->Multiply(sh,beamspec_sig_up);
	histSignalSys[s][0]->Add(sh);

	histSignalSys[s][1]->Multiply(sh,beamspec_sig_down);
	histSignalSys[s][1]->Add(sh);




  //FILL  Selection Systematic errors
  	 s=4;

	for(Int_t i=1;i<=histBgrSys[s][0]->GetNbinsX();i++){
	Double_t bg_sys=0.002,sig_sys=0.002;	
	if(i==1){
	 t1->Branch("Selection_Systematic_errors_bg", &bg_sys);
	 t1->Branch("Selection_Systematic_errors_sig`", &sig_sys);}	
	histBgrSys[s][0]->Fill(i,bg_sys);
	histSignalSys[s][0]->Fill(i,sig_sys);
	}

#endif 






    cout<<" Integral before           :"<<sh->Integral()<<endl;  
//   	sh->Scale(pow(_lambda,4));
    cout<<" Integral after lambda^4   :"<<sh->Integral()<<endl;

   
    cout<<"Before add channel"<<endl;
    TSysLimitChannel *channel=new TSysLimitChannel();
    channel->SetData(bh);
    channel->SetPrediction(sh,bh,0); // without errors (sh,bh,0)

#ifdef Systematics
//################# NUMBER OF SYSTEMATIC ERRORS ########################
    NSYS=6;
// ADD 	SYSTEMATIC ERRORS
    for(Int_t m=0;m<NSYS;m++) {
	    TString name("Sys_error_");
	    if(m==0){name += "luminosity";
	    channel->AddSysRelative(histSignalSys[m][0],histBgrSys[m][0],name,0); // correlative add 1 
	    cout<< "DONE "<<name<<endl;
	    }else if (m==3) {
	    name += "beam spectra";
	    channel->AddSysUpDown(histSignalSys[m][0],histSignalSys[m][1],histBgrSys[m][0],histBgrSys[m][1],name,0); // correlative add 1 
	    cout<< "DONE "<<name<<endl;
	    } else if (m==4) {name += "selection";
	    	  name +=m;
	    channel->AddSysRelative(histSignalSys[m][0],histBgrSys[m][0],name,0); // correlative add 1
	    cout<< "DONE "<<name<<endl;
//	    channel->AddSysUpDown(histSignalSys[m][0],histSignalSys[m][1],histBgrSys[m][0],histBgrSys[m][1],name,1);
	    } else if (m==5) {
	    name += "whizard";
	    channel->AddSysRelative(histSignalSys[m][0],histBgrSys[m][0],name,0);
	    } else {name += "polarization";
	    	  name +=m;
	    channel->AddSysUpDown(histSignalSys[m][0],histSignalSys[m][1],histBgrSys[m][0],histBgrSys[m][1],name,0);
	    cout<< "DONE "<<name<<endl;
	    }
	
    
    
    }
    
#endif

    TSysLimit limit(0); 
    limit.AddChannel(channel);

     
    Double_t CL=0.0;
    Double_t k = 100.0;
    Double_t k_last = 100.0;
    Double_t stepwidth = 512;
    Double_t factor =0;
    int counter =0;
    

    
    while(stepwidth>0.0044)
    {

        CL=0.0;
    	while( CL < (1-ExpCL))
	{
 
	
	factor =1/pow(k,4);
	
 

	     limit.CalculateCL(factor,50000);
	     TSysLimitResult const *result=limit.GetResult(3); // Log(S+B/B)
	     result->Print();
	CL=result->GetDataCLs();   
	cout<<"CLs expected  = "<<result->GetExpectedCLs()<<", CLs observed "<<CL<<"| k ="<<k<<endl;
	

	
/*      for(Int_t method=0;method<limit.GetNMethod();method++) {
    	TSysLimitResult const *result=limit.GetResult(method);
	//TSysLimitResult const *result=limit.GetResult();
	Double_t_t cl;
        cout<<"=========================================\n";
	cout<<"Method: "<<method;
        if(method==limit.GetIndexPBock()) cout<<" (the default method)";
        cout<<"\n";
	result->Print();

	cl=result->GetDataCLs();
	cout<<"CLs = "<<cl;
	cl=result->GetExpectedCLs();
	cout<<" expected: "<<cl<<"\n";

	cl=result->GetDataCLb();
	cout<<"CLb = "<<cl;
	cl=result->GetExpectedCLb();
	cout<<" expected: "<<cl<<"\n";

	cl=result->GetDataCLsb();
	cout<<"CLsb = "<<cl;
	cl=result->GetExpectedCLsb();
	cout<<" expected: "<<cl<<"\n";

} */


	if (CL < (1-ExpCL))
	    k_last = k;
	  	
	k += stepwidth; 

	  counter++;
	  cout<<" COUNTER = "<<counter<<endl;
	  cout<<" stepwidth = "<<stepwidth<<endl;
	  if (counter>40)break;

	}

    k = k_last;
    stepwidth *= 0.5;
    }
	  cout<<" COUNTER AFTER = "<<counter<<endl;
	
   	Sensitivity->Fill(_mass,k);
	list->Add(Sensitivity);
		 
    cout <<"Lambda out "<<k<<endl; 
    cout <<"CLs = "<<CL<<endl;
    
    
      channel->Delete();
//      histSignalSys[0]->Delete();
//      histBgrSys[0]->Delete();
   
   if (l==0){
   t1->Fill();
   t1->Print();
  // list->Add(beamspec);
	}
     
     sh->Delete();
     bh->Delete();
 
    
//     for(Int_t method=0;method<limit.GetNMethod();method++) {
//     	TSysLimitResult const *result=limit.GetResult(method);
// 	//TSysLimitResult const *result=limit.GetResult();
// 	Double_t_t cl;
//         cout<<"=========================================\n";
// 	cout<<"Method: "<<method;
//         if(method==limit.GetIndexPBock()) cout<<" (the default method)";
//         cout<<"\n";
// 	result->Print();
// 
// 	cl=result->GetDataCLs();
// 	cout<<"CLs = "<<cl;
// 	cl=result->GetExpectedCLs();
// 	cout<<" expected: "<<cl<<"\n";
// 
// 	cl=result->GetDataCLb();
// 	cout<<"CLb = "<<cl;
// 	cl=result->GetExpectedCLb();
// 	cout<<" expected: "<<cl<<"\n";
// 
// 	cl=result->GetDataCLsb();
// 	cout<<"CLsb = "<<cl;
// 	cl=result->GetExpectedCLsb();
// 	cout<<" expected: "<<cl<<"\n";
// 
//         /* Double_t_t x,dx;
//         x=result->GetAvgXData(&dx);
//         cout<<"X(data) = "<<x<<" +/- "<<dx<<"\n";
//         x=result->GetAvgXB(&dx);
//         cout<<"X(B) = "<<x<<" +/- "<<dx<<"\n";
//         x=result->GetAvgXSB(&dx);
//         cout<<"X(SB) = "<<x<<" +/- "<<dx<<"\n"; */
// 
//     }

/*     cout<<"=========================================\n";
    cout<<"run TLIMIT without systematic error\n";
    TConfidenceLevel *tcl=
	TLimit::ComputeLimit(sh,bh,bh,50000);
    cout<<" CLb="<<tcl->CLb()<<"\n";
    cout<<" CLs="<<tcl->CLs()<<"\n";
    cout<<" CLsb="<<tcl->CLsb()<<"\n";
    cout<<" Expected CLs="<<tcl->GetExpectedCLs_b()<<" "<<"\n"; 
    cout<<" Expected CLsb="<<tcl->GetExpectedCLsb_b()<<" "<<"\n"; 
    cout<<" Expected CLb="<<tcl->GetExpectedCLb_b()<<" "<<"\n";
    
  */   

    	infile_sig->Close();
    	infile_bg->Close(); 
    
}
    
    f->cd();
 list->Print();
 list->Write();
 t1->Write();
// beamspec->Write(); 
  cout<<"END LOOP"<<endl;
  f->Close();
  cout<<"SAVE FILE"<<endl;  
 

 
    

    return 0;
}
