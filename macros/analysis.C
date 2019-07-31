#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include <iostream>
#include <csignal>

using namespace std;

//#include "eventselection.C"
//#include "input.C"

#ifndef __SIGHANDLER__
#define __SIGHANDLER__
void signalhandler(int singal)
{
  cerr << "signalhandler called. abort." << endl;
  abort(); 
}
#endif

// This is the main macro producing basic histograms.
// "Event" object is a holder of relevant data e.g. definition of histgrams, inputfiles.
// We will create 6 Event objects : nung(LR/RL), bhabhang(LL/LR/RL/RR) so that
// we can multiply event weight for each polarization later.
// See Event::process() in eventselection.C for the actual analysis.
void analysis()
{
  signal(SIGINT,signalhandler);

  // Prepare output file
  stringstream foutname;
  foutname << "plots/plots.root" << ends;
  cerr << "Output plots have been written into " << foutname.str().data() << endl;
  TFile* output = new TFile(foutname.str().data(),"RECREATE");

  // Parameters to be used in hNrecNgenEmc_photon.
  const int nxbins_e = 17;
  const double xbins_e[nxbins_e] = {0,5,10,15,20,25,30,35,40,45,50,70,90,120,150,200,250};

  // Define Event object which contains analyses methods and output histograms.
  Event* EnungLR = new Event;
  EnungLR->setProcessType(nungLR);
  output->cd();
  EnungLR->outputs.hCutStats           = new TH1F("hCutStats_nungLR",";;",5,0,5);
  EnungLR->outputs.hE_photon           = new TH1F("hE_photon_nungLR",";E [GeV/c];",300,0,300);
  EnungLR->outputs.hNrecNgen_photon    = new TH1F("hNrecNgen_photon_nungLR",";# #gamma_{rec}/#gamma_{gen};",8,0,8);
  EnungLR->outputs.hNrecNgenEmc_photon = new TH2F("hNrecNgenEmc_photon_nungLR",";E_{#gamma,MC} [GeV/c];N_{rec}",nxbins_e-1,xbins_e,8,0,8);
  EnungLR->outputs.hNrecNgenCostheta_photon = new TH2F("hNrecNgenCostheta_photon_nungLR",";cos#theta_{#gamma,MC};N_{rec}",100,0,1,8,0,8);

  EnungLR->outputs.hPt_ep_isr             = new TH1F("hPt_ep_nungLR_isr"   ,";Pt [GeV/c];",270,0,270);
  EnungLR->outputs.hPt_ep_ol              = new TH1F("hPt_ep_nungLR_ol"    ,";Pt [GeV/c];",270,0,270);
  EnungLR->outputs.hPt_ep_other           = new TH1F("hPt_ep_nungLR_other" ,";Pt [GeV/c];",270,0,270);
  EnungLR->outputs.hPt_pfo_isr            = new TH1F("hPt_pfo_nungLR_isr"  ,";Pt [GeV/c];",270,0,270);
  EnungLR->outputs.hPt_pfo_ol             = new TH1F("hPt_pfo_nungLR_ol"   ,";Pt [GeV/c];",270,0,270);
  EnungLR->outputs.hPt_pfo_other          = new TH1F("hPt_pfo_nungLR_other",";Pt [GeV/c];",270,0,270);
  EnungLR->outputs.hE_photon_rest         = new TH1F("hE_photon_nungLR_rest",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_photon_ol           = new TH1F("hE_photon_nungLR_ol",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_V0_rest             = new TH1F("hE_V0_nungLR_rest",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_V0_ol               = new TH1F("hE_V0_nungLR_ol",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_neutron_rest        = new TH1F("hE_neutron_nungLR_rest",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_neutron_ol          = new TH1F("hE_neutron_nungLR_ol",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_electron_rest       = new TH1F("hE_electron_nungLR_rest",";E [GeV];",50,0,50);
  EnungLR->outputs.hE_electron_ol         = new TH1F("hE_electron_nungLR_ol",";E [GeV];",50,0,50);
  EnungLR->outputs.hE_muon_rest           = new TH1F("hE_muon_nungLR_rest",";E [GeV];",50,0,50);
  EnungLR->outputs.hE_muon_ol             = new TH1F("hE_muon_nungLR_ol",";E [GeV];",50,0,50);
  EnungLR->outputs.hE_pion_rest           = new TH1F("hE_pion_nungLR_rest",";E [GeV];",50,0,50);
  EnungLR->outputs.hE_pion_ol             = new TH1F("hE_pion_nungLR_ol",";E [GeV];",50,0,50);
  EnungLR->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_nungLR",";E [GeV];",750,0,750);
  EnungLR->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_nungLR",";E [GeV];",750,0,750);
  EnungLR->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_nungLR",";# of BCal clusters;",6,0,6);
  EnungLR->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_nungLR",";# of BCal clusters;",6,0,6);
  EnungLR->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_nungLR",";# of BCal clusters;",6,0,6);
  EnungLR->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_nungLR",";Pt [GeV];",100,0,20);
  EnungLR->outputs.hPt_R_bcal_bcalcoord   = new TH2F("hPt_R_bcal_bcalcoord_nungLR",";Pt [GeV];R [mm]",100,0,20,100,0,150);
  EnungLR->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_nungLR",";Pt [GeV];",100,0,20);
  EnungLR->outputs.hPt_bcal               = new TH1F("hPt_bcal_nungLR",";Pt [GeV];",100,0,20);
  EnungLR->outputs.hE_bcal                = new TH1F("hE_bcal_nungLR",";E [GeV];",350,0,350);

  EnungLR->outputs.hRZ_bcal_wo_cut        = new TH2F("hRZ_bcal_wo_cut_nungLR",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EnungLR->outputs.hRZ_bcal_w_PtEcut      = new TH2F("hRZ_bcal_w_PtEcut_nungLR",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EnungLR->outputs.SignalEvent            = new TNtuple("SignalEvent_nungLR","","e:phi_bcalcoord:estar:phistar:thetastar:sqrtsstar:gen_e");
  EnungLR->outputs.SignalPhoton           = new TNtuple("SignalPhoton_nungLR","","gen_endx:gen_endy:gen_endz:gen_isDecayedInTracker:gen_isDecayedInCalorimeter:gen_e:gen_phi:gen_theta:gen_ndaughters:rec_e:rec_phi:rec_theta:rec_mcindex:nISR:isMCSignalEvt:isRecSignalEvt:ismatched:relWeight:isPassedPtCut:isPassedECut:isPassedBCalVeto:nrec_pfoAsPhoton:nrec_pfoAsNonPhoton:nAcceptablePhoton_MC_per_evt:ev");
 
  SetInputFiles(EnungLR); // see input.C
  EnungLR->process();


  Event* EnungRL = new Event;
  EnungRL->setProcessType(nungRL);
  output->cd();
  EnungRL->outputs.hCutStats           = new TH1F("hCutStats_nungRL",";;",5,0,5);
  EnungRL->outputs.hE_photon           = new TH1F("hE_photon_nungRL",";E [GeV/c];",300,0,300);
  EnungRL->outputs.hNrecNgen_photon    = new TH1F("hNrecNgen_photon_nungRL",";# #gamma_{rec}/#gamma_{gen};",8,0,8);
  EnungRL->outputs.hNrecNgenEmc_photon = new TH2F("hNrecNgenEmc_photon_nungRL",";E_{#gamma,MC} [GeV/c];N_{rec}",nxbins_e-1,xbins_e,8,0,8);
  EnungRL->outputs.hNrecNgenCostheta_photon = new TH2F("hNrecNgenCostheta_photon_nungRL",";cos#theta_{#gamma,MC};N_{rec}",100,0,1,8,0,8);

  EnungRL->outputs.hPt_ep_isr             = new TH1F("hPt_ep_nungRL_isr"   ,";Pt [GeV/c];",270,0,270);
  EnungRL->outputs.hPt_ep_ol              = new TH1F("hPt_ep_nungRL_ol"    ,";Pt [GeV/c];",270,0,270);
  EnungRL->outputs.hPt_ep_other           = new TH1F("hPt_ep_nungRL_other" ,";Pt [GeV/c];",270,0,270);
  EnungRL->outputs.hPt_pfo_isr            = new TH1F("hPt_pfo_nungRL_isr"  ,";Pt [GeV/c];",270,0,270);
  EnungRL->outputs.hPt_pfo_ol             = new TH1F("hPt_pfo_nungRL_ol"   ,";Pt [GeV/c];",270,0,270);
  EnungRL->outputs.hPt_pfo_other          = new TH1F("hPt_pfo_nungRL_other",";Pt [GeV/c];",270,0,270);
  EnungRL->outputs.hE_photon_rest         = new TH1F("hE_photon_nungRL_rest",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_photon_ol           = new TH1F("hE_photon_nungRL_ol",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_V0_rest             = new TH1F("hE_V0_nungRL_rest",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_V0_ol               = new TH1F("hE_V0_nungRL_ol",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_neutron_rest        = new TH1F("hE_neutron_nungRL_rest",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_neutron_ol          = new TH1F("hE_neutron_nungRL_ol",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_electron_rest       = new TH1F("hE_electron_nungRL_rest",";E [GeV];",50,0,50);
  EnungRL->outputs.hE_electron_ol         = new TH1F("hE_electron_nungRL_ol",";E [GeV];",50,0,50);
  EnungRL->outputs.hE_muon_rest           = new TH1F("hE_muon_nungRL_rest",";E [GeV];",50,0,50);
  EnungRL->outputs.hE_muon_ol             = new TH1F("hE_muon_nungRL_ol",";E [GeV];",50,0,50);
  EnungRL->outputs.hE_pion_rest           = new TH1F("hE_pion_nungRL_rest",";E [GeV];",50,0,50);
  EnungRL->outputs.hE_pion_ol             = new TH1F("hE_pion_nungRL_ol",";E [GeV];",50,0,50);
  EnungRL->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_nungRL",";E [GeV];",750,0,750);
  EnungRL->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_nungRL",";E [GeV];",750,0,750);
  EnungRL->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_nungRL",";# of BCal clusters;",6,0,6);
  EnungRL->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_nungRL",";# of BCal clusters;",6,0,6);
  EnungRL->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_nungRL",";# of BCal clusters;",6,0,6);
  EnungRL->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_nungRL",";Pt [GeV];",100,0,20);
  EnungRL->outputs.hPt_R_bcal_bcalcoord   = new TH2F("hPt_R_bcal_bcalcoord_nungRL",";Pt [GeV];R [mm]",100,0,20,100,0,150);
  EnungRL->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_nungRL",";Pt [GeV];",100,0,20);
  EnungRL->outputs.hPt_bcal               = new TH1F("hPt_bcal_nungRL",";Pt [GeV];",100,0,20);
  EnungRL->outputs.hE_bcal                = new TH1F("hE_bcal_nungRL",";E [GeV];",350,0,350);

  EnungRL->outputs.hRZ_bcal_wo_cut        = new TH2F("hRZ_bcal_wo_cut_nungRL",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EnungRL->outputs.hRZ_bcal_w_PtEcut      = new TH2F("hRZ_bcal_w_PtEcut_nungRL",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EnungRL->outputs.SignalEvent            = new TNtuple("SignalEvent_nungRL","","e:phi_bcalcoord:estar:phistar:thetastar:sqrtsstar:gen_e");
  EnungRL->outputs.SignalPhoton           = new TNtuple("SignalPhoton_nungRL","","gen_endx:gen_endy:gen_endz:gen_isDecayedInTracker:gen_isDecayedInCalorimeter:gen_e:gen_phi:gen_theta:gen_ndaughters:rec_e:rec_phi:rec_theta:rec_mcindex:nISR:isMCSignalEvt:isRecSignalEvt:ismatched:relWeight:isPassedPtCut:isPassedECut:isPassedBCalVeto:nrec_pfoAsPhoton:nrec_pfoAsNonPhoton:nAcceptablePhoton_MC_per_evt:ev");
  SetInputFiles(EnungRL); // see input.C
  EnungRL->process();

  // bhabha
  Event* EbhabhangLL = new Event;
  EbhabhangLL->setProcessType(bhabhangLL);
  output->cd();
  EbhabhangLL->outputs.hCutStats              = new TH1F("hCutStats_bhabhangLL",";;",5,0,5);
  EbhabhangLL->outputs.hPt_ep_isr             = new TH1F("hPt_ep_bhabhangLL_isr"   ,";Pt [GeV/c];",270,0,270);
  EbhabhangLL->outputs.hPt_ep_ol              = new TH1F("hPt_ep_bhabhangLL_ol"    ,";Pt [GeV/c];",270,0,270);
  EbhabhangLL->outputs.hPt_ep_other           = new TH1F("hPt_ep_bhabhangLL_other" ,";Pt [GeV/c];",270,0,270);
  EbhabhangLL->outputs.hPt_pfo_isr            = new TH1F("hPt_pfo_bhabhangLL_isr"  ,";Pt [GeV/c];",270,0,270);
  EbhabhangLL->outputs.hPt_pfo_ol             = new TH1F("hPt_pfo_bhabhangLL_ol"   ,";Pt [GeV/c];",270,0,270);
  EbhabhangLL->outputs.hPt_pfo_other          = new TH1F("hPt_pfo_bhabhangLL_other",";Pt [GeV/c];",270,0,270);
  EbhabhangLL->outputs.hE_photon_rest         = new TH1F("hE_photon_bhabhangLL_rest",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_photon_ol           = new TH1F("hE_photon_bhabhangLL_ol",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_photon_electron     = new TH1F("hE_photon_bhabhangLL_electron",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_V0_rest             = new TH1F("hE_V0_bhabhangLL_rest",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_V0_ol               = new TH1F("hE_V0_bhabhangLL_ol",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_neutron_rest        = new TH1F("hE_neutron_bhabhangLL_rest",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_neutron_ol          = new TH1F("hE_neutron_bhabhangLL_ol",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_electron_rest       = new TH1F("hE_electron_bhabhangLL_rest",";E [GeV];",50,0,50);
  EbhabhangLL->outputs.hE_electron_ol         = new TH1F("hE_electron_bhabhangLL_ol",";E [GeV];",50,0,50);
  EbhabhangLL->outputs.hE_muon_rest           = new TH1F("hE_muon_bhabhangLL_rest",";E [GeV];",50,0,50);
  EbhabhangLL->outputs.hE_muon_ol             = new TH1F("hE_muon_bhabhangLL_ol",";E [GeV];",50,0,50);
  EbhabhangLL->outputs.hE_pion_rest           = new TH1F("hE_pion_bhabhangLL_rest",";E [GeV];",50,0,50);
  EbhabhangLL->outputs.hE_pion_ol             = new TH1F("hE_pion_bhabhangLL_ol",";E [GeV];",50,0,50);
  EbhabhangLL->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_bhabhangLL",";E [GeV];",750,0,750);
  EbhabhangLL->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_bhabhangLL",";E [GeV];",750,0,750);
  EbhabhangLL->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_bhabhangLL",";# of BCal clusters;",6,0,6);
  EbhabhangLL->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_bhabhangLL",";# of BCal clusters;",6,0,6);
  EbhabhangLL->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_bhabhangLL",";# of BCal clusters;",6,0,6);
  EbhabhangLL->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_bhabhangLL",";Pt [GeV];",100,0,20);
  EbhabhangLL->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_bhabhangLL",";Pt [GeV];",100,0,20);
  EbhabhangLL->outputs.hPt_bcal               = new TH1F("hPt_bcal_bhabhangLL",";Pt [GeV];",100,0,20);
  EbhabhangLL->outputs.hE_bcal                = new TH1F("hE_bcal_bhabhangLL",";E [GeV];",350,0,350);

  EbhabhangLL->outputs.hRZ_bcal_wo_cut        = new TH2F("hRZ_bcal_wo_cut_bhabhangLL",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EbhabhangLL->outputs.hRZ_bcal_w_PtEcut      = new TH2F("hRZ_bcal_w_PtEcut_bhabhangLL",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EbhabhangLL->outputs.SignalEvent            = new TNtuple("SignalEvent_bhabhangLL","","e:phi_bcalcoord:estar:phistar:thetastar:sqrtsstar:gen_e");
  EbhabhangLL->outputs.SignalPhoton           = new TNtuple("SignalPhoton_bhabhangLL","","gen_endx:gen_endy:gen_endz:gen_isDecayedInTracker:gen_isDecayedInCalorimeter:gen_e:gen_phi:gen_theta:gen_ndaughters:rec_e:rec_phi:rec_theta:rec_mcindex:nISR:isMCSignalEvt:isRecSignalEvt:ismatched:relWeight:isPassedPtCut:isPassedECut:isPassedBCalVeto:nrec_pfoAsPhoton:nrec_pfoAsNonPhoton:nAcceptablePhoton_MC_per_evt:ev");
  SetInputFiles(EbhabhangLL); // see input.C
  EbhabhangLL->process();

  Event* EbhabhangLR = new Event;
  EbhabhangLR->setProcessType(bhabhangLR);
  output->cd();
  EbhabhangLR->outputs.hCutStats              = new TH1F("hCutStats_bhabhangLR",";;",5,0,5);
  EbhabhangLR->outputs.hPt_ep_isr             = new TH1F("hPt_ep_bhabhangLR_isr"   ,";Pt [GeV/c];",270,0,270);
  EbhabhangLR->outputs.hPt_ep_ol              = new TH1F("hPt_ep_bhabhangLR_ol"    ,";Pt [GeV/c];",270,0,270); 
  EbhabhangLR->outputs.hPt_ep_other           = new TH1F("hPt_ep_bhabhangLR_other" ,";Pt [GeV/c];",270,0,270);
  EbhabhangLR->outputs.hPt_pfo_isr            = new TH1F("hPt_pfo_bhabhangLR_isr"  ,";Pt [GeV/c];",270,0,270);
  EbhabhangLR->outputs.hPt_pfo_ol             = new TH1F("hPt_pfo_bhabhangLR_ol"   ,";Pt [GeV/c];",270,0,270);
  EbhabhangLR->outputs.hPt_pfo_other          = new TH1F("hPt_pfo_bhabhangLR_other",";Pt [GeV/c];",270,0,270);
  EbhabhangLR->outputs.hE_photon_rest         = new TH1F("hE_photon_bhabhangLR_rest",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_photon_ol           = new TH1F("hE_photon_bhabhangLR_ol",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_photon_electron     = new TH1F("hE_photon_bhabhangLR_electron",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_V0_rest             = new TH1F("hE_V0_bhabhangLR_rest",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_V0_ol               = new TH1F("hE_V0_bhabhangLR_ol",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_neutron_rest        = new TH1F("hE_neutron_bhabhangLR_rest",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_neutron_ol          = new TH1F("hE_neutron_bhabhangLR_ol",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_electron_rest       = new TH1F("hE_electron_bhabhangLR_rest",";E [GeV];",50,0,50);
  EbhabhangLR->outputs.hE_electron_ol         = new TH1F("hE_electron_bhabhangLR_ol",";E [GeV];",50,0,50);
  EbhabhangLR->outputs.hE_muon_rest           = new TH1F("hE_muon_bhabhangLR_rest",";E [GeV];",50,0,50);
  EbhabhangLR->outputs.hE_muon_ol             = new TH1F("hE_muon_bhabhangLR_ol",";E [GeV];",50,0,50);
  EbhabhangLR->outputs.hE_pion_rest           = new TH1F("hE_pion_bhabhangLR_rest",";E [GeV];",50,0,50);
  EbhabhangLR->outputs.hE_pion_ol             = new TH1F("hE_pion_bhabhangLR_ol",";E [GeV];",50,0,50);
  EbhabhangLR->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_bhabhangLR",";E [GeV];",750,0,750);
  EbhabhangLR->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_bhabhangLR",";E [GeV];",750,0,750);
  EbhabhangLR->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_bhabhangLR",";# of BCal clusters;",6,0,6);
  EbhabhangLR->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_bhabhangLR",";# of BCal clusters;",6,0,6);
  EbhabhangLR->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_bhabhangLR",";# of BCal clusters;",6,0,6);
  EbhabhangLR->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_bhabhangLR",";Pt [GeV];",100,0,20);
  EbhabhangLR->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_bhabhangLR",";Pt [GeV];",100,0,20);
  EbhabhangLR->outputs.hPt_bcal               = new TH1F("hPt_bcal_bhabhangLR",";Pt [GeV];",100,0,20);
  EbhabhangLR->outputs.hE_bcal                = new TH1F("hE_bcal_bhabhangLR",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hRZ_bcal_wo_cut        = new TH2F("hRZ_bcal_wo_cut_bhabhangLR",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EbhabhangLR->outputs.hRZ_bcal_w_PtEcut      = new TH2F("hRZ_bcal_w_PtEcut_bhabhangLR",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EbhabhangLR->outputs.SignalEvent            = new TNtuple("SignalEvent_bhabhangLR","","e:phi_bcalcoord:estar:phistar:thetastar:sqrtsstar:gen_e");
  EbhabhangLR->outputs.SignalPhoton           = new TNtuple("SignalPhoton_bhabhangLR","","gen_endx:gen_endy:gen_endz:gen_isDecayedInTracker:gen_isDecayedInCalorimeter:gen_e:gen_phi:gen_theta:gen_ndaughters:rec_e:rec_phi:rec_theta:rec_mcindex:nISR:isMCSignalEvt:isRecSignalEvt:ismatched:relWeight:isPassedPtCut:isPassedECut:isPassedBCalVeto:nrec_pfoAsPhoton:nrec_pfoAsNonPhoton:nAcceptablePhoton_MC_per_evt:ev");
  SetInputFiles(EbhabhangLR); // see input.C
  EbhabhangLR->process();

  Event* EbhabhangRL = new Event;
  EbhabhangRL->setProcessType(bhabhangRL);
  output->cd();
  EbhabhangRL->outputs.hCutStats              = new TH1F("hCutStats_bhabhangRL",";;",5,0,5);
  EbhabhangRL->outputs.hPt_ep_isr             = new TH1F("hPt_ep_bhabhangRL_isr"   ,";Pt [GeV/c];",270,0,270);
  EbhabhangRL->outputs.hPt_ep_ol              = new TH1F("hPt_ep_bhabhangRL_ol"    ,";Pt [GeV/c];",270,0,270);
  EbhabhangRL->outputs.hPt_ep_other           = new TH1F("hPt_ep_bhabhangRL_other" ,";Pt [GeV/c];",270,0,270);
  EbhabhangRL->outputs.hPt_pfo_isr            = new TH1F("hPt_pfo_bhabhangRL_isr"  ,";Pt [GeV/c];",270,0,270);
  EbhabhangRL->outputs.hPt_pfo_ol             = new TH1F("hPt_pfo_bhabhangRL_ol"   ,";Pt [GeV/c];",270,0,270);
  EbhabhangRL->outputs.hPt_pfo_other          = new TH1F("hPt_pfo_bhabhangRL_other",";Pt [GeV/c];",270,0,270);
  EbhabhangRL->outputs.hE_photon_rest         = new TH1F("hE_photon_bhabhangRL_rest",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_photon_ol           = new TH1F("hE_photon_bhabhangRL_ol",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_photon_electron     = new TH1F("hE_photon_bhabhangRL_electron",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_V0_rest             = new TH1F("hE_V0_bhabhangRL_rest",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_V0_ol               = new TH1F("hE_V0_bhabhangRL_ol",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_neutron_rest        = new TH1F("hE_neutron_bhabhangRL_rest",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_neutron_ol          = new TH1F("hE_neutron_bhabhangRL_ol",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_electron_rest       = new TH1F("hE_electron_bhabhangRL_rest",";E [GeV];",50,0,50);
  EbhabhangRL->outputs.hE_electron_ol         = new TH1F("hE_electron_bhabhangRL_ol",";E [GeV];",50,0,50);
  EbhabhangRL->outputs.hE_muon_rest           = new TH1F("hE_muon_bhabhangRL_rest",";E [GeV];",50,0,50);
  EbhabhangRL->outputs.hE_muon_ol             = new TH1F("hE_muon_bhabhangRL_ol",";E [GeV];",50,0,50);
  EbhabhangRL->outputs.hE_pion_rest           = new TH1F("hE_pion_bhabhangRL_rest",";E [GeV];",50,0,50);
  EbhabhangRL->outputs.hE_pion_ol             = new TH1F("hE_pion_bhabhangRL_ol",";E [GeV];",50,0,50);
  EbhabhangRL->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_bhabhangRL",";E [GeV];",750,0,750);
  EbhabhangRL->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_bhabhangRL",";E [GeV];",750,0,750);
  EbhabhangRL->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_bhabhangRL",";# of BCal clusters;",6,0,6);
  EbhabhangRL->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_bhabhangRL",";# of BCal clusters;",6,0,6);
  EbhabhangRL->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_bhabhangRL",";# of BCal clusters;",6,0,6);
  EbhabhangRL->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_bhabhangRL",";Pt [GeV];",100,0,20);
  EbhabhangRL->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_bhabhangRL",";Pt [GeV];",100,0,20);
  EbhabhangRL->outputs.hPt_bcal               = new TH1F("hPt_bcal_bhabhangRL",";Pt [GeV];",100,0,20);
  EbhabhangRL->outputs.hE_bcal                = new TH1F("hE_bcal_bhabhangRL",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hRZ_bcal_wo_cut        = new TH2F("hRZ_bcal_wo_cut_bhabhangRL",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EbhabhangRL->outputs.hRZ_bcal_w_PtEcut      = new TH2F("hRZ_bcal_w_PtEcut_bhabhangRL",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EbhabhangRL->outputs.SignalEvent            = new TNtuple("SignalEvent_bhabhangRL","","e:phi_bcalcoord:estar:phistar:thetastar:sqrtsstar:gen_e");
  EbhabhangRL->outputs.SignalPhoton           = new TNtuple("SignalPhoton_bhabhangRL","","gen_endx:gen_endy:gen_endz:gen_isDecayedInTracker:gen_isDecayedInCalorimeter:gen_e:gen_phi:gen_theta:gen_ndaughters:rec_e:rec_phi:rec_theta:rec_mcindex:nISR:isMCSignalEvt:isRecSignalEvt:ismatched:relWeight:isPassedPtCut:isPassedECut:isPassedBCalVeto:nrec_pfoAsPhoton:nrec_pfoAsNonPhoton:nAcceptablePhoton_MC_per_evt:ev");
  SetInputFiles(EbhabhangRL); // see input.C
  EbhabhangRL->process();

  Event* EbhabhangRR = new Event;
  EbhabhangRR->setProcessType(bhabhangRR);
  output->cd();
  EbhabhangRR->outputs.hCutStats              = new TH1F("hCutStats_bhabhangRR",";;",5,0,5);
  EbhabhangRR->outputs.hPt_ep_isr             = new TH1F("hPt_ep_bhabhangRR_isr"   ,";Pt [GeV/c];",270,0,270);
  EbhabhangRR->outputs.hPt_ep_ol              = new TH1F("hPt_ep_bhabhangRR_ol"    ,";Pt [GeV/c];",270,0,270);
  EbhabhangRR->outputs.hPt_ep_other           = new TH1F("hPt_ep_bhabhangRR_other" ,";Pt [GeV/c];",270,0,270);
  EbhabhangRR->outputs.hPt_pfo_isr            = new TH1F("hPt_pfo_bhabhangRR_isr"  ,";Pt [GeV/c];",270,0,270);
  EbhabhangRR->outputs.hPt_pfo_ol             = new TH1F("hPt_pfo_bhabhangRR_ol"   ,";Pt [GeV/c];",270,0,270);
  EbhabhangRR->outputs.hPt_pfo_other          = new TH1F("hPt_pfo_bhabhangRR_other",";Pt [GeV/c];",270,0,270);
  EbhabhangRR->outputs.hE_photon_rest         = new TH1F("hE_photon_bhabhangRR_rest",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_photon_ol           = new TH1F("hE_photon_bhabhangRR_ol",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_photon_electron     = new TH1F("hE_photon_bhabhangRR_electron",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_V0_rest             = new TH1F("hE_V0_bhabhangRR_rest",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_V0_ol               = new TH1F("hE_V0_bhabhangRR_ol",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_neutron_rest        = new TH1F("hE_neutron_bhabhangRR_rest",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_neutron_ol          = new TH1F("hE_neutron_bhabhangRR_ol",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_electron_rest       = new TH1F("hE_electron_bhabhangRR_rest",";E [GeV];",50,0,50);
  EbhabhangRR->outputs.hE_electron_ol         = new TH1F("hE_electron_bhabhangRR_ol",";E [GeV];",50,0,50);
  EbhabhangRR->outputs.hE_muon_rest           = new TH1F("hE_muon_bhabhangRR_rest",";E [GeV];",50,0,50);
  EbhabhangRR->outputs.hE_muon_ol             = new TH1F("hE_muon_bhabhangRR_ol",";E [GeV];",50,0,50);
  EbhabhangRR->outputs.hE_pion_rest           = new TH1F("hE_pion_bhabhangRR_rest",";E [GeV];",50,0,50);
  EbhabhangRR->outputs.hE_pion_ol             = new TH1F("hE_pion_bhabhangRR_ol",";E [GeV];",50,0,50);
  EbhabhangRR->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_bhabhangRR",";E [GeV];",750,0,750);
  EbhabhangRR->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_bhabhangRR",";E [GeV];",750,0,750);
  EbhabhangRR->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_bhabhangRR",";# of BCal clusters;",6,0,6);
  EbhabhangRR->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_bhabhangRR",";# of BCal clusters;",6,0,6);
  EbhabhangRR->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_bhabhangRR",";# of BCal clusters;",6,0,6);
  EbhabhangRR->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_bhabhangRR",";Pt [GeV];",100,0,20);
  EbhabhangRR->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_bhabhangRR",";Pt [GeV];",100,0,20);
  EbhabhangRR->outputs.hPt_bcal               = new TH1F("hPt_bcal_bhabhangRR",";Pt [GeV];",100,0,20);
  EbhabhangRR->outputs.hE_bcal                = new TH1F("hE_bcal_bhabhangRR",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hRZ_bcal_wo_cut        = new TH2F("hRZ_bcal_wo_cut_bhabhangRR",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EbhabhangRR->outputs.hRZ_bcal_w_PtEcut      = new TH2F("hRZ_bcal_w_PtEcut_bhabhangRR",";Z [mm];R [mm]",100,3220,3270,100,0,120);
  EbhabhangRR->outputs.SignalEvent            = new TNtuple("SignalEvent_bhabhangRR","","e:phi_bcalcoord:estar:phistar:thetastar:sqrtsstar:gen_e");
  EbhabhangRR->outputs.SignalPhoton           = new TNtuple("SignalPhoton_bhabhangRR","","gen_endx:gen_endy:gen_endz:gen_isDecayedInTracker:gen_isDecayedInCalorimeter:gen_e:gen_phi:gen_theta:gen_ndaughters:rec_e:rec_phi:rec_theta:rec_mcindex:nISR:isMCSignalEvt:isRecSignalEvt:ismatched:relWeight:isPassedPtCut:isPassedECut:isPassedBCalVeto:nrec_pfoAsPhoton:nrec_pfoAsNonPhoton:nAcceptablePhoton_MC_per_evt:ev");
  SetInputFiles(EbhabhangRR); // see input.C
  EbhabhangRR->process();

  output->cd();
  EnungLR->outputs.hCutStats->Write();
  EnungLR->outputs.hPt_ep_other->Write();
  EnungLR->outputs.hPt_ep_ol->Write();
  EnungLR->outputs.hPt_ep_isr->Write();
  EnungLR->outputs.hPt_pfo_other->Write();
  EnungLR->outputs.hPt_pfo_ol->Write();
  EnungLR->outputs.hPt_pfo_isr->Write();
  EnungLR->outputs.hE_photon_ol->Write();
  EnungLR->outputs.hE_photon_rest->Write();
  EnungLR->outputs.hE_V0_ol->Write();
  EnungLR->outputs.hE_V0_rest->Write();
  EnungLR->outputs.hE_neutron_ol->Write();
  EnungLR->outputs.hE_neutron_rest->Write();
  EnungLR->outputs.hE_electron_ol->Write();
  EnungLR->outputs.hE_electron_rest->Write();
  EnungLR->outputs.hE_muon_ol->Write();
  EnungLR->outputs.hE_muon_rest->Write();
  EnungLR->outputs.hE_pion_ol->Write();
  EnungLR->outputs.hE_pion_rest->Write();
  EnungLR->outputs.hEvis_pfo->Write();
  EnungLR->outputs.hEvis_pfo_wo_pi_n->Write();
  EnungLR->outputs.hNBcalClusters->Write();
  EnungLR->outputs.hNBcalClusters1ISR->Write();
  EnungLR->outputs.hNBcalClustersMultiISR->Write();
  EnungLR->outputs.hE_photon->Write();
  EnungLR->outputs.hNrecNgen_photon->Write();
  //EnungLR->outputs.gNrecNgenEmc_photon->SetName("gNrecNgenEmc_photon_nungLR");
  //EnungLR->outputs.gNrecNgenEmc_photon->Write();
  //EnungLR->outputs.gNrecNgenCostheta_photon->SetName("gNrecNgenCostheta_photon_nungLR");
  //EnungLR->outputs.gNrecNgenCostheta_photon->Write();
  EnungLR->outputs.hNrecNgenEmc_photon->Write();
  EnungLR->outputs.hNrecNgenCostheta_photon->Write();
  EnungLR->outputs.hPt_bcal_bcalcoord->Write();
  EnungLR->outputs.hPt_R_bcal_bcalcoord->Write();
  EnungLR->outputs.hPtMax_bcal_bcalcoord->Write();
  EnungLR->outputs.hPt_bcal->Write();
  EnungLR->outputs.hE_bcal->Write();
  EnungLR->outputs.hRZ_bcal_wo_cut->Write();
  EnungLR->outputs.hRZ_bcal_w_PtEcut->Write();
  EnungLR->outputs.SignalEvent->Write();
  EnungLR->outputs.SignalPhoton->Write();

  EnungRL->outputs.hCutStats->Write();
  EnungRL->outputs.hPt_ep_other->Write();
  EnungRL->outputs.hPt_ep_ol->Write();
  EnungRL->outputs.hPt_ep_isr->Write();
  EnungRL->outputs.hPt_pfo_other->Write();
  EnungRL->outputs.hPt_pfo_ol->Write();
  EnungRL->outputs.hPt_pfo_isr->Write();
  EnungRL->outputs.hE_photon_ol->Write();
  EnungRL->outputs.hE_photon_rest->Write();
  EnungRL->outputs.hE_V0_ol->Write();
  EnungRL->outputs.hE_V0_rest->Write();
  EnungRL->outputs.hE_neutron_ol->Write();
  EnungRL->outputs.hE_neutron_rest->Write();
  EnungRL->outputs.hE_electron_ol->Write();
  EnungRL->outputs.hE_electron_rest->Write();
  EnungRL->outputs.hE_muon_ol->Write();
  EnungRL->outputs.hE_muon_rest->Write();
  EnungRL->outputs.hE_pion_ol->Write();
  EnungRL->outputs.hE_pion_rest->Write();
  EnungRL->outputs.hEvis_pfo->Write();
  EnungRL->outputs.hEvis_pfo_wo_pi_n->Write();
  EnungRL->outputs.hNBcalClusters->Write();
  EnungRL->outputs.hNBcalClusters1ISR->Write();
  EnungRL->outputs.hNBcalClustersMultiISR->Write();
  EnungRL->outputs.hE_photon->Write();
  EnungRL->outputs.hNrecNgen_photon->Write();
  //EnungRL->outputs.gNrecNgenEmc_photon->SetName("gNrecNgenEmc_photon_nungRL");
  //EnungRL->outputs.gNrecNgenEmc_photon->Write();
  //EnungRL->outputs.gNrecNgenCostheta_photon->SetName("gNrecNgenCostheta_photon_nungRL");
  //EnungRL->outputs.gNrecNgenCostheta_photon->Write();
  EnungRL->outputs.hNrecNgenEmc_photon->Write();
  EnungRL->outputs.hNrecNgenCostheta_photon->Write();
  EnungRL->outputs.hPt_bcal_bcalcoord->Write();
  EnungRL->outputs.hPt_R_bcal_bcalcoord->Write();
  EnungRL->outputs.hPtMax_bcal_bcalcoord->Write();
  EnungRL->outputs.hPt_bcal->Write();
  EnungRL->outputs.hE_bcal->Write();
  EnungRL->outputs.hRZ_bcal_wo_cut->Write();
  EnungRL->outputs.hRZ_bcal_w_PtEcut->Write();
  EnungRL->outputs.SignalEvent->Write();
  EnungRL->outputs.SignalPhoton->Write();

  EbhabhangLL->outputs.hCutStats->Write();
  EbhabhangLL->outputs.hPt_ep_ol->Write();
  EbhabhangLL->outputs.hPt_ep_isr->Write();
  EbhabhangLL->outputs.hPt_ep_other->Write();
  EbhabhangLL->outputs.hPt_pfo_ol->Write();
  EbhabhangLL->outputs.hPt_pfo_isr->Write();
  EbhabhangLL->outputs.hPt_pfo_other->Write();
  EbhabhangLL->outputs.hE_photon_ol->Write();
  EbhabhangLL->outputs.hE_photon_electron->Write();
  EbhabhangLL->outputs.hE_photon_rest->Write();
  EbhabhangLL->outputs.hE_V0_ol->Write();
  EbhabhangLL->outputs.hE_V0_rest->Write();
  EbhabhangLL->outputs.hE_neutron_ol->Write();
  EbhabhangLL->outputs.hE_neutron_rest->Write();
  EbhabhangLL->outputs.hE_electron_ol->Write();
  EbhabhangLL->outputs.hE_electron_rest->Write();
  EbhabhangLL->outputs.hE_muon_ol->Write();
  EbhabhangLL->outputs.hE_muon_rest->Write();
  EbhabhangLL->outputs.hE_pion_ol->Write();
  EbhabhangLL->outputs.hE_pion_rest->Write();
  EbhabhangLL->outputs.hEvis_pfo->Write();
  EbhabhangLL->outputs.hEvis_pfo_wo_pi_n->Write();
  EbhabhangLL->outputs.hNBcalClusters->Write();
  EbhabhangLL->outputs.hPt_bcal_bcalcoord->Write();
  EbhabhangLL->outputs.hPtMax_bcal_bcalcoord->Write();
  EbhabhangLL->outputs.hPt_bcal->Write();
  EbhabhangLL->outputs.hE_bcal->Write();
  EbhabhangLL->outputs.hRZ_bcal_wo_cut->Write();
  EbhabhangLL->outputs.hRZ_bcal_w_PtEcut->Write();
  EbhabhangLL->outputs.SignalEvent->Write();
  EbhabhangLL->outputs.SignalPhoton->Write();

  EbhabhangLR->outputs.hCutStats->Write();
  EbhabhangLR->outputs.hPt_ep_ol->Write();
  EbhabhangLR->outputs.hPt_ep_isr->Write();
  EbhabhangLR->outputs.hPt_ep_other->Write();
  EbhabhangLR->outputs.hPt_pfo_ol->Write();
  EbhabhangLR->outputs.hPt_pfo_isr->Write();
  EbhabhangLR->outputs.hPt_pfo_other->Write();
  EbhabhangLR->outputs.hE_photon_ol->Write();
  EbhabhangLR->outputs.hE_photon_electron->Write();
  EbhabhangLR->outputs.hE_photon_rest->Write();
  EbhabhangLR->outputs.hE_V0_ol->Write();
  EbhabhangLR->outputs.hE_V0_rest->Write();
  EbhabhangLR->outputs.hE_neutron_ol->Write();
  EbhabhangLR->outputs.hE_neutron_rest->Write();
  EbhabhangLR->outputs.hE_electron_ol->Write();
  EbhabhangLR->outputs.hE_electron_rest->Write();
  EbhabhangLR->outputs.hE_muon_ol->Write();
  EbhabhangLR->outputs.hE_muon_rest->Write();
  EbhabhangLR->outputs.hE_pion_ol->Write();
  EbhabhangLR->outputs.hE_pion_rest->Write();
  EbhabhangLR->outputs.hEvis_pfo->Write();
  EbhabhangLR->outputs.hEvis_pfo_wo_pi_n->Write();
  EbhabhangLR->outputs.hNBcalClusters->Write();
  EbhabhangLR->outputs.hPt_bcal_bcalcoord->Write();
  EbhabhangLR->outputs.hPtMax_bcal_bcalcoord->Write();
  EbhabhangLR->outputs.hPt_bcal->Write();
  EbhabhangLR->outputs.hE_bcal->Write();
  EbhabhangLR->outputs.hRZ_bcal_wo_cut->Write();
  EbhabhangLR->outputs.hRZ_bcal_w_PtEcut->Write();
  EbhabhangLR->outputs.SignalEvent->Write();
  EbhabhangLR->outputs.SignalPhoton->Write();

  EbhabhangRL->outputs.hCutStats->Write();
  EbhabhangRL->outputs.hPt_ep_ol->Write();
  EbhabhangRL->outputs.hPt_ep_isr->Write();
  EbhabhangRL->outputs.hPt_ep_other->Write();
  EbhabhangRL->outputs.hPt_pfo_ol->Write();
  EbhabhangRL->outputs.hPt_pfo_isr->Write();
  EbhabhangRL->outputs.hPt_pfo_other->Write();
  EbhabhangRL->outputs.hE_photon_ol->Write();
  EbhabhangRL->outputs.hE_photon_electron->Write();
  EbhabhangRL->outputs.hE_photon_rest->Write();
  EbhabhangRL->outputs.hE_V0_ol->Write();
  EbhabhangRL->outputs.hE_V0_rest->Write();
  EbhabhangRL->outputs.hE_neutron_ol->Write();
  EbhabhangRL->outputs.hE_neutron_rest->Write();
  EbhabhangRL->outputs.hE_electron_ol->Write();
  EbhabhangRL->outputs.hE_electron_rest->Write();
  EbhabhangRL->outputs.hE_muon_ol->Write();
  EbhabhangRL->outputs.hE_muon_rest->Write();
  EbhabhangRL->outputs.hE_pion_ol->Write();
  EbhabhangRL->outputs.hE_pion_rest->Write();
  EbhabhangRL->outputs.hEvis_pfo->Write();
  EbhabhangRL->outputs.hEvis_pfo_wo_pi_n->Write();
  EbhabhangRL->outputs.hNBcalClusters->Write();
  EbhabhangRL->outputs.hPt_bcal_bcalcoord->Write();
  EbhabhangRL->outputs.hPtMax_bcal_bcalcoord->Write();
  EbhabhangRL->outputs.hPt_bcal->Write();
  EbhabhangRL->outputs.hE_bcal->Write();
  EbhabhangRL->outputs.hRZ_bcal_wo_cut->Write();
  EbhabhangRL->outputs.hRZ_bcal_w_PtEcut->Write();
  EbhabhangRL->outputs.SignalEvent->Write();
  EbhabhangRL->outputs.SignalPhoton->Write();

  EbhabhangRR->outputs.hCutStats->Write();
  EbhabhangRR->outputs.hPt_ep_ol->Write();
  EbhabhangRR->outputs.hPt_ep_isr->Write();
  EbhabhangRR->outputs.hPt_ep_other->Write();
  EbhabhangRR->outputs.hPt_pfo_ol->Write();
  EbhabhangRR->outputs.hPt_pfo_isr->Write();
  EbhabhangRR->outputs.hPt_pfo_other->Write();
  EbhabhangRR->outputs.hE_photon_ol->Write();
  EbhabhangRR->outputs.hE_photon_electron->Write();
  EbhabhangRR->outputs.hE_photon_rest->Write();
  EbhabhangRR->outputs.hE_V0_ol->Write();
  EbhabhangRR->outputs.hE_V0_rest->Write();
  EbhabhangRR->outputs.hE_neutron_ol->Write();
  EbhabhangRR->outputs.hE_neutron_rest->Write();
  EbhabhangRR->outputs.hE_electron_ol->Write();
  EbhabhangRR->outputs.hE_electron_rest->Write();
  EbhabhangRR->outputs.hE_muon_ol->Write();
  EbhabhangRR->outputs.hE_muon_rest->Write();
  EbhabhangRR->outputs.hE_pion_ol->Write();
  EbhabhangRR->outputs.hE_pion_rest->Write();
  EbhabhangRR->outputs.hEvis_pfo->Write();
  EbhabhangRR->outputs.hEvis_pfo_wo_pi_n->Write();
  EbhabhangRR->outputs.hNBcalClusters->Write();
  EbhabhangRR->outputs.hPt_bcal_bcalcoord->Write();
  EbhabhangRR->outputs.hPtMax_bcal_bcalcoord->Write();
  EbhabhangRR->outputs.hPt_bcal->Write();
  EbhabhangRR->outputs.hE_bcal->Write();
  EbhabhangRR->outputs.hRZ_bcal_wo_cut->Write();
  EbhabhangRR->outputs.hRZ_bcal_w_PtEcut->Write();
  EbhabhangRR->outputs.SignalEvent->Write();
  EbhabhangRR->outputs.SignalPhoton->Write();
}

