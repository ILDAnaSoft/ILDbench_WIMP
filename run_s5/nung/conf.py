#!/usr/bin/python
import os

# samples will be chosen from the follwoing directory.
#===== for s5 sample with new B field map
LISTDIR="/hsm/ilc/grid/storm/prod/ilc/mc-opt-3/ild/dst-merged/500-TDR_ws/2f_Z_nuNg/ILD_s5_o1_v02/v02-00-02"

FILESUFFIX="slcio"
# samples will be chosen by searching the follwoing label in the file names.
PROCESSES=["nung.eL.pR","nung.eR.pL"]

# geometry file
#===== for s5 sample
GEARFILE="/cvmfs/ilc.desy.de/sw/ILDConfig/v02-00-01/StandardConfig/production/Gear/gear_ILD_s5_v02.xml"

# number of input files per one steering file. 
nfilesInOneshot = 5; 

# directory that includes template xml files. 
TEMPLATEXMLORIGDIR = os.environ['MPDIR'] + "/run_s5/XML_TMPLATES"
#===== samples includes MCParticle (l5, s5 sample)
TEMPLATEFILE       = "monophoton.xml"

#===== for s5 sample
OUTPUT_PREFIX      = "s5_500GeV."


# no need to change below
# common
LOGDIR      = "log"
XMLDIR      = "generatedXMLs"
TEMPLATEDIR = "templateXMLs"
OUTDIR_ROOT = "root"
SPACE       = "                 "
