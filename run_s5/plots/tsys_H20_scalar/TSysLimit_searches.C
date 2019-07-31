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
#include "TSystem.h"

using namespace std;

#define Systematics

int main(int argc, char const *argv[]) {

 if (gSystem->AccessPathName("outputs")) {
  cerr << "outputs does not exist!" << endl;
  cerr << "Creating outputs directory..." << endl;
  gSystem->Exec("mkdir outputs");
  cerr << "Done!" << endl;
 } 



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
    
    //sprintf(filename,"outputs/Sensitivity_Lumi_%.0f_Lumi_LL_%.0f_Lumi_LR_%.0f_Lumi_RL_%.0f_Lumi_RR_%.0f_Mass%.0f_2Sigma.root",lumi_tot,lumi_LL,lumi_LR,lumi_RL,lumi_RR,_mass);
    sprintf(filename,"outputs/Sensitivity_Lumi_%.0f_Lumi_LL_%.0f_Lumi_LR_%.0f_Lumi_RL_%.0f_Lumi_RR_%.0f_Mass%.3g_2Sigma.root",lumi_tot,lumi_LL,lumi_LR,lumi_RL,lumi_RR,_mass);
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
     if (l != 1 ) continue;
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
#if 0
     Sensitivity = new TH1D(filename,filename,250,1,250);
#else
const int nmass = 255;
const double masses[nmass] = 
{ 1.e-9, 1.e-6, 1.e-3, 0.1,
  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10.,
 11., 12., 13., 14., 15., 16., 17., 18., 19., 20.,
 21., 22., 23., 24., 25., 26., 27., 28., 29., 30.,
 31., 32., 33., 34., 35., 36., 37., 38., 39., 40.,
 41., 42., 43., 44., 45., 46., 47., 48., 49., 50.,
 51., 52., 53., 54., 55., 56., 57., 58., 59., 60.,
 61., 62., 63., 64., 65., 66., 67., 68., 69., 70.,
 71., 72., 73., 74., 75., 76., 77., 78., 79., 80.,
 81., 82., 83., 84., 85., 86., 87., 88., 89., 90.,
 91., 92., 93., 94., 95., 96., 97., 98., 99.,100.,
101.,102.,103.,104.,105.,106.,107.,108.,109.,110.,
111.,112.,113.,114.,115.,116.,117.,118.,119.,120.,
121.,122.,123.,124.,125.,126.,127.,128.,129.,130.,
131.,132.,133.,134.,135.,136.,137.,138.,139.,140.,
141.,142.,143.,144.,145.,146.,147.,148.,149.,150.,
151.,152.,153.,154.,155.,156.,157.,158.,159.,160.,
161.,162.,163.,164.,165.,166.,167.,168.,169.,170.,
171.,172.,173.,174.,175.,176.,177.,178.,179.,180.,
181.,182.,183.,184.,185.,186.,187.,188.,189.,190.,
191.,192.,193.,194.,195.,196.,197.,198.,199.,200.,
201.,202.,203.,204.,205.,206.,207.,208.,209.,210.,
211.,212.,213.,214.,215.,216.,217.,218.,219.,220.,
221.,222.,223.,224.,225.,226.,227.,228.,229.,230.,
231.,232.,233.,234.,235.,236.,237.,238.,239.,240.,
241.,242.,243.,244.,245.,246.,247.,248.,249.,250.,
251.};
     Sensitivity = new TH1D(filename,filename,nmass-1,masses);
#endif
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
        //finname1 << "../outputs_test/output_mass" << _mass << "_epol-0.8_ppol-0.3_op" << l << ".root" << ends;
        TFile * infile_sig1 = new TFile(finname1.str().data(),"READ");
        TH1D* sh1=(TH1D*)infile_sig1->Get("hE_wimp");
        TH1D* bh1=(TH1D*)infile_sig1->Get("hE_bkg");

        stringstream finname2;
        //finname2 << "../outputs/output_mass" << _mass << "_epol-0.8_ppol0.3_op" << l << ".root" << ends;
        finname2 << "../outputs_test/output_mass" << _mass << "_epol-0.8_ppol0.3_op" << l << ".root" << ends;
        TFile * infile_sig2 = new TFile(finname2.str().data(),"READ");
        TH1D* sh2=(TH1D*)infile_sig2->Get("hE_wimp");
        TH1D* bh2=(TH1D*)infile_sig2->Get("hE_bkg");

        stringstream finname3;
        finname3 << "../outputs/output_mass" << _mass << "_epol0.8_ppol-0.3_op" << l << ".root" << ends;
        //finname3 << "../outputs_test/output_mass" << _mass << "_epol0.8_ppol-0.3_op" << l << ".root" << ends;
        TFile * infile_sig3 = new TFile(finname3.str().data(),"READ");
        TH1D* sh3=(TH1D*)infile_sig3->Get("hE_wimp");
        TH1D* bh3=(TH1D*)infile_sig3->Get("hE_bkg");

        stringstream finname4;
        finname4 << "../outputs/output_mass" << _mass << "_epol0.8_ppol0.3_op" << l << ".root" << ends;
        //finname4 << "../outputs_test/output_mass" << _mass << "_epol0.8_ppol0.3_op" << l << ".root" << ends;
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

//	for(Int_t i=1;i<=220;i++){
for(Int_t i=1;i<=256;i++){
if(i<=4)error_size=0.00515536;	else
if(i<=12)error_size=0.00565114;	else
if(i<=20)error_size=0.00912941;	else
if(i<=28)error_size=0.0108754;	else
if(i<=36)error_size=0.00745131;	else
if(i<=44)error_size=0.00558222;	else
if(i<=52)error_size=0.00718882;	else
if(i<=60)error_size=0.00739812;	else
if(i<=68)error_size=0.0127743;	else
if(i<=76)error_size=0.0199586;	else
if(i<=84)error_size=0.0256957;	else
if(i<=92)error_size=0.0266059;	else
if(i<=100)error_size=0.0245221;	else
if(i<=108)error_size=0.0258785;	else
if(i<=116)error_size=0.0248569;	else
if(i<=124)error_size=0.0249769;	else
if(i<=132)error_size=0.0221096;	else
if(i<=140)error_size=0.0211073;	else
if(i<=148)error_size=0.0204979;	else
if(i<=156)error_size=0.0197116;	else
if(i<=164)error_size=0.0180942;	else
if(i<=172)error_size=0.0203637;	else
if(i<=180)error_size=0.0218549;	else
if(i<=188)error_size=0.0226852;	else
if(i<=196)error_size=0.0230078;	else
if(i<=204)error_size=0.0217949;	else
if(i<=212)error_size=0.0200271;	else
if(i<=220)error_size=0.0167558;	else
if(i<=228)error_size=0.0117962;	else
if(i<=236)error_size=0.00524025;	else
if(i<=244)error_size=-0.00221275;	else
if(i<=252)error_size=-0.0051049;	else
if(i<=260)error_size=-0.00445201;	else
{cout<<"Same size";}

beamspec_bg_up3->Fill(i,error_size);
}

//	for(Int_t i=1;i<=220;i++){
for(Int_t i=1;i<=256;i++){
if(i<=4)error_size=-0.00551192;	else
if(i<=12)error_size=-0.00604199;	else
if(i<=20)error_size=-0.00976088;	else
if(i<=28)error_size=-0.0116276;	else
if(i<=36)error_size=-0.0079667;	else
if(i<=44)error_size=-0.00596831;	else
if(i<=52)error_size=-0.00768605;	else
if(i<=60)error_size=-0.00790983;	else
if(i<=68)error_size=-0.0136579;	else
if(i<=76)error_size=-0.0213392;	else
if(i<=84)error_size=-0.0274732;	else
if(i<=92)error_size=-0.0284463;	else
if(i<=100)error_size=-0.0262184;	else
if(i<=108)error_size=-0.0276686;	else
if(i<=116)error_size=-0.0265764;	else
if(i<=124)error_size=-0.0267047;	else
if(i<=132)error_size=-0.0236391;	else
if(i<=140)error_size=-0.0225674;	else
if(i<=148)error_size=-0.0219158;	else
if(i<=156)error_size=-0.0210751;	else
if(i<=164)error_size=-0.0193458;	else
if(i<=172)error_size=-0.0217724;	else
if(i<=180)error_size=-0.0233667;	else
if(i<=188)error_size=-0.0242545;	else
if(i<=196)error_size=-0.0245994;	else
if(i<=204)error_size=-0.0233025;	else
if(i<=212)error_size=-0.0214125;	else
if(i<=220)error_size=-0.0179148;	else
if(i<=228)error_size=-0.0126122;	else
if(i<=236)error_size=-0.00560269;	else
if(i<=244)error_size=0.00236589;	else
if(i<=252)error_size=0.00545811;	else
if(i<=260)error_size=0.00476005;	else
{cout<<"Same size";}

 beamspec_bg_down3->Fill(i,error_size);
}


//for(Int_t i=1;i<=220;i++){
for(Int_t i=1;i<=256;i++){
if(i<=4)error_size=0.00280405;	else
if(i<=12)error_size=0.00273633;	else
if(i<=20)error_size=0.00333868;	else
if(i<=28)error_size=0.00304412;	else
if(i<=36)error_size=0.00288591;	else
if(i<=44)error_size=0.00239835;	else
if(i<=52)error_size=0.00258283;	else
if(i<=60)error_size=0.00235648;	else
if(i<=68)error_size=0.00325887;	else
if(i<=76)error_size=0.00394223;	else
if(i<=84)error_size=0.00472291;	else
if(i<=92)error_size=0.00490335;	else
if(i<=100)error_size=0.00476342;	else
if(i<=108)error_size=0.00505719;	else
if(i<=116)error_size=0.00496699;	else
if(i<=124)error_size=0.00476663;	else
if(i<=132)error_size=0.00467327;	else
if(i<=140)error_size=0.00442177;	else
if(i<=148)error_size=0.00466679;	else
if(i<=156)error_size=0.00467288;	else
if(i<=164)error_size=0.00529454;	else
if(i<=172)error_size=0.00575803;	else
if(i<=180)error_size=0.00680414;	else
if(i<=188)error_size=0.00905874;	else
if(i<=196)error_size=0.0100875;	else
if(i<=204)error_size=0.0104987;	else
if(i<=212)error_size=0.0110028;	else
if(i<=220)error_size=0.0105149;	else
if(i<=228)error_size=0.00748501;	else
if(i<=236)error_size=0.003355;	else
if(i<=244)error_size=-0.00263181;	else
if(i<=252)error_size=-0.00516093;	else
if(i<=260)error_size=-0.00443009;	else
{cout<<"Same size";}

 beamspec_bg_up1->Fill(i,error_size);

}

//for(Int_t i=1;i<=220;i++){
for(Int_t i=1;i<=256;i++){
if(i<=4)error_size=-0.00299795;	else
if(i<=12)error_size=-0.00292555;	else
if(i<=20)error_size=-0.00356956;	else
if(i<=28)error_size=-0.00325464;	else
if(i<=36)error_size=-0.00308548;	else
if(i<=44)error_size=-0.00256419;	else
if(i<=52)error_size=-0.00276143;	else
if(i<=60)error_size=-0.00251942;	else
if(i<=68)error_size=-0.00348424;	else
if(i<=76)error_size=-0.00421487;	else
if(i<=84)error_size=-0.00504956;	else
if(i<=92)error_size=-0.00524248;	else
if(i<=100)error_size=-0.00509287;	else
if(i<=108)error_size=-0.00540696;	else
if(i<=116)error_size=-0.00531052;	else
if(i<=124)error_size=-0.0050963;	else
if(i<=132)error_size=-0.00499649;	else
if(i<=140)error_size=-0.00472759;	else
if(i<=148)error_size=-0.00498956;	else
if(i<=156)error_size=-0.00499607;	else
if(i<=164)error_size=-0.00566072;	else
if(i<=172)error_size=-0.00615628;	else
if(i<=180)error_size=-0.00727476;	else
if(i<=188)error_size=-0.00968533;	else
if(i<=196)error_size=-0.0107853;	else
if(i<=204)error_size=-0.0112248;	else
if(i<=212)error_size=-0.0117638;	else
if(i<=220)error_size=-0.0112422;	else
if(i<=228)error_size=-0.00800273;	else
if(i<=236)error_size=-0.00358702;	else
if(i<=244)error_size=0.00281394;	else
if(i<=252)error_size=0.00551801;	else
if(i<=260)error_size=0.00473662;	else
{cout<<"Same size";}

 beamspec_bg_down1->Fill(i,error_size);

}


//for(Int_t i=1;i<=220;i++){
for(Int_t i=1;i<=256;i++){
if(i<=4)error_size=0.00405329;	else
if(i<=12)error_size=0.00386146;	else
if(i<=20)error_size=0.00667643;	else
if(i<=28)error_size=0.00773925;	else
if(i<=36)error_size=0.00515258;	else
if(i<=44)error_size=0.0035471;	else
if(i<=52)error_size=0.00456318;	else
if(i<=60)error_size=0.00437243;	else
if(i<=68)error_size=0.00662979;	else
if(i<=76)error_size=0.0105942;	else
if(i<=84)error_size=0.0130246;	else
if(i<=92)error_size=0.0138775;	else
if(i<=100)error_size=0.0132036;	else
if(i<=108)error_size=0.0140611;	else
if(i<=116)error_size=0.013723;	else
if(i<=124)error_size=0.0139609;	else
if(i<=132)error_size=0.0128523;	else
if(i<=140)error_size=0.0124978;	else
if(i<=148)error_size=0.0125847;	else
if(i<=156)error_size=0.0124329;	else
if(i<=164)error_size=0.012154;	else
if(i<=172)error_size=0.0139508;	else
if(i<=180)error_size=0.0155879;	else
if(i<=188)error_size=0.0174642;	else
if(i<=196)error_size=0.0184692;	else
if(i<=204)error_size=0.0181613;	else
if(i<=212)error_size=0.0173445;	else
if(i<=220)error_size=0.0150418;	else
if(i<=228)error_size=0.0107095;	else
if(i<=236)error_size=0.00480041;	else
if(i<=244)error_size=-0.00230374;	else
if(i<=252)error_size=-0.00511648;	else
if(i<=260)error_size=-0.0044473;	else
{cout<<"Same size";}

 beamspec_bg_up4->Fill(i,error_size);

}

//for(Int_t i=1;i<=220;i++){
for(Int_t i=1;i<=256;i++){
if(i<=4)error_size=-0.00433361;	else
if(i<=12)error_size=-0.00412851;	else
if(i<=20)error_size=-0.00713822;	else
if(i<=28)error_size=-0.00827456;	else
if(i<=36)error_size=-0.00550895;	else
if(i<=44)error_size=-0.0037924;	else
if(i<=52)error_size=-0.00487877;	else
if(i<=60)error_size=-0.00467483;	else
if(i<=68)error_size=-0.00708835;	else
if(i<=76)error_size=-0.011327;	else
if(i<=84)error_size=-0.0139255;	else
if(i<=92)error_size=-0.0148374;	else
if(i<=100)error_size=-0.0141169;	else
if(i<=108)error_size=-0.0150337;	else
if(i<=116)error_size=-0.0146722;	else
if(i<=124)error_size=-0.0149266;	else
if(i<=132)error_size=-0.0137413;	else
if(i<=140)error_size=-0.0133623;	else
if(i<=148)error_size=-0.0134552;	else
if(i<=156)error_size=-0.0132929;	else
if(i<=164)error_size=-0.0129947;	else
if(i<=172)error_size=-0.0149158;	else
if(i<=180)error_size=-0.0166662;	else
if(i<=188)error_size=-0.0186723;	else
if(i<=196)error_size=-0.0197468;	else
if(i<=204)error_size=-0.0194176;	else
if(i<=212)error_size=-0.0185443;	else
if(i<=220)error_size=-0.0160823;	else
if(i<=228)error_size=-0.0114503;	else
if(i<=236)error_size=-0.00513242;	else
if(i<=244)error_size=0.00246318;	else
if(i<=252)error_size=0.00547049;	else
if(i<=260)error_size=0.00475502;	else
{cout<<"Same size";}

 beamspec_bg_down4->Fill(i,error_size);

}


//for(Int_t i=1;i<=220;i++){
for(Int_t i=1;i<=256;i++){
if(i<=4)error_size=0.00272456;	else
if(i<=12)error_size=0.00254932;	else
if(i<=20)error_size=0.00284199;	else
if(i<=28)error_size=0.00267255;	else
if(i<=36)error_size=0.00243309;	else
if(i<=44)error_size=0.00217703;	else
if(i<=52)error_size=0.00229721;	else
if(i<=60)error_size=0.00233161;	else
if(i<=68)error_size=0.00300768;	else
if(i<=76)error_size=0.00362658;	else
if(i<=84)error_size=0.00442349;	else
if(i<=92)error_size=0.00457807;	else
if(i<=100)error_size=0.00445492;	else
if(i<=108)error_size=0.00467978;	else
if(i<=116)error_size=0.00459241;	else
if(i<=124)error_size=0.00436142;	else
if(i<=132)error_size=0.00429882;	else
if(i<=140)error_size=0.00403878;	else
if(i<=148)error_size=0.00427636;	else
if(i<=156)error_size=0.0042751;	else
if(i<=164)error_size=0.00492256;	else
if(i<=172)error_size=0.0052926;	else
if(i<=180)error_size=0.00627956;	else
if(i<=188)error_size=0.00851125;	else
if(i<=196)error_size=0.00949185;	else
if(i<=204)error_size=0.00990133;	else
if(i<=212)error_size=0.010463;	else
if(i<=220)error_size=0.0100911;	else
if(i<=228)error_size=0.00717637;	else
if(i<=236)error_size=0.00320443;	else
if(i<=244)error_size=-0.00266882;	else
if(i<=252)error_size=-0.00516622;	else
if(i<=260)error_size=-0.00442813;	else
{cout<<"Same size";}

 beamspec_bg_up2->Fill(i,error_size);

}
//for(Int_t i=1;i<=220;i++){
for(Int_t i=1;i<=256;i++){
if(i<=4)error_size=-0.00291297;	else
if(i<=12)error_size=-0.00272561;	else
if(i<=20)error_size=-0.00303851;	else
if(i<=28)error_size=-0.00285736;	else
if(i<=36)error_size=-0.00260133;	else
if(i<=44)error_size=-0.00232756;	else
if(i<=52)error_size=-0.00245605;	else
if(i<=60)error_size=-0.00249284;	else
if(i<=68)error_size=-0.00321567;	else
if(i<=76)error_size=-0.00387738;	else
if(i<=84)error_size=-0.00472942;	else
if(i<=92)error_size=-0.00489469;	else
if(i<=100)error_size=-0.00476303;	else
if(i<=108)error_size=-0.00500344;	else
if(i<=116)error_size=-0.00491003;	else
if(i<=124)error_size=-0.00466306;	else
if(i<=132)error_size=-0.00459613;	else
if(i<=140)error_size=-0.0043181;	else
if(i<=148)error_size=-0.00457212;	else
if(i<=156)error_size=-0.00457077;	else
if(i<=164)error_size=-0.00526302;	else
if(i<=172)error_size=-0.00565866;	else
if(i<=180)error_size=-0.00671388;	else
if(i<=188)error_size=-0.00909996;	else
if(i<=196)error_size=-0.0101484;	else
if(i<=204)error_size=-0.0105862;	else
if(i<=212)error_size=-0.0111868;	else
if(i<=220)error_size=-0.0107891;	else
if(i<=228)error_size=-0.00767274;	else
if(i<=236)error_size=-0.00342603;	else
if(i<=244)error_size=0.00285352;	else
if(i<=252)error_size=0.00552367;	else
if(i<=260)error_size=0.00473453;	else{cout<<"Same size";}

 beamspec_bg_down2->Fill(i,error_size);

}


//for(Int_t i=1;i<=220;i++){
for(Int_t i=1;i<=256;i++){

if(i<=4)error_size=-0.00190277;	else
if(i<=16)error_size=-0.00210895;	else
if(i<=28)error_size=-0.00235467;	else
if(i<=40)error_size=-0.00240303;	else
if(i<=52)error_size=-0.00256453;	else
if(i<=64)error_size=-0.00265161;	else
if(i<=76)error_size=-0.00281178;	else
if(i<=88)error_size=-0.00292928;	else
if(i<=100)error_size=-0.00308231;	else
if(i<=112)error_size=-0.0031653;	else
if(i<=124)error_size=-0.00351855;	else
if(i<=136)error_size=-0.00348562;	else
if(i<=148)error_size=-0.00363181;	else
if(i<=160)error_size=-0.0038753;	else
if(i<=172)error_size=-0.00390835;	else
if(i<=184)error_size=-0.00420119;	else
if(i<=196)error_size=-0.00438232;	else
if(i<=208)error_size=-0.00466582;	else
if(i<=220)error_size=-0.00484375;	else
if(i<=232)error_size=-0.00532534;	else
if(i<=244)error_size=-0.00558795;	else
if(i<=256)error_size=-0.00539484;	else{cout<<"Same size";}


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

//for(Int_t i=1;i<=220;i++){
for(Int_t i=1;i<=256;i++){


if(i<=4)error_size=0.00203447;	else
if(i<=16)error_size=0.00225491;	else
if(i<=28)error_size=0.00251763;	else
if(i<=40)error_size=0.00256933;	else
if(i<=52)error_size=0.00274201;	else
if(i<=64)error_size=0.00283511;	else
if(i<=76)error_size=0.00300636;	else
if(i<=88)error_size=0.00313199;	else
if(i<=100)error_size=0.0032956;	else
if(i<=112)error_size=0.00338433;	else
if(i<=124)error_size=0.00376202;	else
if(i<=136)error_size=0.00372682;	else
if(i<=148)error_size=0.00388312;	else
if(i<=160)error_size=0.00414346;	else
if(i<=172)error_size=0.00417878;	else
if(i<=184)error_size=0.00449189;	else
if(i<=196)error_size=0.00468555;	else
if(i<=208)error_size=0.00498865;	else
if(i<=220)error_size=0.0051789;	else
if(i<=232)error_size=0.00569381;	else
if(i<=244)error_size=0.00597457;	else
if(i<=256)error_size=0.00576811;	else{cout<<"Same size";}


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
