#ifndef WIMP_FUNCTIONS_h
#define WIMP_FUNCTIONS_h

#include <iostream>
#include <cstdio>
#include <TMath.h>
#include <TSpline.h>
#include <TH2.h>

#ifndef FUNCTIONS_h
//#include "functions.h"
#endif
#include "Functions.C"
using namespace std;

// ##################################################################
// DECLARATIONS
// ##################################################################

int LoadWIMPParameters(FILE* f);
double GetWIMP_PolFactor(double kappa_eRpL, double kappa_eRpR,double kappa_eLpL,
			       double kappa_eLpR,double Pe, double Pp);
//double DiffWIMPCrossSection(double ecms, double E, double theta);
//double CoreDiffWIMPCrossSection(double ecms, double E, double theta);
double GetSignalWeight(double ecms, double E, double theta, double XSec_bg);
double GetCoreSignalWeight(double ecms, double E, double theta, double XSec_bg);
double TotalWIMPXSec(double Emin, double Emax, double PTCut, double coscut);
double TotalCoreWIMPXSec(double Emin, double Emax, double PTCut, double coscut);

// ##################################################################
//  WIMP PARAMETERS
// ##################################################################

double _mass;
double _alpha_em;
double _BR;
double _sigma_an;
double _annihilator;
double _spin;
double _kappa_eRpL;
double _kappa_eRpR;
double _kappa_eLpL;
double _kappa_eLpR;
double _lambda;


double _BR_eff; 
double _WIMP_PolFactor;




TSpline3* spline_eLpR;
TSpline3* spline_eRpL;


// ##################################################################
// DEFINITIONS
// ##################################################################


int LoadWIMPParameters(FILE* f){

 char thisParName[16];
 float thisValue;

 while (fscanf (f, "%s %f ", thisParName, &thisValue) != EOF) {
   // JUST PRINTOUT
   // printf ("%s %.3f\n",thisParName,thisValue);
   
//   if (!memcmp (thisParName, "wimpMass", strlen(thisParName)))
//     _mass = thisValue;
   if (!memcmp (thisParName, "alpha_em", strlen(thisParName)))
     _alpha_em = thisValue;
//   if (!memcmp (thisParName, "sigma_an", strlen(thisParName)))
//     _sigma_an = thisValue;
//   if (!memcmp (thisParName, "wimpSpin", strlen(thisParName)))
//     _spin = thisValue;
//   if (!memcmp (thisParName, "Annihilator", strlen(thisParName)))
//     _annihilator = thisValue;
//   if (!memcmp (thisParName, "BR_ep", strlen(thisParName)))
//     _BR = thisValue;
//   if (!memcmp (thisParName, "kappa_eRpL", strlen(thisParName)))
//     _kappa_eRpL = thisValue;
//   if (!memcmp (thisParName, "kappa_eRpR", strlen(thisParName)))
//     _kappa_eRpR = thisValue;
//   if (!memcmp (thisParName, "kappa_eLpL", strlen(thisParName)))
//     _kappa_eLpL = thisValue;
//   if (!memcmp (thisParName, "kappa_eLpR", strlen(thisParName)))
//      _kappa_eLpR = thisValue;
 }
 return 0;
}



// #######################################################################

double GetWIMP_PolFactor(double kappa_eRpL, double kappa_eRpR, double kappa_eLpL, double kappa_eLpR,double Pe, double Pp){
  
  double Polfactor = (0.25*(1.0+Pe) * ((1.0-Pp)*kappa_eRpL + (1.0+Pp)*kappa_eRpR)+
		      0.25*(1.0-Pe) * ((1.0-Pp)*kappa_eLpL + (1.0+Pp)*kappa_eLpR));
  // printf("WIMP polarisation factor:  %.3f\n",Polfactor);
 return Polfactor;
}


// #################################################################

/*
double DiffWIMPCrossSection(double ecms, double E, double theta){
  const double PI = TMath::Pi();
  double diffXSec(0.0);

  double E_max = ((0.5*ecms)*(0.5*ecms)-(_mass*_mass))/(0.5*ecms);
  if (E > E_max ){
    diffXSec = 0.0;
    return diffXSec;
  }

 
  double x = 2.0*E/ecms;
  diffXSec = (_alpha_em * _BR_eff*_sigma_an/(16.0*PI))*
    ((1.0+(1.0-x)*(1.0-x))/x)*1.0/(TMath::Sin(theta)*TMath::Sin(theta))*
    (pow(2.0,2.0*_annihilator)*(2.0*_spin+1.0)*(2.0*_spin+1.0))*
    pow((1.0-(4.0*_mass*_mass/((1.0-x)*ecms*ecms))),(0.5+_annihilator));
  return diffXSec;
}
*/

