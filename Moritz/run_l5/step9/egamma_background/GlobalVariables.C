#include <TTree.h>
// #include "Functions.C"

int SetGlobalTreeBranches(TTree* tree);
int SetXSecTreeBranches(TTree* tree);
int SetTreeBranches(TTree* tree);
int SetPreProcTreeBranches(TTree* tree);
int SetCalibratedTreeBranches(TTree* tree);
int SetSelPhotonTreeBranches(TTree* tree);
int SetSelectionEfficienciesTreeBranches(TTree* tree);
int SetScalingFactorsTreeBranches(TTree* tree);
int SetBcalTreeBranches(TTree* tree);

int LoadGlobalTree(TTree* tree);
int LoadTree(TTree* tree);
int LoadPreProcTree(TTree* tree);
int LoadCalibratedTree(TTree* tree);
int LoadSelPhotonTree(TTree* tree);
int LoadXSecTree(TTree* tree);
int LoadSelectionEfficienciesTree(TTree* tree);
int LoadScalingFactorsTree(TTree* tree);
int LoadBcalTree(TTree* tree);

//######### Global Variables, Leave names ###########################

//---------- Event, Run and Physics Process Properties ---------
int RunID;
int NumberOfEvents;
int NumberOfEventsInRun;
int NumberOfEventsInFile;
char Process[20];
double CrossSection;
float MCLumi;
float crosss;
double MCLumi_Run;
double CMSEnergy;
double EventCMSEnergy;
double CollisionEnergy;
float electron_polarisation, positron_polarisation;

double PolWeight;
double EventWeight;


int EventID;
int nMCParticles;
int nFirstSimMCParticles;
int nRecoParticles;
int nTracks;
int nClusters;
int nProcessedRecos;
int nCalibratedRecos;
int nSelPhotons;
int nBcalParticles;

#if 1 //RY added
double P_e, P_p;
#endif

//------------------ MCParticle properties on generator level --------------------

int MC_id[1000];
int MC_isReal[1000];
int MC_genStatus[1000];
int MC_isCreatedInSim[1000];
int MC_isBackScatter[1000];
int MC_vertexNotParentEndpoint[1000];
int MC_isDecayedInTracker[1000];
int MC_isDecayedInCalo[1000];
int MC_hasLeftDet[1000];
int MC_isStopped[1000];

int MC_type[1000];
double MC_px[1000];
double MC_py[1000];
double MC_pz[1000];
double MC_energy[1000];
double MC_vertex_x[1000];
double MC_vertex_y[1000];
double MC_vertex_z[1000];
double MC_endpoint_x[1000];
double MC_endpoint_y[1000];
double MC_endpoint_z[1000];
double MC_mass[1000];
float MC_charge[1000];

double MC_absP[1000];
double MC_cosTheta[1000];
double MC_phi[1000];
    
//------------------ First MCParticle properties created by Detector simulation --------------------

int FirstSimMC_id[1000];
int FirstSimMC_ParentId[1000];
int FirstSimMC_isReal[1000];
int FirstSimMC_genStatus[1000];
int FirstSimMC_isCreatedInSim[1000];
int FirstSimMC_isBackScatter[1000];
int FirstSimMC_vertexNotParentEndpoint[1000];
int FirstSimMC_isDecayedInTracker[1000];
int FirstSimMC_isDecayedInCalo[1000];
int FirstSimMC_hasLeftDet[1000];
int FirstSimMC_isStopped[1000];


int FirstSimMC_type[1000];
double FirstSimMC_px[1000];
double FirstSimMC_py[1000];
double FirstSimMC_pz[1000];
double FirstSimMC_energy[1000];
double FirstSimMC_vertex_x[1000];
double FirstSimMC_vertex_y[1000];
double FirstSimMC_vertex_z[1000];
double FirstSimMC_endpoint_x[1000];
double FirstSimMC_endpoint_y[1000];
double FirstSimMC_endpoint_z[1000];
double FirstSimMC_mass[1000];
float FirstSimMC_charge[1000];

double FirstSimMC_absP[1000];
double FirstSimMC_cosTheta[1000];
double FirstSimMC_phi[1000];


//------------------ ReconstructedParticle properties --------------------

int Reco_id[1000];
int Reco_type[1000];
int Reco_isBCal[1000];
double Reco_px[1000];
double Reco_py[1000];
double Reco_pz[1000];
double Reco_energy[1000];
double Reco_mass[1000];
float Reco_charge[1000];
float Reco_position_x[1000];
float Reco_position_y[1000];
float Reco_position_z[1000];

double Reco_absP[1000];
double Reco_cosTheta[1000];
double Reco_phi[1000];

int RecoToMCId[1000];
int RecoToFirstSimParentId[1000];
float RelationWeight[1000];
int RecoToTrackId[1000];
int RecoToClusterId[1000];


float Reco_cov_pxpx[1000];
float Reco_cov_pypx[1000];
float Reco_cov_pypy[1000];
float Reco_cov_pzpx[1000];
float Reco_cov_pzpy[1000];
float Reco_cov_pzpz[1000];
float Reco_cov_Epx[1000];
float Reco_cov_Epy[1000];
float Reco_cov_Epz[1000];
float Reco_cov_EE[1000];


//------------------- Cluster properties ---------------------------------

int Cluster_id[1000];
int Cluster_type[1000];

float Cluster_energy[1000];

float Cluster_position_x[1000];
float Cluster_position_y[1000];
float Cluster_position_z[1000];

float Cluster_cov_xx[1000];
float Cluster_cov_yx[1000];
float Cluster_cov_yy[1000];
float Cluster_cov_zx[1000];
float Cluster_cov_zy[1000];
float Cluster_cov_zz[1000];

float Cluster_iTheta[1000];
float Cluster_iPhi[1000];

float Cluster_cov_tt[1000];
float Cluster_cov_pt[1000];
float Cluster_cov_pp[1000];

//------------------- Track properties -----------------------------------

int Track_id[1000];
int Track_type[1000];
float Track_d0[1000];
float Track_phi[1000];
float Track_omega[1000];
float Track_z0[1000];
float Track_tanlambda[1000];
float Track_refpoint_x[1000];
float Track_refpoint_y[1000];
float Track_refpoint_z[1000];
float Track_chi2[1000];
float Track_dedx[1000];
float Track_dedxerr[1000];
float Track_radiusInnerHit[1000];

float Track_cov_d0d0[1000];
float Track_cov_phid0[1000];
float Track_cov_phiphi[1000];
float Track_cov_omegad0[1000];
float Track_cov_omegaphi[1000];
float Track_cov_omegaomega[1000];
float Track_cov_z0d0[1000];
float Track_cov_z0phi[1000];
float Track_cov_z0omega[1000];
float Track_cov_z0z0[1000];
float Track_cov_tanlambdad0[1000];
float Track_cov_tanlambdaphi[1000];
float Track_cov_tanlambdaomega[1000];
float Track_cov_tanlambdaz0[1000];
float Track_cov_tanlambdatanlambda[1000];

// ------------ Processed Particles ----------------

int ProcessedReco_id[1000];
int ProcessedReco_type[1000];
int ProcessedReco_isBCal[1000];
double ProcessedReco_px[1000];
double ProcessedReco_py[1000];
double ProcessedReco_pz[1000];
double ProcessedReco_energy[1000];
double ProcessedReco_mass[1000];
float ProcessedReco_charge[1000];
float ProcessedReco_position_x[1000];
float ProcessedReco_position_y[1000];
float ProcessedReco_position_z[1000];

