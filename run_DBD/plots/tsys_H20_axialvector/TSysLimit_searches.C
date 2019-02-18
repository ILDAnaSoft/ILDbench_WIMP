#include <sstream>
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

  Double_t lumi_tot = 4000.0; // set to desired lumi
  Double_t input_lumi = 500.0; // this probably never changes
  Double_t lumi_LL = 0.1*lumi_tot;
  Double_t lumi_LR = 0.4*lumi_tot;
  Double_t lumi_RL = 0.4*lumi_tot;
  Double_t lumi_RR = 0.1*lumi_tot;
  Double_t lumi_weight_LL = lumi_LL/input_lumi;
  Double_t lumi_weight_LR = lumi_LR/input_lumi;
  Double_t lumi_weight_RL = lumi_RL/input_lumi;
  Double_t lumi_weight_RR = lumi_RR/input_lumi;
  
  //Double_t Pe = 100.; // input from command line
  //Double_t Pp = 100.; // input from command line
  char filename[256];
  char _operator[20];
  Double_t _mass=1000; // input from command line
  Double_t _spin=0.5;
  Double_t _lambda =1580;
  Double_t ExpCL = 0.9545; //0.9
  
   
    if(argc>1) {
	cout <<" Mass = "<< argv[1] << endl;
	//cout <<" Pe = "<< argv[2] << endl;
	//cout <<" Pp = "<< argv[3] << endl;	
	    _mass=atof(argv[1]);
	     //Pe=atof(argv[2]);
	     //Pp=atof(argv[3]);
    } else { exit(1); } 

    //cout<<" Pe = "<<Pe<<"| Pp = "<<Pp<<endl;
    
    sprintf(filename,"outputs/Sensitivity_Lumi_%.0f_Lumi_LL_%.0f_Lumi_LR_%.0f_Lumi_RL_%.0f_Lumi_RR_%.0f_Mass%.0f_2Sigma.root",lumi_tot,lumi_LL,lumi_LR,lumi_RL,lumi_RR,_mass);
//    sprintf(filename,"Results/Sensitivity_Pe%.1f_Pp%.1f_Lumi%.0f_Mass%.0f_3Sigma_CLTSys_onebin_with_errors.root",Pe,Pp,lumi,_mass);
//    sprintf(filename,"Results/Sensitivity_Pe%.1f_Pp%.1f_Lumi%.0f_Mass%.0f_90CLTSys_lumi_pole_polp_beamspec_select_withsys_corel.root",Pe,Pp,lumi,_mass);    
    
    cout<<filename<<endl;
    TFile * f= new TFile(filename,"recreate");
    TTree * t1=new TTree("Parameters","All parameters used in calculation");
    TList* list = new TList();
    TH1D* Sensitivity;
    
	 //t1->Branch("Pe", &Pe, "new_v/D");
	 //t1->Branch("Pp", &Pp, "new_v/D");	 
      t1->Branch("Lumi_LL", &lumi_LL, "new_v/D");
      t1->Branch("Lumi_LR", &lumi_LR, "new_v/D");
      t1->Branch("Lumi_RL", &lumi_RL, "new_v/D");
      t1->Branch("Lumi_RR", &lumi_RR, "new_v/D");
      t1->Branch("Lumi", &lumi_tot, "new_v/D");

	 t1->Branch("ExpCL", &ExpCL, "new_v/D"); 
	 
	 bool OPvector=false;
	 bool OPscalarS=false;
	 bool OPaxialv=false;
	 
for (int l=0;l<3;l++){
#if 1
     if (l != 2 ) continue;
#endif  	
     if (l == 0){
    		sprintf(_operator,"Vector");  
    		OPvector=true;
     } else if (l == 1){
	    	sprintf(_operator,"Scalar,s-channel");
	    	OPscalarS=true;
     }  else if (l == 2){ 
	    	sprintf(_operator,"Axial-vector");  
	    	OPaxialv=true;
    } else {cout<<"###########################FALD ############################### "<<endl;}

    sprintf(filename,"Sensitivity %s",_operator);
     Sensitivity = new TH1D(filename,filename,250,1,250);
    cout<<_operator<<endl;


 
//Create Beam spectra effect
 TH1D* beamspec_bg_down1 = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_bg_down2 = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_bg_down3 = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_bg_down4 = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_bg_up1 = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_bg_up2 = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_bg_up3 = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_bg_up4 = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_sig_up = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);
 TH1D* beamspec_sig_down = new TH1D("Beam spectra","Beam spectra",300,0.0,300.0);

    
    cout<<" Mass = "<<_mass<<endl;
   
