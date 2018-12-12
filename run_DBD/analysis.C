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

void signalhandler(int singal)
{
  cerr << "signalhandler called. abort." << endl;
  abort(); 
}

void Event::process(string fname)
{
  TFile fin(fname.c_str());
  TTree* data = static_cast<TTree*>(fin.Get("evtdata"));

  int nevents = data->GetEntries();

  int nPhoton_MC = 0;
  int nPhoton_Rec = 0;

  // event loop
  //nevents = 100; // for testing
  //Event event(data);
  SetTree(data);


  _totalNEvt += nevents;
  int nsignalevt = 0;
  for (int ev = 0; ev < nevents; ev++) {

    /*
    // progress bar
    if (ev==nevents-1) {
      cerr << "\r" << fixed << setprecision(0) << "100 %" << flush;
      cerr << setprecision(4) << endl;
    }
    else  cerr << "\r" << fixed << setprecision(0) << float(ev)/float(nevents)*100. << " %" << flush;
    */

    callGetEntry(ev);

    // Efficinecy of ISR photon reconstcution
    if (isAcceptableEvent(ev)) {
      int nrec = 0;
      for (int i = 0; i < npfos; i++) {
        if (pfo_pdg[i]==22) {
	   if (mcr_index[i] == getSignalIndex()) {
	       nrec++;
           } 
        } 
      } 
      if (outputs.hNrecNgen_photon)         outputs.hNrecNgen_photon->Fill(nrec);        // Corresponds to 5.14     
      if (outputs.hNrecNgenEmc_photon)      outputs.hNrecNgenEmc_photon->Fill(getSignalE(),nrec); // Corresponds to 5.15 (a)    
      if (outputs.hNrecNgenCostheta_photon) outputs.hNrecNgenCostheta_photon->Fill(TMath::Cos(getSignalTheta()),nrec); // Corresponds to 5.15 (c)    
    } 


    bool isSignalEvt   = false;
    for (int i = 0; i < npfos; i++) {

      // Check if this event is signal like.
      if (ptmaxphoton_theta > 7./180.*TMath::Pi() && ptmaxphoton_theta < 173./180.*TMath::Pi()) {
        if ( (fabs(ptmaxphoton_phi_bcalcoord/TMath::Pi()*180.)>35. && ptmaxphoton_pt_bcalcoord>1.92 ) ||
             (fabs(ptmaxphoton_phi_bcalcoord/TMath::Pi()*180.)<=35. && ptmaxphoton_pt_bcalcoord>5.65)  ) {
          if (ptmaxphoton_e > 2.) {
            if (outputs.hE_photon) outputs.hE_photon->Fill(ptmaxphoton_e); // Before max energy cut. Corresponds to Fig 5.8     
            if (ptmaxphoton_e < 220.) {
            //if (ptmaxphoton_e < 1000.) {
              isSignalEvt = true;
              //cerr << "This event has signal." << endl;
            } // Max energy cut 
          } // Min energy cut
        } // Pt_max cut depending on |phi| in bcal coordinates.
      } // theta restriction

    } // PFO loop

    if (isSignalEvt) _signalNEvt++;

    //if (!isPassedECut(ev)) continue; 

    // Do something only when this event is signal-like.
    if (isSignalEvt) {


      for (int i = 0; i < npfos; i++) {
        TLorentzVector p4(pfo_px[i],pfo_py[i],pfo_pz[i],pfo_e[i]);
        // e+/e- pt distribution 
        if (abs(pfo_pdg[i])==11) { // select electron/positron 
          if (mcr_isoverlay[i])                outputs.hPt_ep_ol->Fill(p4.Pt());
          else if (mcr_isOriginatedFromISR[i]) outputs.hPt_ep_isr->Fill(p4.Pt());
          //else if ((mcr_pdg[mcr_parentIndex[i][0]]==22&&(mcr_parentIndex[i][0]>=8&&mcr_parentIndex[i][0]<=10))||
          //         (mcr_pdg[mcr_parentIndex[i][1]]==22&&(mcr_parentIndex[i][1]>=8&&mcr_parentIndex[i][1]<=10)) ) outputs.hPt_ep_isr->Fill(p4.Pt());
          else                                 outputs.hPt_ep_other->Fill(p4.Pt());
        }
        // Charged PFO except e+/e- pt distribution 
        else if (fabs(pfo_chrg[i])>0) { // select charged pfo 
          if (mcr_isoverlay[i])                outputs.hPt_pfo_ol->Fill(p4.Pt());
          else if (mcr_isOriginatedFromISR[i]) outputs.hPt_pfo_isr->Fill(p4.Pt());
          //else if ((mcr_pdg[mcr_parentIndex[i][0]]==22&&(mcr_parentIndex[i][0]>=8&&mcr_parentIndex[i][0]<=10))||
          //         (mcr_pdg[mcr_parentIndex[i][1]]==22&&(mcr_parentIndex[i][1]>=8&&mcr_parentIndex[i][1]<=10)) ) outputs.hPt_pfo_isr->Fill(p4.Pt());
          else                                 outputs.hPt_pfo_other->Fill(p4.Pt());
        }

      }

      if (!isPassedPtCut(ev)) continue; 

      // pfo loop
      float esum         = 0.;
      float esum_wo_pi_n = 0.;
      for (int i = 0; i < npfos; i++) {

        // photon E distribution 
        //if (abs(pfo_pdg[i])==22&&!mcr_isOriginatedFromISR[i]) { // select photon 
        //if (abs(pfo_pdg[i])==22&&!(mcr_index[i]>=8&&mcr_index[i]<=10)) { // select photon 
        if (abs(pfo_pdg[i])==22&& i != ptmaxphoton_index ) { // select photon 
          if (mcr_isoverlay[i])                outputs.hE_photon_ol->Fill(pfo_e[i]);
          else if (outputs.hE_photon_electron && abs(mcr_pdg[i])==11) outputs.hE_photon_electron->Fill(pfo_e[i]);// for bhabha only 
          else                                 outputs.hE_photon_rest->Fill(pfo_e[i]);
        }

        // V0 E distribution 
        if (abs(pfo_pdg[i])==310||abs(pfo_pdg[i])==3122) { // select V0 
          if (mcr_isoverlay[i])                outputs.hE_V0_ol->Fill(pfo_e[i]);
          else                                 outputs.hE_V0_rest->Fill(pfo_e[i]);
        }

        // neutron E distribution 
        if (abs(pfo_pdg[i])==2112) { // select neutron 
          if (mcr_isoverlay[i])                outputs.hE_neutron_ol->Fill(pfo_e[i]);
          else                                 outputs.hE_neutron_rest->Fill(pfo_e[i]);
        }

        // electron E distribution 
        if (abs(pfo_pdg[i])==11) { // select electron 
          if (mcr_isoverlay[i])                outputs.hE_electron_ol->Fill(pfo_e[i]);
          else                                 outputs.hE_electron_rest->Fill(pfo_e[i]);
        }

        // muon E distribution 
        if (abs(pfo_pdg[i])==13) { // select muon 
          if (mcr_isoverlay[i])                outputs.hE_muon_ol->Fill(pfo_e[i]);
          else                                 outputs.hE_muon_rest->Fill(pfo_e[i]);
        }

        // pion E distribution 
        if (abs(pfo_pdg[i])==211) { // select pion 
          if (mcr_isoverlay[i])                outputs.hE_pion_ol->Fill(pfo_e[i]);
          else                                 outputs.hE_pion_rest->Fill(pfo_e[i]);
        }

        // Compute energy sum except for ptmaxphoton.
        if (pfo_e[i]>5. && i != ptmaxphoton_index ) { // individual energy cut
          esum += pfo_e[i];
          //if (!(abs(pfo_pdg[i])==211||abs(pfo_pdg[i])==111||abs(pfo_pdg[i])==2112)) {
          //if (!(abs(pfo_pdg[i])==211||abs(pfo_pdg[i])==2112)) {
          if (pfo_pdg[i]==22||abs(pfo_pdg[i])==11||abs(pfo_pdg[i])==13||pfo_pdg[i]==310||abs(pfo_pdg[i])==3122){
            esum_wo_pi_n += pfo_e[i];
          }
        }
      }
      outputs.hEvis_pfo->Fill(esum);
      outputs.hEvis_pfo_wo_pi_n->Fill(esum_wo_pi_n);


      if (isPassedECut(ev) && getNPhotons()>0) { 

        //cerr << "passed event. ev = " << ev << endl;
        outputs.hNBcalClusters->Fill(nbcalclrs);
        if (getNISRPhotons()==1) outputs.hNBcalClusters1ISR->Fill(nbcalclrs);
        else if (getNISRPhotons()>=0) outputs.hNBcalClustersMultiISR->Fill(nbcalclrs); // this is different from the original Moritz's macro.
      }

    }


  } // event loop
}