double ProcessedReco_absP[1000];
double ProcessedReco_cosTheta[1000];
double ProcessedReco_phi[1000];

int ProcessedToRecoId[1000];
int ProcessedRecoRelatedToId[1000];
float ProcessedRecoRelationWeight[1000];
int NumberOfMerged[1000];

// ------------ Calibrated Particles ----------------

int CalibratedReco_id[1000];
int CalibratedReco_type[1000];
int CalibratedReco_isBCal[1000];
double CalibratedReco_px[1000];
double CalibratedReco_py[1000];
double CalibratedReco_pz[1000];
double CalibratedReco_energy[1000];
double CalibratedReco_mass[1000];
float CalibratedReco_charge[1000];
float CalibratedReco_position_x[1000];
float CalibratedReco_position_y[1000];
float CalibratedReco_position_z[1000];

double CalibratedReco_absP[1000];
double CalibratedReco_cosTheta[1000];
double CalibratedReco_phi[1000];

int CalibratedToRecoId[1000];
int CalibratedRecoRelatedToId[1000];
float CalibratedRecoRelationWeight[1000];



// ------------ Selected Photons ---------------

float RCENE[1000];


// --------------- Bcal particles for e1e1 processes

double Bcal_px[1000];
double Bcal_py[1000];
double Bcal_pz[1000];
double Bcal_energy[1000];
double Bcal_mass[1000];
float Bcal_charge[1000];
float Bcal_efficiency[1000];
double Bcal_absP[1000];
double Bcal_cosTheta[1000];
double Bcal_phi[1000];
int BcalToMCId[1000];


// --- Background Cross Section -----------------


double XSec;

double s_prime;
double E_prime;
double Theta_prime;


// --- SelectionEfficiencyTree
    
double Entries_BeforeCuts;
double Entries_AfterKinCuts;
double Entries_AfterAllCuts;
double CrossSection_AfterKinCuts;
 
double Efficiency_KinCuts;
double Efficiency_RecCuts;
double Efficiency_AllCuts;
 

// --- Scalingfactors

double ScalingFactorp0p0;
double ScalingFactorp8p0;
double ScalingFactorp8m3;
double ScalingFactorp8m6;
double ScalingFactorm8p0;
double ScalingFactorm8p3;
double ScalingFactorm8p6;

double PolXSecp0p0;
double PolXSecp8p0;
double PolXSecp8m3;
double PolXSecp8m6;
double PolXSecm8p0;
double PolXSecm8p3;
double PolXSecm8p6;



// ###########  Set Tree Branches ###################

int SetXSecTreeBranches(TTree* tree){

  tree->Branch("XSec",&XSec,"XSec/D");
  tree->Branch("s_prime",&s_prime,"s_prime/D");
  tree->Branch("E_prime",&E_prime,"E_prime/D");
  tree->Branch("Theta_prime",&Theta_prime,"Theta_prime/D");

  return 0;
};


int SetGlobalTreeBranches(TTree* tree){

  tree->Branch("Process",&Process,"Process/C");
  tree->Branch("RunID",&RunID,"RunID/I");
  tree->Branch("NumberOfEventsInRun",&NumberOfEventsInRun,"NumberOfEventsInRun/I");
  tree->Branch("NumberOfEventsInFile",&NumberOfEventsInFile,"NumberOfEventsInFile/I");
  tree->Branch("CrossSection",&CrossSection,"CrossSection/D");
  tree->Branch("MCLumi",&MCLumi,"MCLumi/D");
  tree->Branch("CMSEnergy",&CMSEnergy,"CMSEnergy/D");
  tree->Branch("P_e",&P_e,"P_e/D");
  tree->Branch("P_p",&P_p,"P_p/D");

  return 0;
};