#if 0
    sprintf(filename,"/afs/desy.de/group/flc/pool/haberm/wimps/FINAL_MC_SAMPLES/tsys3D/INPUT_SIGNAL/1D_Data_Signal_Pe-0.8_Pp-0.3_Lumi%.0f.root",input_lumi);
    TFile * infile_sig1 = new TFile(filename,"READ");
    infile_sig1->cd();
    sprintf(filename,"M%.0f_S%.1f_%s_Lambda%.0f",_mass,_spin,_operator,_lambda); 
    TH1D* sh1=(TH1D*)infile_sig1->Get(filename);

    sprintf(filename,"/afs/desy.de/group/flc/pool/haberm/wimps/FINAL_MC_SAMPLES/tsys3D/INPUT_SIGNAL/1D_Data_Signal_Pe-0.8_Pp0.3_Lumi%.0f.root",input_lumi);
    TFile * infile_sig2 = new TFile(filename,"READ");
    infile_sig2->cd();
    sprintf(filename,"M%.0f_S%.1f_%s_Lambda%.0f",_mass,_spin,_operator,_lambda); 
    TH1D* sh2=(TH1D*)infile_sig2->Get(filename);

    sprintf(filename,"/afs/desy.de/group/flc/pool/haberm/wimps/FINAL_MC_SAMPLES/tsys3D/INPUT_SIGNAL/1D_Data_Signal_Pe0.8_Pp-0.3_Lumi%.0f.root",input_lumi);
    TFile * infile_sig3 = new TFile(filename,"READ");
    infile_sig3->cd();
    sprintf(filename,"M%.0f_S%.1f_%s_Lambda%.0f",_mass,_spin,_operator,_lambda); 
    TH1D* sh3=(TH1D*)infile_sig3->Get(filename);

    sprintf(filename,"/afs/desy.de/group/flc/pool/haberm/wimps/FINAL_MC_SAMPLES/tsys3D/INPUT_SIGNAL/1D_Data_Signal_Pe0.8_Pp0.3_Lumi%.0f.root",input_lumi);
    TFile * infile_sig4 = new TFile(filename,"READ");
    infile_sig4->cd();
    sprintf(filename,"M%.0f_S%.1f_%s_Lambda%.0f",_mass,_spin,_operator,_lambda); 
    TH1D* sh4=(TH1D*)infile_sig4->Get(filename);

    sprintf(filename,"/afs/desy.de/group/flc/pool/haberm/wimps/FINAL_MC_SAMPLES/tsys3D/INPUT_BACKGROUND/Data_Background_Pe-0.8_Pp-0.3_Lumi%.0f.root",input_lumi);
    TFile * infile_bg1 = new TFile(filename,"READ");
    infile_bg1->cd();

    sprintf(filename,"Background_Pe-0.8_Pp-0.3_Lumi%.0f",input_lumi);
    TH1D* bh1=(TH1D*)infile_bg1->Get(filename);

    sprintf(filename,"/afs/desy.de/group/flc/pool/haberm/wimps/FINAL_MC_SAMPLES/tsys3D/INPUT_BACKGROUND/Data_Background_Pe-0.8_Pp0.3_Lumi%.0f.root",input_lumi);
    TFile * infile_bg2 = new TFile(filename,"READ");
    infile_bg2->cd();

    sprintf(filename,"Background_Pe-0.8_Pp0.3_Lumi%.0f",input_lumi);
    TH1D* bh2=(TH1D*)infile_bg2->Get(filename);


    sprintf(filename,"/afs/desy.de/group/flc/pool/haberm/wimps/FINAL_MC_SAMPLES/tsys3D/INPUT_BACKGROUND/Data_Background_Pe0.8_Pp-0.3_Lumi%.0f.root",input_lumi);
    TFile * infile_bg3 = new TFile(filename,"READ");
    infile_bg3->cd();

    sprintf(filename,"Background_Pe0.8_Pp-0.3_Lumi%.0f",input_lumi);
    TH1D* bh3=(TH1D*)infile_bg3->Get(filename);


    sprintf(filename,"/afs/desy.de/group/flc/pool/haberm/wimps/FINAL_MC_SAMPLES/tsys3D/INPUT_BACKGROUND/Data_Background_Pe0.8_Pp0.3_Lumi%.0f.root",input_lumi);
    TFile * infile_bg4 = new TFile(filename,"READ");
    infile_bg4->cd();

    sprintf(filename,"Background_Pe0.8_Pp0.3_Lumi%.0f",input_lumi);
    TH1D* bh4=(TH1D*)infile_bg4->Get(filename);
