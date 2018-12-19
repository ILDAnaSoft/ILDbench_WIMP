#ifndef __EVENTSELECTION__
#define __EVENTSELECTION__

const int NMAX = 10000;

enum ProcessType {
  nungLR,
  nungRL,
  bhabhangLL,
  bhabhangLR,
  bhabhangRL,
  bhabhangRR
};

enum CutType {
 nocut,
 sigdef,
 ptcut,
 ecut,
 bcalveto 
};

class Event
{
   public:
        Event() : _currentEv(-1)
                  {}
	void SetTree(TTree* T) { 
           _T = T;
           // MCParticle
           _T->SetBranchAddress("nmcps",&nmcps);
           _T->SetBranchAddress("mcp_pdg",mcp_pdg);
           _T->SetBranchAddress("mcp_index",mcp_index);
           _T->SetBranchAddress("mcp_nparents",mcp_nparents);
           _T->SetBranchAddress("mcp_parentIndex",mcp_parentIndex);
           _T->SetBranchAddress("mcp_ndaughters",mcp_ndaughters);
           _T->SetBranchAddress("mcp_daughterIndex",mcp_daughterIndex);
           _T->SetBranchAddress("mcp_e",mcp_e);
           _T->SetBranchAddress("mcp_phi",mcp_phi);
           _T->SetBranchAddress("mcp_theta",mcp_theta);
           _T->SetBranchAddress("mcp_endx",mcp_endx);
           _T->SetBranchAddress("mcp_endy",mcp_endy);
           _T->SetBranchAddress("mcp_endz",mcp_endz);
           // PFO
           _T->SetBranchAddress("npfos",&npfos);
           _T->SetBranchAddress("pfo_pdg",pfo_pdg);
           _T->SetBranchAddress("pfo_chrg",pfo_chrg);
           _T->SetBranchAddress("pfo_e",pfo_e);
           _T->SetBranchAddress("pfo_px",pfo_px);
           _T->SetBranchAddress("pfo_py",pfo_py);
           _T->SetBranchAddress("pfo_pz",pfo_pz);
           _T->SetBranchAddress("pfo_phi",pfo_phi);
           _T->SetBranchAddress("pfo_theta",pfo_theta);
           _T->SetBranchAddress("pfo_cal_x",pfo_cal_x);
           _T->SetBranchAddress("pfo_cal_y",pfo_cal_y);
           _T->SetBranchAddress("pfo_cal_z",pfo_cal_z);
           _T->SetBranchAddress("pfo_ecal_e",pfo_ecal_e);
           _T->SetBranchAddress("pfo_hcal_e",pfo_hcal_e);
           _T->SetBranchAddress("emaxphoton_index",&emaxphoton_index);
           _T->SetBranchAddress("emaxphoton_e",&emaxphoton_e);
           _T->SetBranchAddress("emaxphoton_theta",&emaxphoton_theta);
           _T->SetBranchAddress("emaxphoton_pt_bcalcoord",&emaxphoton_pt_bcalcoord);
           _T->SetBranchAddress("emaxphoton_phi_bcalcoord",&emaxphoton_phi_bcalcoord);
           _T->SetBranchAddress("ptmaxphoton_index",&ptmaxphoton_index);
           _T->SetBranchAddress("ptmaxphoton_e",&ptmaxphoton_e);
           _T->SetBranchAddress("ptmaxphoton_theta",&ptmaxphoton_theta);
           _T->SetBranchAddress("ptmaxphoton_pt_bcalcoord",&ptmaxphoton_pt_bcalcoord);
           _T->SetBranchAddress("ptmaxphoton_phi_bcalcoord",&ptmaxphoton_phi_bcalcoord);
           // RecoMCTruthLink 
           _T->SetBranchAddress("mcr_pdg",mcr_pdg);
           _T->SetBranchAddress("mcr_weight",mcr_weight);
           _T->SetBranchAddress("mcr_index",mcr_index);
           _T->SetBranchAddress("mcr_nparents",mcr_nparents);
           _T->SetBranchAddress("mcr_parentIndex",mcr_parentIndex);
           _T->SetBranchAddress("mcr_e",mcr_e);
           _T->SetBranchAddress("mcr_phi",mcr_phi);
           _T->SetBranchAddress("mcr_theta",mcr_theta);
           _T->SetBranchAddress("mcr_isoverlay",mcr_isoverlay);
           _T->SetBranchAddress("mcr_isOriginatedFromISR",mcr_isOriginatedFromISR);
           // BCal cluster
           _T->SetBranchAddress("nbcalclrs",&nbcalclrs);
           _T->SetBranchAddress("bcal_e",bcal_e);
           _T->SetBranchAddress("bcal_phi",bcal_phi);
           _T->SetBranchAddress("bcal_theta",bcal_theta);
           _T->SetBranchAddress("bcal_x",bcal_x);
           _T->SetBranchAddress("bcal_y",bcal_y);
           _T->SetBranchAddress("bcal_z",bcal_z);
           _T->SetBranchAddress("bcal_pt_bcalcoord",bcal_pt_bcalcoord);
        }