int SetTreeBranches(TTree* tree){

  tree->Branch("Process",&Process,"Process/C");
  tree->Branch("RunID",&RunID,"RunID/I");
  tree->Branch("NumberOfEvents",&NumberOfEvents,"NumberOfEvents/I");
  tree->Branch("CrossSection",&CrossSection,"CrossSection/D");
  tree->Branch("MCLumi_Run",&MCLumi_Run,"MCLumi_Run/D");
  tree->Branch("CMSEnergy",&CMSEnergy,"CMSEnergy/D");
  tree->Branch("EventCMSEnergy",&EventCMSEnergy,"EventCMSEnergy/D");
  tree->Branch("CollisionEnergy",&CollisionEnergy,"CollisionEnergy/D");
  tree->Branch("P_e",&P_e,"P_e/D");
  tree->Branch("P_p",&P_p,"P_p/D");
  tree->Branch("PolWeight",&PolWeight,"PolWeight/D");
  tree->Branch("EventWeight",&EventWeight,"EventWeight/D"); 
  tree->Branch("EventID",&EventID,"EventID/I");
  tree->Branch("nMCParticles",&nMCParticles,"nMCParticles/I");
  tree->Branch("nFirstSimMCParticles",&nFirstSimMCParticles,"nFirstSimMCParticles/I");
  tree->Branch("nRecoParticles",&nRecoParticles,"nRecoParticles/I");
  tree->Branch("nTracks",&nTracks,"nTracks/I");    
  tree->Branch("nClusters",&nClusters,"nClusters/I");    
  // MC

  tree->Branch("MC_id",&MC_id,"MC_id[nMCParticles]/I");
  tree->Branch("MC_isReal",&MC_isReal,"MC_isReal[nMCParticles]/I");
  tree->Branch("MC_genStatus",&MC_genStatus,"MC_genStatus[nMCParticles]/I");

  tree->Branch("MC_isCreatedInSim",&MC_isCreatedInSim,"MC_isCreatedInSim[nMCParticles]/I");
  tree->Branch("MC_isBackScatter",&MC_isBackScatter,"MC_isBackScatter[nMCParticles]/I");
  tree->Branch("MC_vertexNotParentEndpoint",&MC_vertexNotParentEndpoint,"MC_vertexNotParentEndpoint[nMCParticles]/I");
  tree->Branch("MC_isDecayedInTracker",&MC_isDecayedInTracker,"MC_isDecayedInTracker[nMCParticles]/I");
  tree->Branch("MC_isDecayedInCalo",&MC_isDecayedInCalo,"MC_isDecayedInCalo[nMCParticles]/I");
  tree->Branch("MC_hasLeftDet",&MC_hasLeftDet,"MC_hasLeftDet[nMCParticles]/I");
  tree->Branch("MC_isStopped",&MC_isStopped,"MC_isStopped[nMCParticles]/I");

  tree->Branch("MC_type",&MC_type,"MC_type[nMCParticles]/I");
  tree->Branch("MC_px",&MC_px,"MC_px[nMCParticles]/D");
  tree->Branch("MC_py",&MC_py,"MC_py[nMCParticles]/D");
  tree->Branch("MC_pz",&MC_pz,"MC_pz[nMCParticles]/D");
  tree->Branch("MC_energy",&MC_energy,"MC_energy[nMCParticles]/D");
  tree->Branch("MC_vertex_x",&MC_vertex_x,"MC_vertex_x[nMCParticles]/D");
  tree->Branch("MC_vertex_y",&MC_vertex_y,"MC_vertex_y[nMCParticles]/D");
  tree->Branch("MC_vertex_z",&MC_vertex_z,"MC_vertex_z[nMCParticles]/D");
  tree->Branch("MC_endpoint_x",&MC_endpoint_x,"MC_endpoint_x[nMCParticles]/D");
  tree->Branch("MC_endpoint_y",&MC_endpoint_y,"MC_endpoint_y[nMCParticles]/D");
  tree->Branch("MC_endpoint_z",&MC_endpoint_z,"MC_endpoint_z[nMCParticles]/D");
  tree->Branch("MC_mass",&MC_mass,"MC_mass[nMCParticles]/D");
  tree->Branch("MC_charge",&MC_charge,"MC_charge[nMCParticles]/F");
  tree->Branch("MC_absP",&MC_absP,"MC_absP[nMCParticles]/D");
  tree->Branch("MC_cosTheta",&MC_cosTheta,"MC_cosTheta[nMCParticles]/D");
  tree->Branch("MC_phi",&MC_phi,"MC_phi[nMCParticles]/D");

  // First Simulation parent

  tree->Branch("FirstSimMC_id",&FirstSimMC_id,"FirstSimMC_id[nFirstSimMCParticles]/I");
  tree->Branch("FirstSimMC_ParentId",&FirstSimMC_ParentId,"FirstSimMC_ParentId[nFirstSimMCParticles]/I");
  tree->Branch("FirstSimMC_isReal",&FirstSimMC_isReal,"FirstSimMC_isReal[nFirstSimMCParticles]/I");
  tree->Branch("FirstSimMC_genStatus",&FirstSimMC_genStatus,"FirstSimMC_genStatus[nFirstSimMCParticles]/I");

  tree->Branch("FirstSimMC_isCreatedInSim",&FirstSimMC_isCreatedInSim,"FirstSimMC_isCreatedInSim[nFirstSimMCParticles]/I");
  tree->Branch("FirstSimMC_isBackScatter",&FirstSimMC_isBackScatter,"FirstSimMC_isBackScatter[nFirstSimMCParticles]/I");
  tree->Branch("FirstSimMC_vertexNotParentEndpoint",&FirstSimMC_vertexNotParentEndpoint,"FirstSimMC_vertexNotParentEndpoint[nFirstSimMCParticles]/I");
  tree->Branch("FirstSimMC_isDecayedInTracker",&FirstSimMC_isDecayedInTracker,"FirstSimMC_isDecayedInTracker[nFirstSimMCParticles]/I");
  tree->Branch("FirstSimMC_isDecayedInCalo",&FirstSimMC_isDecayedInCalo,"FirstSimMC_isDecayedInCalo[nFirstSimMCParticles]/I");
  tree->Branch("FirstSimMC_hasLeftDet",&FirstSimMC_hasLeftDet,"FirstSimMC_hasLeftDet[nFirstSimMCParticles]/I");
  tree->Branch("FirstSimMC_isStopped",&FirstSimMC_isStopped,"FirstSimMC_isStopped[nFirstSimMCParticles]/I");

  tree->Branch("FirstSimMC_type",&FirstSimMC_type,"FirstSimMC_type[nFirstSimMCParticles]/I");
  tree->Branch("FirstSimMC_px",&FirstSimMC_px,"FirstSimMC_px[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_py",&FirstSimMC_py,"FirstSimMC_py[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_pz",&FirstSimMC_pz,"FirstSimMC_pz[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_energy",&FirstSimMC_energy,"FirstSimMC_energy[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_vertex_x",&FirstSimMC_vertex_x,"FirstSimMC_vertex_x[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_vertex_y",&FirstSimMC_vertex_y,"FirstSimMC_vertex_y[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_vertex_z",&FirstSimMC_vertex_z,"FirstSimMC_vertex_z[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_endpoint_x",&FirstSimMC_endpoint_x,"FirstSimMC_endpoint_x[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_endpoint_y",&FirstSimMC_endpoint_y,"FirstSimMC_endpoint_y[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_endpoint_z",&FirstSimMC_endpoint_z,"FirstSimMC_endpoint_z[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_mass",&FirstSimMC_mass,"FirstSimMC_mass[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_charge",&FirstSimMC_charge,"FirstSimMC_charge[nFirstSimMCParticles]/F");
  tree->Branch("FirstSimMC_absP",&FirstSimMC_absP,"FirstSimMC_absP[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_cosTheta",&FirstSimMC_cosTheta,"FirstSimMC_cosTheta[nFirstSimMCParticles]/D");
  tree->Branch("FirstSimMC_phi",&FirstSimMC_phi,"FirstSimMC_phi[nFirstSimMCParticles]/D");

  // Reco particles

  tree->Branch("Reco_id",&Reco_id,"Reco_id[nRecoParticles]/I");
  tree->Branch("Reco_type",&Reco_type,"Reco_type[nRecoParticles]/I");
  tree->Branch("Reco_isBCal",&Reco_isBCal,"Reco_isBCal[nRecoParticles]/I");
  tree->Branch("Reco_px",&Reco_px,"Reco_px[nRecoParticles]/D");
  tree->Branch("Reco_py",&Reco_py,"Reco_py[nRecoParticles]/D");
  tree->Branch("Reco_pz",&Reco_pz,"Reco_pz[nRecoParticles]/D");
  tree->Branch("Reco_energy",&Reco_energy,"Reco_energy[nRecoParticles]/D");
  tree->Branch("Reco_mass",&Reco_mass,"Reco_mass[nRecoParticles]/D");
  tree->Branch("Reco_charge",&Reco_charge,"Reco_charge[nRecoParticles]/F");
  tree->Branch("Reco_position_x",&Reco_position_x,"Reco_position_x[nRecoParticles]/F");
  tree->Branch("Reco_position_y",&Reco_position_y,"Reco_position_y[nRecoParticles]/F");
  tree->Branch("Reco_position_z",&Reco_position_z,"Reco_position_z[nRecoParticles]/F");
  tree->Branch("Reco_absP",&Reco_absP,"Reco_absP[nRecoParticles]/D");
  tree->Branch("Reco_cosTheta",&Reco_cosTheta,"Reco_cosTheta[nRecoParticles]/D");
  tree->Branch("Reco_phi",&Reco_phi,"Reco_phi[nRecoParticles]/D");
  tree->Branch("RecoToMCId",&RecoToMCId,"RecoToMCId[nRecoParticles]/I");
  tree->Branch("RecoToFirstSimParentId",&RecoToFirstSimParentId,"RecoToFirstSimParentId[nRecoParticles]/I");
  tree->Branch("RelationWeight",&RelationWeight,"RelationWeight[nRecoParticles]/F");
  tree->Branch("RecoToTrackId",&RecoToTrackId,"RecoToTrackId[nRecoParticles]/I");
  tree->Branch("RecoToClusterId",&RecoToClusterId,"RecoToClusterId[nRecoParticles]/I");
  tree->Branch("Reco_cov_pxpx",&Reco_cov_pxpx,"Reco_cov_pxpx[nRecoParticles]/F");
  tree->Branch("Reco_cov_pypx",&Reco_cov_pypx,"Reco_cov_pypx[nRecoParticles]/F");
  tree->Branch("Reco_cov_pypy",&Reco_cov_pypy,"Reco_cov_pypy[nRecoParticles]/F");
  tree->Branch("Reco_cov_pzpx",&Reco_cov_pzpx,"Reco_cov_pzpx[nRecoParticles]/F");
  tree->Branch("Reco_cov_pzpy",&Reco_cov_pzpy,"Reco_cov_pzpy[nRecoParticles]/F");
  tree->Branch("Reco_cov_pzpz",&Reco_cov_pzpz,"Reco_cov_pzpz[nRecoParticles]/F");
  tree->Branch("Reco_cov_Epx",&Reco_cov_Epx,"Reco_cov_Epx[nRecoParticles]/F");
  tree->Branch("Reco_cov_Epy",&Reco_cov_Epy,"Reco_cov_Epy[nRecoParticles]/F");
  tree->Branch("Reco_cov_Epz",&Reco_cov_Epz,"Reco_cov_Epz[nRecoParticles]/F");
  tree->Branch("Reco_cov_EE",&Reco_cov_EE,"Reco_cov_EE[nRecoParticles]/F");

  // Tracks

  tree->Branch("Track_id",&Track_id,"Track_id[nTracks]/I");
  tree->Branch("Track_type",&Track_type,"Track_type[nTracks]/I");
  tree->Branch("Track_d0",&Track_d0,"Track_d0[nTracks]/F");
  tree->Branch("Track_phi",&Track_phi,"Track_phi[nTracks]/F");
  tree->Branch("Track_omega",&Track_omega,"Track_omega[nTracks]/F");
  tree->Branch("Track_z0",&Track_z0,"Track_z0[nTracks]/F");
  tree->Branch("Track_tanlambda",&Track_tanlambda,"Track_tanlambda[nTracks]/F");
  tree->Branch("Track_refpoint_x",&Track_refpoint_x,"Track_refpoint_x[nTracks]/F");
  tree->Branch("Track_refpoint_y",&Track_refpoint_y,"Track_refpoint_y[nTracks]/F");
  tree->Branch("Track_refpoint_z",&Track_refpoint_z,"Track_refpoint_z[nTracks]/F");
  tree->Branch("Track_chi2",&Track_chi2,"Track_chi2[nTracks]/F");
  tree->Branch("Track_dedx",&Track_dedx,"Track_dedx[nTracks]/F");
  tree->Branch("Track_dedxerr",&Track_dedxerr,"Track_dedxerr[nTracks]/F");
  tree->Branch("Track_radiusInnerHit",&Track_radiusInnerHit,"Track_radiusInnerHit[nTracks]/F");

  tree->Branch("Track_cov_d0d0",&Track_cov_d0d0,"Track_cov_d0d0[nTracks]/F");
  tree->Branch("Track_cov_phid0",&Track_cov_phid0,"Track_cov_phid0[nTracks]/F");
  tree->Branch("Track_cov_phiphi",&Track_cov_phiphi,"Track_cov_phiphi[nTracks]/F");
  tree->Branch("Track_cov_omegad0",&Track_cov_omegad0,"Track_cov_omegad0[nTracks]/F");
  tree->Branch("Track_cov_omegaphi",&Track_cov_omegaphi,"Track_cov_omegaphi[nTracks]/F");
  tree->Branch("Track_cov_omegaomega",&Track_cov_omegaomega,"Track_cov_omegaomega[nTracks]/F");
  tree->Branch("Track_cov_z0d0",&Track_cov_z0d0,"Track_cov_z0d0[nTracks]/F");
  tree->Branch("Track_cov_z0phi",&Track_cov_z0phi,"Track_cov_z0phi[nTracks]/F");
  tree->Branch("Track_cov_z0omega",&Track_cov_z0omega,"Track_cov_z0omega[nTracks]/F");
  tree->Branch("Track_cov_z0z0",&Track_cov_z0z0,"Track_cov_z0z0[nTracks]/F");
  tree->Branch("Track_cov_tanlambdad0",&Track_cov_tanlambdad0,"Track_cov_tanlambdad0[nTracks]/F");
  tree->Branch("Track_cov_tanlambdaphi",&Track_cov_tanlambdaphi,"Track_cov_tanlambdaphi[nTracks]/F");
  tree->Branch("Track_cov_tanlambdaomega",&Track_cov_tanlambdaomega,"Track_cov_tanlambdaomega[nTracks]/F");
  tree->Branch("Track_cov_tanlambdaz0",&Track_cov_tanlambdaz0,"Track_cov_tanlambdaz0[nTracks]/F");
  tree->Branch("Track_cov_tanlambdatanlambda",&Track_cov_tanlambdatanlambda,"Track_cov_tanlambdatanlambda[nTracks]/F");


  // Clusters

  tree->Branch("Cluster_id",&Cluster_id,"Cluster_id[nClusters]/I");
  tree->Branch("Cluster_type",&Cluster_type,"Cluster_type[nClusters]/I");
  tree->Branch("Cluster_energy",&Cluster_energy,"Cluster_energy[nClusters]/F");
  tree->Branch("Cluster_position_x",&Cluster_position_x,"Cluster_position_x[nClusters]/F");
  tree->Branch("Cluster_position_y",&Cluster_position_y,"Cluster_position_y[nClusters]/F");
  tree->Branch("Cluster_position_z",&Cluster_position_z,"Cluster_position_z[nClusters]/F");
  tree->Branch("Cluster_cov_xx",&Cluster_cov_xx,"Cluster_cov_xx[nClusters]/F");
  tree->Branch("Cluster_cov_yx",&Cluster_cov_yx,"Cluster_cov_yx[nClusters]/F");
  tree->Branch("Cluster_cov_yy",&Cluster_cov_yy,"Cluster_cov_yy[nClusters]/F");
  tree->Branch("Cluster_cov_zx",&Cluster_cov_zx,"Cluster_cov_zx[nClusters]/F");
  tree->Branch("Cluster_cov_zy",&Cluster_cov_zy,"Cluster_cov_zy[nClusters]/F");
  tree->Branch("Cluster_cov_zz",&Cluster_cov_zz,"Cluster_cov_zz[nClusters]/F");
  tree->Branch("Cluster_iTheta",&Cluster_iTheta,"Cluster_iTheta[nClusters]/F");
  tree->Branch("Cluster_iPhi",&Cluster_iPhi,"Cluster_iPhi[nClusters]/F");
  tree->Branch("Cluster_cov_tt",&Cluster_cov_tt,"Cluster_cov_tt[nClusters]/F");
  tree->Branch("Cluster_cov_pt",&Cluster_cov_pt,"Cluster_cov_pt[nClusters]/F");
  tree->Branch("Cluster_cov_pp",&Cluster_cov_pp,"Cluster_cov_pp[nClusters]/F");

  return 0;
};

