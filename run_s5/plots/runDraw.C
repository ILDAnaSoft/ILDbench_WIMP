void runDraw() 
{
  gROOT->SetBatch(kTRUE);

  TString rootFilePath(topDirPath+"/run_s5/plots/plots.root");
  drawPlots(rootFilePath); // load in rootlogon.C
}
