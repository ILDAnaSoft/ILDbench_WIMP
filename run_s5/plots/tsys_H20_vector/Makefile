#========================================================
#	a simple makefile to compile our first programs
#========================================================
.SUFFIXES : .o .c .C .h

CC = g++ -g -Wall -std=c++11 
#CFLAGS= -I`root-config --incdir` -I . -fPIC
CFLAGS= -I$(shell root-config --incdir) -I . -fPIC
#CLIBS= -L/cern/pro/lib -lmathlib -lkernlib -lpacklib -llapack3 -lblas -L /usr/lib -lshift -lnsl -lcrypt -ldl
# CLIBS= -L/usr/lib64 -L/cern/pro/lib -lmathlib -lkernlib -lpacklib -llapack -lblas  -L /usr/lib -lnsl -lcrypt -ldl
#CXXFLAGS=-g `root-config --cflags` 
CXXFLAGS=-g $(shell root-config --cflags) 
#LDFLAGS= `root-config --ldflags` -L.
#LDFLAGS= $(CFLAGS)  `root-config --libs`  -lTreePlayer
LDFLAGS= $(CFLAGS)  $(shell root-config --libs)  -lTreePlayer
#FLIBS= -lg2c -lm 
FLIBS= -lm 
F77=g77
# CLIBS=`cernlib`
LIB=stslimit
LB=lib$(LIB).so
DICTLB=lib$(LIB)Dict.so

all:  .rootversion  tags $(OBJC) testlimit

clean:
	rm -f Makefile.dep *.o *.a

.rootversion: rootversion

rootversion:
	@if [[ -f .rootversion ]]; \
        then \
          echo ".rootversion exists: " ; \
          cat .rootversion ; \
          if [[ `cat .rootversion` == `root-config --version` ]] ; \
          then echo "root version has not changed." ; \
          else echo "root version has changed! => will recompile everything."; \
            root-config --version > .rootversion ; \
            make clean;  \
          fi \
        else echo ".rootversion will be created." \
          root-config --version > .rootversion ; \
          make clean ;\
        fi

Makefile.dep: *.h *.C .rootversion
	touch Makefile.dep
	makedepend -fMakefile.dep -I. -I$(shell root-config --incdir) *.C
#makedepend -fMakefile.dep -I. -I`root-config --incdir` *.C

tags:
	ctags ./*.[hC]
        
depend: Makefile.dep
        
include Makefile.dep

OBJC=
OBJC += TSysLimit.o
OBJC += TSysLimitChannel.o
OBJC += TSysLimitResult.o
OBJC += TSysLimitResultPBock.o
OBJC += TSysLimitResultLogL.o
OBJC += TSysLimitScan.o

CINTOBJC=
CINTOBJC += TSysLimitDict.o
CINTOBJC += TSysLimitChannelDict.o
CINTOBJC += TSysLimitResultDict.o
CINTOBJC += TSysLimitResultPBockDict.o
CINTOBJC += TSysLimitResultLogLDict.o
CINTOBJC += TSysLimitScanDict.o

             
# ${LB}: $(OBJC)
# 	ar rv $@ $(OBJC)
# 
# ${DICTLB}: $(CINTOBJC)
# 	ar rv $@ $(CINTOBJC)
# 
$(LB): $(OBJC)
#	ld --export-dynamic -shared -rpath . $(OBJC) -o $(LB)
#	$(CC) --export-dynamic -shared  $(OBJC) -o $(LB)
	$(CC) -rdynamic -shared  $(OBJC) -o $(LB)

# $(DICTLB): $(CINTOBJC)
# 	$(CC) --export-dynamic -shared $(CINTOBJC) -o $(DICTLB)
# 
# testlimit: testlimit.o $(LB)
# 	$(CC) testlimit.o $(LDFLAGS) $(LB)  \
#         -o testlimit


TSys_ke: TSysLimit_searches_ke.C $(LB) Makefile
	$(CC) $(CXXFLAGS) $< -o  $@ $(LDFLAGS) $(LB) \
	$(ROOTLIBS) -lrt

TSysLimit: TSysLimit_searches.C $(LB) Makefile
	$(CC) $(CXXFLAGS) $< -o  $@ $(LDFLAGS) $(LB) \
	$(ROOTLIBS) -lrt

TLimit_shape: TLimit_lambda_searches_shape.C $(LB) Makefile
	$(CC) $(CXXFLAGS) $< -o  $@ $(LDFLAGS) $(LB) \
	$(ROOTLIBS) -lrt	

# Write my program and try to get resulats
OneBinCL: CLc_searching_lambda.C $(LB) Makefile
	$(CC) $(CXXFLAGS) $< -o  $@ $(LDFLAGS) $(LB) \
	$(ROOTLIBS) -lrt
	
# Write my program and try to get resulats
OneBinTSys: TSysLimit_searches_onebin.C $(LB) Makefile
	$(CC) $(CXXFLAGS) $< -o  $@ $(LDFLAGS) $(LB) \
	$(ROOTLIBS) -lrt
		
	
	
		
# testlimit: testlimit.C $(LB) $(DICTLB) Makefile
# 	$(CC) $(CXXFLAGS) $< -o  $@ $(LDFLAGS) -l$(LIB)Dict \
# 	$(ROOTLIBS) -lrt
          
docu: 
	doxygen doxygen.config
	make -C doc/latex ps_2on1
	cd doc/latex ; rm *.tex *.dvi *.aux *.eps *.log *.ilg *.ind *.sty Makefile *.idx *.toc ; gzip -f *.ps 

.C.o:
	$(CC) $< $(CFLAGS)  -c -o $@
.C :
	$(CC) $< $(LDFLAGS) $(CLIBS) $(FLIBS) -o $@
.f.o :
	$(F77) $< -c -o $@


# DO NOT DELETE