int SetPreProcTreeBranches(TTree* tree){
    
  tree->Branch("nProcessedRecos",&nProcessedRecos,"nProcessedRecos/I");
  tree->Branch("ProcessedReco_id",&ProcessedReco_id,"ProcessedReco_id[nProcessedRecos]/I");
  tree->Branch("ProcessedReco_type",&ProcessedReco_type,"ProcessedReco_type[nProcessedRecos]/I");
  tree->Branch("ProcessedReco_isBCal",&ProcessedReco_isBCal,"ProcessedReco_isBCal[nProcessedRecos]/I");
  tree->Branch("ProcessedReco_px",&ProcessedReco_px,"ProcessedReco_px[nProcessedRecos]/D");
  tree->Branch("ProcessedReco_py",&ProcessedReco_py,"ProcessedReco_py[nProcessedRecos]/D");
  tree->Branch("ProcessedReco_pz",&ProcessedReco_pz,"ProcessedReco_pz[nProcessedRecos]/D");
  tree->Branch("ProcessedReco_energy",&ProcessedReco_energy,"ProcessedReco_energy[nProcessedRecos]/D");
  tree->Branch("ProcessedReco_mass",&ProcessedReco_mass,"ProcessedReco_mass[nProcessedRecos]/D");
  tree->Branch("ProcessedReco_charge",&ProcessedReco_charge,"ProcessedReco_charge[nProcessedRecos]/F");
  tree->Branch("ProcessedReco_position_x",&ProcessedReco_position_x,"ProcessedReco_position_x[nProcessedRecos]/F");
  tree->Branch("ProcessedReco_position_y",&ProcessedReco_position_y,"ProcessedReco_position_y[nProcessedRecos]/F");
  tree->Branch("ProcessedReco_position_z",&ProcessedReco_position_z,"ProcessedReco_position_z[nProcessedRecos]/F");
  tree->Branch("ProcessedToRecoId",&ProcessedToRecoId,"ProcessedToRecoId[nProcessedRecos]/I");
  tree->Branch("ProcessedRecoRelatedToId",&ProcessedRecoRelatedToId,"ProcessedRecoRelatedToId[nProcessedRecos]/I");
  tree->Branch("ProcessedRecoRelationWeight",&ProcessedRecoRelationWeight,"ProcessedRecoRelationWeight[nProcessedRecos]/F");
  tree->Branch("NumberOfMerged",&NumberOfMerged,"NumberOfMerged[nProcessedRecos]/I");
  tree->Branch("ProcessedReco_absP",&ProcessedReco_absP,"ProcessedReco_absP[nProcessedRecos]/D");
  tree->Branch("ProcessedReco_cosTheta",&ProcessedReco_cosTheta,"ProcessedReco_cosTheta[nProcessedRecos]/D");
  tree->Branch("ProcessedReco_phi",&ProcessedReco_phi,"ProcessedReco_phi[nProcessedRecos]/D");

  return 0;
};


