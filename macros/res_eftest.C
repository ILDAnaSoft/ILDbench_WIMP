void res_eftest(){

		
        TFile* fin = new TFile("/home/belle2/mustahid/work/MonoPhoton_2019_9_5/ILDbench_WIMP/scripts/run_l5/nung/root/l5_500GeV.nung_1.root");
	
        TTree* data = static_cast<TTree*>(fin->Get("evtdata"));
	
	  	
//	TH2D* htheta_sigma = new TH2D("htheta_sigma",";#theta;#sigma of fit",1000,0,3,100,0.2,0.3); 	
	TH1D* hmcr_pfo_theta = new TH1D("hmcr_pfo_theta",";#theta_{pfo}-#theta_{mcr}",100,-1,1); 	
	TH1D* hmcr_pfo_e = new TH1D("hmcr_pfo_e",";E_{pfo}-E_{mcr}",400,-300,300); 	
	TH1D* hmcr_pfo_phi = new TH1D("hmcr_pfo_phi",";#phi_{pfo}-#phi_{mcr}",100,-7,7); 	
//        TH1D* hpfo_theta = new TH1D("hpfo_theta",";#theta;",100,0,4);  
//        TH1D* hpfo_phi = new TH1D("hpfo_phi",";#phi;",100,-3,3);  
//	TCanvas* cmcr_pfo_e = new TCanvas("example","",600,400);
//	TCanvas* ctheta_sigma = new TCanvas("example","",600,400);
	//TCanvas* cpfo_theta_phi = new TCanvas("phi theta","",900,600);
	//cpfo_theta_phi->Divide(2,1);
	
 	TF1* fmcr_pfo_e = new TF1("fmcr_pfo_e","gaus(0)",-50,50);

        const int NMAX = 10000;
        int npfos, nmcr, mcr_pdg[NMAX], mcr_index[NMAX], mcr_nparents[NMAX], mcr_parentIndex[NMAX][10], mcr_ndaughters[NMAX], mcr_daughterIndex[NMAX][10];
	float pfo_e[NMAX], mcr_e[NMAX], mcr_theta[NMAX], sigma[NMAX], pfo_phi[NMAX], pfo_theta[NMAX], angle[NMAX], temp = 0, mcr_phi[NMAX];


	bool bPassed;


    data->SetBranchAddress("mcr_pdg",mcr_pdg);
    data->SetBranchAddress("mcr_e",mcr_e);
  	data->SetBranchAddress("mcr_index",mcr_index);
  	data->SetBranchAddress("mcr_nparents",mcr_nparents);
  	data->SetBranchAddress("mcr_parentIndex",mcr_parentIndex);
  	data->SetBranchAddress("mcr_ndaughters",mcr_ndaughters);
  	data->SetBranchAddress("mcr_daughterIndex",mcr_daughterIndex);
    data->SetBranchAddress("pfo_e",pfo_e);
  	data->SetBranchAddress("pfo_theta",pfo_theta);
  	data->SetBranchAddress("pfo_phi",pfo_phi);
  	data->SetBranchAddress("mcr_theta",mcr_theta);
  	data->SetBranchAddress("mcr_phi",mcr_phi);
  	data->SetBranchAddress("mcr_theta",mcr_theta);
//  	data->SetBranchAddress("mcr_endx",mcr_endx);
//  	data->SetBranchAddress("mcr_endy",mcr_endy);
//  	data->SetBranchAddress("mcr_endz",mcr_endz);
	data->SetBranchAddress("npfos",&npfos);
	//data->SetBranchAddress("nmcr",&nmcr);





        
   
	
	int nevents = data->GetEntries();
	int a[3],i=0;//to determine how many entries are excluded in cut
	
	for(int p=0; p<3; p++) a[p]=0;
		
	for(int ev=0; ev<nevents; ev++){
		data->GetEntry(ev);


					
		for(int ip=0; ip < npfos; ip++){ //npfos and nmcr are the same

            bPassed= (mcr_pdg[ip]==22 && mcr_parentIndex[ip][0]==2 && mcr_parentIndex[ip][1]==3);
             
                       
            if(bPassed){        
                    
                i++;
                       
               // cout<<"g outside loop inside if "<<g<<"in the event ev "<<ev<<endl;
               // cout<<"v outside loop inside if "<<v<<"in the event ev "<<ev<<endl;
               // cout<<"vbar outside loop inside if "<<vbar<<"in the event ev "<<ev<<endl;

                        //hmcr_theta->Fill(mcr_theta[ip]);
                hmcr_pfo_theta->Fill(pfo_theta[ip]-mcr_theta[ip]);
	        	if( (pfo_theta[ip]-mcr_theta[ip])<=0.2 && (pfo_theta[ip]-mcr_theta[ip])>=-0.2 )	{
	    	    	a[0]++;
			        	 	//cout<<"a[0] "<<a[0]<<endl;
			  	}
			        	
			  	hmcr_pfo_e->Fill(pfo_e[ip]-mcr_e[ip]);	
	        	if( (pfo_e[ip]-mcr_e[ip])<=50 && (pfo_e[ip]-mcr_e[ip])>=-50 )	{
		       		a[1]++;
			        	 	//cout<<"a[1] "<<a[1]<<endl;
		       	}
			        		

			   	hmcr_pfo_phi->Fill(pfo_phi[ip]-mcr_phi[ip]);
	        	if( (pfo_phi[ip]-mcr_phi[ip])<=2 && (pfo_phi[ip]-mcr_phi[ip])>=-2 ) 	{
                    a[2]++;
			        	 	//cout<<"a[2] "<<a[2]<<endl;
			    }
            }
         }
        
       }
     
     

  
	
    
	cout<< "number of (-0.2<=theta<=0.2)/(theta after bPassed)  "<<(float)a[0]/(float) i<<endl;
	cout<< "number of (2<=phi<=2)/(phi after bPassed)  "<<(float)a[2]/(float) i<<endl;
	cout<< "number of (-50<=e<=50)/(e after bPassed)  "<<(float)a[1]/(float) i<<endl;



#if 0
	cout<<"number of (-0.2<=theta<=0.2)/(theta after bPassed)  "<<a[0]/i<<endl;
	cout<<"number of (2<=phi<=2)/(phi after bPassed)  "<<a[2]/i<<endl;
	cout<<"number of (-50<=e<=0.50)/(theta after bPassed)  "<<a[1]/i<<endl;
#endif

	TCanvas* cpfo_theta_phi = new TCanvas("phi theta","",900,600);
	cpfo_theta_phi->Divide(2,2);

	cpfo_theta_phi->cd(1);
	gPad->SetLogy();
	gStyle->SetOptFit(1);
	hmcr_pfo_theta->Draw();
	//cpfo_theta_phi->SaveAs("cmcr_pfo_theta.pdf");

	cpfo_theta_phi->cd(2);
	gPad->SetLogy();
	//hmcr_pfo_phi->Fit("fmcr_pfo_e");
	gStyle->SetOptFit(1);
	hmcr_pfo_phi->Draw();
	//cpfo_theta_phi->SaveAs("cmcr_pfo_phi.pdf");
	
		
	cpfo_theta_phi->cd(3);
	gPad->SetLogy();
	//hmcr_pfo_e->Fit("fmcr_pfo_e");
	gStyle->SetOptFit(1);
	hmcr_pfo_e->Draw();	
	

	
	cpfo_theta_phi->cd(4);
	TPaveText *pt = new TPaveText(.05,.1,.95,.8);
	pt->AddText("bPassed = (  (mcr_pdg[ip]==22) && (mcr_parentIndex[ip][0]==2 && mcr_parentIndex[ip][1]==3) )");
	TText *t1 = pt->AddText("#frac{Entries -0.2 #leq #theta #leq 0.2}{Entries when bPassed==1} = 0.998737");	
	TText *t2 = pt->AddText("#frac{Entries -2 #leq #phi #leq 2}{Entries when bPassed==1} = 0.995817 ");	
	TText *t3 = pt->AddText("#frac{Entries -50 #leq Energy #leq 50}{Entries when bPassed==1} =0.98599 ");	
	pt->Draw();
	
	cpfo_theta_phi->SaveAs("cmcr_pfo_all.pdf");
	
}	