#else
        stringstream finname1;
        finname1 << "../outputs/output_mass" << _mass << "_epol-0.8_ppol-0.3_op" << l << ".root" << ends;
        TFile * infile_sig1 = new TFile(finname1.str().data(),"READ");
        TH1D* sh1=(TH1D*)infile_sig1->Get("hE_wimp");
        TH1D* bh1=(TH1D*)infile_sig1->Get("hE_bkg");

        stringstream finname2;
        finname2 << "../outputs/output_mass" << _mass << "_epol-0.8_ppol0.3_op" << l << ".root" << ends;
        TFile * infile_sig2 = new TFile(finname2.str().data(),"READ");
        TH1D* sh2=(TH1D*)infile_sig2->Get("hE_wimp");
        TH1D* bh2=(TH1D*)infile_sig2->Get("hE_bkg");

        stringstream finname3;
        finname3 << "../outputs/output_mass" << _mass << "_epol0.8_ppol-0.3_op" << l << ".root" << ends;
        TFile * infile_sig3 = new TFile(finname3.str().data(),"READ");
        TH1D* sh3=(TH1D*)infile_sig3->Get("hE_wimp");
        TH1D* bh3=(TH1D*)infile_sig3->Get("hE_bkg");

        stringstream finname4;
        finname4 << "../outputs/output_mass" << _mass << "_epol0.8_ppol0.3_op" << l << ".root" << ends;
        TFile * infile_sig4 = new TFile(finname4.str().data(),"READ");
        TH1D* sh4=(TH1D*)infile_sig4->Get("hE_wimp");
        TH1D* bh4=(TH1D*)infile_sig4->Get("hE_bkg");
#endif
    
 

//    cout<<" Integral after 1/lambda^4 :"<<sh->Integral()<<endl;
//    cout<<" Integral Background       :"<<bh->Integral()<<endl;
    
//       sh->Rebin(300);
//       bh->Rebin(300); 
  cout<<" Nbins        :"<<bh1->GetNbinsX()<<endl;

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
    TH1D *histBgrSys1[NSYS][2];
    TH1D *histBgrSys2[NSYS][2];
    TH1D *histBgrSys3[NSYS][2];
    TH1D *histBgrSys4[NSYS][2];
    TH1D *histSignalSys1[NSYS][2];
    TH1D *histSignalSys2[NSYS][2];
    TH1D *histSignalSys3[NSYS][2];
    TH1D *histSignalSys4[NSYS][2];
    for(Int_t s=0;s<NSYS;s++) {
       	for(Int_t ds=0;ds<2;ds++) {
	    TString name("Sys_error_");
	    name += sys_names[s];
	    
	    TString name1,name2;
	    
            name2 =name+"_background";
	    name2 +=ds;
	    cout<<name2<<endl;
	    histBgrSys1[s][ds]=new TH1D(name2,"Background errors 1",300,0.0,300.0);
	    histBgrSys2[s][ds]=new TH1D(name2,"Background errors 2",300,0.0,300.0);
	    histBgrSys3[s][ds]=new TH1D(name2,"Background errors 3",300,0.0,300.0);
	    histBgrSys4[s][ds]=new TH1D(name2,"Background errors 4",300,0.0,300.0);

	    name1 =name+"_signal";
	    name1 +=ds;
	    histSignalSys1[s][ds]=new TH1D(name1,"Signal errors 1",300,0.0,300.0);
	    histSignalSys2[s][ds]=new TH1D(name1,"Signal errors 2",300,0.0,300.0);
	    histSignalSys3[s][ds]=new TH1D(name1,"Signal errors 3",300,0.0,300.0);
	    histSignalSys4[s][ds]=new TH1D(name1,"Signal errors 4",300,0.0,300.0);
            cout<<name1<<endl;
    	}
    }
