#include "/home/ilc/yonamine/work/MonoPhoton/Git/upload/ILDbench_WIMP/macros/util.C"
#include "/home/ilc/yonamine/work/MonoPhoton/Git/upload/ILDbench_WIMP/macros/makeSigAndBkgDist.C"
void runMakeSigAndBkgDist(double mass = 1) {
  gROOT->SetBatch(kTRUE);
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  TString rootFilePath(topDirPath+"/run_DBD/plots/plots.root");
  gROOT->LoadMacro(styleMacroPath.Data());
  makeSigAndBkgDist(rootFilePath,mass);
}