        void callGetEntry(int ev) {

          if (_currentEv==ev) return; // Do nothing if this function has been called once.

          _T->GetEntry(ev);
          _currentEv = ev; 

          // Check if this event is a signal-like event.
          int nAcceptablePhoton_MC_per_evt = 0;
          signal_index = -1.;
          signal_e = -1.;
          _nISRPhotons = 0;
          for (int i = 0; i < nmcps; i++) {
            if (mcp_pdg[i]==22 && mcp_parentIndex[i][0]==2&&mcp_parentIndex[i][1]==3) { // select only initial ones
              _nISRPhotons++;
              if (mcp_ndaughters[i] < 2 && mcp_e[i]>2. && mcp_theta[i]>7/180.*TMath::Pi() && mcp_theta[i]<173/180.*TMath::Pi()) { 
                // select photon (non converted photon only)
                nAcceptablePhoton_MC_per_evt++;
                signal_index = i;
                signal_e = mcp_e[i];
                signal_phi = mcp_phi[i];
                signal_theta = mcp_theta[i];
              }
            }
          }
          // Define signal events:
          _isAcceptableEvent = (_nISRPhotons==1&&nAcceptablePhoton_MC_per_evt==1); 

          // PFO loop
          _nPhotons = 0;
          for (int i = 0; i < npfos; i++) {
            if (pfo_pdg[i]==22) _nPhotons++;
          }

        }

        bool isAcceptableEvent(int ev) {
          callGetEntry(ev);
          return _isAcceptableEvent;
        }

        bool isPassedPtCut(int ev) {
          callGetEntry(ev);
          for (int i = 0; i < npfos; i++) {
            TLorentzVector p4(pfo_px[i],pfo_py[i],pfo_pz[i],pfo_e[i]);
            if (abs(pfo_pdg[i])==11) { // electron/positron cases
              if (p4.Pt()>0.5) return false;
            } else if (fabs(pfo_chrg[i])>0) { // other charged pfos
              if (p4.Pt()>3.) return false;
            } 
          }
          return true;
        }

        bool isPassedECut(int ev) {
          callGetEntry(ev);
          float esum = 0.;
          float esum_wo_pi_n = 0.;
          for (int i = 0; i < npfos; i++) {
            if (i==ptmaxphoton_index) continue;
            if (pfo_e[i]>5.) { // only consider PFOs having energy over 5GeV.
              esum += pfo_e[i];
              //if (!(abs(pfo_pdg[i])==211||abs(pfo_pdg[i])==2112)) {
              if (pfo_pdg[i]==22||abs(pfo_pdg[i])==11||abs(pfo_pdg[i])==13||pfo_pdg[i]==310||abs(pfo_pdg[i])==3122){
                esum_wo_pi_n += pfo_e[i];
              }
            }
          }
          if (esum>30.) return false;
          if (esum_wo_pi_n>10.) return false;
          return true;
        }

        int getSignalIndex() const { 
          if (signal_index>0) return signal_index; 
          else return -1.;
        }

        float getSignalE() const { 
          if (signal_e>0) return signal_e; 
          else return -1.;
        }

        float getSignalTheta() const { 
          if (signal_e>0) return signal_theta; 
          else return -1.;
        }

        int getNISRPhotons() const { return _nISRPhotons; }

        int getNPhotons() const { return _nPhotons; }

        void setProcessType(ProcessType type) { _ptype = type; }

        ProcessType getProcessType() const { return _ptype; }

        void process();

        void process(string fname);

        void processAfterEventLoop();

        void clearFileList() { inputfiles.clear(); };