#endif     
 	bh1->Scale(lumi_weight_LL);
 	bh2->Scale(lumi_weight_LR);
 	bh3->Scale(lumi_weight_RL);
 	bh4->Scale(lumi_weight_RR);
 	sh1->Scale(lumi_weight_LL);
 	sh2->Scale(lumi_weight_LR);
 	sh3->Scale(lumi_weight_RL);
 	sh4->Scale(lumi_weight_RR);
	sh1->Scale(pow(_lambda,4));
	sh2->Scale(pow(_lambda,4));
	sh3->Scale(pow(_lambda,4));
	sh4->Scale(pow(_lambda,4));

#ifdef Systematics
// Fill errors histograms
cout<<"BINS = "<<histBgrSys1[0][0]->GetNbinsX()<<endl;
  

  
  //FILL  LUMINOSITY Systematic errors
    Int_t s=0;

	for(Int_t i=1;i<=histBgrSys1[s][0]->GetNbinsX();i++){
	Double_t bg_sys=0.0026,sig_sys=0.0026;
	if(i==1){
	 t1->Branch("bg_sys_lumi", &bg_sys);
	 t1->Branch("sig_sys_lumi", &sig_sys);}	
	histBgrSys1[s][0]->Fill(i,bg_sys);
	histBgrSys2[s][0]->Fill(i,bg_sys);
	histBgrSys3[s][0]->Fill(i,bg_sys);
	histBgrSys4[s][0]->Fill(i,bg_sys);
	histSignalSys1[s][0]->Fill(i,sig_sys);
	histSignalSys2[s][0]->Fill(i,sig_sys);
	histSignalSys3[s][0]->Fill(i,sig_sys);
	histSignalSys4[s][0]->Fill(i,sig_sys);
	}

  //FILL WHIZARD SYSTEMATIC ERRORS
	s=5;
	
	for (Int_t i=1; i<=histBgrSys1[s][0]->GetNbinsX(); i++){
		Double_t bg_sys=0.0013, sig_sys=0.0013;
		if(i==1){
	 	t1->Branch("bg_sys_lumi", &bg_sys);
	 	t1->Branch("sig_sys_lumi", &sig_sys);}	
	 	histBgrSys1[s][0]->Fill(i,bg_sys);
	 	histBgrSys2[s][0]->Fill(i,bg_sys);
	 	histBgrSys3[s][0]->Fill(i,bg_sys);
	 	histBgrSys4[s][0]->Fill(i,bg_sys);
	 	histSignalSys1[s][0]->Fill(i,sig_sys);
	 	histSignalSys2[s][0]->Fill(i,sig_sys);
	 	histSignalSys3[s][0]->Fill(i,sig_sys);
	 	histSignalSys4[s][0]->Fill(i,sig_sys);
	}   
  


  //FILL  Pp Systematic errors 
        s=1; 
	
	for(Int_t i=1;i<=histBgrSys1[s][0]->GetNbinsX();i++){
       Double_t error_size4=0.0008;
       Double_t error_size2=0.0008;
       Double_t error_size1=0.0004;
       Double_t error_size3=0.0004;

	Double_t signal_bin1 = sh1->GetBinContent(i);
	Double_t signal_bin2 = sh2->GetBinContent(i);
	Double_t signal_bin3 = sh3->GetBinContent(i);
	Double_t signal_bin4 = sh4->GetBinContent(i);
	Double_t bg_bin1 = bh1->GetBinContent(i);	
	Double_t bg_bin2 = bh2->GetBinContent(i);
	Double_t bg_bin3 = bh3->GetBinContent(i);
	Double_t bg_bin4 = bh4->GetBinContent(i);
//	cout<<"signal_bin = "<<signal_bin<<"| bg_bin = "<<bg_bin<<" ;"<<endl;
		 
	Double_t 	 bg_sysup1=bg_bin1*(1.0+error_size1);
	Double_t 	 bg_sysdown1=bg_bin1*(1.0-error_size1);
	Double_t 	 bg_sysup2=bg_bin2*(1.0+error_size2);
	Double_t 	 bg_sysdown2=bg_bin2*(1.0-error_size2);
	Double_t 	 bg_sysup3=bg_bin3*(1.0+error_size3);
	Double_t 	 bg_sysdown3=bg_bin3*(1.0-error_size3);
	Double_t 	 bg_sysup4=bg_bin4*(1.0+error_size4);
	Double_t 	 bg_sysdown4=bg_bin4*(1.0-error_size4);
	Double_t	 sig_sysup1=signal_bin1*(1.0+error_size1);
	Double_t	 sig_sysdown1=signal_bin1*(1.0-error_size1);
	Double_t	 sig_sysup2=signal_bin2*(1.0+error_size2);
	Double_t	 sig_sysdown2=signal_bin2*(1.0-error_size2);
	Double_t	 sig_sysup3=signal_bin3*(1.0+error_size3);
	Double_t	 sig_sysdown3=signal_bin3*(1.0-error_size3);
	Double_t	 sig_sysup4=signal_bin4*(1.0+error_size4);
	Double_t	 sig_sysdown4=signal_bin4*(1.0-error_size4);
	
	histBgrSys1[s][0]->Fill(i,bg_sysup1);
	histBgrSys1[s][1]->Fill(i,bg_sysdown1);
	histBgrSys2[s][0]->Fill(i,bg_sysup2);
	histBgrSys2[s][1]->Fill(i,bg_sysdown2);		
	histBgrSys3[s][0]->Fill(i,bg_sysup3);
	histBgrSys3[s][1]->Fill(i,bg_sysdown3);
	histBgrSys4[s][0]->Fill(i,bg_sysup4);
	histBgrSys4[s][1]->Fill(i,bg_sysdown4);
	histSignalSys1[s][0]->Fill(i,sig_sysup1);
	histSignalSys1[s][1]->Fill(i,sig_sysdown1);	
	histSignalSys2[s][0]->Fill(i,sig_sysup2);
	histSignalSys2[s][1]->Fill(i,sig_sysdown2);
	histSignalSys3[s][0]->Fill(i,sig_sysup3);
	histSignalSys3[s][1]->Fill(i,sig_sysdown3);	
	histSignalSys4[s][0]->Fill(i,sig_sysup4);
	histSignalSys4[s][1]->Fill(i,sig_sysdown4);
	
	}
  
 
  //FILL  Pe Systematic errors 
        s=2;
	for(Int_t i=1;i<=histBgrSys1[s][0]->GetNbinsX();i++){
	Double_t error_size1=0.0008;
	Double_t error_size2=0.0008;
	Double_t error_size3=0.0002;
	Double_t error_size4=0.0002;
	
	if(i==1){cout<<"POL E eroor 1 ="<<error_size1<<endl;
		 t1->Branch("Pe_Systematic_error1", &error_size1);
		 cout<<"POL E eroor 2 ="<<error_size2<<endl;
		 t1->Branch("Pe_Systematic_error2", &error_size2);
		 cout<<"POL E eroor 3 ="<<error_size3<<endl;
		 t1->Branch("Pe_Systematic_error3", &error_size3);
		 cout<<"POL E eroor 4 ="<<error_size4<<endl;
		 t1->Branch("Pe_Systematic_error4", &error_size4);}	
	
	Double_t signal_bin1 = sh1->GetBinContent(i);
	Double_t signal_bin2 = sh2->GetBinContent(i);
	Double_t signal_bin3 = sh3->GetBinContent(i);
	Double_t signal_bin4 = sh4->GetBinContent(i);
	Double_t bg_bin1 = bh1->GetBinContent(i);	
	Double_t bg_bin2 = bh2->GetBinContent(i);
	Double_t bg_bin3 = bh3->GetBinContent(i);
	Double_t bg_bin4 = bh4->GetBinContent(i);
//	cout<<"signal_bin = "<<signal_bin<<"| bg_bin = "<<bg_bin<<" ;"<<endl;
		 
	Double_t 	 bg_sysup1=bg_bin1*(1.0+error_size1);
	Double_t 	 bg_sysdown1=bg_bin1*(1.0-error_size1);
	Double_t 	 bg_sysup2=bg_bin2*(1.0+error_size2);
	Double_t 	 bg_sysdown2=bg_bin2*(1.0-error_size2);
	Double_t 	 bg_sysup3=bg_bin3*(1.0+error_size3);
	Double_t 	 bg_sysdown3=bg_bin3*(1.0-error_size3);
	Double_t 	 bg_sysup4=bg_bin4*(1.0+error_size4);
	Double_t 	 bg_sysdown4=bg_bin4*(1.0-error_size4);
	Double_t	 sig_sysup1=signal_bin1*(1.0+error_size1);
	Double_t	 sig_sysdown1=signal_bin1*(1.0-error_size1);
	Double_t	 sig_sysup2=signal_bin2*(1.0+error_size2);
	Double_t	 sig_sysdown2=signal_bin2*(1.0-error_size2);
	Double_t	 sig_sysup3=signal_bin3*(1.0+error_size3);
	Double_t	 sig_sysdown3=signal_bin3*(1.0-error_size3);
	Double_t	 sig_sysup4=signal_bin4*(1.0+error_size4);
	Double_t	 sig_sysdown4=signal_bin4*(1.0-error_size4);
	
	histBgrSys1[s][0]->Fill(i,bg_sysup1);
	histBgrSys1[s][1]->Fill(i,bg_sysdown1);
	histBgrSys2[s][0]->Fill(i,bg_sysup2);
	histBgrSys2[s][1]->Fill(i,bg_sysdown2);		
	histBgrSys3[s][0]->Fill(i,bg_sysup3);
	histBgrSys3[s][1]->Fill(i,bg_sysdown3);
	histBgrSys4[s][0]->Fill(i,bg_sysup4);
	histBgrSys4[s][1]->Fill(i,bg_sysdown4);
	histSignalSys1[s][0]->Fill(i,sig_sysup1);
	histSignalSys1[s][1]->Fill(i,sig_sysdown1);	
	histSignalSys2[s][0]->Fill(i,sig_sysup2);
	histSignalSys2[s][1]->Fill(i,sig_sysdown2);
	histSignalSys3[s][0]->Fill(i,sig_sysup3);
	histSignalSys3[s][1]->Fill(i,sig_sysdown3);	
	histSignalSys4[s][0]->Fill(i,sig_sysup4);
	histSignalSys4[s][1]->Fill(i,sig_sysdown4);

	}
 
 //##########################################################################
  //FILL  Beam spectra parameters   

