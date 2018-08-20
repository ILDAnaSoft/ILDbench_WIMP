
## ILDbench_WIMP

Mono-photon WIMP search

### Installation

Explain here:

- what are the package dependencies (iLCSoft, others ?)
- how to compile your package. Should normally be something like:

```shell
source /path/to/ilcsoft/init_ilcsoft.sh
mkdir build
cd build
cmake -C $ILCSOFT/ILCSoft.cmake ..
make install
```

### How to run the analysis

1) cd scripts/run_DBD (or run_l5, run_s5)
2) mkdir nung (for nung analysis)
3) cd nung
4) cp ../SKELTON/*.py .         // copy scripts to submit many jobs to a cpu cluster.
5) (Edit conf.py if necessary)
6) python makeSteeringFiles.py  // produce many steering files from the directory path specified in conf.py.
7) python manyRun.py            // run the steering files created above.

Example:

```shell
export MARLIN_DLL=./lib/libILDbench_WIMP.so
Marlin ./scripts/ExampleProcessor.xml
```

If you want to provide a lot of details on your analysis, use the doc/Readme.md and point to it from this Readme.md file:

More documentation available here in [doc/Readme.md](doc/Readme.md) !

### Issues and contact

Explain here how can people reach you:

- via the Github issue interface. For the skeleton package: https://github.com/ILDAnaSoft/ILDbench_WIMP/issues
- **not mandatory**:
    - email address
    - working institute