        void addToFileList(string file) { inputfiles.push_back(file); };

        struct Outputs
        {
          Outputs() : hCutStats(0),
                      hE_photon(0),
                      hNrecNgen_photon(0),
                      hNrecNgenEmc_photon(0),
                      hNrecNgenCostheta_photon(0),
                      gNrecNgenEmc_photon(0),
                      gNrecNgenCostheta_photon(0),
                      hPt_ep_isr(0),
                      hPt_ep_ol(0),
                      hPt_ep_other(0),
                      hPt_pfo_isr(0),
                      hPt_pfo_ol(0),
                      hPt_pfo_other(0),
                      hE_photon_ol(0),
                      hE_photon_electron(0),
                      hE_photon_rest(0),
                      hE_V0_ol(0),
                      hE_V0_rest(0),
                      hE_neutron_ol(0),
                      hE_neutron_rest(0),
                      hE_electron_ol(0),
                      hE_electron_rest(0),
                      hE_muon_ol(0),
                      hE_muon_rest(0),
                      hE_pion_ol(0),
                      hE_pion_rest(0),
                      hEvis_pfo(0),
                      hEvis_pfo_wo_pi_n(0),
                      hNBcalClusters(0),
                      hNBcalClusters1ISR(0),
                      hNBcalClustersMultiISR(0),
                      hPt_bcal_bcalcoord(0),
                      hPtMax_bcal_bcalcoord(0),
                      hPt_bcal(0),
                      hE_bcal(0) {}

          TH1F* hCutStats;

          TH1F* hE_photon;
          TH1F* hNrecNgen_photon;
          TH2F* hNrecNgenEmc_photon;
          TH2F* hNrecNgenCostheta_photon;
          TGraphErrors* gNrecNgenEmc_photon;
          TGraphErrors* gNrecNgenCostheta_photon;

          TH1F* hPt_ep_isr;
          TH1F* hPt_ep_ol;
          TH1F* hPt_ep_other;
          TH1F* hPt_pfo_isr;
          TH1F* hPt_pfo_ol;
          TH1F* hPt_pfo_other;
          TH1F* hE_photon_ol;
          TH1F* hE_photon_electron;
          TH1F* hE_photon_rest;
          TH1F* hE_V0_ol;
          TH1F* hE_V0_rest;
          TH1F* hE_neutron_ol;
          TH1F* hE_neutron_rest;
          TH1F* hE_electron_ol;
          TH1F* hE_electron_rest;
          TH1F* hE_muon_ol;
          TH1F* hE_muon_rest;
          TH1F* hE_pion_ol;
          TH1F* hE_pion_rest;
          TH1F* hEvis_pfo;
          TH1F* hEvis_pfo_wo_pi_n;
          TH1F* hNBcalClusters;
          TH1F* hNBcalClusters1ISR;
          TH1F* hNBcalClustersMultiISR;

          TH1F* hPt_bcal_bcalcoord;
          TH1F* hPtMax_bcal_bcalcoord;
          TH1F* hPt_bcal;
          TH1F* hE_bcal;
        };

        Outputs outputs;

   private:
        ProcessType _ptype;
        float       _xsec;
        int         _nTotalEntries;
        vector<string> inputfiles;
	TTree* _T;
        int _currentEv;
        // MCParticle
	int signal_index;
        float signal_e, signal_phi, signal_theta;
        bool _isAcceptableEvent;
        bool _isSignalLikeEvent;
        int _nISRPhotons;
        int _nPhotons;

