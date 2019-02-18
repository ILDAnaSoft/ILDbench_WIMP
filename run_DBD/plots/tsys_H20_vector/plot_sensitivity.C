void plot_sensitivity()
{
  const int nmass = 250;
  double _mass_op1[nmass];
  double _lambda_op1[nmass];
  int index = 0;
  for (int mass = 1; mass < nmass; mass++) {
    stringstream fname_op1;
    fname_op1 << "outputs/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass" << mass << "_2Sigma.root" << ends; 

    TFile fin_op1(fname_op1.str().data());
    TH1D* h_op1 = static_cast<TH1D*>(fin_op1.Get("Sensitivity Vector"));
    //TH1D* h_op1 = static_cast<TH1D*>(fin_op1.Get("Sensitivity Axial-vector"));
    _mass_op1[index] = double(mass); 
    _lambda_op1[index] = h_op1->GetBinContent(mass); 
    index++;
  }
  TGraph* g_op1 = new TGraph(index,_mass_op1,_lambda_op1);
  g_op1->Draw("ap");
}
