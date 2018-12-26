#!/usr/bin/python

import sys,json

def getXsec(process):
	fin = open("genmetaByID.json")
	s = fin.read()
	dict = json.loads(s)
	for key in dict:
		elements = dict[key]
		pname = elements["process_names"]	
		epol  = elements["polarization1"]
		ppol  = elements["polarization2"]
		
		xsec  = elements["cross_section_in_fb"]
		#if "nung" in pname:
		#	print pname + " " + epol + " " + ppol + " " + xsec
		#elif "bhabhang" in pname:
		#	print pname + " " + epol + " " + ppol + " " + xsec
		if process in pname + ".e" + epol + ".p" + ppol:
			print xsec

args = sys.argv
if len(args)==2:
	getXsec(args[1])
