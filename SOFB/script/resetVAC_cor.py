from numpy import *
import numpy as np

import sys
import time 
import cothread
from cothread.catools import caput, caget

sp=0;

#!/bin/bash
temp=0.0
index = ['01','03','05','07','09','11','13','15','17','19','21','23','25','27','29']
ps = ['CL1A','CL2A','CM1B','CM1A','CH2B','CH1B']
for i in index: 
	for j in ps:
		PV1= 'vSR:C'+ i + '-MG{PS:' + j + '}I:Sp1-SP' 
		PV2= 'vSR:C'+ i + '-MG{PS:' + j + '}I:Sp2-SP' 
		caput(PV1,sp)
		caput(PV2,sp)
		print "*"


temp=0.0
index = ['02','04','06','08','10','12','14','16','18','20','22','24','26','28','30']
ps = ['CH1A','CH2A','CM1B','CM1A','CL2B','CL1B']
for i in index: 
	for j in ps:
		PV1= 'vSR:C'+ i + '-MG{PS:' + j + '}I:Sp1-SP' 
		PV2= 'vSR:C'+ i + '-MG{PS:' + j + '}I:Sp2-SP' 
		caput(PV1,sp)
		caput(PV2,sp)
		print "-"


