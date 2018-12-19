#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include <iostream>
#include <csignal>

using namespace std;

#include "eventselection.C"
#include "input.C"

void signalhandler(int singal)
{
  cerr << "signalhandler called. abort." << endl;
  abort(); 
}

// This is the main macro producing basic histograms.
// "Event" object is a holder of relevant data e.g. definition of histgrams, inputfiles.
// We will create 6 Event objects : nung(LR/RL), bhabhang(LL/LR/RL/RR) so that
// we can multiply event weight for each polarization later.
// See Event::process() in eventselection.C for the actual analysis.
void analysis()
{
  signal(SIGINT,signalhandler);
  // Define Event object which contains analyses methods and output histograms.
  Event* EnungLR = new Event;
  EnungLR->setProcessType(nungLR);
  EnungLR->outputs.hCutStats           = new TH1F("hCutStats_nungLR",";;",5,0,5);
  EnungLR->outputs.hE_photon           = new TH1F("hE_photon_nungLR",";E [GeV/c];",300,0,300);
  EnungLR->outputs.hNrecNgen_photon    = new TH1F("hNrecNgen_photon_nungLR",";# #gamma_{rec}/#gamma_{gen};",8,0,8);
  EnungLR->outputs.hNrecNgenEmc_photon = new TH2F("hNrecNgenEmc_photon_nungLR",";E_{#gamma,MC} [GeV/c];#bar{N_{rec}/N_{gen}}",100,0,250,100,0,8);
  EnungLR->outputs.hNrecNgenCostheta_photon = new TH2F("hNrecNgenCostheta_photon_nungLR",";cos#theta_{#gamma,MC};#bar{N_{rec}/N_{gen}}",100,0,1,100,0,8);

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
  EnungLR->outputs.hE_electron_rest       = new TH1F("hE_electron_nungLR_rest",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_electron_ol         = new TH1F("hE_electron_nungLR_ol",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_muon_rest           = new TH1F("hE_muon_nungLR_rest",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_muon_ol             = new TH1F("hE_muon_nungLR_ol",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_pion_rest           = new TH1F("hE_pion_nungLR_rest",";E [GeV];",350,0,350);
  EnungLR->outputs.hE_pion_ol             = new TH1F("hE_pion_nungLR_ol",";E [GeV];",350,0,350);
  EnungLR->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_nungLR",";E [GeV];",750,0,750);
  EnungLR->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_nungLR",";E [GeV];",750,0,750);
  EnungLR->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_nungLR",";# of BCal clusters;",6,0,6);
  EnungLR->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_nungLR",";# of BCal clusters;",6,0,6);
  EnungLR->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_nungLR",";# of BCal clusters;",6,0,6);
  EnungLR->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_nungLR",";Pt [GeV];",100,0,20);
  EnungLR->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_nungLR",";Pt [GeV];",100,0,20);
  EnungLR->outputs.hPt_bcal               = new TH1F("hPt_bcal_nungLR",";Pt [GeV];",100,0,20);
  EnungLR->outputs.hE_bcal                = new TH1F("hE_bcal_nungLR",";E [GeV];",350,0,350);
 
  SetInputFiles(EnungLR); // see input.C
  EnungLR->process();
  // do something after event loop.
  EnungLR->processAfterEventLoop();


  Event* EnungRL = new Event;
  EnungRL->setProcessType(nungRL);
  EnungRL->outputs.hCutStats           = new TH1F("hCutStats_nungRL",";;",5,0,5);
  EnungRL->outputs.hE_photon           = new TH1F("hE_photon_nungRL",";E [GeV/c];",300,0,300);
  EnungRL->outputs.hNrecNgen_photon    = new TH1F("hNrecNgen_photon_nungRL",";# #gamma_{rec}/#gamma_{gen};",8,0,8);
  EnungRL->outputs.hNrecNgenEmc_photon = new TH2F("hNrecNgenEmc_photon_nungRL",";E_{#gamma,MC} [GeV/c];#bar{N_{rec}/N_{gen}}",100,0,250,100,0,8);
  EnungRL->outputs.hNrecNgenCostheta_photon = new TH2F("hNrecNgenCostheta_photon_nungRL",";cos#theta_{#gamma,MC};#bar{N_{rec}/N_{gen}}",100,0,1,100,0,8);

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
  EnungRL->outputs.hE_electron_rest       = new TH1F("hE_electron_nungRL_rest",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_electron_ol         = new TH1F("hE_electron_nungRL_ol",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_muon_rest           = new TH1F("hE_muon_nungRL_rest",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_muon_ol             = new TH1F("hE_muon_nungRL_ol",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_pion_rest           = new TH1F("hE_pion_nungRL_rest",";E [GeV];",350,0,350);
  EnungRL->outputs.hE_pion_ol             = new TH1F("hE_pion_nungRL_ol",";E [GeV];",350,0,350);
  EnungRL->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_nungRL",";E [GeV];",750,0,750);
  EnungRL->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_nungRL",";E [GeV];",750,0,750);
  EnungRL->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_nungRL",";# of BCal clusters;",6,0,6);
  EnungRL->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_nungRL",";# of BCal clusters;",6,0,6);
  EnungRL->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_nungRL",";# of BCal clusters;",6,0,6);
  EnungRL->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_nungRL",";Pt [GeV];",100,0,20);
  EnungRL->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_nungRL",";Pt [GeV];",100,0,20);
  EnungRL->outputs.hPt_bcal               = new TH1F("hPt_bcal_nungRL",";Pt [GeV];",100,0,20);
  EnungRL->outputs.hE_bcal                = new TH1F("hE_bcal_nungRL",";E [GeV];",350,0,350);

  SetInputFiles(EnungRL); // see input.C
  EnungRL->process();
  // do something after event loop.
  EnungRL->processAfterEventLoop();

  // bhabha
  Event* EbhabhangLL = new Event;
  EbhabhangLL->setProcessType(bhabhangLL);
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
  EbhabhangLL->outputs.hE_electron_rest       = new TH1F("hE_electron_bhabhangLL_rest",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_electron_ol         = new TH1F("hE_electron_bhabhangLL_ol",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_muon_rest           = new TH1F("hE_muon_bhabhangLL_rest",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_muon_ol             = new TH1F("hE_muon_bhabhangLL_ol",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_pion_rest           = new TH1F("hE_pion_bhabhangLL_rest",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hE_pion_ol             = new TH1F("hE_pion_bhabhangLL_ol",";E [GeV];",350,0,350);
  EbhabhangLL->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_bhabhangLL",";E [GeV];",750,0,750);
  EbhabhangLL->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_bhabhangLL",";E [GeV];",750,0,750);
  EbhabhangLL->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_bhabhangLL",";# of BCal clusters;",6,0,6);
  EbhabhangLL->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_bhabhangLL",";# of BCal clusters;",6,0,6);
  EbhabhangLL->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_bhabhangLL",";# of BCal clusters;",6,0,6);
  EbhabhangLL->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_bhabhangLL",";Pt [GeV];",100,0,20);
  EbhabhangLL->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_bhabhangLL",";Pt [GeV];",100,0,20);
  EbhabhangLL->outputs.hPt_bcal               = new TH1F("hPt_bcal_bhabhangLL",";Pt [GeV];",100,0,20);
  EbhabhangLL->outputs.hE_bcal                = new TH1F("hE_bcal_bhabhangLL",";E [GeV];",350,0,350);

  SetInputFiles(EbhabhangLL); // see input.C
  EbhabhangLL->process();
  // do something after event loop.
  EbhabhangLL->processAfterEventLoop();

  Event* EbhabhangLR = new Event;
  EbhabhangLR->setProcessType(bhabhangLR);
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
  EbhabhangLR->outputs.hE_electron_rest       = new TH1F("hE_electron_bhabhangLR_rest",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_electron_ol         = new TH1F("hE_electron_bhabhangLR_ol",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_muon_rest           = new TH1F("hE_muon_bhabhangLR_rest",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_muon_ol             = new TH1F("hE_muon_bhabhangLR_ol",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_pion_rest           = new TH1F("hE_pion_bhabhangLR_rest",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hE_pion_ol             = new TH1F("hE_pion_bhabhangLR_ol",";E [GeV];",350,0,350);
  EbhabhangLR->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_bhabhangLR",";E [GeV];",750,0,750);
  EbhabhangLR->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_bhabhangLR",";E [GeV];",750,0,750);
  EbhabhangLR->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_bhabhangLR",";# of BCal clusters;",6,0,6);
  EbhabhangLR->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_bhabhangLR",";# of BCal clusters;",6,0,6);
  EbhabhangLR->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_bhabhangLR",";# of BCal clusters;",6,0,6);
  EbhabhangLR->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_bhabhangLR",";Pt [GeV];",100,0,20);
  EbhabhangLR->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_bhabhangLR",";Pt [GeV];",100,0,20);
  EbhabhangLR->outputs.hPt_bcal               = new TH1F("hPt_bcal_bhabhangLR",";Pt [GeV];",100,0,20);
  EbhabhangLR->outputs.hE_bcal                = new TH1F("hE_bcal_bhabhangLR",";E [GeV];",350,0,350);
  SetInputFiles(EbhabhangLR); // see input.C
  EbhabhangLR->process();
  // do something after event loop.
  EbhabhangLR->processAfterEventLoop();

  Event* EbhabhangRL = new Event;
  EbhabhangRL->setProcessType(bhabhangRL);
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
  EbhabhangRL->outputs.hE_electron_rest       = new TH1F("hE_electron_bhabhangRL_rest",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_electron_ol         = new TH1F("hE_electron_bhabhangRL_ol",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_muon_rest           = new TH1F("hE_muon_bhabhangRL_rest",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_muon_ol             = new TH1F("hE_muon_bhabhangRL_ol",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_pion_rest           = new TH1F("hE_pion_bhabhangRL_rest",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hE_pion_ol             = new TH1F("hE_pion_bhabhangRL_ol",";E [GeV];",350,0,350);
  EbhabhangRL->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_bhabhangRL",";E [GeV];",750,0,750);
  EbhabhangRL->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_bhabhangRL",";E [GeV];",750,0,750);
  EbhabhangRL->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_bhabhangRL",";# of BCal clusters;",6,0,6);
  EbhabhangRL->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_bhabhangRL",";# of BCal clusters;",6,0,6);
  EbhabhangRL->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_bhabhangRL",";# of BCal clusters;",6,0,6);
  EbhabhangRL->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_bhabhangRL",";Pt [GeV];",100,0,20);
  EbhabhangRL->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_bhabhangRL",";Pt [GeV];",100,0,20);
  EbhabhangRL->outputs.hPt_bcal               = new TH1F("hPt_bcal_bhabhangRL",";Pt [GeV];",100,0,20);
  EbhabhangRL->outputs.hE_bcal                = new TH1F("hE_bcal_bhabhangRL",";E [GeV];",350,0,350);
  SetInputFiles(EbhabhangRL); // see input.C
  EbhabhangRL->process();
  EbhabhangRL->processAfterEventLoop();

  Event* EbhabhangRR = new Event;
  EbhabhangRR->setProcessType(bhabhangRR);
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
  EbhabhangRR->outputs.hE_electron_rest       = new TH1F("hE_electron_bhabhangRR_rest",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_electron_ol         = new TH1F("hE_electron_bhabhangRR_ol",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_muon_rest           = new TH1F("hE_muon_bhabhangRR_rest",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_muon_ol             = new TH1F("hE_muon_bhabhangRR_ol",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_pion_rest           = new TH1F("hE_pion_bhabhangRR_rest",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hE_pion_ol             = new TH1F("hE_pion_bhabhangRR_ol",";E [GeV];",350,0,350);
  EbhabhangRR->outputs.hEvis_pfo              = new TH1F("hEvis_pfo_bhabhangRR",";E [GeV];",750,0,750);
  EbhabhangRR->outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_bhabhangRR",";E [GeV];",750,0,750);
  EbhabhangRR->outputs.hNBcalClusters         = new TH1F("hNBcalClusters_bhabhangRR",";# of BCal clusters;",6,0,6);
  EbhabhangRR->outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_bhabhangRR",";# of BCal clusters;",6,0,6);
  EbhabhangRR->outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_bhabhangRR",";# of BCal clusters;",6,0,6);
  EbhabhangRR->outputs.hPt_bcal_bcalcoord     = new TH1F("hPt_bcal_bcalcoord_bhabhangRR",";Pt [GeV];",100,0,20);
  EbhabhangRR->outputs.hPtMax_bcal_bcalcoord  = new TH1F("hPtMax_bcal_bcalcoord_bhabhangRR",";Pt [GeV];",100,0,20);
  EbhabhangRR->outputs.hPt_bcal               = new TH1F("hPt_bcal_bhabhangRR",";Pt [GeV];",100,0,20);
  EbhabhangRR->outputs.hE_bcal                = new TH1F("hE_bcal_bhabhangRR",";E [GeV];",350,0,350);
  SetInputFiles(EbhabhangRR); // see input.C
  EbhabhangRR->process();
  // do something after event loop.
  EbhabhangRR->processAfterEventLoop();

  stringstream foutname;
  foutname << "plots/plots.root" << ends;
  cerr << "Output plots have been written into " << foutname.str().data() << endl;
  TFile* output = new TFile(foutname.str().data(),"RECREATE");
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
  EnungLR->outputs.hNBcalClusters1ISR->Write();
  EnungLR->outputs.hNBcalClustersMultiISR->Write();
  EnungLR->outputs.hE_photon->Write();
  EnungLR->outputs.hNrecNgen_photon->Write();
  EnungLR->outputs.gNrecNgenEmc_photon->SetName("gNrecNgenEmc_photon_nungLR");
  EnungLR->outputs.gNrecNgenEmc_photon->Write();
  EnungLR->outputs.gNrecNgenCostheta_photon->SetName("gNrecNgenCostheta_photon_nungLR");
  EnungLR->outputs.gNrecNgenCostheta_photon->Write();
  EnungLR->outputs.hPt_bcal_bcalcoord->Write();
  EnungLR->outputs.hPtMax_bcal_bcalcoord->Write();
  EnungLR->outputs.hPt_bcal->Write();
  EnungLR->outputs.hE_bcal->Write();

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
  EnungRL->outputs.hNBcalClusters1ISR->Write();
  EnungRL->outputs.hNBcalClustersMultiISR->Write();
  EnungRL->outputs.hE_photon->Write();
  EnungRL->outputs.hNrecNgen_photon->Write();
  EnungRL->outputs.gNrecNgenEmc_photon->SetName("gNrecNgenEmc_photon_nungRL");
  EnungRL->outputs.gNrecNgenEmc_photon->Write();
  EnungRL->outputs.gNrecNgenCostheta_photon->SetName("gNrecNgenCostheta_photon_nungRL");
  EnungRL->outputs.gNrecNgenCostheta_photon->Write();
  EnungRL->outputs.hPt_bcal_bcalcoord->Write();
  EnungRL->outputs.hPtMax_bcal_bcalcoord->Write();
  EnungRL->outputs.hPt_bcal->Write();
  EnungRL->outputs.hE_bcal->Write();

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
}

