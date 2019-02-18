#include <TTree.h>
#include "GlobalVariables.C"


int CreatePolarisationWeights(double Pe, double Pp);
double GetEventWeight(double lumi, double Pe, double Pp); // = polarisationweight * lumifactor
double GetEventWeight(double lumi, double generated_lumi, double Pe, double Pp);
double GetPolarisationWeight(double Pe, double Pp);

int GetHighEnergyReconstructedPhoton();             // Return index of reco photon with highest energy, default = -1 

int GetHighEnergyProcessedPhoton();                 // Return index of processed photon with highest energy, default = -1 
int GetHighEnergyProcessedPhoton(int& nPhotons);    // Return index and number of processed photons in event
int GetHighEnergyProcessedPhoton(int& nPhotons, double& E_active, double& P_T_active);// returns sum of energy and PT of all other
                                                                                          // particles

int GetHighEnergyCalibratedPhoton(int& nPhotons);    // Return index and number of calibrated photons in event
// --------------------------------------------------------------------------------

int GetHighEnergyReconstructedPhoton(){
  int index = -1;
  double energy = 0.0;

  for ( int j(0); j < nRecoParticles; j++ ){
    if ( Reco_type[j] == 22 ){
      if ( Reco_energy[j] > energy){
	energy =  Reco_energy[j];
	index = j;
      }
    }
  }
  return index;
}

// #############################################################

int GetHighEnergyProcessedPhoton(){
  int index = -1;
  double energy = 0.0;

  for ( int j(0); j < nProcessedRecos; j++ ){
    if ( ProcessedReco_type[j] == 22 ){
      if ( ProcessedReco_energy[j] > energy){
	energy =  ProcessedReco_energy[j];
	index = j;
      }
    }
  }
  return index;
}


// #############################################################

int GetHighEnergyProcessedPhoton(int& nPhotons){
  int index = -1;
  double energy = 0.0;

  for ( int j(0); j < nProcessedRecos; j++ ){
    if ( ProcessedReco_type[j] == 22 ){
      nPhotons++;
      if ( ProcessedReco_energy[j] > energy){
	energy =  ProcessedReco_energy[j];
	index = j;
      }
    }
  }
  return index;
}


// #############################################################

int GetHighEnergyProcessedPhoton(int& nPhotons, double& E_active, double& P_T_active){
  int index = -1;
  double energy = 0.0;

  E_active = 0.0;
  P_T_active = 0.0;

  for ( int j(0); j < nProcessedRecos; j++ ){
    if ( ProcessedReco_type[j] == 22 ){
      nPhotons++;
      if ( ProcessedReco_energy[j] > energy){
	energy =  ProcessedReco_energy[j];
	index = j;
      }
    }
    else{
      E_active += ProcessedReco_energy[j];
      P_T_active += ProcessedReco_absP[j]*sin(acos(ProcessedReco_cosTheta[j]));
    }
  }
  return index;
}


int GetHighEnergyCalibratedPhoton(int& nPhotons){
  int index = -1;
  double energy = 0.0;
  
  for ( int j(0); j < nCalibratedRecos; j++ ){
    if ( CalibratedReco_type[j] == 22 ){
      nPhotons++;
      if ( CalibratedReco_energy[j] > energy){
	energy =  CalibratedReco_energy[j];
	index = j;
      }
    }
  }
  return index;
}


int GetHighEnergyCalibratedPhotonWOBeamCal(int& nPhotons){
  int index = -1;
  double energy = 0.0;
  
  for ( int j(0); j < nCalibratedRecos; j++ ){
    if ( CalibratedReco_type[j] == 22 && !CalibratedReco_isBCal[j]){
      nPhotons++;
      if ( CalibratedReco_energy[j] > energy){
	energy =  CalibratedReco_energy[j];
	index = j;
      }
    }
  }
  return index;
}

// ################################################################################
// ########### Weights for Polarisation Mixing   ##################################
// ################################################################################

//  Configurations (P_e/P_p)       (-1.0/1.0) | (1.0/-1.0) | (1.0/1.0) | (-1.0/-1.0)
double PolarisationWeights[4] = {    0.25    ,   0.25     ,    0.25   ,    0.25   };  // (0.0,0.0)


// --------------------------------------------------------------------------------

//int CreatePolarisationWeights(double Pe, double Pp){
//
//
//  PolarisationWeights[0] = ((1-Pe)*(1+Pp))/4.0;
//  PolarisationWeights[1] = ((1+Pe)*(1-Pp))/4.0;
//  PolarisationWeights[2] = ((1+Pe)*(1+Pp))/4.0;
//  PolarisationWeights[3] = ((1-Pe)*(1-Pp))/4.0;
//
//  //printf("Polarisation Weights: (Pe/Pp):    (-1/1)  (1/-1)  (1/1)  (-1/-1)\n");
//  //printf("                                  %.3f   %.3f   %.3f  %.3f\n\n",PolarisationWeights[0],PolarisationWeights[1],PolarisationWeights[2],PolarisationWeights[3]);
//  return 0;
//}

