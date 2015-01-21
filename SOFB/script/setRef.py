## Running from the same server to avoid EPICS ARRARY SIZE issus #
## export EPICS_CA_MAX_ARRAY_BYTES=800000


from numpy import *
import numpy as np

import sys
import time 
import cothread
from cothread.catools import caput, caget

xREF=0.0
yREF=0.0

refPV= 'vSR-SOFB{BPM}orb:xRef'
refZero = array(floor(random.rand(180)*0))
for i in range(0,179):
	refZero[i]= xREF
caput(refPV, refZero,wait=False) 

refPV= 'vSR-SOFB{BPM}orb:yRef'
refZero = array(floor(random.rand(180)*0))
for i in range(0,179):
	refZero[i]= yREF
caput(refPV, refZero,wait=False) 

spPV= 'vSR-SOFB{}deltaSP'
spSet = array(floor(random.rand(360)*.0))
caput(spPV, spSet,wait=False) 


def sv(filename,x):
	ff=open(filename,'w')
	pickle.dump(x,ff)
	ff.close()

def rl(filename):
	ff=open(filename)
	xx=pickle.load(ff)
	ff.close()
	return xx

print "vvvvvvvvvvvvvvvvvvvvvvvvv333"
