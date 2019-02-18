#!/usr/bin/python
import os
cmd = "bsub -q l -o log.std -e log.err \"./TSysLimit 1\""
#cmd = "bsub -q l -o log.std -e log.err \"./TSysLimit 2 0 0\""
os.system(cmd)