Double_t error_size=0;

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

beamspec_bg_up3->Fill(i,error_size);
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

 beamspec_bg_down3->Fill(i,error_size);
}


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

 beamspec_bg_up1->Fill(i,error_size);

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

 beamspec_bg_down1->Fill(i,error_size);

}


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

 beamspec_bg_up4->Fill(i,error_size);

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

 beamspec_bg_down4->Fill(i,error_size);

}


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

 beamspec_bg_up2->Fill(i,error_size);

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

 beamspec_bg_down2->Fill(i,error_size);

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


 	histBgrSys1[s][0]->Multiply(bh1,beamspec_bg_up1);
	histBgrSys1[s][0]->Add(bh1);	

 	histBgrSys1[s][1]->Multiply(bh1,beamspec_bg_down1);
	histBgrSys1[s][1]->Add(bh1);

 	histBgrSys2[s][0]->Multiply(bh2,beamspec_bg_up2);
	histBgrSys2[s][0]->Add(bh2);	

 	histBgrSys2[s][1]->Multiply(bh2,beamspec_bg_down2);
	histBgrSys2[s][1]->Add(bh2);

 	histBgrSys3[s][0]->Multiply(bh3,beamspec_bg_up3);
	histBgrSys3[s][0]->Add(bh3);	

 	histBgrSys3[s][1]->Multiply(bh3,beamspec_bg_down3);
	histBgrSys3[s][1]->Add(bh3);

 	histBgrSys4[s][0]->Multiply(bh4,beamspec_bg_up4);
	histBgrSys4[s][0]->Add(bh4);	

 	histBgrSys4[s][1]->Multiply(bh4,beamspec_bg_down4);
	histBgrSys4[s][1]->Add(bh4);



	histSignalSys1[s][0]->Multiply(sh1,beamspec_sig_up);
	histSignalSys1[s][0]->Add(sh1);

	histSignalSys1[s][1]->Multiply(sh1,beamspec_sig_down);
	histSignalSys1[s][1]->Add(sh1);

	histSignalSys2[s][0]->Multiply(sh2,beamspec_sig_up);
	histSignalSys2[s][0]->Add(sh2);

	histSignalSys2[s][1]->Multiply(sh2,beamspec_sig_down);
	histSignalSys2[s][1]->Add(sh2);

	histSignalSys3[s][0]->Multiply(sh3,beamspec_sig_up);
	histSignalSys3[s][0]->Add(sh3);

	histSignalSys3[s][1]->Multiply(sh3,beamspec_sig_down);
	histSignalSys3[s][1]->Add(sh3);

	histSignalSys4[s][0]->Multiply(sh4,beamspec_sig_up);
	histSignalSys4[s][0]->Add(sh4);

	histSignalSys4[s][1]->Multiply(sh4,beamspec_sig_down);
	histSignalSys4[s][1]->Add(sh4);




  //FILL  Selection Systematic errors
  	 s=4;

	for(Int_t i=1;i<=histBgrSys1[s][0]->GetNbinsX();i++){
	Double_t bg_sys=0.002,sig_sys=0.002;	
	if(i==1){
	 t1->Branch("Selection_Systematic_errors_bg", &bg_sys);
	 t1->Branch("Selection_Systematic_errors_sig`", &sig_sys);}	
	histBgrSys1[s][0]->Fill(i,bg_sys);
	histBgrSys2[s][0]->Fill(i,bg_sys);
	histBgrSys3[s][0]->Fill(i,bg_sys);
	histBgrSys4[s][0]->Fill(i,bg_sys);
	histSignalSys1[s][0]->Fill(i,sig_sys);
	histSignalSys2[s][0]->Fill(i,sig_sys);
	histSignalSys3[s][0]->Fill(i,sig_sys);
	histSignalSys4[s][0]->Fill(i,sig_sys);
	}