void Event::processAfterEventLoop()
{
  if (outputs.hNrecNgenEmc_photon&&outputs.hNrecNgenCostheta_photon) { 
    const int    xbins_e = outputs.hNrecNgenEmc_photon->GetNbinsX();
    double x_min_e = outputs.hNrecNgenEmc_photon->GetXaxis()->GetBinLowEdge(1);
    double x_max_e = outputs.hNrecNgenEmc_photon->GetXaxis()->GetBinUpEdge(xbins_e);
    const int    ybins_e = outputs.hNrecNgenEmc_photon->GetNbinsY();
    double y_min_e = outputs.hNrecNgenEmc_photon->GetYaxis()->GetBinLowEdge(1);
    double y_max_e = outputs.hNrecNgenEmc_photon->GetYaxis()->GetBinUpEdge(ybins_e);
    const int    xbins_cos = outputs.hNrecNgenCostheta_photon->GetNbinsX();
    double x_min_cos = outputs.hNrecNgenCostheta_photon->GetXaxis()->GetBinLowEdge(1);
    double x_max_cos = outputs.hNrecNgenCostheta_photon->GetXaxis()->GetBinUpEdge(xbins_cos);
    const int    ybins_cos = outputs.hNrecNgenCostheta_photon->GetNbinsY();
    double y_min_cos = outputs.hNrecNgenCostheta_photon->GetYaxis()->GetBinLowEdge(1);
    double y_max_cos = outputs.hNrecNgenCostheta_photon->GetYaxis()->GetBinUpEdge(ybins_cos);

    double x_e[xbins_e], xerr_e[xbins_e], y_e[xbins_e], yerr_e[xbins_e];
    for (int ix = 1; ix <= xbins_e; ix++) {
      x_e[ix] = outputs.hNrecNgenEmc_photon->GetXaxis()->GetBinCenter(ix);
      xerr_e[ix] = outputs.hNrecNgenEmc_photon->GetXaxis()->GetBinWidth(ix)/TMath::Sqrt(12);
      TH1F h_y_e("h_y_e","",ybins_e,y_min_e,y_max_e);
      for (int iy = 1; iy <= ybins_e; iy++) {
        for (int icontent = 0; icontent < outputs.hNrecNgenEmc_photon->GetBinContent(ix,iy); icontent++) {
          h_y_e.Fill(outputs.hNrecNgenEmc_photon->GetYaxis()->GetBinCenter(iy)); 
        }
      }
      y_e[ix] = h_y_e.GetMean();
      yerr_e[ix] = h_y_e.GetRMS() / TMath::Sqrt(h_y_e.GetEntries());
      //yerr_e[ix] = TMath::Sqrt(h_y_e.GetRMS()*h_y_e.GetRMS()-h_y_e.GetMean()*h_y_e.GetMean()) / TMath::Sqrt(h_y_e.GetEntries());
    }
    outputs.gNrecNgenEmc_photon = new TGraphErrors(xbins_e,x_e,y_e,xerr_e,yerr_e);
    outputs.gNrecNgenEmc_photon->SetTitle(";E_{#gamma,MC} [GeV/c];#bar{N_{rec}/N_{gen}}");

    double x_cos[xbins_cos], xerr_cos[xbins_cos], y_cos[xbins_cos], yerr_cos[xbins_cos];
    for (int ix = 1; ix <= xbins_cos; ix++) {
      x_cos[ix] = outputs.hNrecNgenCostheta_photon->GetXaxis()->GetBinCenter(ix);
      xerr_cos[ix] = outputs.hNrecNgenCostheta_photon->GetXaxis()->GetBinWidth(ix)/TMath::Sqrt(12);
      TH1F h_y_cos("h_y_cos","",ybins_cos,y_min_cos,y_max_cos);
      for (int iy = 1; iy <= ybins_cos; iy++) {
        for (int icontent = 0; icontent < outputs.hNrecNgenCostheta_photon->GetBinContent(ix,iy); icontent++) {
          h_y_cos.Fill(outputs.hNrecNgenCostheta_photon->GetYaxis()->GetBinCenter(iy)); 
        }
      }
      y_cos[ix] = h_y_cos.GetMean();
      yerr_cos[ix] = h_y_cos.GetRMS() / TMath::Sqrt(h_y_cos.GetEntries());
      //yerr_cos[ix] = TMath::Sqrt(h_y_cos.GetRMS()*h_y_cos.GetRMS()-h_y_cos.GetMean()*h_y_cos.GetMean()) / TMath::Sqrt(h_y_cos.GetEntries());
      //y_cos[ix] = fitfunc.GetParameter(1);
      //yerr_cos[ix] = fitfunc.GetParameter(2)/TMath::Sqrt(h_y_cos.GetEntries());
    }
    outputs.gNrecNgenCostheta_photon = new TGraphErrors(xbins_cos,x_cos,y_cos,xerr_cos,yerr_cos);
    outputs.gNrecNgenCostheta_photon->SetTitle(";cos#theta_{#gamma,MC};#bar{N_{rec}/N_{gen}}");


    cerr << "Total N events = " << _totalNEvt << endl;
    cerr << "Singal Efficincy = " << float(_signalNEvt)/float(_totalNEvt) << endl;
  }
}

