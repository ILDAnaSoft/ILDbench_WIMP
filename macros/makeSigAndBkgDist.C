#include "WIMP_functions.C"

void makeSigAndBkgDist(TString fname = "plots.root", double mass = 1)
{
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR is to be pointing to ILDbench_WIMP and should be defined in an init script.
  TString auxDirPath(topDirPath+"/macros/aux");

   if (gSystem->AccessPathName("outputs")) {
    cerr << "outputs does not exist!" << endl;
    cerr << "Creating outputs directory..." << endl;
    gSystem->Exec("mkdir outputs");
    cerr << "Done!" << endl;
   } 

  TFile* fin = new TFile(fname.Data());

  UpdateMetaData(); // see util.C
  float xs_nungLR = getXsec("nung.eL.pR");
  float xs_nungRL = getXsec("nung.eR.pL");
  float xs_bhabhangLL = getXsec("bhabhang.eL.pL");
  float xs_bhabhangLR = getXsec("bhabhang.eL.pR");
  float xs_bhabhangRL = getXsec("bhabhang.eR.pL");
  float xs_bhabhangRR = getXsec("bhabhang.eR.pR");

  const float L = 500.; 
  const float epol_abs = 0.8;
  const float ppol_abs = 0.3;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      float epol, ppol;
      if (i==0&&j==0) {
        epol = epol_abs;
        ppol = ppol_abs;
      } else if (i==1&&j==0) {
        epol = -epol_abs;
        ppol = ppol_abs;
      } else if (i==0&&j==1) {
        epol = epol_abs;
        ppol = -ppol_abs;
      } else {
        epol = -epol_abs;
        ppol = -ppol_abs;
      }
 
      enum POL { LL, LR, RL, RR };
      float pfrac[4]; // coefficient for each cross section regarding to beam polarization. 
      pfrac[LL] =  (1-epol) * (1-ppol) / 4.;
      pfrac[LR] =  (1-epol) * (1+ppol) / 4.;
      pfrac[RL] =  (1+epol) * (1-ppol) / 4.;
      pfrac[RR] =  (1+epol) * (1+ppol) / 4.;

      for (int k = 0; k < 3; k++) {
        int optype = k;
        //int optype = 0; // vector
        //int optype = 1; // scalar, s-channel
        //int optype = 2; // axial vector 
        // Process mask based on WIMP models. Turn on/off each process.
        float proc_mask_LL;
        float proc_mask_LR;
        float proc_mask_RL;
        float proc_mask_RR;
        if (optype == 0){
          //Vector operator
          proc_mask_LL = 0.;
          proc_mask_LR = 1.;
          proc_mask_RL = 1.;
          proc_mask_RR = 0.;
        } else if (optype == 1||optype == 2) {
          //Axial-Vector operator And Scalar s-channel
          proc_mask_LL = 1.;
          proc_mask_LR = 0.;
          proc_mask_RL = 0.;
          proc_mask_RR = 1.;
        }

        TH1F* hCutStats_nungLR              = static_cast<TH1F*>(fin->Get("hCutStats_nungLR"));
        TH1F* hCutStats_nungRL              = static_cast<TH1F*>(fin->Get("hCutStats_nungRL"));
        TH1F* hCutStats_bhabhangLL          = static_cast<TH1F*>(fin->Get("hCutStats_bhabhangLL"));
        TH1F* hCutStats_bhabhangLR          = static_cast<TH1F*>(fin->Get("hCutStats_bhabhangLR"));
        TH1F* hCutStats_bhabhangRL          = static_cast<TH1F*>(fin->Get("hCutStats_bhabhangRL"));
        TH1F* hCutStats_bhabhangRR          = static_cast<TH1F*>(fin->Get("hCutStats_bhabhangRR"));
        int n_nung_LR = hCutStats_nungLR->GetBinContent(1); // nentries in "nocut" bin
        int n_nung_RL = hCutStats_nungRL->GetBinContent(1); // nentries in "nocut" bin
        int n_bhabhang_LL = hCutStats_bhabhangLL->GetBinContent(1); // nentries in "nocut" bin
        int n_bhabhang_LR = hCutStats_bhabhangLR->GetBinContent(1); // nentries in "nocut" bin
        int n_bhabhang_RL = hCutStats_bhabhangRL->GetBinContent(1); // nentries in "nocut" bin
        int n_bhabhang_RR = hCutStats_bhabhangRR->GetBinContent(1); // nentries in "nocut" bin

        // Event weights for MC sampels.
        float ew_nung_LR = xs_nungLR * L / n_nung_LR * 2; // nung sample will be divided into two, one for signal, another for background.
        float ew_nung_RL = xs_nungRL * L / n_nung_RL * 2; // then weight should be doubled.  
        float ew_bhabhang_LL = xs_bhabhangLL * L / n_bhabhang_LL;
        float ew_bhabhang_LR = xs_bhabhangLR * L / n_bhabhang_LR;
        float ew_bhabhang_RL = xs_bhabhangRL * L / n_bhabhang_RL;
        float ew_bhabhang_RR = xs_bhabhangRR * L / n_bhabhang_RR;


#if 1 // nung reweighting for WIMP signals

        // some constant parameters
        double cos_cut_7 = 0.992546; // region that we can define signals.
        double ptmin_small = 1.92; // phi-dependent: either 1.92 or 5.65
        double e_thresh_small = 15.75; // 15.75 for ptmin=1.92 and 46.36 for ptmin=5.65
        double ptmin_large = 5.65; // phi-dependent: either 1.92 or 5.65
        double e_thresh_large = 46.36; // 15.75 for ptmin=1.92 and 46.36 for ptmin=5.65

        // Theoretical cross section
        TH2D* h_WIMPdsigmadE[2];          // output
        for (int ph(0); ph < 2; ph++){   // two phi sections
          double ptmin;
          double e_thresh;
          if (ph==0){
            ptmin=ptmin_small;
            e_thresh=e_thresh_small;
          } else { // ph == 1
            ptmin=ptmin_large;
            e_thresh=e_thresh_large;
          }
          // variables defined in WIMP_functions.C
          //_mass = 1;
          _mass = mass;
          _spin = 0.5;
          _lambda=1580.;
          _alpha_em = 0.00781750809112087431;
          stringstream hname;
          hname << "DsigmadE_WIMP_ph" << ph << ends; 
          h_WIMPdsigmadE[ph] = new TH2D(hname.str().data(),"DsigmadE_WIMP;E[GeV];d#sigma /dE [fb]",250,0.5,250.5,502,0,502);

          // call DsigmaE_WIMP_new function defined in WIMP_functions.C
          DsigmadE_WIMP_new(h_WIMPdsigmadE[ph],500.0,cos_cut_7,optype,ptmin,e_thresh);
        }
        const double cos_cut = 0.999992; // FIXME Why not cos_cut_7?
        const double ptmin2 = 0.0;
        const double e_thresh2 = 0.0;
        TH2D* h_WIMPdsigmadE_largerTH = new TH2D("DsigmadE_WIMP_largerTH","DsigmadE_WIMP_largerTH;E[GeV];d#sigma /dE [fb]",250,0.5,250.5,502,0,502);
        DsigmadE_WIMP_new2(h_WIMPdsigmadE_largerTH,500.0,cos_cut,optype,ptmin2,e_thresh2);

        // Reading MC samples
        float signal_e;         // energy of the photon with highest Pt.
        float phi_bcalcoord;  
        float estar, sqrtsstar; // energy and sqrt(s) at C.O.M frame of nung, which are computed from gen info.
                                // This is necessary to compare theoretical cross section.
        float phistar, thetastar; 
        TNtuple* SignalEvent_nungLR = static_cast<TNtuple*>(fin->Get("SignalEvent_nungLR"));
        SignalEvent_nungLR->SetBranchAddress("e",&signal_e);
        SignalEvent_nungLR->SetBranchAddress("phi_bcalcoord",&phi_bcalcoord);
        SignalEvent_nungLR->SetBranchAddress("estar",&estar);
        SignalEvent_nungLR->SetBranchAddress("phistar",&phistar);
        SignalEvent_nungLR->SetBranchAddress("thetastar",&thetastar);
        SignalEvent_nungLR->SetBranchAddress("sqrtsstar",&sqrtsstar);

        TNtuple* SignalEvent_nungRL = static_cast<TNtuple*>(fin->Get("SignalEvent_nungRL"));
        SignalEvent_nungRL->SetBranchAddress("e",&signal_e);
        SignalEvent_nungRL->SetBranchAddress("phi_bcalcoord",&phi_bcalcoord);
        SignalEvent_nungRL->SetBranchAddress("estar",&estar);
        SignalEvent_nungRL->SetBranchAddress("phistar",&phistar);
        SignalEvent_nungRL->SetBranchAddress("thetastar",&thetastar);
        SignalEvent_nungRL->SetBranchAddress("sqrtsstar",&sqrtsstar);

        TNtuple* SignalEvent_bhabhangLL = static_cast<TNtuple*>(fin->Get("SignalEvent_bhabhangLL"));
        SignalEvent_bhabhangLL->SetBranchAddress("e",&signal_e);
        SignalEvent_bhabhangLL->SetBranchAddress("phi_bcalcoord",&phi_bcalcoord);
        SignalEvent_bhabhangLL->SetBranchAddress("estar",&estar);
        SignalEvent_bhabhangLL->SetBranchAddress("phistar",&phistar);
        SignalEvent_bhabhangLL->SetBranchAddress("thetastar",&thetastar);
        SignalEvent_bhabhangLL->SetBranchAddress("sqrtsstar",&sqrtsstar);

        TNtuple* SignalEvent_bhabhangLR = static_cast<TNtuple*>(fin->Get("SignalEvent_bhabhangLR"));
        SignalEvent_bhabhangLR->SetBranchAddress("e",&signal_e);
        SignalEvent_bhabhangLR->SetBranchAddress("phi_bcalcoord",&phi_bcalcoord);
        SignalEvent_bhabhangLR->SetBranchAddress("estar",&estar);
        SignalEvent_bhabhangLR->SetBranchAddress("phistar",&phistar);
        SignalEvent_bhabhangLR->SetBranchAddress("thetastar",&thetastar);
        SignalEvent_bhabhangLR->SetBranchAddress("sqrtsstar",&sqrtsstar);

        TNtuple* SignalEvent_bhabhangRL = static_cast<TNtuple*>(fin->Get("SignalEvent_bhabhangRL"));
        SignalEvent_bhabhangRL->SetBranchAddress("e",&signal_e);
        SignalEvent_bhabhangRL->SetBranchAddress("phi_bcalcoord",&phi_bcalcoord);
        SignalEvent_bhabhangRL->SetBranchAddress("estar",&estar);
        SignalEvent_bhabhangRL->SetBranchAddress("phistar",&phistar);
        SignalEvent_bhabhangRL->SetBranchAddress("thetastar",&thetastar);
        SignalEvent_bhabhangRL->SetBranchAddress("sqrtsstar",&sqrtsstar);

        TNtuple* SignalEvent_bhabhangRR = static_cast<TNtuple*>(fin->Get("SignalEvent_bhabhangRR"));
        SignalEvent_bhabhangRR->SetBranchAddress("e",&signal_e);
        SignalEvent_bhabhangRR->SetBranchAddress("phi_bcalcoord",&phi_bcalcoord);
        SignalEvent_bhabhangRR->SetBranchAddress("estar",&estar);
        SignalEvent_bhabhangRR->SetBranchAddress("phistar",&phistar);
        SignalEvent_bhabhangRR->SetBranchAddress("thetastar",&thetastar);
        SignalEvent_bhabhangRR->SetBranchAddress("sqrtsstar",&sqrtsstar);

        // Input
        TString filename(auxDirPath+"/Xsec_whizard_pt192.root");
        TFile* f_bg_exp192 = new TFile(filename.Data(),"OPEN");
        TH2D* h_bg_2d_192 = (TH2D*)f_bg_exp192->Get("vv_Xsec_whizard");

        filename(auxDirPath+"/Xsec_whizard_pt565.root");
        TFile* f_bg_exp565 = new TFile(filename.Data(),"OPEN");
        TH2D* h_bg_2d_565 = (TH2D*)f_bg_exp565->Get("vv_Xsec_whizard");

        filename(auxDirPath+"/Xsec_whizard_largerThetaRange.root");
        TFile* f_bg_largerTH = new TFile(filename.Data(),"OPEN");
        TH2D* h_bg_largerTH = (TH2D*)f_bg_largerTH->Get("vv_Xsec_whizard");


        // Output 
        TH1D* hE_bkg = new TH1D("hE_bkg","Background;E [GeV]; Entries",300,0.,300.);
        hE_bkg->Sumw2();

        TH1D* hE_wimp = new TH1D("hE_wimp","Signal;E [GeV]; Entries",300,0.,300.);
        hE_wimp->Sumw2();

        // commonly used variables.
        int ph;
        double ptmin;
        double e_thresh;
        double coscut;
        int _bin_x;
        int _bin_y;
        float xsec_bg;  // background cross section without beam polarizations. to be checked.
        float xsec_sig; // signal cross section without beam polarizations.

#if 1
        // bhabhang_LL
        for (int ev = 0; ev < SignalEvent_bhabhangLL->GetEntries(); ev++) {
          SignalEvent_bhabhangLL->GetEntry(ev);
          hE_bkg->Fill(signal_e,ew_bhabhang_LL*pfrac[LL]);
        }
        // bhabhang_LR
        for (int ev = 0; ev < SignalEvent_bhabhangLR->GetEntries(); ev++) {
          SignalEvent_bhabhangLR->GetEntry(ev);
          hE_bkg->Fill(signal_e,ew_bhabhang_LR*pfrac[LR]);
        }
        // bhabhang_RL
        for (int ev = 0; ev < SignalEvent_bhabhangRL->GetEntries(); ev++) {
          SignalEvent_bhabhangRL->GetEntry(ev);
          hE_bkg->Fill(signal_e,ew_bhabhang_RL*pfrac[RL]);
        }
        // bhabhang_RR
        for (int ev = 0; ev < SignalEvent_bhabhangRR->GetEntries(); ev++) {
          SignalEvent_bhabhangRR->GetEntry(ev);
          hE_bkg->Fill(signal_e,ew_bhabhang_RR*pfrac[RR]);
        }
#endif

  // nung_LR
        for (int ev = 0; ev < SignalEvent_nungLR->GetEntries(); ev++) {
          SignalEvent_nungLR->GetEntry(ev);
          // nung sampel will be divid into two: one for background, another for WIMP.
          if (ev%2==1) { // for background
            hE_bkg->Fill(signal_e,ew_nung_LR*pfrac[LR]);
          } else { // for WIMP
            if (TMath::Abs(phi_bcalcoord)>35./180*TMath::Pi()){ 
            	ph=0;
            	ptmin=ptmin_small;
  	      e_thresh=e_thresh_small;
            } else {
            	ph=1;
            	ptmin=ptmin_large;
  	      e_thresh=e_thresh_large;
            }

            if (estar <= ptmin) coscut=.1;
            if (estar > e_thresh && estar > ptmin) coscut=cos_cut_7;
            if (estar < e_thresh && estar > ptmin) coscut=TMath::Sqrt(estar*estar-ptmin*ptmin)/estar;

            if (TMath::Abs(cos(thetastar))>coscut){ // outside
            	_bin_x = h_bg_largerTH->GetXaxis()->FindBin(estar); // dsigma/dE in fb
            	_bin_y = h_bg_largerTH->GetYaxis()->FindBin(sqrtsstar);
            	xsec_bg = h_bg_largerTH->GetBinContent(_bin_x,_bin_y);

              // Reuse _bin_x and _bin_y for later.
              _bin_x = h_WIMPdsigmadE_largerTH->GetXaxis()->FindBin(estar);
              _bin_y = h_WIMPdsigmadE_largerTH->GetYaxis()->FindBin(sqrtsstar);
	      xsec_sig = h_WIMPdsigmadE_largerTH->GetBinContent(_bin_x,_bin_y);
            } else { // inside (=signal?)
                if (ph==0){
                	_bin_x = h_bg_2d_192->GetXaxis()->FindBin(estar); // dsigma/dE in fb
                	_bin_y = h_bg_2d_192->GetYaxis()->FindBin(sqrtsstar);
                	xsec_bg = h_bg_2d_192->GetBinContent(_bin_x,_bin_y);
                } else { // ph == 1
                	_bin_x = h_bg_2d_565->GetXaxis()->FindBin(estar); // dsigma/dE in fb
                	_bin_y = h_bg_2d_565->GetYaxis()->FindBin(sqrtsstar);
                	xsec_bg = h_bg_2d_565->GetBinContent(_bin_x,_bin_y);
                }

                // Reuse _bin_x and _bin_y for later.
                _bin_x = h_WIMPdsigmadE[ph]->GetXaxis()->FindBin(estar);
                _bin_y = h_WIMPdsigmadE[ph]->GetYaxis()->FindBin(sqrtsstar);
                xsec_sig = h_WIMPdsigmadE[ph]->GetBinContent(_bin_x,_bin_y);
            }

      // Event weights for WIMP by reweighting nung event weights.
      //                 turn on/off / event weight wrt current beam pol / signal ratio to bkg.
#if 0
      double ew_xng_LL = proc_mask_LL * ew_nung_LR * pfrac[LR] * xsec_sig/xsec_bg;
      double ew_xng_LR = proc_mask_LR * ew_nung_LR * pfrac[LR] * xsec_sig/xsec_bg;
      double ew_xng_RL = proc_mask_RL * ew_nung_LR * pfrac[LR] * xsec_sig/xsec_bg;
      double ew_xng_RR = proc_mask_RR * ew_nung_LR * pfrac[LR] * xsec_sig/xsec_bg;
#else
            double ew_xng_LL = proc_mask_LL * ew_nung_LR * 0.25 * xsec_sig/xsec_bg;
            double ew_xng_LR = proc_mask_LR * ew_nung_LR * 0.25 * xsec_sig/xsec_bg;
            double ew_xng_RL = proc_mask_RL * ew_nung_LR * 0.25 * xsec_sig/xsec_bg;
            double ew_xng_RR = proc_mask_RR * ew_nung_LR * 0.25 * xsec_sig/xsec_bg;
#endif
            double ew_xng_from_nung_LR = ew_xng_LL*pfrac[LL]
                                        +ew_xng_LR*pfrac[LR]
                                        +ew_xng_RL*pfrac[RL]
                                        +ew_xng_RR*pfrac[RR];
//cerr << "ev = " << ev << endl;
//cerr << "Sigma_PolFactor = " << Sigma_PolFactor(proc_mask_RL, proc_mask_RR, proc_mask_LL, proc_mask_LR,epol,ppol)
//     << " " << proc_mask_LL*pfrac[LL] + proc_mask_LR*pfrac[LR] + proc_mask_RL*pfrac[RL] + proc_mask_RR*pfrac[RR] << endl;
//cerr << "w = " << ew_nung_LR*pfrac[LR] << endl;
//cerr << "w2 = " << ew_xng_from_nung_LR << endl;
//cerr << "xs_sig/xs_bg = " << xsec_sig/xsec_bg << endl;
//cerr << "xs_sig = " << xsec_sig << endl;
//cerr << "xs_bg = " << xsec_bg << endl;
//cerr << "estar = " << estar << " sqrtsstar = " << sqrtsstar << endl;
           if (ew_xng_from_nung_LR > 0.) hE_wimp->Fill(signal_e, ew_xng_from_nung_LR);
         }
       }

#if 1
       // nung_RL
       for (int ev = 0; ev < SignalEvent_nungRL->GetEntries(); ev++) {
         SignalEvent_nungRL->GetEntry(ev);
         // nung sampel will be divid into two: one for background, another for WIMP.
         if (ev%2==1) { // for background
           hE_bkg->Fill(signal_e,ew_nung_RL*pfrac[RL]);
         } else { // for WIMP
           if (TMath::Abs(phi_bcalcoord)>35./180*TMath::Pi()){ 
           	ph=0;
           	ptmin=ptmin_small;
       	e_thresh=e_thresh_small;
           } else {
           	ph=1;
           	ptmin=ptmin_large;
       	e_thresh=e_thresh_large;
           }

           if (estar <= ptmin) coscut=.1;
           if (estar > e_thresh && estar > ptmin) coscut=cos_cut_7;
           if (estar < e_thresh && estar > ptmin) coscut=TMath::Sqrt(estar*estar-ptmin*ptmin)/estar;

           if (TMath::Abs(cos(thetastar))>coscut){ // outside
           	_bin_x = h_bg_largerTH->GetXaxis()->FindBin(estar); // dsigma/dE in fb
           	_bin_y = h_bg_largerTH->GetYaxis()->FindBin(sqrtsstar);
           	xsec_bg = h_bg_largerTH->GetBinContent(_bin_x,_bin_y);

             // Reuse _bin_x and _bin_y for later.
             _bin_x = h_WIMPdsigmadE_largerTH->GetXaxis()->FindBin(estar);
             _bin_y = h_WIMPdsigmadE_largerTH->GetYaxis()->FindBin(sqrtsstar);
         xsec_sig = h_WIMPdsigmadE_largerTH->GetBinContent(_bin_x,_bin_y);
           } else { // inside (=signal?)
               if (ph==0){
               	_bin_x = h_bg_2d_192->GetXaxis()->FindBin(estar); // dsigma/dE in fb
               	_bin_y = h_bg_2d_192->GetYaxis()->FindBin(sqrtsstar);
               	xsec_bg = h_bg_2d_192->GetBinContent(_bin_x,_bin_y);
               } else { // ph == 1
               	_bin_x = h_bg_2d_565->GetXaxis()->FindBin(estar); // dsigma/dE in fb
               	_bin_y = h_bg_2d_565->GetYaxis()->FindBin(sqrtsstar);
               	xsec_bg = h_bg_2d_565->GetBinContent(_bin_x,_bin_y);
               }

               // Reuse _bin_x and _bin_y for later.
               _bin_x = h_WIMPdsigmadE[ph]->GetXaxis()->FindBin(estar);
               _bin_y = h_WIMPdsigmadE[ph]->GetYaxis()->FindBin(sqrtsstar);
               xsec_sig = h_WIMPdsigmadE[ph]->GetBinContent(_bin_x,_bin_y);
           }

      // Event weights for WIMP by reweighting nung event weights.
      //                 turn on/off / event weight wrt current beam pol / signal ratio to bkg.
#if 0
      double ew_xng_LL = proc_mask_LL * ew_nung_RL * pfrac[RL] * xsec_sig/xsec_bg;
      double ew_xng_LR = proc_mask_LR * ew_nung_RL * pfrac[RL] * xsec_sig/xsec_bg;
      double ew_xng_RL = proc_mask_RL * ew_nung_RL * pfrac[RL] * xsec_sig/xsec_bg;
      double ew_xng_RR = proc_mask_RR * ew_nung_RL * pfrac[RL] * xsec_sig/xsec_bg;
#else
          double ew_xng_LL = proc_mask_LL * ew_nung_RL * 0.25 * xsec_sig/xsec_bg;
          double ew_xng_LR = proc_mask_LR * ew_nung_RL * 0.25 * xsec_sig/xsec_bg;
          double ew_xng_RL = proc_mask_RL * ew_nung_RL * 0.25 * xsec_sig/xsec_bg;
          double ew_xng_RR = proc_mask_RR * ew_nung_RL * 0.25 * xsec_sig/xsec_bg;
#endif
          double ew_xng_from_nung_RL = ew_xng_LL*pfrac[LL]
                                      +ew_xng_LR*pfrac[LR]
                                      +ew_xng_RL*pfrac[RL]
                                      +ew_xng_RR*pfrac[RR];
          if (ew_xng_from_nung_RL > 0.) hE_wimp->Fill(signal_e, ew_xng_from_nung_RL);
        }
      }
#endif
#endif
#if 1 // additional entires for background
      filename = auxDirPath+"/rew_input_20180416_pt_e_05.root";
cerr << "###### test : filename.Data() = " << filename.Data() << endl;
      TFile* fbkg = new TFile(filename.Data());
      TTree* treebkg = static_cast<TTree*>(fbkg->Get("selected_photons"));
      TTree* treeglb = static_cast<TTree*>(fbkg->Get("global"));
      float MClumi, crosss;
      treeglb->SetBranchAddress("MCLumi",&MClumi);
      treeglb->SetBranchAddress("crosss",&crosss);
      treeglb->GetEntry(0);
      treebkg->Draw("RCENE>>hbkg_add(300,0,300)");
      TH1D* hbkg_add = static_cast<TH1D*>(gROOT->FindObject("hbkg_add"));
      //cerr << MClumi << " " << crosss << endl;
      hbkg_add->Scale(L/MClumi); 
      hE_bkg->Add(hbkg_add);
#endif

      stringstream fotname;
      fotname << "outputs/output_mass" << mass << "_epol" << epol << "_ppol" << ppol << "_op" << optype <<  ".root" << ends;
      TFile* fot = new TFile(fotname.str().data(),"RECREATE");
      h_WIMPdsigmadE[0]->Write();
      h_WIMPdsigmadE[1]->Write();
      hE_bkg->Write();
      hE_wimp->Write();
//cerr << "  xs_nungLR = " << xs_nungLR 
//     << "  xs_nungRL = " << xs_nungRL
//     << "  xs_bhabhangLL = " << xs_bhabhangLL 
//     << "  xs_bhabhangLR = " << xs_bhabhangLR 
//     << "  xs_bhabhangRL = " << xs_bhabhangRL
//     << "  xs_bhabhangRR = " << xs_bhabhangRR << endl;
// 
//cerr << "weightLL = " << ew_bhabhang_LL*pfrac[LL] << endl;
//cerr << "weightLR = " << ew_bhabhang_LR*pfrac[LR] << endl;
//cerr << "weightRL = " << ew_bhabhang_RL*pfrac[RL] << endl;
//cerr << "weightRR = " << ew_bhabhang_RR*pfrac[RR] << endl;
//cerr << "weight nung LR = " << ew_nung_LR*pfrac[LR] << endl;
//cerr << "weight nung RL = " << ew_nung_RL*pfrac[RL] << endl;
//cerr << "n_nung_LR = " << n_nung_LR << endl;
//cerr << "n_nung_RL = " << n_nung_RL << endl;
//cerr << "n_bhabhang_LL = " << n_bhabhang_LL << endl;
//cerr << "n_bhabhang_LR = " << n_bhabhang_LR << endl;
//cerr << "n_bhabhang_RL = " << n_bhabhang_RL << endl;
//cerr << "n_bhabhang_RR = " << n_bhabhang_RR << endl;
      } // i loop
    } // j loop
  } // k loop
}