// #################################################################


/*
double WIMPdsigmadx(double ecms, double E, double cos_cut){
  const double PI = TMath::Pi();
  double diffXSec(0.0);

  double E_max = ((0.5*ecms)*(0.5*ecms)-(_mass*_mass))/(0.5*ecms);
  if (E > E_max){
    diffXSec = 0.0;
    return diffXSec;
  }

  double theta = TMath::ACos(cos_cut);
  double theta1 = theta;
  double theta2 = PI - theta;
  double integration_theta =  TMath::Log(TMath::Tan(theta2/2.0)) - TMath::Log(TMath::Tan(theta1/2.0 ));


  double x = 2.0*E/ecms;
  diffXSec = (_alpha_em * _BR_eff*_sigma_an/(16.0*PI))*
    ((1.0+(1.0-x)*(1.0-x))/x)*integration_theta*
    (pow(2.0,2.0*_annihilator)*(2.0*_spin+1.0)*(2.0*_spin+1.0))*
    pow((1.0-(4.0*_mass*_mass/((1.0-x)*ecms*ecms))),(0.5+_annihilator));
  return diffXSec;
}
*/
// #################################################################
/*
TH1D* DsigmadE_WIMP(double ecms, double coscut){
  
  TH1D* h = new TH1D("DsigmadE_WIMP","DsigmadE_WIMP;E[GeV];d#sigma /dE [fb]",300,0.0,300.0);
  double E;

  for (int i(1); i < 301; i++){
    E = h->GetXaxis()->GetBinCenter(i);    
    double xsec = WIMPdsigmadx(ecms, E,coscut);
    xsec *=  1000*2/500.0; // conversion pb->fb and x->E
    h->SetBinContent(i,xsec);
  }
  return h;
}
*/
// #################################################################
/*
void DsigmadE_WIMP(TH1D* h, double ecms, double coscut){
  
  double E;

  for (int i(1); i < 301; i++){
    E = h->GetXaxis()->GetBinCenter(i);    
    double xsec = WIMPdsigmadx(ecms, E,coscut);
    xsec *=  1000*2/500.0; // conversion pb->fb and x->E
    h->SetBinContent(i,xsec);
  }
  return;
}
*/

// #################################################################

/*
double CoreDiffWIMPCrossSection(double ecms, double E, double theta){ // has to be multiplied with kappa_eff and (2*S+1)^2
  const double PI = TMath::Pi();
  double diffXSec(0.0);

  double E_max = ((0.5*ecms)*(0.5*ecms)-(_mass*_mass))/(0.5*ecms);
  if (E > E_max){   // Only kinematic cut?
    diffXSec = 0.0;
    return diffXSec;
  }

 
  double x = 2.0*E/ecms;
  diffXSec = (_alpha_em * _sigma_an/(16.0*PI))*
    ((1.0+(1.0-x)*(1.0-x))/x)*1.0/(TMath::Sin(theta)*TMath::Sin(theta))*
    (pow(2.0,2.0*_annihilator))*
    pow((1.0-(4.0*_mass*_mass/((1.0-x)*ecms*ecms))),(0.5+_annihilator));
     
  return diffXSec; 
}
*/
// #################################################################

/*
double GetSignalWeight(double ecms, double E, double theta, double XSec_bg){

  double weight(0.0);

  double wimp_xsec = DiffWIMPCrossSection(ecms,E,theta);
  weight = wimp_xsec/XSec_bg; 


  return weight;
}
*/
// #################################################################
/*
double GetCoreSignalWeight(double ecms, double E, double theta, double XSec_bg){

  double weight(0.0);

  double wimp_xsec = CoreDiffWIMPCrossSection(ecms,E,theta);
  weight = wimp_xsec/XSec_bg; 


  return weight;
}
*/
// #################################################################
/*
double TotalWIMPXSec(double Emin, double Emax, double PTCut, double coscut){
  double XSec(.0);

  double dxs(0.0);

  double x; 
  double cos; 
           
  double E;
  double thet;
  double pt;

  TH2D* xsec = new TH2D("xsec","XSec;x;cos(#Theta)",1000,0.0,1.0,1000,-1.0,1.0);
  for (int i(1); i < 1001; i++){
    x = xsec->GetXaxis()->GetBinCenter(i);    
    //    E = run_CMSEnergy*x/2.0;
    E = CMSEnergy*x/2.0;
    if (E < Emin || E > Emax) continue;

    for (int j(1); j < 1001; j++){
      
      cos = xsec->GetYaxis()->GetBinCenter(j);
      thet = TMath::ACos(cos);
      pt = E * TMath::Sin(thet);
      if (TMath::Abs(cos) > coscut || pt < PTCut) continue;


      dxs = DiffWIMPCrossSection(CMSEnergy,E,thet);
      // dxs = DiffWIMPCrossSection(run_CMSEnergy,E,thet);
      xsec->SetBinContent(i,j,dxs);
    }
  }
  XSec = xsec->Integral("WIDTH");
  delete xsec;
  return XSec;
}
*/

