void runMakeSigAndBkgDist(double mass = 1) {
  gROOT->SetBatch(kTRUE);
  TString rootFilePath(topDirPath+"/run_s5/plots/plots.root");
  makeSigAndBkgDist(rootFilePath,mass); // load in rootlogon.C
}
