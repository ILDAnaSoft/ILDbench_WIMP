
## ILDbench_WIMP

Mono-photon WIMP search
The analysis codes in this repository are originated from
the macros developed by
Moritz Habermehl for his PhD thesis and
aiming for simplifying the analysis procedures as much as possible.

3 steps for plots :

1) Run MonoPhoton Processor in Marlin framework. This main function
is to extract necessary variables and to keep them in convenient formats.
This step converts slcio file to root file.
Raw level data can be accessed from these output root files.
The steering files to run this processor can be produced by python scripts in
run_DBD, run_l5, run_s5 directories for multiple inputs files.

2) Run run.C macro in ROOT framework, which invokes some other macros in macros directory. 
This step is the main part of the analysis based on the study by Moritz.
This produces individual histograms that will be used as ingredients for final plots. 
This process is time-consuming and thus ideally is to be run once.
On the ohter hand, it would be convenient if we can decorate final plots later. 
This is why step3 (next step) is separated from this process.
Since run_DBD, run_l5 and run_s5 are identical except for input files,
the part where input files are specified is moved into input.C, so that
we can commonly use the other parts (e.g. analysis.C, eventselection.C).

3) Run plots/runDraw.C macro in ROOT framework. This main function
is to compile/decorate histgrams. 
("Save as .C" doesn't work well for THStack objects at the time of this writing.)

### Installation

```shell
source /path/to/ilcsoft/init_ilcsoft.sh
mkdir build
cd build
cmake -C $ILCSOFT/ILCSoft.cmake ..
make install
```

### How to run the analysis
0) setup enviroment
  a) source /path/to/ilcsoft/init_ilcsoft.sh
  b) cd ILDbench_WIMP
  c) export MPDIR="$PWD"
     export MARLIN_DLL="$MPDIR/MonoPhotonProcessors/lib/libMonoPhotonProcessors.so:$MARLIN_DLL"

  For convenience, would be better to copy init_ilcsoft.sh to this directory and add b) into it.

1) cd run_DBD (or run_l5, run_s5)
3) cd nung (or bhabhang)
4) cp ../SKELTON/*.py .         // copy utility scripts e.g. to submit many jobs to CPU clusters.
5) (Edit conf.py if necessary)
6) python makeSteeringFiles.py  // produce many steering files from the directory path specified in conf.py.
6') Marlin generatedXMLs/dbd_500GeV.nung.eL.pR_1.xml // test run. stop if you see no problem. 
7) python manyRun.py            // run all the steering files created above.

### Issues and contact
- via the Github issue interface. For the skeleton package: https://github.com/ILDAnaSoft/ILDbench_WIMP/issues


