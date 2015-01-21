## Running from the same server to avoid EPICS ARRARY SIZE issus #
## export EPICS_CA_MAX_ARRAY_BYTES=800000


from numpy import *
import numpy as np

import sys
import time 
import cothread
from cothread.catools import caput, caget

spPV= 'vSR-SOFB{}SP'
spSet = array(floor(random.rand(360)*0.0))
caput(spPV, spSet,wait=False) 

print "vvvvvvvvvvvvvvvvvvvvvvvvv333"