int CreatePolarisationWeights(double Pe, double Pp){

  // ELECTRONS
  double e_Np_Nm = (1.0 + Pe) / (1.0 - Pe);
  double e_FracNp = 1.0 / (1.0 + 1/e_Np_Nm);
  double e_FracNm = 1.0 / (1.0 + e_Np_Nm);


  // POSITRONS
  double p_Np_Nm = (1.0 + Pp) / (1.0 - Pp);
  double p_FracNp = 1.0 / (1.0 + 1/p_Np_Nm);
  double p_FracNm = 1.0 / (1.0 + p_Np_Nm);

  PolarisationWeights[0] = (e_FracNm * p_FracNp);
  PolarisationWeights[1] = (e_FracNp * p_FracNm);
  PolarisationWeights[2] = (e_FracNp * p_FracNp);
  PolarisationWeights[3] = (e_FracNm * p_FracNm);

  //printf("Polarisation Weights: (%.1f/%.1f):    (-1/1)  (1/-1)  (1/1)  (-1/-1)\n",Pe,Pp);
  //printf("                                       %.3f   %.3f   %.3f  %.3f\n\n",PolarisationWeights[0],PolarisationWeights[1],PolarisationWeights[2],PolarisationWeights[3]);
  return 0;
}
// --------------------------------------------------------------------------------

double GetEventWeight(double lumi, double Pe, double Pp){

  int index = -1;  //index of Pol configuration in file

  if (Pe == -1.0 && Pp ==  1.0) index = 0;
  if (Pe ==  1.0 && Pp == -1.0) index = 1;
  if (Pe ==  1.0 && Pp ==  1.0) index = 2; 
  if (Pe == -1.0 && Pp == -1.0) index = 3; 
  //  else{printf("GetEventWeight: Wrong Input!\n");}
  double weight = (lumi/MCLumi_Run) * PolarisationWeights[index];

  return weight;
}


// --------------------------------------------------------------------------------

double GetEventWeight(double lumi,double generated_lumi, double Pe, double Pp){

  int index = -1;  //index of Pol configuration in file
//  cout <<" Pe = " << Pe<<" | Pp = "<< Pp<< endl;

  if (Pe == -1.0 && Pp ==  1.0) index = 0; 
  if (Pe ==  1.0 && Pp == -1.0) index = 1;
  if (Pe ==  1.0 && Pp ==  1.0) index = 2; 
  if (Pe == -1.0 && Pp == -1.0) index = 3; 

  //else {printf("GetEventWeight: Wrong Input!\n");}
  double weight = (lumi/generated_lumi) * PolarisationWeights[index];
  //     cout <<" PolWeight = " <<PolarisationWeights[index]<<" Pe = " << Pe<<" | Pp = "<< Pp<< endl;
  return weight;
}


// --------------------------------------------------------------------------------

double GetPolarisationWeight(double Pe, double Pp){

  int index = -1;  //index of Pol configuration in file

  if (Pe == -1.0 && Pp ==  1.0) index = 0;
  if (Pe ==  1.0 && Pp == -1.0) index = 1;
  if (Pe ==  1.0 && Pp ==  1.0) index = 2;
  if (Pe == -1.0 && Pp == -1.0) index = 3;

  double weight = PolarisationWeights[index];

  return weight;
}




// #################### Geometry ###################################################

//VTX, Single layer configuration		

//double vtx_cosTheta[5] = {0.9724,0.9790,0.9589,0.9335,0.9015};
//double vtx_X0 = 0.11;

//VTX, Double layer configuration		

double vtx_cosTheta[6] = {0.9688,0.9609,0.9589,0.9546,0.9071,0.9015};
double vtx_X0 = 0.13;

//VTX support strcture additional

double vtxsupp_cosTheta = 0.9589;
double  vtxsupp_X0 =  0.7;

//SIT 	

double sit_cosTheta[2] = {0.9137,0.9019};
double sit_X0 =  0.65;

//FTD

double ftd_cosTheta[7][2] = {{0.985,0.802},{0.991,0.914},{0.994,0.902},{0.995,0.959},{0.995,0.978},{0.996,0.986},{0.996,0.991}};
double ftd_X0[2] = {0.25,0.65};

// BeamPipe

double beampipe_cosTheta[2][2] = {{0.0,0.9929},{0.9929,0.9964}};
double beampipe_X0 = 0.5;

//SET  2 layers with

double set_cosTheta = 0.789;
double set_X0 = 0.65;


//ETD 3 discs
double etd_cosTheta[2] = {0.985,0.800};
double etd_X0 =  1.1;

//TPC inner and outer

double fieldcage_cosTheta[2] = {0.985,0.791};
double fieldcage_X0[2] = {0.8,2.5};

double gas_cosTheta = 0.985;
double gas_X0 = 0.65;

double endcap_cosTheta[2] = {0.985,0.791};
double endcap_X0 = 12.5;

