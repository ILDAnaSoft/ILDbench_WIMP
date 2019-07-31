#ifndef __EVENTSELECTION__
#define __EVENTSELECTION__

const int NMAX = 20000;

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
	void SetInputTree(TTree* T) { 
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
           _T->SetBranchAddress("mcp_px",mcp_px);
           _T->SetBranchAddress("mcp_py",mcp_py);
           _T->SetBranchAddress("mcp_pz",mcp_pz);
           _T->SetBranchAddress("mcp_phi",mcp_phi);
           _T->SetBranchAddress("mcp_theta",mcp_theta);
           _T->SetBranchAddress("mcp_endx",mcp_endx);
           _T->SetBranchAddress("mcp_endy",mcp_endy);
           _T->SetBranchAddress("mcp_endz",mcp_endz);
           _T->SetBranchAddress("mcp_isDecayedInTracker",mcp_isDecayedInTracker);
           _T->SetBranchAddress("mcp_isDecayedInCalorimeter",mcp_isDecayedInCalorimeter);
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
           _T->SetBranchAddress("bcal_e_bcalcoord",bcal_e_bcalcoord);
           _T->SetBranchAddress("bcal_phi",bcal_phi);
           _T->SetBranchAddress("bcal_phi_bcalcoord",bcal_phi_bcalcoord);
           _T->SetBranchAddress("bcal_theta",bcal_theta);
           _T->SetBranchAddress("bcal_theta_bcalcoord",bcal_theta_bcalcoord);
           _T->SetBranchAddress("bcal_x",bcal_x);
           _T->SetBranchAddress("bcal_x_bcalcoord",bcal_x_bcalcoord);
           _T->SetBranchAddress("bcal_y",bcal_y);
           _T->SetBranchAddress("bcal_z",bcal_z);
           _T->SetBranchAddress("bcal_r",bcal_r);
           _T->SetBranchAddress("bcal_r_bcalcoord",bcal_r_bcalcoord);
           _T->SetBranchAddress("bcal_pt_bcalcoord",bcal_pt_bcalcoord);
        }

        void callGetEntry(int ev) {

          if (_currentEv==ev) return; // Do nothing if this function has been called once.

          _T->GetEntry(ev);
          _currentEv = ev; 

          // Check if this event is a signal-like event.
          int nAcceptablePhoton_MC_per_evt = 0;
          _signal_index = -1.;
          int signal_index_wo_acceptancecut = -1.; // This is necessary for nung reweighting for WIMP signals.
          _signal_e_star = -1.;
          _sqrtS_star = -1.;
          _signal_e = -1.;
          _nISRPhotons = 0;
          float highestPt = -1.; 
          float highestPt_wo_acceptancecut = -1.; 
          for (int i = 0; i < nmcps; i++) {
            if (mcp_pdg[i]==22 && mcp_parentIndex[i][0]==2&&mcp_parentIndex[i][1]==3) { // select only initial ones
              _nISRPhotons++;
              TVector3 mom(mcp_px[i],mcp_py[i],mcp_pz[i]);
              if (highestPt_wo_acceptancecut < mom.Pt()) {
                  highestPt_wo_acceptancecut = mom.Pt();
                  signal_index_wo_acceptancecut = i;
              }
              
#if 1
              if (mcp_ndaughters[i] < 2 && mcp_e[i]>2. && mcp_theta[i]>7/180.*TMath::Pi() && mcp_theta[i]<173/180.*TMath::Pi()) { 
                nAcceptablePhoton_MC_per_evt++;
              // RY test (20190617)
#else
              if (mcp_theta[i]>7/180.*TMath::Pi() && mcp_theta[i]<173/180.*TMath::Pi()) { 
                if (mcp_ndaughters[i] < 2 && mcp_e[i]>2.) nAcceptablePhoton_MC_per_evt++;
#endif
                // select photon (non converted photon only)
              // RY test (20190621)
              //if (mcp_ndaughters[i] < 2 && mcp_e[i]>10. && mcp_theta[i]>7/180.*TMath::Pi() && mcp_theta[i]<173/180.*TMath::Pi()) { 
                if (highestPt < mom.Pt()) {
                  highestPt = mom.Pt();
                  _signal_index = i;
                  _signal_e = mcp_e[i];
                  _signal_phi = mcp_phi[i];
                  _signal_theta = mcp_theta[i];
                }
              }
            }
          }
          // Define signal events:
          _isAcceptableEvent = (_nISRPhotons==1&&nAcceptablePhoton_MC_per_evt==1); 
          _nAcceptablePhoton_MC_per_evt = nAcceptablePhoton_MC_per_evt; 

          // PFO loop
          _nPhotons = 0;
          for (int i = 0; i < npfos; i++) {
            if (pfo_pdg[i]==22) _nPhotons++;
            //if (i > 100000) break;
          }

          // compute sqrt(s) and Egamma at nunug centre-of-mass frame
          TLorentzVector p4v_nu1(mcp_px[6],mcp_py[6],mcp_pz[6],mcp_e[6]);
          TLorentzVector p4v_nu2(mcp_px[7],mcp_py[7],mcp_pz[7],mcp_e[7]);
          int s = signal_index_wo_acceptancecut; 
          TLorentzVector p4v_isr(mcp_px[s],mcp_py[s],mcp_pz[s],mcp_e[s]);
          TLorentzVector p4v_nung = p4v_nu1 + p4v_nu2 + p4v_isr;
          _sqrtS_star = p4v_nung.M(); 
          TVector3 beta(p4v_nung.BoostVector());
          double gamma = p4v_nung.Gamma();
          // parallel vector and vertical vector to beta.
          TVector3 p3v_isr_para(beta*(beta.Dot(p4v_isr.Vect())/beta.Mag2()));
          TVector3 p3v_isr_vert(p4v_isr.Vect()-p3v_isr_para);
          // Lorentz transformation
          TVector3 p3v_isr_para_star = -gamma*beta*p4v_isr.E() + gamma*p3v_isr_para; 
          TVector3 p3v_isr_star = p3v_isr_para_star + p3v_isr_vert; 
          _signal_e_star = gamma*p4v_isr.E()-gamma*beta.Dot(p3v_isr_para); 
          _signal_phi_star = p3v_isr_star.Phi();
          _signal_theta_star = TMath::ACos(p3v_isr_star.Z()/p3v_isr_star.Mag()); 

//std::cerr << "test: " << s << " " << _signal_e_star << " pdg(6) = " << mcp_pdg[6] << " pdg(7) = " << mcp_pdg[7] << std::endl;
//if (s<0) abort();
          //TLorentzVector p4v_isr_star(p3v_isr_perp_star+p3v_isr_vert,Egamma_star);
          //p4v_isr.Boost(-beta);
          //p4v_nung.Boost(-beta);
          //std::cerr << "E : " << p4v_isr.E() << " " << _signal_e_star << std::endl;
          //std::cerr << "S : " << p4v_nung.E() << " " << _sqrtS_star << std::endl;
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
#if 1 //FIXME
              if (p4.Pt()>0.5) return false;
#else // temporary test
              if (p4.Pt()>3.) return false;
#endif
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
          if (_signal_index>=0) return _signal_index; 
          else return -1.;
        }

        float getSignalE() const { 
          if (_signal_e>=0) return _signal_e; 
          else return -1.;
        }

        float getSignalTheta() const { 
          return _signal_theta; 
        }

        float getSignalEstar() const { 
          if (_signal_e_star>=0) return _signal_e_star; 
          else return -1.;
        }

        float getSignalPhistar() const { 
          return _signal_phi_star; 
        }

        float getSignalThetastar() const { 
          return _signal_theta_star; 
        }

        float getSqrtSstar() const { 
          if (_sqrtS_star>=0) return _sqrtS_star; 
          else return -1.;
        }

        int getNISRPhotons() const { return _nISRPhotons; }

        int getNPhotons() const { return _nPhotons; }

        void setProcessType(ProcessType type) { _ptype = type; }

        ProcessType getProcessType() const { return _ptype; }

        void process();  // For Moritz analysis

        void process2(); // For additional tests

        void process(string fname);

        void process2(string fname);

        void clearFileList() { inputfiles.clear(); };

        void addToFileList(string file) { inputfiles.push_back(file); };

        struct Outputs
        {
          Outputs() :  
                      hCutStats(0),
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
                      hPt_R_bcal_bcalcoord(0),
                      hPtMax_bcal_bcalcoord(0),
                      hPt_bcal(0),
                      hE_bcal(0),
                      hRZ_bcal_wo_cut(0),
                      hRZ_bcal_w_PtEcut(0),
                      hECosTheta_wo_cut(0), 
                      hECosTheta_w_cut(0),
                      SignalEvent(0),
                      SignalPhoton(0),
                      hDiffPtMaxPhotonEvsPtMaxPhotonE(0) {}

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
          TH2F* hPt_R_bcal_bcalcoord;
          TH1F* hPtMax_bcal_bcalcoord;
          TH1F* hPt_bcal;
          TH1F* hE_bcal;
          TH2F* hRZ_bcal_wo_cut;
          TH2F* hRZ_bcal_w_PtEcut;

          TH2F* hECosTheta_wo_cut;
          TH2F* hECosTheta_w_cut;

          TNtuple* SignalEvent;
          TNtuple* SignalPhoton;
    
          TH2F* hDiffPtMaxPhotonEvsPtMaxPhotonE;
        };

        Outputs outputs;

   private:
        ProcessType _ptype;
        float       _xsec;
        int         _nTotalEntries;
        vector<string> inputfiles;
	TTree* _T;   // input tree
	TTree* _SET; // output signal event tree 
        int _currentEv;
        // MCParticle
	int _signal_index;
        float _signal_e, _signal_phi, _signal_theta;
        float _signal_e_star, _sqrtS_star;
        float _signal_phi_star, _signal_theta_star;
        bool _isAcceptableEvent;
        bool _isSignalLikeEvent;
        int _nISRPhotons;
        int _nPhotons;
        int _nAcceptablePhoton_MC_per_evt;

   public:
        int nmcps, mcp_pdg[NMAX], mcp_index[NMAX];
        int mcp_nparents[NMAX], mcp_parentIndex[NMAX][10];
        int mcp_ndaughters[NMAX], mcp_daughterIndex[NMAX][10];
        float mcp_e[NMAX], mcp_phi[NMAX], mcp_theta[NMAX];
        float mcp_px[NMAX], mcp_py[NMAX], mcp_pz[NMAX];
        float mcp_endx[NMAX], mcp_endy[NMAX], mcp_endz[NMAX];
        bool mcp_isOriginatedFromISR[NMAX], mcp_isoverlay[NMAX];
        bool mcp_isDecayedInTracker[NMAX], mcp_isDecayedInCalorimeter[NMAX];
        int npfos, pfo_pdg[NMAX],mcr_pdg[NMAX], mcr_index[NMAX], mcr_nparents[NMAX], mcr_parentIndex[NMAX][10];
        float pfo_e[NMAX], pfo_px[NMAX], pfo_py[NMAX], pfo_pz[NMAX], pfo_phi[NMAX], pfo_theta[NMAX];
        float pfo_cal_x[NMAX],  pfo_cal_y[NMAX],  pfo_cal_z[NMAX];
        float pfo_ecal_e[NMAX], pfo_hcal_e[NMAX];
        float pfo_chrg[NMAX];
        float mcr_e[NMAX], mcr_phi[NMAX], mcr_theta[NMAX], mcr_weight[NMAX];
        bool mcr_isOriginatedFromISR[NMAX], mcr_isoverlay[NMAX];
        int nbcalclrs;
        float bcal_e[NMAX], bcal_phi[NMAX], bcal_theta[NMAX];
        float bcal_e_bcalcoord[NMAX], bcal_phi_bcalcoord[NMAX], bcal_theta_bcalcoord[NMAX];
        float bcal_x[NMAX], bcal_y[NMAX], bcal_z[NMAX], bcal_r[NMAX];
        float bcal_x_bcalcoord[NMAX];
        float bcal_r_bcalcoord[NMAX];
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

void Event::process2()
{
  for (int i = 0; i < inputfiles.size(); i++ ) {
    cerr << "Loading " << inputfiles[i] << " ";
    process2(inputfiles[i]);
  }
}

void Event::process(string fname)
{
  TFile fin(fname.c_str());
  TTree* data = static_cast<TTree*>(fin.Get("evtdata"));

  int nevents = data->GetEntries();
  int nPhoton_MC = 0;
  int nPhoton_Rec = 0;

  SetInputTree(data);

  if (outputs.hCutStats) {
    // These labels will not be saved in the output root file with ROOT6.08/06, 
    // but this has been officially fixed (May 2017).
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
      if (outputs.hNrecNgenEmc_photon)      outputs.hNrecNgenEmc_photon->Fill(getSignalE(),nrec);                      // Corresponds to Fig. 5.15 (a). Ngen = 1 here.  
      if (outputs.hNrecNgenCostheta_photon) outputs.hNrecNgenCostheta_photon->Fill(TMath::Cos(getSignalTheta()),nrec); // Corresponds to Fig. 5.15 (c). Ngen = 1 here.    
    } 
#if 1   
    for (int ibcal = 0; ibcal < nbcalclrs; ibcal++) {
      if (outputs.hRZ_bcal_wo_cut) {
        //const float bcal_e_threshold = 32.; // FIXME 
        const float bcal_e_threshold = 36.; // FIXME 
        if (bcal_e[ibcal]>bcal_e_threshold) {
          outputs.hRZ_bcal_wo_cut->Fill(TMath::Abs(bcal_z[ibcal]),bcal_r_bcalcoord[ibcal]);
        }
      }
    }
#endif

    bool isSignalEvt   = false;
    //for (int i = 0; i < npfos; i++) {
// need only energy

    // Check if this event is signal like.
    if (ptmaxphoton_theta > 7./180.*TMath::Pi() && ptmaxphoton_theta < 173./180.*TMath::Pi()) {
      if ( (fabs(ptmaxphoton_phi_bcalcoord/TMath::Pi()*180.)>35. && ptmaxphoton_pt_bcalcoord>1.92 ) ||
           (fabs(ptmaxphoton_phi_bcalcoord/TMath::Pi()*180.)<=35. && ptmaxphoton_pt_bcalcoord>5.65)  ) {
        if (ptmaxphoton_e > 2.) {
          if (outputs.hE_photon) outputs.hE_photon->Fill(ptmaxphoton_e); // Before max energy cut. Corresponds to Fig 5.8     
          //if (ptmaxphoton_e < 220.) {
          if (ptmaxphoton_e < 250.) {
          //if (ptmaxphoton_e < 300.) {
          //if (ptmaxphoton_e < 500.) {
          //if (ptmaxphoton_e < 501.) {
          //if (ptmaxphoton_e < 502.) {
          //
          //if (ptmaxphoton_e < 505.) {
          //
          //if (ptmaxphoton_e < 510.) {
          //if (ptmaxphoton_e < 550.) {
          //if (ptmaxphoton_e < 650.) {
          //if (ptmaxphoton_e < 750.) {
          //if (ptmaxphoton_e < 1000.) { // Effictively remove the cut on maximum energy.
            isSignalEvt = true;
          } // Max energy cut 
        } // Min energy cut
      } // Pt_max cut depending on |phi| in bcal coordinates.
    } // theta restriction

    //} // PFO loop



    //if (!isPassedECut(ev)) continue; 

    bool _isPassedPtCut = isPassedPtCut(ev);
    bool _isPassedECut = isPassedECut(ev);
    bool _isPassedBCalVeto = false;

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

      //if (!isPassedPtCut(ev)) continue; 
      if (_isPassedPtCut) { 
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

      } // pt cut condition

      if (_isPassedPtCut && _isPassedECut && getNPhotons()>0) { 
        if (outputs.hCutStats) outputs.hCutStats->Fill(ecut); 

#if 1   
        for (int ibcal = 0; ibcal < nbcalclrs; ibcal++) {
          if (outputs.hRZ_bcal_w_PtEcut) {
            //const float bcal_e_threshold = 32.; // FIXME
            const float bcal_e_threshold = 36.; // FIXME
            if (bcal_e[ibcal]>bcal_e_threshold) { 
              outputs.hRZ_bcal_w_PtEcut->Fill(TMath::Abs(bcal_z[ibcal]),bcal_r_bcalcoord[ibcal]);
            }
          }
        }
#endif

#if 1   //FIXME. Temporary treatment for IDR sample (20181219)  
        // Cluster threshold was wrongly set to be 0.06, but this should be 32.
        // The energy cut will be performed here.
        //const float bcal_e_threshold = 32.;
        const float bcal_e_threshold = 36.;
        //const float bcal_e_thresholdmax = 300.; // Temporary measure for the wrong value of the minimum energy per pad
        int nbcalclrs_after_ecut = 0;
        bool pass = true;
        for (int ibcal = 0; ibcal < nbcalclrs; ibcal++) {
#if 1  // FIXME 
          if (bcal_e[ibcal]>bcal_e_threshold) nbcalclrs_after_ecut++;
#else  // test // neglect outer rim bcal hits
#if 0
          if (bcal_e[ibcal]>bcal_e_threshold &&
              //(fabs(TMath::Cos(bcal_theta_bcalcoord[ibcal]))>0.9997) ) nbcalclrs_after_ecut++;
              (fabs(TMath::Cos(bcal_theta_bcalcoord[ibcal]))>0.99993) ) nbcalclrs_after_ecut++;
#else // test // neglect outer rim bcal hits
#if 0
          if (bcal_e[ibcal]>bcal_e_threshold &&
              //fabs(TMath::Cos(bcal_theta_bcalcoord[ibcal]))>0.9997 &&
              (fabs(TMath::Cos(bcal_theta_bcalcoord[ibcal]))>0.99993||fabs(TMath::Cos(bcal_theta_bcalcoord[ibcal]))<0.99988) 
             ) nbcalclrs_after_ecut++;
#else
if ( bcal_e[ibcal]>bcal_e_threshold 
     &&
     (
       (
         bcal_phi_bcalcoord[ibcal]<0
         &&
         (
           TMath::Cos(bcal_theta_bcalcoord[ibcal])>0.999925||TMath::Cos(bcal_theta_bcalcoord[ibcal])<0.999895
         )
       )
       ||
       (
         bcal_phi_bcalcoord[ibcal]>0
         &&
         (
           TMath::Cos(bcal_theta_bcalcoord[ibcal])<-0.999925||TMath::Cos(bcal_theta_bcalcoord[ibcal])>-0.999895
         )
       )
     )
   ) nbcalclrs_after_ecut++;
#endif
#endif
#endif
          //if (bcal_e[ibcal]>bcal_e_threshold &&
          //    bcal_e[ibcal]<bcal_e_thresholdmax ) nbcalclrs_after_ecut++;
        }
#endif

        //cerr << "passed event. ev = " << ev << endl;
        outputs.hNBcalClusters->Fill(nbcalclrs_after_ecut);
        if (getNISRPhotons()==1) outputs.hNBcalClusters1ISR->Fill(nbcalclrs_after_ecut);
        else if (getNISRPhotons()>=0) outputs.hNBcalClustersMultiISR->Fill(nbcalclrs_after_ecut); // this is different from the original Moritz's macro.
        
        if (nbcalclrs_after_ecut==0) {
          _isPassedBCalVeto = true;

          if (outputs.hCutStats) outputs.hCutStats->Fill(bcalveto); 
#if 1 
          if (outputs.SignalEvent) {
            float data[7]; // e:phi_bcalcoord:estar:phistar:thetastar:sqrtsstar:gen_e
            data[0] = ptmaxphoton_e;
            data[1] = ptmaxphoton_phi_bcalcoord;
            data[2] = getSignalEstar(); 
            data[3] = getSignalPhistar(); 
            data[4] = getSignalThetastar(); 
            data[5] = getSqrtSstar(); 
            data[6] = getSignalE(); 
#if 1
if (ptmaxphoton_e>501) {
  std::cerr << "#### ptmaxphoton > 501 !!! " << std::endl;
  for (int i = 0; i < 7; i++) {
    std::cerr << data[i] << " "; 
  }
  std::cerr << std::endl;
}
#endif
            outputs.SignalEvent->Fill(data);
          }
         
#else
std::cerr << "test npfos = " << npfos << std::endl; 
std::cerr << "ptmaxphoton_e = " << ptmaxphoton_e << std::endl;
for (int i = 0; i < npfos; i++) {
  std::cerr << " i = " << i << " pdg = " << pfo_pdg[i] << std::endl;
}
#endif
        }

        float ptmax = -1.;
        for (int ibcal = 0; ibcal < nbcalclrs; ibcal++) {
          if (outputs.hPt_bcal_bcalcoord) outputs.hPt_bcal_bcalcoord->Fill(bcal_pt_bcalcoord[ibcal]);
          if (outputs.hPt_R_bcal_bcalcoord) outputs.hPt_R_bcal_bcalcoord->Fill(bcal_pt_bcalcoord[ibcal],TMath::Sqrt(bcal_x_bcalcoord[ibcal]*bcal_x_bcalcoord[ibcal]+bcal_y[ibcal]*bcal_y[ibcal]));
          TVector3 xv(bcal_x[ibcal],bcal_y[ibcal],bcal_z[ibcal]);
          TVector3 pv(bcal_e[ibcal]*xv.Unit());
          if (outputs.hPt_bcal)           outputs.hPt_bcal->Fill(pv.Pt());
          if (outputs.hE_bcal)            outputs.hE_bcal->Fill(bcal_e[ibcal]);
          // Find maximum pt
          if (bcal_pt_bcalcoord[ibcal]>ptmax) ptmax = bcal_pt_bcalcoord[ibcal];
        }
        if (ptmax>0 && outputs.hPtMax_bcal_bcalcoord) outputs.hPtMax_bcal_bcalcoord->Fill(ptmax);
      }

    } // signal events

    // Photon Efficiency, Purity, energy resolution, angular resolution 
    if (outputs.SignalPhoton) { // This includes photons from the events which do not passed the signal event criterias e.g. pt cut.
        float data[25]; // gen_endx, gen_endy, gen_endz, gen_isDecayInTracker, gen_isDecayedInCalorimeter, gen_e, gen_phi, gen_theta, gen_ndaughters, rec_e, rec_phi, rec_theta, rec_mcindex, nISR ,isMCSignalEvt, isRecSignalEvt, ismatched, MCRelation weight isPassedPtCut, isPassedECut, isPassedBCalVeto, nrec_pfoAsPhoton, nrec_pfoAsNonPhoton, nAcceptablePhoton_MC_per_evt, ev

//Obsolete :  nrec_angle_only, nrec_with_angle,
//
        data[0] = mcp_endx[_signal_index];
        data[1] = mcp_endy[_signal_index];
        data[2] = mcp_endz[_signal_index];
        data[3] = mcp_isDecayedInTracker[_signal_index];
        data[4] = mcp_isDecayedInCalorimeter[_signal_index];
        data[5] = mcp_e[_signal_index];
        data[6] = mcp_phi[_signal_index];
        data[7] = mcp_theta[_signal_index];
        data[8] = mcp_ndaughters[_signal_index];
        data[9] = pfo_e[ptmaxphoton_index];
        data[10] = pfo_phi[ptmaxphoton_index];
        data[11] = pfo_theta[ptmaxphoton_index];
        data[12] = mcr_index[ptmaxphoton_index];
        data[13] = getNISRPhotons();
        data[14] = isAcceptableEvent(ev); 
        data[15] = isSignalEvt; 
        data[16] = ((_signal_index==mcr_index[ptmaxphoton_index]) ? 1. : 0.); 
        data[17] = mcr_weight[ptmaxphoton_index];
        data[18] = _isPassedPtCut;
        data[19] = _isPassedECut;
        data[20] = _isPassedBCalVeto;
#if 1
        int nrec_pfoAsPhoton = 0;
        int nrec_pfoAsNonPhoton = 0;

        for (int i = 0; i < npfos; i++) {
          //if (pfo_pdg[i]==22) {
            

            // MCParticle PFO matching by LCRelation 
	        if (mcr_index[i] == _signal_index) {
              if (pfo_pdg[i]==22) nrec_pfoAsPhoton++;
              else                nrec_pfoAsNonPhoton++;
            } 

#if 0
            // MCParticle PFO matching by angles (LCRelation doesn't seem to work at the gap between barrel and endcap)
	        if ((fabs(mcp_phi[_signal_index]-pfo_phi[i])<0.005||fabs(fabs(mcp_phi[_signal_index]-pfo_phi[i])-2*TMath::Pi())<0.005)&&  // 0.005 ~ 5 sigma for phi 
                fabs(mcp_theta[_signal_index]-pfo_theta[i])<0.1) { // 0.005 ~ 5 sigma for theta (in 0.81 < cosTheta < 0.84 for s5)
	          nrec_angle_only++;
            } 

            // MCParticle PFO matching by LCRelation OR angles
	        if ( ( (fabs(mcp_phi[_signal_index]-pfo_phi[i])<0.005||fabs(fabs(mcp_phi[_signal_index]-pfo_phi[i])-2*TMath::Pi())<0.005)&&  
                fabs(mcp_theta[_signal_index]-pfo_theta[i])<0.1 ) ||
	           (mcr_index[i] == _signal_index) 
                ) { 
	          nrec_with_angle++;
            } 
#endif

          //} 
        } 

        data[21] = nrec_pfoAsPhoton;
        data[22] = nrec_pfoAsNonPhoton;
        //data[23] = nrec_angle_only;
        //data[24] = nrec_with_angle;
        data[23] = _nAcceptablePhoton_MC_per_evt;
        data[24] = ev;
#endif
        outputs.SignalPhoton->Fill(data);
    }


  } // event loop
}

// For additional tests
void Event::process2(string fname)
{
  TFile fin(fname.c_str());
  TTree* data = static_cast<TTree*>(fin.Get("evtdata"));

  int nevents = data->GetEntries();
  std::cerr << nevents << endl;
  SetInputTree(data);


  const int ms1 = int(nevents/4);
  const int ms2 = ms1*2;
  const int ms3 = ms1*3;
  // event loop
  for (int ev = 0; ev < nevents; ev++) {
    if      (ev == ms1) cerr << ".";
    else if (ev == ms2) cerr << ".";
    else if (ev == ms3) cerr << "." << endl;

    callGetEntry(ev);

    bool isSignalEvt   = false;
    if (ptmaxphoton_theta > 7./180.*TMath::Pi() && ptmaxphoton_theta < 173./180.*TMath::Pi()) { // to be better photon ID.
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

    if (isAcceptableEvent(ev)) { // check only events with one ISR photon
      if (mcr_index[emaxphoton_index]==8) {
        outputs.hDiffPtMaxPhotonEvsPtMaxPhotonE->Fill(mcr_e[emaxphoton_index],pfo_e[emaxphoton_index]-mcr_e[emaxphoton_index]);
      }
    }
  }
}

#endif
