// Set input files (output of MonoPhotonProcessor) depending on processes.
// Will stop reading when a file specified doesn't exist. 
// Use a small number for testing.
const int NMAX_INPUTFILES = 1;

void SetInputFiles(Event* ev)
{
  switch(ev->getProcessType()) {
    case nungLR:
       {
         ev->clearFileList();
         int nmaxfiles = NMAX_INPUTFILES; 
         for (int i = 1; i <= nmaxfiles; i++) {
             stringstream fname;
             fname << "nung/root/dbd_500GeV.nung.eL.pR_" << i << ".root" << ends;
             if (gSystem->AccessPathName(fname.str().data())) break;
             ev->addToFileList(fname.str());
         }
       }
       break;
    case nungRL:
       {
         ev->clearFileList();
         int nmaxfiles = NMAX_INPUTFILES; 
         for (int i = 1; i <= nmaxfiles; i++) {
             stringstream fname;
             fname << "nung/root/dbd_500GeV.nung.eR.pL_" << i << ".root" << ends;
             if (gSystem->AccessPathName(fname.str().data())) break;
             ev->addToFileList(fname.str());
         }
       }
       break;
    case bhabhangLL:
       {
         ev->clearFileList();
         int nmaxfiles = NMAX_INPUTFILES; 
         for (int i = 1; i <= nmaxfiles; i++) {
             stringstream fname;
             fname << "bhabhang/root/dbd_500GeV.bhabhang.eL.pL_" << i << ".root" << ends;
             if (gSystem->AccessPathName(fname.str().data())) break;
             ev->addToFileList(fname.str());
         }
       }
       break;
    case bhabhangLR:
       {
         ev->clearFileList();
         int nmaxfiles = NMAX_INPUTFILES; 
         for (int i = 1; i <= nmaxfiles; i++) {
             stringstream fname;
             fname << "bhabhang/root/dbd_500GeV.bhabhang.eL.pR_" << i << ".root" << ends;
             if (gSystem->AccessPathName(fname.str().data())) break;
             ev->addToFileList(fname.str());
         }
       }
       break;
    case bhabhangRL:
       {
         ev->clearFileList();
         int nmaxfiles = NMAX_INPUTFILES; 
         for (int i = 1; i <= nmaxfiles; i++) {
             stringstream fname;
             fname << "bhabhang/root/dbd_500GeV.bhabhang.eR.pL_" << i << ".root" << ends;
             if (gSystem->AccessPathName(fname.str().data())) break;
             ev->addToFileList(fname.str());
         }
       }
       break;
    case bhabhangRR:
       {
         ev->clearFileList();
         int nmaxfiles = NMAX_INPUTFILES; 
         for (int i = 1; i <= nmaxfiles; i++) {
             stringstream fname;
             fname << "bhabhang/root/dbd_500GeV.bhabhang.eR.pR_" << i << ".root" << ends;
             if (gSystem->AccessPathName(fname.str().data())) break;
             ev->addToFileList(fname.str());
         }
       }
       break;
    default:
       cerr << "ProcessType must be set with Event::setEventType()." << endl;
       abort();
  }
}