   public:
        int nmcps, mcp_pdg[NMAX], mcp_index[NMAX];
        int mcp_nparents[NMAX], mcp_parentIndex[NMAX][10];
        int mcp_ndaughters[NMAX], mcp_daughterIndex[NMAX][10];
        float mcp_e[NMAX], mcp_phi[NMAX], mcp_theta[NMAX];
        float mcp_endx[NMAX], mcp_endy[NMAX], mcp_endz[NMAX];
        bool mcp_isOriginatedFromISR[NMAX], mcp_isoverlay[NMAX];
        int npfos, pfo_pdg[NMAX],mcr_pdg[NMAX], mcr_index[NMAX], mcr_nparents[NMAX], mcr_parentIndex[NMAX][10];
        float pfo_e[NMAX], pfo_px[NMAX], pfo_py[NMAX], pfo_pz[NMAX], pfo_phi[NMAX], pfo_theta[NMAX];
        float pfo_cal_x[NMAX],  pfo_cal_y[NMAX],  pfo_cal_z[NMAX];
        float pfo_ecal_e[NMAX], pfo_hcal_e[NMAX];
        float pfo_chrg[NMAX];
        float mcr_e[NMAX], mcr_phi[NMAX], mcr_theta[NMAX], mcr_weight[NMAX];
        bool mcr_isOriginatedFromISR[NMAX], mcr_isoverlay[NMAX];
        int nbcalclrs;
        float bcal_e[NMAX], bcal_phi[NMAX], bcal_theta[NMAX];
        float bcal_x[NMAX], bcal_y[NMAX], bcal_z[NMAX];
        float bcal_px_bcalcoord[NMAX], bcal_pt_bcalcoord[NMAX];
        int   emaxphoton_index, ptmaxphoton_index;
        float emaxphoton_e, ptmaxphoton_pt_bcalcoord, emaxphoton_pt_bcalcoord, ptmaxphoton_e;
        float ptmaxphoton_phi_bcalcoord, emaxphoton_phi_bcalcoord;
        float ptmaxphoton_theta, emaxphoton_theta;
};

void Event::process()
{
  for (int i = 0; i < inputfiles.size(); i++ ) {
    cerr << "Loading " << inputfiles[i] << " ";
    process(inputfiles[i]);
  }
}