int SetCalibratedTreeBranches(TTree* tree){
    
  tree->Branch("nCalibratedRecos",&nCalibratedRecos,"nCalibratedRecos/I");
  tree->Branch("CalibratedReco_id",&CalibratedReco_id,"CalibratedReco_id[nCalibratedRecos]/I");
  tree->Branch("CalibratedReco_type",&CalibratedReco_type,"CalibratedReco_type[nCalibratedRecos]/I");
  tree->Branch("CalibratedReco_isBCal",&CalibratedReco_isBCal,"CalibratedReco_isBCal[nCalibratedRecos]/I");
  tree->Branch("CalibratedReco_px",&CalibratedReco_px,"CalibratedReco_px[nCalibratedRecos]/D");
  tree->Branch("CalibratedReco_py",&CalibratedReco_py,"CalibratedReco_py[nCalibratedRecos]/D");
  tree->Branch("CalibratedReco_pz",&CalibratedReco_pz,"CalibratedReco_pz[nCalibratedRecos]/D");
  tree->Branch("CalibratedReco_energy",&CalibratedReco_energy,"CalibratedReco_energy[nCalibratedRecos]/D");
  tree->Branch("CalibratedReco_mass",&CalibratedReco_mass,"CalibratedReco_mass[nCalibratedRecos]/D");
  tree->Branch("CalibratedReco_charge",&CalibratedReco_charge,"CalibratedReco_charge[nCalibratedRecos]/F");
  tree->Branch("CalibratedReco_position_x",&CalibratedReco_position_x,"CalibratedReco_position_x[nCalibratedRecos]/F");
  tree->Branch("CalibratedReco_position_y",&CalibratedReco_position_y,"CalibratedReco_position_y[nCalibratedRecos]/F");
  tree->Branch("CalibratedReco_position_z",&CalibratedReco_position_z,"CalibratedReco_position_z[nCalibratedRecos]/F");
  tree->Branch("CalibratedToRecoId",&CalibratedToRecoId,"CalibratedToRecoId[nCalibratedRecos]/I");
  tree->Branch("CalibratedRecoRelatedToId",&CalibratedRecoRelatedToId,"CalibratedRecoRelatedToId[nCalibratedRecos]/I");
  tree->Branch("CalibratedRecoRelationWeight",&CalibratedRecoRelationWeight,"CalibratedRecoRelationWeight[nCalibratedRecos]/F");
  tree->Branch("NumberOfMerged",&NumberOfMerged,"NumberOfMerged[nCalibratedRecos]/I");
  tree->Branch("CalibratedReco_absP",&CalibratedReco_absP,"CalibratedReco_absP[nCalibratedRecos]/D");
  tree->Branch("CalibratedReco_cosTheta",&CalibratedReco_cosTheta,"CalibratedReco_cosTheta[nCalibratedRecos]/D");
  tree->Branch("CalibratedReco_phi",&CalibratedReco_phi,"CalibratedReco_phi[nCalibratedRecos]/D");

  return 0;
};

int SetSelPhotonTreeBranches(TTree* tree){
    
  tree->Branch("RCENE",&RCENE,"RCENE/I");


  return 0;
};

int SetSelectionEfficienciesTreeBranches(TTree* tree){
  tree->Branch("Entries_BeforeCuts",&Entries_BeforeCuts,"Entries_BeforeCuts/D");
  tree->Branch("Entries_AfterKinCuts",&Entries_AfterKinCuts,"Entries_AfterKinCuts/D");
  tree->Branch("Entries_AfterAllCuts",&Entries_AfterAllCuts,"Entries_AfterAllCuts/D");
  tree->Branch("CrossSection_AfterKinCuts",&CrossSection_AfterKinCuts,"CrossSection_AfterKinCuts/D");
  tree->Branch("Efficiency_KinCuts",&Efficiency_KinCuts,"Efficiency_KinCuts/D");
  tree->Branch("Efficiency_RecCuts",&Efficiency_RecCuts,"Efficiency_RecCuts/D");
  tree->Branch("Efficiency_AllCuts",&Efficiency_AllCuts,"Efficiency_AllCuts/D");

  return 0;
}

int SetScalingFactorsTreeBranches(TTree* tree){

  tree->Branch("ScalingFactorp0p0",&ScalingFactorp0p0,"ScalingFactorp0p0/D");
  tree->Branch("ScalingFactorp8p0",&ScalingFactorp8p0,"ScalingFactorp8p0/D");
  tree->Branch("ScalingFactorp8m3",&ScalingFactorp8m3,"ScalingFactorp8m3/D");
  tree->Branch("ScalingFactorp8m6",&ScalingFactorp8m6,"ScalingFactorp8m6/D");
  tree->Branch("ScalingFactorm8p0",&ScalingFactorm8p0,"ScalingFactorm8p0/D");
  tree->Branch("ScalingFactorm8p3",&ScalingFactorm8p3,"ScalingFactorm8p3/D");
  tree->Branch("ScalingFactorm8p6",&ScalingFactorm8p6,"ScalingFactorm8p6/D");
  
  tree->Branch("PolXSecp0p0",&PolXSecp0p0,"PolXSecp0p0/D");
  tree->Branch("PolXSecp8p0",&PolXSecp8p0,"PolXSecp8p0/D");
  tree->Branch("PolXSecp8m3",&PolXSecp8m3,"PolXSecp8m3/D");
  tree->Branch("PolXSecp8m6",&PolXSecp8m6,"PolXSecp8m6/D");
  tree->Branch("PolXSecm8p0",&PolXSecm8p3,"PolXSecm8p0/D");
  tree->Branch("PolXSecm8p3",&PolXSecm8p6,"PolXSecm8p3/D");
  tree->Branch("PolXSecm8p6",&PolXSecm8p3,"PolXSecm8p6/D");
return 0;
}