void analysis()
{
  signal(SIGINT,signalhandler);

  // Define Event object which contains analyses methods and output histograms.
  Event nung;
  nung.outputs.hE_photon           = new TH1F("hE_photon",";E [GeV/c];",300,0,300);
  nung.outputs.hNrecNgen_photon    = new TH1F("hNrecNgen_photon",";# #gamma_{rec}/#gamma_{gen};",8,0,8);
  nung.outputs.hNrecNgenEmc_photon = new TH2F("hNrecNgenEmc_photon",";E_{#gamma,MC} [GeV/c];#bar{N_{rec}/N_{gen}}",100,0,250,100,0,8);
  nung.outputs.hNrecNgenCostheta_photon = new TH2F("hNrecNgenCostheta_photon",";cos#theta_{#gamma,MC};#bar{N_{rec}/N_{gen}}",100,0,1,100,0,8);

  nung.outputs.hPt_ep_isr             = new TH1F("hPt_ep_nung_isr"   ,";Pt [GeV/c];",250,0,250);
  nung.outputs.hPt_ep_ol              = new TH1F("hPt_ep_nung_ol"    ,";Pt [GeV/c];",250,0,250);
  nung.outputs.hPt_ep_other           = new TH1F("hPt_ep_nung_other" ,";Pt [GeV/c];",250,0,250);
  nung.outputs.hPt_pfo_isr            = new TH1F("hPt_pfo_nung_isr"  ,";Pt [GeV/c];",250,0,250);
  nung.outputs.hPt_pfo_ol             = new TH1F("hPt_pfo_nung_ol"   ,";Pt [GeV/c];",250,0,250);
  nung.outputs.hPt_pfo_other          = new TH1F("hPt_pfo_nung_other",";Pt [GeV/c];",250,0,250);
  nung.outputs.hE_photon_rest         = new TH1F("hE_photon_nung_rest",";E [GeV];",350,0,350);
  nung.outputs.hE_photon_ol           = new TH1F("hE_photon_nung_ol",";E [GeV];",350,0,350);
  nung.outputs.hE_V0_rest             = new TH1F("hE_V0_nung_rest",";E [GeV];",350,0,350);
  nung.outputs.hE_V0_ol               = new TH1F("hE_V0_nung_ol",";E [GeV];",350,0,350);
  nung.outputs.hE_neutron_rest        = new TH1F("hE_neutron_nung_rest",";E [GeV];",350,0,350);
  nung.outputs.hE_neutron_ol          = new TH1F("hE_neutron_nung_ol",";E [GeV];",350,0,350);
  nung.outputs.hE_electron_rest       = new TH1F("hE_electron_nung_rest",";E [GeV];",350,0,350);
  nung.outputs.hE_electron_ol         = new TH1F("hE_electron_nung_ol",";E [GeV];",350,0,350);
  nung.outputs.hE_muon_rest           = new TH1F("hE_muon_nung_rest",";E [GeV];",350,0,350);
  nung.outputs.hE_muon_ol             = new TH1F("hE_muon_nung_ol",";E [GeV];",350,0,350);
  nung.outputs.hE_pion_rest           = new TH1F("hE_pion_nung_rest",";E [GeV];",350,0,350);
  nung.outputs.hE_pion_ol             = new TH1F("hE_pion_nung_ol",";E [GeV];",350,0,350);
  nung.outputs.hEvis_pfo              = new TH1F("hEvis_pfo_nung",";E [GeV];",750,0,750);
  nung.outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_nung",";E [GeV];",750,0,750);
  nung.outputs.hNBcalClusters         = new TH1F("hNBcalClusters_nung",";# of BCal clusters;",6,0,6);
  nung.outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_nung",";# of BCal clusters;",6,0,6);
  nung.outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_nung",";# of BCal clusters;",6,0,6);


  int nmaxfiles_nung = 100; // Stop reading when a file doesn't exist. Specify a small number for testing.
  for (int i = 1; i <= nmaxfiles_nung; i++) {
      // nung LR
      stringstream fname;
      fname << "nung/root/dbd_500GeV.nung.eL.pR_" << i << ".root" << ends;
      if (gSystem->AccessPathName(fname.str().data())) break;
      cerr << "Loading " << fname.str().data() << " ... " << endl;
      nung.process(fname.str().data());
  }

  for (int i = 1; i <= nmaxfiles_nung; i++) {
      // nung RL
      stringstream fname;
      fname << "nung/root/dbd_500GeV.nung.eR.pL_" << i << ".root" << ends;
      if (gSystem->AccessPathName(fname.str().data())) break;
      cerr << "Loading " << fname.str().data() << " ... " << endl;
      nung.process(fname.str().data());
  }

  // do something after event loop.
  nung.processAfterEventLoop();

  // bhabha
  Event bhabhang;
  bhabhang.outputs.hPt_ep_isr             = new TH1F("hPt_ep_bhabhang_isr"   ,";Pt [GeV/c];",250,0,250);
  bhabhang.outputs.hPt_ep_ol              = new TH1F("hPt_ep_bhabhang_ol"    ,";Pt [GeV/c];",250,0,250);
  bhabhang.outputs.hPt_ep_other           = new TH1F("hPt_ep_bhabhang_other" ,";Pt [GeV/c];",250,0,250);
  bhabhang.outputs.hPt_pfo_isr            = new TH1F("hPt_pfo_bhabhang_isr"  ,";Pt [GeV/c];",250,0,250);
  bhabhang.outputs.hPt_pfo_ol             = new TH1F("hPt_pfo_bhabhang_ol"   ,";Pt [GeV/c];",250,0,250);
  bhabhang.outputs.hPt_pfo_other          = new TH1F("hPt_pfo_bhabhang_other",";Pt [GeV/c];",250,0,250);
  bhabhang.outputs.hE_photon_rest         = new TH1F("hE_photon_bhabhang_rest",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_photon_ol           = new TH1F("hE_photon_bhabhang_ol",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_photon_electron     = new TH1F("hE_photon_bhabhang_electron",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_V0_rest             = new TH1F("hE_V0_bhabhang_rest",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_V0_ol               = new TH1F("hE_V0_bhabhang_ol",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_neutron_rest        = new TH1F("hE_neutron_bhabhang_rest",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_neutron_ol          = new TH1F("hE_neutron_bhabhang_ol",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_electron_rest       = new TH1F("hE_electron_bhabhang_rest",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_electron_ol         = new TH1F("hE_electron_bhabhang_ol",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_muon_rest           = new TH1F("hE_muon_bhabhang_rest",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_muon_ol             = new TH1F("hE_muon_bhabhang_ol",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_pion_rest           = new TH1F("hE_pion_bhabhang_rest",";E [GeV];",350,0,350);
  bhabhang.outputs.hE_pion_ol             = new TH1F("hE_pion_bhabhang_ol",";E [GeV];",350,0,350);
  bhabhang.outputs.hEvis_pfo              = new TH1F("hEvis_pfo_bhabhang",";E [GeV];",750,0,750);
  bhabhang.outputs.hEvis_pfo_wo_pi_n      = new TH1F("hEvis_pfo_wo_pi_n_bhabhang",";E [GeV];",750,0,750);
  bhabhang.outputs.hNBcalClusters         = new TH1F("hNBcalClusters_bhabhang",";# of BCal clusters;",6,0,6);
  bhabhang.outputs.hNBcalClusters1ISR     = new TH1F("hNBcalClusters1ISR_bhabhang",";# of BCal clusters;",6,0,6);
  bhabhang.outputs.hNBcalClustersMultiISR = new TH1F("hNBcalClustersMultiISR_bhabhang",";# of BCal clusters;",6,0,6);

  int nmaxfiles_bhabhang = 100;
  for (int i = 1; i <= nmaxfiles_bhabhang; i++) {
      // bhabhang LL
      stringstream fname;
      fname << "bhabhang/root/dbd_500GeV.bhabhang.eL.pL_" << i << ".root" << ends;
      if (gSystem->AccessPathName(fname.str().data())) break;
      cerr << "Loading " << fname.str().data() << " ... " << endl;
      bhabhang.process(fname.str().data());
  }
  for (int i = 1; i <= nmaxfiles_bhabhang; i++) {
      // bhabhang LR
      stringstream fname;
      fname << "bhabhang/root/dbd_500GeV.bhabhang.eL.pR_" << i << ".root" << ends;
      if (gSystem->AccessPathName(fname.str().data())) break;
      cerr << "Loading " << fname.str().data() << " ... " << endl;
      bhabhang.process(fname.str().data());
  }
  for (int i = 1; i <= nmaxfiles_bhabhang; i++) {
      // bhabhang RL
      stringstream fname;
      fname << "bhabhang/root/dbd_500GeV.bhabhang.eR.pL_" << i << ".root" << ends;
      if (gSystem->AccessPathName(fname.str().data())) break;
      cerr << "Loading " << fname.str().data() << " ... " << endl;
      bhabhang.process(fname.str().data());
  }
  for (int i = 1; i <= nmaxfiles_bhabhang; i++) {
      // bhabhang RR
      stringstream fname;
      fname << "bhabhang/root/dbd_500GeV.bhabhang.eR.pR_" << i << ".root" << ends;
      if (gSystem->AccessPathName(fname.str().data())) break;
      cerr << "Loading " << fname.str().data() << " ... " << endl;
      bhabhang.process(fname.str().data());
  }

  bhabhang.processAfterEventLoop();

  stringstream foutname;
  foutname << "plots/plots.root" << ends;
  cerr << "Output plots have been written into " << foutname.str().data() << endl;
  TFile* output = new TFile(foutname.str().data(),"RECREATE");
  nung.outputs.hPt_ep_other->Write();
  nung.outputs.hPt_ep_ol->Write();
  nung.outputs.hPt_ep_isr->Write();
  bhabhang.outputs.hPt_ep_ol->Write();
  bhabhang.outputs.hPt_ep_isr->Write();
  bhabhang.outputs.hPt_ep_other->Write();
  nung.outputs.hPt_pfo_other->Write();
  nung.outputs.hPt_pfo_ol->Write();
  nung.outputs.hPt_pfo_isr->Write();
  bhabhang.outputs.hPt_pfo_ol->Write();
  bhabhang.outputs.hPt_pfo_isr->Write();
  bhabhang.outputs.hPt_pfo_other->Write();
  nung.outputs.hE_photon_ol->Write();
  nung.outputs.hE_photon_rest->Write();
  bhabhang.outputs.hE_photon_ol->Write();
  bhabhang.outputs.hE_photon_electron->Write();
  bhabhang.outputs.hE_photon_rest->Write();
  nung.outputs.hE_V0_ol->Write();
  nung.outputs.hE_V0_rest->Write();
  bhabhang.outputs.hE_V0_ol->Write();
  bhabhang.outputs.hE_V0_rest->Write();
  nung.outputs.hE_neutron_ol->Write();
  nung.outputs.hE_neutron_rest->Write();
  bhabhang.outputs.hE_neutron_ol->Write();
  bhabhang.outputs.hE_neutron_rest->Write();
  nung.outputs.hE_electron_ol->Write();
  nung.outputs.hE_electron_rest->Write();
  bhabhang.outputs.hE_electron_ol->Write();
  bhabhang.outputs.hE_electron_rest->Write();
  nung.outputs.hE_muon_ol->Write();
  nung.outputs.hE_muon_rest->Write();
  bhabhang.outputs.hE_muon_ol->Write();
  bhabhang.outputs.hE_muon_rest->Write();
  nung.outputs.hE_pion_ol->Write();
  nung.outputs.hE_pion_rest->Write();
  bhabhang.outputs.hE_pion_ol->Write();
  bhabhang.outputs.hE_pion_rest->Write();
  nung.outputs.hEvis_pfo->Write();
  bhabhang.outputs.hEvis_pfo->Write();
  nung.outputs.hEvis_pfo_wo_pi_n->Write();
  bhabhang.outputs.hEvis_pfo_wo_pi_n->Write();
  nung.outputs.hNBcalClusters1ISR->Write();
  nung.outputs.hNBcalClustersMultiISR->Write();
  bhabhang.outputs.hNBcalClusters->Write();
  nung.outputs.hE_photon->Write();
  nung.outputs.hNrecNgen_photon->Write();
  nung.outputs.gNrecNgenEmc_photon->Write();
  nung.outputs.gNrecNgenCostheta_photon->Write();
}

