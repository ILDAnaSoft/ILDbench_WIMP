#!/usr/bin/python
import os
#cmd = "bsub -q l -o log.std -e log.err \"./TSysLimit 1 0 0\""
for mass in range(1,250):
	cmd = "bsub -q l -o log_m" + str(mass) + "e0p0.std -e log_m" + str(mass)+ "e0p0.err \"./TSysLimit " + str(mass) + " 0 0\""
	os.system(cmd)
	cmd = "bsub -q l -o log_m" + str(mass) + "e0.8p-0.3.std -e log_m" + str(mass)+ "e0.8p-0.3.err \"./TSysLimit " + str(mass) + " 0.8 -0.3\""
	os.system(cmd)