void Event::process(string fname)
{
  TFile fin(fname.c_str());
  TTree* data = static_cast<TTree*>(fin.Get("evtdata"));

  int nevents = data->GetEntries();
  int nPhoton_MC = 0;
  int nPhoton_Rec = 0;

  SetTree(data);

  if (outputs.hCutStats) {
    // These labels will not be saved in the output root file with ROOT6.08/06, 
    // but this officially has been fixed (May 2017).
    outputs.hCutStats->GetXaxis()->SetBinLabel(1,"No cut"); 
    outputs.hCutStats->GetXaxis()->SetBinLabel(2,"Sig. def."); 
    outputs.hCutStats->GetXaxis()->SetBinLabel(3,"Pt cut"); 
    outputs.hCutStats->GetXaxis()->SetBinLabel(4,"E cut"); 
    outputs.hCutStats->GetXaxis()->SetBinLabel(5,"Bcal veto"); 
  }

  const int ms1 = int(nevents/4);
  const int ms2 = ms1*2;
  const int ms3 = ms1*3;
  // event loop
  for (int ev = 0; ev < nevents; ev++) {

    if      (ev == ms1) cerr << ".";
    else if (ev == ms2) cerr << ".";
    else if (ev == ms3) cerr << "." << endl;

    if (outputs.hCutStats) outputs.hCutStats->Fill(nocut); 

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
      if (outputs.hNrecNgen_photon)         outputs.hNrecNgen_photon->Fill(nrec);                                      // Corresponds to Fig. 5.14     
      if (outputs.hNrecNgenEmc_photon)      outputs.hNrecNgenEmc_photon->Fill(getSignalE(),nrec);                      // Corresponds to Fig. 5.15 (a)    
      if (outputs.hNrecNgenCostheta_photon) outputs.hNrecNgenCostheta_photon->Fill(TMath::Cos(getSignalTheta()),nrec); // Corresponds to Fig. 5.15 (c)    
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
            //if (ptmaxphoton_e < 1000.) { // Effictively remove the cut on maximum energy.
              isSignalEvt = true;
            } // Max energy cut 
          } // Min energy cut
        } // Pt_max cut depending on |phi| in bcal coordinates.
      } // theta restriction

    } // PFO loop


    //if (!isPassedECut(ev)) continue; 


    // Proceed only when this event is signal-like.
    if (isSignalEvt) {

      if (outputs.hCutStats) outputs.hCutStats->Fill(sigdef); 

      for (int i = 0; i < npfos; i++) {
        TLorentzVector p4(pfo_px[i],pfo_py[i],pfo_pz[i],pfo_e[i]);
        // e+/e- pt distribution 
        if (abs(pfo_pdg[i])==11) { // select electron/positron 
          if (mcr_isoverlay[i])                outputs.hPt_ep_ol->Fill(p4.Pt());
          //else if (mcr_isOriginatedFromISR[i]) outputs.hPt_ep_isr->Fill(p4.Pt());
          else if ((mcp_pdg[mcr_parentIndex[i][0]]==22&&(mcr_parentIndex[i][0]>=8&&mcr_parentIndex[i][0]<=11))||
                   (mcp_pdg[mcr_parentIndex[i][1]]==22&&(mcr_parentIndex[i][1]>=8&&mcr_parentIndex[i][1]<=11)) ) outputs.hPt_ep_isr->Fill(p4.Pt());
          else                                 outputs.hPt_ep_other->Fill(p4.Pt());
        }
        // Charged PFO except e+/e- pt distribution 
        else if (fabs(pfo_chrg[i])>0) { // select charged pfo 
          if (mcr_isoverlay[i])                outputs.hPt_pfo_ol->Fill(p4.Pt());
          //else if (mcr_isOriginatedFromISR[i]) outputs.hPt_pfo_isr->Fill(p4.Pt());
          else if ((mcp_pdg[mcr_parentIndex[i][0]]==22&&(mcr_parentIndex[i][0]>=8&&mcr_parentIndex[i][0]<=11))||
                   (mcp_pdg[mcr_parentIndex[i][1]]==22&&(mcr_parentIndex[i][1]>=8&&mcr_parentIndex[i][1]<=11)) ) outputs.hPt_pfo_isr->Fill(p4.Pt());
          else                                 outputs.hPt_pfo_other->Fill(p4.Pt());
        }

      }

      if (!isPassedPtCut(ev)) continue; 

      if (outputs.hCutStats) outputs.hCutStats->Fill(ptcut); 

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
        if (pfo_pdg[i]==310||pfo_pdg[i]==3122) { // select V0 
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
          if (pfo_pdg[i]==22||abs(pfo_pdg[i])==11||abs(pfo_pdg[i])==13||pfo_pdg[i]==310||pfo_pdg[i]==3122){
            esum_wo_pi_n += pfo_e[i];
          }
        }
      }
      outputs.hEvis_pfo->Fill(esum);
      outputs.hEvis_pfo_wo_pi_n->Fill(esum_wo_pi_n);


      if (isPassedECut(ev) && getNPhotons()>0) { 
        if (outputs.hCutStats) outputs.hCutStats->Fill(ecut); 

#if 1   //FIXME. Temporary treatment for IDR sample (20181219)  
        // Cluster threshold was wrongly set to be 0.06, but this should be 32.
        // The energy cut will be performed here.
        const float bcal_e_threshold = 32.;
        int nbcalclrs_after_ecut = 0;
        bool pass = true;
        for (int ibcal = 0; ibcal < nbcalclrs; ibcal++) {
          if (bcal_e[ibcal]>bcal_e_threshold) nbcalclrs_after_ecut++;
        }
#endif

        //cerr << "passed event. ev = " << ev << endl;
        outputs.hNBcalClusters->Fill(nbcalclrs_after_ecut);
        if (getNISRPhotons()==1) outputs.hNBcalClusters1ISR->Fill(nbcalclrs_after_ecut);
        else if (getNISRPhotons()>=0) outputs.hNBcalClustersMultiISR->Fill(nbcalclrs_after_ecut); // this is different from the original Moritz's macro.
        
        if (nbcalclrs_after_ecut==0) {
          if (outputs.hCutStats) outputs.hCutStats->Fill(bcalveto); 
        }

        float ptmax = -1.;
        for (int ibcal = 0; ibcal < nbcalclrs; ibcal++) {
          if (outputs.hPt_bcal_bcalcoord) outputs.hPt_bcal_bcalcoord->Fill(bcal_pt_bcalcoord[ibcal]);
          TVector3 xv(bcal_x[ibcal],bcal_y[ibcal],bcal_z[ibcal]);
          TVector3 pv(bcal_e[ibcal]*xv.Unit());
          if (outputs.hPt_bcal)           outputs.hPt_bcal->Fill(pv.Pt());
          if (outputs.hE_bcal)            outputs.hE_bcal->Fill(bcal_e[ibcal]);
          // Find maximum pt
          if (bcal_pt_bcalcoord[ibcal]>ptmax) ptmax = bcal_pt_bcalcoord[ibcal];
        }
        if (ptmax>0 && outputs.hPtMax_bcal_bcalcoord) outputs.hPtMax_bcal_bcalcoord->Fill(ptmax);
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

  }
}

#endif
