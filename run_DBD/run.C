// How to run : root -l run.C
{
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString MacroPath1(topDirPath+"/macros/eventselection.C");
  TString MacroPath2("input.C");
  TString MacroPath3(topDirPath+"/macros/analysis.C");
  gROOT->LoadMacro(MacroPath1.Data());
  gROOT->LoadMacro(MacroPath2.Data());
  gROOT->LoadMacro(MacroPath3.Data());
  analysis();
}
