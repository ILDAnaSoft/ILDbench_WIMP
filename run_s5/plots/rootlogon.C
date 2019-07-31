{
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.

  TString drawPlotsMacroPath(topDirPath+"/macros/drawPlots.C");
  gROOT->LoadMacro(drawPlotsMacroPath.Data());

  TString makeSigAndBkgDistMacroPath(topDirPath+"/macros/makeSigAndBkgDist.C");
  gROOT->LoadMacro(makeSigAndBkgDistMacroPath.Data());

  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  gROOT->LoadMacro(styleMacroPath.Data());
}
