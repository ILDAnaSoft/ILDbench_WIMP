void plot_sensitivity()
{
  const int nmass = 250;
  double _mass_00[nmass];
  double _mass_p08m03[nmass];
  double _lambda_00[nmass];
  double _lambda_p08m03[nmass];
  int index = 0;
  for (int mass = 1; mass < nmass; mass++) {
    stringstream fname_00, fname_p08m03;
    fname_00 << "outputs/Sensitivity_Pe0.0_Pp0.0_Lumi500_Mass" << mass << "_2Sigma_lumi_pole_polp_beamspec_select_withsys_corel.root" << ends; 
    fname_p08m03 << "outputs/Sensitivity_Pe0.8_Pp-0.3_Lumi500_Mass" << mass << "_2Sigma_lumi_pole_polp_beamspec_select_withsys_corel.root" << ends; 

    TFile fin_00(fname_00.str().data());
    TH1D* h_00 = static_cast<TH1D*>(fin_00.Get("Sensitivity Vector"));
    _mass_00[index] = double(mass); 
    _lambda_00[index] = h_00->GetBinContent(mass); 

    TFile fin_p08m03(fname_p08m03.str().data());
    TH1D* h_p08m03 = static_cast<TH1D*>(fin_p08m03.Get("Sensitivity Vector"));
    _mass_p08m03[index] = double(mass); 
    _lambda_p08m03[index] = h_p08m03->GetBinContent(mass); 

    index++;
  }
  TGraph* g_00 = new TGraph(index,_mass_00,_lambda_00);
  TGraph* g_p08m03 = new TGraph(index,_mass_p08m03,_lambda_p08m03);
  g_p08m03->Draw("ap");
  g_00->Draw("p same");
}