// #################################################################
/*
double TotalCoreWIMPXSec(double Emin, double Emax, double PTCut, double coscut){
  double XSec(.0);

  double dxs(0.0);

  double x; 
  double cos; 
           
  double E;
  double thet;
  double pt;

  TH2D* xsec = new TH2D("xsec","XSec;x;cos(#Theta)",1000,0.0,1.0,1000,-1.0,1.0);
  for (int i(1); i < 1001; i++){
    x = xsec->GetXaxis()->GetBinCenter(i);    
    // E = run_CMSEnergy*x/2.0;
    E = CMSEnergy*x/2.0;
    if (E < Emin || E > Emax) continue;

    for (int j(1); j < 1001; j++){
      
      cos = xsec->GetYaxis()->GetBinCenter(j);
      thet = TMath::ACos(cos);
      pt = E * TMath::Sin(thet);
      if (TMath::Abs(cos) > coscut || pt < PTCut) continue;

      dxs = CoreDiffWIMPCrossSection(CMSEnergy,E,thet);
      //      dxs = CoreDiffWIMPCrossSection(run_CMSEnergy,E,thet);
      xsec->SetBinContent(i,j,dxs);
    }
  }
  XSec = xsec->Integral("WIDTH");
  delete xsec;
  return XSec;
}
*/

double FitShape(double* e,double* par){
  
  // const double PI = TMath::Pi();
  double fitval;

  // par[0]: norm, par[1]: annihilator, par[2]: mass, par[3]: ecms

  double x = e[0]*2.0/par[3];
  if (( 4.0*par[2]*par[2]/((1.0-x)*par[3]*par[3]) ) > 1.0) {
    fitval = 0.0;
    return fitval;
  }

  fitval = par[0]* 
    //(_alpha_em * _sigma_an/(16.0*PI))*
    ((1.0+(1.0-x)*(1.0-x))/x)*
    (pow(2.0,2.0*par[1]))*
    pow((1.0-(4.0*par[2]*par[2]/((1.0-x)*par[3]*par[3]))),(0.5+par[1]));
  return fitval;
}

double fitcont(double* e,double* par){

  double fitval;
  fitval = par[0] * (PolarisationWeights[0] * spline_eLpR->Eval(e[0]) + PolarisationWeights[1] * spline_eRpL->Eval(e[0]));
  return fitval;
}


double fitfunc(double* e,double* par){
  double fitval;
  fitval = FitShape(e,par) + fitcont(e,&par[4]);
  return fitval;
}


// Calculation cross secrion using diff operrators 
// #################################################################

