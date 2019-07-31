void runDraw() 
{
  gROOT->SetBatch(kTRUE);

  TString rootFilePath(topDirPath+"/run_l5/plots/plots.root");
  drawPlots(rootFilePath); // load in rootlogon.C
}
