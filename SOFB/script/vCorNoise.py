## Running from the same server to avoid EPICS ARRARY SIZE issus #
## export EPICS_CA_MAX_ARRAY_BYTES=900000
# reduce(min, ormXXRV.flat) for min in the array

############  SVD Calculation ###############
import sys
import time 
from numpy import *
import numpy as np
import cothread
from cothread.catools import caput, caget
import pickle

sp=0
n=0
spPV='vSR:C30-MG{PS:CH1A}I:Sp1-SP'
while(1):
	sp=0.00005*math.cos(6.28*n)
	caput(spPV, sp, wait=False) 
	temp=caget(spPV)
	print temp
	n=n+1
	time.sleep(20)
	

