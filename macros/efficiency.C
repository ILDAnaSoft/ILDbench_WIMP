void efficiency(){

		
        TFile* fin = new TFile("/home/belle2/mustahid/work/MonoPhoton_2019_9_5/ILDbench_WIMP/scripts/run_l5/nung/root/l5_500GeV.nung_1.root");
	
        TTree* data = static_cast<TTree*>(fin->Get("evtdata"));
	
	  	
//	TH2D* htheta_sigma = new TH2D("htheta_sigma",";#theta;#sigma of fit",1000,0,3,100,0.2,0.3); 	
	TH1D* hmcp_pfo_theta = new TH1D("hmcp_pfo_theta",";#theta_{mcp}",100,-1,4); 	
	TH1D* hmcp_pfo_e = new TH1D("hmcp_pfo_e",";E_{pfo}-E_{mcp}",400,-300,300); 	
	TH1D* hmcp_pfo_phi = new TH1D("hmcp_pfo_phi",";#phi_{pfo}-#phi_{mcp}",100,-7,7); 	

    TH1D* hmcp_theta = new TH1D("hmcp_theta",";#theta_{mcp}",100,-1,4); 	
//        TH1D* hpfo_theta = new TH1D("hpfo_theta",";#theta;",100,0,4);  
//        TH1D* hpfo_phi = new TH1D("hpfo_phi",";#phi;",100,-3,3);  
//	TCanvas* cmcp_pfo_e = new TCanvas("example","",600,400);
//	TCanvas* ctheta_sigma = new TCanvas("example","",600,400);
	//TCanvas* cpfo_theta_phi = new TCanvas("phi theta","",900,600);
	//cpfo_theta_phi->Divide(2,1);
	
 	TF1* fmcp_pfo_e = new TF1("fmcp_pfo_e","gaus(0)",-50,50);

    const int NMAX = 10000;
    int npfos, nmcps, mcp_pdg[NMAX], mcp_index[NMAX], mcp_nparents[NMAX], mcp_parentIndex[NMAX][10], mcp_daughterIndex[NMAX][10],mcp_ndaughters[NMAX];
	float pfo_e[NMAX], mcp_e[NMAX], mcp_theta[NMAX], sigma[NMAX], pfo_phi[NMAX], pfo_theta[NMAX], mcp_phi[NMAX], angle[NMAX], temp = 1;


	bool bPassed;

    data->SetBranchAddress("mcp_pdg",mcp_pdg);
    data->SetBranchAddress("mcp_e",mcp_e);
  	data->SetBranchAddress("mcp_index",mcp_index);
  	data->SetBranchAddress("mcp_nparents",mcp_nparents);
  	data->SetBranchAddress("mcp_parentIndex",mcp_parentIndex);
  	data->SetBranchAddress("mcp_ndaughters",mcp_ndaughters);
  	data->SetBranchAddress("mcp_daughterIndex",mcp_daughterIndex);
    data->SetBranchAddress("pfo_e",pfo_e);
  	data->SetBranchAddress("pfo_theta",pfo_theta);
  	data->SetBranchAddress("pfo_phi",pfo_phi);
  	data->SetBranchAddress("mcp_theta",mcp_theta);
  	data->SetBranchAddress("mcp_phi",mcp_phi);
  	//data->SetBranchAddress("mcp_theta",mcp_theta);
//  	data->SetBranchAddress("mcp_endx",mcp_endx);
//  	data->SetBranchAddress("mcp_endy",mcp_endy);
//  	data->SetBranchAddress("mcp_endz",mcp_endz);
	data->SetBranchAddress("npfos",&npfos);
	data->SetBranchAddress("nmcps",&nmcps);




	int nevents = data->GetEntries();
    
    for(int ev=0; ev<nevents; ev++){
		
        data->GetEntry(ev);

        int m = 0; //m makes sure parent ID are electron positron

		for(int ip=0; ip < nmcps; ip++){
        
            if(mcp_pdg[ip]==22 &&  mcp_nparents[ip]==2){
            

                for(int j= 0; j < mcp_nparents[ip]; j++){
                
                    if(mcp_pdg[mcp_parentIndex[ip][j]]==11 || mcp_pdg[mcp_parentIndex[ip][j]]==-11) m++; 
                    //cout<<"m "<<m<<endl;                
                }
            
                int g=0, v=0, vbar=0;
                //if(m==2) {cout<<"m outside loop "<<m<<" in the event ev "<<ev<<endl;}

                if(m==2 && mcp_ndaughters[mcp_parentIndex[ip][0]]==3){
            
                    
                    for(int k=0; k< mcp_ndaughters[ip]; k++){
                        
                         if( mcp_pdg[mcp_daughterIndex[mcp_parentIndex[ip][0]][k]]==22 ) g++;
                         if( mcp_pdg[mcp_daughterIndex[mcp_parentIndex[ip][0]][k]]==12 ) v++;
                         if( mcp_pdg[mcp_daughterIndex[mcp_parentIndex[ip][0]][k]]==-12 ) vbar++;
                                
                    }
                         
                     if(g==1 && v== 1 && vbar==1){ 
                       // cout<<"g outside loop inside if "<<g<<"in the event ev "<<ev<<endl;
                       // cout<<"v outside loop inside if "<<v<<"in the event ev "<<ev<<endl;
                       // cout<<"vbar outside loop inside if "<<vbar<<"in the event ev "<<ev<<endl;

                        hmcp_theta->Fill(mcp_theta[ip]);

                        cout<<"mcp index "<<ip<<endl;

                        bool e = pfo_e[ip]<=(mcp_e[ip]+50) && pfo_e[ip]>=(mcp_e[ip]-50) ;
                        bool theta =  pfo_theta[ip]<=(mcp_theta[ip]+0.2) && pfo_theta[ip]>=(mcp_theta[ip]-0.2);
                        bool phi= pfo_phi[ip]<=(mcp_phi[ip]+2) && pfo_phi[ip]>=(mcp_phi[ip]-2);
                        if( e && theta  && phi ){
                         
                              hmcp_pfo_theta->Fill(mcp_theta[ip]);                    
                         }

                    
                    }
                }
            }
        }
      
        
    
   // for(int ip=0; ip < npfos; ip++){
   //     
   //         if(mcp_pdg[ip]==22 &&  mcp_nparents[ip]==2){
   //         
   //             int m=0;

   //             for(int j= 0; j < mcp_nparents[ip]; j++){
   //             
   //                 if(mcp_pdg[mcp_parentIndex[ip][j]]==11 || mcp_pdg[mcp_parentIndex[ip][j]]==-11) m++; 
   //                 //cout<<"m "<<m<<endl;                
   //             }
   //         
   //             int g=0, v=0, vbar=0;
   //             //if(m==2) {cout<<"m outside loop "<<m<<" in the event ev "<<ev<<endl;}

   //             if(m==2 && mcp_ndaughters[mcp_parentIndex[ip][0]]==3){
   //         
   //                 
   //                 for(int k=0; k< mcp_ndaughters[ip]; k++){
   //                     
   //                      if( mcp_pdg[mcp_daughterIndex[mcp_parentIndex[ip][0]][k]]==22 ) g++;
   //                      if( mcp_pdg[mcp_daughterIndex[mcp_parentIndex[ip][0]][k]]==12 ) v++;
   //                      if( mcp_pdg[mcp_daughterIndex[mcp_parentIndex[ip][0]][k]]==-12 ) vbar++;
   //                             
   //                 }
   //                      
   //                  if(g==1 && v== 1 && vbar==1){ 

   //                      //cout<<"test "<<endl;

   //                      //hmcp_theta->Fill(mcp_theta[ip]);


                            //                      
   //                     // cout<<"e "<<e<<endl;
   //                     // cout<<"theta "<<theta<<endl;
   //                     // cout<<"phi "<<phi<<endl;

                         
   //                 }
   //             }
   //        }        
   //     }
   
    }

        TH1D* hefficiency = (TH1D*)hmcp_pfo_theta->Clone("hefficiency");
        hefficiency->Divide(hmcp_theta);

        TCanvas* cpfo_theta_phi = new TCanvas("phi theta","",900,600);
    	cpfo_theta_phi->Divide(2,2);
    
    	cpfo_theta_phi->cd(1);
    	gPad->SetLogy();
    	gStyle->SetOptFit(1);
    	hmcp_theta->Draw();
        //cpfo_theta_phi->SaveAs("cmcp_theta.pdf");

        cpfo_theta_phi->cd(2);
    	gPad->SetLogy();
    	gStyle->SetOptFit(1);
    	hmcp_pfo_theta->Draw();
        //cpfo_theta_phi->SaveAs("cmcp_theta_pfo_cond.pdf");

        cpfo_theta_phi->cd(3);
    	//gPad->SetLogy();
    	gStyle->SetOptFit(1);
    	hefficiency->Draw();
        cpfo_theta_phi->SaveAs("cefficiency_without_factor.pdf");




}

