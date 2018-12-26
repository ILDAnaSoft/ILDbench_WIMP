void UpdateMetaData()
{
  // Get genmetaByID.json if any updated version.
  gSystem->Exec("wget -N https://ild.ngt.ndu.ac.jp/CDS/files/genmetaByID.json");

  // Check if the file is updated.
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString fileName("genmetaByID.json");
  
  TString findCmd("find -type l -name ");
  findCmd += fileName;
  TString checklink(gSystem->GetFromPipe(findCmd.Data()));

  if (checklink.Length()==0) { // When the file is updated.

    // Store the file in a common directory and make a symbolic link.
    TString MacroDir(topDirPath+"/macros");
    TString rsyncCmd("rsync -t ");
    rsyncCmd += fileName;
    rsyncCmd += " ";
    rsyncCmd += MacroDir; 
    gSystem->Exec(rsyncCmd.Data());
    TString rmCmd("rm ");
    rmCmd += fileName;
    //gSystem->Exec("rm genmetaByID.json");
    gSystem->Exec(rmCmd.Data());
    TString lnCmd("ln -s ");
    lnCmd += MacroDir;
    lnCmd += "/";
    lnCmd += fileName;
    lnCmd += " .";
    gSystem->Exec(lnCmd.Data());

    // Match the time stamps between the original file and the symbolic link.
    TString statCmd("stat --format=%y ");
    statCmd += MacroDir;
    statCmd += "/";
    statCmd += fileName;
    TString timestamp(gSystem->GetFromPipe(statCmd.Data()));
    TString touchCmd("touch ");
    touchCmd += fileName; 
    touchCmd += " -h -m -d \"";
    touchCmd += timestamp;
    touchCmd += "\"";
    gSystem->Exec(touchCmd.Data());
  }
}

float getXsec(TString procname) 
{
  TString topDirPath(gSystem->GetFromPipe("echo $MPDIR")); // MPDIR should be defined in an init script.
  TString MacroDir(topDirPath+"/macros");
  TString getXsecCmd("python ");
  getXsecCmd += MacroDir + "/getXsec.py " + procname;
  return atof(gSystem->GetFromPipe(getXsecCmd.Data()));
}