double WIMPdsigmadx_new(double ecms_star, double E, double cos_cut, int _operator){
  const double PI = TMath::Pi();
  double diffXSec(0.0);
  double ecms_star_bin_low = ecms_star-0.5; // lower bin edge for energy cutoff -> conservative (some allowed WIMP events get weight 0)

  double E_max = ((0.5*ecms_star_bin_low)*(0.5*ecms_star_bin_low)-(_mass*_mass))/(0.5*ecms_star_bin_low);
  
  
  if ( E > E_max ){
    diffXSec = 0.0;
    return diffXSec;

  }

 double theta = TMath::ACos(cos_cut);
   double theta1 = theta;
   double theta2 = PI - theta;
  double integration_theta2 =  TMath::Cos(theta1)-TMath::Cos(theta2);
  double integration_theta1 =  TMath::Log(TMath::Tan(theta2/2.0)) - TMath::Log(TMath::Tan(theta1/2.0 ));
//  if(_mass==100)
//  cout<<"Integral Theta1 = "<<integration_theta1<<"Integral Theta2 = "<<integration_theta2<<endl;
  
  double z = 2.0*E/ecms_star;
  double mu=_mass/ecms_star;
  

   if (_operator==0){
   //Vector Integration theta
  diffXSec = (_alpha_em/(12.0*PI*PI))*(ecms_star*ecms_star/pow(_lambda,4))*
	      (1/z)*sqrt((1-z-4*mu*mu)/(1-z))*
	      (1-z+2*mu*mu)*
	      (4*(1-z)*integration_theta1+z*z*
	      (2*integration_theta1-integration_theta2));
	   }

     if (_operator==1){
  //Scalar, s-chanel
         diffXSec = (_alpha_em/(8.0*PI*PI))*(ecms_star*ecms_star/pow(_lambda,4))*
  	     (1/z)*integration_theta1*
	     pow(((1-z-4*mu*mu)/(1-z)),1.5)*
	     (1-z)*(2*(1-z)+z*z); 	     
   	     }

	if (_operator==2){	     
  //Axial-vector	     
      diffXSec = (_alpha_em/(12.0*PI*PI))*(ecms_star*ecms_star/pow(_lambda,4))*
  	      (1/z)*pow(((1-z-4*mu*mu)/(1-z)),1.5)*(1-z)*
	       (4*(1-z)*integration_theta1+z*z*
	      (2*integration_theta1-integration_theta2));
	     }
     		

  return diffXSec;
}

double WIMPdsigmadx_new2(double ecms_star, double E, double cos_cut, int _operator){
  const double PI = TMath::Pi();
  double diffXSec(0.0);
  double ecms_star_bin_low = ecms_star-0.5; // lower bin edge for energy cutoff -> conservative (some allowed WIMP events get weight 0)

  double E_max = ((0.5*ecms_star_bin_low)*(0.5*ecms_star_bin_low)-(_mass*_mass))/(0.5*ecms_star_bin_low);
  
  
  if ( E > E_max ){
    diffXSec = 0.0;
    return diffXSec;

  }

 double theta = TMath::ACos(cos_cut);
   double theta1 = theta;
   double theta2 = PI - theta;
  double integration_theta2 =  TMath::Cos(theta1)-TMath::Cos(theta2);
  double integration_theta1 =  TMath::Log(TMath::Tan(theta2/2.0)) - TMath::Log(TMath::Tan(theta1/2.0 ));
//  if(_mass==100)
//  cout<<"Integral Theta1 = "<<integration_theta1<<"Integral Theta2 = "<<integration_theta2<<endl;
  
  double z = 2.0*E/ecms_star;
  double mu=_mass/ecms_star;
  

   if (_operator==0){
   //Vector Integration theta
  diffXSec = (_alpha_em/(12.0*PI*PI))*(ecms_star*ecms_star/pow(_lambda,4))*
	      (1/z)*sqrt((1-z-4*mu*mu)/(1-z))*
	      (1-z+2*mu*mu)*
	      (4*(1-z)*integration_theta1+z*z*
	      (2*integration_theta1-integration_theta2));
	   }

     if (_operator==1){
  //Scalar, s-chanel
         diffXSec = (_alpha_em/(8.0*PI*PI))*(ecms_star*ecms_star/pow(_lambda,4))*
  	     (1/z)*integration_theta1*
	     pow(((1-z-4*mu*mu)/(1-z)),1.5)*
	     (1-z)*(2*(1-z)+z*z); 	     
   	     }

	if (_operator==2){	     
  //Axial-vector	     
      diffXSec = (_alpha_em/(12.0*PI*PI))*(ecms_star*ecms_star/pow(_lambda,4))*
  	      (1/z)*pow(((1-z-4*mu*mu)/(1-z)),1.5)*(1-z)*
	       (4*(1-z)*integration_theta1+z*z*
	      (2*integration_theta1-integration_theta2));
	     }
     		

  return diffXSec;
}

// #################################################################