int SetBcalTreeBranches(TTree* tree){

  tree->Branch("nBcalParticles",&nBcalParticles,"nBcalParticles/I");

  tree->Branch("Bcal_px",&Bcal_px,"Bcal_px[nBcalParticles]/D");
  tree->Branch("Bcal_py",&Bcal_py,"Bcal_py[nBcalParticles]/D");
  tree->Branch("Bcal_pz",&Bcal_pz,"Bcal_pz[nBcalParticles]/D");
  tree->Branch("Bcal_energy",&Bcal_energy,"Bcal_energy[nBcalParticles]/D");
  tree->Branch("Bcal_mass",&Bcal_mass,"Bcal_mass[nBcalParticles]/D");
  tree->Branch("Bcal_charge",&Bcal_charge,"Bcal_charge[nBcalParticles]/F");
  tree->Branch("Bcal_efficiency",&Bcal_efficiency,"Bcal_efficiency[nBcalParticles]/F");
  tree->Branch("Bcal_absP",&Bcal_absP,"Bcal_absP[nBcalParticles]/D");
  tree->Branch("Bcal_cosTheta",&Bcal_cosTheta,"Bcal_cosTheta[nBcalParticles]/D");
  tree->Branch("Bcal_phi",&Bcal_phi,"Bcal_phi[nBcalParticles]/D");
  tree->Branch("BcalToMCId",&BcalToMCId,"BcalToMCId[nBcalParticles]/I");

return 0;
}

//#################################################################################
//################### Load Tree Branches ##########################################
//#################################################################################

int LoadGlobalTree(TTree* tree){

//  tree->SetBranchAddress("Process",&Process);
//  tree->SetBranchAddress("RunID",&RunID);
//  tree->SetBranchAddress("NumberOfEventsInRun",&NumberOfEventsInRun);
//  tree->SetBranchAddress("NumberOfEventsInFile",&NumberOfEventsInFile);
//  tree->SetBranchAddress("CrossSection",&CrossSection);
  tree->SetBranchAddress("MCLumi",&MCLumi);
  tree->SetBranchAddress("crosss",&crosss);
//  tree->SetBranchAddress("CMSEnergy",&CMSEnergy);
  tree->SetBranchAddress("electron_polarisation",&electron_polarisation);
  tree->SetBranchAddress("positron_polarisation",&positron_polarisation);

  return 0;
};


