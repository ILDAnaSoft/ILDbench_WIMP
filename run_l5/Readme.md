## How to run

1) Run MonophotonProcessor (produce TTree that contain low level information.) 
	- Move into the subdirectory with process name (nung/bhabhang).
	- Edit conf.py.
		Most probable required changes are LISTDIR and GEARFILE. The scripts described later will search input slcio files that have a keyword, which is specified with PROCESSES, in their file names recursively starting from LISTDIR.  
	- Run makeSteeringFiles.py.
		`python makeSteeringFiles.py`	
		This will generate steering files from the information in conf.py and also prepare some output directories.
	- Check new steering files produced in generatedXMLs. 
		These files are created based on monophoton.xml in XML_TEMPLATES. This can be modfied in conf.py.
	- Run manyRun.py. 
		This scripts will submit jobs using all the steering files in generatedXMLs. Note that this script is only tested on KEKCC.

2) Run run.C (produce ROOT file that contain histograms.)
	- Move to the directory where you can find nung and bhabhang directories. 
	- Edit input.C if necessary.
		You have to specify the directory where you store the output root files from MonophotonProcesssor.
	- Run run.C.
		`root -l run.C`
		This will load and run analysis macros. 

3) Run runDraw.C (produce PDF files.)
	- Move to plots directory. 
	- Run runDraw.C. 
		`root -l runDraw.C`

3') Plot exclusion limit (produce PDF files.)
	- See README in plots directory. 
