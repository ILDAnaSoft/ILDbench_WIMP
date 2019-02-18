#!/usr/bin/python
import os
#cmd = "bsub -q l -o log.std -e log.err \"./TSysLimit 1 0 0\""
for mass in range(1,250):
	cmd = "bsub -q l -o log_m" + str(mass) + " -e log_m" + str(mass)+ ".err \"./TSysLimit " + str(mass) + "\""
	os.system(cmd)