int LoadTree(TTree* tree){

  tree->SetBranchAddress("Process",&Process);
  tree->SetBranchAddress("RunID",&RunID);
  tree->SetBranchAddress("NumberOfEvents",&NumberOfEvents);
  tree->SetBranchAddress("CrossSection",&CrossSection);
  tree->SetBranchAddress("MCLumi_Run",&MCLumi_Run);
  tree->SetBranchAddress("CMSEnergy",&CMSEnergy);
  tree->SetBranchAddress("EventCMSEnergy",&EventCMSEnergy);
  tree->SetBranchAddress("CollisionEnergy",&CollisionEnergy);
  tree->SetBranchAddress("P_e",&P_e);
  tree->SetBranchAddress("P_p",&P_p);
  tree->SetBranchAddress("PolWeight",&PolWeight);
  tree->SetBranchAddress("EventWeight",&EventWeight); 
  tree->SetBranchAddress("EventID",&EventID);
  tree->SetBranchAddress("nMCParticles",&nMCParticles);
  tree->SetBranchAddress("nFirstSimMCParticles",&nFirstSimMCParticles);
  tree->SetBranchAddress("nRecoParticles",&nRecoParticles);
  tree->SetBranchAddress("nTracks",&nTracks);    
  tree->SetBranchAddress("nClusters",&nClusters);    
  // MC

  tree->SetBranchAddress("MC_id",&MC_id);
  tree->SetBranchAddress("MC_isReal",&MC_isReal);
  tree->SetBranchAddress("MC_genStatus",&MC_genStatus);

  tree->SetBranchAddress("MC_isCreatedInSim",&MC_isCreatedInSim);
  tree->SetBranchAddress("MC_isBackScatter",&MC_isBackScatter);
  tree->SetBranchAddress("MC_vertexNotParentEndpoint",&MC_vertexNotParentEndpoint);
  tree->SetBranchAddress("MC_isDecayedInTracker",&MC_isDecayedInTracker);
  tree->SetBranchAddress("MC_isDecayedInCalo",&MC_isDecayedInCalo);
  tree->SetBranchAddress("MC_hasLeftDet",&MC_hasLeftDet);
  tree->SetBranchAddress("MC_isStopped",&MC_isStopped);

  tree->SetBranchAddress("MC_type",&MC_type);
  tree->SetBranchAddress("MC_px",&MC_px);
  tree->SetBranchAddress("MC_py",&MC_py);
  tree->SetBranchAddress("MC_pz",&MC_pz);
  tree->SetBranchAddress("MC_energy",&MC_energy);
  tree->SetBranchAddress("MC_vertex_x",&MC_vertex_x);
  tree->SetBranchAddress("MC_vertex_y",&MC_vertex_y);
  tree->SetBranchAddress("MC_vertex_z",&MC_vertex_z);
  tree->SetBranchAddress("MC_endpoint_x",&MC_endpoint_x);
  tree->SetBranchAddress("MC_endpoint_y",&MC_endpoint_y);
  tree->SetBranchAddress("MC_endpoint_z",&MC_endpoint_z);
  tree->SetBranchAddress("MC_mass",&MC_mass);
  tree->SetBranchAddress("MC_charge",&MC_charge);
  tree->SetBranchAddress("MC_absP",&MC_absP);
  tree->SetBranchAddress("MC_cosTheta",&MC_cosTheta);
  tree->SetBranchAddress("MC_phi",&MC_phi);

  // First Simulation parent

  tree->SetBranchAddress("FirstSimMC_id",&FirstSimMC_id);
  tree->SetBranchAddress("FirstSimMC_ParentId",&FirstSimMC_ParentId);
  tree->SetBranchAddress("FirstSimMC_isReal",&FirstSimMC_isReal);
  tree->SetBranchAddress("FirstSimMC_genStatus",&FirstSimMC_genStatus);

  tree->SetBranchAddress("FirstSimMC_isCreatedInSim",&FirstSimMC_isCreatedInSim);
  tree->SetBranchAddress("FirstSimMC_isBackScatter",&FirstSimMC_isBackScatter);
  tree->SetBranchAddress("FirstSimMC_vertexNotParentEndpoint",&FirstSimMC_vertexNotParentEndpoint);
  tree->SetBranchAddress("FirstSimMC_isDecayedInTracker",&FirstSimMC_isDecayedInTracker);
  tree->SetBranchAddress("FirstSimMC_isDecayedInCalo",&FirstSimMC_isDecayedInCalo);
  tree->SetBranchAddress("FirstSimMC_hasLeftDet",&FirstSimMC_hasLeftDet);
  tree->SetBranchAddress("FirstSimMC_isStopped",&FirstSimMC_isStopped);

  tree->SetBranchAddress("FirstSimMC_type",&FirstSimMC_type);
  tree->SetBranchAddress("FirstSimMC_px",&FirstSimMC_px);
  tree->SetBranchAddress("FirstSimMC_py",&FirstSimMC_py);
  tree->SetBranchAddress("FirstSimMC_pz",&FirstSimMC_pz);
  tree->SetBranchAddress("FirstSimMC_energy",&FirstSimMC_energy);
  tree->SetBranchAddress("FirstSimMC_vertex_x",&FirstSimMC_vertex_x);
  tree->SetBranchAddress("FirstSimMC_vertex_y",&FirstSimMC_vertex_y);
  tree->SetBranchAddress("FirstSimMC_vertex_z",&FirstSimMC_vertex_z);
  tree->SetBranchAddress("FirstSimMC_endpoint_x",&FirstSimMC_endpoint_x);
  tree->SetBranchAddress("FirstSimMC_endpoint_y",&FirstSimMC_endpoint_y);
  tree->SetBranchAddress("FirstSimMC_endpoint_z",&FirstSimMC_endpoint_z);
  tree->SetBranchAddress("FirstSimMC_mass",&FirstSimMC_mass);
  tree->SetBranchAddress("FirstSimMC_charge",&FirstSimMC_charge);
  tree->SetBranchAddress("FirstSimMC_absP",&FirstSimMC_absP);
  tree->SetBranchAddress("FirstSimMC_cosTheta",&FirstSimMC_cosTheta);
  tree->SetBranchAddress("FirstSimMC_phi",&FirstSimMC_phi);

  // Reco particles

  tree->SetBranchAddress("Reco_id",&Reco_id);
  tree->SetBranchAddress("Reco_type",&Reco_type);
  tree->SetBranchAddress("Reco_isBCal",&Reco_isBCal);
  tree->SetBranchAddress("Reco_px",&Reco_px);
  tree->SetBranchAddress("Reco_py",&Reco_py);
  tree->SetBranchAddress("Reco_pz",&Reco_pz);
  tree->SetBranchAddress("Reco_energy",&Reco_energy);
  tree->SetBranchAddress("Reco_mass",&Reco_mass);
  tree->SetBranchAddress("Reco_charge",&Reco_charge);
  tree->SetBranchAddress("Reco_position_x",&Reco_position_x);
  tree->SetBranchAddress("Reco_position_y",&Reco_position_y);
  tree->SetBranchAddress("Reco_position_z",&Reco_position_z);
  tree->SetBranchAddress("Reco_absP",&Reco_absP);
  tree->SetBranchAddress("Reco_cosTheta",&Reco_cosTheta);
  tree->SetBranchAddress("Reco_phi",&Reco_phi);
  tree->SetBranchAddress("RecoToMCId",&RecoToMCId);
  tree->SetBranchAddress("RecoToFirstSimParentId",&RecoToFirstSimParentId);
  tree->SetBranchAddress("RelationWeight",&RelationWeight);
  tree->SetBranchAddress("RecoToTrackId",&RecoToTrackId);
  tree->SetBranchAddress("RecoToClusterId",&RecoToClusterId);
  tree->SetBranchAddress("Reco_cov_pxpx",&Reco_cov_pxpx);
  tree->SetBranchAddress("Reco_cov_pypx",&Reco_cov_pypx);
  tree->SetBranchAddress("Reco_cov_pypy",&Reco_cov_pypy);
  tree->SetBranchAddress("Reco_cov_pzpx",&Reco_cov_pzpx);
  tree->SetBranchAddress("Reco_cov_pzpy",&Reco_cov_pzpy);
  tree->SetBranchAddress("Reco_cov_pzpz",&Reco_cov_pzpz);
  tree->SetBranchAddress("Reco_cov_Epx",&Reco_cov_Epx);
  tree->SetBranchAddress("Reco_cov_Epy",&Reco_cov_Epy);
  tree->SetBranchAddress("Reco_cov_Epz",&Reco_cov_Epz);
  tree->SetBranchAddress("Reco_cov_EE",&Reco_cov_EE);

  // Tracks

  tree->SetBranchAddress("Track_id",&Track_id);
  tree->SetBranchAddress("Track_type",&Track_type);
  tree->SetBranchAddress("Track_d0",&Track_d0);
  tree->SetBranchAddress("Track_phi",&Track_phi);
  tree->SetBranchAddress("Track_omega",&Track_omega);
  tree->SetBranchAddress("Track_z0",&Track_z0);
  tree->SetBranchAddress("Track_tanlambda",&Track_tanlambda);
  tree->SetBranchAddress("Track_refpoint_x",&Track_refpoint_x);
  tree->SetBranchAddress("Track_refpoint_y",&Track_refpoint_y);
  tree->SetBranchAddress("Track_refpoint_z",&Track_refpoint_z);
  tree->SetBranchAddress("Track_chi2",&Track_chi2);
  tree->SetBranchAddress("Track_dedx",&Track_dedx);
  tree->SetBranchAddress("Track_dedxerr",&Track_dedxerr);
  tree->SetBranchAddress("Track_radiusInnerHit",&Track_radiusInnerHit);

  tree->SetBranchAddress("Track_cov_d0d0",&Track_cov_d0d0);
  tree->SetBranchAddress("Track_cov_phid0",&Track_cov_phid0);
  tree->SetBranchAddress("Track_cov_phiphi",&Track_cov_phiphi);
  tree->SetBranchAddress("Track_cov_omegad0",&Track_cov_omegad0);
  tree->SetBranchAddress("Track_cov_omegaphi",&Track_cov_omegaphi);
  tree->SetBranchAddress("Track_cov_omegaomega",&Track_cov_omegaomega);
  tree->SetBranchAddress("Track_cov_z0d0",&Track_cov_z0d0);
  tree->SetBranchAddress("Track_cov_z0phi",&Track_cov_z0phi);
  tree->SetBranchAddress("Track_cov_z0omega",&Track_cov_z0omega);
  tree->SetBranchAddress("Track_cov_z0z0",&Track_cov_z0z0);
  tree->SetBranchAddress("Track_cov_tanlambdad0",&Track_cov_tanlambdad0);
  tree->SetBranchAddress("Track_cov_tanlambdaphi",&Track_cov_tanlambdaphi);
  tree->SetBranchAddress("Track_cov_tanlambdaomega",&Track_cov_tanlambdaomega);
  tree->SetBranchAddress("Track_cov_tanlambdaz0",&Track_cov_tanlambdaz0);
  tree->SetBranchAddress("Track_cov_tanlambdatanlambda",&Track_cov_tanlambdatanlambda);


  // Clusters

  tree->SetBranchAddress("Cluster_id",&Cluster_id);
  tree->SetBranchAddress("Cluster_type",&Cluster_type);
  tree->SetBranchAddress("Cluster_energy",&Cluster_energy);
  tree->SetBranchAddress("Cluster_position_x",&Cluster_position_x);
  tree->SetBranchAddress("Cluster_position_y",&Cluster_position_y);
  tree->SetBranchAddress("Cluster_position_z",&Cluster_position_z);
  tree->SetBranchAddress("Cluster_cov_xx",&Cluster_cov_xx);
  tree->SetBranchAddress("Cluster_cov_yx",&Cluster_cov_yx);
  tree->SetBranchAddress("Cluster_cov_yy",&Cluster_cov_yy);
  tree->SetBranchAddress("Cluster_cov_zx",&Cluster_cov_zx);
  tree->SetBranchAddress("Cluster_cov_zy",&Cluster_cov_zy);
  tree->SetBranchAddress("Cluster_cov_zz",&Cluster_cov_zz);
  tree->SetBranchAddress("Cluster_iTheta",&Cluster_iTheta);
  tree->SetBranchAddress("Cluster_iPhi",&Cluster_iPhi);
  tree->SetBranchAddress("Cluster_cov_tt",&Cluster_cov_tt);
  tree->SetBranchAddress("Cluster_cov_pt",&Cluster_cov_pt);
  tree->SetBranchAddress("Cluster_cov_pp",&Cluster_cov_pp);
  return 0;
};

