void plot_sensitivity()
{
//  const int nmass = 250;
const int nmass = 255;
const double masses[nmass] = 
{ 1.e-9, 1.e-6, 1.e-3, 0.1,
  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10.,
 11., 12., 13., 14., 15., 16., 17., 18., 19., 20.,
 21., 22., 23., 24., 25., 26., 27., 28., 29., 30.,
 31., 32., 33., 34., 35., 36., 37., 38., 39., 40.,
 41., 42., 43., 44., 45., 46., 47., 48., 49., 50.,
 51., 52., 53., 54., 55., 56., 57., 58., 59., 60.,
 61., 62., 63., 64., 65., 66., 67., 68., 69., 70.,
 71., 72., 73., 74., 75., 76., 77., 78., 79., 80.,
 81., 82., 83., 84., 85., 86., 87., 88., 89., 90.,
 91., 92., 93., 94., 95., 96., 97., 98., 99.,100.,
101.,102.,103.,104.,105.,106.,107.,108.,109.,110.,
111.,112.,113.,114.,115.,116.,117.,118.,119.,120.,
121.,122.,123.,124.,125.,126.,127.,128.,129.,130.,
131.,132.,133.,134.,135.,136.,137.,138.,139.,140.,
141.,142.,143.,144.,145.,146.,147.,148.,149.,150.,
151.,152.,153.,154.,155.,156.,157.,158.,159.,160.,
161.,162.,163.,164.,165.,166.,167.,168.,169.,170.,
171.,172.,173.,174.,175.,176.,177.,178.,179.,180.,
181.,182.,183.,184.,185.,186.,187.,188.,189.,190.,
191.,192.,193.,194.,195.,196.,197.,198.,199.,200.,
201.,202.,203.,204.,205.,206.,207.,208.,209.,210.,
211.,212.,213.,214.,215.,216.,217.,218.,219.,220.,
221.,222.,223.,224.,225.,226.,227.,228.,229.,230.,
231.,232.,233.,234.,235.,236.,237.,238.,239.,240.,
241.,242.,243.,244.,245.,246.,247.,248.,249.,250.,
251.};

  double _mass_op[nmass];
  double _lambda_op[nmass];
  int index = 0;

  for (int mass = 0; mass < nmass; mass++) {
    char filename[256];
    sprintf(filename,"outputs/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass%.3g_2Sigma.root",masses[mass]);
    cerr << filename << endl;
    TFile fin(filename);
    TH1D* h_op = static_cast<TH1D*>(fin.Get("Sensitivity Vector"));
	if (!h_op) break;
    //_mass_op[index] = double(mass); 
    _mass_op[index] = double(masses[mass]); 
    //_lambda_op[index] = h_op->GetBinContent(mass); 
	cerr << "_mass_op = " << double(masses[mass]) << endl;
    cerr << "h_op->GetNbinX() = " << h_op->GetNbinsX() << endl;
    int bin = h_op->FindBin(double(masses[mass]));
    cerr << "bin = " << bin << endl;
    cerr << "h_op->GetBinCenter(bin) = " << h_op->GetBinCenter(bin) << endl;
	cerr << "h_op->GetBinContent(int(h_op->FindBin(mass)) = " << h_op->GetBinContent(int(h_op->FindBin(masses[mass])));
    _lambda_op[index] = h_op->GetBinContent(int(h_op->FindBin(masses[mass])));
    index++;
  }
  TGraph* g_op = new TGraph(index,_mass_op,_lambda_op);
  g_op->Draw("ap");

#if 0
  for (int mass = 1; mass < nmass; mass++) {
    cerr << "mass = " << mass << endl;
    stringstream fname_op1;
    fname_op1 << "outputs/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass" << mass << "_2Sigma.root" << ends; 
    //fname_op1 << "outputs_run10_emax505/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass" << mass << "_2Sigma.root" << ends; 
    //fname_op1 << "outputs_wo_run10_emax505/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass" << mass << "_2Sigma.root" << ends; 
    //fname_op1 << "outputs_run_all_emax505/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass" << mass << "_2Sigma.root" << ends; 
    //fname_op1 << "outputs_run1_emax505/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass" << mass << "_2Sigma.root" << ends; 
    //fname_op1 << "outputs_emax550/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass" << mass << "_2Sigma.root" << ends; 
    //fname_op1 << "outputs_emax1000/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass" << mass << "_2Sigma.root" << ends; 
    //fname_op1 << "outputs_test/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass" << mass << "_2Sigma.root" << ends; 

    TFile fin_op1(fname_op1.str().data());
    TH1D* h_op1 = static_cast<TH1D*>(fin_op1.Get("Sensitivity Vector"));
    //TH1D* h_op1 = static_cast<TH1D*>(fin_op1.Get("Sensitivity Axial-vector"));
    _mass_op1[index] = double(mass); 
    _lambda_op1[index] = h_op1->GetBinContent(mass); 
    index++;
  }
  TGraph* g_op1 = new TGraph(index,_mass_op1,_lambda_op1);
  g_op1->Draw("ap");
#endif
}