#endif 






    cout<<" Integral before           :"<<sh1->Integral()<<endl;  
//   	sh->Scale(pow(_lambda,4));
    cout<<" Integral after lambda^4   :"<<sh1->Integral()<<endl;

   
    cout<<"Before add channel"<<endl;
    TSysLimitChannel *channel1=new TSysLimitChannel();
    channel1->SetData(bh1);
    channel1->SetPrediction(sh1,bh1,0); // without errors (sh,bh,0)

    TSysLimitChannel *channel2=new TSysLimitChannel();
    channel2->SetData(bh2);
    channel2->SetPrediction(sh2,bh2,0); // without errors (sh,bh,0)

    TSysLimitChannel *channel3=new TSysLimitChannel();
    channel3->SetData(bh3);
    channel3->SetPrediction(sh3,bh3,0); // without errors (sh,bh,0)

    TSysLimitChannel *channel4=new TSysLimitChannel();
    channel4->SetData(bh4);
    channel4->SetPrediction(sh4,bh4,0); // without errors (sh,bh,0)

#ifdef Systematics
//################# NUMBER OF SYSTEMATIC ERRORS ########################
    NSYS=6;
// ADD 	SYSTEMATIC ERRORS
    for(Int_t m=0;m<NSYS;m++) {
	    TString name("Sys_error_");
	    if(m==0){name += "luminosity";
	    channel1->AddSysRelative(histSignalSys1[m][0],histBgrSys1[m][0],name,0); // correlative add 1 
	    channel2->AddSysRelative(histSignalSys2[m][0],histBgrSys2[m][0],name,0);
	    channel3->AddSysRelative(histSignalSys3[m][0],histBgrSys3[m][0],name,0);
	    channel4->AddSysRelative(histSignalSys4[m][0],histBgrSys4[m][0],name,0);
	    cout<< "DONE "<<name<<endl;
	    }else if (m==3) {
	    name += "beam spectra";
	    channel1->AddSysUpDown(histSignalSys1[m][0],histSignalSys1[m][1],histBgrSys1[m][0],histBgrSys1[m][1],name,0); // correlative add 1 
	    channel2->AddSysUpDown(histSignalSys2[m][0],histSignalSys2[m][1],histBgrSys2[m][0],histBgrSys2[m][1],name,0);
	    channel3->AddSysUpDown(histSignalSys3[m][0],histSignalSys3[m][1],histBgrSys3[m][0],histBgrSys3[m][1],name,0);
	    channel4->AddSysUpDown(histSignalSys4[m][0],histSignalSys4[m][1],histBgrSys4[m][0],histBgrSys4[m][1],name,0);
	    cout<< "DONE "<<name<<endl;
	    } else if (m==4) {name += "selection";
	    	  name +=m;
	    channel1->AddSysRelative(histSignalSys1[m][0],histBgrSys1[m][0],name,0); // correlative add 1
	    channel2->AddSysRelative(histSignalSys2[m][0],histBgrSys2[m][0],name,0);
	    channel3->AddSysRelative(histSignalSys3[m][0],histBgrSys3[m][0],name,0);
	    channel4->AddSysRelative(histSignalSys4[m][0],histBgrSys4[m][0],name,0);
	    cout<< "DONE "<<name<<endl;
//	    channel->AddSysUpDown(histSignalSys[m][0],histSignalSys[m][1],histBgrSys[m][0],histBgrSys[m][1],name,1);
	    } else if (m==5) {
	    name += "whizard";
	    channel1->AddSysRelative(histSignalSys1[m][0],histBgrSys1[m][0],name,0);
	    channel2->AddSysRelative(histSignalSys2[m][0],histBgrSys2[m][0],name,0);
	    channel3->AddSysRelative(histSignalSys3[m][0],histBgrSys3[m][0],name,0);
	    channel4->AddSysRelative(histSignalSys4[m][0],histBgrSys4[m][0],name,0);
	    } else {name += "polarization";
	    	  name +=m;
	    channel1->AddSysUpDown(histSignalSys1[m][0],histSignalSys1[m][1],histBgrSys1[m][0],histBgrSys1[m][1],name,0);
	    channel2->AddSysUpDown(histSignalSys2[m][0],histSignalSys2[m][1],histBgrSys2[m][0],histBgrSys2[m][1],name,0);
	    channel3->AddSysUpDown(histSignalSys3[m][0],histSignalSys3[m][1],histBgrSys3[m][0],histBgrSys3[m][1],name,0);
	    channel4->AddSysUpDown(histSignalSys4[m][0],histSignalSys4[m][1],histBgrSys4[m][0],histBgrSys4[m][1],name,0);
	    cout<< "DONE "<<name<<endl;
	    }
	
    
    
    }
    
#endif

    TSysLimit limit(0); 
    limit.AddChannel(channel1);
    limit.AddChannel(channel2);
    limit.AddChannel(channel3);
    limit.AddChannel(channel4);

     
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
    
    
      channel1->Delete();
      channel2->Delete();
      channel3->Delete();
      channel4->Delete();
//      histSignalSys[0]->Delete();
//      histBgrSys[0]->Delete();
   
   if (l==0){
   t1->Fill();
   t1->Print();
  // list->Add(beamspec);
	}

     sh1->Delete();
     sh2->Delete();
     sh3->Delete();
     sh4->Delete();
     bh1->Delete();
     bh2->Delete();
     bh3->Delete();
     bh4->Delete();
 
    
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

    	infile_sig1->Close();
    	infile_sig2->Close();
    	infile_sig3->Close();
    	infile_sig4->Close();
    	//infile_bg1->Close(); 
    	//infile_bg2->Close();
    	//infile_bg3->Close();
    	//infile_bg4->Close();
    
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