int LoadPreProcTree(TTree* tree){
  tree->SetBranchAddress("nProcessedRecos",&nProcessedRecos);
  tree->SetBranchAddress("ProcessedReco_id",&ProcessedReco_id);
  tree->SetBranchAddress("ProcessedReco_type",&ProcessedReco_type);
  tree->SetBranchAddress("ProcessedReco_isBCal",&ProcessedReco_isBCal);
  tree->SetBranchAddress("ProcessedReco_px",&ProcessedReco_px);
  tree->SetBranchAddress("ProcessedReco_py",&ProcessedReco_py);
  tree->SetBranchAddress("ProcessedReco_pz",&ProcessedReco_pz);
  tree->SetBranchAddress("ProcessedReco_energy",&ProcessedReco_energy);
  tree->SetBranchAddress("ProcessedReco_mass",&ProcessedReco_mass);
  tree->SetBranchAddress("ProcessedReco_charge",&ProcessedReco_charge);
  tree->SetBranchAddress("ProcessedReco_position_x",&ProcessedReco_position_x);
  tree->SetBranchAddress("ProcessedReco_position_y",&ProcessedReco_position_y);
  tree->SetBranchAddress("ProcessedReco_position_z",&ProcessedReco_position_z);
  tree->SetBranchAddress("ProcessedToRecoId",&ProcessedToRecoId);
  tree->SetBranchAddress("ProcessedRecoRelatedToId",&ProcessedRecoRelatedToId);
  tree->SetBranchAddress("ProcessedRecoRelationWeight",&ProcessedRecoRelationWeight);
  tree->SetBranchAddress("NumberOfMerged",&NumberOfMerged);
  tree->SetBranchAddress("ProcessedReco_absP",&ProcessedReco_absP);
  tree->SetBranchAddress("ProcessedReco_cosTheta",&ProcessedReco_cosTheta);
  tree->SetBranchAddress("ProcessedReco_phi",&ProcessedReco_phi);

  return 0;
};

int LoadCalibratedTree(TTree* tree){
  tree->SetBranchAddress("nCalibratedRecos",&nCalibratedRecos);
  tree->SetBranchAddress("CalibratedReco_id",&CalibratedReco_id);
  tree->SetBranchAddress("CalibratedReco_type",&CalibratedReco_type);
  tree->SetBranchAddress("CalibratedReco_isBCal",&CalibratedReco_isBCal);
  tree->SetBranchAddress("CalibratedReco_px",&CalibratedReco_px);
  tree->SetBranchAddress("CalibratedReco_py",&CalibratedReco_py);
  tree->SetBranchAddress("CalibratedReco_pz",&CalibratedReco_pz);
  tree->SetBranchAddress("CalibratedReco_energy",&CalibratedReco_energy);
  tree->SetBranchAddress("CalibratedReco_mass",&CalibratedReco_mass);
  tree->SetBranchAddress("CalibratedReco_charge",&CalibratedReco_charge);
  tree->SetBranchAddress("CalibratedReco_position_x",&CalibratedReco_position_x);
  tree->SetBranchAddress("CalibratedReco_position_y",&CalibratedReco_position_y);
  tree->SetBranchAddress("CalibratedReco_position_z",&CalibratedReco_position_z);
  tree->SetBranchAddress("CalibratedToRecoId",&CalibratedToRecoId);
  tree->SetBranchAddress("CalibratedRecoRelatedToId",&CalibratedRecoRelatedToId);
  tree->SetBranchAddress("CalibratedRecoRelationWeight",&CalibratedRecoRelationWeight);
  tree->SetBranchAddress("NumberOfMerged",&NumberOfMerged);
  tree->SetBranchAddress("CalibratedReco_absP",&CalibratedReco_absP);
  tree->SetBranchAddress("CalibratedReco_cosTheta",&CalibratedReco_cosTheta);
  tree->SetBranchAddress("CalibratedReco_phi",&CalibratedReco_phi);

  return 0;
};

int LoadSelPhotonTree(TTree* tree){
  tree->SetBranchAddress("RCENE",&RCENE);


  return 0;
};

// Background XSec

int LoadXSecTree(TTree* tree){
  tree->SetBranchAddress("XSec",&XSec);
  tree->SetBranchAddress("s_prime",&s_prime);
  tree->SetBranchAddress("E_prime",&E_prime);
  tree->SetBranchAddress("Theta_prime",&Theta_prime);
  return 0;
};


int LoadSelectionEfficienciesTree(TTree* tree){
  tree->SetBranchAddress("Entries_BeforeCuts",&Entries_BeforeCuts);
  tree->SetBranchAddress("Entries_AfterKinCuts",&Entries_AfterKinCuts);
  tree->SetBranchAddress("Entries_AfterAllCuts",&Entries_AfterAllCuts);
  tree->SetBranchAddress("CrossSection_AfterKinCuts",&CrossSection_AfterKinCuts);
  tree->SetBranchAddress("Efficiency_KinCuts",&Efficiency_KinCuts);
  tree->SetBranchAddress("Efficiency_RecCuts",&Efficiency_RecCuts);
  tree->SetBranchAddress("Efficiency_AllCuts",&Efficiency_AllCuts);

  return 0;
}

int LoadScalingFactorsTree(TTree* tree){

  tree->SetBranchAddress("ScalingFactorp0p0",&ScalingFactorp0p0);
  tree->SetBranchAddress("ScalingFactorp8p0",&ScalingFactorp8p0);
  tree->SetBranchAddress("ScalingFactorp8m3",&ScalingFactorp8m3);
  tree->SetBranchAddress("ScalingFactorp8m6",&ScalingFactorp8m6);
  tree->SetBranchAddress("ScalingFactorm8p0",&ScalingFactorm8p0);
  tree->SetBranchAddress("ScalingFactorm8p3",&ScalingFactorm8p3);
  tree->SetBranchAddress("ScalingFactorm8p6",&ScalingFactorm8p6);

  tree->SetBranchAddress("PolXSecp0p0",&PolXSecp0p0);
  tree->SetBranchAddress("PolXSecp8p0",&PolXSecp8p0);
  tree->SetBranchAddress("PolXSecp8m3",&PolXSecp8m3);
  tree->SetBranchAddress("PolXSecp8m6",&PolXSecp8m6);
  tree->SetBranchAddress("PolXSecm8p0",&PolXSecm8p0);
  tree->SetBranchAddress("PolXSecm8p3",&PolXSecm8p3);
  tree->SetBranchAddress("PolXSecm8p6",&PolXSecm8p6);
return 0;

}


int LoadBcalTree(TTree* tree){

  tree->SetBranchAddress("nBcalParticles",&nBcalParticles);

  tree->SetBranchAddress("Bcal_px",&Bcal_px);
  tree->SetBranchAddress("Bcal_py",&Bcal_py);
  tree->SetBranchAddress("Bcal_pz",&Bcal_pz);
  tree->SetBranchAddress("Bcal_energy",&Bcal_energy);
  tree->SetBranchAddress("Bcal_mass",&Bcal_mass);
  tree->SetBranchAddress("Bcal_charge",&Bcal_charge);
  tree->SetBranchAddress("Bcal_efficiency",&Bcal_efficiency);
  tree->SetBranchAddress("Bcal_absP",&Bcal_absP);
  tree->SetBranchAddress("Bcal_cosTheta",&Bcal_cosTheta);
  tree->SetBranchAddress("Bcal_phi",&Bcal_phi);
  tree->SetBranchAddress("BcalToMCId",&BcalToMCId);

return 0;
}