void DsigmadE_WIMP_new(TH2D* h, double ecms, double coscut7, int _operator, double ptmin, double ethresh){
  
  double E,ecms_star,counter,coscut;
  
  for (int i(1); i < 251; i++){
    E = h->GetXaxis()->GetBinCenter(i);
    if (E <= ptmin){
    		coscut=.1;
    }
    if (E > ethresh && E > ptmin){
    		coscut=coscut7;
    }
    if (E < ethresh && E > ptmin){
#if 0
    		coscut=sqrt(E**2-ptmin**2)/E;
#else
    		coscut=sqrt(E*E-ptmin*ptmin)/E;
#endif
    }
    //cout << "Energy " << i << " cos_cut " << coscut << endl;
  for (int j(1); j < 503; j++){ 
    ecms_star = h->GetYaxis()->GetBinCenter(j);
    double xsec = WIMPdsigmadx_new(ecms_star, E, coscut, _operator);
    xsec *=  2/500.0; // conversion z->E,  
    xsec *= 0.38938*pow(10.0,12.0); // conversion 1/Gev^2 to fb; 
      if(_mass==1&&i>0&&i<211){
   // cout<<"Cross section = "<<xsec<<" Value mass = "<<_mass<<" Spin = "<<_spin<<" Lambda = "<<_lambda<<" Photon Energy = "<<E<<endl;
    counter+=xsec;
//    if(i==210)
   // cout<<"Counter = "<<counter<<" E = "<<E<<endl;
    }  
    
    h->SetBinContent(i,j,xsec);
  }
  }
  return;
}


void DsigmadE_WIMP_new2(TH2D* h, double ecms, double coscut7, int _operator, double ptmin, double ethresh){
  
  double E,ecms_star,counter,coscut;
  
  for (int i(1); i < 251; i++){
    E = h->GetXaxis()->GetBinCenter(i);
    if (E <= ptmin){
    		coscut=.1;
    }
    if (E > ethresh && E > ptmin){
    		coscut=coscut7;
    }
    if (E < ethresh && E > ptmin){
#if 0
    		coscut=sqrt(E**2-ptmin**2)/E;
#else
    		coscut=sqrt(E*E-ptmin*ptmin)/E;
#endif
    }
    //cout << "Energy " << i << " cos_cut " << coscut << endl;
  for (int j(1); j < 503; j++){ 
    ecms_star = h->GetYaxis()->GetBinCenter(j);
    double xsec = WIMPdsigmadx_new2(ecms_star, E, coscut, _operator);
    xsec *=  2/500.0; // conversion z->E,  
    xsec *= 0.38938*pow(10.0,12.0); // conversion 1/Gev^2 to fb; 
      if(_mass==1&&i>0&&i<211){
   // cout<<"Cross section = "<<xsec<<" Value mass = "<<_mass<<" Spin = "<<_spin<<" Lambda = "<<_lambda<<" Photon Energy = "<<E<<endl;
    counter+=xsec;
//    if(i==210)
   // cout<<"Counter = "<<counter<<" E = "<<E<<endl;
    }  
    
    h->SetBinContent(i,j,xsec);
  }
  }
  return;
}

// #######################################################################

double Sigma_PolFactor(double sigma_eRpL, double sigma_eRpR, double sigma_eLpL, double sigma_eLpR,double Pe, double Pp){
  
  double Polfactor = (0.25*(1.0+Pe) * ((1.0+Pp)*sigma_eRpR + (1.0-Pp)*sigma_eRpL)+
		      0.25*(1.0-Pe) * ((1.0+Pp)*sigma_eLpR + (1.0-Pp)*sigma_eLpL));
  // printf("WIMP polarisation factor:  %.3f\n",Polfactor); 
 return Polfactor;
}


//double FitShape1(double* e,double* par){
//  
//  const double PI = TMath::Pi();
//  double fitval;
//
//  // par[0]: norm, par[1]: annihilator, par[2]: mass, par[3]: ecms
//
//  char str[256];
//
//  sprintf(str,"((1.0+(1.0-x)*(1.0-x))/x)* %.10f *   TMath::Power((1.0-(4.0*%.10f/((1.0-x)*%.10f))),(0.5+%.10f))",(pow(2.0,2.0*par[1])),par[2]*par[2],par[3]*par[3],par[1]);
//
//  TF1* f = new TF1("f1",str);
//
//   double integral = f->Integral(par[5]*2.0/par[3],par[6]*2.0/par[3]);
//   cout << "INT: "<< integral << endl;
//   par[0] = par[4]/integral;
//
//  double x = e[0]*2.0/par[3];
//  if (( 4.0*par[2]*par[2]/((1.0-x)*par[3]*par[3]) ) > 1.0) {
//    fitval = 0.0;
//    return fitval;
//  }
//
//  fitval = par[0]* 
//    //(_alpha_em * _sigma_an/(16.0*PI))*
//    ((1.0+(1.0-x)*(1.0-x))/x)*
//    (pow(2.0,2.0*par[1]))*
//    pow((1.0-(4.0*par[2]*par[2]/((1.0-x)*par[3]*par[3]))),(0.5+par[1]));
//
//
//  return fitval;
//}

#endif
