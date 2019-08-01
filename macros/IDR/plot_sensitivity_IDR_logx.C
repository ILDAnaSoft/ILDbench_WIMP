void plot_sensitivity_IDR_logx()
{
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  gROOT->LoadMacro(styleMacroPath.Data());

  const int nmass = 255;
  double _mass[nmass];
  double _lambda_l5_op0[nmass];
  double _lambda_l5_op1[nmass];
  double _lambda_l5_op2[nmass];
  double _lambda_s5_op0[nmass];
  double _lambda_s5_op1[nmass];
  double _lambda_s5_op2[nmass];
  int index = 0;

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

  for (int i = 0; i < nmass; i++) {
    char fname_l5_op0[256];
    char fname_l5_op1[256];
    char fname_l5_op2[256];
    char fname_s5_op0[256];
    char fname_s5_op1[256];
    char fname_s5_op2[256];
    sprintf(fname_l5_op0,"run_l5/plots/tsys_H20_vector_new/outputs/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass%.3g_2Sigma.root",masses[i]);
    sprintf(fname_l5_op1,"run_l5/plots/tsys_H20_scalar_new/outputs/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass%.3g_2Sigma.root",masses[i]);
    sprintf(fname_l5_op2,"run_l5/plots/tsys_H20_axialvector_new/outputs/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass%.3g_2Sigma.root",masses[i]);
    sprintf(fname_s5_op0,"run_s5/plots/tsys_H20_vector_new/outputs/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass%.3g_2Sigma.root",masses[i]);
    sprintf(fname_s5_op1,"run_s5/plots/tsys_H20_scalar_new/outputs/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass%.3g_2Sigma.root",masses[i]);
    sprintf(fname_s5_op2,"run_s5/plots/tsys_H20_axialvector_new/outputs/Sensitivity_Lumi_4000_Lumi_LL_400_Lumi_LR_1600_Lumi_RL_1600_Lumi_RR_400_Mass%.3g_2Sigma.root",masses[i]);

    _mass[index] = masses[i]; 

    TString filePath_l5_op0(topDirPath+fname_l5_op0);
    TString filePath_s5_op0(topDirPath+fname_s5_op0);
    TString filePath_l5_op1(topDirPath+fname_l5_op1);
    TString filePath_s5_op1(topDirPath+fname_s5_op1);
    TString filePath_l5_op2(topDirPath+fname_l5_op2);
    TString filePath_s5_op2(topDirPath+fname_s5_op2);
    TFile fin_l5_op0(filePath_l5_op0.Data());
    TH1D* h_l5_op0 = static_cast<TH1D*>(fin_l5_op0.Get("Sensitivity Vector"));
	if (!h_l5_op0) break;
    _lambda_l5_op0[index] = h_l5_op0->GetBinContent(int(h_l5_op0->FindBin(masses[i])))/1.e3;

    TFile fin_l5_op1(filePath_l5_op1.Data());
    TH1D* h_l5_op1 = static_cast<TH1D*>(fin_l5_op1.Get("Sensitivity Scalar,s-channel"));
    _lambda_l5_op1[index] = h_l5_op1->GetBinContent(int(h_l5_op1->FindBin(masses[i])))/1.e3;

    TFile fin_l5_op2(filePath_l5_op2.Data());
    TH1D* h_l5_op2 = static_cast<TH1D*>(fin_l5_op2.Get("Sensitivity Axial-vector"));
    _lambda_l5_op2[index] = h_l5_op2->GetBinContent(int(h_l5_op2->FindBin(masses[i])))/1.e3;

    TFile fin_s5_op0(filePath_s5_op0.Data());
    TH1D* h_s5_op0 = static_cast<TH1D*>(fin_s5_op0.Get("Sensitivity Vector"));
    _lambda_s5_op0[index] = h_s5_op0->GetBinContent(int(h_s5_op0->FindBin(masses[i])))/1.e3;

    TFile fin_s5_op1(filePath_s5_op1.Data());
    TH1D* h_s5_op1 = static_cast<TH1D*>(fin_s5_op1.Get("Sensitivity Scalar,s-channel"));
    _lambda_s5_op1[index] = h_s5_op1->GetBinContent(int(h_s5_op1->FindBin(masses[i])))/1.e3;

    TFile fin_s5_op2(filePath_s5_op2.Data());
    TH1D* h_s5_op2 = static_cast<TH1D*>(fin_s5_op2.Get("Sensitivity Axial-vector"));
    _lambda_s5_op2[index] = h_s5_op2->GetBinContent(int(h_s5_op2->FindBin(masses[i])))/1.e3;

    index++;
  }

  TH1D* axis = new TH1D("axis","",1,1.e-9,1.e3);
  axis->SetTitle(";M_{#chi} [GeV];#Lambda_{95} [TeV]");
  axis->GetYaxis()->SetTitleOffset(1.);
  axis->GetXaxis()->SetTitleOffset(1.25);
  axis->SetMaximum(3.4);
  //axis->GetXaxis()->SetRangeUser(1.e-9,1.e3);

  TGraph* g_l5_op0 = new TGraph(index,_mass,_lambda_l5_op0);
  //g_l5_op0->SetTitle(";M_{#chi} [GeV];#Lambda_{95} [GeV]");
  //g_l5_op0->GetYaxis()->SetTitleOffset(1.45);
  //g_l5_op0->GetXaxis()->SetRangeUser(1.e-9,1.e3);

  TGraph* g_l5_op1 = new TGraph(index,_mass,_lambda_l5_op1);
  TGraph* g_l5_op2 = new TGraph(index,_mass,_lambda_l5_op2);
  TGraph* g_s5_op0 = new TGraph(index,_mass,_lambda_s5_op0);
  TGraph* g_s5_op1 = new TGraph(index,_mass,_lambda_s5_op1);
  TGraph* g_s5_op2 = new TGraph(index,_mass,_lambda_s5_op2);
  g_l5_op0->SetLineColor(4);
  g_l5_op1->SetLineColor(4);
  g_l5_op2->SetLineColor(4);
  g_s5_op0->SetLineColor(2);
  g_s5_op1->SetLineColor(2);
  g_s5_op2->SetLineColor(2);
  g_l5_op0->SetLineStyle(1);
  g_l5_op1->SetLineStyle(9);
  g_l5_op2->SetLineStyle(2);
  g_s5_op0->SetLineStyle(1);
  g_s5_op1->SetLineStyle(9);
  g_s5_op2->SetLineStyle(2);
  g_l5_op0->SetLineWidth(4);
  g_l5_op1->SetLineWidth(4);
  g_l5_op2->SetLineWidth(4);
  g_s5_op0->SetLineWidth(2);
  g_s5_op1->SetLineWidth(2);
  g_s5_op2->SetLineWidth(2);

  TCanvas* c = new TCanvas("c","",600,600);
  axis->Draw();
  //g_l5_op0->Draw("al");
  g_l5_op0->Draw("l same");
  g_l5_op1->Draw("l same");
  g_l5_op2->Draw("l same");
  g_s5_op0->Draw("l same");
  g_s5_op1->Draw("l same");
  g_s5_op2->Draw("l same");


  TLatex *tex = new TLatex();
  TBox* b = new TBox(1.e-9,0,1e3,0.5);
  b->SetFillColorAlpha(kGray+1, 1);
  b->Draw("same");
  tex->DrawLatexNDC(0.5,0.22,"#scale[0.8]{#color[0]{EFT not valid}}");

  TLegend *leg = new TLegend(0.22,0.65,0.58,0.30);
  leg->SetTextFont(62);
  leg->SetTextSize(0.03); 
  leg->SetTextAlign(12);
  leg->AddEntry(g_l5_op0,"IDR-L, Vector","l"); 
  leg->AddEntry(g_l5_op1,"IDR-L, Scalar","l"); 
  leg->AddEntry(g_l5_op2,"IDR-L, Axial Vector","l"); 
  leg->AddEntry(g_s5_op0,"IDR-S, Vector","l"); 
  leg->AddEntry(g_s5_op1,"IDR-S, Scalar","l"); 
  leg->AddEntry(g_s5_op2,"IDR-S, Axial Vector","l"); 
  leg->Draw();


  tex->SetTextSize(0.05);
  tex->DrawLatexNDC(0.22,0.67,"#scale[1.5]{#font[62]{ILD}} #font[42]{preliminary}");

  tex->DrawLatexNDC(0.55,0.42,"#scale[0.8]{#color[15]{ #font[72]{Expected WIMP}}}"); 
  tex->DrawLatexNDC(0.55,0.37,"#scale[0.8]{#color[15]{ #font[72]{exclusion region}}}");

  c->SetLogx();
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.05);
  c->SetTopMargin(0.05);
  c->SetBottomMargin(0.18);
  c->RedrawAxis();

  c->Print("sensitivity_H20_IDR_logx.pdf");
  c->Print("sensitivity_H20_IDR_logx.C");

}
