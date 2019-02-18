#include "/home/ilc/yonamine/work/MonoPhoton/Git/upload/ILDbench_WIMP/macros/util.C"
#include "/home/ilc/yonamine/work/MonoPhoton/Git/upload/ILDbench_WIMP/macros/drawPlots.C"
void runDraw() {
  gROOT->SetBatch(kTRUE);
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString styleMacroPath(topDirPath+"/macros/ildstyle.C");
  TString rootFilePath(topDirPath+"/run_l5/plots/plots.root");
  gROOT->LoadMacro(styleMacroPath.Data());
  //gROOT->LoadMacro(utilMacroPath.Data());
  //gROOT->LoadMacro(drawPlotsMacroPath.Data());
  drawPlots(rootFilePath);
}
